project(common)
file(GLOB common_header_files ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB common_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
if(NOT DISABLED_CUDA)
  file(GLOB common_cu_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cu")
  add_library(common_cu STATIC ${common_cu_src_files} ${common_header_files})
  set_target_properties(
    common_cu
    PROPERTIES POSITION_INDEPENDENT_CODE ON
               CUDA_SEPARABLE_COMPILATION ON
               LINKER_LANGUAGE CUDA)
  target_include_directories(common_cu PUBLIC ${ROOT_HEADER_DIRS}
                                              ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_library(common STATIC ${common_src_files} ${common_header_files})
target_include_directories(common PUBLIC ${ROOT_HEADER_DIRS}
                                         ${CMAKE_CURRENT_SOURCE_DIR})
