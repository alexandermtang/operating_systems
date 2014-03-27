## Alexander Tang
## CS 344 - HW 2
===
 
# Part 3
## Signaling on xv6

**Usage**: `./signal_test`

Signaling on xv6 was implemented as another system call on xv6. Please run `git diff` to see all the changes.

# Part 4
## What is the cost of an exception on xv6?

**Usage**: `./signal_test`

The average time of a single exception handler was determined to be about 48300 microseconds. This was measured by deliberately accessing an address outside the process' space, causing a page fault. After letting the process trap 1000 times, some assembly code was used to skip the faulty C instruction. The average of 1000 exceptions was taken to find the cost of a single exception on xv6.

# Part 5
## Compare the cost of a signal on Linux vs xv6

- Cost of a signal on Linux: 0.75 microseconds
- Cost of a signal on xv6: 48300 microseconds

The cost of a signal on xv6 is much greater than the cost of a signal on Linux.