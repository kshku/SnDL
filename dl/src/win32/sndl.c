#include "sndl/sndl.h"

#if defined(SN_OS_WINDOWS)

#include <windows.h>

void *sn_dl_open(const char *path, int32_t flags) {
    SN_UNUSED(flags);
    return (void *)LoadLibrary(path);
}

void *sn_dl_get_symbol(void *handle, const char *symbol) {
    return (void *)GetProcAddress((HMODULE)handle, symbol);
}

bool sn_dl_close(void *handle) {
    return FreeLibrary((HMODULE)handle);
}

#endif
