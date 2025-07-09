cmake_minimum_required(VERSION 3.10)
project(ncvm-ui)

# Limit compiler to GCC because I want to use the __FILE_NAME__ macro.
if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message (FATAL_ERROR "Invalid compiler!")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_compile_options(-Wall -Wextra -pedantic -Werror)
# add_compile_options(-Wall -Wextra -pedantic -Winit-self -Wuninitialized)

set(SRC_LIST
    main.cpp
    command-line-args.cpp
    logging/manager.cpp
    logging/sdj.cpp
    logging/writer.cpp
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
    ui/windows/options-menu/exit.cpp
    ui/windows/journal/outter-frame.cpp
    ui/windows/journal/inside.cpp
    ui/windows/status/outter-frame.cpp
    ui/windows/status/inside.cpp
    vm/collection.cpp
    vm/manager.cpp)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSTEMD REQUIRED libsystemd)
find_library(NCURSES_EXTRA panel HINTS /usr/lib64)

if(CURSES_FOUND AND SYSTEMD_FOUND)
    message(STATUS "Found: ${CURSES_LIBRARIES} and ${SYSTEMD_LIBRARIES}")
    include_directories(ui ui/windows ${CURSES_INCLUDE_DIRS} PRIVATE ${SYSTEMD_INCLUDE_DIRS})

    add_executable(ncvm-ui ${SRC_LIST})
    target_link_libraries(ncvm-ui ${CURSES_LIBRARIES} ${NCURSES_EXTRA} ${SYSTEMD_LIBRARIES})
else()
    message(FATAL_ERROR "ncurses not found.")
endif()

install(TARGETS ncvm-ui RUNTIME DESTINATION bin)
