add_library(entities "")

target_sources(entities
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/LineEntity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ObstacleEntity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ScoringEntity.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CircleCollider.cpp
    
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/LineEntity.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ObstacleEntity.hpp
  ${CMAKE_CURRENT_LIST_DIR}/ScoringEntity.hpp
  ${CMAKE_CURRENT_LIST_DIR}/CircleCollider.hpp
)

target_include_directories(entities
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
  
target_link_libraries(entities
    PRIVATE
    scenes
  )