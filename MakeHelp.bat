@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by NOTEPADMT.HPJ. >"hlp\NotepadMT.hm"
echo. >>"hlp\NotepadMT.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\NotepadMT.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\NotepadMT.hm"
echo. >>"hlp\NotepadMT.hm"
echo // Prompts (IDP_*) >>"hlp\NotepadMT.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\NotepadMT.hm"
echo. >>"hlp\NotepadMT.hm"
echo // Resources (IDR_*) >>"hlp\NotepadMT.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\NotepadMT.hm"
echo. >>"hlp\NotepadMT.hm"
echo // Dialogs (IDD_*) >>"hlp\NotepadMT.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\NotepadMT.hm"
echo. >>"hlp\NotepadMT.hm"
echo // Frame Controls (IDW_*) >>"hlp\NotepadMT.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\NotepadMT.hm"
REM -- Make help for Project NOTEPADMT


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\NotepadMT.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\NotepadMT.hlp" goto :Error
if not exist "hlp\NotepadMT.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\NotepadMT.hlp" Debug
if exist Debug\nul copy "hlp\NotepadMT.cnt" Debug
if exist Release\nul copy "hlp\NotepadMT.hlp" Release
if exist Release\nul copy "hlp\NotepadMT.cnt" Release
echo.
goto :done

:Error
echo hlp\NotepadMT.hpj(1) : error: Problem encountered creating help file

:done
echo.
