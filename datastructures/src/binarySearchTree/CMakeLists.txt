# Build static and shared libs for binarySearchTree
add_library(BinarySearchTreeStatic STATIC binarySearchTree.c)
add_library(BinarySearchTreeShared SHARED binarySearchTree.c)

target_include_directories(BinarySearchTreeStatic PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(BinarySearchTreeShared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Build test binary
add_executable(BinarySearchTreeTest testBinarySearchTree.c)
target_include_directories(BinarySearchTreeTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(BinarySearchTreeTest PRIVATE BinarySearchTreeStatic)

# Register test
enable_testing()
add_test(NAME BinarySearchTreeTest COMMAND BinarySearchTreeTest)
