# W4824 Computer Architecture Project 1

Author: Carmen Wu, Michael Stone

## Log
* **October 7, 2020
Ran the original dram_test.c program for various buffer sizes using repetition size of 1000. Notice constant jumps in clock ticks in all test cases. We also observed that the first cycle in every test with buffer size greater than 32, takes the most number of clock ticks and significantly higher than the average clock ticks. We have the same observation for both computers. However, when buffer size drops to 32 bytes and below, the significant jump in the first cycle disappear. The number of click in the first cycle in such cases are in-line with the average number of clicks.

* **October 14, 2020
Modified dram_test.c to output the number of ticks for each cycle and the total number of ticks for each test. Wrote a python program to plot the number of clock ticks for each test case. Each test case has a different buffer size. Given that the number of ticks is significantly higher in the first cycle across all test cases, we decide that the graphs of raw data is skewed by the number of ticks in the first cycle. Therefore, we made two graphs for each test case: one with raw data; the other one with normalized data that excludes the highest 1% and lowest 1% number of ticks. In the normalized graphs, we observed "fault lines". These graphs shows number of clock ticks are at about the same level at the beginning. But then the number of ticks dropped consistently to a lower level. And the number of ticks stayed at this level till the end.

* **October 17, 2020
We suspect that the "fault lines" observed from the graphs generated on October 14 are related to cache not being completely flushed. It is possible that clflush() function in the original dram_test.c program only flushes one cache line, rather than our original assumption that it flushes the entire cache of linebuffer and linebuffercopy. We therefore created a modified version dram_test_modified.c, which aims to flush the entire cache for linebuffer and linebuffercopy. Based on our research, most cache lines are of size 32 bytes, 64 bytes and 128 bytes. Our modified program call clflush() every 32 bytes, to be conservative, on linebuffer and linebuffercopy.

## Observation
* Significant number of clock ticks in the first cycle. We believe in the first cycle, extra time is neede for initial setup, setting up TLB for initial tranlation of virtual addresses to physical address, etc.

* The jump in number of ticks during the first cycle disappears when buffer size is 32 bytes or below. This is likely due to the buffer size being insignificant to spare the extra time needed for initial setup.

* There are constant jumps in clock ticks through all cycles in all test cases. This is likely due to the processer prioritizing other programs over the dram_test program causing the memcopy() to wait.

* open row policy

* Initially our assumption on function clflush() is that it flushes out the entire cache related to linebuffer and linebuffercopy. The "fault lines" observed in the graphs, however, suggests that it is not the case. We suspect that clflush() does not flush the whole cache, otherwise there would not have been a dip in the number of ticks overall after the program has run for some cycles. Assuming that clflush() flushes only one cache line (size 32 bytes or 64 bytes in most cases), we modified the dram_test.c program to call clflush() enough time in each cycle to ensure clearing the entire cache. The result is that the number of ticks are lowered in the modified program compared to the original program.



