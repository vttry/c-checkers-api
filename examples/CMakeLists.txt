project(examples C)

# The main program
add_executable(BuildGameTree BuildGameTree.c)
target_link_libraries(BuildGameTree PRIVATE CheckersGameApi)
