#include "../unity/unity.h"
#include "../src/edit_distance/edit_distance.h"

void setUp(void) {}
void tearDown(void) {}

void test_base_cases(void) {
    TEST_ASSERT_EQUAL_INT(0, edit_distance("", ""));
    TEST_ASSERT_EQUAL_INT(1, edit_distance("a", ""));
    TEST_ASSERT_EQUAL_INT(1, edit_distance("", "a"));
}

void test_examples_recursive(void) {
    TEST_ASSERT_EQUAL_INT(1, edit_distance("casa", "cassa"));
    TEST_ASSERT_EQUAL_INT(2, edit_distance("casa", "cara"));
    TEST_ASSERT_EQUAL_INT(2, edit_distance("vinaio", "vino"));
    TEST_ASSERT_EQUAL_INT(4, edit_distance("tassa", "passato"));
    TEST_ASSERT_EQUAL_INT(0, edit_distance("pioppo", "pioppo"));
}

void test_dynamic_matches_recursive(void) {
    const char *s1[] = {"casa", "casa", "vinaio", "tassa", "pioppo"};
    const char *s2[] = {"cassa","cara","vino","passato","pioppo"};
    for (int i = 0; i < 5; ++i) {
        int rec = edit_distance(s1[i], s2[i]);
        int dyn = edit_distance_dyn(s1[i], s2[i]);
        TEST_ASSERT_EQUAL_INT(rec, dyn);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_base_cases);
    RUN_TEST(test_examples_recursive);
    RUN_TEST(test_dynamic_matches_recursive);
    return UNITY_END();
}