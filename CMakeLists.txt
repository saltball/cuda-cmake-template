cmake_minimum_required(VERSION 3.20)

project(openacc_prj LANGUAGES CXX)

option(DISABLED_CUDA "Disable CUDA" OFF)

set(PRJ_SRC_LIST)
set(PRJ_HEADER_LIST)
set(PRJ_LIBRARIES)
set(PRJ_INCLUDE_DIRS)
set(PRJ_COMPILE_OPTIONS)
set(PRJ_COMPILE_FEATURES)

include("cmake/AutoDetectCudaArch.cmake")

if(NOT DISABLED_CUDA)
  enable_language(CUDA)
endif()

message("-- system arch:  ${CMAKE_SYSTEM_PROCESSOR}")

if(NOT PROJECT_OUTPUT_DIR)
  set(PROJECT_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
  message("-- output path:  ${PROJECT_OUTPUT_DIR} ")
endif()

# set output path
set(PROJECT_OUTPUT_DIR ${PROJECT_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR})
set(PROJECT_INCLUDE_DIR ${PROJECT_OUTPUT_DIR}/include)

# mkdir directory
file(MAKE_DIRECTORY ${PROJECT_INCLUDE_DIR})
file(MAKE_DIRECTORY ${PROJECT_OUTPUT_DIR}/bin)
file(MAKE_DIRECTORY ${PROJECT_OUTPUT_DIR}/lib)

# set the target path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUTPUT_DIR}/lib)

# set the source files
file(GLOB root_header_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB root_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cu")
file(GLOB root_cu_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

list(APPEND PRJ_HEADER_LIST ${root_header_files})
list(APPEND PRJ_SRC_LIST ${root_src_files} ${root_cu_src_files})
list(APPEND PRJ_INCLUDE_DIRS ${OpenMP_CXX_INCLUDE_DIRS})
list(APPEND PRJ_COMPILE_FEATURES cxx_std_14)

# CUDA and C++ compiler flags
set(cxx_flags
    $<$<CXX_COMPILER_ID:MSVC>:-D_SCL_SECURE_NO_WARNINGS
    /bigobj
    /openmp
    /std:c++11> #< TODO> Add MSVC-specific compiler flags here
    $<$<CXX_COMPILER_ID:GNU>:-Wall
    -m64
    -fopenmp
    -O3
    -std=c++11> #< TODO> Add GCC/Clang-specific compiler flags here
)
set(CUDA_NVCC_FLAGS
${CUDA_NVCC_FLAGS};
    -Xcompiler=$<$<CXX_COMPILER_ID:GNU>:-Wall
    -fopenmp
    -O3>
    -Xcudafe=--display_error_number
    ${CUDA_ARCHS}
    -lineinfo
    --expt-extended-lambda
    -use_fast_math
    # -Xptxas -warn-spills -res-usage #-v
    $<$<CXX_COMPILER_ID:GNU>:-O3>
    # -G
)

#
add_executable(${PROJECT_NAME} ${PRJ_SRC_LIST} ${PRJ_HEADER_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${PRJ_INCLUDE_DIRS})

target_compile_options(${PROJECT_NAME} PRIVATE ${PRJ_COMPILE_OPTIONS})

target_compile_features(${PROJECT_NAME} PUBLIC ${PRJ_COMPILE_FEATURES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${PRJ_LIBRARIES})
