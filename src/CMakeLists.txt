project(CheckersGame C)

# All sources that also need to be included into a static library
add_library(CheckersGameLib STATIC CheckersGame.c CheckersGame.h Move.h Move.c Checker.h Player.h)
target_include_directories(CheckersGameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CheckersGameLib PRIVATE sglib)

# All sources that also need to be included into a CheckersGameAPI
add_library(CheckersGameApi STATIC CheckersGameApi.h CheckersGameApi.c GameTree.h GameTree.c)
target_include_directories(CheckersGameApi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CheckersGameApi PRIVATE sglib CheckersGameLib)

