/*************************************************************
 * @file   main.c                                            *
 * @author Papaioannou Antonis 						  	     *
 *                                                    	     *
 * @brief  Source file for the needs of CS-240b project 2018 *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Shopping.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

 /* Uncomment the following line to enable debugging prints
  * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

void PrintTreeShops(struct Shop *root) {/*kanei print ta shops xwris to X kai to DONE wste na thn xrhsimopoihsw kai se alla events*/
	if (root == shopSentinel) return;
	PrintTreeShops(root->lc);
	counter++;
	printf("\tShop%d=",counter);
	struct Product *tempProduct = root->products;
	if (tempProduct == NULL) {
		printf("\n");
		PrintTreeShops(root->rc);
		return; /*ean den exei kanena proion*/
	}
	while (tempProduct->next != NULL) {
		printf("<%d,%d,%d> ", tempProduct->pid, tempProduct->qty, tempProduct->price);
		tempProduct = tempProduct->next;
	}
	printf("<%d,%d,%d>\n", tempProduct->pid, tempProduct->qty, tempProduct->price);/*kai gia to teleutaio proion*/
	PrintTreeShops(root->rc);
}

  /**
   * @brief Print shops
   *
   * @return 1 on success
   *         0 on failure
   */

int PrintShops(void)
{
	struct Shop *temproot = shopRoot;
	if (shopRoot == shopSentinel) return 0;/*den uparxei kanena shop*/
	printf("X\n");
	PrintTreeShops(temproot);
	printf("DONE\n");
	return 1;
}

void PrintCustomerTree(struct C_Product *root) {/*kanei print to tree tou kathe customer me inorder*/
	if (root == NULL) return;
	PrintCustomerTree(root->lc);
	printf("<%d,%d> ",root->pid,root->qty );
	PrintCustomerTree(root->rc);
}

void PrintCustomersClear() {/*kanei print ta customers xwris to Y kai to DONE wste na thn xrhsimopoihsw kai se alla events*/
	int i = 1;
	int j;
	for (j = 0; j < size; j++) {
		if (customers_hash[j] != NULL) {
			printf("\tCustomer%d=", i++);
			PrintCustomerTree(customers_hash[j]->shopping_tree);
			printf("\n");
		}
	}

}
/**
 * @brief Print customers
 *
 * @return 1 on success
 *         0 on failure
 */
int PrintCustomers(void)
{
	printf("Y\n");
	PrintCustomersClear();
	printf("DONE\n");
	return 1;
}

  /**
   * @brief Optional function to initialize data structures that
   *        need initialization
   *
   * @return 1 on success
   *         0 on failure
   */
int Initialize(void)
{
	int i = 0;
	counter = 0;
	ShopTypes[4] = ShopTypes[3] = ShopTypes[2] = ShopTypes[1] = ShopTypes[0] = NULL;/*arxikopoihsh shopTypes pinaka*/
	shopRoot = (struct Shop*)malloc(sizeof(struct Shop)); /*Shop list header initialization*/
	if (shopRoot == NULL) return 0;
	shopRoot->lc = shopRoot->rc  = NULL;/*arxikopoihsh Shop tree*/
	shopRoot->products = NULL;
	shopRoot->sid = shopRoot->type = -1;
	shopSentinel = shopRoot;
	/*parakatw ftiaxnw ton hash table*/
	int tempsize = 1.5*max_customers_g;/* ena statistika arketa grhgoro megethos table.*/
	while (1) {
		if (primes_g[i] > tempsize) break;
		i++;
	}
	
	size = primes_g[i];/*to megethos einai to prwtos prime arithmos megaluteros tou tempsize*/
	customers_hash = (struct Customer**)malloc(size*sizeof(struct Customer*)); /*desmeush mnhmhs tou hashtable*/
	if (customers_hash == NULL) return 0;
	for (i = 0; i < size; i++) {/*arxikopoihsh hashtable*/
		customers_hash[i] = NULL;
	}	
		i = 0;
	while (1) {/*me ton idio tropo vriskw enan prime*/
		if (primes_g[i] > tempsize/2) break;
		i++;
	}
	
	prime = primes_g[i];

	/*apo edw kai katw gia to categorize*/
	shopRootType1 = (struct Shop*)malloc(sizeof(struct Shop)); /*Shop list header initialization*/
	if (shopRootType1 == NULL) return 0;
	shopRootType2 = (struct Shop*)malloc(sizeof(struct Shop)); /*Shop list header initialization*/
	if (shopRootType2 == NULL) return 0;
	shopRootType3 = (struct Shop*)malloc(sizeof(struct Shop)); /*Shop list header initialization*/
	if (shopRootType3 == NULL) return 0;
	shopRootType4 = (struct Shop*)malloc(sizeof(struct Shop)); /*Shop list header initialization*/
	if (shopRootType4 == NULL) return 0;
	shopRootType5 = (struct Shop*)malloc(sizeof(struct Shop)); /*Shop list header initialization*/
	if (shopRootType5 == NULL) return 0;
	shopRootType1->lc = shopRootType1->rc = NULL;
	shopRootType1->products = NULL;
	shopRootType1->sid = shopRootType1->type= -1;
	Sentinel1 = shopRootType1;
	shopRootType2->lc = shopRootType2->rc  = NULL;
	shopRootType2->products = NULL;
	shopRootType2->sid = shopRootType2->type = -1;
	Sentinel2 = shopRootType2;
	shopRootType3->lc = shopRootType3->rc  = NULL;
	shopRootType3->products = NULL;
	shopRootType3->sid = shopRootType3->type = -1;
	Sentinel3 = shopRootType3;
	shopRootType4->lc = shopRootType4->rc =  NULL;
	shopRootType4->products = NULL;
	shopRootType4->sid = shopRootType4->type = -1;
	Sentinel4 = shopRootType4;
	shopRootType5->lc = shopRootType5->rc = NULL;
	shopRootType5->products = NULL;
	shopRootType5->sid = shopRootType5->type = -1;
	Sentinel5 = shopRootType5;
	return 1;
}



struct Shop* insert(struct Shop* root, int sid,int type)
{
	/* If the tree is empty, return a new node */
	if (root == shopSentinel) {
		struct Shop *temp= (struct Shop*)malloc(sizeof(struct Shop));
		if (temp == NULL) return NULL;
		temp->lc = temp->rc = shopSentinel;
		temp->products = NULL;
		temp->sid = sid;
		temp->type = type;
		return temp;
	}

	/* Otherwise, recur down the tree */
	if (sid < root->sid) root->lc = insert(root->lc,sid,type);
	else if (sid> root->sid) root->rc = insert(root->rc, sid,type);

	/* return the (unchanged) node pointer */
	return root;
}

void printRegisterShops(struct Shop *root) {
	
	if (root == shopSentinel) return;
	printRegisterShops(root->lc);
	printf("<%d,%d> ", root->sid, root->type);	
	printRegisterShops(root->rc);
	
}
/**
 * @brief Register shop
 *
 * @param sid   The shop's id
 * @param type  The shop's type
 *
 * @return 1 on success
 *         0 on failure
 */
int RegisterShop(int sid, int type)
{
	shopRoot = insert(shopRoot, sid, type);
	printf("R <sid> <type>\n\tShops=");
	printRegisterShops(shopRoot);
	if (shopRoot == NULL) return 0;/*error se periptwsh pou den dulepsei h malloc*/
	printf("\nDONE\n");
	return 1;
}

struct Shop* search(struct Shop* root, int sid)
{
	
	if (root->sid == sid) return root;

	if (root->sid < sid) return search(root->rc, sid);

	return search(root->lc, sid);
}
/**
 * @brief Supply shop
 *
 * @param sid       The shop's id
 * @param pid       The product's id
 * @param quantity  The product's quantity
 * @param price     The product's price
 *
 * @return 1 on success
 *         0 on failure
 */
int SupplyShop(int sid, int pid, int quantity, int price)
{
	/*epeidh den anaferete sthn ekfwnhsh, thn periptwsh pou uparxei hdh to proion sth lista 
	thn antimetwpizw kratwntas thn timh tou paliou kai prosthetontas tis posothtes*/
	struct Product *new_product = (struct Product*)malloc(sizeof(struct Product)); 
	if (shopRoot == NULL) return 0;
	new_product->pid = pid;
	new_product->price = price;
	new_product->qty = quantity;
	shopSentinel->sid = sid;/*arxikopoiw ton frouro gia na kanw thn anazhthsh*/
	struct Shop *temp = search(shopRoot, sid);/*psaxnw me thn search to katasthma*/
	if (temp == shopSentinel) return 0;/*an den uparxei to katasthma sid*/
	struct Product *pp = temp->products;
	if (pp == NULL) {/*an einai adia h lista */
		new_product->next = NULL;
		temp->products = new_product;
	}
	else {
		while ((pp->next != NULL) && (pp->next->pid < pid)) {
			pp = pp->next;
		}

		if (pp->next == NULL) {
			if (pp == temp->products) {
				if (pp->pid == pid) {
					pp->qty = pp->qty + quantity;
				}
				else if (pid < pp->pid) {
					new_product->next = pp;
					temp->products = new_product;
				}
				else {
					new_product->next = NULL;
					pp->next = new_product;
				}
			}
		}
		else {

			if (pp == temp->products) {
				if (pp->pid == pid) {
					pp->qty = pp->qty + quantity;
				}
				else if (pid < pp->pid) {
					new_product->next = pp;
					temp->products = new_product;
				}
				else if (pp->next->pid == pid) {/*an uparxei hdh to proion apla prosthetei tis posothtes*/
					pp->next->qty = pp->next->qty + quantity;
				}
				else {
					new_product->next = pp->next;
					pp->next = new_product;
				}
			}
			else {

				if (pp->next->pid == pid) {/*an uparxei hdh to proion apla prosthetei tis posothtes*/
					pp->next->qty = pp->next->qty + quantity;
				}
				else {
					new_product->next = pp->next;
					pp->next = new_product;
				}
			}
		}
	}
	printf("S <sid>	<pid> <quantity> <price>\n");
	PrintTreeShops(shopRoot);
	counter = 0;/*gia na 3anaxrhsimopoihsw ton counter*/
	printf("DONE\n");


	return 1;
}

/**
 * @brief Register customer
 *
 * @param cid The customer's id
 *
 * @return 1 on success
 *         0 on failure
 */
int RegisterCustomer(int cid)
{
	int i,newIndex;
	struct Customer *new_customer = (struct Customer*)malloc(sizeof(struct Customer));
	if (new_customer == NULL) return 0;
	new_customer->cid = cid;
	new_customer->shopping_size = 0;
	new_customer->shopping_tree = NULL;
	/*
	int index1 = cid % size;
	if (customers_hash[index1] != NULL) {/*edw uparxei sugkroush 
		int index2 = prime - (cid%prime);
		i = 1;
		while (1) {/*mexri na vrei kenh thesh 
			int newIndex = (index1 + i * index2) % size;
			if (customers_hash[newIndex] == NULL) {
				customers_hash[newIndex] = new_customer;
				break;
			}
			i++;
		}
	}
	else customers_hash[index1] = new_customer;
	*/
	int index1 = cid % size;
	int index2 = prime - (cid%prime);
	for (i = 0; i < size; i++) {
		newIndex = (index1 + i * index2) % size;
		if (customers_hash[newIndex] == NULL) {
			customers_hash[newIndex] = new_customer;
			break;
		}
	}
	

	printf("C <cid>\n\tCustomers=");
	for (i = 0; i < size; i++) {
		if (customers_hash[i] != NULL) {
			printf("<%d> ", customers_hash[i]->cid);
		}
	}
	printf("\nDONE\n");
	return 1;
}


int searchCidIndexOld(int cid) {/*psaxnw to index sto opoio einai o customer cid*/
	
	int index1 = cid % size;
	if (customers_hash[index1] == NULL) return -1;/*an den uparxei*/
	if (customers_hash[index1]->cid == cid) return index1;
	int i = 1;
	int index2 = prime - (cid%prime);
	while (1) {

		int newIndex = (index1 + i * index2) % size;
		if (customers_hash[newIndex] == NULL) return -1;/*an den uparxei*/
		if (customers_hash[newIndex]->cid == cid) return newIndex;
		i++;
	}
	
}

int searchCidIndex(int cid) {
	int i;
	int index1 = cid % size;
	int index2 = prime - (cid%prime);
	for(i=0;i<size;i++){

		int newIndex = (index1 + i * index2) % size;
		if (customers_hash[newIndex] == NULL) return -1;
		if (customers_hash[newIndex]->cid == cid) return newIndex;
	}
}




struct C_Product* insertProduct(struct C_Product* root, int pid,int quantity)
{
	if (root == NULL) {
		struct C_Product *temp = (struct C_Product*)malloc(sizeof(struct C_Product));
		temp->lc = temp->rc = NULL;
		temp->pid = pid;
		temp->qty = quantity;
		return temp;
	}

	if (pid < root->pid) root->lc = insertProduct(root->lc, pid, quantity);
	else if (pid > root->pid) root->rc = insertProduct(root->rc, pid, quantity);

	return root;
}

/**
 * @brief Add to shopping list
 *
 * @param cid       The customer's id
 * @param pid       The product's id
 * @param quantity  The quantity of the product
 *
 * @return 1 on success
 *         0 on failure
 */
int AddToShoppingList(int cid, int pid, int quantity)
{
	int index=searchCidIndex(cid);
	if (index == -1||index >size-1)	return 0;
	customers_hash[index]->shopping_tree = insertProduct(customers_hash[index]->shopping_tree, pid, quantity);
	customers_hash[index]->shopping_size++;
	printf("L <cid>	<pid> <quantity>\n");
	PrintCustomersClear();
	printf("DONE\n");
	return 1;
}

struct C_Product *DeleteProduct(struct C_Product *root, int pid) {

	if (root == NULL) return root;

	if (root->pid==pid){
		/* komvos me ena h kanena paidi */
		if (root->lc == NULL)
		{
			struct C_Product *temp = root->rc;
			
			return temp;
		}
		else if (root->rc == NULL)
		{
			struct C_Product *temp = root->lc;
			
			return temp;
		}

		/*duo paidia ara vriskw ton epomeno sthn inorder */
		struct C_Product* temp=root->rc;
		while (temp && temp->lc != NULL)
			temp = temp->lc;

		/*antigrafw ta stoixeia tou  kai ton diagrafw*/
		root->pid= temp->pid;
		root->qty = temp->qty;
		root->rc = DeleteProduct(root->rc, temp->pid);
	}
	else if (root->pid<pid) root->rc = DeleteProduct(root->rc, pid);

	else root->lc = DeleteProduct(root->lc,pid);

	return root;
}
/**
 * @brief Delete from shopping list
 *
 * @param cid  The customer's id
 * @param pid  The product's id
 *
 * @return 1 on success
 *         0 on failure
 */
int DeleteFromShoppingList(int cid, int pid)
{
	int index = searchCidIndex(cid);
	if (index == -1||index >size-1)	return 0;
	customers_hash[index]->shopping_tree = DeleteProduct(customers_hash[index]->shopping_tree, pid);
	customers_hash[index]->shopping_size--;
	printf("D <cid>	<pid>\n");
	PrintCustomersClear();
	printf("DONE\n");
	return 1;
}





void CreateCustomerTable(struct C_Product *root, struct C_Product **products_table) {

	if (root == NULL) return;
	CreateCustomerTable(root->lc, products_table);
	products_table[counter++] = root;
	CreateCustomerTable(root->rc, products_table);
	
}

void WalkShops(struct Shop *root, struct C_Product **products_table,int size) {

	if (root == shopSentinel) return;
	WalkShops(root->lc,products_table,size);
	struct Product *temp = root->products;
	int cnt = 0;
	if (counter != size) {/*an den einai ola ta qty tou pinaka 0*/

		while (temp != NULL) {/* an exei proionta to magazi*/

			if (cnt == size) break;/*an exei teliwsei pinakas proiontwn*/
			if (temp->pid == products_table[cnt]->pid) {
				if (temp->qty > products_table[cnt]->qty) {
					temp->qty = temp->qty - products_table[cnt]->qty;
					products_table[cnt]->qty = 0;
					counter++;
				}
				else {
					products_table[cnt]->qty = products_table[cnt]->qty - temp->qty;
					temp->qty = 0;
				}
				cnt++;
				continue;

			}
			else if (temp->pid > products_table[cnt]->pid) {
				cnt++;
				continue;
			}
			if (temp->next != NULL) temp = temp->next;
			else break;
		}
	}
	WalkShops(root->rc, products_table, size);
}
/**
 * @brief Go shopping
 *
 * @param cid The customer's id
 *
 * @return 1 on success
 *         0 on failure
 */
int GoShopping(int cid)
{
	int index = searchCidIndex(cid);
	if (index == -1||index >size-1)	return 0;
	struct C_Product **products_table =  (struct C_Product**)malloc(customers_hash[index]->shopping_size * sizeof(struct C_Product*));
	counter = 0;
	CreateCustomerTable(customers_hash[index]->shopping_tree, products_table);
	counter = 0;/*edw tha ton xrhsimopoiwsh san counter pou diexnei ta proionta ston pinaka product_table pou exun 0 qty*/
	WalkShops(shopRoot, products_table, customers_hash[index]->shopping_size);
	printf("G <cid>\n\tCustomer%d=", cid);
	PrintCustomerTree(customers_hash[index]->shopping_tree);
	printf("\n");
	PrintTreeShops(shopRoot);
	printf("DONE\n");
	return 1;	
}

/*sunenwsh twn 2 pinakwn se enan ta3inomhmeno*/
void mergeArrays(struct C_Product **arr1, struct C_Product **arr2, int index1, int index2, struct C_Product **arr3)
{
	int i = 0, j = 0, k = 0;

	/*oso exoun stoixeia opoio einai mikrotero to vazw kai kai proxwraw se auto to array  */
	while (i < index1 && j < index2)
	{
		if (arr1[i]->pid < arr2[j]->pid)
			arr3[k++] = arr1[i++];
		else
			arr3[k++] = arr2[j++];
	}

	/*apothikeuw ta stoixeia pou apomenoun otan kapoia apo ta 2 array ftasei sto telos tou */
	if (i < index1) {
		while (i < index1) arr3[k++] = arr1[i++];
	}
	if (j < index2) {
		while (j < index2) arr3[k++] = arr2[j++];
	}
}


struct C_Product* sortedArrayToBST(struct C_Product **arr, int start, int end)
{
	if (start > end) return NULL;
		

	/* riza to mesaio stoixeio gia na einai isoropoihmeno*/
	int mid = (start + end) / 2;
	struct C_Product *root = (struct C_Product*)malloc(sizeof(struct C_Product));
	counter++;
	root->pid = arr[mid]->pid;
	root->qty = arr[mid]->qty;

	root->lc = sortedArrayToBST(arr, start, mid - 1);
	root->rc = sortedArrayToBST(arr, mid + 1, end);

	return root;
}
/**
 * @brief Customers shop together
 *
 * @param cid1  The id of the first customer
 * @param cid2  The id of the second customer
 *
 * @return 1 on success
 *         0 on failure
 */
int ShopTogether(int cid1, int cid2)
{
	int index1 = searchCidIndex(cid1);
	if (index1==-1||index1>size-1 ) return 0;/* den to vrhke*/
	int index2 = searchCidIndex(cid2);
	if (index2==-1||index2>size-1 ) return 0;/* den to vrhke*/
	struct C_Product **cid1_table = (struct C_Product**)malloc(customers_hash[index1]->shopping_size * sizeof(struct C_Product*));
	struct C_Product **cid2_table = (struct C_Product**)malloc(customers_hash[index2]->shopping_size * sizeof(struct C_Product*));
	struct C_Product **common_table = (struct C_Product**)malloc((customers_hash[index1]->shopping_size + customers_hash[index2]->shopping_size) * sizeof(struct C_Product*));
	counter = 0;
	CreateCustomerTable(customers_hash[index1]->shopping_tree, cid1_table);
	counter = 0;
	CreateCustomerTable(customers_hash[index2]->shopping_tree, cid2_table);
	mergeArrays(cid1_table, cid2_table, customers_hash[index1]->shopping_size, customers_hash[index2]->shopping_size, common_table);
	counter = 0;
	customers_hash[index1]->shopping_tree = sortedArrayToBST(common_table, 0, (customers_hash[index1]->shopping_size + customers_hash[index2]->shopping_size)-1);
	customers_hash[index1]->shopping_size = counter;
	customers_hash[index2] = NULL;/*diagrafh tou cid2 shopping tree */
	printf("M <cid1> <cid2>\n\tCustomer%d=", cid1);
	PrintCustomerTree(customers_hash[index1]->shopping_tree);
	printf("\nDONE\n");
	return 1;
}

struct Shop* insertType(struct Shop* root, struct Shop* Sentinel, struct Product *products, int sid, int type)
{
	
	if (root == Sentinel) {
		struct Shop *temp = (struct Shop*)malloc(sizeof(struct Shop));
		if (temp == NULL) return NULL;
		temp->lc = temp->rc = Sentinel;
		temp->products = products;
		temp->sid = sid;
		temp->type = type;
		return temp;
	}

	
	if (sid < root->sid) root->lc = insertType(root->lc, Sentinel,products ,sid, type);
	else if (sid > root->sid) root->rc = insertType(root->rc, Sentinel,products ,sid, type);

	/*epistrofh tou kainurgiou dentrou*/
	return root;
}


void WalkTypeShops(struct Shop* root) {

	if (root == shopSentinel) return;
	WalkTypeShops(root->lc );
	switch (root->type){	
	case 1: 
		shopRootType1 = insertType(shopRootType1, Sentinel1,root->products, root->sid, root->type);
		break;
	
	case 2:
		shopRootType2 = insertType(shopRootType2, Sentinel2, root->products, root->sid, root->type);
		break;
	case 3:
		shopRootType3 = insertType(shopRootType3, Sentinel3, root->products, root->sid, root->type);
		break;
	case 4:
		shopRootType4 = insertType(shopRootType4, Sentinel4, root->products, root->sid, root->type);
		break;
	case 5:
		shopRootType5 = insertType(shopRootType5, Sentinel5, root->products, root->sid, root->type);
		break;	
	}
	WalkTypeShops(root->rc);
	
}
void PrintTreeTypeShops(struct Shop *root, struct Shop *Sentinel) {
	if (root == Sentinel) return;
	PrintTreeTypeShops(root->lc,Sentinel);
	counter++;
	printf("\t\tShop%d=", root->sid);
	struct Product *tempProduct = root->products;
	if (tempProduct == NULL) {
		printf("\n");
		PrintTreeTypeShops(root->rc,Sentinel);
		return; /*ean den exei kanena proion*/
	}
	while (tempProduct->next != NULL) {
		printf("<%d,%d,%d> ", tempProduct->pid, tempProduct->qty, tempProduct->price);
		tempProduct = tempProduct->next;
	}
	printf("<%d,%d,%d>\n", tempProduct->pid, tempProduct->qty, tempProduct->price);/*kai gia to teleutaio proion*/
	PrintTreeTypeShops(root->rc,Sentinel);
}
/**
 * @brief Categorize shops
 *
 * @return 1 on success
 *         0 on failure
 */
int CategorizeShops(void)
{
	counter = 0;
	WalkTypeShops(shopRoot);
	printf("T\n\tType1\n");
	PrintTreeTypeShops(shopRootType1,Sentinel1);
	printf("\tType2\n");
	PrintTreeTypeShops(shopRootType2, Sentinel2);
	printf("\tType3\n");
	PrintTreeTypeShops(shopRootType3, Sentinel3);
	printf("\tType4\n");
	PrintTreeTypeShops(shopRootType4, Sentinel4);
	printf("\tType5\n");
	PrintTreeTypeShops(shopRootType5, Sentinel5);
	printf("DONE\n");
	return 1;
}

/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int FreeAll(void)
{
	return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	
	
	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

			/* dummy event '0'. Get the total number of customers */
			case '0':
				{
					sscanf(buff, "%c %u", &event, &max_customers_g);
					Initialize();
					DPRINT("%c MAX CUSTOMERS: %u\n", event, max_customers_g);
					break;
				}

				/* Register shop
				 * R <sid> <type> */
			case 'R':
				{
					int sid, type;

					sscanf(buff, "%c %d %d", &event, &sid, &type);
					DPRINT("%c %d %d\n", event, sid, type);

					if (RegisterShop(sid, type)) {
						DPRINT("%c %d %d succeeded\n", event, sid, type);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, sid, type);
					}

					break;
				}

				/* Supply shop
				 * S <sid> <pid> <quantity> <price> */
			case 'S':
				{
					int sid, pid, quantity, price;

					sscanf(buff, "%c %d %d %d %d", &event, &sid, &pid, &quantity, &price);
					DPRINT("%c %d %d %d %d\n", event, sid, pid, quantity, price);

					if (SupplyShop(sid, pid, quantity, price)) {
						DPRINT("%c %d %d %d %d succeeded\n", event, sid, pid, quantity, price);
					} else {
						fprintf(stderr, "%c %d %d %d %d failed\n", event, sid, pid, quantity, price);
					}

					break;
				}

				/* Register customer
				 * C <cid> */
			case 'C':
				{
					int cid;

					sscanf(buff, "%c %d", &event, &cid);
					DPRINT("%c %d\n", event, cid);

					if (RegisterCustomer(cid)) {
						DPRINT("%c %d succeeded\n", event, cid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, cid);
					}

					break;
				}

				/* Add to shopping list
				 * L <cid> <pid> <quantity> */
			case 'L':
				{
					int cid, pid, quantity;

					sscanf(buff, "%c %d %d %d", &event, &cid, &pid, &quantity);
					DPRINT("%c %d %d %d\n", event, cid, pid, quantity);

					if (AddToShoppingList(cid, pid, quantity)) {
						DPRINT("%c %d %d %d succeeded\n", event, cid, pid, quantity);
					} else {
						fprintf(stderr, "%c %d %d %d failed\n", event, cid, pid, quantity);
					}

					break;
				}

				/* Delete from shopping list
				 * D <cid> <pid> */
			case 'D':
				{
					int cid, pid;

					sscanf(buff, "%c %d %d", &event, &cid, &pid);
					DPRINT("%c %d %d\n", event, cid, pid);

					if (DeleteFromShoppingList(cid, pid)) {
						DPRINT("%c %d %d succeeded\n", event, cid, pid);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, cid, pid);
					}

					break;
				}

				/* Go shopping
				 * G <cid> */
			case 'G':
				{
					int cid;

					sscanf(buff, "%c %d", &event, &cid);
					DPRINT("%c %d\n", event, cid);

					if (GoShopping(cid)) {
						DPRINT("%c %d succeeded\n", event, cid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, cid);
					}

					break;
				}

				/* Shop together
				 * M <cid1> <cid2> */
			case 'M':
				{
					int cid1, cid2;

					sscanf(buff, "%c %d %d", &event, &cid1, &cid2);
					DPRINT("%c %d %d\n", event, cid1, cid2);

					if (ShopTogether(cid1, cid2)) {
						DPRINT("%c %d %d succeeded\n", event, cid1, cid2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, cid1, cid2);
					}

					break;
				}

				/* Categorize shops
				 * T */
			case 'T':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (CategorizeShops()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Print shops
				 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (PrintShops()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Print customers
				 * Y */
			case 'Y':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (PrintCustomers()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

				/* Empty line */
			case '\n':
				break;

				/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	FreeAll();
	return (EXIT_SUCCESS);
}