enable_testing()

set(SRCS
    test.c
)

add_executable(sn_dl_test)
target_sources(sn_dl_test PRIVATE ${SRCS})
target_link_libraries(sn_dl_test PRIVATE sndl)

add_test(NAME sn_dl_test COMMAND sn_dl_test)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" AND SN_DL_BUILD_SHARED)
    add_custom_target(copy_dlls ALL
        COMMENT "Copy the dlls"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_RUNTIME_DLLS:sn_dl_test>" "$<TARGET_FILE_DIR:sn_dl_test>"
        COMMAND_EXPAND_LISTS
    )

    add_dependencies(copy_dlls sn_dl_test)
endif()

add_library(dl_test_lib SHARED testlib.c)
target_compile_definitions(sn_dl_test PRIVATE SN_DL_TEST_LIB="$<TARGET_FILE:dl_test_lib>")
