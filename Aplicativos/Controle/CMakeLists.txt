add_subdirectory(Interface)
add_subdirectory(Modulos)

set(Aplicativo Controle)

list(APPEND Includes
  ${CMAKE_CURRENT_SOURCE_DIR}/Gui/dialogpesquisar.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.h
  )

list(APPEND Guis
  ${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.ui
  )

list(APPEND Recursos
  ${CMAKE_CURRENT_SOURCE_DIR}/recursos.qrc
  )

list(APPEND Sources
  ${Guis}
  ${Recursos}
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.cpp
  )

add_executable(${Aplicativo} ${Sources})

# run uic to generate ui_*.h source files
list(LENGTH Guis TmGuis)
if(${TmGuis})
  COPPERSPICE_RESOURCES(
    ${Guis}
  )
endif()

# Cria o arquivo de recurso compilado.
list(LENGTH Recursos TmRecursos)
if(${TmRecursos})
  COPPERSPICE_RESOURCES_BINARY(${CMAKE_BINARY_DIR}/bin ${Recursos})
endif()
target_link_libraries(${Aplicativo}
  PRIVATE CopperSpice::CsCore
  PRIVATE CopperSpice::CsGui
  PRIVATE CopperSpice::CsSql
  PRIVATE MitoR::Global
  PRIVATE MitoR::Log
  PRIVATE MitoR::Configuracao
  PRIVATE MitoR::Modulos
  PRIVATE Controle::IControle
  PRIVATE Sessao::ISessao
  )