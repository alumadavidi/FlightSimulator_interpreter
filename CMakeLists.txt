cmake_minimum_required(VERSION 3.15)
project(untitled11)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(untitled11 main.cpp Command/Command.h Command/CommandsClasses.cpp Command/CommandsClasses.h VariableAir.cpp VariableAir.h Singleton.h Parser.cpp Parser.h Lexer.cpp Lexer.h Command/InitMaps.cpp Command/InitMaps.h ShuntingAlgorithm/BasicVar.cpp ShuntingAlgorithm/BasicVar.h ShuntingAlgorithm/BinaryAndUnaryAbstract.cpp ShuntingAlgorithm/BinaryAndUnaryAbstract.h ShuntingAlgorithm/BinaryOperators.cpp ShuntingAlgorithm/BinaryOperators.h ShuntingAlgorithm/Expression.h ShuntingAlgorithm/Interpeter.cpp ShuntingAlgorithm/UnaryOperators.cpp ShuntingAlgorithm/UnaryOperators.h ShuntingAlgorithm/Interpeter.h ProgramInclude.h)