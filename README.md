P.E.W.S Public ESP32 Web Server
===============================

### Hello everyone, here is a simple tool if you ever wanted to use an ESP32 as a webserver anyone around the word can see!

Required Tools and such:
------------------------

*   A Windows, MacOS or Linux computer
*   Arduino IDE
*   Super DMZ web tunneling account
*   The code above
*   An ESP32 capable of connecting to the internet via WiFi or Ethernet (obviously)

Step 1: Setup
-------------

*   Install the SuperDMZ library in the library manager by going to the top toolbar in Arduino IDE, click Tools, then Manage Libraries, then serach for SuperDMZ, and install version 1.2.0
*   Still in the Library Manager, install ESP Async WebServer version 3.12.0, by ESP32Async
*   Go to the top toolbar in Arduino IDE, click Tools, then Board, then Board Manager, Search for the esp32 board by Espressif Systems, and install version 3.0.7, as newer versions may break compatibility with other libraries

Step 2: SuperDMZ
----------------

*   Go to https://superdmz.com/ and create a free account
*   Once logged in, click on My Tunnels in the options bar on the side, and then press New Tunnel
*   Name the tunnel whatever you like, and choose whatever name you want for the public url, click next
*   Select any server you want (preferably the one nearest you), then select HTTP/HTTPS, when the pop-up comes up, select Local HTTP, not Local HTTPS, then select Direct Routing, make the local porton on target machine port 80, leave the Self Control empty
*   Select Public Access, so anyone across the world can access your website, and then click create tunnel
*   You might be wondering why we chose HTTP, to keep things simple, we will use HTTP and not HTTPS because HTTP doesn't require a certificate, but HTTPS does, which requires a lot of messign around, which I don't want to make this tricky

Step 3: Code
------------

*   Go back into Arduino IDE, and look for the variable in the code that is called WIFI\_SSID, replace the value with your Wi-FI name (note: if your Wi-Fi has wifi\_name 5g and wifi\_name (wifi\_name being your actual wifi's name), do **not** select the 5g one, as it will not work, if you do not have two wifi's, ignore this
*   Replace the value of the WIFI\_PASS variable to your Wi-Fi password
*   In the SuperDMZ tunnel, find your token for the tunnel, it should be 48 characters long of random characters.
*   Make sure the LOCAL\_PORT variable is set to 80
*   While not required, if you like to, you can change the html code, but for now, I would leave it the way it is, just as a test
*   Once done, save the script

Step 4: Compile and Flash
-------------------------

*   Plug in your ESP32
*   Click on the dropdown next to the Start Debugging button, and select Select other board on port
*   In the boards section, type in what every esp32 you are using, and then select the com port in the ports side
*   Note: if you don't see any port on the side, makew sure your cable can transfer data, if that still doesn't work, install the ESP32 driver at this[](https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
*   Click the Upload button and wait for it to compile and flash to the ESP32
*   Once finished, go to your SuperDMZ tunnel dashboard, and select the SUPERDMZ URL, paste it into your URL bar in your web browser and press enter
*   If it says somethign like Your connection is not private, click Advanced, and then proceed to the website, this might change depending on your browser, but it will be similar to what I explained
*   If you can connect, and the webpage shows, Viola! Your ESP32 is publically accessible!
*   Send the link to a friend or family memebr to test out, or test it on your phone, using your mobile data and not your Wi-Fi to make sure anyone can see it
