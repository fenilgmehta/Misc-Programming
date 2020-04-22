cmake_minimum_required(VERSION 3.8)
project("Misc-Programming")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE on)

# add_subdirectory("75_CodeForces")  # Best
# add_subdirectory("76_CodeChef")
# add_subdirectory("77_HackerRank")
# add_subdirectory("78_HackerEarth")
# add_subdirectory("Daily Coding Programs")

file(GLOB sourceFILES *.cpp *.c)

FOREACH (sourceFile ${sourceFILES})
    get_filename_component(sourceFile_Path ${sourceFile} PATH)
    MESSAGE(STATUS "Process file, path: ${sourceFile}")

    get_filename_component(sourceFile_Name ${sourceFile} NAME)
    string(REPLACE " " "_" sourceFile_Name ${sourceFile_Name})
    string(REPLACE "'" "" sourceFile_Name ${sourceFile_Name})
    string(REPLACE "\"" "" sourceFile_Name ${sourceFile_Name})
    string(REPLACE "(" "_" sourceFile_Name ${sourceFile_Name})
    string(REPLACE ")" "_" sourceFile_Name ${sourceFile_Name})
    MESSAGE(STATUS "Process file, name: \"${sourceFile_Name}\"")

    add_executable("${sourceFile_Name}" "${sourceFile}")
endforeach (sourceFile)
