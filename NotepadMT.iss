[Setup]
AppName=NotepadMT
AppVerName=NotepadMT
DefaultDirName={pf}\NotepadMT
DefaultGroupName=NotepadMT
AllowNoIcons=yes
LicenseFile=LICENSE.TXT
OutputBaseFilename=NotepadMTSetup

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: "Release\NotepadMT.cnt"; DestDir: "{app}"
Source: "Release\NotepadMT.exe"; DestDir: "{app}"
Source: "Release\NOTEPADMT.HLP"; DestDir: "{app}"

[Icons]
Name: "{group}\NotepadMT"; Filename: "{app}\NotepadMT.exe"
Name: "{group}\{cm:UninstallProgram,NotepadMT}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\NotepadMT"; Filename: "{app}\NotepadMT.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\NotepadMT.exe"; Description: "{cm:LaunchProgram,NotepadMT}"; Flags: nowait postinstall skipifsilent
