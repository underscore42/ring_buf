/*
Example of a FIFO ring buffer.

Steven MacDonald macdsteven@gmail.com

Some GPL or public license would go here, from the legal department. 2020.
*/

/*
Notes:
ring_buf struct is sort of private, not exposed in header.
incr_addr and decr_addr are private
*/


#include "ring_buf.h"

struct ring_buf_t {
	uint8_t *buffer;
	size_t read_ptr;
	size_t write_ptr;
	size_t max; //of the buffer
	bool overwrite; // allow for overwrites
	bool full; // derived from read_ptr and write_ptr on incr and decr
};

//Private functions
static void incr_addr(ring_obj rb)
{
	if(ring_buf_full(rb))
		rb->write_ptr = (rb->write_ptr + 1)%rb->max;
	rb->read_ptr = (rb->read_ptr + 1)%rb->max;
	rb->full = (rb->read_ptr == rb->write_ptr);
}

static void decr_addr(ring_obj rb)
{
	rb->full = false;
	rb->write_ptr = (rb->write_ptr + 1)%rb->max;
}

//Public functions
bool ring_buf_full(ring_obj rb)
{
	assert(rb); // make sure we have something to work with
	return(rb->full);
}

size_t ring_buf_size(ring_obj rb)
{
	assert(rb);
	size_t size = rb->max;
	if(!rb->full){
		if(rb->read_ptr >= rb->write_ptr)
			size = (rb->read_ptr - rb->write_ptr);
		else
			size = (rb->max + rb->read_ptr - rb->write_ptr);
	}
	return size;
}

size_t ring_buf_max_size(ring_obj rb)
{
	assert(rb);
	return rb->max;
}

void ring_buf_free(ring_obj rb)
{
	if (rb!=NULL)
		free(rb);
}


bool ring_buf_empty(ring_obj rb)
{
	assert(rb);
	return (!rb->full && (rb->read_ptr == rb->write_ptr));
}

ring_obj ring_buf_init(uint8_t *buffer, size_t size, bool overwrite)
{
	assert(buffer && size);
	ring_obj rb = malloc(sizeof(ring_buf_t));
	assert(rb);

	rb->buffer = buffer;
	rb->max = size;
	rb->overwrite = overwrite;
	ring_buf_reset(rb);
	assert(ring_buf_empty(rb));

	return rb;
}

void ring_buf_reset(ring_obj rb)
{
	assert(rb);
	rb->read_ptr = 0;
	rb->write_ptr = 0;
	rb->full = false;
	//rb->overwrite don't change, as only reseting data, not type of ring
}

int ring_buf_push(ring_obj rb, uint8_t data)
{
	int rv =0;

	assert(rb && rb->buffer);
	if (rb->overwrite){
		rb->buffer[rb->read_ptr] = data;
		incr_addr(rb);
	} else {
		if(!ring_buf_full(rb))
		{
			rb->buffer[rb->read_ptr] = data;
			incr_addr(rb);
		} else {
			rv = -1;
			//printk("Warning: ring buffer full\n"); // use printk if in kernel
		}
	}
	return rv;
}

int ring_buf_pull(ring_obj rb, uint8_t *data)
{
	int rv =-1;

	assert(rb && data && rb->buffer);
	if(!ring_buf_empty(rb))
	{
		*data = rb->buffer[rb->write_ptr];
		decr_addr(rb);
		rv = 0;
	}

	return rv;
}
