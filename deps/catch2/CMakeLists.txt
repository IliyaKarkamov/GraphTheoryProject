cmake_minimum_required(VERSION 3.14)
project(catch2)

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE include)