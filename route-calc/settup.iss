; -- route-calc.iss --
[Setup]
AppName=route-calc
AppVersion=1.0
DefaultDirName=route-calc
DisableProgramGroupPage=yes
UninstallDisplayIcon={app}\route-calc.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output

[Files]
Source: "route-calc.exe"; DestDir: "{app}"
Source: "icudt52.dll"; DestDir: "{app}"
Source: "icuin52.dll"; DestDir: "{app}"
Source: "icuuc52.dll"; DestDir: "{app}"
Source: "msvcp110.dll"; DestDir: "{app}"
Source: "msvcr110.dll"; DestDir: "{app}"
Source: "Qt5Core.dll"; DestDir: "{app}"
Source: "Qt5Gui.dll"; DestDir: "{app}"
Source: "Qt5Svg.dll"; DestDir: "{app}"
Source: "Qt5Widgets.dll"; DestDir: "{app}"
Source: "route-calc_en.qm"; DestDir: "{app}"
Source: "route-calc_ru.qm"; DestDir: "{app}"
Source: "platforms\qwindows.dll"; DestDir: "{app}\platforms"
