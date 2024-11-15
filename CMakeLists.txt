
cmake_minimum_required(VERSION 3.20)
project(test)

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 添加路径下的所有源文件
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

# 排除 binary_heap.cpp 文件
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/binary_heap.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})
add_executable(binary_heap binary_heap.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/base)

target_link_libraries(${PROJECT_NAME} PUBLIC easyx)

# graph
file(GLOB SRC_FILES_GRAPH ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(graph ${SRC_FILES_GRAPH})
