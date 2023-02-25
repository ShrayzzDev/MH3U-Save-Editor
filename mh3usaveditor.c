#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mh3usaveditor.h"

unsigned int endianSwap(unsigned int nb)
{
	return (nb>>8) | (nb<<8);
}

int chargeCoffre(Item *coffre[])
{
	FILE *fr;
	int i, valInter, valInter2;
	fr = fopen("user1","rb");
	if (fr == NULL)
	{
		printf("Fichier introuvable");
		exit;
	}
	fseek(fr,432,SEEK_SET);
	printf("on sait jamais\n");
	for (i = 0; i < 996; i++)
	{
		coffre[i] = (Item *)malloc(sizeof(Item));
		fread(&valInter,sizeof(int)/2,1,fr);
		coffre[i]->itemID = endianSwap(valInter);	
		fread(&valInter2,sizeof(int)/2,1,fr);
		coffre[i]->nbItem = endianSwap(valInter2);
	}
	fclose (fr);
}

int chargeItemId(ItemID *tab[])
{
	FILE *fr;
	int i;
	fr = fopen("item ids","r");
	if (fr == NULL)
	{
		printf("Fichier id item introuvable");
		exit;
	}
	for (i = 0; i < 1532; i++)
	{
		tab[i] = (ItemID *)malloc(sizeof(ItemID));
		fscanf(fr,"%hhd",&tab[i]->itemID);
		fgets(tab[i]->name,50,fr);
		tab[i]->name[strlen(tab[i]->name)-1] = '\0';
	}
	fclose(fr);
}

void afficheItemId(ItemID *tab[])
{
	int i;
	for (i = 0; i < 1532; i++)
		printf("%hd %s\n",tab[i]->itemID,tab[i]->name);
}

void affichage (ItemID *tab[], Item *coffre[])
{
	int i;
	char *nomItem;
	printf("Nom:\tNombre:\n");
	for (i = 0; i < 996; i++)
	{
		nomItem = recherche(tab,coffre[i]->itemID);
		printf("%s %d\n",nomItem,coffre[i]->nbItem);
		printf("%X %d\n",coffre[i]->itemID,)
	}
}

char* recherche(ItemID *tab[], unsigned int itemID)
{
	int i;
	for (i = 0; i < 1532; i++)
		if (itemID == tab[i]->itemID)
			return tab[i]->name;
}

int menu (void)
{
	int choix = 0;
	Item *coffre[996];
	printf("test1\n");
	chargeCoffre(coffre);
	printf("test1\n");
	ItemID *correspondre[1532];
	chargeItemId(correspondre);
	printf("test1\n");
	while (choix != 9)
	{	
		printf("---------------------------------\n");
		printf("|       MH3U Save Editor	|\n");
		printf("|				|\n");
		printf("|	1. Edit Zenny count	|\n");
		printf("|	2. Affichage		|\n");
		printf("|				|\n");
		printf("|				|\n");
		printf("|				|\n");
		printf("|				|\n");
		printf("|				|\n");
		printf("|				|\n");
		printf("---------------------------------\n");
		printf("Quel est votre choix ?\n");
		scanf("%d",&choix);
		if (choix == 1)
			printf("change les zenny (pas encore fait)");
		if (choix == 2)
			affichage(correspondre,coffre);
		if (choix != 1 && choix != 2)
			{printf("Fermeture du logiciel\n");exit;}
	}
}
