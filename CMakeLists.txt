cmake_minimum_required(VERSION 2.8)
project( TCPsocket )

#use c++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -g")

find_package( OpenCV REQUIRED )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_executable( server 
server.cpp 
src/tcpServer.cpp
)

target_link_libraries( server ${OpenCV_LIBS} )

add_executable( client 
client.cpp 
src/tcpClient.cpp
)

target_link_libraries( client ${OpenCV_LIBS} )
