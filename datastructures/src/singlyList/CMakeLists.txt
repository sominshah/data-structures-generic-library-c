# Build static and shared libs for singlyList
add_library(SinglyListStatic STATIC singlyList.c)
add_library(SinglyListShared SHARED singlyList.c)

target_include_directories(SinglyListStatic PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(SinglyListShared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Build test binary
add_executable(SinglyListTest testSinglyList.c)
target_include_directories(SinglyListTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(SinglyListTest PRIVATE SinglyListStatic)

# Register test
enable_testing()
add_test(NAME SinglyListTest COMMAND SinglyListTest)
