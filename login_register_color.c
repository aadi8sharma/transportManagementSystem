#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "admin_login_details.h"
#define ID_PASS_MAX 20
int rerun=0;


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
    {   system("clear");
        FILE *cfile = fopen("log_customer.csv", "a+");

       // printf("\n\n\t\t\t\tEnter your name: ");
        enter("Name : ", 4);
        scanf("%s", add_c.name);
        //printf("\n\t\t\t\tEnter new login id: ");
        enter("New Username : ", 4);
        scanf("%s", add_c.clogin.id);
        //printf("\n\t\t\t\tEnter new password: ");
        enter("New Password : ", 4);
        scanf("%s", add_c.clogin.pass);

        if (!cfile)
        {
            // error in file opening
            printf("\t\t\t\tCan't open file.\n");
            return;
        }

        system("clear");
        fprintf(cfile, "%s|%s|%s\n", add_c.name, add_c.clogin.id, add_c.clogin.pass); // add record to database
        
        printf("\n\t\t\t\t%sPlease wait while we create your account%s", YELLOW_TEXT, RESET_TEXT);
        loading();

        fclose(cfile);
        rerun=1;
    }



    else if (choice == 2)
    {
        FILE *dfile = fopen("log_driver.csv", "a+");

        //printf("\n\t\t\t\tEnter your name: ");
        enter("Name : ", 4);

        scanf("%s", add_d.name);

        //printf("\n\t\t\t\tEnter new login id: ");
        enter("New Username : ", 4);

        scanf("%s", add_d.dlogin.id);

        //printf("\n\t\t\t\tEnter new password: ");
        enter("New Password : ", 4);

        scanf("%s", add_d.dlogin.pass);
        if (!dfile)
        {
            // error in file opening
            printf("\t\t\t\tCan't open file.\n");
            return;
        }
        system("clear");
        fprintf(dfile, "%s|%s|%s\n", add_d.name, add_d.dlogin.id, add_d.dlogin.pass); // add record to database

        printf("\n\t\t\t\t%sPlease wait while we create your account%s", YELLOW_TEXT, RESET_TEXT);
       loading();
       
        fclose(dfile);
        rerun=1;
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
int pass_attempts = 3;
relogin:
 pass_attempts = 3;
  
    printf("\t\t\t\t\t\t\t%sLOG IN%s\n\n", BCYN, RESET_TEXT);
    printf("\t\t\t\t%sSelect account type:%s \n\n\t\t\t\t%s(1) Customer\n\t\t\t\t(2) Driver%s\n", BYEL, RESET_TEXT, BLUE_TEXT, RESET_TEXT);
    int choice;
    printf("%s",GREEN_TEXT);
    enter(">>>", 4);
    printf("%s", RESET_TEXT);
    scanf("%d", &choice);
    system("clear");
    
    if (choice == 1)
    {
        FILE *cfile = fopen("log_customer.csv", "r");

        //printf("\n\t\t\t\tEnter log in id: ");
        enter("Username : ", 4);

        scanf("%s", check_c.clogin.id);

        while (fscanf(cfile, "%49[^|]|%19[^|]|%19[^\n]\n", add_c.name, add_c.clogin.id, add_c.clogin.pass) != EOF)
        {
            if (strcmp(add_c.clogin.id, check_c.clogin.id) == 0)
            {
            tryPass_C:
                if (pass_attempts > 0)
                {
                    //printf("\n\t\t\t\tEnter password: ");
                    enter("Password : ", 4);

                    scanf("%s", check_c.clogin.pass);
                    pass_attempts--;
                    system("clear");
                    if (strcmp(add_c.clogin.pass, check_c.clogin.pass) == 0)
                    {
                        printf("\n\t\t\t\t%sKindly wait while we fetch your account%s", YELLOW_TEXT,RESET_TEXT);
                        loading();
                        printf("Under construction.");
                        fclose(cfile);
                    }
                    else
                    {
                        printf("\n\t\t\t\t%sIncorrect password.%s\n\t\t\t\t%d attempts left.\n",RED_TEXT,RESET_TEXT, pass_attempts);
                        usleep(1500000);
                        system("clear");
                        goto tryPass_C;
                    }
                }
                else
                {    fflush(stdout);
                     fflush(stdin);
                     for (int i = 30; i > 0; i--)

                    {
                        printf("Account temporarily disabled, wait for %d seconds", i);
                        usleep(1000000);
                        system("clear");
                    }
                    pass_attempts = 3;
                    goto tryPass_C;
                }
            }
        }
    }
    else if (choice == 2)
    {
        FILE *dfile = fopen("log_driver.csv", "r");

        //printf("\n\t\t\t\tEnter log in id: ");
        enter("Username : ", 4);

        scanf("%s", check_d.dlogin.id);

        while (fscanf(dfile, "%49[^|]|%19[^|]|%19[^\n]\n", add_d.name, add_d.dlogin.id, add_d.dlogin.pass) != EOF)
        {
            if (strcmp(add_d.dlogin.id, check_d.dlogin.id) == 0)
            {
            tryPass_D:
                if (pass_attempts > 0)
                {
                    //printf("\n\t\t\t\tEnter password: ");
                    enter("Password : ", 4);

                    scanf("%s", check_d.dlogin.pass);
                    pass_attempts--;
                    system("clear");
                    if (strcmp(add_d.dlogin.pass, check_d.dlogin.pass) == 0)
                    {
                        printf("\n\t\t\t\t%sKindly wait while we fetch your account%s", YELLOW_TEXT,RESET_TEXT);
                        loading();
                        printf("Under construction.");
                        fclose(dfile);
                    }
                    else
                    {
                        printf("\n\t\t\t\t%sIncorrect password.%s\n\t\t\t\t%d attempts left.",RED_TEXT,RESET_TEXT, pass_attempts);
                        usleep(1500000);
                        system("clear");
                        goto tryPass_D;
                    }
                }
                else
                {
                    for (int i = 60; i > 0; i--)
                    {
                        printf("Account temporarily disabled, wait for %d seconds", i);
                        usleep(1000000);
                        system("clear");
                    }
                    pass_attempts = 3;
                    goto tryPass_D;
                }
            }
        }
    }
    else if (choice == 3) {rerun=1;}
    else {  printf("\t\t\t\t%sINVALID CHOICE%s\n",RED_TEXT, RESET_TEXT); usleep(2000000);
        goto relogin; }
}

int main()
{ system("clear");

    int ab=0;
    strt: system("clear");
printf("\t\t\t\t\t\t%sTRANSPORT MANAGEMENT SYSTEM%s\n\n",BWHT,RESET_TEXT);
printf("\t\t\t\t%s1. Log In Account\n\n\t\t\t\t2. Register New Account\n\n\t\t\t\t3. About\n\n\t\t\t\t4. Admin Login\n\n\t\t\t\t%s", CYAN_TEXT, GREEN_TEXT);
enter("Enter Choice : ", 4);
printf("%s", RESET_TEXT);
scanf("%d", &ab);
    switch(ab)
    { 
        case 1:
        {
            loginf();
            if (rerun==1) {goto strt;}
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

        case 4:
        {
                int pass_attempts = 3;
              system("clear");
              char admin_key[50];
              adminTry:
              if (pass_attempts > 0)
        {
            pass_attempts--;
            printf("\t\t\t\t\t\t\tADMIN LOG IN");
            printf("\n\n\t\t\t\tEnter key: ");
            scanf("%s", admin_key);
            if (strcmp(admin_key, ADMIN_PASS) == 0)
            {
                loading();
                admin();
            }
            else
            {
                printf("\n\t\t\t\tIncorrect key.\n\t\t\t\t%d attempts left.", pass_attempts);
                usleep(1500000);
                system("clear");
                goto adminTry;
            }
        }
        else
        {
            for (int i = 60; i > 0; i--)
            {
                printf("Account temporarily disabled, redirecting to main menu in %d seconds", i);
                usleep(1000000);
                system("clear");
            }
            goto strt;
          //  main();
        }
        break;

        }
        default:
        {printf("\t\t\t\t%sINVALID CHOICE%s\n",RED_TEXT, RESET_TEXT); usleep(2000000);
          goto strt;
          break;}

    }
    return 0;
}
