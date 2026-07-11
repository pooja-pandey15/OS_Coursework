# Task 1 notes

## 1_threads.c
Made 3 threads, each one is a "printer" that just prints a start and done message.
Order of output changes each run because threads run independently,
 not one after another.

## 2_race_condition.c
Two threads both add to jobs_done at the same time, no lock.
Ran it 3 times, got 3 different wrong numbers (128927, 100131, 150272) instead of 
200000.
This happens because jobs_done++ is not one step, it's read-add-write, 
so threads can overlap and lose updates.

## 3_mutex_fix.c
Same as before but added a mutex lock around jobs_done++.
Now only one thread can touch jobs_done at a time.
Ran it 3 times, got exactly 200000 every time. Fixed.

## 4_round_robin.c
3 printers take turns, one job each, round and round until all 9 jobs are done.
Turn number wraps back to 0 after printer 2 using turn % printers.
This is a simple version, no threads here, just simulating the turn order.

