# LogAnalyzer.ps1
# Create a script to summarise login attemtps

$filterDate = (Get-Date).AddDays(-1)
$successCount = (Get-EventLog -LogName "Security" | Where-Object {$_.EventID -like 4624} | Where-Object {$_.TimeGenerated -ge $filterDate} | Measure-Object).Count
$failedCount = (Get-EventLog -LogName "Security" | Where-Object {$_.EventID -like 4625} | Where-Object {$_.TimeGenerated -ge $filterDate} | Measure-Object).Count

$totalCount = $successCount + $failedCount

Write-Host "Total Login Attempts in the past day: $totalCount`n`tSuccessful: $successCount`n`tFailed: $failedCount"
