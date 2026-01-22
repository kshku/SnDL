if(SN_DL_BUILD_SHARED)
    add_library(sndl SHARED)
    target_compile_definitions(sndl PRIVATE SN_EXPORT)
else()
    add_library(sndl STATIC)
    target_compile_definitions(sndl PUBLIC SN_DL_STATIC)
endif()

target_include_directories(sndl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(sndl PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(sndl PRIVATE sn_dl_configs)

add_subdirectory(src)
