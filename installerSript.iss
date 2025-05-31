[Setup]
AppName=Studentu-analize
AppVersion=3.0
AppPublisher=Neda Davidaviciute
DefaultDirName={autopf}\VU\Neda
DefaultGroupName=VU\Neda
OutputBaseFilename=setup
OutputDir=.
PrivilegesRequired=admin
Compression=lzma
SolidCompression=yes

[Files]
Source: "build\Objektinis.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "files\studentai10000.txt"; DestDir: "{app}\files"; Flags: ignoreversion
Source: "files\studentai100000.txt"; DestDir: "{app}\files"; Flags: ignoreversion

[Dirs]
Name: "{app}\analysis"   ; 

[Icons]
Name: "{group}\Vardenis-Pavardenis"; Filename: "{app}\Objektinis.exe"
Name: "{commondesktop}\Vardenis-Pavardenis"; Filename: "{app}\Objektinis.exe"

[Run]
Filename: "{app}\Objektinis.exe"; Description: "Paleisti programą"; Flags: nowait postinstall skipifsilent
