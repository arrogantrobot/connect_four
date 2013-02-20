cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS python REQUIRED)
message("Include dirs of boost: " ${Boost_INCLUDE_DIRS} )
message("Libs of boost: " ${Boost_LIBRARIES} )

find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS} )
message("Libs of Python: " ${PYTHON_LIBRARIES} )

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${PYTHON_INCLUDE_DIRS}
)

add_library(testpy
    python_confor.cpp
)

target_link_libraries(testpy
    ${Boost_LIBRARIES}
    ${PYTHON_LIBRARIES}
)

add_executable(connect_four
	connect_four.cpp
	Board.cpp
    MiniMaxTree.cpp
)

add_executable(confour
	confor.cpp
	Board.cpp
    MiniMaxTree.cpp
)

add_subdirectory(gtest-1.6.0)
add_executable(connect_four_test
    ConnectFourTest.cpp
    Board.cpp
    MiniMaxTree.cpp
)
target_link_libraries(connect_four_test
    gtest
    gtest_main
)
