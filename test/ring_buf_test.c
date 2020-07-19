/*
Example of a FIFO ring buffer.

Steven MacDonald macdsteven@gmail.com

Some GPL or public license would go here, from the legal department. 2020.
*/

/*
Future tests if desired.
 Test two buffers at some time, same type.
 Test two buffers at same time, different type.
 Buffer size is limited to uint8. Extend?
 Extend to varous data format tests. Limited to uint_8
 Buffer of incredibly large size test.
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ring_buf.h"

int ring_buf_test(uint8_t size, bool overwrite, uint8_t expected_result)
{
	uint8_t test_output;
	uint8_t *buffer = malloc(size*sizeof(uint8_t));

	printf("\n-test-start----------------------------\n");
	printf("Test: Ring Buffer Overwrite Test\n");
	printf("    : Size        = %d\n",size);
	printf("    : Overwrite    = %d\n",overwrite);
	printf("-----------------------------------\n");

	ring_obj rb = ring_buf_init(buffer, size, overwrite);

	printf("Buffer initialized.\n");

	printf("\n******\nAdding %d values \n", size + 2);
	for(uint8_t i = 0; i < size+2; i++)
	{
		if(ring_buf_push(rb, i)==-1)
			printf("Warning: ring buffer full\n");
	}

	printf("Full: %d, items: %zu\n", ring_buf_full(rb), ring_buf_size(rb));

	printf("\n******\nReading back values: ");
	while(!ring_buf_empty(rb))
	{
		uint8_t data;

		ring_buf_pull(rb, &data);
		printf("%u ", data);
		test_output=data; // only testing against the last output
	}

	free(buffer);
	ring_buf_free(rb);

	printf("\n-----------------------------end-test--\n");

	if (expected_result == test_output){
		return 0;
	} else {
		return -1;
	}
}

int main(void)
{
	int t1,t2; // fails are -1, so signed

	t1 = ring_buf_test(100, true, 101);
	t2 = ring_buf_test(100, false, 99);

	printf("\n");
	printf("*****************************************************\n");
	printf("* TEST REPORT - ring_buf.c/.h                       *\n");
	printf("*****************************************************\n");

	if (t1 == 0){
		printf("Test: Ring buffer, overwrite enabled, SUCCESS!\n");
	} else {
		printf("Test: Ring buffer, overwrite enabled, FAILED\n");
	}
	if (t2 == 0){
		printf("Test: Ring buffer, overwrite disabled, SUCCESS!\n");
	} else {
		printf("Test: Ring buffer, overwrite disabled, FAILED\n");
	}
	printf("*****************************************************\n");
}

