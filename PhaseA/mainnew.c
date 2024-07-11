/*************************************************************
 * @file   main.c                                            *
 * @author Nikolaos Batsaras <batsaras@csd.uoc.gr>  	     *
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
 /**
  * @brief Print shops
  *
  * @return 1 on success
  *         0 on failure
  */
int PrintShops(void)
{
	struct Shop* temp = H->next;/*start on the first non-header shop*/
	struct Product *pp;
	if (temp == NULL) return 0;/*kanena shop den uparxei*/
	int counter = 1;
	while (temp != H) {
		pp = temp->products;
		
		if (pp == NULL)	
		{/*an den exei proionta kapoio shop*/
			temp = temp->next;
			printf("\tShop%d=\n", counter);
			counter++;
			continue;
		}
		
		printf("\tShop%d=", counter);
		while (pp->next != NULL) {/*alliws ektupwse mexri proteleutaio*/
			printf("<%d,%d,%d>,", pp->pid, pp->quantity, pp->price);
			pp = pp->next;
		}
		/*ektupwse gia teleutaio kai phgene sto epomeno shop*/
		printf("<%d,%d,%d>\n", pp->pid, pp->quantity, pp->price);
		counter++;
		temp = temp->next;
	}
	return 1;
}




/**
 * @brief Print customers
 *
 * @return 1 on success
 *         0 on failure
 */
int PrintCustomers(void)
{
	struct Customer* temp = Customers;
	struct C_Product* pp;
	if (Customers == Sentinel) return 0;/*only sentinel exists*/
	int counter = 1;

	
	while (temp != Sentinel) {
		pp = temp->shopping_list;
		if (pp == NULL)
		{/*an den exei proionta kapoio shop*/
			temp = temp->next;
			printf("\tCustomer%d=\n", counter);
			counter++;
			continue;
		}
		printf("\tCustomer%d=", counter);
		while (pp->next != NULL) {/*mexri kai to proteleutaio*/
			printf("<%d,%d>,", pp->pid, pp->quantity);
			pp = pp->next;
		}
		printf("<%d,%d>\n", pp->pid, pp->quantity);/*gia to teleutaio*/
		counter++;
		temp = temp->next;
	}

	return 1;
}






int DeleteZeroQuantities(void) {
	struct Shop *temp = H->next;
	struct Product *tempProduct=NULL;
	struct Product *lastProduct=NULL;
	struct C_Product *tempCProduct = NULL;
	struct C_Product *lastCProduct = NULL;
	
	struct Customer *tempCustomer = Customers;
	if (tempCustomer == Sentinel) return 0;/*den uparxoun customers*/
	if (temp==NULL) return 0;/*den uparxoun shops*/
	while (temp != H) {
		tempProduct = temp->products;
		if (tempProduct == NULL) {
			temp = temp->next;
			continue;
		}
		while (tempProduct->next != NULL) {
			if (tempProduct->quantity == 0) {
				if (lastProduct == NULL) {/* an einai to prwto*/
					temp->products = temp->products->next;
				}
				else {
					lastProduct->next = tempProduct->next;
				}
			}
			lastProduct = tempProduct;
			tempProduct = tempProduct->next;
		}
		if (tempProduct->quantity == 0) {
			if (lastProduct == NULL) {/*an einai to prwto*/
				temp->products = temp->products->next;
			}
			else {
				lastProduct->next = tempProduct->next;
			}
		}
		lastProduct =NULL;/*edw evaza =tempproduct	*/
		temp = temp->next;
	}

	while (tempCustomer != Sentinel) {
		tempCProduct = tempCustomer->shopping_list;
		if (tempCProduct == NULL) {
			tempCustomer = tempCustomer->next;
			continue;
		}
		while (tempCProduct->next != NULL) {
			if (tempCProduct->quantity == 0) {
				if (lastCProduct == NULL) {/* an einai to prwto*/
					tempCustomer->shopping_list = tempCustomer->shopping_list->next;
				}
				else {
					lastCProduct->next = tempCProduct->next;
				}
			}
			lastCProduct = tempCProduct;
			tempCProduct = tempCProduct->next;
		}
		if (tempCProduct->quantity == 0) {
			if (lastCProduct == NULL) {/* an einai to prwto*/
				tempCustomer->shopping_list= tempCustomer->shopping_list->next;
			}
			else {
				lastCProduct->next = tempCProduct->next;
			}
		}
		lastCProduct = NULL;/*edw evaza =tempCproduct	*/	
		tempCustomer = tempCustomer->next;
	}
	return 0;
}

struct Product *merge(struct Product *p, struct Product *q, struct Product *sorting)
{
	struct Product *head3;
	if (p == NULL) return q;	
	if (q == NULL) return p;
	
	if (p && q)
	{
		if (p->pid <= q->pid)
		{
			sorting = p;
			p = sorting->next;
		}
		else
		{
			sorting = q;
			q = sorting->next;
		}
	}
	head3 = sorting;
	while (p && q)
	{
		if (p->pid <= q->pid)
		{
			sorting->next = p;
			sorting = p;
			p = sorting->next;
		}
		else
		{
			sorting->next = q;
			sorting = q;
			q = sorting->next;
		}
	}

	if (p == NULL) sorting->next = q;
	if (q == NULL) sorting->next = p;
	return head3;
}

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int Initialize (void)
{
    H=(struct Shop*)malloc(sizeof(struct Shop)); /*Shop list header initialization*/
    if(H == NULL) return 0;
    H->next=NULL;
    H->prev=NULL;
	Sentinel = (struct Customer*)malloc(sizeof(struct Customer));
	if (Sentinel == NULL) return 0;
	Sentinel->next = NULL;
	Sentinel->shopping_list = NULL;
	Sentinel->cid = -1;
	Customers =Sentinel;
	/*arxikopoihsh twn 5 listwn diaforetikou type shop,kai tou pinaka me ta cheapest*/
	shop[0]=  NULL;
	shop[1]=  NULL;
	shop[2] = NULL;
	shop[3] = NULL;
	shop[4]=  NULL;
	cheapest[0] = NULL;
	cheapest[1] = NULL;
	cheapest[2] = NULL;
	cheapest[3] = NULL;
	cheapest[4] = NULL;

	return 1;
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
int RegisterShop (int sid, int type)
{
    printf("R <sid> <type>\n\tShops=");
    struct Shop* temp=H;
    if(temp->next==NULL){/*first shop node*/
        struct Shop* first_shop = (struct Shop*)malloc(sizeof(struct Shop));
        if(first_shop == NULL) return 0;
        first_shop->sid=sid;
        first_shop->type=type;
        first_shop->next=temp;
        first_shop->prev=temp;
        first_shop->products=NULL;
        temp->next=temp->prev=first_shop;
		printf("<%d,%d>\nDONE\n", sid,type);
		return 1;
    }
	temp = temp->next;
    while (temp->next!=H){
        temp=temp->next;
        printf("<%d,%d>,",temp->sid,temp->type);
    }
    struct Shop* new_shop = (struct Shop*)malloc(sizeof(struct Shop));
    if(new_shop == NULL) return 0;
    new_shop->sid=sid;
    new_shop->type=type;
    new_shop->next=temp->next;
    new_shop->prev=temp;
    new_shop->products=NULL;
	temp->next = new_shop;
    printf("<%d,%d>\nDONE\n",new_shop->sid,new_shop->type);
	return 1;
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
int SupplyShop (int sid, int pid, int quantity, int price)
{
    struct Shop *temp= H->next;/*start on the first non-header shop;*/
	if (temp == NULL) return 0;
    struct Product *pp;
    while((temp->sid!=sid)&&(temp!=H)){
        temp=temp->next;
    }
    if(temp==H){
        return 0;/*didnt find the shop*/
    }
     pp=temp->products;
     struct Product* new_product = (struct Product*)malloc(sizeof(struct Product));
     if(new_product == NULL) return 0;
     new_product->pid=pid;
     new_product->quantity=quantity;
     new_product->price=price;
	 if (pp == NULL) {/*gia to prwto proion*/

		 new_product->next = NULL;
		 temp->products = new_product;/*edw anti gia temp->prod eixa pp*/
		
	 }
	 else {
		 while ((pp->next != NULL) && (pp->next->pid < pid)) {
			 pp = pp->next;
		 }
		 if (pp->next == NULL) {
			 if (pp->pid == pid) {
				 pp->quantity = pp->quantity + quantity;
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
		 else{
			 if (pp == temp->products) {/*auto prosthesa*/
				 if (pp->pid == pid) {
					 pp->quantity = pp->quantity + quantity;
				 }
				 else if (pid < pp->pid) {
					 new_product->next = pp;
					 temp->products = new_product;
				 }else if (pp->next->pid == pid) {/*au3anei ta quantities an 3anavrei kapoio proion*/
					 pp->next->quantity = pp->next->quantity + quantity;

				 }
				 else {

					 new_product->next = pp->next;
					 pp->next = new_product;
				 }
			 }
			 else {

				 if (pp->next->pid == pid) {/*au3anei ta quantities an 3anavrei kapoio proion*/
					 pp->next->quantity = pp->next->quantity + quantity;

				 }
				 else {

					 new_product->next = pp->next;
					 pp->next = new_product;
				 }

			 }
		 }
	 }
    printf("S <sid> <pid> <quantity> <price>\n");
    PrintShops();
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
int RegisterCustomer (int cid)
{
	printf("C <cid>\n\tCustomers=");
    struct Customer* temp= Customers;
    struct Customer* new_customer=(struct Customer*)malloc(sizeof(struct Customer));
    if(new_customer==NULL) return 0;
	new_customer->cid = cid;
	new_customer->next = Sentinel;
	new_customer->shopping_list = NULL;

	if (temp == Sentinel) {
		Customers=temp=new_customer;
		printf("<%d>\n", temp->cid);
		printf("DONE\n");
	}
	else {

		while (temp->next != Sentinel) {
			printf("<%d>,", temp->cid);
			temp = temp->next;
		}
		printf("<%d>,", temp->cid);
		printf("<%d>\n",cid);
		printf("DONE\n");
		temp->next = new_customer;
	}
	return 1;
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
	struct Customer* temp = Customers;
	struct C_Product* new_product = (struct C_Product*)malloc(sizeof(struct C_Product));
	struct C_Product* pp;
	if (new_product == NULL) return 0;
	new_product->pid = pid;
	new_product->quantity = quantity;
	Sentinel->cid = cid;
	while (temp->cid != cid) {
		temp = temp->next;
	}
	if (temp == Sentinel) return 0;
	pp = temp->shopping_list;
	if (pp == NULL) {
		new_product->next = NULL;
		temp->shopping_list = new_product;	
		
	}
	else {

		while ((pp->next != NULL) && (pp->next->pid < pid)) {	
			pp = pp->next;

		}
		
		if (pp->next == NULL) {
			if (pp == temp->shopping_list) {
				if (pp->pid == pid) {
					pp->quantity = pp->quantity + quantity;
				}
				else if (pid < pp->pid) {
					new_product->next = pp;
					temp->shopping_list = new_product;
				}

				else {
					new_product->next = NULL;
					pp->next = new_product;
				}
			}
		}
		else {

			if (pp == temp->shopping_list) {
				if (pp->pid == pid) {
					pp->quantity = pp->quantity + quantity;
				}
				else if (pid < pp->pid) {
					new_product->next = pp;
					temp->shopping_list = new_product;
				}else if (pp->next->pid == pid) {/*an uparxei hdh to proion apla prosthetei tis posothtes*/
					pp->next->quantity = pp->next->quantity + quantity;
				}
				else {
					new_product->next = pp->next;
					pp->next = new_product;
				}
			}
			else {

				if (pp->next->pid == pid) {/*an uparxei hdh to proion apla prosthetei tis posothtes*/
					pp->next->quantity = pp->next->quantity + quantity;
				}
				else {
					new_product->next = pp->next;
					pp->next = new_product;
				}
			}
		}
	}

	printf("L <cid> <pid> <quantity>\n");
	PrintCustomers();
	printf("DONE\n");

	return 1;
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
	struct Customer *temp = Customers;
	struct C_Product *tempP;
	struct C_Product *last = NULL;
	if (temp == Sentinel) return 0;/*an den uparxoun customers*/
	Sentinel->cid = cid;
	while (temp->cid != cid) {
		temp = temp->next;
	}
	if (temp == Sentinel) return 0;/* den uparxei o cid customer*/
	if (temp->shopping_list == NULL) return 0;/*den exei kanena proion*/

	tempP = temp->shopping_list;

	while ((tempP->pid != pid) && (tempP->next != NULL)) {
		last = tempP;
		tempP = tempP->next;
	}
	if (tempP->next == NULL) {/*an einai to teleutaio*/
		if (tempP->pid == pid) {/* an einai to teleutaio to anazhtoumeno pid*/
			if (last == NULL) {
				temp->shopping_list = NULL;

			}
			else {
				last->next = tempP->next;
			}
			printf("D <cid> <pid>\n");
			PrintCustomers();
			printf("DONE\n");
		}
		else
		{
			if (last == NULL) return 0;
			last->next = NULL;
			printf("D <cid> <pid>\n");
			PrintCustomers();
			printf("DONE\n");
		}
		return 1;

	}
	
	if (last == NULL) {
		temp->shopping_list = tempP->next;
		printf("D <cid> <pid>\n");
		PrintCustomers();
		printf("DONE\n");
		return 1;
	}else{
	
		last->next = tempP->next;
		printf("D <cid> <pid>\n");
		PrintCustomers();
		printf("DONE\n");
		return 1;
	}
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

	struct Customer *tempCustomer = Customers;
	struct Shop *tempShop = H->next;/*start in the first non header shop*/
	if (tempShop == NULL) return 0; /*den uparxoun shops*/
	struct Product *tempShopProduct;
	if (tempCustomer == Sentinel) return 0; /*den uparxoun customers*/
    Sentinel->cid=cid;
    while(tempCustomer->cid!=cid){
        tempCustomer=tempCustomer->next;
    }
	if (tempCustomer == Sentinel) return 0; /* den vrhke ton customer*/
    struct C_Product *tempCustomerProduct=tempCustomer->shopping_list;
	if (tempCustomerProduct == NULL) return 0;/*den thelei proionta o customer*/

	while (tempShop != H) {
		tempShopProduct = tempShop->products;
		if (tempShopProduct == NULL) {
			tempCustomerProduct = tempCustomer->shopping_list;/*kainurgio*/
			tempShop = tempShop->next;
			continue;
		}

		while (tempShopProduct->next != NULL) {
			 while (tempCustomerProduct->next != NULL) {
				if (tempShopProduct->pid == tempCustomerProduct->pid) {
					if ((tempShopProduct->quantity - tempCustomerProduct->quantity) >= 0) {
						tempShopProduct->quantity = tempShopProduct->quantity - tempCustomerProduct->quantity;
						tempCustomerProduct->quantity = 0;

					}
					else {
						tempCustomerProduct->quantity = tempCustomerProduct->quantity - tempShopProduct->quantity;
						tempShopProduct->quantity = 0;

					}

				}
				tempCustomerProduct = tempCustomerProduct->next;
			 }
			/*gia to telutaio proion */
			if (tempShopProduct->pid == tempCustomerProduct->pid) {
				if ((tempShopProduct->quantity - tempCustomerProduct->quantity) >= 0) {
					tempShopProduct->quantity = tempShopProduct->quantity - tempCustomerProduct->quantity;
					tempCustomerProduct->quantity = 0;

				}
				else {
					tempCustomerProduct->quantity = tempCustomerProduct->quantity - tempShopProduct->quantity;
					tempShopProduct->quantity = 0;

				}

			}
			tempShopProduct = tempShopProduct->next;

		}
		/*gia to teleutaio proion tu katanalwth*/
		while (tempCustomerProduct->next != NULL) {
			if (tempShopProduct->pid == tempCustomerProduct->pid) {
				if ((tempShopProduct->quantity - tempCustomerProduct->quantity) >= 0) {
					tempShopProduct->quantity = tempShopProduct->quantity - tempCustomerProduct->quantity;
					tempCustomerProduct->quantity = 0;

				}
				else {
					tempCustomerProduct->quantity = tempCustomerProduct->quantity - tempShopProduct->quantity;
					tempShopProduct->quantity = 0;

				}

			}
			tempCustomerProduct = tempCustomerProduct->next;
		}
		/*gia to telutaio proion tou katasthmatos*/
		if (tempShopProduct->pid == tempCustomerProduct->pid) {
			if ((tempShopProduct->quantity - tempCustomerProduct->quantity) >= 0) {
				tempShopProduct->quantity = tempShopProduct->quantity - tempCustomerProduct->quantity;
				tempCustomerProduct->quantity = 0;

			}
			else {
				tempCustomerProduct->quantity = tempCustomerProduct->quantity - tempShopProduct->quantity;
				tempShopProduct->quantity = 0;

			}

		}
		tempShop = tempShop->next;
		tempCustomerProduct = tempCustomer->shopping_list;
	}
	/*edw tha kanw ta delete opoiou komvou proiontos exei 0 quantity kai stis 2 listes*/
	DeleteZeroQuantities();
	DeleteZeroQuantities();
	printf("G <cid>\n");
	PrintCustomers();
	printf("\n");
	PrintShops();
	printf("DONE\n");
	return 1;
}




/**
 * @brief Store close
 *
 * @param sid1  The id of the acquisitor shop
 * @param sid2  The id of the closing shop
 *
 * @return 1 on success
 *         0 on failure
 */
int StoreClose (int sid1, int sid2)
{
	int uparxoun = 0;
    struct Shop *temp=H;
	if (temp->next == NULL) return 0;/*den uparxoun shops*/
	struct Shop *shop1=NULL;
	struct Shop *shop2=NULL;
	struct Product *pro1;
	struct Product *pro2;
	temp = H->next;/* first non header shop*/
	while (temp != H) {
		if (temp->sid == sid1) {
			shop1 = temp;
			uparxoun++;
		}

		if (temp->sid == sid2) {
			shop2 = temp;
			uparxoun++;

		}
		temp = temp->next;
	}
	if (uparxoun != 2) return 0;/*den uparxoun ta 2 katasthmata*/
	if (shop1->products == NULL) {
		shop1->products = shop2->products;
		shop2->prev->next = shop2->next;/*diagrafh shop2*/
	}
	if (shop2->products == NULL) {
		shop2->prev->next = shop2->next;/*diagrafh shop2*/
	}
	pro1 = shop1->products;
	pro2 = shop2->products;
	struct Product* sorted = (struct Product*)malloc(sizeof(struct Product));
	if (sorted == NULL) return 0;
	shop1->products = merge(pro1, pro2,sorted);/*kalw thn merge*/
	shop2->prev->next = shop2->next;/*diagrafh shop2*/
    printf("M <sid1> <sid2>\n");
    PrintShops();
    printf("DONE\n");
	return 1;
}

/**
 * @brief Categorize shops
 *
 * @return 1 on success
 *         0 on failure
 */
int CategorizeShops (void)
{
	int i;
	int j=1;
	struct CategorizedShop *last[5];
	struct CategorizedShop *print[5];
	last[0]=NULL;
	last[1]=NULL;
	last[2]=NULL;
	last[3]=NULL;
	last[4]=NULL;
	struct Shop *temp = H;
	if (temp == NULL) return 0;/*den uparxei kanena shop*/
	temp = H->next;/*3ekiname apo to prwto oxi header shop*/
	while (temp != H) {
		struct CategorizedShop* new_shop = (struct CategorizedShop*)malloc(sizeof(struct CategorizedShop));
		if (new_shop == NULL) return 0;
		new_shop->products = temp->products;
		new_shop->next = NULL;
		new_shop->sid = temp->sid;
		switch (temp->type) {
		case 0:
			if (shop[0] == NULL) {/*to prwto shop0*/
				shop[0] = new_shop;
				last[0] = shop[0];
			}
			else {
				last[0]->next = new_shop;
				last[0] = new_shop;
			}
			break;

		case 1:
			if (shop[1] == NULL) {/*to prwto shop1*/
				shop[1] = new_shop;
				last[1] = shop[1];
			}
			else {
				last[1]->next = new_shop;
				last[1] = new_shop;
			}

			break;
		case 2:
			if (shop[2] == NULL) {/*to prwto shop2*/	
				shop[2] = new_shop;
				last[2] = shop[2];
			}else {
				last[2]->next = new_shop;
				last[2] = new_shop;
			}

			break;

		case 3:
			if (shop[3] == NULL) {/*to prwto shop3*/		
				shop[3] = new_shop;
				last[3] = shop[3];
			}else {
				last[3]->next = new_shop;
				last[3] = new_shop;
			}
			break;

		case 4:
			if (shop[4]== NULL) {/*to prwto shop4*/	
				shop[4] = new_shop;
				last[4] = shop[4];
			}else {
				last[4]->next = new_shop;
				last[4] = new_shop;
			}
			break;
		
		}
		temp = temp->next;
	}
	
	printf("T\n");
	for(i=0;i<=4;i++){
		print[i] = shop[i];
		printf(" Type%d\n", i );
		if (print[i] != NULL) {
			
			while (print[i]->next != NULL) {
				printf("\tShop%d=", j);
				if (print[i]->products == NULL) {
					printf("\n");
					print[i] = print[i]->next;
					j++;
					continue;
				}
				while (print[i]->products->next != NULL) {
					printf("<%d,%d,%d>,", print[i]->products->pid, print[i]->products->quantity, print[i]->products->price);
					print[i]->products = print[i]->products->next;
					
				}
				j++;
				printf("<%d,%d,%d>\n", print[i]->products->pid, print[i]->products->quantity, print[i]->products->price);
				print[i] = print[i]->next;
			}
			/*gia to teleutaio shop*/
			printf("\tShop%d=", j);
			if (print[i]->products == NULL) {
				printf("\n");
				print[i] = print[i]->next;
				j++;
				continue;
			}
			
			while (print[i]->products->next != NULL) {
				printf("<%d,%d,%d>,", print[i]->products->pid, print[i]->products->quantity, print[i]->products->price);
				print[i]->products = print[i]->products->next;
			
			}
			j++;
			printf("<%d,%d,%d>\n", print[i]->products->pid, print[i]->products->quantity, print[i]->products->price);

		}
		else {
			continue;
		}
	}
	printf("DONE\n");
	
	return 1;
}

/**
 * @brief Find cheapest products
 *
 * @return 1 on success
 *         0 on failure
 */
int FindCheapestProducts (void)
{
	int i, j;
	int gematestheseis = 0;
	struct Shop* temp = H->next;/*start on the first non-header shop*/
	struct Product *pp;
	if (temp == NULL) return 0;/*kanena shop den uparxei*/
	while (temp != H) {
		pp = temp->products;
		if (pp == NULL){/*an den exei proionta kapoio shop*/
			temp = temp->next;
			continue;
		}
		while (pp->next != NULL) {/*arxikopoihsh tou pinaka*/
			if (gematestheseis==0) {
				cheapest[0] = pp;
				gematestheseis++;
			}
			else if (gematestheseis == 1) {
				if (pp->price < cheapest[0]->price) {
					cheapest[1] = cheapest[0];
					cheapest[0] = pp;
				}
				else {
					cheapest[1] = pp;
				}
				gematestheseis++;
			}
			else if (gematestheseis == 2) {
				if (pp->price < cheapest[0]->price) {
					cheapest[2] = cheapest[1];
					cheapest[1] = cheapest[0];
					cheapest[0] = pp;
				}
				else if (pp->price < cheapest[1]->price){
					cheapest[2] = cheapest[1];
					cheapest[1] = pp;
				}
				else {
					cheapest[2] = pp;
				}
				gematestheseis++;
			}
			else if (gematestheseis == 3) {
				if (pp->price < cheapest[0]->price) {
					cheapest[3] = cheapest[2];
					cheapest[2] = cheapest[1];
					cheapest[1] = cheapest[0];
					cheapest[0] = pp;
				}
				else if (pp->price < cheapest[1]->price) {
					cheapest[3] = cheapest[2];
					cheapest[2] = cheapest[1];
					cheapest[1] = pp;
				}
				else if (pp->price < cheapest[2]->price) {
					cheapest[3] = cheapest[2];
					cheapest[2] = pp;
				}
				else {
					cheapest[3] = pp;
				}
				gematestheseis++;
			}else if (gematestheseis == 4) {
				if (pp->price < cheapest[0]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = cheapest[2];
					cheapest[2] = cheapest[1];
					cheapest[1] = cheapest[0];
					cheapest[0] = pp;
				}
				else if (pp->price < cheapest[1]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = cheapest[2];
					cheapest[2] = cheapest[1];
					cheapest[1] = pp;
				}
				else if (pp->price < cheapest[2]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = cheapest[2];
					cheapest[2] = pp;
				}
				else if (pp->price < cheapest[3]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = pp;
				}
				else {
					cheapest[4] = pp;
				}
				gematestheseis++;
			}
			else {

				if (pp->price < cheapest[0]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = cheapest[2];
					cheapest[2] = cheapest[1];
					cheapest[1] = cheapest[0];
					cheapest[0] = pp;

				}
				else if (pp->price < cheapest[1]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = cheapest[2];
					cheapest[2] = cheapest[1];
					cheapest[1] = pp;
				}
				else if (pp->price < cheapest[2]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = cheapest[2];
					cheapest[2] = pp;
				}
				else if (pp->price < cheapest[3]->price) {
					cheapest[4] = cheapest[3];
					cheapest[3] = pp;
				}
				else if (pp->price < cheapest[4]->price) {
					cheapest[4] = pp;
				}

			}
			
			pp = pp->next;
		}/*kai gia to teleutaio stoixeio*/
		if (gematestheseis == 0) {
			cheapest[0] = pp;
			gematestheseis++;
		}
		else if (gematestheseis == 1) {
			if (pp->price < cheapest[0]->price) {
				cheapest[1] = cheapest[0];
				cheapest[0] = pp;
			}
			else {
				cheapest[1] = pp;
			}
			gematestheseis++;
		}
		else if (gematestheseis == 2) {
			if (pp->price < cheapest[0]->price) {
				cheapest[2] = cheapest[1];
				cheapest[1] = cheapest[0];
				cheapest[0] = pp;
			}
			else if (pp->price < cheapest[1]->price) {
				cheapest[2] = cheapest[1];
				cheapest[1] = pp;
			}
			else {
				cheapest[2] = pp;
			}
			gematestheseis++;
		}
		else if (gematestheseis == 3) {
			if (pp->price < cheapest[0]->price) {
				cheapest[3] = cheapest[2];
				cheapest[2] = cheapest[1];
				cheapest[1] = cheapest[0];
				cheapest[0] = pp;
			}
			else if (pp->price < cheapest[1]->price) {
				cheapest[3] = cheapest[2];
				cheapest[2] = cheapest[1];
				cheapest[1] = pp;
			}
			else if (pp->price < cheapest[2]->price) {
				cheapest[3] = cheapest[2];
				cheapest[2] = pp;
			}
			else {
				cheapest[3] = pp;
			}
			gematestheseis++;
		}
		else if (gematestheseis == 4) {
			if (pp->price < cheapest[0]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = cheapest[2];
				cheapest[2] = cheapest[1];
				cheapest[1] = cheapest[0];
				cheapest[0] = pp;
			}
			else if (pp->price < cheapest[1]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = cheapest[2];
				cheapest[2] = cheapest[1];
				cheapest[1] = pp;
			}
			else if (pp->price < cheapest[2]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = cheapest[2];
				cheapest[2] = pp;
			}
			else if (pp->price < cheapest[3]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = pp;
			}
			else {
				cheapest[4] = pp;
			}
			gematestheseis++;
		}
		else {

			if (pp->price < cheapest[0]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = cheapest[2];
				cheapest[2] = cheapest[1];
				cheapest[1] = cheapest[0];
				cheapest[0] = pp;

			}else if (pp->price < cheapest[1]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = cheapest[2];
				cheapest[2] = cheapest[1];
				cheapest[1] = pp;				
			}
			else if (pp->price < cheapest[2]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = cheapest[2];
				cheapest[2] = pp;
			}
			else if (pp->price < cheapest[3]->price) {
				cheapest[4] = cheapest[3];
				cheapest[3] = pp;
			}
			else if (pp->price < cheapest[4]->price) {
				cheapest[4] = pp;				
			}
			
			/*
			for (i = 0; i <= 4; i++) {
				if (pp->price < cheapest[i]->price) break;

			}
			
			for (j = i; j <= 3; j++) {
				cheapest[j + 1] = cheapest[j];

			}
			
			if (pp->price < cheapest[i]->price) cheapest[i] = pp;
			*/
		}
		
		temp = temp->next;
	}

	/*printing*/
	printf("F\n\tCheapest Products: ");
	for (i = 0; i <= 3; i++) {
		if (cheapest[i] == NULL) continue;
		printf("<%d,%d,%d>,", cheapest[i]->pid, cheapest[i]->quantity, cheapest[i]->price);
	}
	if (cheapest[4] != NULL) printf("<%d,%d,%d>\nDONE\n", cheapest[4]->pid, cheapest[4]->quantity, cheapest[4]->price);
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
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	Initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch (buff[0]) {

			/* Comment */
		case '#':
			break;

			/* Register shop
			 * R <sid> <type> */
		case 'R':
		{
			int sid, type;

			sscanf(buff, "%c %d %d", &event, &sid, &type);
			DPRINT("%c %d %d\n", event, sid, type);

			if (RegisterShop(sid, type)) {
				DPRINT("%c %d %d succeeded\n", event, sid, type);
			}
			else {
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
			}
			else {
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
			}
			else {
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
			}
			else {
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
			}
			else {
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
			}
			else {
				fprintf(stderr, "%c %d failed\n", event, cid);
			}

			break;
		}

		/* Store close
		 * M <sid1> <sid2> */
		case 'M':
		{
			int sid1, sid2;

			sscanf(buff, "%c %d %d", &event, &sid1, &sid2);
			DPRINT("%c %d %d\n", event, sid1, sid2);

			if (StoreClose(sid1, sid2)) {
				DPRINT("%c %d %d succeeded\n", event, sid1, sid2);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, sid1, sid2);
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
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Find cheapest products
		 * F */
		case 'F':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (FindCheapestProducts()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
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
			}
			else {
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
			}
			else {
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
