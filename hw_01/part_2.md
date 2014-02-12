# Part 2 
## Cost of fork()

Usage: `./part2 <size-in-MB>`

The program `./part2` loops 10,000 times to compute the average cost of a `fork()` call. In each loop, a timer is started and then an array of `<size-in-MB>` MB is allocated and initialized. `fork()` is called and the parent waits for the child using `waitpid()`. Once the child returns, the parent records the time of this `fork()` call in usecs. The following is a chart of the results:

![image](file:///Users/alextang/Code/RU/operating_systems/hw_01/part2.jpg =600x)