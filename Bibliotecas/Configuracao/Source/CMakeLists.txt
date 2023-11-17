set(Biblioteca Configuracao)

list(APPEND Includes
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/MitoR/Configuracao.hpp
  )

list(APPEND Sources
  ${CMAKE_CURRENT_SOURCE_DIR}/Configuracao.cpp
  )

add_library(${Biblioteca}
  SHARED ${Sources}
  )
add_library("${PROJECT_NAME}::${Biblioteca}" ALIAS ${Biblioteca})

target_link_libraries(${Biblioteca}
  PRIVATE CopperSpice::CsCore
  PRIVATE CopperSpice::CsGui
  PUBLIC MitoR::Global
  PRIVATE MitoR::Log
  PRIVATE nlohmann_json::nlohmann_json
  )

target_include_directories(${Biblioteca}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
  )

target_compile_definitions(${Biblioteca}
  PRIVATE MITOR_BUILD_LIB
  )