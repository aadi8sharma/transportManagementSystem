#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "customer.h"

void driver_login(char isid[])
{
	FILE *dDetails=fopen("driver_details.csv","r");
	FILE *orders=fopen("orders.csv","r");
	int chk=0,p;
	while(fscanf(dDetails,"%19[^|]|%49[^|]|%19[^|]|%d\n",read_d.dlogin.id,read_d.name,read_d.curr_veh.vehicleNumber,&read_d.order_id)!=EOF)
	{
		if(strcmp(isid, read_d.dlogin.id) == 0)
		{
			chk=1;
			break;
	}
	}
	if(chk==1)
	{
	while(fscanf(orders,"%d|%99[^|]|%99[^|]|%d|%99[^|]|%19[^\n]\n",&record.customer_order_id, record.pickup, record.item, &record.quantity, record.destination, record.customer_ID)!=EOF)
			{
				if(read_d.order_id == record.customer_order_id)
				{
				printf("Driver name: %s\nVehicle number: %s\nOrder number: %d\n\nPickup location: %s\nItem: %s\nQuantity: %d\nDestination: %s", read_d.name, read_d.curr_veh.vehicleNumber, record.customer_order_id, record.pickup, record.item, record.quantity, record.destination);
				p=1;
				break;
				}
			}
	if(p==0)
	printf("Database error");
	}
	fclose(orders);
	fclose(dDetails);
}
