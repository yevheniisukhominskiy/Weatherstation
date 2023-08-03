<p align="center">
   <img src="https://i.ibb.co/8c1HjPm/Weatherstation.png" alt="Weatherstation" border="0" width=700px>
</p>

  

<p align="center">
    <img src="https://img.shields.io/badge/Version-1.0-violet?style=for-the-badge" alt="Version">
    <img src="https://img.shields.io/github/license/yevheniisukhominskiy/Weatherstation?style=for-the-badge" alt="License">
</p>

## Content

1. [Overview](https://github.com/yevheniisukhominskiy/Weatherstation#overview)
	
2. [Documentation](https://github.com/yevheniisukhominskiy/Weatherstation#documentation)
    1. [Required components](https://github.com/yevheniisukhominskiy/Weatherstation#required-components)
	2. [Connection](https://github.com/yevheniisukhominskiy/Weatherstation#required-components)
	3. [Compile the sketch for ESP8266](https://github.com/yevheniisukhominskiy/Weatherstation#compile-the-sketch-for-esp8266)
	4. [Connecting to the FTP Client and Uploading the Web Page](https://github.com/yevheniisukhominskiy/Weatherstation#connecting-to-the-ftp-client-and-uploading-the-web-page)
	5. [Using a web application](https://github.com/yevheniisukhominskiy/Weatherstation#using-a-web-application)


3. [Distribution](https://github.com/yevheniisukhominskiy/Weatherstation#distribution)

4. [Developers](https://github.com/yevheniisukhominskiy/Weatherstation#developers)

5. [License](https://github.com/yevheniisukhominskiy/Weatherstation#license)

6. [Warning](https://github.com/yevheniisukhominskiy/Weatherstation#warning)

---

<img src="https://i.ibb.co/grys3kq/image.png" alt="image" border="0">

---

## Overview

**Weatherstation** is a software application of a weather station with a web interface, designed for measuring atmospheric parameters such as temperature, humidity, and atmospheric pressure, as well as for generating weather forecasts based on these data.


## Documentation
#### Required components

This project utilizes only two components: the ESP8266 microcontroller and the BME280 sensor module (temperature, humidity, pressure).

The project does not support other microcontrollers, but it doesn't mean you cannot experiment with other Arduino components.

#### Connection

| **ESP8266** | **BME280** |
|-------------|------------|
| 3V          | VIN        |
| GND         | GND        |
| D1          | SCL        |
| D2          | SDA        |

You can solder the connections directly with wires or use a breadboard and male-to-male jumper wires. However, in future updates, a PCB layout will be available where you can simply solder the microcontroller and sensor onto the board. This will be introduced in the upcoming releases.
**It's important to connect when the microcontroller is not powered by the main power source.**


#### Compile the sketch for ESP8266
At the beginning of the `main.cpp` sketch, you must fill in the variables for connecting to the Wi-Fi network. The access point can be either a local one (without internet access) or a networked one.

```С++
#define WIFI_SSID "YOURNETWORKNAME"
#define WIFI_PASS "YOURNETWORKPASS"
```

In the `setup()` function, you must also set the username and password for file transfer (`index.html`, `style.css`, `script.js` etc) through the FTP protocol.

```С++
ftpSrv.begin("login","password");
```
Avoid using the same username and password for the FTP client (especially "admin", "admin") to prioritize security. The more you neglect security, the more vulnerable your server becomes to external attacks.

Upload the latest firmware version to the microcontroller using either Arduino IDE or PlatformIO.

#### Connecting to the FTP Client and Uploading the Web Page
Unfortunately, for the current version **v. 0.1(alpha)**, most FTP clients do not connect properly. Currently, only one tested candidate works on Windows:[WinSCP](https://winscp.net/eng/download.php). If you want to use your own client, feel free to do so, but the author does not guarantee successful connection to the server.

**Connecting to the client is done after compiling the sketch on the board, which should be connected while using the server.**

<img src="https://i.ibb.co/HBYt9zf/image-1.png" alt="image-1" border="0">

After launching the application, a window will appear where you need to fill in the following details:
```
File Protocol: FTP
Encryption: No encryption
Host Name: The IP address that will appear in the Serial Monitor after connecting to the network.
Port Number: 21
Login: The username you provided, as explained above.
Password: The password you provided, as explained above.

```
<img src="https://i.ibb.co/FmGyKgz/image.png" alt="image" border="0">

Then, click on the `Login` button at the bottom.

Next, add all the files of the website in the `web-client` directory. It is essential to copy them to the server without any subdirectories, as FTP does not understand them and will produce an error.
<img src="https://i.ibb.co/D70VfpD/image-2.png" alt="image-2" border="0">

#### Using a web application

Everything is simple here. It is enough to enter the ip, which will appear in the port monitoring of the connected device address in any browser on any device. However, the latest version has not yet added adaptation for mobile devices.

**For example:**

<img src="https://i.ibb.co/HBYt9zf/image-1.png" alt="image-1" border="0">

Congratulations! You did a great job if you understood the author's explanations, as it's written in an alien language. 👽

## Distribution

- Available only here
## Developers

- [Yevhenii Sukhominskiy]([GitHub Profile Link](https://github.com/yevheniisukhominskiy))

## Version
* 1.0 - beta version of the project

## License

Project **Weatherstation** is distributed under the MIT license.
## Warning

1. By using this project, you agree to the "Disclaimer" and take full responsibility that may be placed upon you.

2. The information provided is for users' free knowledge on topics that may be of interest to them.

3. The author is not responsible for the relevance, accuracy, completeness, or quality of the provided information. Any claims or complaints regarding material or moral damage due to the use or non-use of the information provided, including the use of incorrect or incomplete information, are entirely excluded.

