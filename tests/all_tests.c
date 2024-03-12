#include "greatest.h"

extern SUITE(test_bmp);
extern SUITE(test_playfair);
extern SUITE(test_utils);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(test_utils);
    RUN_SUITE(test_bmp);
    RUN_SUITE(test_playfair);
    GREATEST_MAIN_END();
}

