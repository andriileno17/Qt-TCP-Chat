project(ChatClient)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON) 

find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

add_executable(Client
    src/main.cpp
    src/mainwindow.cpp
    include/mainwindow.h
    ui/mainwindow.ui
)

target_include_directories(Client PRIVATE include)

target_link_libraries(Client PRIVATE Qt6::Core Qt6::Network Qt6::Widgets)