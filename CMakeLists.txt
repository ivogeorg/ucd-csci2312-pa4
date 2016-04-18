cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    examples/virtual_operator.cpp
    Advantage.h
    Agent.h
    AggressiveAgentStrategy.h
    CMakeLists.txt
    DefaultAgentStrategy.h
    ErrorContext.cpp
    ErrorContext.h
    Exceptions.h
    Food.h
    Game.h
    Gaming.h
    GamingTests.cpp
    GamingTests.h
    main.cpp
    Piece.h
    Resource.h
    Simple.h
    Strategic.h
    Strategy.h Advantage.cpp Agent.cpp AggressiveAgentStrategy.cpp DefaultAgentStrategy.cpp Exceptions.cpp Food.cpp Game.cpp Piece.cpp Resource.cpp Simple.cpp Strategic.cpp)

add_executable(ucd_csci2312_pa4 ${SOURCE_FILES})