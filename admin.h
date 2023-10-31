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
    int found = 0;

    while (fscanf(inputFile, " %99[^|]|%99[^|\n]\n", driverName, vehicleNumber) != EOF)
    {
        if (strcmp(driverName, nameToDelete) == 0)
        {
            found = 1;
            continue; // Skip this line (record to be deleted)
        }

        fprintf(tempFile, "%s|%s\n", driverName, vehicleNumber); // Write the line back to the temporary file
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

    while (fscanf(inputFile, "%19[^\n]\n", vehicleNumber) != EOF)
    {
        if (strcmp(vehicleNumber, vehicleNumberToDelete) == 0)
        {
            found = 1;
            continue; // Skip this line (record to be deleted)
        }

        fprintf(tempFile, "%s\n", vehicleNumber); // Write the line back to the temporary file
    }

    fclose(inputFile);
    fclose(tempFile);

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
    system("cls");
    char k;
    short x = 1;
    while (x == 1)
    {
        int ch1;
        const char *filename = "driver_details.csv";
        const char *filename1 = "vehicle_details.csv";
        printf("\t\t\t\t1. Add record\n\t\t\t\t2. View record\n\t\t\t\t3. Delete record\n");
        printf("\t\t\t\tEnter choice :\n\t\t\t\t>>>");
        scanf("%d", &ch1);
        system("cls");
        if (ch1 == 1)
        {
            int ch;
            printf("\t\t\t\t1. Vehicle details\n\t\t\t\t2. Driver details\n\t\t\t\t3. Order details\n");
            printf("\t\t\t\tEnter choice :\n>>>");
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
                    printf("\t\t\t\tError opening the file.\n");
                }
                else
                {
                    // Consume any leftover newline characters
                    clear_leftover();

                    // Input vehicle details from the user
                    printf("\t\t\t\tEnter Vehicle Number: ");
                    fgets(newVehicle.vehicleNumber, 20, stdin);

                    // Remove the trailing newline from the input
                    remove_endline(newVehicle.vehicleNumber);

                    // Write the details to the CSV file
                    fprintf(file, "%s\n", newVehicle.vehicleNumber);

                    // Close the file
                    fclose(file);
                    system("cls");
                    loading();
                    printf("\t\t\t\tVehicle details added to the CSV file.\n");
                }
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
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
                    fp = fopen("vehicle_details.csv", "r");
                    FILE *dfile = fopen("log_driver.csv", "r+");

                    // Consume any leftover newline characters
                    clear_leftover();

                    // Input driver details from the user
                    printf("\t\t\t\tEnter Driver's ID: ");
                    fgets(check_d.dlogin.id, ID_PASS_MAX, stdin);

                    remove_endline(check_d.dlogin.id);

                    if (fp == NULL || dfile == NULL)
                    {
                        printf("\t\t\t\tError opening the file.\n");
                    }

                    else
                    {
                        while (fscanf(dfile, "%49[^|]|%19[^|]|%19[^\n]\n", add_d.name, add_d.dlogin.id, add_d.dlogin.pass) != EOF)
                        {
                            if (check_d.dlogin.id == add_d.dlogin.id)
                            {
                                break;
                            }
                        }
                        printf("Vehicle Number\n");

                        // Read and print each line from the CSV file
                        while (fscanf(fp, "%19[^|]\n", viewVehicle.vehicleNumber) != EOF)
                        {
                            printf("%s\n", viewVehicle.vehicleNumber);
                        }
                        fclose(fp);
                        printf("\n\t\t\t\tEnter vehicle number from list: ");
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
                            printf("\t\t\t\tVehicle not in list\n");
                        }

                        else
                        {

                            // Write the details to the CSV file
                            fprintf(file, "%s|%s\n", add_d.name, add_d.curr_veh.vehicleNumber);

                            // Close the file
                            fclose(file);
                            fclose(dfile);
                            system("cls");
                            loading();
                            printf("\t\t\t\tDriver details added to the CSV file.\n");
                        }
                    }
                }
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            case 3:
                // Open the CSV file in append mode
                file = fopen("order_details.csv", "a");

                if (file == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }
                else
                {
                    clear_leftover();

                    // Input vehicle details from the user
                    printf("\t\t\t\tEnter Customer Number: ");
                    fgets(add_o.cus.name, 50, stdin);
                    remove_endline(add_o.cus.name);

                    printf("\t\t\t\tEnter Pick up location: ");
                    fgets(add_o.pick_loc, 100, stdin);
                    remove_endline(add_o.pick_loc);

                    printf("\t\t\t\tEnter Delivery location: ");
                    fgets(add_o.del_dest, 100, stdin);
                    remove_endline(add_o.del_dest);

                    // Write the details to the CSV file
                    fprintf(file, "%s|%s|%s\n", add_o.cus.name, add_o.pick_loc, add_o.del_dest);

                    // Close the file
                    fclose(file);
                    system("cls");
                    loading();
                    printf("\t\t\t\tOrder details added to the CSV file.\n");
                }
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;

            default:
                clear_leftover();
                printf("\t\t\t\tWrong choice...\n");
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            }
        }
        if (ch1 == 2)
        {

            int ch;
            printf("\t\t\t\t1. Vehicle details\n\t\t\t\t2. Driver details\n\t\t\t\t3. Oreder details\n");
            printf("\t\t\t\tEnter choice :\n\t\t\t\t>>>");
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
                    printf("\t\t\t\tError opening the file.\n");
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
                printf("\n\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            case 2:
                fp = fopen("driver_details.csv", "r");

                if (fp == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
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
                printf("\n\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            case 3:
                fp = fopen("order_details.csv", "r");

                if (fp == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
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
                printf("\n\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;

            default:
                printf("\t\t\t\tWrong choice...\n");
                clear_leftover();
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            }
        }
        if (ch1 == 3)
        {
            int ch;
            printf("\t\t\t\t1. Vehicle details\n\t\t\t\t2. Driver details\n\t\t\t\t3. Oreder details\n");
            printf("\t\t\t\tEnter choice :\n\t\t\t\t>>>");
            scanf("%d", &ch);
            system("cls");
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
                    printf("\t\t\t\tEnter vehicle number of the vehicle to be deleted: ");
                    fgets(delVehicle.vehicleNumber, 20, stdin);
                    remove_endline(delVehicle.vehicleNumber);
                    int chck = 0;
                    fp = fopen("vehicle_details.csv", "r");
                    while (fscanf(fp, "%19[^\n]\n", viewVehicle.vehicleNumber) != EOF)
                    {
                        if (strcmp(viewVehicle.vehicleNumber, delVehicle.vehicleNumber) == 0)
                        {
                            chck = 1;
                            break;
                        }
                    }
                    if (chck == 0)
                    {
                        printf("\t\t\t\tVehicle not in list\n");
                    }

                    else
                    {
                        del_v(filename1, delVehicle.vehicleNumber);
                    }
                }
                clear_leftover();
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            case 2:

                file = fopen("driver_details.csv", "r");

                if (file == NULL)
                {
                    printf("\t\t\t\tError opening the file.\n");
                }

                else
                {
                    printf("Customer name\tPick up location\tDelivery destination\n");

                    // Read and print each line from the CSV file
                    while (fscanf(file, "%99[^|]|%99[^|]|%99[^\n]\n", read_o.cus.name, read_o.pick_loc, read_o.del_dest) != EOF)
                    {
                        printf("%-10s\t%-19s\t%s\n", read_o.cus.name, read_o.pick_loc, read_o.del_dest);
                    }
                    fclose(file);

                    clear_leftover();
                    printf("\t\t\t\tEnter driver name to be deleted: ");
                    fgets(del_d.name, 100, stdin);
                    remove_endline(del_d.name);
                    int chck = 0;
                    fp = fopen("driver_details.csv", "r");
                    while (fscanf(fp, "%99[^|]|%19[^\n]\n", read_d.name, read_d.curr_veh.vehicleNumber) != EOF)
                    {
                        if (strcmp(del_d.name, read_d.name))
                        {
                            chck = 1;
                            break;
                        }
                    }
                    fclose(fp);
                    if (chck == 0)
                    {
                        printf("\t\t\t\tDriver not in list\n");
                    }
                    else
                    {
                        delDriver(filename, del_d.name);
                    }
                }
                clear_leftover();
                printf("\t\t\t\tPress enter to continue");
                scanf("%c", &k);
                break;
            default:
                break;
            }
        }

        system("cls");
        printf("\t\t\t\tPress 0 to exit and 1 to continue: ");
        scanf("%hi", &x);
    }
}