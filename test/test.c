#include <sndl/sndl.h>
#include <stdio.h>
#include <assert.h>

typedef int (*dl_binop_fn)(int, int);

static void test_basic_load(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_DEFAULT);
    assert(handle && "sn_dl_open failed");

    dl_binop_fn add =
        (dl_binop_fn)sn_dl_get_symbol(handle, "dl_test_add");
    assert(add && "sn_dl_get_symbol(add) failed");

    dl_binop_fn sub =
        (dl_binop_fn)sn_dl_get_symbol(handle, "dl_test_sub");
    assert(sub && "sn_dl_get_symbol(sub) failed");

    assert(add(2, 3) == 5);
    assert(sub(7, 4) == 3);

    assert(sn_dl_close(handle));
}

static void test_flags(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_NOW | SN_DL_OPEN_FLAG_LOCAL);

    assert(handle && "sn_dl_open_ex failed");

    dl_binop_fn add =
        (dl_binop_fn)sn_dl_get_symbol(handle, "dl_test_add");

    assert(add);
    assert(add(10, 5) == 15);

    assert(sn_dl_close(handle));
}

static void test_invalid_symbol(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_NONE);
    assert(handle);

    void *sym = sn_dl_get_symbol(handle, "this_symbol_does_not_exist");
    assert(sym == NULL);

    assert(sn_dl_close(handle));
}

static void test_double_close(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_NONE);
    assert(handle);

    assert(sn_dl_close(handle));
    assert(!sn_dl_close(handle)); /* must fail safely */
}

int main(void) {
    printf("[SnDL] running tests...\n");

    test_basic_load();
    test_flags();
    test_invalid_symbol();
    test_double_close();

    printf("[SnDL] all tests passed\n");
    return 0;
}

