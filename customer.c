#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct customer_record
{
    int customer_order_id;
    char pickup[2000];
    char item[2000];
    char destination[2000];
    int quantity;
}record;

void add_order()
{    
    FILE *ptr1;
    ptr1=fopen("File.csv","a+");
    if (ptr1==NULL)
    {
        printf("Error!");
    }
    int line_count=0;
    char buffer[2000],ch;
    fseek(ptr1,0,SEEK_SET);
    //Counting the number of lines in the file already. 
    while ((ch = fgetc(ptr1)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }
    fseek(ptr1,0,SEEK_SET);
    int index;
    char buffer1[2000];
    if (line_count==0)
    index=line_count;
    else if(line_count==1)
    {
        fgets(buffer1,2000,ptr1);
        index=atoi(buffer1);
    }
    else
    {
    for (int i=0;i<line_count-1;i++)
    {
        fgets(buffer,2000,ptr1);
        fscanf(ptr1,"%s",buffer1);
    }
    index=atoi(buffer1);
    }

    fseek(ptr1,0,SEEK_SET);
    //Used to use up the \n character so that fgets() function can work properly
    while ((getchar()) != '\n');


    char item[2000],destination[2000],pickup[2000];
    //Input of the pickup location
    printf("Enter the pickup location:");
    fgets(pickup,2000,stdin);
    //Used to remove the \n inputed during entering of the "pickup" string
    if (pickup[strlen(pickup)-1]=='\n')
    pickup[strlen(pickup)-1]='\0';
    //Input of items to be ordered
    printf("Enter the item to be ordered:");
    fgets(item,2000,stdin);
    if (item[strlen(item)-1]=='\n')
    item[strlen(item)-1]='\0';
    //Input of quantity of items to be ordered
    printf("Enter the quantity of the item:");
    int quantity;
    scanf("%d",&quantity); 
    //Input of destination of the order
    printf("Enter the destination:");
    while ((getchar()) != '\n');
    fgets(destination,2000,stdin);
    if (destination[strlen(destination)-1]=='\n')
    destination[strlen(destination)-1]='\0';
    //Values are copied onto the struct record
    strcpy(record.pickup,pickup);
    strcpy(record.destination,destination);
    strcpy(record.item,item);
    record.quantity=quantity;
    //record.customer_order_id=line_count;
    //Customer order id is taken as 1 greater than index
    record.customer_order_id=index+1;
    fprintf(ptr1,"%d %s %s %d %s ",record.customer_order_id,record.pickup,record.item,record.quantity,record.destination);
    fprintf(ptr1,"\n");
    printf("\nOrder has been placed!\n");
    fclose(ptr1);
}

void view_orders()
{
    FILE *ptr=fopen("File.csv","r");
    char ch;
    do
    {
        ch=fgetc(ptr);
        printf("%c",ch);
    } while (ch!=EOF);
    
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
        remove("File.csv"); // Delete the original file
        rename("Temp.csv", "File.csv"); // Rename the temp file to the original file
        printf("Order successfully deleted.\n");
    }
}


int main()
    {
        t:
        printf("Choose an option among the available functions as specified below:\n");
        printf("1.ADD AN ORDER:\n");
        printf("2:VIEW ENTIRE ORDER HISTORY:\n");
        printf("3.VIEW A PARTICULAR ORDER HISTORY:\n");
        printf("4.DELETE A RECORD:\n");
        int choice;
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
            {  
                add_order();
                printf("\nDo you want to make any other changes? If yes type 1 else type 0:");
                int choice1;
                scanf("%d",&choice1);
                if (choice1==1)
                goto t;
                break;
            }
            case 2:
            {
                view_orders();
                printf("\nDo you want to make any other changes? If yes type 1 else type 0:");
                int choice1;
                scanf("%d",&choice1);
                if (choice1==1)
                goto t;
                break;
            }
            case 3:
            {
                char n[2000];
                printf("Enter customer order id to be searched for:");
                while (getchar()!='\n');

                fgets(n,2000,stdin);
                if (n[strlen(n)-1]=='\n')
                n[strlen(n)-1]='\0';
                view_order(n);
                printf("\nDo you want to make any other changes? If yes type 1 else type 0:");
                int choice1;
                scanf("%d",&choice1);
                if (choice1==1)
                goto t;
                break;
            }
            case 4:
            {
                int index;
                printf("Enter the customer order id of the line to be deleted:");
                scanf("%d",&index);
                deleteOrderByOrderNumber(index);
                printf("\nDo you want to make any other changes? If yes type 1 else type 0:");
                int choice1;
                scanf("%d",&choice1);
                if (choice1==1)
                goto t;
                break;
            }
            default:
            {printf("Invalid option chosen\n");
            goto t;}
        }
        return 0;
    }