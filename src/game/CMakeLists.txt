add_library(game "")

target_sources(game
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Game.cpp
    
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/IScene.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Game.hpp
  )
target_include_directories(game
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

  target_link_libraries(game
    PRIVATE
    scenes    
    entities
  )