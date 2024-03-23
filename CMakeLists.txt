cmake_minimum_required(VERSION 3.2)

project(Astral)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/API.cpp
        src/Astral.cpp
        
        src/Runtime/Memory/GarbageCollector.cpp
        src/Runtime/Memory/MemoryBlock.cpp
        
        src/Runtime/Types/AstralTypes.cpp
        src/Runtime/Variables/Variable.cpp
        src/Runtime/Variables/Variables.cpp
        
        src/Runtime/BindFunction.cpp
        src/Runtime/BooleanHandler.cpp
        src/Runtime/BuiltInFunctions.cpp
        src/Runtime/BuiltInLibraries.cpp
        src/Runtime/Interpreter.cpp
        src/Runtime/Library.cpp
        src/Runtime/MathsHandler.cpp
        
        src/Compilation/Tokenisation/Lexer.cpp
        
        src/Compilation/Parsing/Expressions/BinaryOp.cpp
        src/Compilation/Parsing/Expressions/CallParameters.cpp
        src/Compilation/Parsing/Expressions/DecrementExpression.cpp
        src/Compilation/Parsing/Expressions/Factorial.cpp
        src/Compilation/Parsing/Expressions/FunctionCall.cpp
        src/Compilation/Parsing/Expressions/Grouping.cpp
        src/Compilation/Parsing/Expressions/IncrementExpression.cpp
        src/Compilation/Parsing/Expressions/Literal.cpp
        src/Compilation/Parsing/Expressions/UnaryOp.cpp
        
        src/Compilation/Parsing/Statements/Block.cpp
        src/Compilation/Parsing/Statements/Break.cpp
        src/Compilation/Parsing/Statements/Continue.cpp
        src/Compilation/Parsing/Statements/Empty.cpp
        src/Compilation/Parsing/Statements/ExpressionStatement.cpp
        src/Compilation/Parsing/Statements/Function.cpp
        src/Compilation/Parsing/Statements/IfStatement.cpp
        src/Compilation/Parsing/Statements/Include.cpp
        src/Compilation/Parsing/Statements/MemberAssignment.cpp
        src/Compilation/Parsing/Statements/ParamList.cpp
        src/Compilation/Parsing/Statements/Program.cpp
        src/Compilation/Parsing/Statements/Return.cpp
        src/Compilation/Parsing/Statements/StructDefinition.cpp
        src/Compilation/Parsing/Statements/Using.cpp
        src/Compilation/Parsing/Statements/While.cpp
        src/Compilation/Parsing/Statements/VariableAssignment.cpp
        src/Compilation/Parsing/Statements/VariableDefinition.cpp
        
        src/Compilation/Parsing/Expression.cpp
        src/Compilation/Parsing/Parser.cpp
        src/Compilation/Parsing/ParseTree.cpp
        src/Compilation/Parsing/Statement.cpp
        
        src/Compilation/Linker/Linker.cpp
        
        src/Compilation/Compiler/Compiler.cpp
)

add_library(Astral SHARED ${SOURCES})

#set_target_properties(Astral, PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
