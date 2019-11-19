# current sharing
add_executable(solenoid
    solenoid.cpp)
target_link_libraries(solenoid 
    mylib-st ${LIBS} ${RAT_MLFMM_LIBRARY} ${RAT_COMMON_LIBRARY} ${RAT_MODELS_LIBRARY})

# enable CUDA linking
if(ENABLE_CUDA)
set_target_properties(solenoid PROPERTIES LINKER_LANGUAGE CUDA)
endif()

