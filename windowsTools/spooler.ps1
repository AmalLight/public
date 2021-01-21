net stop spooler
del /q /f /s "%systemroot%\System32\Spool\Printers\*.*"
net start spooler
