project(hello LANGUAGES CXX)

if(NOT DISABLED_CUDA)
  enable_language(CUDA)
endif()

set(PRJ_SRC_LIST)
set(PRJ_HEADER_LIST)
set(PRJ_LIBRARIES)
set(PRJ_INCLUDE_DIRS)
set(PRJ_COMPILE_OPTIONS)
# set(PRJ_COMPILE_FEATURES)

file(GLOB hello_header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB hello_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cu")
file(GLOB hello_cu_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB common_src_files "${QC_ROOT_DIRS}/common/*.cpp")

message(STATUS common_src_files:${common_src_files})

list(APPEND PRJ_HEADER_LIST ${hello_header_files} ${ROOT_HEADER_FILES})
list(APPEND PRJ_SRC_LIST ${hello_src_files} ${hello_cu_src_files} ${common_src_files})
list(APPEND PRJ_INCLUDE_DIRS ${OpenMP_CXX_INCLUDE_DIRS} ${ROOT_HEADER_DIRS} ./include)
# list(APPEND PRJ_COMPILE_FEATURES cxx_std_14)

# https://developer.nvidia.com/blog/building-cuda-applications-cmake

add_executable(${PROJECT_NAME} ${PRJ_SRC_LIST} ${PRJ_HEADER_LIST})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRJ_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${PRJ_COMPILE_OPTIONS})
# target_compile_features(${PROJECT_NAME} PUBLIC ${PRJ_COMPILE_FEATURES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRJ_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
