#ifndef BMP_H
#define BMP_H

char* reverse(const char* text);
char* vigenere_encrypt(const char* key, const char* text);
char* vigenere_decrypt(const char* key, const char* text);
char* bit_encrypt(const char* text);
char* bit_decrypt(const char* text);
char* bmp_encrypt(const char* key, const char* text);
char* bmp_decrypt(const char* key, const char* text);

// -------------------------------------------------------

#define CAESAR_ENCRYPT 1
#define CAESAR_DECRYPT -1

char* vigenere_str(const char* key, const char* text, char caesar_direction);
char caesar_character(char input_char, char step, char caesar_direction);

unsigned char bit_encrypt_char(unsigned char t);
unsigned char bit_decrypt_char(unsigned char t);

#endif /* BMP_H */