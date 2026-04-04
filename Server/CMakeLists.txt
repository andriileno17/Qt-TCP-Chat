project(ChatServer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

add_executable(Server
    src/main.cpp
    src/chatserver.cpp
    include/chatserver.h
)

target_include_directories(Server PRIVATE include)

target_link_libraries(Server PRIVATE Qt6::Core Qt6::Network)