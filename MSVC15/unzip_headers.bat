@echo off
setlocal
cd /d %~dp0
Call :UnZipFile "..\include\" "..\resources\dejavu.h.zip" "..\include\dejavu.h"
Call :UnZipFile "..\include\" "..\resources\unifont.h.zip" "..\include\unifont.h"
exit /b

:UnZipFile <ExtractTo> <ExtractFrom>
set vbs="_.vbs"
if exist %vbs% del /f /q %vbs% 
>%vbs%  echo Set fso = CreateObject("Scripting.FileSystemObject")
>>%vbs% echo If NOT fso.FileExists(%3) Then
>>%vbs% echo If NOT fso.FolderExists(%1) Then
>>%vbs% echo fso.CreateFolder(%1)
>>%vbs% echo End If
>>%vbs% echo dim fullPathZip, fullPathTo
>>%vbs% echo fullPathZip = fso.GetAbsolutePathName(%2)
>>%vbs% echo fullPathTo = fso.GetAbsolutePathName(%1)
>>%vbs% echo set objShell = CreateObject("Shell.Application")
>>%vbs% echo set FilesInZip=objShell.NameSpace(fullPathZip).items
>>%vbs% echo objShell.NameSpace(fullPathTo).CopyHere(FilesInZip)
>>%vbs% echo Set objShell = Nothing
>>%vbs% echo End If
>>%vbs% echo Set fso = Nothing
cscript //nologo %vbs%
if exist %vbs% del /f /q %vbs%

