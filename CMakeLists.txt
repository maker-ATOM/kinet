cmake_minimum_required(VERSION 3.22.1)

project("kinet")

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(kinet src/main.cpp)

target_link_libraries(kinet ${CURSES_LIBRARIES}) 

install(TARGETS kinet DESTINATION ${CMAKE_INSTALL_BINDIR}) # Install the project so as to use from anywhere within the terminal