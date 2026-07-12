# author github.com/MIrrox27/Time-Tracker
# CMakelists.txt

cmake_minimum_required(VERSION 3.15)
project(Time-Tracker VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

# Собираем все файлы .cpp в папке src автоматически
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(tmt ${SOURCES})