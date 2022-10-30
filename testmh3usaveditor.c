#include <stdio.h>
#include "mh3usaveditor.h"

int main()
{
	int test, i, rien;
	FILE *fr;
	fr = fopen("testhex","r");
	if (fr == NULL)
	{
		printf("Fichier introuvable");
	}
	fscanf(fr,"%X",&test);
	printf("%d | %X \n",test,test);
	return 0;
}