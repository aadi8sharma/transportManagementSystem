#include <stdio.h>

#define ID_PASS_MAX 20

struct LoginDetails
{
    char id[ID_PASS_MAX];
    char pass[ID_PASS_MAX];
};

struct Vehicle
{
    char vehicleNumber[20];

} newVehicle, viewVehicle, delVehicle;

struct Customer
{
    char name[50];
    struct LoginDetails clogin;

} add_c, check_c, upd_c, read_c;

struct Order
{
    struct Customer cus;
    char pick_loc[100];
    char del_dest[100];
    char item[100];
    int quantity;
} add_o, upd_o, check_o, read_o;

struct Driver
{
    char name[50];
    struct LoginDetails dlogin;
    struct Vehicle curr_veh;
    int order_id;
} add_d, check_d, upd_d, read_d, del_d;

struct customer_record
{
    int customer_order_id;
    char pickup[100];
    char item[100];
    char destination[100];
    int quantity;
    char customer_ID[ID_PASS_MAX];
}record, read_co;
