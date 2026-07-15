// author github.com/MIrrox27/Time-Tracker
// src/main.cpp

#include <windows.h>
#include <iostream>
#include <map>
#include <string> 
#include <fstream>
#include <chrono>
#include <algorithm>
#include <clocale>
#include <ctime>


std::string lower(std::string text){
  std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
    return std::tolower(c);
  });
  return text;
}

bool is_special_or_space(const std::string& str) {
    if (str.empty()) return false; // Пустая строка не содержит спецсимволов

    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::ispunct(c) || std::isspace(c);
    });
}

std::string clear_name(std::string str){
std::string apps[] = {
    
    "Google Chrome", "Chrome",
    "Mozilla Firefox", "Firefox",
    "Microsoft Edge", "Edge",
    "Opera",
    "Brave",
    "Vivaldi",
    "Tor Browser", "Tor",
    "Yandex Browser", "Яндекс Браузер",
    "DuckDuckGo", "Duck Duck Go",

    
    "Visual Studio Code", "VS Code", "Code - OSS",
    "Visual Studio",
    "IntelliJ IDEA", "IDEA",
    "PyCharm",
    "WebStorm",
    "Sublime Text", "Sublime",
    "Notepad++", "Notepad plus",
    "Android Studio",

    
    "Windows Terminal", "Terminal",
    "Command Prompt", "cmd.exe",
    "PowerShell", "powershell.exe",

    
    "File Explorer", "Explorer", "Проводник",

    
    "Discord",
    "Slack",
    "Telegram",
    "WhatsApp",
    "Zoom",
    "Microsoft Teams", "Teams",

   
    "Microsoft Word", "Word",
    "Microsoft Excel", "Excel",
    "Microsoft PowerPoint", "PowerPoint",
    "Outlook",

    
    "VLC", "VideoLAN",
    "Media Player Classic", "MPC-HC",
    "Spotify",

    
    "Adobe Photoshop", "Photoshop",
    "Adobe Premiere", "Premiere",

    
    "GitHub Desktop",
    "Figma",
    "Blender",
    "Unity"
};
  

  for (const auto& b : apps){
    if (lower(str).find(lower(b)) != std::string::npos){
      str = b;
      break;
    }
  }

  /*str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) {
    return !std::isalnum(c) && c != ' '; 
  }), str.end());*/

  if (is_special_or_space(str)){
    str = "Other";
  }

  return str;
}


std::string sec_to_hours(int sec){
  std::string result;

  std::string hms[] = {
    " hours, ", " minutes, ", " seconds, "};

  result = std::to_string(sec / 3600) + " hours, " + std::to_string(sec % 3600 / 60) + " minutes, " + std::to_string((sec % 3600) % 60) + " seconds";
  return result;
}


bool is_AFK(int max_seconds){
  LASTINPUTINFO lii;
  lii.cbSize = sizeof(LASTINPUTINFO);

  if (GetLastInputInfo(&lii)){
    DWORD idleTime = (GetTickCount64() - lii.dwTime) / 1000;

    if (idleTime >= max_seconds){
      return true;
    }
    return false;
  }
  return false; 
}


int main(){
  bool running = true;
  std::map<std::string, int> timer;
  int time = 0;
  int time_print;
  int time_exit;
  std::cout << "Enter time (sec), to print your statistic and time to exit (format: 'time1 time2'): ";
  std::cin >> time_print;
  std::cin >> time_exit;
  int time_step = time_print;
  

  while (running){
    HWND hwnd = GetForegroundWindow();
    if  (hwnd != NULL){
      char buffer[256];
      GetWindowTextA(hwnd, buffer, sizeof(buffer));
      //std::cout << buffer << std::endl;
      std::string window_name = buffer;
      window_name = clear_name(window_name);

      if (timer.count(window_name) > 0){
        timer[window_name]++;
      }
      else{
        timer[window_name] = 1;
      }      
    }


    time++;
    std::time_t t = std::time(nullptr);
    if (time ==  time_print && time != time_exit) {
      std::cout << "\n\n=================== STATISTIC" <<  " ===================\n" << " --- "<< std::ctime(&t) << std::endl;
      for (const auto& name : timer) {
        std::cout << name.first << " : " << sec_to_hours(name.second) << std::endl;
      }
      time_print += time_step;
    }


    if (time == time_exit){
      std::cout << "\n\n=================== (END) STATISTIC" <<  " ===================\n" << " --- "<< std::ctime(&t) << std::endl;
      for (const auto& name : timer) {
        std::cout << name.first << " : " << sec_to_hours(name.second) << std::endl;
      }
      running = false;
    }
    Sleep(1000);
  }


  std::cout << "\n --- Thank's for using my program! \n --- My other projects: https://github.com/MIrrox27?tab=repositories";
  return 0;
}
