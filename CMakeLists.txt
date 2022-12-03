cmake_minimum_required(VERSION 3.23)
project(FormulaAnalysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(FormulaAnalysis main.cpp opt.h opt.cpp opts.h)
