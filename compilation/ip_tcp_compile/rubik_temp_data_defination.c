#include "rubik_interface.h"
#include "rubik_temp_data_defination.h"
#include <stdlib.h>
struct pure_ip_temp_data_t *pure_ip_temp_data;
struct temp_t *temp;
void temp_data_init ()
{
	pure_ip_temp_data = malloc (sizeof (struct pure_ip_temp_data_t));
	temp = malloc (sizeof (struct temp_t));
}
