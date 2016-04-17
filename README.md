Wireless remote control for PC power
-----------------------------------------

This project is based on ESP8266 and provides web interface controlling PC
power supply.

The hardware is connected to standard ATX power/reset buttons and
power/activity LEDs in parallel (the existing functionality of switches and
LEDs is retained).

See `hardware/` for schematics and hardware connections.
See `firmware/` for the firmware and web interface which runs on ESP8266.

Pre-built binaries and flashing instructions are available in
`firmware/prebuilt-binaries`.

Web interface
-----------------

Web interface can be accessed on both AP and station interfaces. Default IP
address for AP mode is 192.168.4.1.

Password is sent as GET parameter (yes, I know, that's not how it should be
done):

http://192.168.4.1/?auth=authpasskey

![Screenshot of web interface](img/screenshot-0.png?raw=true "Screenshot of web
interface")

Known limitations
-------------------------

This project is in `works-for-me` stage of prototype. More likely than not, it
will reset your computer in the least-convenient time. Consider yourself
warned!

* PC is reset when ESP is rebooted (including firmware update!)
* OTA firmware update support is work-in-progress,
* Authentication is really dumb (password provided by GET parameter).


