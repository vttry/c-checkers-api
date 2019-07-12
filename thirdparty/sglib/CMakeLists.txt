project (Catch C)

# Header only library, therefore INTERFACE
add_library(sglib INTERFACE)

# INTERFACE targets only have INTERFACE properties
target_include_directories(sglib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)