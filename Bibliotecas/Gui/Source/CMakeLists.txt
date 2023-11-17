set(Biblioteca Gui)

list(APPEND Guis
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogpesquisar.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogpesquisarct.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogpesquisartabela.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogpesquisararvore.ui
  )

list(APPEND Sources
  ${Guis}
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogpesquisarct.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogpesquisartabela.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dialogpesquisar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/gui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/keyeventfilter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/eventfiltermudancafocus.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/relationaliddelegate.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/callbackpaintdelegate.cpp
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