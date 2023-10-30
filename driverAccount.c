#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

//regular colored text
#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
#define YELLOW_TEXT "\x1B[33m"
#define BLUE_TEXT "\x1B[34m"
#define RESET_TEXT "\x1B[0m"
#define PINK_TEXT "\x1B[35m"


//bold colored
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

typedef struct driver{
    char username[50];
    char name[50];
    char vehiclenum[15];

} driverdata;


void loading(void) {
    int i;
    int width = 40;  // Width of the loading bar

    for (i = 0; i <= width; i++) //for each iteration it prints some = and other spaces
    {
        // Printing the loading bar
        printf("\r%s[%s",BBLU, BRED);
        for (int j = 0; j < i; j++) {
            printf("=");
        }
    

        // Print spaces to clear the previous progress
        for (int j = i; j < width; j++) {
            printf(" ");
        }

        // Printing the percentage completion
        printf("%s] %d%%",BBLU, i * 100 / width);

        fflush(stdout);
        if (i%10==0) {usleep(500000);}
       else if (i<width/2) {usleep(65000);}
       else {usleep(20000);} 
    }
    printf("\n%sLoading Complete!%s\n", BGRN, RESET_TEXT);
    usleep(900000);
system("clear");
}


void driverpage(char input[]) //this needs to be a function where an input string is given
{ 
if (strcmp(input, "newaccount")==0)
 { FILE* dvr= fopen("driver.csv", "w");
 } 




else 
{ 
FILE* dvr= fopen("driver.csv", "r");
loading();


    //after the driver logs in, his name, vehicle, info and options to edit his info, and check his previous deliviries and due deliveries.
//option to cancel a delivery
char arr[100];
while (fgets(arr,100,dvr)!=NULL)
{printf("%s", arr);} 


//Name-
//Age-
//Vehicle no.
//vehicle type
fclose("driver.csv");
//due deliveries
//previous deliveries
//edit profile
//exit

}




   // return 0;
}


int main()
{ //loading();
driverpage("hello123");
    
    return 0;
}