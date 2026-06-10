set(HEADERFILES
    sndl.h
)

set(SPECIFIC_SRCS
    sndl.c
)

set(INCLUDE_BASE "${PROJECT_SOURCE_DIR}/dl/include/sndl")

set(SUBDIRS
    win32
    nix
)

list(TRANSFORM HEADERFILES PREPEND "${INCLUDE_BASE}/")

target_sources(sndl PRIVATE ${HEADERFILES})

foreach(dir IN LISTS SUBDIRS)
    foreach(src IN LISTS SPECIFIC_SRCS)
        target_sources(sndl PRIVATE "${dir}/${src}")
    endforeach()
endforeach()
