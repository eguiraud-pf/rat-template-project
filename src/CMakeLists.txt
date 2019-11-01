# current sharing
add_executable(main
    main.cpp)
target_link_libraries(main 
    ${LIBS} ${RAT_MLFMM_LIBRARY} ${RAT_COMMON_LIBRARY})

# enable CUDA linking
if(ENABLE_CUDA)
set_target_properties(main PROPERTIES LINKER_LANGUAGE CUDA)
endif()

