#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"
#include "loading.h"
#define ID_PASS_MAX 20
int rerun=0;
int pass_attempts = 3;

void reg()
{  loading();

   rereg:
   system("clear");
    printf("\t\t\t\t\t\t\t%sREGISTER%s\t\t\t\n\n", BCYN, RESET_TEXT);
    printf("\t\t\t\t%sSelect account type: %s\n\n\t\t\t\t(1) Customer\n\t\t\t\t(2) Driver\n\t\t\t\t(3) Exit%s\n", YELLOW_TEXT, BLUE_TEXT, RESET_TEXT);
    int choice;
    printf("%s",GREEN_TEXT);
    enter(">>>", 4);
    printf("%s", RESET_TEXT);
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
        
        loading();

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
    else if (choice==3) 
    {
       rerun=1;
    }
    else 
    {   printf("\t\t\t\t%sINVALID CHOICE%s\n",RED_TEXT, RESET_TEXT); usleep(2000000);
        goto rereg;}
}

void loginf()
{   loading();
   
    printf("\t\t\t\t\t\t\t%sLOG IN%s\n\n", BCYN, RESET_TEXT);
    printf("\t\t\t\t%sSelect account type:%s \n\n\t\t\t\t%s(1) Customer\n\t\t\t\t(2) Driver%s\n", BYEL, RESET_TEXT, BLUE_TEXT, RESET_TEXT);
    int choice;
    printf("%s",GREEN_TEXT);
    enter(">>>", 4);
    printf("%s", RESET_TEXT);
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
{ system("clear");

    int ab=0;
    strt: system("clear");
printf("\t\t\t\t\t\t%sTRANSPORT MANAGEMENT SYSTEM%s\n\n",BWHT,RESET_TEXT);
printf("\t\t\t\t%s1. Log In Account\n\n\t\t\t\t2. Register New Account\n\n\t\t\t\t3. About%s\n\n\t\t\t\t%s", CYAN_TEXT, RESET_TEXT, GREEN_TEXT);
enter("Enter Choice : ", 4);
printf("%s", RESET_TEXT);
scanf("%d", &ab);
    switch(ab)
    { 
        case 1:
        {
            loginf();
            break;
        }

        case 2:
        { 
            reg();
            if (rerun==1) {goto strt;}
            break;
        }

        case 3:
        { system("clear");
        printf("%s", BYEL);
         char credits[1000]="\t\t\t\tEnd-Sem Project ||\t\t\t\tAaditya Sharma |\t\t\t\tUnmilan Das |\t\t\t\tPathya Taya |\t\t\t\tSwastik Mantri |\t\t\t\tSuvansh Sharma|";
        int key=0;
          while (credits[key]!='\0')
          { if (credits[key]=='|') {printf("\n%s", RESET_TEXT);}
          else
           { printf("%c", credits[key]);}
          fflush(stdout);
          key++;
          usleep(30000);
            }
            printf("\t\t\t\t");
            char esc;
            fflush(stdin);
            scanf("%c", &esc);
            goto strt;

            break;
        }
        default:
        {printf("\t\t\t\t%sINVALID CHOICE%s\n",RED_TEXT, RESET_TEXT); usleep(2000000);
          goto strt;
          break;}

    }
    return 0;
}
