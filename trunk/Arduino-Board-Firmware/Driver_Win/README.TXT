Arduino Mega ADK.inf:

Original Arduino Treiber für das Arduino Mega ADK Board.

BA-Robot-Arduino Mega ADK.inf

Angepasster Treiber für das Arduino Mega ADK Board.

Flashen des Devices:

benötigt: Flip (v.3.4.5)

Arduino Mega ADK in den DFU Modus bringen (ab Rev2 des Boardes die PINS jumpern.)
Flip starten.
Select Device: AT90USB82 wählen
Start Communication via USB

BootLoader sichern: 

Buffer -> Optionen -> Whole Buffer anklicken
Device -> Read -> from 00000 to 00FFF
Save Buffer as HEX File.

BootLoader schreiben:

File -> Load Hex File
HEX_Files\Arduino-Mega_ADK_USBSERIAL_VID_16C0_PID_27D8.hex laden
Alles links anklicken
Run
Start
Usb Gerät abziehen, neu anstecken und den mitgelieferten Treiber installieren

Eigenen Bootlader erstellen: 

- Packet LUFA 100807_Included_Mega_ADK_BA-Robot.rar entpacken
- im Ordner Projects/arduino-usbserial die Datei Descriptors.c entsprechen anpassen.
( Beispiel: VendorID, ProductID, ProductString -> den Unicode String) 
- nun die Systemumgebungsvariable PATH anpassen PATH = %PATH%;(PATH_TO_LUFA)\WinAVR-20100110\bin;(PATH_TO_LUFA)\WinAVR-20100110\utils\bin;
- cmd starten, ins Verzeichnis Projects\arduino-usbserial wechseln -> make 
- nun hat man im Verzeichnis Projects\arduino-usbserial die Datei "arduino-usbserial.hex" welches der neue Bootloader sit, den man nun mit Flip flashen kann
