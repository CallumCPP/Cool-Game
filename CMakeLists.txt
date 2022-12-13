cmake_minimum_required(VERSION 3.20)
project(Game)
find_package(raylib 3.0 QUIET)

if (NOT raylib_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    include_directories(${raylib_SOURCE_DIR})

  endif()

endif()

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} raylib)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   rm -r $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   copy_directory ${CMAKE_SOURCE_DIR}/Textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures)


add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/Levels)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   rm -r $<TARGET_FILE_DIR:${PROJECT_NAME}>/Levels)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E 
                   copy_directory ${CMAKE_SOURCE_DIR}/Levels $<TARGET_FILE_DIR:${PROJECT_NAME}>/Levels)
