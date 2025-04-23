cmake_minimum_required(VERSION 3.16)
project(SwitchBotControllerProject)

# C++標準の設定 (例: C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# サブディレクトリ追加
add_subdirectory(src)