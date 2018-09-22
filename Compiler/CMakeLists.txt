cmake_minimum_required(VERSION 3.7)
project(Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FileHandler.cpp FileHandler.h LexicalParser.cpp LexicalParser.h Node.cpp Node.h NFAGenerator.cpp NFAGenerator.h DFAGenerator.cpp DFAGenerator.h graphGenerator.cpp graphGenerator.h Graph.cpp Graph.h Edge.cpp Edge.h TokenPath.cpp TokenPath.h TableRow.cpp TableRow.h ParsingUtils.cpp ParsingUtils.h SyntaxParser.cpp SyntaxParser.h ParserOptmizer.cpp ParserOptmizer.h FirstFollow.cpp FirstFollow.h parseTable.cpp parseTable.h treeHandler.cpp treeHandler.h FileWriter.cpp FileWriter.h ParserTreeGenerator.cpp ParserTreeGenerator.h StringVectorUtilis.cpp StringVectorUtilis.h tokensGenerator.cpp tokensGenerator.h)
add_executable(Compiler ${SOURCE_FILES})