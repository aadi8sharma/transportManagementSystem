#include <stdio.h>
#include <string.h>
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
    int line_count=1;
    char buffer[2000],ch;
    fseek(ptr1,0,SEEK_SET);
    while ((ch = fgetc(ptr1)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }
    fseek(ptr1,0,SEEK_SET);
    char ch2;
    int counter=0;
    for (int i=0;i<line_count;i++)
    {
        while(ch2!=EOF)
        {
            ch2=fgetc(ptr1);
            if (ch2=='\n')
            {
                counter++;
                break;
            }
        }
    }
    line_count=counter;
    
    fseek(ptr1,0,SEEK_SET);
    while ((getchar()) != '\n');


    char item[2000],destination[2000],pickup[2000];
    printf("Enter the pickup location:");
    fgets(pickup,2000,stdin);
    if (pickup[strlen(pickup)-1]=='\n')
    pickup[strlen(pickup)-1]='\0';
    printf("Enter the item to be ordered:");
    fgets(item,2000,stdin);
    if (item[strlen(item)-1]=='\n')
    item[strlen(item)-1]='\0';
    printf("Enter the quantity of the item:");
    int quantity;
    scanf("%d",&quantity); 
    printf("Enter the destination:");
    while ((getchar()) != '\n');
    fgets(destination,2000,stdin);
    if (destination[strlen(destination)-1]=='\n')
    destination[strlen(destination)-1]='\0';
    strcpy(record.pickup,pickup);
    strcpy(record.destination,destination);
    strcpy(record.item,item);
    record.quantity=quantity;
    record.customer_order_id=line_count;
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

int main()
    {
        t:
        printf("Choose an option among the available functions as specified below:\n");
        printf("1.ADD AN ORDER:\n");
        printf("2:VIEW ORDER HISTORY:\n");
        printf("3.EDIT A RECORD:\n");
        int choice;
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
            {  
                add_order();
                printf("Do you want to make any other changes? If yes type 1 else type 0:");
                int choice1;
                scanf("%d",&choice1);
                if (choice1==1)
                goto t;
                break;
            }
            case 2:
            {
                view_orders();
                printf("Do you want to make any other changes? If yes type 1 else type 0:");
                int choice1;
                scanf("%d",&choice1);
                if (choice1==1)
                goto t;
                break;
            }
            default:
            {printf("Invalid option chosen");}
        }
        return 0;
    }