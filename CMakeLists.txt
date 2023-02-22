cmake_minimum_required(VERSION 3.5)
project(lispp)

include(common.cmake)

add_library(lispp-lib
        lispp/tokenizer.cpp
        lispp/exceptions.cpp
        )

add_executable(lispp
  lispp/main.cpp)

target_link_libraries(lispp
  lispp-lib)

add_executable(test_lispp
  test/test_tokenizer.cpp
        catch_main.cpp)

target_link_libraries(test_lispp
  lispp-lib)

add_executable(test_tokenizer
        test/test_tokenizer.cpp
        catch_main.cpp)

target_link_libraries(test_tokenizer
        lispp-lib)

add_executable(test_parser
        catch_main.cpp)

target_link_libraries(test_parser
        lispp-lib)
