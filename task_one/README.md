# Task 1: Process Management and Threading

Simple examples showing threads, race conditions, mutex locks, round robin scheduling, and deadlock.
Scenario used: printers sharing print jobs.

## Files

- 1_threads.c - creates 3 threads (printers), each prints a message
- 2_race_condition.c - two threads update a shared counter with no protection, shows wrong results
- 3_mutex_fix.c - same as above but with a mutex lock, shows correct results
- 4_round_robin.c - simulates 3 printers taking turns on a job queue
- 5_deadlock.c - two threads each need two locks, shows a deadlock and then the fix

## How to compile and run

Each file is separate. Example for file 1:

```bash
gcc 1_threads.c -o 1_threads -lpthread
./1_threads
```

Same pattern for the others (2, 3, 5 also need -lpthread, file 4 does not since it has no threads).

For 5_deadlock.c, run it with timeout so it doesn't hang forever if it deadlocks:

```bash
timeout 5 ./5_deadlock
```

To switch between the unsafe (deadlock) and safe (fixed) version, open 5_deadlock.c and comment/uncomment this line at the top:

```c
// #define SAFE 1
```

## Notes

See notes.md for what each file does and what the results were.
Screenshots of the output are in the screenshots folder.
