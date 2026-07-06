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


## Stage 2: LRU page replacement
- Same 3 frames and identical 12-page reference string as Stage 1, for direct comparison.
- Tracked a "last_used" timestamp per frame, updated on every access (hit or fault).
  On a fault with no free frames, evicted whichever frame had the smallest
  (oldest) last_used value.
- Result: 2 hits, 10 faults (16.67% hit ratio) - WORSE than FIFO's 3 hits/9 faults
  on this same reference string.
- Key finding: this shows that no replacement algorithm is universally best -
  performance depends on the specific access pattern. Here, LRU's eviction choice
  at request 9 (evicting page 5) left page 1 vulnerable to eviction sooner than
  FIFO's choice did, causing one extra fault later in the sequence.
