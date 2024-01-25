/*Ava Wiggins
finalProject
due 12/9/23
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 2048

/*In this section you will offer the user to add,remove or alter an inventory item.
Adding an item will include all attribute values while removing an item will delete the item from the database.
Altering an item will offer the chance to change the price or quantity on hand manually.*/

/*INTRODUCTION TO THE DATABASE*/
float introduction()
{
    printf("Hello! You are welcome to make a transaction using this application.\nChoose your action below!\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/*UPDATING ITEM DATABASE*/
float updateDatabase()
{
    /*start with adding items to the database*/
    FILE *filePTR;

    char itemID[20];
    char itemName[20];
    char itemPrice[20];
    char itemQuantity[20];
    printf("Enter Item ID: ");
    gets(itemID);
    printf("Enter Item Name: ");
    gets(itemName);
    printf("Add Item Unit Price: ");
    gets(itemPrice);
    printf("Item Quantity: ");
    gets(itemQuantity);
    filePTR = fopen("database.txt", "a");

    fprintf(filePTR, "%s %s %s %s\n", itemID, itemName, itemPrice, itemQuantity);

    fclose(filePTR);
}

/*ALTERING AN ITEM*/
float alterItem()
{
    printf("If you would like to alter an Item, enter database.txt as the filename\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    FILE *file, *temp;
    char filename[FILENAME_SIZE];
    char buffer[MAX_LINE];
    char replaceId[20];
    char replaceIdNew[20];
    char replaceName[MAX_LINE];
    char replacePrice[MAX_LINE];
    char replaceQuantity[MAX_LINE];

    printf("File: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("Replace Item, Enter Item ID: ");
    scanf("%s", replaceId);
    getchar();

    printf("Enter new Item ID: ");
    scanf("%s", replaceIdNew);
    getchar();

    printf("Enter new Item Name: ");
    fgets(replaceName, MAX_LINE, stdin);
    replaceName[strcspn(replaceName, "\n")] = '\0';

    printf("Enter new Item Unit Price: ");
    fgets(replacePrice, MAX_LINE, stdin);
    replacePrice[strcspn(replacePrice, "\n")] = '\0';

    printf("Enter new Item Quantity: ");
    fgets(replaceQuantity, MAX_LINE, stdin);
    replaceQuantity[strcspn(replaceQuantity, "\n")] = '\0';

    temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    bool itemReplaced = false;

    while (fgets(buffer, MAX_LINE, file))
    {
        char currentItemId[20];
        if (sscanf(buffer, "%19s", currentItemId) != 1)
        {
            // Handle invalid input
            continue;
        }

        if (strcmp(currentItemId, replaceId) == 0)
        {
            fprintf(temp, "%s %s %s %s\n", replaceIdNew, replaceName, replacePrice, replaceQuantity);
            itemReplaced = true;
        }
        else
        {
            fputs(buffer, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (!itemReplaced)
    {
        remove("temp.txt");
        printf("Item with ID %s not found.\n", replaceId);
        return;
    }

    remove(filename);
    rename("temp.txt", filename);

    printf("Item with ID %s replaced successfully.\n", replaceId);
}

/*REMOVING AN ITEM*/
float removeItem()
{

    printf("If you would like to remove an Item, enter database.txt as the filename\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FILE *file, *temp;

    char filename[FILENAME_SIZE];
    char temp_filename[FILENAME_SIZE];

    char buffer[MAX_LINE];
    char deleteItemId[20];

    printf("File: ");
    scanf("%s", filename);

    strcpy(temp_filename, "temp____");
    strcat(temp_filename, filename);

    printf("Delete Item with ID: ");
    scanf("%s", deleteItemId);

    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error opening file(s)\n");
        return 1;
    }

    char currentItemId[20];

    while (fgets(buffer, MAX_LINE, file))
    {

        sscanf(buffer, "%s", currentItemId);

        if (strcmp(currentItemId, deleteItemId) != 0)
        {
            fputs(buffer, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename(temp_filename, filename);

    printf("Item with ID %s removed successfully.\n", deleteItemId);
}

/*PURCHASING AN ITEM*/
float purchaseItem()
{
    char itemName[20];
    float itemQuantity;
    float itemPrice;
    float sum;
    printf("Enter the name of the item you would like to purchase: ");
    scanf("%s", itemName);
    printf("Enter the quantity: ");
    scanf("%f", &itemQuantity);
    printf("Enter the item price: ");
    scanf("%f", &itemPrice);
    sum = itemQuantity * itemPrice;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "                 Receipt                  \n");
    printf("          Your total is %.2f\n", sum);
    printf("		Thank you!              \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    return sum;
}

float viewInventory()
{
    FILE *fileptr;
    char open;
    fileptr = fopen("database.txt", "r");

    do
    {
        open = fgetc(fileptr);
        printf("%c", open);
    } while (open != EOF);

    fclose(fileptr);
}

/*SEARCH FOR AN ITEM*/
float search()
{

    printf("If you would like to search an Item, enter database.txt as the filename\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    FILE *fileptr;
    char filename[FILENAME_SIZE];
    char search[20];
    char buffer[MAX_LINE];

    printf("Enter the filename: ");
    scanf("%s", filename);
    fileptr = fopen(filename, "r");

    printf("Enter the item you would like to search for: ");
    scanf("%s", search);
    getchar();

    bool wordFound = false;

    while (fgets(buffer, MAX_LINE, fileptr) != NULL)
    {
        if (strstr(buffer, search) != NULL)
        {
            printf("Word '%s' found in the database:\n", search);
            printf("%s", buffer);
            wordFound = true;
            break;
        }
    }

    fclose(fileptr);

    if (!wordFound)
    {
        printf("Word '%s' not found in the file.\n", search);
    }

    return 0;
}

/*TOTAL PRICE OF ITEMS SOLD*/
float soldItems()
{
    char itemName[20];
    float itemQuantity;
    float itemPrice;
    float sum;
    printf("View item invetory to check quantity and price of an item\n");
    printf("What item would you like to check the funds of?: ");
    scanf("%s", itemName);
    printf("What is that items quantity?: ");
    scanf("%f", &itemQuantity);
    printf("What is the unit price of the item?: ");
    scanf("%f", &itemPrice);
    sum = itemQuantity * itemPrice;
    printf("The total funds of the item is %.2f", sum);
    return sum;
}

/*MENU SELECTION*/
float databaseSelection()
{
    int userPick;
    printf("\t\t\t      Main Menu\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "1. Add an item => Item ID, Item Name, Item Unit Price and Item Quantity\n"
           "2. Alter an Item\n"
           "3. Remove an Item\n"
           "4. Purchase an Item\n"
           "5. View Invnetory\n"
           "6. Search Inventory\n"
           "7. Sold Items\n"
           "8. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &userPick);
    getchar();
    /*operation*/
    if (userPick == 1)
    {
        printf("You picked to add an item\n");
        userPick = updateDatabase();
    }
    else if (userPick == 2)
    {
        printf("You picked to alter an item\n");
        userPick = alterItem();
    }
    else if (userPick == 3)
    {
        printf("You picked to remove an item\n");
        userPick = removeItem();
    }
    else if (userPick == 4)
    {
        printf("You picked to purchase an item\n");
        userPick = purchaseItem();
    }
    else if (userPick == 5)
    {
        printf("You picked to view invetory\n");
        userPick = viewInventory();
    }
    else if (userPick == 6)
    {
        printf("You picked to search inventory\n");
        userPick = search();
    }
    else if (userPick == 7)
    {
        printf("You picked to view the total value of the items\n");
        userPick = soldItems();
    }
    else
    {
        printf("Goodbye");
    }
    return userPick;
}

/*FUNCTION CALLS*/
int main()
{

    introduction();
    databaseSelection();
    return 0;
}
