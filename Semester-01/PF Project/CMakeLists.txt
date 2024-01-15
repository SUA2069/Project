cmake_minimum_required(VERSION 3.27)
project(GTKTutorial)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# List of your source files
set(SOURCE_FILES
    main.c
    testcodes.c
    # Add more files as needed
)

# Generate an executable for each source file
foreach(SOURCE_FILE ${SOURCE_FILES})
    # Extract the file name without extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
    
    # Add executable for the source file
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
    
    # Link libraries
    target_link_libraries(${EXECUTABLE_NAME} ${GTK3_LIBRARIES})
endforeach()

