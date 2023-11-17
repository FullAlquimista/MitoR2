set(Biblioteca Sql)

list(APPEND Guis
  )

list(APPEND Sources
  ${Guis}
  operacao.cpp
  sqlnucleo.cpp
  tabelactsql.cpp
  tabelasql.cpp
  validarentrada.cpp
  )

# run uic to generate ui_*.h source files
list(LENGTH Guis TmGuis)
if(${TmGuis})
  COPPERSPICE_RESOURCES(
    ${Guis}
  )
endif()

add_library(${Biblioteca}
  SHARED ${Sources}
  )
add_library("${PROJECT_NAME}::${Biblioteca}" ALIAS ${Biblioteca})

target_link_libraries(${Biblioteca}
  PUBLIC MitoR::Global
  PUBLIC CopperSpice::CsCore
  PUBLIC CopperSpice::CsGui
  PUBLIC CopperSpice::CsSql
  PUBLIC spdlog::spdlog
  )

target_include_directories(${Biblioteca}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
  )

target_compile_definitions(${Biblioteca}
  PRIVATE MITOR_BUILD_LIB
  )