cmake_minimum_required(VERSION 3.21)
set(Projeto MitoR)
project(${Projeto})

list(APPEND CMAKE_PREFIX_PATH
  C:/Bibliotecas/CopperSpice/1.8.1.1/Mgw64-11.2.0/cmake/CopperSpice
  C:/Bibliotecas/NlohmannJson/3.11.2/Mgw64-11.2.0/share/cmake/nlohmann_json
  C:/Bibliotecas/Spdlog/1.11/Mgw64-11.2.0/lib/cmake/spdlog
  )

list(APPEND GTEST_ROOT
  C:/Bibliotecas/GoogleTest/1.13/Mgw64-11.2.0
  )

enable_testing()

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckTypeSize)

find_package(CopperSpice REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(gtest REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# location for building binary files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Habilita as opções de compilação:
if (MSVC)
  # warning level 4 and all warnings as errors
  #add_compile_options(/W4 /WX)
else ()
  # lots of warnings and all warnings as errors
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

# Macro para construir o arquivo de recursos binário.
macro(COPPERSPICE_RESOURCES_BINARY OUTPUT_DIR RESOURCES)

  foreach (resource ${RESOURCES} ${ARGN})
    get_filename_component(rscext ${resource} EXT)
    get_filename_component(rscname ${resource} NAME_WE)

    if (${rscext} STREQUAL ".qrc")
      set(rscout ${OUTPUT_DIR}/${rscname}.rcc) #CMAKE_RUNTIME_OUTPUT_DIRECTORY CMAKE_CURRENT_BINARY_DIR

      add_custom_command(
        OUTPUT ${rscout}

        COMMAND CopperSpice::rcc -binary "${resource}" -o "${rscout}"
        MAIN_DEPENDENCY "${resource}"
      )

      set_property(SOURCE ${resource} APPEND PROPERTY OBJECT_DEPENDS ${rscout})

    endif ()

  endforeach ()
endmacro()

add_subdirectory(Bibliotecas/Global)
add_subdirectory(Bibliotecas/Log)
add_subdirectory(Bibliotecas/Gui)
add_subdirectory(Bibliotecas/Sql)
add_subdirectory(Bibliotecas/Configuracao)
add_subdirectory(Bibliotecas/Modulos)
add_subdirectory(Bibliotecas/Recursos)
add_subdirectory(Aplicativos/Controle)
add_subdirectory(Aplicativos/Teste)