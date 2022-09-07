set(CMAKE_OSX_ARCHITECTURES "x86_64")
add_executable(wormy Main.cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/external/sfml/include)

add_subdirectory(entities)
add_subdirectory(scenes)
add_subdirectory(game)

# Provide the full path to the library, so CMake knows where to find it.
target_link_libraries(wormy
  PRIVATE
    entities
    scenes
    game
    
    ${CMAKE_CURRENT_LIST_DIR}/external/sfml/lib/libsfml-graphics.dylib
    ${CMAKE_CURRENT_LIST_DIR}/external/sfml/lib/libsfml-window.dylib
    ${CMAKE_CURRENT_LIST_DIR}/external/sfml/lib/libsfml-system.dylib
  )