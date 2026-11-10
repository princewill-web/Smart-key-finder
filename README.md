# Smart Key Finder

A pocket-sized Wi-Fi gadget built on an ESP-01 (ESP8266). It creates its own Wi-Fi network and hosts a small web page with a button that switches a buzzer on and off, so you can locate a keychain from your phone.

## How it works
1. The ESP-01 starts as a Wi-Fi access point.
2. Connect your phone to the network and open `http://192.168.4.1` (or `http://mycarkey.local` on devices that support mDNS).
3. Tap **Toggle buzz!** to start or stop the buzzer. The page shows the current state (0 = not buzzing, 1 = buzzing).

## Hardware
- ESP-01 (ESP8266) module
- Active or passive buzzer on GPIO2
- Power supply (3.3 V)

## Software
Arduino IDE (C++) with the ESP8266 board package. Libraries: `ESP8266WiFi`, `ESP8266WebServer`, `ESP8266mDNS`.

## Setup
1. Install the ESP8266 board package in the Arduino IDE.
2. Open the sketch and **change the access point password** in `setupAP()` to your own.
3. Upload it to the ESP-01, connect the buzzer to GPIO2, and power it up.

## Author
Princewill Ugochukwu Oguguom · [LinkedIn](https://www.linkedin.com/in/princewill-oguguom-84b733237/)
