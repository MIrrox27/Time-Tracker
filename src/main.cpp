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

std::string lower(std::string text){
  std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
    return std::tolower(c);
  });
  return text;
}

std::string clear_name(std::string str){

    std::string browsers[] = {
    "Google Chrome", "Mozilla Firefox", "Microsoft Edge",
    "Opera", "Brave", "Vivaldi", 
    "Tor Browser", "Yandex Browser", "Duck Duck Go"
  };
  

  for (const auto& b : browsers){
    if (lower(str).find(lower(b)) != std::string::npos){
      str = b;
      break;
    }
  }
/*
  str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) {
    return !std::isalnum(c) && c != ' '; 
  }), str.end());
*/

  return str;

}


int main(){
  setlocale(LC_ALL, "Russian");
  bool running = true;
  std::map<std::string, int> timer;
  int time = 0;
  int time_print;
  int time_exit;
  std::cout << "Enter time (sec), to print your statistic and time to exit (format: 'time1 time2'): ";
  std::cin >> time_print;
  std::cin >> time_exit;
  

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
    if (time ==  time_print && time != time_exit) {
      std::cout << "========================= STATISTIC =========================\n\n";
      for (const auto& name : timer) {
        std::cout << name.first << " : " << name.second << std::endl;
      }
      time_print *= 2;
    }

    if (time == time_exit){
      std::cout << "========================= STATISTIC =========================\n\n";
      for (const auto& name : timer) {
        std::cout << name.first << " : " << name.second << std::endl;
      }
      break;

    }
    Sleep(1000);
  }


  std::cout << "Thank's for using my program! \nMy another projects: https://github.com/MIrrox27?tab=repositories";
  return 0;
}