# Task 2 - Design Notes (working draft)

## Stage 1: FIFO page replacement
- Simulated 3 physical frames and a 12-page reference string (a standard
  textbook example: 1,2,3,4,1,2,5,1,2,3,4,5).
- Used an "oldest_index" pointer that cycles through frames in order,
  implementing First-In-First-Out eviction: whichever page was loaded first
  gets evicted first when a new page must be brought in and frames are full.
- Result: 3 hits, 9 faults out of 12 requests (25% hit ratio).
- Notable inefficiency observed: page 1 was evicted at request 3, then
  immediately needed again at request 4, causing an avoidable fault - this
  demonstrates FIFO's key weakness, it ignores how soon a page will be reused.
