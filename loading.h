#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// regular colored text
#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
#define YELLOW_TEXT "\x1B[33m"
#define BLUE_TEXT "\x1B[34m"
#define RESET_TEXT "\x1B[0m"
#define PINK_TEXT "\x1B[35m"
#define CYAN_TEXT "\x1B[36m"
// bold colored
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

// Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

void loading(void)
{  
    int i;
    int width = 40; // Width of the loading bar
    printf("\n");
    for (i = 0; i <= width; i++) // for each iteration it prints some = and other spaces
    {   
        // Printing the loading bar
        printf("\r\t\t\t\t%s[%s", BBLU, BRED);
        for (int j = 0; j < i; j++)
        {
            printf("=");
        }

        // Print spaces to clear the previous progress
        for (int j = i; j < width; j++)
        {
            printf(" ");
        }

        // Printing the percentage completion
        printf("%s] %d%%", BBLU, i * 100 / width);

        fflush(stdout);
        if (i % 15 == 0)
        {
            usleep(500000);
        }
        else if (i < width / 2)
        {
            usleep(65000);
        }
        else
        {
            usleep(20000);
        }
    }
    printf("\n\t\t\t\t%sLoading Complete!%s\n", BGRN, RESET_TEXT);
    usleep(900000);
    system("clear");
}


void enter(char ent[], int t)
{ printf("\n");
int count=0;
while (count<t) {printf("\t"); count++;}
int key=0;
          while (ent[key]!='\0')
          { count=0;
            if (ent[key]=='|') {printf("\n");  while (count<t) {printf("\t"); count++;}}
          else
           { printf("%c", ent[key]);}
          fflush(stdout);
          key++;
          usleep(30000);
          
            }
           
}
