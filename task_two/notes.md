# Task 2 notes

## 1_fifo.c
Phone can only hold 3 apps in memory at once.
FIFO closes whichever app was opened first (oldest), not caring if it might be needed again soon.
Used apps list: 1,2,3,4,1,2,5,1,2,3,4,5
Result: 3 hits, 9 faults.
