cmake_minimum_required(VERSION 3.10)
project(ncvm-ui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_compile_options(-Wall -Wextra -pedantic -Werror)
# add_compile_options(-Wall -Wextra -pedantic -Winit-self -Wuninitialized)

set(SRC_LIST
    main.cpp
    ui/layout.cpp
    ui/event-handler.cpp
    ui/windows/collection.cpp
    ui/windows/rectangle.cpp
    ui/windows/background.cpp
    ui/windows/information.cpp
    ui/windows/vm-control/vm-outter-frame.cpp
    ui/windows/vm-control/vm-controller.cpp
    ui/windows/vm-control/one.cpp
    ui/windows/vm-control/two.cpp
    ui/windows/vm-control/three.cpp
    ui/windows/vm-control/four.cpp
    ui/windows/options-button.cpp
    ui/windows/options-menu/options-window.cpp
    ui/windows/options-menu/about.cpp
    ui/windows/options-menu/exit.cpp)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
find_library(NCURSES_EXTRA panel HINTS /usr/lib64)

if(CURSES_FOUND)
    message(STATUS "Found: ${CURSES_LIBRARIES}")
    include_directories(ui ui/windows ${CURSES_INCLUDE_DIRS})

    add_executable(ncvm-ui ${SRC_LIST})
    target_link_libraries(ncvm-ui ${CURSES_LIBRARIES} ${NCURSES_EXTRA})
else()
    message(FATAL_ERROR "ncurses not found.")
endif()

install(TARGETS ncvm-ui RUNTIME DESTINATION bin)
