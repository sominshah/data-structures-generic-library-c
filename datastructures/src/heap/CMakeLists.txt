# Build static and shared libs for heap
add_library(HeapStatic STATIC heap.c)
add_library(HeapShared SHARED heap.c)

target_include_directories(HeapStatic PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(HeapShared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Build test binary
add_executable(HeapTest testHeap.c)
target_include_directories(HeapTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(HeapTest PRIVATE HeapStatic)

# Register test
enable_testing()
add_test(NAME HeapTest COMMAND HeapTest)
