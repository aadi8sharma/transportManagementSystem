#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"

struct customer_record
{
    int customer_order_id;
    char pickup[100];
    char item[100];
    char destination[100];
    int quantity;
    char customer_ID[ID_PASS_MAX];
}record, read_co;

void add_order(char cus_id[ID_PASS_MAX])
{    
    FILE *ptr1;
    ptr1=fopen("orders.csv","a+");
    if (ptr1==NULL)
    {
        printf("Error opening file.");
    }
    else
    {
    strcpy(record.customer_ID, cus_id);
    int line_count=0;
    char buffer[100],ch;
    fseek(ptr1,0,SEEK_SET);
    //Counting the number of lines in the file already present. 
    while ((ch = fgetc(ptr1)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }
    fseek(ptr1,0,SEEK_SET);
    int index;
    char buffer1[100];
    if (line_count==0)
    index=line_count;
    else if(line_count==1)
    {
        fgets(buffer1,100,ptr1);
        index=atoi(buffer1);
    }
    else
    {
    for (int i=0;i<line_count-1;i++)
    {
        fgets(buffer,100,ptr1);
        fscanf(ptr1,"%s",buffer1);
    }
    index=atoi(buffer1);
    }

    fseek(ptr1,0,SEEK_SET);
    //Used to use up the \n character so that fgets() function can work properly
    while ((getchar()) != '\n');


    char item[100],destination[100],pickup[100];
    //Input of the pickup location
    printf("Enter the pickup location:");
    fgets(add_o.pick_loc,100,stdin);
    //Used to remove the \n inputed during entering of the "pickup" string
    if (add_o.pick_loc[strlen(add_o.pick_loc)-1]=='\n')
    add_o.pick_loc[strlen(add_o.pick_loc)-1]='\0';
    //Input of items to be ordered
    printf("Enter the item to be ordered:");
    fgets(add_o.item,100,stdin);
    if (add_o.item[strlen(add_o.item)-1]=='\n')
    add_o.item[strlen(add_o.item)-1]='\0';
    //Input of quantity of items to be ordered
    printf("Enter the quantity of the item:");

    scanf("%d",&add_o.quantity); 
    //Input of destination of the order
    printf("Enter the destination:");
    while ((getchar()) != '\n');
    fgets(add_o.del_dest,100,stdin);
    if (add_o.del_dest[strlen(add_o.del_dest)-1]=='\n')
    add_o.del_dest[strlen(add_o.del_dest)-1]='\0';
    
    //Customer order id is taken as 1 greater than index
    record.customer_order_id=index+1;
    fprintf(ptr1,"%d|%s|%s|%d|%s|%s\n",record.customer_order_id,add_o.pick_loc,add_o.item,add_o.quantity,add_o.del_dest, record.customer_ID);
    fprintf(ptr1,"\n");
    printf("\nOrder has been placed!\n");
    fclose(ptr1);
    }
}

void view_orders(char cus_id[ID_PASS_MAX])
{
    FILE *ptr=fopen("orders.csv","r+");
    system("cls");
    printf("\n\t\t\t\t\t\t\tYOUR ORDERS");
    printf("\n\n\tOrder ID\t\tPickup Location\t\tItem Name\t\tQuantity\t\tDestination\n\n");
    while(fscanf(ptr, "%d|%99[^|]|%99[^|]|%d|%99[^|]|%19[^\n]\n", &read_co.customer_order_id, read_co.pickup, read_co.item, &read_co.quantity, read_co.destination, read_co.customer_ID) != EOF)
    {
        if(strcmp(cus_id, read_co.customer_ID) == 0)
        {
            printf("\t%d\t\t%s\t\t%s\t\t%d\t\t%s\n", read_co.customer_order_id, read_co.pickup, read_co.item, read_co.quantity, read_co.destination);
        }
    }
}

void view_order(char index[2000])
{
    FILE *ptr=fopen("File.csv","r");
    char ch;
    int chk=0;
    while ((ch=fgetc(ptr))!=EOF)
    {
        if (ch=='\n')
        {
            char ch2[2000];
            fscanf(ptr,"%s",ch2);
            if (strcmp(index,ch2)==0)
            {
                ch=fgetc(ptr);
                printf("%s ",ch2);
                while (ch!='\n')
                {
                    ch=fgetc(ptr);
                    printf("%c",ch);
                }
                chk=1;
            }
        }
    }
    char ch3;
    if (chk==0)
    {
        char ch2[2000];
        fseek(ptr,0,SEEK_SET);
        fscanf(ptr,"%s",ch2);
        if (strcmp(index,ch2)==0)
        {
            printf("%s",ch2);
            while (ch3!='\n')
            {
                ch3=fgetc(ptr);
                printf("%c",ch3);
                chk=1;
            }
        }
    }
    if (chk==0)
    printf("Invalid Customer ID entered");
    fclose(ptr);
}

void deleteOrderByOrderNumber(int orderNumber) {
    FILE *inputFile = fopen("File.csv", "r");
    FILE *tempFile = fopen("Temp.csv", "w");

    if (inputFile == NULL || tempFile == NULL) {
        printf("Error opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char line[200];
    int currentOrderNumber;
    int found = 0;

    while (fgets(line, sizeof(line), inputFile) != NULL) {
        sscanf(line, "%d", &currentOrderNumber);

        // Check if the order number matches the one to be deleted
        if (currentOrderNumber == orderNumber) {
            found = 1;
            continue; // Skips writing the line to the temp file
        }

        fputs(line, tempFile); // Write the line to the temporary file
    }

    fclose(inputFile);
    fclose(tempFile);

    if (found == 0) {
        printf("Order number not found in the file.\n");
    } else {
        remove("orders.csv"); // Delete the original file
        rename("Temp.csv", "orders.csv"); // Rename the temp file to the original file
        printf("Order successfully deleted.\n");
    }
}


