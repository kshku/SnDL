#include <sndl/sndl.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_ASSERT(x) do { if (!(x)) { fprintf(stderr, "FAIL [%s:%d]: %s\n", __FILE__, __LINE__, #x); abort(); } } while(0)

typedef int (*dl_binop_fn)(int, int);

static dl_binop_fn dl_fn_cast(void *sym) {
    union { void *p; dl_binop_fn f; } u;
    u.p = sym;
    return u.f;
}

static void test_basic_load(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_DEFAULT);
    TEST_ASSERT(handle && "sn_dl_open failed");

    dl_binop_fn add = dl_fn_cast(sn_dl_get_symbol(handle, "dl_test_add"));
    TEST_ASSERT(add && "sn_dl_get_symbol(add) failed");

    dl_binop_fn sub = dl_fn_cast(sn_dl_get_symbol(handle, "dl_test_sub"));
    TEST_ASSERT(sub && "sn_dl_get_symbol(sub) failed");

    TEST_ASSERT(add(2, 3) == 5);
    TEST_ASSERT(sub(7, 4) == 3);

    TEST_ASSERT(sn_dl_close(handle));
}

static void test_flags(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_NOW | SN_DL_OPEN_FLAG_LOCAL);

    TEST_ASSERT(handle && "sn_dl_open_ex failed");

    dl_binop_fn add = dl_fn_cast(sn_dl_get_symbol(handle, "dl_test_add"));

    TEST_ASSERT(add);
    TEST_ASSERT(add(10, 5) == 15);

    TEST_ASSERT(sn_dl_close(handle));
}

static void test_invalid_symbol(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_NONE);
    TEST_ASSERT(handle);

    void *sym = sn_dl_get_symbol(handle, "this_symbol_does_not_exist");
    TEST_ASSERT(sym == NULL);

    TEST_ASSERT(sn_dl_close(handle));
}

static void test_double_close(void) {
    void *handle = sn_dl_open(SN_DL_TEST_LIB, SN_DL_OPEN_FLAG_NONE);
    TEST_ASSERT(handle);

    TEST_ASSERT(sn_dl_close(handle));
    TEST_ASSERT(!sn_dl_close(handle)); /* must fail safely */
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

