#include <stdio.h>
#include "mh3usaveditor.h"

void test (void)
{
	int test, i, rien;
	unsigned short test2;
	FILE *fr;
	fr = fopen("user1","rb");
	if (fr == NULL)
	{
		printf("Fichier introuvable");
	}
	fseek(fr,432,SEEK_SET);
	fread(&test2,sizeof(int),1,fr);
	test2 = endianSwap(test2);
	printf("%d | %X \n",test2,test2);
}

int main(void)
{
	menu();
	return 0;
}