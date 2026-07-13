# Task 2: Memory Management Simulation

Simple examples showing page replacement algorithms (FIFO and LRU).
Scenario used: a phone with limited storage, only able to keep 3 apps open in memory at once.

## Files

- 1_fifo.c - simulates FIFO page replacement, closes the oldest opened app when memory is full
- 2_lru.c - simulates LRU page replacement, closes the least recently used app when memory is full
- 3_compare.c - runs both algorithms on the same app list and compares hits/faults

## How to compile and run

```bash
gcc 1_fifo.c -o 1_fifo
./1_fifo
```

Same pattern for 2_lru.c and 3_compare.c (no extra libraries needed, just gcc).

## Notes

See notes.md for what each file does and the results.
Screenshots of the output are in the screenshots folder.
