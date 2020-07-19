Demo code for a FIFO circular (ring) buffer.

in C

==================================================

Design ideas/decisions:

Has core basics functions for a typical FIFO ring buffer. There was
an attempt to make this safe for non blocking code, no printf's. Was
also designed for simplicity of code, improves maintainability.

For this example the structure is allocated in init, done once, rather as
items are added to ensure that there whole structure will be there
and faster access when pushing data.

Multiple ring buffers can be create as needed by the programmer. However
the designer is responsible for cleaning up after usage if desired.

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

Testing:
     Basic tests for overwrite and non-overwrite are provided.
     Additional tests could be added, I've noted some.

==================================================

Sample build and execution of test code.

To build:
cd ./ring_buf/
meson . build; cd build; ninja

On Debian 10 (buster) might look like this:
gandalf@QixII:~/projects/cubic/ring_buf$ meson . build; cd build; ninja; ./ring_buf
The Meson build system
Version: 0.49.2
Source dir: /home/gandalf/projects/cubic/ring_buf
Build dir: /home/gandalf/projects/cubic/ring_buf/build
Build type: native build
Project name: ring_buf
Project version: undefined
Native C compiler: cc (gcc 8.3.0 "cc (Debian 8.3.0-6) 8.3.0")
Build machine cpu family: x86_64
Build machine cpu: x86_64
Build targets in project: 1
Found ninja-1.8.2 at /usr/bin/ninja
[3/3] Linking target ring_buf.

==================================================
To example run:
./ring_buf

Typical results:
-test-start----------------------------

Test: Ring Buffer Overwrite Test
    : Size        = 100
    : Overwire    = 1
-----------------------------------
Buffer initialized.

******
Adding 102 values 
Full: 1, items: 100

******
Reading back values: 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 
-----------------------------end-test--

-test-start----------------------------

Test: Ring Buffer Overwrite Test
    : Size        = 100
    : Overwire    = 0
-----------------------------------
Buffer initialized.

******
Adding 102 values 
Warning: ring buffer full
Warning: ring buffer full
Full: 1, items: 100

******
Reading back values: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 
-----------------------------end-test--

*****************************************************
* TEST REPORT - ring_buf.c/.h                       *
*****************************************************
Test: Ring buffer, overwrite enabled, SUCCESS!
Test: Ring buffer, overwrite disabled, SUCCESS!
