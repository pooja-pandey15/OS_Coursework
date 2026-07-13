# Task 2 notes

## 1_fifo.c
Phone can only hold 3 apps in memory at once.
FIFO closes whichever app was opened first (oldest), not caring if it might be needed again soon.
Used apps list: 1,2,3,4,1,2,5,1,2,3,4,5
Result: 3 hits, 9 faults.

## 2_lru.c
Same 3 memory slots and same app list as before.
LRU closes whichever app hasn't been used for the longest time, instead of just the oldest one.
Result: 2 hits, 10 faults - actually worse than FIFO here.
This shows LRU isn't always better, it depends on the pattern of app usage.


## 3_compare.c
Runs FIFO and LRU on the same app list and prints both results together.
FIFO: 3 hits, 9 faults
LRU: 2 hits, 10 faults
FIFO did better here, which shows no single algorithm is always the best, it depends on the pattern of the reference string.
