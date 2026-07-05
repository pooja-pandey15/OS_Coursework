# Task 1: Process Management and Threading

## Overview
This program demonstrates multi-threaded process management concepts in C using
POSIX threads (pthreads). It is split into two parts:

1. **Round-robin task scheduler simulation** - 3 worker threads take turns
   (strict rotation, enforced with a condition variable) claiming and completing
   tasks from a shared queue. Access to shared data is protected by a mutex.
2. **Deadlock prevention demonstration** - two threads each require two mutexes.
   Consistent lock acquisition order across both threads prevents deadlock.

## Concepts demonstrated
- Thread creation and synchronization (`pthread_create`, `pthread_join`)
- Mutex locking to prevent race conditions (`pthread_mutex_t`)
- Condition variables for turn-based coordination (`pthread_cond_t`)
- Round-robin scheduling simulation
- Deadlock avoidance via consistent lock ordering

## Requirements
- Linux environment (developed and tested on Ubuntu 24.04)
- gcc compiler
- pthread library (included with gcc on Linux by default)

## How to compile

```bash
gcc scheduler.c -o scheduler -lpthread
```

## How to run

```bash
./scheduler
```

## Expected output
The program will:
1. Print each thread claiming and completing tasks in strict round-robin order
   (Thread 0, 1, 2, 0, 1, 2, ...) until all 9 tasks are completed.
2. Then run the deadlock prevention demo, showing both threads successfully
   acquiring both mutexes and completing without any deadlock or timeout.

## Development history
This program was built incrementally across 5 stages, each demonstrating one
concept in isolation before being combined into the final version above:
1. Basic thread creation
2. Race condition demonstration (unprotected shared counter)
3. Race condition fix (mutex)
4. Round-robin scheduler simulation (standalone)
5. Deadlock demonstration and prevention (consistent lock ordering)

Full details of each stage, including reasoning and test results, are in
`notes.md`. Screenshots of program output at each stage are in `screenshots/`.
The complete commit history is available in the project's git log.
