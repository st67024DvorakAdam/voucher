#include <stdio.h>

typedef struct voucher {
	int id;
	char lokalita[20];
	char poznamky[256];
	char code[10]; //xx-yyy-yyy
}tVoucher;

char* dejCode(char* prefix);

void ulozVoucher(tVoucher v);

void zpracujData(char* jmSoub);

