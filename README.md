# Zadanie Jednotkové testy pre skupinu z oboru Počítačové modelovanie (pondelok 13:30 PK6_PC16)

## Podmienky
Vašou úlohou je napísať jednotkové testy pre program Top Secret (zadanie z predmetu programovanie pre študentov z oboru Informatika - [znenie zadania](http://it4kt.cnl.sk/c/pvjc/2018/problemset.02.top.secret.html)).

- Vytvorte aspoň **8 jednotkových testov primeranej zložitosti**.
- Otestujte aspoň **5 rôznych funkcií**.
- Doimplementujte a **otestujte** neimplementované funkcie
  <br> (označené komentárom `"TODO complete implementation of this function"`).
- Ak objavíte v implementácii chyby, môžete ich opraviť.

Študenti môžu vytvoriť vlastnú implementáciu programu Top Secret alebo použiť dodanú implementáciu, v ktorej je potrebné doplniť implementáciu vybraných funkcií.

## Odovzdávanie

- V **12\. týždni** bude kontrolovaná posledná verzia (posledný commit) vo vetve *master*.
- Odovzdávanie na Git (pridajte Michala Vrábla ako člena projektu - rola *reporter*)
  - Svoju verziu zadania si vytvorte ako kópiu tohoto repozitára do vlastného menného pristoru na serveri Gitlab pomocou tlačidla **fork** (rozvetvenie repozitára) vpravo hore na stránke repozitára.


*Nasledujúci popis funkcií bude pravdepodobne ešte priebežne vylaďovaný.*

## Modul Playfair

Princípom Playfairovej šifry (pozri [Playfair cipher na Wikipedii](https://en.wikipedia.org/wiki/Playfair_cipher)) je rozdelenie textu do dvojíc znakov. Ak sú obidva znaky dvojice:

- na rovnakom riadku matice 5x5, nahradia sa písmenami napravo od nich
  - (ak sa písmeno v matici nachádza v poslednom stĺpci, pre šifrovanie použite písmeno v prvom stĺpci riadku)
- v rovnakom stĺpci matice 5x5, nahradia sa písmenami pod nimi
  - (ak sa písmeno v matici nachádza v poslednom riadku, pre šifrovanie použite písmeno v prvom riadku stĺpca)
- na rozdielnych riadkoch a stĺpcoch matice 5x5, nahradia sa písmenami na priesečníkoch daných stĺpcov a riadkov
  - (použije sa riadok šifovaného písmena, a stĺpec druhého písmena páru)


- Funkcie
  - `char* playfair_encrypt(const char* key, const char* text)`  
    `char* playfair_decrypt(const char* key, const char* text)`
    - Funkcia vráti `NULL`, ak zašifrovanie  resp. odšifrovanie nebolo úspešné.
    - V prípade, že niektoré z pravidiel týkajúce sa vstupných parametrov bolo porušené alebo funkcia na vstupe dostane miesto ktoréhokoľvek parametra hodnotu `NULL`, funkcia hodnotu `NULL` aj vráti.
    - Parametre:
      - `const char* text` - Odkaz na reťazec, ktorý reprezentuje text na zašifrovanie.
        - Tento text môže pozostávať
          - len z písmen, pričom na veľkosti písmen nezáleží,
          - alebo zo znaku medzery.
          - Žiadne iné znaky nie sú prípustné (nie je možné ich zašifrovať).
        - **Pri šifrovaní** (`playfair_encrypt()`)
          - Jedno písmeno z abecedy, zameníme za iné (v našom prípade W za V)
          - Ak sa pred šifrovaním zistíte, že sú v texte dve po sebe idúce písmená rovnaké, medzi tieto dve písmená pridajte písmeno `'X'`.
          - Znak `'X'` sa nepridáva medzi 2 rovnaké znaky `'X'` a šifruje sa podľa stĺpca matice.
          - Ak je dĺžka tohto reťazca nepárna (po pridaní `'X'` medzi dvojité znaky a odstránení medzier), písmeno `'X'` pridajte aj na koniec vstupného textu.
        - **Pri dešifrovaní** (`playfair_decrypt()`)
            - výskyt znaku `'W'` pri vstupnom texte považuje za chybu a funkcia na dešifrovanie má v takomto prípade vrátiť `NULL`.
      - `const char* key` - Odkaz na reťazec, ktorý reprezentuje kľúč, pomocou ktorého bude text zašifrovaný.
        - Kľúč je reprezentovaný textom, v ktorom nezáleží na veľkosti písmen.
        - Reťazac môže obsahovať len male a veľké písmená abecedy a medzery.
        - Jednotlivé písmená sa v kľúči nemôžu opakovať.
          - Ak sa opakujú tak vo vašej implementácii zabezpečte, že duplikáty budú odstránené - ponecháva sa prvý výskyt písmena.
        - Medzery v kľúči sú ignorované.
        - Znaky sa nachádzajú sa na prvých miestach matice
          - (ak sa opakujú tak vo vašej implementácii zabezpečte, že duplikáty budú odstránené).
        - Jedno písmeno z abecedy, zameníme za iné (v našom prípade `W` za `V`)
- Príklad:
  - V prípade, že kľúč je `"belfast"`, matica 5x5 je rozdelená nasledovne (v našom prípade bol úmyselne vynechaný znak `'W'`):

```
B E L F A
S T C D G
H I J K M
N O P Q R
U V X Y Z
```

  - Ak s týmto kľúčom zašifrujeme slovo `KRYPTOGRAFIA`, výsledkom bude šifrovaný text `MQXQIVMZBAME`, pre `MANAGER` to bude `RGRBTAPZ`.

Použitie funkcie na zašifrovanie/dešifrovaonie sú ilustrované na nasledujúcich príkladoch:

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


### Modul BMP

#### Reverz
- `char* reverse(const char* text)`,
- vráti kópiu vstupného reťazca v obrátenom poradí (UPPERCASE).
- V prípade, že niektoré z pravidiel týkajúce sa vstupných parametrov bolo porušené alebo funkcia na vstupe dostane miesto ktoréhokoľvek parametra hodnotu `NULL`, funkcia hodnotu `NULL` aj vráti.

#### Vigenèrova šifra
- Predstavuje rozšírenie cézarovej šifry o kľúč, ktorý bude pri šifrovaní a dešifrovaní použitý.
- V cézarovej šifre je každé písmeno šifrovaného reťazca posunuté o nejaký počet miest v abecede. Napríkad ak je posun **3**, tak znak `A` je zašifrovaný ako znak `D`.
- Vigenerová šifra použiva tabuľku - Vigenerov štvorec - abeceda napísaná v 26 riadkoch, tak že v každom riadku je abeceda cyklicky posunútá o jeden krok doľava. ([Ukážka štvorca - Wikipédia](https://en.wikipedia.org/wiki/File:Vigen%C3%A8re_square_shading.svg))
- Funkcie
  - `char* vigenere_encrypt(const char* key, const char* text)`   
    `char* vigenere_decrypt(const char* key, const char* text)`
    - Výsledný text reprezentujte veľkými písmenami (UPPERCASE)
    - Funkcia vráti adresu kópie reťazca zašifrovanú resp. odšifrovanú pomocou Venierovej šifry
    - Funkcia vráti `NULL`, ak zašifrovanie  resp. odšifrovanie nebolo úspešné.
    - V prípade, že niektoré z pravidiel týkajúce sa vstupných parametrov bolo porušené alebo funkcia na vstupe dostane miesto ktoréhokoľvek parametra hodnotu `NULL`, funkcia hodnotu `NULL` aj vráti.
    - Význam jednotlivých parametrov funkcií je nasledovný:
      - `const char* key` - Reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu.
        - Kľúč je reprezentovaný ako jedno slovo a môže pozostávať len zo znakov abecedy.
        - Na veľkosti písmen nezáleží.
      - `const char* text` - Reťazec na zašifrovanie resp. odšifrovanie.
        - ~~Reťazac môže obsahovať len male a veľké písmená abecedy *(EXTRA PRAVIDLO)*.~~
- Príklad:

```c
char* encrypted;
// basic test with long text
encrypted = vigenere_encrypt("CoMPuTeR", "Hello world!");
printf("%s\n", encrypted);
// "JSXAI PSINR!"
```

#### Bitový chaos
- Znak, ktorý má byť zašifrovaný, si rozdeľte na polovicu (4 bity + 4 bity).
- Následne bity v prvej polovici rozdeľte do párov a ich hodnoty v páre navzájom vymeňte.
- Takto vytvorenú štvoricu bitov použite pre operáciu XOR nad zvyšnými 4 bitmi.
- Funkcie
  - `char* bit_encrypt(const char* text)`  
    `char* bit_decrypt(const char* text)`
    - V prípade, že funkcia na vstupe dostane miesto parametra hodnotu `NULL`, funkcia hodnotu `NULL` aj vráti.
- **Príklad - písmeno - 'H':**
  1. Písmeno 'H' má v ASCII tabuľke hodnotu 72. Hodnota 72 vyzerá v dvojkovej sústave nasledovne: `01001000`. Prvé 4 bity sú teda `0100` a druhé 4 bity sú `1000`.
  2. Prvá polovica bitov 0100 pozostáva z dvoch párov (`01` a `00`), v ktorých jednotlivé bity navzájom vymeníme (z páru 01 sa stane 10 a z páru `00` sa stane pár `00`). Tým dostaneme hodnotu `1000`.
  3. Takto upravenú podobu prvých štyroch bitov použijeme ako parameter operácie XOR spolu so zvyšnými štyrmi bitmi:

```
1000      // druhá polovica
1000 XOR  // prvá polovica po výmene bitov v dvojici
--------
0000
```
  - Spojením oboch získaných štvoríc bitov (prvá štvorica 1000, ktorú sme získali ako výsledok v 2. kroku a druhá štvorica 0000, ktorú sme získali ako výsledok v 3. kroku) dostaneme hodnotu 10000000, ktorá predstavuje zašifrovanú podobu písmena 'H' pomocou tejto metódy.

- Použitie tejto funkcie je ilustrované na nasledujúcom príklade:

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

#### Šifra BMP
- Ak chcete reťazec zašifrovať, postupujte nasledovne:
  1. vstupný reťazec najprv prežeňte funkciou `reverse()`
  2. získaný reťazec následne prežeňte funkciou `vigenere_encrypt()`
  3. výsledný reťazec ešte prežeňte funkciou `bit_encrypt()`
- Funkcie
  - `char* bmp_encrypt(const char* key, const char* text)`  
    `char* bmp_decrypt(const char* key, const char* text)`
    - Funkcia vráti `NULL`, ak zašifrovanie  resp. odšifrovanie nebolo úspešné.
    - Parametere
      - `const char* key` - Reťazec reprezentujúci kľúč použitý na zašifrovanie aj odšifrovanie textu, odovzdaný funkcii `vigenere_encrypt()`.
        - Kľúč môže pozostávať len zo znakov, pričom na veľkosti nezáleží.
        - Rovnaké požiadavky ako pri funkcii `vigenere_encrypt()`.
      - `const char* text` - Reťazec na zašifrovanie resp. odšifrovanie.
      - Rovnaké požiadavky ako pri funkcii `reverse()`.
