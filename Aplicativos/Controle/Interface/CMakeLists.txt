set(Interface IControle)

add_library(${Interface} INTERFACE)
add_library("Controle::${Interface}" ALIAS ${Interface})

target_link_libraries(${Interface}
  INTERFACE CopperSpice::CsCore
  INTERFACE CopperSpice::CsGui
  INTERFACE CopperSpice::CsSql
  INTERFACE MitoR::Global
  INTERFACE MitoR::Log
  INTERFACE MitoR::Configuracao
  INTERFACE MitoR::Modulos
  )

target_include_directories(${Interface}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )