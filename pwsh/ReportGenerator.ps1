# ReportGenerator.ps1
# Create script to gather logs from several sources, parse and analyse them.
# The script should then generate a report highlighting potential incidents
# This script gets a report of all potential incidents of the past month.

$filterDate = (Get-Date).AddDays(-30)

Write-Host "Collecting event logs since $filterDate..."
$evSystem = Get-EventLog -LogName "System" | Where-Object {$_.TimeGenerated -ge $filterDate}
$evApplication = Get-EventLog -LogName "Application" | Where-Object {$_.TimeGenerated -ge $filterDate}
$evSecurity = Get-EventLog -LogName "Security" | Where-Object {$_.TimeGenerated -ge $filterDate}


Write-Host "Evaluating events..."
$bsodCount = 0
$appCrashes = @{}
$failedLogins = @{}
$secAlerts = @{}

# System events
$bsodCount = ($evSystem | Where-Object {$_.EventID -like 1001} | Measure-Object).Count

# Application events
## Evaluate app crashes
$evApplication | Where-Object {$_.EventID -like 1000} | ForEach-Object {
    $appCrashes[$_.ReplacementStrings[0]] += 1  # Appname is [0]
}

# Security events
## Evaluate failed logins
$evSecurity | Where-Object {$_.EventID -like 4625} | ForEach-Object {
    $user = (-join($_.ReplacementStrings[6], "/", $_.ReplacementStrings[5]))
    $failedLogins[$user] += 1
}
## Other potential problems
$alertIds = @(
    1102,  # Clearing of Audit Log
    4670,  # Changing of object's ACL
    4732   # User added to Security Local group
)
$evSecurity | Where-Object {$_.EventID -In $alertIds} | ForEach-Object {
    $secAlerts[$_.EventID] += 1
}

# Report
Write-Host "BSOD Count: $bsodCount"
Write-Host "App Crashes:"
foreach ($app in $appCrashes.Keys) {
    Write-Host "`t$app : $($appCrashes[$app])"
}
Write-Host "Failed Logins:"
foreach ($user in $failedLogins.Keys) {
    Write-Host "`t$user : $($failedLogins[$user])"
}
Write-Host "Alerts:"
foreach ($evId in $secAlerts.Keys) {
    Write-Host "`tEvent $evId : $($secAlerts[$evId])"
}
