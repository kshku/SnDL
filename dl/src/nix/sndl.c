#include "sndl/sndl.h"

#if defined(SN_OS_LINUX) || defined(SN_OS_MAC)

#include <dlfcn.h>

void *sn_dl_open(const char *path, int32_t flags) {
    int dl_flags = 0;
    if (flags & SN_DL_OPEN_FLAG_LAZY) dl_flags |= RTLD_LAZY;
    else dl_flags |= RTLD_NOW;

    if (flags & SN_DL_OPEN_FLAG_GLOBAL) dl_flags |= RTLD_GLOBAL;
    else dl_flags |= RTLD_LOCAL;

    return dlopen(path, dl_flags);
}

void *sn_dl_get_symbol(void *handle, const char *symbol) {
    return dlsym(handle, symbol);
}

bool sn_dl_close(void *handle) {
    return dlclose(handle) == 0;
}

#endif
