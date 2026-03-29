#pragma once

#include "sndl/defines.h"

#include "sndl/api.h"

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
