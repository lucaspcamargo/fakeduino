cmake_minimum_required(VERSION 3.5)

project(fakeduino LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

add_library(fakeduino SHARED
  fakeduino_global.h
  fakeduino.cpp
  fakeduino.h

  src/Arduino.cpp
  src/DHTx.cpp
  src/EEPROM.cpp
  src/KeyPress.cpp
  src/LiquidCrystal.cpp
  src/Serial.cpp

  impl/liquidcrystalimpl.cpp
  impl/dhtimpl.cpp
  impl/serialmonitor.cpp
  impl/workspace.cpp

  res/fakeduino.qrc
)

target_include_directories(fakeduino PUBLIC include)
target_include_directories(fakeduino PRIVATE impl)

target_link_libraries(fakeduino PRIVATE Qt5::Widgets Qt5::SerialPort)

target_compile_definitions(fakeduino PRIVATE FAKEDUINO_LIBRARY)

export( TARGETS fakeduino FILE ${PROJECT_BINARY_DIR}/fakeduino.cmake )
