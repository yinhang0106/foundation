file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.cpp)
foreach (source ${sources})
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
endforeach ()

target_link_libraries(fliter PUBLIC TBB::tbb)
target_compile_options(fliter PUBLIC -mavx2 -mfma)