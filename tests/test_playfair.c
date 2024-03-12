#include <stdio.h>
#include <stdlib.h>
#include "greatest.h"
#include "../playfair.h"


TEST playfair_encrypt_even_length_str() {
    ASSERT_STR_EQ("ISJZJQXNTKJC", playfair_encrypt("SeCReT", "Hello world"));
    PASS();
}


TEST playfair_decrypt_even_length_str() {
    // TODO Fix the assertion.
    ASSERT_STR_EQ("HELXLOVORLDX", playfair_decrypt("SeCReT", "HELXLOVORLDX"));  
    PASS();
}


SUITE(test_playfair) {
    RUN_TEST(playfair_encrypt_even_length_str);
    RUN_TEST(playfair_decrypt_even_length_str);
}

