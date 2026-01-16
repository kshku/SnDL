#pragma once

#include "sndl/defines.h"

#if defined(SN_DL_STATIC)
    #define SN_API
#else
    #ifdef SN_EXPORT
        #if defined(SN_OS_LINUX) || defined(SN_OS_MAC)
            #define SN_API __attribute__((visibility("default")))
        #elif defined(SN_OS_WINDOWS)
            #define SN_API __declspec(dllexport)
        #else
            #error "Should not reach here!"
        #endif
    #else
        #if defined(SN_OS_LINUX) || defined(SN_OS_MAC)
            #define SN_API
        #elif defined(SN_OS_WINDOWS)
            #define SN_API __declspec(dllimport)
        #else
            #error "Should not reach here!"
        #endif
    #endif
#endif

typedef enum snDLOpenFlags {
    SN_DL_OPEN_FLAG_NONE = 0,

    SN_DL_OPEN_FLAG_LAZY = SN_BIT_FLAG(0), /**< Resolve symbols on first use */
    SN_DL_OPEN_FLAG_NOW = SN_BIT_FLAG(1), /**< Resolve all symbols immediately */

    SN_DL_OPEN_FLAG_LOCAL = SN_BIT_FLAG(2), /**< Symbols not visible to other libraries */
    SN_DL_OPEN_FLAG_GLOBAL = SN_BIT_FLAG(3), /**< Symbols visible to other libraries */

    SN_DL_OPEN_FLAG_DEFAULT = SN_DL_OPEN_FLAG_NOW | SN_DL_OPEN_FLAG_LOCAL
} snDLOpenFlags;

/**
 * @brief Open a dll.
 *
 * @param path Path to the dll.
 * @param flags The snDLOpenFlags
 *
 * @note On platforms that doesn't support flags, they are ignored.
 *
 * @return Returns NULL on failure else handle to the opened dll.
 */
SN_API void *sn_dl_open(const char *path, int32_t flags);

/**
 * @brief Get the symbol from the dll.
 *
 * @param handle Handle to the opened dll.
 * @param symbol Name of the symbol.
 *
 * @return Returns the symbol or NULL on failure.
 */
SN_API void *sn_dl_get_symbol(void *handle, const char *symbol);

/**
 * @brief Close the opened dll.
 *
 * @param handle The handle to the opened dll.
 */
SN_API bool sn_dl_close(void *handle);

#undef SN_API
