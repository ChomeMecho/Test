#ifndef UTILS_H
#define UTILS_H

int isalpha_str(const char* text);
char* remove_duplicate_characters(const char* str);
char* remove_character(const char* str, char removed_char);
char* separate_duplicate_characters(const char* str, char separator);
char* expand_to_even_length(const char* str, char expand_char);
void replace_character(char* str, char find, char replace);
void strtoupper(char* str);

#endif /* UTILS_H */