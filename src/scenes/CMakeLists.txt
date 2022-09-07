add_library(scenes "")

target_sources(scenes
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/WormyScene.cpp

  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/WormyScene.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Scenes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InputPosition.hpp
  )
target_include_directories(scenes
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

  target_link_libraries(scenes
    PRIVATE    
    game
    entities
  )