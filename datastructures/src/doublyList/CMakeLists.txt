# Build static and shared libs for doublyList
add_library(DoublyListStatic STATIC doublyList.c)
add_library(DoublyListShared SHARED doublyList.c)

target_include_directories(DoublyListStatic PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(DoublyListShared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Build test binary
add_executable(DoublyListTest testDoublyList.c)
target_include_directories(DoublyListTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(DoublyListTest PRIVATE DoublyListStatic)

# Register test
enable_testing()
add_test(NAME DoublyListTest COMMAND DoublyListTest)
