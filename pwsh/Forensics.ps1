# Forensics.ps1
# Create a script to gather basic forensic data from a Windows system.

$outDir = ".\out"
New-Item -Path '.' -Name $outDir -ItemType Directory

Get-ComputerInfo | Format-Table -AutoSize | Out-File -Width 512 -FilePath "$outDir\sysinfo.txt"
Get-LocalUser | Format-Table -AutoSize | Out-File -Width 512 -FilePath "$outDir\userinfo.txt"
Get-CimInstance Win32_Process | Select ProcessId,Name,HandleCount,ExecutablePath | Sort-Object ProcessId | Format-Table -AutoSize | Out-File -Width 512 -FilePath "$outDir\procinfo.txt"
Get-NetIPAddress | Select InterfaceIndex,InterfaceAlias,IPAddress | Sort-Object InterfaceIndex | Format-Table -AutoSize | Out-File -Width 512 -FilePath "$outDir\ifinfo.txt"
Get-NetTCPConnection | Select State,LocalAddress,LocalPort,RemoteAddress,RemotePort,OwningProcess | Sort-Object State | Format-Table -AutoSize | Out-File -Width 512 -FilePath "$outDir\conntcpinfo.txt"
Get-NetUDPEndpoint   | Select LocalAddress,LocalPort,RemoteAddress,RemotePort,OwningProcess | Sort-Object LocalAddress | Format-Table -AutoSize | Out-File -Width 512 -FilePath "$outDir\connudpinfo.txt"
Get-EventLog -LogName System -Newest 100 | Out-File -Width 512 -FilePath "$outDir\eventloginfo.txt"
