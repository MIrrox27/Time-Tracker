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

bool is_special_or_space(const std::string& str) {
    if (str.empty()) return false; // Пустая строка не содержит спецсимволов

    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::ispunct(c) || std::isspace(c);
    });
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
  /*
  result.push_back(sec / 3600); // кол-во часов
  result.push_back(hms[0]);
  result.push_back((sec % 3600) / 60); // кол-во минут
  result.push_back(hms[1]);
  result.push_back((sec % 3600) % 60); // секунды
  result.push_back(hms[2]);
*/
  return result;
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
        std::cout << name.first << " : " << sec_to_hours(name.second) << std::endl;
      }
      time_print *= 2;
    }

    if (time == time_exit){
      std::cout << "========================= STATISTIC =========================\n\n";
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
