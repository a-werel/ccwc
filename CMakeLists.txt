cmake_minimum_required(VERSION 4.1)

if(NOT DEFINED PACKAGE_NAME)
    set(PACKAGE_NAME ccwc)
endif()

project(${PACKAGE_NAME} CXX)

file(GLOB SRC_FILES "src/*.cpp")
add_library(${PACKAGE_NAME} ${SRC_FILES})
target_include_directories(${PACKAGE_NAME} PUBLIC include)

add_executable(${PACKAGE_NAME}_bin main.cpp)
set_target_properties(${PACKAGE_NAME}_bin PROPERTIES OUTPUT_NAME ${PACKAGE_NAME})
target_link_libraries(${PACKAGE_NAME}_bin PRIVATE ${PACKAGE_NAME})

file(GLOB HEADER_FILES "include/ne/*.h")
foreach(HEADER_FILE ${HEADER_FILES})
    file(RELATIVE_PATH HEADER_FILE_RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${HEADER_FILE})
    list(APPEND HEADER_FILES_RELATIVE ${HEADER_FILE_RELATIVE})
endforeach()
set_target_properties(${PACKAGE_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_FILES_RELATIVE}")

install(TARGETS ${PACKAGE_NAME} ${PACKAGE_NAME}_bin PUBLIC_HEADER DESTINATION "include/ne")

if(NOT BUILD_TESTING STREQUAL OFF)
    add_subdirectory(test)
endif()
