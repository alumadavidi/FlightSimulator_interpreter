cmake_minimum_required(VERSION 3.15)
project(hhh)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(untitled11 main.cpp Command.h CommandsClasses.cpp CommandsClasses.h ProgVariables.cpp ProgVariables.h Parser.cpp Parser.h Lexer.cpp Lexer.h InitMaps.cpp InitMaps.h BasicVar.cpp BasicVar.h BinaryAndUnaryAbstract.cpp BinaryAndUnaryAbstract.h BinaryOperators.cpp BinaryOperators.h Expression.h Interpeter.cpp UnaryOperators.cpp UnaryOperators.h Interpeter.h ProgramInclude.h serverCommand.cpp serverCommand.h ClientCommand.cpp ClientCommand.h Data.h Data.cpp)