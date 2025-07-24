# Build static and shared libs for queue
add_library(QueueStatic STATIC queue.c)
add_library(QueueShared SHARED queue.c)

target_include_directories(QueueStatic PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(QueueShared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Build test binary
add_executable(QueueTest testQueue.c)
target_include_directories(QueueTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(QueueTest PRIVATE QueueStatic)

# Register test
enable_testing()
add_test(NAME QueueTest COMMAND QueueTest)
