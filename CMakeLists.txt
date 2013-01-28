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
