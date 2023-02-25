/*
	
*/

typedef struct{
	unsigned short itemID;
	unsigned short nbItem;
}Item;

typedef struct{
	unsigned short itemID;
	char name[50];
}ItemID;

int menu (void);

/*
	Affiche les options
*/

int choix (void);


unsigned int endianSwap(unsigned int nb);

void test (void);

int chargeItemId(ItemID *tab[]);

void affichage (ItemID *tab[], Item *coffre[]);

char* recherche(ItemID *tab[], unsigned int itemID);

int chargeCoffre(Item *coffre[]);

void afficheItemId(ItemID *tab[]);