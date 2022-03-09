project(op)
file(GLOB op_header_files ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB op_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
if(NOT DISABLED_CUDA)
  file(GLOB op_cu_src_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cu")
  add_library(op_cu STATIC ${op_cu_src_files} ${op_header_files})
  set_target_properties(
    op_cu
    PROPERTIES POSITION_INDEPENDENT_CODE ON
               CUDA_SEPARABLE_COMPILATION ON
               LINKER_LANGUAGE CUDA)
  target_include_directories(op_cu PUBLIC ${ROOT_HEADER_DIRS}
                                          ${CMAKE_CURRENT_SOURCE_DIR})
endif()
add_library(op STATIC ${op_src_files} ${op_header_files})
target_include_directories(op PUBLIC ${ROOT_HEADER_DIRS}
                                     ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(op common)
