#include "playfair.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


char* playfair_encrypt(const char* key, const char* text) {
    if(key == NULL || text == NULL)
        return NULL;
    
    size_t key_len = strlen(key);
    size_t text_len = strlen(text);
    
    if(key_len <= 0 || text_len <= 0) 
        return NULL;
    
    char  playfair_matrix[5][5];
    if(playfair_matrix_build(playfair_matrix, key) < 0)
        return NULL;
    
    char* tmp_text = remove_character(text, ' ');
    
    if(!isalpha_str(tmp_text)) 
        return NULL;
        
    strtoupper(tmp_text);
    replace_character(tmp_text, PLAYFAIR_REPLACED_CHAR, PLAYFAIR_REPLACEMENT_CHAR);
    
    char* new_text = separate_duplicate_characters(tmp_text, PLAYFAIR_PAIR_SEPARATOR_CHAR); //remove_duplicate_characters(text);
    free(tmp_text);
    
    tmp_text = expand_to_even_length(new_text, PLAYFAIR_PAIR_SEPARATOR_CHAR);
    if(tmp_text) {
        free(new_text);
        new_text = tmp_text;
    }
    
    text_len = strlen(new_text);
    if(text_len <= 0) 
        return NULL;
  
    
    for(size_t i=0; i<text_len; i+=2) {
        size_t char1_i = 0;
        size_t char1_j = 0;
        size_t char2_i = 0;
        size_t char2_j = 0;
        size_t enc_char1_i = 0;
        size_t enc_char1_j = 0;
        size_t enc_char2_i = 0;
        size_t enc_char2_j = 0;
        
        if(!playfair_matrix_locate_character(playfair_matrix, new_text[i], &char1_i, &char1_j) || 
           !playfair_matrix_locate_character(playfair_matrix, new_text[i+1], &char2_i, &char2_j)) {
            return NULL;
        }
        
        if(char1_i == char2_i) {
            enc_char1_j = (char1_j+1) % 5;
            enc_char2_j = (char2_j+1) % 5;
            enc_char1_i = char1_i;
            enc_char2_i = char2_i;
        }
        else if(char1_j == char2_j) {
            enc_char1_i = (char1_i+1) % 5;
            enc_char2_i = (char2_i+1) % 5;
            enc_char1_j = char1_j;
            enc_char2_j = char2_j;
        }
        else {
            enc_char1_i = char1_i;
            enc_char1_j = char2_j;
            enc_char2_i = char2_i;
            enc_char2_j = char1_j;
        }
        
        new_text[i] = playfair_matrix[enc_char1_i][enc_char1_j];
        new_text[i+1] = playfair_matrix[enc_char2_i][enc_char2_j];
    }
         
    return new_text;
}


char* playfair_decrypt(const char* key, const char* text) {
    if(key == NULL || text == NULL)
        return NULL;
    
    size_t key_len = strlen(key);
    size_t text_len = strlen(text);
    
    if(key_len <= 0 || text_len <= 0) 
        return NULL;
 
    char* new_text = remove_character(text, ' ');
    
    if(!isalpha_str(new_text)) 
        return NULL;
     
    strtoupper(new_text);
    
    if(strchr(new_text, PLAYFAIR_REPLACED_CHAR))
        return NULL;
    
    char  playfair_matrix[5][5];
    if(playfair_matrix_build(playfair_matrix, key) < 0)
        return NULL;
    
    text_len = strlen(new_text);
    for(size_t i=0; i<text_len; i+=2) {
        size_t char1_i = 0;
        size_t char1_j = 0;
        size_t char2_i = 0;
        size_t char2_j = 0;
        size_t enc_char1_i = 0;
        size_t enc_char1_j = 0;
        size_t enc_char2_i = 0;
        size_t enc_char2_j = 0;
        
        if(!playfair_matrix_locate_character(playfair_matrix, new_text[i], &enc_char1_i, &enc_char1_j) || 
           !playfair_matrix_locate_character(playfair_matrix, new_text[i+1], &enc_char2_i, &enc_char2_j)) {
            return NULL;
        }
        
        if(enc_char1_i == enc_char2_i) {
            char1_j = enc_char1_j > 0 ? enc_char1_j-1 : 4;
            char1_i =  enc_char1_i;
            char2_j = enc_char2_j > 0 ? enc_char2_j-1 : 4;
            char2_i =  enc_char2_i;
        }
        else if(enc_char1_j == enc_char2_j) {
            char1_i = enc_char1_i > 0 ? enc_char1_i-1 : 4;
            char1_j = enc_char1_j;
            char2_i = enc_char2_i > 0 ? enc_char2_i-1 : 4;
            char2_j = enc_char2_j;
        }
        else {
            char1_i = enc_char1_i;
            char1_j = enc_char2_j;
            char2_i = enc_char2_i;
            char2_j = enc_char1_j;
        }
        
        new_text[i] = playfair_matrix[char1_i][char1_j];
        new_text[i+1] = playfair_matrix[char2_i][char2_j];
    }
        
    return new_text;
}


// -------------------

int playfair_matrix_build(char matrix[5][5], const char* key) {
    if(key == NULL)
        return -1;
    
    if(strlen(key) <= 0) 
        return -1;
    
    char* t_new_key = remove_character(key, ' ');
    strtoupper(t_new_key);
    replace_character(t_new_key, PLAYFAIR_REPLACED_CHAR, PLAYFAIR_REPLACEMENT_CHAR);
    char* new_key = remove_duplicate_characters(t_new_key);
    free(t_new_key);
    
    if(!isalpha_str(new_key)) 
        return -1;
    
    size_t key_len = strlen(new_key);
    
    for(size_t i=0; i<key_len; ++i) {
        matrix[i/5][i%5] = new_key[i];
    }
    
    char alphabet_char = 'A';
    for(size_t i=key_len; i<5*5; ++i) {
        while(strchr(new_key, alphabet_char) || alphabet_char == PLAYFAIR_REPLACED_CHAR) {
            if(alphabet_char < 'Z') 
                ++alphabet_char;
            else
                return -1;
        }
        matrix[i/5][i%5] = alphabet_char;
        ++alphabet_char;
    }
    
    return 0;
}


int playfair_matrix_locate_character(char matrix[5][5], char character, size_t* row_i, size_t* col_j) {
    for(size_t i=0; i<5; ++i) {
        for(size_t j=0; j<5; ++j) {
            if(character==matrix[i][j]) {
                *row_i = i;
                *col_j = j;
                return 1;
            }
        }
    }
    return 0;
}
