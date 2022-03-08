cmake_minimum_required(VERSION 3.12)
project(MIP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB_RECURSE mip_SRC
        "src/**.h"
        "src/**.hpp"
        "src/**.cpp"
        )
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CPLEX_STUDIO_DIR /Applications/CPLEX_Studio201/)
    set(CPLEX_STUDIO_ARCH x86-64_osx)
else ()
    set(CPLEX_STUDIO_DIR /opt/ibm/ILOG/CPLEX_Studio201)
    set(CPLEX_STUDIO_ARCH x86-64_linux)
endif ()


link_directories(${CPLEX_STUDIO_DIR}/concert/lib/${CPLEX_STUDIO_ARCH}/static_pic)
link_directories(${CPLEX_STUDIO_DIR}/cplex/lib/${CPLEX_STUDIO_ARCH}/static_pic)


add_executable(MIP ${mip_SRC})

if (EXISTS "${CPLEX_STUDIO_DIR}/cplex/include/ilcplex/ilocplexi.h")
    target_include_directories(MIP PUBLIC ${CPLEX_STUDIO_DIR}/concert/include)
    target_include_directories(MIP PUBLIC ${CPLEX_STUDIO_DIR}/cplex/include)
    target_compile_definitions(MIP PRIVATE IL_STD)
    target_compile_definitions(MIP PRIVATE CPLEX)
    target_link_libraries(MIP PUBLIC dl)
    target_link_libraries(MIP PUBLIC ilocplex)
    target_link_libraries(MIP PUBLIC cplex)
    target_link_libraries(MIP PUBLIC concert)
    target_link_libraries(MIP PUBLIC pthread)
endif ()