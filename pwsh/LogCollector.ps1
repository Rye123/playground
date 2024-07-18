# LogCollector.ps1
# Create a script to collect "successful logon events" (Event ID 4624) for a time period,
# exporting it to an XML file for later analysis.

$filterDate = (Get-Date).AddHours(-1)  # Here, we do it 1h before
$events = Get-EventLog -LogName "Security" | Where-Object {$_.EventID -like 4624} | Where-Object {$_.TimeGenerated -ge $filterDate}

if ($events) {
    $events | Export-CliXml -Path ".\out.xml"
} else {
    Write-Host "No security logs for successful logon events since an hour ago."
}
