#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "structure.h"
#include "loading.h"
int rerun = 0;

void remove_endline(char a[])
{
    size_t len = strlen(a);
    if (len > 0 && a[len - 1] == '\n')
    {
        a[len - 1] = '\0';
    }
}

void clear_leftover()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Function to delete a record by unique column value
void delDriver(const char *filename, const char *nameToDelete)
{
    FILE *inputFile = fopen(filename, "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (inputFile == NULL || tempFile == NULL)
    {
        perror("\t\t\t\tFile open error");
        exit(EXIT_FAILURE);
    }

    char driverName[100];    // Adjust buffer size based on the expected driver name length
    char vehicleNumber[100]; // Adjust buffer size based on the expected vehicle number length
    char driverID[100];
    char y[10];
    int found = 0;

    while (fscanf(inputFile, " %19[^|]|%49[^|]|%19[^|]|%9[^\n]\n",driverID, driverName, vehicleNumber,y) != EOF)
    {
        if (strcmp(driverID, nameToDelete) == 0)
        {
            found = 1; // Skip this line (record to be deleted)
        }
        else
        fprintf(tempFile, "%s|%s|%s|%s\n",driverID, driverName, vehicleNumber,y); // Write the line back to the temporary file
    }

    fclose(inputFile);
    fclose(tempFile);

    if (remove(filename) != 0)
    {
        perror("\t\t\t\tError deleting the original file");
        exit(EXIT_FAILURE);
    }

    if (rename("temp.csv", filename) != 0)
    {
        perror("\t\t\t\tError renaming the temporary file");
        exit(EXIT_FAILURE);
    }

    if (found)
    {
        printf("\t\t\t\tRecord for driver '%s' deleted successfully.\n", nameToDelete);
    }
    else
    {
        printf("\t\t\t\tRecord for driver '%s' not found.\n", nameToDelete);
    }
}


void del_v(const char *filename, const char *vehicleNumberToDelete)
{
    FILE *inputFile = fopen(filename, "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (inputFile == NULL || tempFile == NULL)
    {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    char vehicleNumber[100]; // Adjust buffer size based on the expected vehicle number length
    int found = 0;

    while (fscanf(inputFile, " %99[^\n]\n", vehicleNumber) != EOF)
    {
        if (strcmp(vehicleNumber, vehicleNumberToDelete) == 0)
        {
            found = 1;
        }
        else
        {
            fprintf(tempFile, "%s\n", vehicleNumber); // Write the line back to the temporary file
        }
    }

    fclose(inputFile);
    fclose(tempFile);

    if (remove(filename) != 0)
    {
        perror("Error deleting the original file");
        exit(EXIT_FAILURE);
    }

    if (rename("temp.csv", filename) != 0)
    {
        perror("Error renaming the temporary file");
        exit(EXIT_FAILURE);
    }

    if (found)
    {
        printf("Record for vehicle number '%s' deleted successfully.\n", vehicleNumberToDelete);
    }
    else
    {
        printf("Record for vehicle number '%s' not found.\n", vehicleNumberToDelete);
    }
}

void admin()
{
    system("clear");
    char k;
    short x = 1;
    while (x == 1)
    {
        int ch1;
        const char *filename = "driver_details.csv";
        const char *filename1 = "vehicle_details.csv";
        backpage:
        system("clear");
        printf("\n\t\t\t\t\t\t\t%sADMIN ACCOUNT\n\n\t\t\t\t%s(1) Add record\n\t\t\t\t(2) View record\n\t\t\t\t(3) Delete record\n\t\t\t\t(4) Logout\n%s",BCYN, BLUE_TEXT, GREEN_TEXT);
        
        enter(">>>", 4);
        printf("%s", RESET_TEXT);
        scanf("%d", &ch1);
        system("clear");
        if (ch1 == 1)
        {
            int ch;
            detailinput:
            system("clear");
            printf("\n\n\t\t\t\t%s1. Vehicle details\n\n\t\t\t\t2. Driver details%s\n\n", BLUE_TEXT, GREEN_TEXT);
           
           enter(">>>",4);
            printf("%s", RESET_TEXT);
            scanf("%d", &ch);
            //system("clear");
            FILE *file, *fp;

            switch (ch)
            {
            case 1:

                // Open the CSV file in append mode
                file = fopen("vehicle_details.csv", "a");

                if (file == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }
                else
                {
                    // Consume any leftover newline characters
                    clear_leftover();

                    // Input vehicle details from the user

                    enter("Enter vehicle Number : ", 4);

                    fgets(newVehicle.vehicleNumber, 20, stdin);

                    // Remove the trailing newline from the input
                    remove_endline(newVehicle.vehicleNumber);

                    // Write the details to the CSV file
                    fprintf(file, "%s\n", newVehicle.vehicleNumber);

                    // Close the file
                    fclose(file);
                    
                    system("clear");
                    printf("\n\t\t\t\t%sAdding data, kindly wait \n%s", YELLOW_TEXT,RESET_TEXT);
                    loading();
                   
                }
                // printf("\t\t\t\tPress enter to continue");
                // scanf("%c", &k);
                break;
            case 2:
                // Open the CSV file in append mode
                file = fopen("driver_details.csv", "a");

                if (file == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }
                else
                {
                    fp = fopen("vehicle_details.csv", "r+");
                    FILE *dfile = fopen("log_driver.csv", "r+");

                    // Consume any leftover newline characters
                    clear_leftover();

                    // Input driver details from the user
                    printf("\n");
                    enter("Enter Driver's ID : ", 4);

                    fgets(check_d.dlogin.id, ID_PASS_MAX, stdin);

                    remove_endline(check_d.dlogin.id);

                    if (fp == NULL || dfile == NULL)
                    {
                        printf("\t\t\t\tError opening the file.\n");
                    }

                    else
                    {
                        int d_id_exists = 0;
                        while (fscanf(dfile, "%49[^|]|%19[^|]|%19[^\n]\n", add_d.name, add_d.dlogin.id, add_d.dlogin.pass) != EOF)
                        {
                            if (strcmp(check_d.dlogin.id, add_d.dlogin.id) == 0)
                            {
                                d_id_exists = 1;
                                break;
                            }
                        }

                        if(!d_id_exists)
                        {
                            printf("\n\t\t\t\tDriver ID not found, try again.");
                            usleep(1000000);
                            goto detailinput;
                            break;

                        }
                        printf("\nVehicle Number\n");

                        // Read and print each line from the CSV file
                        while (fscanf(fp, "%19[^|]\n", viewVehicle.vehicleNumber) != EOF)
                        {
                            printf("%s\n\n", viewVehicle.vehicleNumber);
                        }
                        fclose(fp);

                       // printf("\n\t\t\t\tEnter vehicle number from list: ");
                       enter("Enter vehicle number from list : ", 4);
                        fgets(add_d.curr_veh.vehicleNumber, 20, stdin);
                        remove_endline(add_d.curr_veh.vehicleNumber);
                        int chck = 0;
                        fp = fopen("vehicle_details.csv", "r");
                        while (fscanf(fp, "%19[^\n]\n", viewVehicle.vehicleNumber) != EOF)
                        {

                            if (strcmp(viewVehicle.vehicleNumber, add_d.curr_veh.vehicleNumber) == 0)
                            {
                                chck = 1;
                                break;
                            }
                        }
                        if (chck == 0)
                        {
                            printf("\n%s\t\t\t\tVehicle not in list\n%s",RED_TEXT,RESET_TEXT);
                        }

                        else
                        {

                            // Write the details to the CSV file
                            fprintf(file, "%s|%s|%s|%d\n",check_d.dlogin.id,add_d.name, add_d.curr_veh.vehicleNumber, 0);

                            // Close the file
                            fclose(file);
                            fclose(dfile);
                            system("clear");
                            loading();
                            printf("\t\t\t\tDriver details added to the CSV file.\n");
                            usleep(1500000);
                        }
                    }
                }
    
               
                break;
            default:
                clear_leftover();
                 printf("\t\t\t\t%sINVALID CHOICE%s\n", RED_TEXT, RESET_TEXT);
                 usleep(2000000);
                   goto detailinput;
                break;
            }
        }
        else if (ch1 == 2)
        {
            char x[10];
            int ch;
            vieword:
            system("clear");
            printf("\n\t\t\t\t\t\t\t%sVIEW RECORD\n\n\t\t\t\t%s1. Vehicle details\n\t\t\t\t2. Driver details\n\t\t\t\t3. Order details\n\n%s", BCYN,BLUE_TEXT,GREEN_TEXT);
          
          
          enter(">>>",4);
          printf("%s",RESET_TEXT);
            scanf("%d", &ch);
            system("clear");
            FILE *fp;
            switch (ch)
            {
             case 1:
                system("clear");
                fp = fopen("vehicle_details.csv", "r");

                if (fp == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }

                else
                {
                    printf("\t\t\t\t\t\t\tVehicle Number\n\n");

                    // Read and print each line from the CSV file
                    while (fscanf(fp, "%19[^|]\n", viewVehicle.vehicleNumber) != EOF)
                    {
                        printf("%s\n", viewVehicle.vehicleNumber);  //add 4 tab spaces some way
                       

                    }
                }
                clear_leftover();
                printf("\n\t\t\t\tPress enter to continue ");
                scanf("%c", &k);
                break;
            case 2:
                fp = fopen("driver_details.csv", "r+");

                if (fp == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }

                else
                {
                    printf("Driver ID\t\tDriver name\t\tCurrent Vehicle\t\tOrder Number\n");

                    // Read and print each line from the CSV file
                     while (fscanf(fp, "%19[^|]|%49[^|]|%19[^|]|%9[^\n]\n",read_d.dlogin.id, read_d.name, read_d.curr_veh.vehicleNumber,x) != EOF)
                    {
                        printf("%-15s\t%19s\t%23s\t%17s\n",read_d.dlogin.id, read_d.name, read_d.curr_veh.vehicleNumber,x);
                    }
                }
                clear_leftover();
                printf("\n\t\t\t\tPress enter to continue ");
                scanf("%c", &k);
                break;
            case 3:
                fp = fopen("orders.csv", "r");

                if (fp == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }

                else
                {
                    printf("Customer order ID\tPick up location\tItem\t\tQuantity\tDestination\tCustomer ID\n");

                    // Read and print each line from the CSV file
                    while (fscanf(fp, "%d|%99[^|]|%99[^|]|%d|%99[^|]|%19[^\n]\n", &read_co.customer_order_id, read_co.pickup, read_co.item,&read_co.quantity,read_co.destination,read_co.customer_ID) != EOF)
                    {
                      printf("%-17d\t%-16s\t%s\t%-15d\t%-12s\t%11s\n",read_co.customer_order_id, read_co.pickup, read_co.item,read_co.quantity,read_co.destination,read_co.customer_ID);

                      //  printf("%d\t%s\t%-10s\t%d\t%-19s\t%s\n",read_co.customer_order_id, read_co.pickup, read_co.item,read_co.quantity,read_co.destination,read_co.customer_ID);
                    }
                }
                clear_leftover();
                printf("\n\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;

            default:
                clear_leftover();
                 printf("\t\t\t\t%sINVALID CHOICE%s\n", RED_TEXT, RESET_TEXT);
                 usleep(2000000);
                 goto vieword;
                break;
            }
        }
        else if (ch1 == 3)
        {
            char x[10];
            int ch;
            printf("%s\t\t\t\t1. Vehicle details\n\t\t\t\t2. Driver details\n\n%s",BLUE_TEXT,GREEN_TEXT);
         
                enter(">>>", 4);
                printf("%s",RESET_TEXT);
            scanf("%d", &ch);
            system("clear");
            FILE *fp, *file;
            switch (ch)
            {
            case 1:
                file = fopen("vehicle_details.csv", "r");

                if (file == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }

                else
                {
                    printf("Vehicle Number\n");

                    // Read and print each line from the CSV file
                    while (fscanf(file, "%19[^\n]\n", viewVehicle.vehicleNumber) != EOF)
                    {
                        printf("%s\n", viewVehicle.vehicleNumber);
                    }

                    fclose(file);

                    clear_leftover();
                    printf("\t\t\t\tEnter vehicle number of the vehicle to be deleted : ");
                    scanf("%s", delVehicle.vehicleNumber);

                    del_v(filename1, delVehicle.vehicleNumber);
                }
                clear_leftover();
               usleep(2000000);
                break;
            case 2:

                file = fopen("driver_details.csv", "r");

                if (file == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }

                else
                {
                    printf("Driver ID\t\tDriver name\t\tCurrent Vehicle\t\tOrder Number\n");

                    // Read and print each line from the CSV file
                    while (fscanf(file, "%19[^|]|%49[^|]|%19[^|]|%9[^\n]\n",read_d.dlogin.id, read_d.name, read_d.curr_veh.vehicleNumber,x) != EOF)
                    {
                        printf("%-15s\t%19s\t%23s\t%17s\n",read_d.dlogin.id, read_d.name, read_d.curr_veh.vehicleNumber,x);
                    }
                    fclose(file);
                    
                    clear_leftover();
                    printf("\n\n");
                    enter("Enter driver name to be deleted : ", 4);
                    fgets(del_d.name, 100, stdin);
                    remove_endline(del_d.name);
                    delDriver(filename, del_d.name);
                   
                }
                clear_leftover();
                fflush(stdin);
                fflush(stdout);
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            default:
                break;
            }
        }
        else if (ch1==4)
        {
            rerun=1;
            break;
        }
        else
        {
            printf("\n\t\t\t\t%sINVALID CHOICE\n%s", RED_TEXT,RESET_TEXT);
            usleep(1500000);
            goto backpage;
        }

        system("clear");
        printf("\n\t\t\t\t%sDo you want to make any other changes?\n\n\t\t\t\t%s(1) Yes\n\t\t\t\t(2) No %s\n",PINK_TEXT, BLUE_TEXT,GREEN_TEXT);
               enter(">>>", 4);
               printf("%s",RESET_TEXT);
        scanf("%hi", &x);
        if (x==2) {break;}
    }
}

void assign_order(int order_ID)
{
    FILE* ddetails = fopen("driver_details.csv", "r+");
    FILE* temp = fopen("Temp.csv","a+");
    char id_[20], name_[50], vehicleno_[20];
    int orderid_;
    while (fscanf(ddetails,"%19[^|]|%49[^|]|%19[^|]|%d\n",id_,name_,vehicleno_,&orderid_)!=EOF)
    {
        if (orderid_== 0)
        {
            orderid_=order_ID;
            fprintf(temp,"%s|%s|%s|%d\n",id_,name_,vehicleno_,orderid_);
            break;
        }
        else
        {
            fprintf(temp,"%s|%s|%s|%d\n",id_,name_,vehicleno_,orderid_);
        }
    }
    while(fscanf(ddetails,"%19[^|]|%49[^|]|%19[^|]|%d\n",id_,name_,vehicleno_,&orderid_)!=EOF)
    {
        fprintf(temp,"%s|%s|%s|%d\n",id_,name_,vehicleno_,orderid_);
    }
    fclose(ddetails);
    fclose(temp);
    remove("driver_details.csv");
    rename("Temp.csv","driver_details.csv");
}
