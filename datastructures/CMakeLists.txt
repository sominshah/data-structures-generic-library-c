cmake_minimum_required(VERSION 3.10)
project(Datastructures C)

#Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

#Include main headers  directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add subdirectories for each module
add_subdirectory(src/singlyList)
add_subdirectory(src/stack)
add_subdirectory(src/queue)
add_subdirectory(src/doublyList)
add_subdirectory(src/heap)
add_subdirectory(src/binarySearchTree)

#add_subdirectory(src/utility)

# Optionally: combine all modules into a super static/shared lib
#add_library(DataStructuresStatic STATIC "")
#add_library(DataStructuresShared SHARED "")

# Link object files from each module to the final DataStructures library
#target_link_libraries(DataStructuresStatic PRIVATE 
#singlyListStatic 
#doublyListStatic
#stackStatic
#utilityStatic)

#target_link_libraries(DataStructuresShared PRIVATE SinglyListShared 
#StackShared
#UtilityShared)




# Optionally, export the public include headers to consumers
#target_include_directories(DataStructuresStatic PUBLIC ${PROJECT_SOURCE_DIR}/include)
#target_include_directories(DataStructuresShared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Enable global test discovery
enable_testing()






