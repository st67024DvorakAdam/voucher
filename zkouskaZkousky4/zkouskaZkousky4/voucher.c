#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voucher.h"
#include <time.h>


char* dejCode(char* prefix){
    char xx[3];
    strncpy(xx, prefix, 2);
    xx[2] = '\0';

    srand(time(NULL));

    char yyy1[4];
    for (int i = 0; i < 3; i++) {
        yyy1[i] = 'a' + rand() % 26; // Generování písmene 'a'-'z'
    }
    yyy1[3] = '\0';


    char yyy2[4];
    for (int i = 0; i < 3; i++) {
        yyy2[i] = 'a' + rand() % 26;
    }
    yyy2[3] = '\0';

  
    char* result = (char*)malloc(11* sizeof(char)); 
    sprintf(result, "%s-%s-%s", xx, yyy1, yyy2);

    return result;
}

void ulozVoucher(tVoucher v) {
    char jmSoub[7];
    strncpy(jmSoub, v.code, 2);
    jmSoub[2] = '.';
    jmSoub[3] = 'c';
    jmSoub[4] = 's';
    jmSoub[5] = 'v';
    jmSoub[6] = '\0';

    FILE* file = fopen(jmSoub, "a"); // Otevøení souboru pro pøidání dat
    if (file == NULL) {
        file = fopen(jmSoub, "w"); // Vytvoøení nového souboru
        if (file == NULL) {
            printf("Chyba pøi vytváøení souboru.\n");
            return;
        }
    }

    fprintf(file, "%d;%s;%s;%s\n", v.id, v.code, v.lokalita, v.poznamky);
    fclose(file);
}

void zpracujData(char* jmSoub) {
    FILE* file = fopen(jmSoub, "r");
    if (file == NULL) {
        perror("Soubor nelze otevrit");
        exit(1);
    }
    char line[1024];
    while (fgets(line, 1024, file) != NULL) {
        tVoucher v;
        char prefix[3];
        char* token = strtok(line, ";");
        v.id = (int)strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        strncpy(prefix, token, 2);
        prefix[2] = '\0';
        char* code = dejCode(prefix);
        strncpy(v.code, code, 10);
        v.code[10] = '\0';

        token = strtok(NULL, ";");
        strncpy(v.lokalita, token, 20);

        token = strtok(NULL, ";");
        strncpy(v.poznamky, token, 256);

        ulozVoucher(v);

        free(code); // Uvolnìní pamìti po použití
    }
    fclose(file);
}