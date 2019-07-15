project(CheckersTests  CXX;RC)

# The test program
add_executable(CheckersTests CheckersTest.cpp)
target_link_libraries(CheckersTests PRIVATE CheckersGameLib catch sglib)