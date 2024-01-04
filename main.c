#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

COORD coord= {0,0};

void Gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

// definition struct
struct products{
    char nameOfpro[50];
    int price;
    int quantity;
};
typedef struct products products;

struct category{
    char nameOfcategory[50];
    int countPro;
    products* pro;
};
typedef struct category category;

struct superMarket{
    category* cat;
    int countCat;
};
typedef struct superMarket superMarket;
//start functions

 void initialize(superMarket* market)
 {
     printf("This is Our Category & Product in store.\n");
     market->countCat=3;
     market->cat=malloc(100*sizeof(category));
     for(int i=0; i<3; i++)
     {
         market->cat[i].pro=malloc(3*sizeof(products));
         market->cat[i].countPro=2;
     }
     strcpy(market->cat[0].nameOfcategory,"Canned");
    strcpy(market->cat[1].nameOfcategory,"Dairy") ;
    strcpy(market->cat[2].nameOfcategory,"Fish");

    strcpy(market->cat[0].pro[0].nameOfpro,"sauce");
    strcpy(market->cat[0].pro[1].nameOfpro,"bean");
    strcpy(market->cat[1].pro[0].nameOfpro,"Cheese");
    strcpy(market->cat[1].pro[1].nameOfpro,"Milk");
    strcpy(market->cat[2].pro[0].nameOfpro,"tuna");
    strcpy(market->cat[2].pro[1].nameOfpro,"salmon");

    market->cat[0].pro[0].price=100;
    market->cat[0].pro[1].price=150;
    market->cat[1].pro[0].price=200;
    market->cat[1].pro[1].price=100;
    market->cat[2].pro[0].price=300;
    market->cat[2].pro[1].price=130;

    market->cat[0].pro[0].quantity=10;
    market->cat[0].pro[1].quantity=15;
    market->cat[1].pro[0].quantity=2;
    market->cat[1].pro[1].quantity=10;
    market->cat[2].pro[0].quantity=4;
    market->cat[2].pro[1].quantity=5;


 }

//show your category and products
 void Display(superMarket* market)
 {
    for(int i=0; i<market->countCat; i++)
    {
        printf("--> The Name of Category is %s .\n",market->cat[i].nameOfcategory);
        for(int j=0; j<market->cat[i].countPro; j++)
        {
            printf("%d the Product is: %s ,its Cost %d and its Quantity %d \n",j+1, market->cat[i].pro[j].nameOfpro,market->cat[i].pro[j].price,market->cat[i].pro[j].quantity);

        }
        printf("\t----------------------------------------------------------------------------\n");
    }
 }

//add Category
 void addCategory(superMarket* market)
 {
     printf("\t\"Create New Category\" \n\n");
     if(market->countCat<100)
     {
         int index =-1;
         char categoryy[20];
         printf("Pleas enter the name of Category: \n");
         scanf("%s",categoryy);
         for(int i=0; i< market->countCat; i++)
        {
            if(strcmp(market->cat[i].nameOfcategory,categoryy)==0)
            {
                index=i;
                break;
            }
        }
           // printf("%d",index);
            if(index==-1)
            {
                strcpy(market->cat[market->countCat].nameOfcategory,categoryy);
                 market->cat[market->countCat].pro=malloc(3*sizeof(products));
                market->cat[market->countCat].countPro=0;
                market->countCat++;
                printf("This Category is added successful.\n");
            }
            else
            {
                         printf("the is exist. \n");

            }


     }
     else{
        printf("No Space to add!! \n");
     }

 }


//remove category
void removeCategory(superMarket* market)
{
    printf("\t\"Delete Catrgory\" \n\n");
    printf("What Category you want to remove??");
    char categoryy[20];
    scanf("%s",categoryy);
    int index=-1;
    if(market->countCat > 0)
    {
        for(int i=0; i<market->countCat; i++)
        {
            if(strcmp(market->cat[i].nameOfcategory,categoryy)==0)
            {
                index=i;
                break;
            }
        }
            if(index!=-1)
            {
                for(int i=index; i<market->countCat-1; i++)
                {
                    market->cat[i]=market->cat[i+1];
                }
                    market->countCat--;
                    printf("The Category is deleted.\n");

            }
        }

    else{
        printf("This Category is not found!!\n");
    }
}

// add product

void addProduct(superMarket* market)
{
    printf("\t\"Create New Product\" \n\n");
    char categoryName[20],ProductName[20];
    int price,quantity;
    int indexCat=-1;
    int indexrPro=-1;
    printf("\nThis Our Category. \n");
    for(int i; i<market->countCat; i++)
    {
        printf("%d)%s \n",i+1,market->cat[i].nameOfcategory);
    }
    printf("Select The Category Name :");
    scanf("%s",categoryName);
    for(int i=0; i<market->countCat; i++)
    {
        if(strcmp(market->cat[i].nameOfcategory,categoryName)==0)
        {
            indexCat=i;
            break;
        }
    }

    if(indexCat!=-1)
    {
        if(market->cat[indexCat].countPro<3)
        {
            printf("Enter The Name of Product ");
            scanf("%s",ProductName);
            for(int i=0; i<market->cat[indexCat].countPro; i++)
            {
                if(strcmp(market->cat[indexCat].pro[i].nameOfpro,ProductName)==0)
                {
                    indexrPro=i;
                    break;
                }
            }

            if(indexrPro!=-1)
            {
                printf("The Product is Already Exist\n");
                printf("Do you want to edit it??if you want to edit,please Enter one. Else Enter zero.\n");
                int Check;
                //printf("if you want to edit,please Enter Yes. Else Enter No \n");
                scanf("%d",&Check);
                if(Check==1)
                {
                    printf("Enter New Price..");
                    scanf("%d",&price);
                    printf("Enter New Quantity..");
                    scanf("%d",&quantity);
                    market->cat[indexCat].pro[indexrPro].price=price;
                    market->cat[indexCat].pro[indexrPro].quantity=quantity;
                    printf("Update New Data Successfully \n");
                }
                else if (Check==0)
                {
                    printf("Good \n");
                }
            }
            else{
                printf("You added The Product`s Name ,Now Enter it`s Price:");

                scanf("%d",&price);
                printf("quantity ");
                scanf("%d",&quantity);

                strcpy(market->cat[indexCat].pro[market->cat[indexCat].countPro].nameOfpro,ProductName);
                market->cat[indexCat].pro[market->cat[indexCat].countPro].price=price;
                market->cat[indexCat].pro[market->cat[indexCat].countPro].quantity=quantity;
                market->cat[indexCat].countPro++;
                printf("Added successfully");

            }

        }

        else{
            products* newPro=malloc((market->cat[indexCat].countPro+2)*sizeof(products));
            for(int i=0; i<market->cat[indexCat].countPro; i++)
            {
                newPro[i]=market->cat[indexCat].pro[i];
            }
            free(market->cat[indexCat].pro);
            market->cat[indexCat].pro=newPro;
            printf("Now Enter your Product Name..");
            scanf("%s",ProductName);
               for(int i=0; 0<market->cat[indexCat].countPro; i++)//why use for again??
            {
                if(strcmp(market->cat[indexCat].pro[i].nameOfpro,ProductName)==0)
                {
                    indexrPro=0;
                    break;
                }
            }

             if(indexrPro!=-1)
            {
                printf("The Product is Already Exist\n");
                printf("Do you want to edit it?? \n");
                char Check[5];;
                printf("if you want to edit,please Enter Yes. Else Enter No .\n");
                scanf("%s",Check);
                if(Check=='Yes')
                {
                    printf("Enter New Price: ");
                    scanf("%s",price);
                    printf("Enter New Quantity: ");
                    scanf("%s",quantity);
                    market->cat[indexCat].pro[indexrPro].price=price;
                    market->cat[indexCat].pro[indexrPro].quantity=quantity;
                    printf("Update New Data Successfully .\n");
                }
                else if (Check=='No')
                {
                    printf("Good job.\n");
                }
            }
            else{
                printf("You added The Product`s Name ,Now Enter it`s Price:");
                scanf("%d",price);
                printf("\n Enter Quantity :");
                scanf("%d",quantity);

                strcpy(market->cat[indexCat].pro[market->cat[indexCat].countPro].nameOfpro,ProductName);
                market->cat[indexCat].pro[market->cat[indexCat].countPro].price=price;
                market->cat[indexCat].pro[market->cat[indexCat].countPro].quantity=quantity;
                market->cat[indexCat].countPro++;
                printf("Added successfully.");

            }

        }
    }
    else{
        printf("This category not Exist.\n");
    }
}

//remove product

void removeProduct(superMarket* market)
{
    printf("\t\"Delete Product\" \n\n");
    char categoryName[20],ProductName[20];
    int indexCat=-1;
    int indexrPro=-1;
    printf("Enter the Product Name which you want to delete :\n");
    scanf("%s",ProductName);
    printf("Enter the Category Name which you want to delete product in it: \n");
    scanf("%s",categoryName);
    for(int i; i<market->countCat; i++)
    {
        if(strcmp(market->cat[i].nameOfcategory,categoryName)==0)
        {
            indexCat=i;
            break;
        }
    }

    if(indexCat!=-1)
    {
        for(int i=0; i<market->cat[indexCat].countPro; i++)
        {
            if(strcmp(market->cat[indexCat].pro[i].nameOfpro,ProductName)==0)
            {
                indexrPro=i;
                break;
            }
        }

        if(indexrPro!=-1)
        {
            for(int i=0; i<market->cat[indexCat].countPro-1; i++)
        {
            market->cat[indexCat].pro[i]=market->cat[indexCat].pro[i+1];
        }
        market->cat[indexCat].countPro--;
        printf("Product removed successfully. \n");
       }
        else{
            printf("This product not found in this category.");
        }
            }

    else{
        printf("This Category is not found.\n");
    }


}

//sell

void sellProduct(superMarket* market)
{
    printf("\t\"Sell Product\" \n\n");
    char categoryName[20],ProductName[20];
    int catIndex=-1,proIndex=-1;
    printf("Enter the product name..\n");
    scanf("%s",ProductName);
    printf("Enter the categoryName..\n");
    scanf("%s",categoryName);


    for(int i=0; i<market->countCat; i++)
    {
        if(strcmp(market->cat[i].nameOfcategory,categoryName)==0)
        {
            catIndex=i;
            break;
        }
    }

    if(catIndex!=-1)
    {
        for(int i=0; i<market->cat[catIndex].countPro; i++)
        {
            if(strcmp(market->cat[catIndex].pro[i].nameOfpro,ProductName)==0)
            {
                proIndex=i;
                break;
            }
        }
        if(proIndex!=-1)
        {
            int quatitySell;
            printf("Enter the quantity you want to sell:\n");
            scanf("%d",&quatitySell);
            if(quatitySell<market->cat[catIndex].pro[proIndex].quantity)
            {
                market->cat[catIndex].pro[proIndex].quantity=quatitySell;
                printf("Mission Done\n");
            }
            else{
                printf("Sorry You can`t sell,enter quantity less than %d %n.",market->cat[catIndex].pro[proIndex].quantity);

            }
        }

        else{
            printf("this product not exist\n");
        }
    }

    else{
        printf("this category not exist\n");
    }
}

//move

void MoveProduct(superMarket* market)
{
    printf("\t\"Move Product\" \n\n");
    char TOcategoryName[20],FROMcategoryName[20],productName[20];
    int fromCate=-1,toCate=-1,proIndex=-1;
    printf("Enter Category Name which product in it and you want to change the location:\n");
    scanf("%s",FROMcategoryName);

    for(int i=0; i<market->countCat; i++)
    {
        if(strcmp(market->cat[i].nameOfcategory,FROMcategoryName)==0)
        {
            fromCate=i;
            break;
        }
    }


        if(fromCate!=-1)
        {
            printf("Enter the Product name:\n");
            scanf("%s",productName);
            for(int i=0; i<market->cat[fromCate].countPro; i++)
            {
                if(strcmp(market->cat[fromCate].pro[i].nameOfpro,productName)==0)
                {
                    proIndex=i;
                    break;
                }
            }
        }
        else{
            printf("This Category not found.\n");
        }

        if(proIndex!=-1)
        {
            printf("Enter Category Name you want to go:\n");
            scanf("%s",TOcategoryName);
             for(int i=0; i<market->countCat; i++)
                {
                    if(strcmp(market->cat[i].nameOfcategory,TOcategoryName)==0)
                    {
                        toCate=i;
                        break;
                    }
                }

        }
        else
        {
            printf("This Product not found.\n");
        }
        if(toCate!=-1)
        {
               if(market->cat[toCate].countPro<100)
               {
                   market->cat[toCate].pro[market->cat[toCate].countPro]= market->cat[fromCate].pro[proIndex];
                   market->cat[toCate].countPro++;
                   for(int i=0; i<market->cat[fromCate].countPro-1; i++)
                   {
                       market->cat[fromCate].pro[i]=market->cat[fromCate].pro[i+1];

                   }
                   market->cat[fromCate].countPro--;
               }
        }
        else{
            printf("this category not found.\n");
        }

}

int main()
{
    superMarket s;
    superMarket *ptr=&s;
    superMarket sup;

  initialize(ptr);

    int selection =0;
    while(1)
    {


        system("cls");

        Gotoxy(40,3);
        SetColor(15);
        printf("\"Hello in Our Super Market\"\n");
        Gotoxy(40,7);
        if(selection==0)
        {
            SetColor(11);
            printf("-->Display Super Market product and category");
            SetColor(15);
        }
        else
        {

            printf("   Display Super Market product and category   ");
        }
        Gotoxy(40,9);
        if(selection==1)
        {
            SetColor(11);
            printf("-->Add Category");
            SetColor(15);
        }
        else
        {

            printf("   Add Category   ");
        }
        Gotoxy(40,10);
        if(selection==2)
        {
            SetColor(11);
            printf("-->Add Product");
            SetColor(15);
        }
        else
        {

            printf("   Add Product   ");
        }
        Gotoxy(40,12);
        if(selection==3)
        {
            SetColor(11);
            printf("-->Remove Category");
            SetColor(15);

        }
        else
        {

            printf("   Remove Category   ");
        }
        Gotoxy(40,13);
        if(selection==4)
        {
            SetColor(11);
            printf("-->Remove Product");

            SetColor(15);

        }
        else
        {

            printf("   Remove Product   ");
        }
        Gotoxy(40,15);
        if(selection==5)
        {
            SetColor(11);
            printf("-->Move Product from Category to Category");
            SetColor(15);

        }
        else
        {

            printf("   Move Product from Category to another   ");
        }
        Gotoxy(40,16);
        if(selection==6)
        {
            SetColor(11);
            printf("-->Sell Products");
            SetColor(15);

        }
        else
        {

            printf("   Sell Products   ");
        }
        Gotoxy(40,18);
        if(selection==7)
        {
            SetColor(20);
            printf("-->Exit");
            SetColor(15);

        }
        else
        {

            printf("  Exit   ");
        }





        char key;
        key=_getch();
        switch(key)
        {
        //  _getch();

        case 72:
            if(selection<=0)
            {
                selection=7;
            }
            else
            {
                selection--;
            }
            break;
        case 80:
            if(selection>=7)
            {
                selection=0;
            }
            else
            {
                selection++;
            }
            break;


        case 13:
            switch(selection)
            {
            case 0:
                system("cls");
                Display(ptr);
                _getch();
                break;
            case 1:
                system("cls");
                addCategory(ptr);
                _getch();
                break;
            case 2:
                system("cls");
                addProduct(ptr);
                _getch();
                break;
            case 3:
                system("cls");
                removeCategory(ptr);
                _getch();
                break;
            case 4:
                system("cls");
                removeProduct(ptr);
                _getch();
                break;
            case 5:
                system("cls");
                MoveProduct(ptr);
                _getch();
                break;
            case 6:
                system("cls");
                sellProduct(ptr);
                _getch();
                break;
            case 7:
                system("cls");
                return 0;
                break;

            }

        }

    }


    //freeMemory(s);
    return 0;
}






