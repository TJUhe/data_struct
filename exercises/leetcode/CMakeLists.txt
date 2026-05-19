function(add_leetcode_chapter name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE ds)
    set_target_properties(${name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endfunction()

add_leetcode_chapter(leetcode_01_arrays_prefix_two_pointers cpp/01_arrays_prefix_two_pointers.cpp)
add_leetcode_chapter(leetcode_02_linked_list cpp/02_linked_list.cpp)
add_leetcode_chapter(leetcode_03_stack_queue cpp/03_stack_queue.cpp)
add_leetcode_chapter(leetcode_04_hash_table cpp/04_hash_table.cpp)
add_leetcode_chapter(leetcode_05_tree_bst cpp/05_tree_bst.cpp)
add_leetcode_chapter(leetcode_06_heap_priority_queue cpp/06_heap_priority_queue.cpp)
add_leetcode_chapter(leetcode_07_graph cpp/07_graph.cpp)
add_leetcode_chapter(leetcode_08_sorting_design cpp/08_sorting_design.cpp)
