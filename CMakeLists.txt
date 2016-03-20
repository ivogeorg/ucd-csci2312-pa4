cmake_minimum_required(VERSION 3.3)
project(ucd-csci2312-pa4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        Game.cpp Game.h
        Piece.cpp Piece.h
        Agent.cpp Agent.h
        Simple.cpp Simple.h
        Strategic.cpp Strategic.h
        Resource.cpp Resource.h
        Food.cpp Food.h
        Advantage.cpp Advantage.h
        GamingTests.cpp GamingTests.h
        ErrorContext.cpp ErrorContext.h
        Exceptions.cpp Exceptions.h
        Strategy.h
        DefaultAgentStrategy.cpp DefaultAgentStrategy.h
        Gaming.h AggressiveAgentStrategy.cpp AggressiveAgentStrategy.h)
add_executable(ucd-csci2312-pa4 ${SOURCE_FILES})