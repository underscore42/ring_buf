/*
Example of a FIFO ring buffer.

Steven MacDonald macdsteven@gmail.com

Some GPL or public license would go here, from the legal department. 2020.
*/

/*
Has core basics functions for a typical FIFO ring buffer. There was
an attempt to make this safe for non blocking code, no printf's. Was
also designed for simplicity of code, improves maintainability.

Basic public parts:
     structure
     init (size up to a uint8 (0-255), "filedescriptor", data can overwrite?)
     free (clean up after yourself)
     empty (blank but don't destroy)
     size (how many elements are currently in there)
     push (single elment push)
     pull (returns data via passed variable, has success/fail error code)
      

Limitations:
     number of elements.
     data formats

*/

#ifndef RING_BUF_H_
#define RING_BUF_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>

typedef struct ring_buf_t ring_buf_t;
typedef ring_buf_t* ring_obj;

/**/
bool ring_buf_full(ring_obj rb);
size_t ring_buf_size(ring_obj rb);
size_t ring_buf_max_size(ring_obj rb);
void ring_buf_free(ring_obj rb);
void ring_buf_reset(ring_obj rb);

/* Core ring buffer functions */
bool ring_buf_empty(ring_obj rb);
ring_obj ring_buf_init(uint8_t *buffer, size_t size, bool overwrite);
int ring_buf_push(ring_obj rb, uint8_t data);
int ring_buf_pull(ring_obj rb, uint8_t *data);

#endif //RING_BUF_H_
