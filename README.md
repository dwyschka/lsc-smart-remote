
# Setup

Each Folder is an own Project

# EspnowServer
is the Server, if HEX-Data was received, its printed out by Serial, and can be processed by iobroker etc. It need to be installed on a second ESP.

# LSCSmartRemote
contains the Code for the switched ESP on the device, it takes the Serial data, received by the second microcontroller, and send it away to the server. The ino file has to be edited, because it needs the mac address of the server-esp.

`uint8_t remoteMac[] = {0x6A, 0xC6, 0x3A, 0xC2, 0xFE, 0x7A};`

has to be edited to your esp-now-server-mac-address
# iobroker-skript 
uses the javascript-adapter on iobroker, add the content from the espnow.js to your adapter. You need to install serialport on iobroker `npm install serialport` and the device has to be changed to your usb-device.
``` 
const port = new SerialPort('/dev/ttyUSB0', {
    baudRate: 115200
})
``` 
