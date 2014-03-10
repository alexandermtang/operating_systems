## Alexander Tang
## CS 344 - HW 2
===
 
# Part 1
## What is the cost of an exception?

**Usage**: `./part1`


The average time of a single exception handler was determined to be about 0.75 microseconds. This was measured by deliberately causing a divide by zero error, causing the kernel to send a SIGFPE signal. In order to force the process to skip the faulty C instruction, `gdb` was used to determined the return address relative to the current frame pointer. On the ilab machine, this offset was determined to be 60 bytes. The value of the return address was incremented by 8, or two assembly instructions (as determined by viewing the assembly file), in order to skip the faulty C instruction.