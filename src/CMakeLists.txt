# compile the MLFMM library
file(GLOB SOURCE_FILES "*.cpp")

# this is the "object library" target: compiles the sources only once
add_library(objlib OBJECT ${SOURCE_FILES})

# shared libraries need PIC
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

# separable compilation
set_target_properties(objlib PROPERTIES CUDA_SEPERABLE_COMPILATION ON)
if(ENABLE_CUDA)
set_target_properties(objlib PROPERTIES LINKER_LANGUAGE CUDA)
endif()

# If we have compiler requirements for this library, list them here
target_compile_features(objlib
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates)

# shared and static libraries built from the same object files
add_library(mylib-sh SHARED $<TARGET_OBJECTS:objlib>)
add_library(mylib-st STATIC $<TARGET_OBJECTS:objlib>)

# properties
set_target_properties(mylib-sh PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(mylib-st PROPERTIES VERSION ${PROJECT_VERSION})

# Depend on a library that we defined in the top-level file
target_link_libraries(mylib-sh ${LIBS} ${RAT_COMMON_LIBRARY} ${RAT_MLFMM_LIBRARY})
target_link_libraries(mylib-st ${LIBS} ${RAT_COMMON_LIBRARY} ${RAT_MLFMM_LIBRARY})

if(ENABLE_CUDA)
set_target_properties(mylib-sh PROPERTIES LINKER_LANGUAGE CUDA)
set_target_properties(mylib-st PROPERTIES LINKER_LANGUAGE CUDA)
endif()