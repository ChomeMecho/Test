#include "bmp.h"
#include "utils.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char* reverse(const char* text) {
    size_t text_len = strlen(text);
    char* reversed = calloc(text_len + 1, sizeof(char));
    
    // TODO complete implementation of this function
    
    return reversed;
}


char* vigenere_encrypt(const char* key, const char* text) {
    return vigenere_str(key, text, CAESAR_ENCRYPT);
}


char* vigenere_decrypt(const char* key, const char* text) {
    return vigenere_str(key, text, CAESAR_DECRYPT);
}


char* bit_encrypt(const char* text) {
    if(text == NULL) 
        return NULL;
    
    size_t text_len = strlen(text);
    char* out = calloc(text_len + 1, sizeof(char));
    
    for(size_t i = 0; i < text_len; i++) {
        out[i] = bit_encrypt_char(text[i]);
    }
    
    return out;
}


char* bit_decrypt(const char* text) {
    char* out = NULL;
    
    // TODO complete implementation of this function
    
    return out;
}


char* bmp_encrypt(const char* key, const char* text) {
    char* out = NULL;
    
    // TODO complete implementation of this function
    
    return out;
}


char* bmp_decrypt(const char* key, const char* text) {
    char* bit_decrypted = bit_decrypt(text);
    char* vigenere_decrypted = vigenere_decrypt(key, bit_decrypted);
    char* reversed = reverse(vigenere_decrypted);
    if(bit_decrypted) free(bit_decrypted);
    if(vigenere_decrypted) free(vigenere_decrypted);
    return reversed;
}


// -------------------------------


char caesar_character(char input_char, char step, char caesar_direction) {
    return (input_char - caesar_direction * 'A' + step * caesar_direction) % 26 + 'A';
}


char* vigenere_str(const char* key, const char* text, char caesar_direction) {
        
    if(key == NULL || text == NULL) 
        return NULL;
    
    size_t key_len = strlen(key);
    size_t text_len = strlen(text);
    
    if(key_len <= 0 || text_len <= 0) 
        return NULL;
    
    if(!isalpha_str(key)) 
        return NULL;
    
    char* enc_text = calloc(text_len + 1, sizeof(char));
    size_t j=0;
    for(size_t i = 0; i < text_len; i++) {
        char key_char = key[j % key_len];
        if(key_char >= 97 && key_char <=122) { 
            // key_char is lowercase character (see ascii table)
            key_char = key_char - ('a' - 'A');
        }
        if(isalpha(text[i])) {
            enc_text[i] = caesar_character(toupper(text[i]), key_char - 'A', caesar_direction);
            ++j;
        }
        else {
            enc_text[i] = text[i];
        }
        
    }
    enc_text[text_len] = '\0';
    
    return enc_text;
}


unsigned char bit_encrypt_char(unsigned char t) {
    unsigned char part1 = t & 0xf0;
    unsigned char part2 = t & 0x0f;
    unsigned char part1_1 = part1 & 0x30;
    unsigned char part1_2 = part1 & 0xc0;
    
    if(part1_1 != 0x30 && part1_1 != 0) {
        part1_1 = (~part1_1) & 0x30;
    }
    if(part1_2 != 0xc0 && part1_2 != 0) {
        part1_2 = (~part1_2) & 0xc0;
    }
    
    unsigned char n_part1 = (part1_1 | part1_2);
    unsigned char n_part2 = (n_part1 >> 4) ^ part2;
    
    unsigned char result = n_part1 | n_part2;
    return result;
}


unsigned char bit_decrypt_char(unsigned char t) {
    unsigned char part1 = t & 0xf0;
    unsigned char part2 = t & 0x0f;
    
    unsigned char n_part2 = (part1 >> 4) ^ part2;
    
    unsigned char part1_1 = part1 & 0x30;
    unsigned char part1_2 = part1 & 0xc0;
    
    if(part1_1 != 0x30 && part1_1 != 0) {
        part1_1 = (~part1_1) & 0x30;
    }
    if(part1_2 != 0xc0 && part1_2 != 0) {
        part1_2 = (~part1_2) & 0xc0;
    }
    
    unsigned char n_part1 = (part1_1 | part1_2);
    
    unsigned char result = n_part1 | n_part2;
    return result;
}
