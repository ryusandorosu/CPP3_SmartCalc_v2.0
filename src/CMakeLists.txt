cmake_minimum_required(VERSION 3.22)
project(debug)

set(CMAKE_CXX_STANDARD 17)

add_executable(debug model/calculation.cc model/parsing.cc model/rpn.cc model/validation.cc backend_manual_test.cc)
