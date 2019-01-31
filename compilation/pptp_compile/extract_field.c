#include "extract_field.h"
#include <stdint.h>
#include <sys/types.h>
uint64_t extract_field (uint8_t * payload, int cur_pos, int field_length)
{

	switch (field_length)
	{
	case 1:
		return (uint64_t) * (uint8_t *) (payload + cur_pos);
	case 2:
		return (uint64_t) (ntohs (*(uint16_t *) (payload + cur_pos)));
	case 4:
		return (uint64_t) (ntohl (*(uint32_t *) (payload + cur_pos)));
		// case 8:
		//   return ntohll(*(uint64_t*)(payload + cur_pos));
	default:
		if (field_length <= 8)
		{
			uint64_t tmp = 0;
			for (int i = 0; i < field_length; i++)
			{
				tmp |=
					((uint64_t) * (payload + cur_pos + i)) << ((field_length -
						i - 1) * 8);
			}
			return tmp;
		}
		//raise error here
		return 0;
	}
}
