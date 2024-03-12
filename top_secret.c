#include "playfair.h"
#include "bmp.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

    {
        printf("------------------------------------------------\n");
        printf("PLAYFAIR\n");
        printf("------------------------------------------------\n");

        char *encrypted, *decrypted;

        // ----------
        
        printf("playfair_encrypt(\"SeCReT\", \"Hello world\")\n");
        
        // even length of string
        encrypted = playfair_encrypt("SeCReT", "Hello world");
        if(encrypted) printf("%s\n", encrypted);
        
        // "Hello world" --> "HELXLOVORLDX"
        // IS JZ JQ XN TK JC
        decrypted = playfair_decrypt("SeCReT", encrypted);
        if(decrypted) printf("%s\n", decrypted);
        // HELXLOVORLDX
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);

        // ----------

        printf("playfair_encrypt(\"world\", \"Hello\")\n");
        
        // odd length of string
        encrypted = playfair_encrypt("world", "Hello");
        if(encrypted) printf("%s\n", encrypted);
        // "Hello" --> "HELXLO"
        // JB RY DR
        decrypted = playfair_decrypt("world", encrypted);
        if(decrypted) printf("%s\n", decrypted);
        // HELXLO
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);

        // ----------
        
        printf("playfair_encrypt(\"Password\", \"Taxi please\")\n");

        // letter 'X' in message
        encrypted = playfair_encrypt("Password", "Taxi please");
        printf("%s\n", encrypted);
        // "Taxi please" --> "TAXIPLEASE"
        // UP YH AK DO OB
        decrypted = playfair_decrypt("Password", encrypted);
        printf("%s\n", decrypted);
        // TAXIPLEASE
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);

        // ----------
        
        printf("playfair_encrypt(\"please\", \"Taxxxiii\")\n");

        // multi 'X's in message
        encrypted = playfair_encrypt("please", "Taxxxiii");
        printf("%s\n", encrypted);
        // "Taxxxiii" --> "TAXXXIIXIX"
        // RS EE VJ JV JV
        decrypted = playfair_decrypt("please", encrypted);
        printf("%s\n", decrypted);
        // TAXXXIIXIX
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);
    }
    
    {
        printf("------------------------------------------------\n");
        printf("REVERSE\n");
        printf("------------------------------------------------\n");
        
        printf("reverse(\"Hello world!\")\n");
        
        char* encrypted = reverse("Hello world!");
        if(encrypted) printf("%s\n", encrypted);
        // "!DLROW OLLEH"
        char* decrypted = reverse(encrypted);
        if(decrypted) printf("%s\n", decrypted);
        
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);
        
    }
    
    {
        printf("------------------------------------------------\n");
        printf("VIGENERE\n");
        printf("------------------------------------------------\n");
        
        printf("vigenere_encrypt(\"CoMPuTeR\", \"Hello world!\")\n");
        
        char *encrypted, *decrypted;
                
        // basic test with long text
        encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");
        if(encrypted) printf("%s\n", encrypted);
        
        // "JSXAI PSINR!"
        decrypted = vigenere_decrypt("CoMPuTeR", encrypted);
        if(decrypted) printf("%s\n", decrypted);
        
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);
    }
    
    {
        printf("------------------------------------------------\n");
        printf("BIT CHAOS\n");
        printf("------------------------------------------------\n");
        
        printf("bit_encrypt(\"Hello world!\")\n");
        
        char *encrypted, *decrypted;

        // basic test with long text
        encrypted = bit_encrypt("Hello world!");
        if(encrypted) {
            for(int i=0; i < 12;i++) {
                printf("%x ", (unsigned char) encrypted[i]);
                //80 9c 95 95 96 11 bc 96 b9 95 9d 10
            }
            printf("\n");
        }
        decrypted = bit_decrypt(encrypted);
        if(decrypted) printf("%s\n", decrypted);
        
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);
    }
    
    {
        printf("------------------------------------------------\n");
        printf("BMP CIPHER\n");
        printf("------------------------------------------------\n");
        
        printf("bmp_encrypt(\"CoMPuTeR\", \"Hello world!\")\n");
        
        char *encrypted, *decrypted;
        // basic test with long text
        encrypted = bmp_encrypt("CoMPuTeR", "Hello world!");
        if(encrypted) {
            for(int i=0; i < 12;i++) {
                printf("%x ", (unsigned char) encrypted[i]);
            }
            printf("\n");
        }
        // "JSXAI PSINR!"
        decrypted = bmp_decrypt("CoMPuTeR", encrypted);
        if(decrypted) printf("%s\n", decrypted);
        
        if(encrypted) free(encrypted);
        if(decrypted) free(decrypted);
    }

    return 0;
}