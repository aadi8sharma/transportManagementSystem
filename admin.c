#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "structure.h"
#include "loading.h"

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

void admin()
{
    char k;
    short x = 1;
    while (x == 1)
    {
        int ch1;
        printf("1. Add record\n2. View record\n3. Delete record\n");
        printf("Enter choice : ");
        scanf("%d", &ch1);
        system("cls");
        if (ch1 == 1)
        {
            int ch;
            printf("1. Vehicle details\n2. Driver details\n3. Order details\n");
            printf("Enter choice : ");
            scanf("%d", &ch);
            system("cls");
            FILE *file, *fp;

            switch (ch)
            {
            case 1:

                // Open the CSV file in append mode
                file = fopen("vehicle_details.csv", "a");

                if (file == NULL)
                {
                    printf("Error opening the file.\n");
                }
                else
                {
                    // Consume any leftover newline characters
                    clear_leftover();

                    // Input vehicle details from the user
                    printf("Enter Vehicle Number: ");
                    fgets(newVehicle.vehicleNumber, 20, stdin);

                    // Remove the trailing newline from the input
                    remove_endline(newVehicle.vehicleNumber);

                    // Write the details to the CSV file
                    fprintf(file, "%s\n", newVehicle.vehicleNumber);

                    // Close the file
                    fclose(file);
                    system("cls");
                    loading();
                    printf("Vehicle details added to the CSV file.\n");
                }
                printf("Press enter to continue");
                scanf("%c", &k);
                break;
            case 2:
                // Open the CSV file in append mode
                file = fopen("driver_details.csv", "a");

                if (file == NULL)
                {
                    printf("Error opening the file.\n");
                }
                else
                {
                    fp = fopen("vehicle_details.csv", "r");

                    // Consume any leftover newline characters
                    clear_leftover();

                    // Input driver details from the user
                    printf("Enter Driver's name: ");
                    fgets(add_d.name, 50, stdin);

                    remove_endline(add_d.name);

                    if (fp == NULL)
                    {
                        printf("Error opening the file.\n");
                    }

                    else
                    {
                        printf("Vehicle Number\n");

                        // Read and print each line from the CSV file
                        while (fscanf(fp, "%19[^|]\n", viewVehicle.vehicleNumber) != EOF)
                        {
                            printf("%s\n", viewVehicle.vehicleNumber);
                        }
                        fclose(fp);
                        printf("Enter vehicle number from list: ");
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
                            printf("Vehicle not in list\n");
                        }

                        else
                        {

                            // Write the details to the CSV file
                            fprintf(file, "%s|%s\n", add_d.name, add_d.curr_veh.vehicleNumber);

                            // Close the file
                            fclose(file);
                            system("cls");
                            loading();
                            printf("Driver details added to the CSV file.\n");
                        }
                    }
                }
                printf("Press enter to continue");
                scanf("%c", &k);
                break;
            case 3:
                // Open the CSV file in append mode
                file = fopen("order_details.csv", "a");

                if (file == NULL)
                {
                    printf("Error opening the file.\n");
                }
                else
                {
                    clear_leftover();

                    // Input vehicle details from the user
                    printf("Enter Customer Number: ");
                    fgets(add_o.cus.name, 50, stdin);
                    remove_endline(add_o.cus.name);

                    printf("Enter Pick up location: ");
                    fgets(add_o.pick_loc, 100, stdin);
                    remove_endline(add_o.pick_loc);

                    printf("Enter Delivery location: ");
                    fgets(add_o.del_dest, 100, stdin);
                    remove_endline(add_o.del_dest);

                    // Write the details to the CSV file
                    fprintf(file, "%s|%s|%s\n", add_o.cus.name, add_o.pick_loc, add_o.del_dest);

                    // Close the file
                    fclose(file);
                    system("cls");
                    loading();
                    printf("Order details added to the CSV file.\n");
                }
                printf("Press enter to continue");
                scanf("%c", &k);
                break;

            default:
                clear_leftover();
                printf("Wrong choice...\n");
                printf("Press enter to continue");
                scanf("%c", &k);
                break;
            }
        }
        if (ch1 == 2)
        {

            int ch;
            printf("1. Vehicle details\n2. Driver details\n3. Oreder details\n");
            printf("Enter choice : ");
            scanf("%d", &ch);
            system("cls");
            FILE *fp;
            switch (ch)
            {
            case 1:
                system("cls");
                fp = fopen("vehicle_details.csv", "r");

                if (fp == NULL)
                {
                    printf("Error opening the file.\n");
                }

                else
                {
                    printf("Vehicle Number\n");

                    // Read and print each line from the CSV file
                    while (fscanf(fp, "%19[^|]\n", viewVehicle.vehicleNumber) != EOF)
                    {
                        printf("%s\n", viewVehicle.vehicleNumber);
                    }
                }
                clear_leftover();
                printf("Press enter to continue");
                scanf("%c", &k);
                break;
            case 2:
                fp = fopen("driver_details.csv", "r");

                if (fp == NULL)
                {
                    printf("Error opening the file.\n");
                }

                else
                {
                    printf("Driver name\t\tCurrent Vehicle\n");

                    // Read and print each line from the CSV file
                    while (fscanf(fp, "%99[^|]|%19[^\n]\n", read_d.name, read_d.curr_veh.vehicleNumber) != EOF)
                    {
                        printf("%-15s\t%12s\n", read_d.name, read_d.curr_veh.vehicleNumber);
                    }
                }
                clear_leftover();
                printf("Press enter to continue");
                scanf("%c", &k);
                break;
            case 3:
                fp = fopen("order_details.csv", "r");

                if (fp == NULL)
                {
                    printf("Error opening the file.\n");
                }

                else
                {
                    printf("Customer name\tPick up location\tDelivery destination\n");

                    // Read and print each line from the CSV file
                    while (fscanf(fp, "%99[^|]|%99[^|]|%99[^\n]\n", read_o.cus.name, read_o.pick_loc, read_o.del_dest) != EOF)
                    {
                        printf("%-10s\t%-19s\t%s\n", read_o.cus.name, read_o.pick_loc, read_o.del_dest);
                    }
                }
                clear_leftover();
                printf("Press enter to continue");
                scanf("%c", &k);
                break;

            default:
                printf("Wrong choice...\n");
                clear_leftover();
                printf("Press any enter to continue");
                scanf("%c", &k);
                break;
            }
        }
        system("cls");
        printf("Press 0 to exit and 1 to continue: ");
        scanf("%hi", &x);
    }
}

int main()
{
    admin();
}