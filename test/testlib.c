#if defined(_WIN32)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

EXPORT int dl_test_add(int a, int b) {
    return a + b;
}

EXPORT int dl_test_sub(int a, int b) {
    return a - b;
}

