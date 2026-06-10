#pragma once

#include <sncore/api_common.h>

#if defined(SN_DL_STATIC)
    #define SN_DL_API
#elif defined(SN_EXPORT)
    #define SN_DL_API SN_API_HELPER_EXPORT
#else
    #define SN_DL_API SN_API_HELPER_IMPORT
#endif
