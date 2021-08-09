project(intentRecognizer)

cmake_minimum_required(VERSION 3.19.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB SOURCES "src/*.cpp")
add_library(intentlib ${SOURCES}) # create static *.a library of intent class
set(LIBRARY_NAME intentlib)


# For creating exe of main application
set(SOURCES_MAIN "src/nlp.cpp")
add_executable(intentRecognizer ${SOURCES_MAIN})
target_link_libraries(intentRecognizer ${LIBRARY_NAME}) # link dependancy to the *.exe
