project(CheckersTests  CXX;C)

# The test program
add_executable(CheckersTests CheckersTest.cpp)
target_link_libraries(CheckersTests PRIVATE CheckersGameLib catch sglib)

# The testApi program
add_executable(CheckersApiTest CheckersApiTest.cpp)
target_link_libraries(CheckersApiTest PRIVATE catch sglib CheckersGameApi)
