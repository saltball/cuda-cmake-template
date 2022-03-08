cmake_minimum_required(VERSION 3.20)

project(openacc_prj LANGUAGES CXX CUDA)

option(DISABLED_CUDA "Disable CUDA" OFF)

set(PRJ_SRC_LIST)
set(PRJ_HEADER_LIST)
set(PRJ_LIBRARIES)
set(PRJ_INCLUDE_DIRS)
set(PRJ_COMPILE_OPTIONS)
set(PRJ_COMPILE_FEATURES)

# Select CUDA arch, by
# https://stackoverflow.com/questions/68223398/how-can-i-get-cmake-to-automatically-detect-the-value-for-cuda-architectures
include(FindCUDA/select_compute_arch)
cuda_detect_installed_gpus(INSTALLED_GPU_CCS_1)
string(STRIP "${INSTALLED_GPU_CCS_1}" INSTALLED_GPU_CCS_2)
string(REPLACE " " ";" INSTALLED_GPU_CCS_3 "${INSTALLED_GPU_CCS_2}")
string(REPLACE "." "" CUDA_ARCH_LIST "${INSTALLED_GPU_CCS_3}")
set(CMAKE_CUDA_ARCHITECTURES ${CUDA_ARCH_LIST})

# Global CUDA
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

# set C and CXX flags, refer to pytorch
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

if(NOT MSVC)
  string(APPEND CMAKE_CXX_FLAGS " -O2 -fPIC")
  string(APPEND CMAKE_CXX_FLAGS " -Wall")
  string(APPEND CMAKE_CXX_FLAGS " -Werror")
else()
  string(APPEND CMAKE_CXX_FLAGS " /O2")
  # string(APPEND CMAKE_CXX_FLAGS " /Wall")
endif()

# set CUDA flags, refer to pytorch
if(MSVC)
  string(APPEND CMAKE_CUDA_FLAGS " -Xcompiler /W4")
else()
  string(APPEND CMAKE_CUDA_FLAGS_DEBUG " -g -lineinfo --source-in-ptx")
  string(APPEND CMAKE_CUDA_FLAGS_RELWITHDEBINFO " -g -lineinfo --source-in-ptx")
endif()

string(APPEND CMAKE_CUDA_FLAGS " -Xfatbin -compress-all")

# set the source files
set(ROOT_HEADER_DIRS ${PROJECT_SOURCE_DIR}/include)
set(QC_ROOT_DIRS ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)

# target_include_directories(${PROJECT_NAME} PRIVATE ${PRJ_INCLUDE_DIRS})

# target_compile_options(${PROJECT_NAME} PRIVATE ${PRJ_COMPILE_OPTIONS})

# target_compile_features(${PROJECT_NAME} PUBLIC ${PRJ_COMPILE_FEATURES})

# target_link_libraries(${PROJECT_NAME} PRIVATE ${PRJ_LIBRARIES})

# transfer all global headers to the include directory
foreach(include ${ROOT_HEADER_FILES})
  message("-- Copying ${include} to ${PROJECT_INCLUDE_DIR}")
  configure_file(${include} ${PROJECT_INCLUDE_DIR} COPYONLY)
endforeach()
