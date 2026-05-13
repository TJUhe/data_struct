cmake_minimum_required(VERSION 3.20)

project(CppDataStructuresLab
    VERSION 1.0.0
    DESCRIPTION "A hands-on C++ data structures tutorial"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(ds INTERFACE)
target_include_directories(ds INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

function(add_ds_example name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE ds)
    set_target_properties(${name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endfunction()

add_ds_example(01_complexity examples/01_complexity/main.cpp)
add_ds_example(02_array_list examples/02_array_list/main.cpp)
add_ds_example(03_linked_list examples/03_linked_list/main.cpp)
add_ds_example(04_stack_queue examples/04_stack_queue/main.cpp)
add_ds_example(05_hash_table examples/05_hash_table/main.cpp)
add_ds_example(06_tree examples/06_tree/main.cpp)
add_ds_example(07_heap_priority_queue examples/07_heap_priority_queue/main.cpp)
add_ds_example(08_graph examples/08_graph/main.cpp)
add_ds_example(09_sorting examples/09_sorting/main.cpp)
add_ds_example(10_integrated_lru examples/10_integrated_lru/main.cpp)

enable_testing()
add_executable(ds_smoke_tests tests/smoke_tests.cpp)
target_link_libraries(ds_smoke_tests PRIVATE ds)
set_target_properties(ds_smoke_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
add_test(NAME ds_smoke_tests COMMAND ds_smoke_tests)

