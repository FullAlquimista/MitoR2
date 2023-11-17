set(Interface ICadastro)

add_library(${Interface} INTERFACE)
add_library("Cadastro::${Interface}" ALIAS ${Interface})

target_link_libraries(${Interface}
  INTERFACE CopperSpice::CsCore
  INTERFACE CopperSpice::CsGui
  INTERFACE CopperSpice::CsSql
  INTERFACE MitoR::Global
  )

target_include_directories(${Interface}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )