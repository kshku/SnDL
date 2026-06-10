# SnDL

Shared library loading abstraction for C17. Provides a cross-platform API to open, close, and look up symbols in dynamically linked libraries (`.so` / `.dylib` / `.dll`).

## API

### Flags

```c
typedef enum SnDLOpenFlags {
    SN_DL_OPEN_FLAG_NONE    = 0,
    SN_DL_OPEN_FLAG_LAZY    = SN_BIT_FLAG(0),    // Resolve symbols on first use
    SN_DL_OPEN_FLAG_NOW     = SN_BIT_FLAG(1),    // Resolve all symbols immediately
    SN_DL_OPEN_FLAG_LOCAL   = SN_BIT_FLAG(2),    // Symbols not visible to other libraries
    SN_DL_OPEN_FLAG_GLOBAL  = SN_BIT_FLAG(3),    // Symbols visible to other libraries
    SN_DL_OPEN_FLAG_DEFAULT = SN_DL_OPEN_FLAG_NOW | SN_DL_OPEN_FLAG_LOCAL
} SnDLOpenFlags;
```

### Functions

| Function | Description |
|----------|-------------|
| `void *sn_dl_open(const char *path, int32_t flags)` | Open a shared library. Returns handle or NULL. |
| `void *sn_dl_get_symbol(void *handle, const char *symbol)` | Look up a symbol by name. Returns pointer or NULL. |
| `bool sn_dl_close(void *handle)` | Close a shared library. Returns true on success. |

## Usage

```c
#include <sndl/sndl.h>
#include <stdio.h>

typedef int (*binop_fn)(int, int);

int main(void) {
    void *handle = sn_dl_open("./mylib.so", SN_DL_OPEN_FLAG_DEFAULT);
    if (!handle) return 1;

    binop_fn add = (binop_fn)sn_dl_get_symbol(handle, "my_add");
    if (add) printf("add(2, 3) = %d\n", add(2, 3));

    sn_dl_close(handle);
    return 0;
}
```

## Adding to your project

```cmake
include(FetchContent)
FetchContent_Declare(sndl
    GIT_REPOSITORY https://github.com/kshku/SnDL.git
    GIT_TAG main
)
FetchContent_MakeAvailable(sndl)

target_link_libraries(myapp PRIVATE sndl)
```

## Build

```sh
cmake -B build
cmake --build build
```

| Option | Default | Description |
|--------|---------|-------------|
| `SN_DL_BUILD_SHARED` | `OFF` | Build as shared library |
| `SN_DL_BUILD_TEST` | `OFF` | Build tests |

## Platform Support

| Platform | Backend |
|----------|---------|
| Linux | `dlfcn.h` (dlopen, dlsym, dlclose) |
| macOS | `dlfcn.h` (dlopen, dlsym, dlclose) |
| Windows | `windows.h` (LoadLibrary, GetProcAddress, FreeLibrary) |

## Dependencies

- **SnCore** — fetched automatically via FetchContent (provides platform detection, macros, and API visibility helpers)
