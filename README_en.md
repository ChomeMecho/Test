# Assignment - Unit testing

## Requirements
Your task is to implement unit tests of a program / library called "Top secret".

- Implement at least **8 unit tests of appropriate complexity**.
- Create unit tests for at least **5 different functions**.
- Finish implementation and **test** presently non-implemented functions  
(marked by a comment `"TODO complete implementation of this function"`).
- You are welcome to find and fix any bugs in the code.
- You can create your own implementation of these cryptographic functions.

## Handing in of the assignment

- The assignments should be handed in during the **8th week** - In the 8th week the last commit in branch *master* will be considered as the final version of the assignment and it will be graded.
- Hand in your assignments to faculty's Git (add Michal Vrábel as a member of your project - role *reporter*)
  - Create your version of the assignment by copying the project into your namespace on the Gitlab server using the button **fork**.
  Address of the project is https://git.kpi.fei.tuke.sk/mv120fd/top_secret_for_fse


## Module Playfair

The principle of the Playfair cipher (see [Playfair cipher on Wikipedia](https://en.wikipedia.org/wiki/Playfair_cipher)) is splitting of the text into pairs. Then following rules are applied to encrypt every pair:

1. If both letters are the same (or only one letter is left), add an "X" after the first letter. Encrypt the new pair and continue. Some variants of Playfair use "Q" instead of "X", but any letter, itself uncommon as a repeated pair, will do.
2. If the letters appear on the same row of your table, replace them with the letters to their immediate right respectively (wrapping around to the left side of the row if a letter in the original pair was on the right side of the row).
3. If the letters appear on the same column of your table, replace them with the letters immediately below respectively (wrapping around to the top side of the column if a letter in the original pair was on the bottom side of the column).
4. If the letters are not on the same row or column, replace them with the letters on the same row respectively but at the other pair of corners of the rectangle defined by the original pair. The order is important – the first letter of the encrypted pair is the one that lies on the same row as the first letter of the plaintext pair.


- Functions:
  - `char* playfair_encrypt(const char* key, const char* text)`  
    `char* playfair_decrypt(const char* key, const char* text)`
    - Functions return `NULL` if encryption or decryption are unsuccessful.
    - In case that any rule regarding input parameters is violated or the function is given `NULL` as a parameter value, the function returns `NULL`.
    - Parameters:
      - `const char* text` - C string representing text to by encrypted.
        - It can only consists of letters the English alphabet or spaces. The letters can be both lowercase and UPPERCASE.
        - **When encrypting** (`playfair_encrypt()`)
          - One letter of the alphabet is replaced by an another - in our case `W` is replaced by `V`.
          - If there are repeating letters, such pairs are broken by inserting a letter `'X'` between the letters.
          - If there are repeating letters `'X'`, an additional letter `'X'` is not added.
          - If length of the text is odd (afrer adding `'X'` and removing spaces), letter `'X'` is added to the end of the string.
        - **When decrypting** (`playfair_decrypt()`)
            - An occurrence of `'W'` character in the input text is considered an error and the function should return `NULL`.
      - `const char* key` - String representing a key used for the encryption or decryption.
        - Represented by letters of the English alphabet - lowercase and UPPERCASE letters.
        - Letters in the key cannot be repeated
          - If there are duplicate letters, the duplicates should be removed preserving only the first occurrence of the letter.
        - Spaces in the key are ignored.
        - The letters are placed into beginning of the Playfair matrix.
        - One letter of the alphabet is replaced by an another  - in our case `W` is replaced by `V`
- Example:
  - If key is `"belfast"`, the 5x5 Playfair matix looks following (in our case letter `'W'` has been excluded):

```
B E L F A
S T C D G
H I J K M
N O P Q R
U V X Y Z
```

  - Using this key the word `KRYPTOGRAFIA` is ciphered into `MQXQIVMZBAME`, and the word  `MANAGER` is `RGRBTAPZ`.

Usage of the described playfair encryption and decryption functions:

```c
char *encrypted, *decrypted;

// even length of string
encrypted = playfair_encrypt("SeCReT", "Hello world");
printf("%s", encrypted);
// "Hello world" --> "HELXLOVORLDX"
// IS JZ JQ XN TK JC
decrypted = playfair_decrypt("SeCReT", encrypted);
printf("%s", decrypted);
// HELXLOVORLDX
free(encrypted);
free(decrypted);

// odd length of string
encrypted = playfair_encrypt("world", "Hello");
printf("%s", encrypted);
// "Hello" --> "HELXLO"
// JB RY DR
decrypted = playfair_decrypt("world", encrypted);
printf("%s", decrypted);
// HELXLO
free(encrypted);
free(decrypted);

// letter 'X' in message
encrypted = playfair_encrypt("Password", "Taxi please");
printf("%s", encrypted);
// "Taxi please" --> "TAXIPLEASE"
// UP YH AK DO OB
decrypted = playfair_decrypt("Password", encrypted);
printf("%s", decrypted);
// TAXIPLEASE
free(encrypted);
free(decrypted);

// multi 'X's in message
encrypted = playfair_encrypt("please", "Taxxxiii");
printf("%s", encrypted);
// "Taxxxiii" --> "TAXXXIIXIX"
// RS EE VJ JV JV
decrypted = playfair_decrypt("please", encrypted);
printf("%s", decrypted);
// TAXXXIIXIX
free(encrypted);
free(decrypted);
```


### Module BMP

#### Reverse
- `char* reverse(const char* text)`,
- Returns a copy of given string in reversed order and UPPERCASE.
- In case that any rule regarding input parameters is violated or the function is given `NULL` as a parameter value, the function returns `NULL`.

#### Vignere cipher
- See description of [the Vignere cipher on Wikipedia](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher).
- It is an extension of the Caesar cipher by adding a key used for encryption and decryption.
- In the Caesar cipher every letter is shifted by a constant number of letters in a alphabet - e.g. if shift is 3, then a letter `'A'` is ciphered a letter `'D'`.
- Vigenere cipher uses a table - Vigenère square - It consists of the alphabet written out 26 times in different rows, each alphabet shifted cyclically to the left compared to the previous alphabet, corresponding to the 26 possible Caesar ciphers. ([The Vigenère square on Wikipédia](https://en.wikipedia.org/wiki/File:Vigen%C3%A8re_square_shading.svg))
- Functions
  - `char* vigenere_encrypt(const char* key, const char* text)`   
    `char* vigenere_decrypt(const char* key, const char* text)`
    - Resulting text is in the UPPERCASE.
    - The function returns encrypted or decrypted copy of the input text.
    - Function returns `NULL` if encryption or decryption is unsuccessful.
    - In case that any rule regarding input parameters is violated or the function is given `NULL` as a parameter value, the function returns `NULL`.
    - parameters:
      - `const char* key` - String representing a key for encryption or decryption.
        - It can consist only of English alphabet letters.
        - The letters can be both lowercase and UPPERCASE.
      - `const char* text` - Encrypted or decrypted text.
        - ~~It can consist only of English alphabet letters.~~
        - The letters can be both lowercase and UPPERCASE.
- Example:

```c
char* encrypted;
// basic test with long text
encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");
printf("%s\n", encrypted);
// "JSXAI PSINR!"
```

#### Bit chaos
- Encrypted character bits are split into 2 parts (left and right) of 4 bits (size of char is 8 bits).
- The 4-bit group on the left is split once again into two parts of 2 bits. And bits within the each pair are swapped.
- The modified 4-bit group from the left side is used in a XOR operation with the 4-bits from the right side.
- Funkcie
  - `char* bit_encrypt(const char* text)`  
    `char* bit_decrypt(const char* text)`
    - If input parameter is `NULL`, the function returns `NULL`.
- **Example - letter 'H':**
  1. Letter 'H' has code `72` in the ASCII table. `72` in binary is `01001000`. The left four bits are `0100` and the right four bits are `1000`.
  2. The left four bits `0100` consist of two pairs (`01` and `00`). The bits in the each pair are swapped (`01` becomes `10`, and `00` becomes `00`). The final value of the left four bits is `1000`.
  3. The modified value of the left four bits `1000` is used in XOR operation with the right four bits:

```
1000      // right four bits
1000 XOR  // modified left four bits
--------
0000
```
  - The resulting encrypted value is constructed by joining of the two groups - modified left four bits `1000` from the step 2, and modified right four bits `0000` from the step 3. Thus, the resulting encrypted value of the letter `H` is `10000000`.

- Code example:

```c
char* encrypted;
// basic test with long text
encrypted = bit_encrypt("Hello world!");
for(int i=0; i < 12;i++) {
    printf("%x ", (unsigned char) encrypted[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
}
free(encrypted);
```

#### Cipher BMP
- The BMP cipher is combination of the previously described ciphers:
  1. an input text is reversed by the function `reverse()`
  2. then the reversed text is encrypted by the function `vigenere_encrypt()`
  3. finally the reversed and encrypted text is encrypted again by the function `bit_encrypt()`
- Functions
  - `char* bmp_encrypt(const char* key, const char* text)`  
    `char* bmp_decrypt(const char* key, const char* text)`
    - Return `NULL` if encryption or decryption is unsuccessful.
    - Parameters
      - `const char* key` - Key used for encryption and decryption, it is passed to the function `vigenere_encrypt()`.
        - All the requirements on the key from the function `vigenere_encrypt()` apply.
      - `const char* text` - Encrypted or decrypted string.
        - All the requirements on the key from the function `reverse()` apply.
