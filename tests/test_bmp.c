#include <stdio.h>
#include <stdlib.h>
#include "greatest.h"
#include "../bmp.h"

TEST vigenere_encrypt_basic_long_text() {
    ASSERT_STR_EQ("JSXAI PSINR!", vigenere_encrypt("CoMPuTeR", "Hello world!"));
    PASS();
}

TEST bmp_encrypt_basic_long_text() {
    unsigned char text[12] = {16, 142, 160, 140, 140, 171, 17, 128, 170, 139, 143, 172};
    char * t = bmp_encrypt("CoMPuTeR", "Hello world!");
    ASSERT(t != NULL);
    ASSERT_MEM_EQ(text, t, 12);
    PASS();
}

TEST reverse_basic_long_text() {
    ASSERT_STR_EQ("!DLROW OLLEH", reverse("Hello world!"));
    PASS();
}

SUITE(test_bmp) {
    RUN_TEST(vigenere_encrypt_basic_long_text);
    RUN_TEST(bmp_encrypt_basic_long_text);
    RUN_TEST(reverse_basic_long_text);
}

