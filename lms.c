/*
* Library Management Project by -->
*
* Nibir Ahmed - 2011333642
* Maliha Anzum Maisha  - 2011380642
* Tasin Hossain Toha - 2011664642
*
*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

//all functions
void mainmenu(void);

void addbook(void);
void viewbooklist(void);
void deletebook(void);
void searchbook(void);

void addcategory(void);
void viewcategories(void);
void deletecategory(void);

void showcategorytoadd(void);

int password(void);
void changepassword(void);

void aboutus(void);

int checkid(int c);
int getdata();

// data structure
struct Books{

    int id;

    char name[50];
    char category[50];
    char author[50];

    int rack;
    int quantity;
    int price;

};


struct Categories{
    char name[50];
};

struct Books b;
struct Categories c;

FILE *fp, *ft, *fc, *fpp;


int main(){

    system("cls");

    if( password() == 1 ){
        mainmenu();
    }else{
        printf("\n\t\t***Wrong Password***\n\n");
    }

    return 0;
}

//show homepage
void mainmenu(void){

	system("cls");
	printf("\n\n                                 **************************************************************************\n");
	printf("                                                     WELCOME TO LIBRARY MANAGEMENT SYSYTEM\n");
	printf("                                 **************************************************************************\n\n\n");
	printf("          1. ALL BOOKS--> \n\n          2. SEARCH BOOKS--> \n\n          3. ADD BOOKS--> \n\n          4. DELETE BOOKS--> \n\n          5. SEE ALL CATEGORIES--> \n\n          6. ADD CATEGORY--> \n\n          7. DELETE CATEGORIES--> \n\n          8. CHANGE PASSWORD--> \n\n          9. About Us--> \n\n          10. EXIT--> \n\n\n             Enter Your Choice ---> ");

	int choice;
	scanf("%d",&choice);

	if(choice==1) {
        viewbooklist();
	}
	else if(choice==2){
        searchbook();
	}
	else if(choice==3){
        addbook();
	}
	else if( choice==4 ){
        deletebook();
	}
	else if( choice==5 ){
        viewcategories();
	}
	else if( choice==6 ){
        addcategory();
	}
	else if( choice==7 ){
        deletecategory();
	}
	else if( choice==8 ){
        changepassword();
	}else if( choice==9 ){
        aboutus();
	}
	else if(choice==10){

		system("cls");
		printf("\n\n\n");
		printf("*******************************THANK YOU**************************************\n\n");

		exit(0);
	}
}

void showcategorytoadd(void){

    //system("cls");
    int i=0;
    printf("\n\n");
    printf("                              ********************** Category List **********************\n\n\n");
    printf("\tNo\t\tName\n");

    fc = fopen("categories.txt","r");

    if( fc == NULL ){
        printf("File opening failed!! or You may not have added categories yet");
        getch();
        mainmenu();

    }else{

        while( fread( &c, sizeof(c) ,1 ,fc ) == 1 ){

            printf("\t%d\t\t", i);
            printf("%s\t\t", c.name);
            printf("\n");
            i++;

        }

        fclose(fc);
    }

}

int checkid( int c ) {  //check whether the record is exist in list or not


	rewind(fp);

	while( fread( &b, sizeof(b), 1, fp ) == 1 )

	if( b.id == c ){

        return 0;  //returns 0 if employee exits

	}

	return 1; //return 1 if it not

}


int getdata() {

    fp = fopen( "books.txt", "r" );

	int t,findrecord;
	char temp_cat[50];
	printf("        BOOK ID :\t");
	scanf("%d",&t);

	if( checkid(t) == 0 ) {
		printf("\n\n");
		printf("\a                        A Book By This ID Already Exists !!!\a");
		getch();
		mainmenu();
		return 0;
	}

    fclose(fp);

	b.id=t;
    fflush(stdin);

    showcategorytoadd();

    printf("\n\n\tWrite a category name from the list: ");

    gets(temp_cat);
    fflush(stdin);

    fc = fopen("categories.txt", "r");
	rewind(fc);

	while( fread( &c, sizeof(c), 1, fc ) == 1 ){

	    if( strcmp( c.name, temp_cat) == 0 ){

			printf("\n\n");
			printf("                               .....................Category Selected....................\n\n");
            strcpy(b.category,temp_cat);
			findrecord = 1;
			fclose(fc);
            break;
	    }
	}
	fclose(fc);

	if( findrecord != 1 ){
        printf("\a\n\nCategory Not Found\n\nPlease Enter The Credentials Again\n\n");
        getch();
        addbook();
	}

	printf("        BOOK NAME : ");

	gets(b.name);
	fflush(stdin);

	printf("        BOOK AUTHOR : ");

	gets(b.author);
    fflush(stdin);

	printf("        RACK NO : ");
	scanf("%d",&b.rack);

	printf("        QUANTITY : ");
	scanf("%d", &b.quantity);

	printf("        PRICE : ");
	scanf("%d", &b.price);

    //for testing
	//printf(" %d %s %s %d %d %d ",b.id,b.name,b.author,b.rack,b.quantity,b.price);

	return 1;
}



void addbook(void){

	system("cls");


	if( getdata() == 1 ){

        fp = fopen( "books.txt", "a" );
        if( fp == NULL ){
                printf("File open failed");
                getch();
                mainmenu();
        }else{
            fseek(fp,0,SEEK_END);
            fwrite( &b,sizeof(b),1,fp );
            fclose(fp);
            printf("\n\n");
            printf("The Book Is Successfully Added !!\n\n");
            printf("Save any more?(Y / N): ");

            if(getch()=='n'){
                fclose(fp);
                mainmenu();
            }else{
                system("cls");
                addbook();
            }
        }
    }

}




void viewbooklist(void){

    system("cls");
    printf("\n\n");
    printf("                              ********************** Book List**********************\n\n\n");
    printf("\tId\t\tName\t\t\tAuthor\t\tRack No\t\tQuantity\tPrice\n");

    fp = fopen("books.txt","r");

    if( fp == NULL ){

        printf("\n\n\nFile opening failed!! or You may not have added any books yet");
        getch();
        mainmenu();

    }else{

        while( fread( &b, sizeof(b) ,1 ,fp ) == 1 ){

            printf("\t%d\t\t", b.id);
            printf("%s\t\t", b.name);
            printf("%s\t\t", b.author);
            printf("%d\t\t", b.rack);
            printf("%d\t\t", b.quantity);
            printf("%d\t\t", b.price);
            printf("\n");

        }
    }

    fclose(fp);

    printf("\n\n\nPress any key to go back......");

    if(getch()){
        mainmenu();
    }

}

void deletebook(void) {

	system("cls");
    int d;
    char another='y';
    int findrecord;

    while( another == 'y' ) {  //infinite loop

	system("cls");
	printf("                Enter The Book ID To Delete :");
	scanf("%d",&d);

	fp = fopen("books.txt","r+");
	rewind(fp);

	while( fread( &b,sizeof(b),1,fp ) == 1 ){

	    if( b.id == d ){

			printf("\n\n");
			printf("                               .....................The Book Record Is Available....................\n\n");
			printf("               Book Name Is: %s\n\n", b.name);
			printf("               Book Rack no is: %d\n\n", b.rack);
			findrecord = 1;

	    }
	}
	if( findrecord != 1 ){

	    printf("                                    .........................No record is found please modify the search..........................\n\n");
	    if(getch())
	    mainmenu();
	}
	if( findrecord == 1 ) {

	    printf("Do You Want To Delete The Record ? (Y/N) \n\n");
	    if(getch()=='y') {

			ft = fopen( "test1.txt","w" );  //temporary file for delete
			rewind(fp);

			while( fread( &b,sizeof(b),1,fp ) == 1 ) {

		    	if(b.id!=d){
					fseek(ft,0,SEEK_CUR);
					fwrite(&b,sizeof(b),1,ft); //write all in temporary file except that
		    	}                              //we want to delete
			}
			fclose(ft);
			fclose(fp);
			remove("books.txt");
			rename("test1.txt","books.txt"); //copy all item from temporary file to fp except that
			//fp=fopen("books.txt","r");    //we want to delete

			if( findrecord == 1 ){

		    	printf("        THE BOOK RECORD IS SUCCESSFULLY DELETED.\n\n");
		    	printf("        Delete Another BOOK Record ? (Y/N) : ");
			}
	    }
		else
		mainmenu();
		fflush(stdin);
		another=getch();
	}
}
mainmenu();
}

/*
    int id;

    char name[50];
    char category[50];
    char author[50];

    int rack;
    int quantity;
    int price;
*/

void searchbook(void){

    system("cls");
    int d;
    char findrecord;
    printf("                                          *****************************Search BOOK Record*********************************\n\n");
    printf("                  Enter Book Id\n");

    scanf("%d",&d);
    printf("\n\n");
    printf("Searching........");

    fp = fopen("books.txt", "r");

    while( fread( &b, sizeof(b), 1, fp ) == 1 ){

        if(b.id == d){

            printf("\n\n");
            printf("...........................The Book Record is available............................\n\n");
            printf("       ID : %d\n\n",b.id);
            printf("       Name : %s\n\n",b.name);
            printf("       Author : %s\n\n",b.author);
            printf("       Rack No : %d\n\n",b.quantity);
            printf("       Quantity : %d\n\n",b.rack);
            printf("       Price : %d\n\n",b.price);

            findrecord='t';
        }

    }
    if( findrecord!='t' ){  //checks whether conditiion enters inside loop or not

        printf("\aNo Record Found\a");
    }

    printf("Try Another Search ? (y/n)");

    if( getch()=='y' ){
        searchbook();
    }else{
        mainmenu();
    }


}

void addcategory(void){

    system("cls");
    printf("\n\tEnter Category Name: ");
    fflush(stdin);
    gets(c.name);

    fc = fopen("categories.txt","a");

    if( fc == NULL ){
        printf("File opening failed!!");
        getch();
        mainmenu();

    }else{

        fwrite( &c, sizeof(c), 1, fc);
        fclose(fc);
        printf("\n\n");
        printf("The Category Is Added Successfully !!\n\n");
        printf("Save any more?(Y / N): ");

        if(getch()=='n'){
                //fclose(fc);
            mainmenu();
        }else{
            system("cls");
            addcategory();
        }
    }




}


void viewcategories(void){

    system("cls");
    int i=0;
    printf("\n\n");
    printf("                              ********************** Category List **********************\n\n\n");
    printf("\tNo\t\tName\n");

    fc = fopen("categories.txt","r");

    if( fc == NULL ){
        printf("File opening failed!! or You may not have added categories yet");
        getch();
        mainmenu();

    }else{

        while( fread( &c, sizeof(c) ,1 ,fc ) == 1 ){

            printf("\t%d\t\t", i);
            printf("%s\t\t", c.name);
            printf("\n");
            i++;

        }

        fclose(fc);

        printf("\n\n\nPress any key to go back......");

        if( getch() ){
            mainmenu();
        }
    }

}
void deletecategory(void){
    system("cls");
    char d[50];
    char another='y';
    int findrecord;


	system("cls");
	printf("\n                Enter The Category Name To Delete :  ");
	fflush(stdin);
	gets(d);
	//scanf("%d",&d);

	fc = fopen("categories.txt", "r+");
	rewind(fc);

	while( fread( &c, sizeof(c), 1, fc ) == 1 ){

	    if( strcmp( c.name, d) == 0 ){

			printf("\n\n");
			printf("                               .....................The Category Record Is Available....................\n\n");
			findrecord = 1;

	    }
	}
	if( findrecord != 1 ){

	    printf("                                    .........................No record is found modify the search..........................\n\n");
	    if(getch())
	    mainmenu();
	}
	if( findrecord == 1 ) {

	    printf("Do You Want To Delete The Record ? (Y/N) \n\n");
	    if( getch() == 'y' ) {

			ft = fopen( "test1.txt","w" );  //temporary file for delete
			rewind(fc);

			while( fread( &c,sizeof(c),1,fc ) == 1 ) {

		    	if( strcmp( c.name, d) != 0 ){

					fseek(ft, 0, SEEK_CUR);

					fwrite(&c,sizeof(c),1,ft); //write all in temporary file except that
		    	}                              //we want to delete
			}

			fclose(ft);
			fclose(fc);
			remove("categories.txt");
			rename("test1.txt","categories.txt"); //copy all item from temporary file to fc except that

	    }

		printf("\n\tCategory Deleted Successfully!\n\tPress any key to go back...");
		fflush(stdin);
		getch();
		mainmenu();
	}

mainmenu();
}




int password(void){

    char usrpass[50];
    char dbpass[50];

    printf("\n\n\n\t\t****************************** PASSWORD PROTECTED ******************************\n\n");
    printf("\n\t\tEnter Your Password:  ");

    fflush(stdin);
    gets(usrpass);

    fpp = fopen("password.txt","r");

    if( fpp == NULL ){
        printf("File open Failed");
    }else{
        fscanf(fpp,"%s", dbpass);
        //printf("%s", dbpass);

        if( strcmp(usrpass,dbpass) == 0 ){
            return 1;
        }
        fclose(fpp);
    }

    return 0;

}
void changepassword(){

    system("cls");

    char usrpass[50], dbpass[50];

    int status;

    printf("\n\t\t****************************** PASSWORD CHANGE AREA ******************************\n\n");
    printf("\n\t\tEnter Your Old Password:  ");

    fflush(stdin);
    gets(usrpass);

    fpp = fopen("password.txt","r");

    if( fpp == NULL ){
        printf("File open Failed");
    }else{
        fscanf(fpp,"%s", dbpass);
        //printf("%s", dbpass);

        if( strcmp(usrpass,dbpass) == 0 ){
            status = 1;
        }
        fclose(fpp);
    }

    if( status == 1 ){

        fpp = fopen("password.txt","w");

        if( fpp == NULL ){
            printf("File open Failed");
        }else{

            printf("\n\t\t*****Password Matched*****\n\n");
            printf("\n\t\tEnter New Password:  ");

            fflush(stdin);
            gets(usrpass);

            fprintf(fpp,"%s", usrpass);
            //printf("%s", dbpass);
            fclose(fpp);
            printf("\n\t\t*****Password change successful*****\n\n");

            getch();
            main();
        }


    }else{
        printf("\n\n\t\t!!!!!Password Didn't Match!! Program Terminating!!!!!\n");
    }

}

void aboutus(){

    system("cls");

    printf("\n******Library Management System******\n");
    printf("\n\nHere's a simple library management system made by:");
    printf("\n\n1. Nibir Ahmed:");
    printf("\nID: 2011333642");
    printf("\n\n2. Maliha Anzum Maisha:");
    printf("\nID: 2011380642");
    printf("\n\n3. Tasin Ahmed Toha:");
    printf("\nID: 2011664642\n\n");

}


















