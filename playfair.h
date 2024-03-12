#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <stddef.h>

#define PLAYFAIR_REPLACED_CHAR       'W'
#define PLAYFAIR_REPLACEMENT_CHAR    'V'
#define PLAYFAIR_PAIR_SEPARATOR_CHAR 'X'

char* playfair_encrypt(const char* key, const char* text);
char* playfair_decrypt(const char* key, const char* text);

int playfair_matrix_build(char matrix[5][5], const char* key);
int playfair_matrix_locate_character(char matrix[5][5], char character, size_t* row_i, size_t* col_j);

#endif /* PLAYFAIR_H */