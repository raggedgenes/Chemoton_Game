; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{D7D8EF2E-BFD4-4949-94AC-6A84BA604B73}
AppName=Chemoton App
AppVersion=0.0.1
;AppVerName=Chemoton App 0.0.1
AppPublisher=Ragged Genes
DefaultDirName={pf}\Chemoton App
DefaultGroupName=Chemoton App
OutputDir=D:\RandD\Chemoton_Game\release
OutputBaseFilename=Chemoton App install
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\RandD\Chemoton_Game\release\dummy\Chemoton_Game.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\RandD\Chemoton_Game\release\r\*"; DestDir: "{app}\r\"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Chemoton App"; Filename: "{app}\Chemoton_Game.exe"
Name: "{commondesktop}\Chemoton App"; Filename: "{app}\Chemoton_Game.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\Chemoton_Game.exe"; Description: "{cm:LaunchProgram,Chemoton App}"; Flags: nowait postinstall skipifsilent

