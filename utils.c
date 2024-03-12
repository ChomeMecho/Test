#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


int isalpha_str(const char* text) {
    for (size_t i = 0; i < strlen(text); i++) {
        if(!isalpha(text[i])) 
            return 0;
    }
    return 1;
}


char* remove_duplicate_characters(const char* str) {
    if(str == NULL)
        return NULL;
    
    size_t str_len = strlen(str);
    char* new_str = calloc(str_len + 1, sizeof(char));
    // calloc - The effective result is the allocation of a zero-initialized memory block of (num*size) bytes.

    if(str_len == 0) 
        return new_str;
    
    new_str[0]=str[0];
    
    size_t j=1;
    
    for(size_t i=1; i<str_len; ++i) {
        int cont = 0;
        for(size_t k=1; k<=j; ++k) {
            if(str[i] == new_str[j-k]) {
                cont=1;
            }
        }
        if(cont){
            continue;
        }
        new_str[j] = str[i];
        ++j;
    }
            
    if(j < str_len) {
        char* tmp_str = new_str;
        new_str = calloc(j+1, sizeof(char));
        memcpy(new_str, tmp_str, j);
        free(tmp_str);
    }
    
    return new_str;
}


char* remove_character(const char* str, char removed_char) {
    if(str == NULL)
        return NULL;
    
    size_t str_len = strlen(str);
    char* new_str = calloc(str_len + 1, sizeof(char));
    // calloc - The effective result is the allocation of a zero-initialized memory block of (num*size) bytes.

    if(str_len == 0) 
        return new_str;
    
    size_t j=0;
    
    for(size_t i=0; i<str_len; ++i) {
        if(str[i] == removed_char) 
            continue;
        new_str[j] = str[i];
        ++j;
    }
        
    if(j < str_len) {
        char* tmp_str = new_str;
        new_str = calloc(j+1, sizeof(char));
        memcpy(new_str, tmp_str, j);
        free(tmp_str);
    }
    
    return new_str;
}


char* separate_duplicate_characters(const char* str, char separator) {
    if(str == NULL)
        return NULL;
    
    size_t str_len = strlen(str);
    char* new_str = calloc(2*str_len + 1, sizeof(char));
    // calloc - The effective result is the allocation of a zero-initialized memory block of (num*size) bytes.

    if(str_len == 0) 
        return new_str;
    
    new_str[0]=str[0];
    
    size_t j=1;
    
    for(size_t i=1; i<str_len; ++i) {
        if(str[i] == new_str[j-1] && str[j-1] != separator) {
            new_str[j] = separator;
            ++j;
        }
        new_str[j] = str[i];
        ++j;
    }
            
    if(j < str_len) {
        char* tmp_str = new_str;
        new_str = calloc(j+1, sizeof(char));
        memcpy(new_str, tmp_str, j);
        free(tmp_str);
    }
    
    return new_str;
}


char* expand_to_even_length(const char* str, char expand_char) {
    size_t str_len = strlen(str);
    
    if(str_len % 2 != 0) {
        char* new_str = calloc(str_len + 2, sizeof(char));
        memcpy(new_str, str, str_len);
        new_str[str_len] = expand_char;
        return new_str;
    }
    return NULL;
}


void replace_character(char* str, char find, char replace) {
    if(str == NULL)
        return;
    
    char *current_pos = strchr(str,find);
    while (current_pos){
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
}


void strtoupper(char* str) {
    if(str == NULL)
        return;
    
    size_t str_len = strlen(str);
    for(size_t i=0; i<str_len; ++i) {
        str[i] = toupper(str[i]);
    }
}
