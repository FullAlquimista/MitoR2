set(Biblioteca Log)

list(APPEND Sources
  ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
  )

add_library(${Biblioteca}
  SHARED ${Sources}
  )
add_library("${PROJECT_NAME}::${Biblioteca}" ALIAS ${Biblioteca})

target_link_libraries(${Biblioteca}
  PUBLIC MitoR::Global
  PUBLIC spdlog::spdlog
  )

target_include_directories(${Biblioteca}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
  )

target_compile_definitions(${Biblioteca}
  PRIVATE MITOR_BUILD_LIB
  )