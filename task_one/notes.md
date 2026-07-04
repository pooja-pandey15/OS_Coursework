# Task 1 - Design Notes (working draft)

## Stage 1: Basic thread creation
- Created 3 threads using pthread_create, each running a worker() function.
- Passed each thread's ID via a separate array (thread_ids[]) rather than the loop
  variable directly, to avoid all threads reading the same memory location after
  the loop finishes.
- Used pthread_join so main() waits for all threads to complete before exiting.
- Observed threads starting in order (0,1,2) but finishing in a different order
  each run - evidence of genuine concurrent execution, not sequential.

## Stage 2: Demonstrating a race condition
- Introduced a shared global variable (shared_counter) incremented by all 3 threads,
  100,000 times each, with no protection.
- counter++ is not atomic - it compiles to 3 separate CPU steps (read, add, write),
  so threads can interleave between these steps and overwrite each other's updates.
- Ran the program 3 times. Results varied: 100,000 / 300,000 / 115,897
  (expected: 300,000 every time). The inconsistency itself is the key evidence of
  a race condition, since a deterministic bug would fail identically every time.
- This confirmed shared_counter must be protected before it can be trusted -
  addressed in Stage 3 using a mutex.

## Stage 3: Fixing the race condition with a mutex
- Introduced a pthread_mutex_t (counter_lock), initialized with pthread_mutex_init.
- Wrapped the critical section (shared_counter++) with pthread_mutex_lock/unlock,
  ensuring only one thread can execute that line at a time.
- Ran the program 3 times: all three runs produced the correct value of 300,000,
  with zero loss - a direct contrast to Stage 2's inconsistent, incorrect results.
- Note: thread completion order still varies between runs (e.g. 0,2,1 then 1,2,0)
  - the mutex guarantees correctness of the shared variable, not a fixed execution
  order. This distinction (mutual exclusion vs scheduling order) is an important
  OS concept.
- Cleaned up the mutex with pthread_mutex_destroy once no longer needed, to avoid
  resource leaks.


## Stage 4: Round-robin scheduler simulation
- Simulated 4 processes with different burst times (10, 5, 8, 3 units) using a
  fixed quantum of 3 units.
- Each process runs for min(remaining burst time, quantum) per turn, then moves
  to the back of the cycle if not yet finished.
- Verified fairness property: Process 4 (shortest job, 3 units) completed first
  (at time 12) despite starting last, because round-robin gives every process a
  turn rather than running jobs to completion in arrival order.
- Calculated turnaround time (completion time) and waiting time (turnaround -
  burst time) per process, plus averages (13.50 waiting, 20.00 turnaround) -
  standard metrics for evaluating scheduling algorithm performance.
