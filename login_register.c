#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"
#include "loading.h"
#define ID_PASS_MAX 20

int pass_attempts = 3;

void reg()
{
    system("cls");
    printf("\t\t\t\t\t\t\tREGISTER\t\t\t\n\n");
    printf("\t\t\t\tSelect account type: \n\n\t\t\t\t(1) Customer\n\t\t\t\t(2) Driver");
    int choice;
    printf("\n\t\t\t\t>>> ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        FILE *cfile = fopen("log_customer.csv", "a+");
        printf("\n\t\t\t\tEnter your name: ");
        scanf("%s", add_c.name);
        printf("\n\t\t\t\tEnter new login id: ");
        scanf("%s", add_c.clogin.id);
        printf("\n\t\t\t\tEnter new password: ");
        scanf("%s", add_c.clogin.pass);
        if (!cfile)
        {
            // error in file opening
            printf("\t\t\t\tCan't open file.\n");
            return;
        }
        system("clear");
        fprintf(cfile, "%s|%s|%s\n", add_c.name, add_c.clogin.id, add_c.clogin.pass); // add record to database
        printf("\n\t\t\t\tPlease wait while we create your account");
        for (int i = 0; i <= 6; i++)
        {
            printf(".");
            usleep(125000);
        }
        system("cls");
        printf("\n\t\t\t\tNew account created.");

        fclose(cfile);
    }

    else if (choice == 2)
    {
        FILE *dfile = fopen("log_driver.csv", "a+");
        printf("\n\t\t\t\tEnter your name: ");
        scanf("%s", add_d.name);
        printf("\n\t\t\t\tEnter new login id: ");
        scanf("%s", add_d.dlogin.id);
        printf("\n\t\t\t\tEnter new password: ");
        scanf("%s", add_d.dlogin.pass);
        if (!dfile)
        {
            // error in file opening
            printf("\t\t\t\tCan't open file.\n");
            return;
        }
        system("cls");
        fprintf(dfile, "%s|%s|%s\n", add_d.name, add_d.dlogin.id, add_d.dlogin.pass); // add record to database
        printf("\n\t\t\t\tPlease wait while we create your account");
        for (int i = 0; i <= 6; i++)
        {
            printf(".");
            usleep(125000);
        }
        system("cls");
        printf("\n\t\t\t\tNew account created.");

        fclose(dfile);
    }
}

void loginf()
{
    system("cls");
    printf("\t\t\t\t\t\t\tLOG IN\n\n");
    printf("\t\t\t\tSelect account type: \n\n\t\t\t\t(1) Customer\n\t\t\t\t(2) Driver");
    int choice;
    printf("\n\t\t\t\t>>>");
    scanf("%d", &choice);
    system("cls");
    if (choice == 1)
    {
        FILE *cfile = fopen("log_customer.csv", "r");
        printf("\n\t\t\t\tEnter log in id: ");
        scanf("%s", check_c.clogin.id);

        while (fscanf(cfile, "%49[^|]|%19[^|]|%19[^\n]\n", add_c.name, add_c.clogin.id, add_c.clogin.pass) != EOF)
        {
            if (strcmp(add_c.clogin.id, check_c.clogin.id) == 0)
            {
            tryPass_C:
                if (pass_attempts > 0)
                {
                    printf("\n\t\t\t\tEnter password: ");
                    scanf("%s", check_c.clogin.pass);
                    pass_attempts--;
                    system("cls");
                    if (strcmp(add_c.clogin.pass, check_c.clogin.pass) == 0)
                    {
                        printf("Loading");
                        loading();
                        printf("Under construction.");
                        fclose(cfile);
                    }
                    else
                    {
                        printf("\n\t\t\t\tIncorrect password.\n\t\t\t\t%d attempts left.", pass_attempts);
                        usleep(1500000);
                        system("cls");
                        goto tryPass_C;
                    }
                }
                else
                {
                    printf("Acount locked");
                    return;
                }
            }
        }
    }
    else
    {
        FILE *dfile = fopen("log_driver.csv", "r");
        printf("\n\t\t\t\tEnter log in id: ");
        scanf("%s", check_d.dlogin.id);

        while (fscanf(dfile, "%49[^|]|%19[^|]|%19[^\n]\n", add_d.name, add_d.dlogin.id, add_d.dlogin.pass) != EOF)
        {
            if (strcmp(add_d.dlogin.id, check_d.dlogin.id) == 0)
            {
            tryPass_D:
                if (pass_attempts > 0)
                {
                    printf("\n\t\t\t\tEnter password: ");
                    scanf("%s", check_d.dlogin.pass);
                    pass_attempts--;
                    system("cls");
                    if (strcmp(add_d.dlogin.pass, check_d.dlogin.pass) == 0)
                    {
                        printf("Loading");
                        loading();
                        printf("Under construction.");
                        fclose(dfile);
                    }
                    else
                    {
                        printf("\n\t\t\t\tIncorrect password.\n\t\t\t\t%d attempts left.", pass_attempts);
                        usleep(1500000);
                        system("cls");
                        goto tryPass_D;
                    }
                }
                else
                {
                    printf("Acount locked");
                    return;
                }
            }
        }
    }
}

int main()
{
    reg();
    return 0;
}