# FileLastWriteTime.ps1
# Create a script to gather write times of files with PowerShell, and sort by last write time.
param([String]$file='.')

Get-ChildItem $file -File | Sort-Object LastWriteTime
