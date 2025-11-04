cmake_minimum_required(VERSION 3.31)
project(DSA_Project2)

set(CMAKE_CXX_STANDARD 17)

#compile flags to match Gradescope test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

##pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2 # seems to work with CLion - if you run into problems, try an older version of catch2 v3
)
FetchContent_MakeAvailable(Catch2)

# These tests can use the Catch2-provided main

include_directories(src)

add_executable(Tests
        test/test.cpp
        src/trieTree.h
        src/hashTable.h
        src/pokemon.h
        src/linkedLists.h
        # your test file
        # add your own header files below
)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
# the name here must match that of your testing executable (the one that has test.cpp)

## Qt UI application
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets QUIET)
if (Qt6Widgets_FOUND)
    add_executable(PokemonUI
            src/app_ui.cpp
            src/trieTree.h
            src/hashTable.h
            src/pokemon.h
            src/linkedLists.h
            src/app_ui.cpp)
    target_link_libraries(PokemonUI PRIVATE Qt6::Widgets)
    # Avoid macro name collisions: prefer Q_SLOTS/Q_SIGNALS over slots/signals
    target_compile_definitions(PokemonUI PRIVATE QT_NO_KEYWORDS)
endif()

