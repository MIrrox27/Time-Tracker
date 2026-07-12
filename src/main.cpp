// author github.com/MIrrox27/Time-Tracker
// src/main.cpp

#include <windows.h>
#include <iostream>
#include <map>
#include <string> 
#include <fstream>
#include <chrono>
#include <clocale>

int main(){
  setlocale(LC_ALL, "Russian");
  bool running = true;
  std::map<std::string, int> timer;
  int time = 0;
  int time_exit = 20;


  while (running){
    HWND hwnd = GetForegroundWindow();
    if  (hwnd != NULL){
      char buffer[256];
      GetWindowTextA(hwnd, buffer, sizeof(buffer));
      //std::cout << buffer << std::endl;
      std::string window_name = buffer;

      if (timer.count(window_name) > 0){
        timer[window_name]++;
      }
      else{
        timer[window_name] = 1;
      }      
    }

    time++;
    if (time ==  time_exit) break;
    Sleep(1000);
  }
  
  for (const auto& name : timer) {
    std::cout << name.first << " : " << name.second << std::endl;
  }


  return 0;
}