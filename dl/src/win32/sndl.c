#include "sndl/sndl.h"

#if defined(SN_OS_WINDOWS)

    #include <sncore/utf.h>
    #include <windows.h>

void *sn_dl_open(const char *path, int32_t flags) {
    SN_UNUSED(flags);
    wchar_t wpath[4096];
    if (sn_utf8_to_utf16(path, wpath, SN_ARRAY_LENGTH(wpath)) == (size_t)-1) return NULL;
    return (void *)LoadLibraryW(wpath);
}

void *sn_dl_get_symbol(void *handle, const char *symbol) {
    return (void *)GetProcAddress((HMODULE)handle, symbol);
}

bool sn_dl_close(void *handle) {
    return FreeLibrary((HMODULE)handle);
}

#endif
