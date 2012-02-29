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

Loader sichern: 

Buffer -> Optionen -> Whole Buffer anklicken
Device -> Read -> from 00000 to 00FFF
Save Buffer as HEX File.

Loader schreiben:

File -> Load Hex File
HEX_Files\Arduino-Mega_ADK_USBSERIAL_VID_16C0_PID_27D8.hex laden
Alles links anklicken
Run
Start
Usb Gerät abziehen, neu anstecken und den mitgelieferten Treiber installieren

