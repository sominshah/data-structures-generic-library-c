# Build static and shared libs for stack
add_library(StackStatic STATIC stack.c)
add_library(StackShared SHARED stack.c)

target_include_directories(StackStatic PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(StackShared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Build test binary
add_executable(StackTest testStack.c)
target_include_directories(StackTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(StackTest PRIVATE StackStatic)

# Register test
enable_testing()
add_test(NAME StackTest COMMAND StackTest)
