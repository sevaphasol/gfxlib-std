cmake_minimum_required( VERSION 3.16 )
project( dr4hui-backend LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include(cmake/funcs.cmake)

setup_constants()
setup_interface()
setup_libs()
install_libs()
build_examples()
