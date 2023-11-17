set(Modulo ModuloAB)

list(APPEND Includes
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/plugin.h
  #${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.h
  )

list(APPEND Guis
  #${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.ui
  )

list(APPEND Recursos
  #${CMAKE_CURRENT_SOURCE_DIR}/recursos.qrc
  )

list(APPEND Jsons
  ${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo}.json # Cria uma dependencia onde o arquivo .json é copiado para o diretório correto.
  #${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo}/config.json # Cria uma dependencia onde o arquivo .json é copiado para o diretório correto.
  )

list(APPEND Sources
  ${Guis}
  ${Recursos}
  ${Jsons}
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/plugin.cpp
  #${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.cpp
  )

add_library(${Modulo} SHARED ${Sources})

# run uic to generate ui_*.h source files
list(LENGTH Guis TmGuis)
if (${TmGuis})
  COPPERSPICE_RESOURCES(
    ${Guis}
  )
endif ()

# Cria o arquivo de recurso compilado.
list(LENGTH Recursos TmRecursos)
if (${TmRecursos})
  COPPERSPICE_RESOURCES_BINARY(${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo} ${Recursos})
endif ()

target_link_libraries(${Modulo}
  PRIVATE CopperSpice::CsCore
  PRIVATE CopperSpice::CsGui
  PRIVATE MitoR::Global
  PRIVATE MitoR::Log
  PRIVATE MitoR::Configuracao
  PRIVATE MitoR::Modulos
  )

set_target_properties(${Modulo} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo}
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo}
  )

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo}.json
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${Modulo}.json ${CMAKE_BINARY_DIR}/bin/Modulos
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${Modulo}.json
  )

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo}/config.json
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/bin/Modulos/${Modulo}/
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/config.json
  )
