set(Interface Global)

list(APPEND Include
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

add_library(${Interface} INTERFACE)
add_library("${PROJECT_NAME}::${Interface}" ALIAS ${Interface})

target_link_libraries(${Interface}
  INTERFACE CopperSpice::CsCore
  )

target_include_directories(${Interface} INTERFACE ${Include})