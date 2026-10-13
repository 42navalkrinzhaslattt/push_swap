# Push_swap

Sorts a list of integers with two stacks and eleven restricted operations, printing the shortest sequence it can find. It uses a greedy "cheapest move" insertion with combined rotations, plus a `checker` program that replays an operation list and verifies the result.

**Stack:** C · Make    **Context:** 42 Berlin curriculum

## Table of Contents
- [The Challenge](#the-challenge)
- [Algorithm: Greedy Cheapest Insertion](#algorithm-greedy-cheapest-insertion)
- [Operations](#operations)
- [Project Structure](#project-structure)
- [Build](#build)
- [Usage](#usage)
- [Bonus: Checker Program](#bonus-checker-program)
- [Implementation Details](#implementation-details)

## The Challenge

There are two stacks, `a` and `b`:
- **Stack a** starts with the input integers (unique, within `int` range)
- **Stack b** starts empty
- **Goal:** stack `a` sorted ascending (smallest on top), stack `b` empty, using as few operations as possible

The 42 subject grades the operation count: for full marks, 100 numbers must be sorted in fewer than 700 operations and 500 numbers in fewer than 5500.

## Algorithm: Greedy Cheapest Insertion

The first version (see git history) used a merge sort; it was replaced by the greedy approach below.

### Strategy
1. **Seed:** if `a` has more than 3 elements, push the first two to `b`.
2. **Pick the cheapest element:** for every element in `a`, compute how many moves it takes to bring it to the top of `a` while `b` is rotated so the element lands in the right place. `b` is kept in descending (circular) order.
3. **Push it:** perform those rotations, using `rr` / `rrr` whenever both stacks turn the same way, then `pb`.
4. Repeat until 3 elements remain in `a`, then sort those 3 with at most two operations.
5. **Merge back:** rotate `b` so its maximum is on top, then push elements back to `a`, rotating `a` in between so each one lands in order.

### Core Functions

#### `count_position()`
Returns the index in `b` where a value must be inserted to keep `b` descending. If the value is a new maximum or minimum, it goes above the current maximum.

#### `count_rotates()`
For element `i` in `a` with target index `j` in `b`, the cost is the minimum of four strategies:

| Strategy | Cost |
|----------|------|
| Both stacks rotate up (`rr`) | `max(i, j)` |
| Both stacks rotate down (`rrr`) | `max(size_a - i, size_b - j)` |
| `a` up, `b` down | `i + (size_b - j)` |
| `a` down, `b` up | `(size_a - i) + j` |

The cheapest element and its signed rotation counts are kept for the push step.

#### `push_sorted_elem()`
Executes the stored rotations (combined while both counts have the same sign, individual otherwise) and pushes the element to `b`.

#### `sort_a_under_3()` / `push_back_to_a()`
Hard-coded sorting for 2 or 3 elements, and the final merge from `b` into `a`.

### Complexity
Choosing each move scans every element of `a` and, for each, every element of `b`, so cost evaluation is O(n²) per push and O(n³) comparisons overall. That is fast enough for the 500-element case the subject targets.

## Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap first 2 elements of stack `a` |
| `sb` | Swap first 2 elements of stack `b` |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push top element from `b` to `a` |
| `pb` | Push top element from `a` to `b` |
| `ra` | Rotate stack `a` up (first becomes last) |
| `rb` | Rotate stack `b` up (first becomes last) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Reverse rotate stack `a` (last becomes first) |
| `rrb` | Reverse rotate stack `b` (last becomes first) |
| `rrr` | `rra` and `rrb` simultaneously |

## Project Structure

```
push_swap/
├── Makefile
├── includes/
│   ├── push_swap.h      # push_swap prototypes
│   ├── checker.h        # checker prototypes
│   ├── shared.h         # t_stack, t_data and shared functions
│   └── get_next_line.h  # used by checker
└── srcs/
    ├── push_swap/
    │   ├── push_swap.c           # entry point
    │   ├── greedy_sort.c         # cost computation and main loop
    │   └── greedy_sort_utils.c   # small-stack sort, merge back, helpers
    ├── shared/
    │   ├── check_input.c         # parsing, overflow and duplicate checks
    │   ├── operations.c          # swap / push / rotate (each prints its name)
    │   └── utils.c               # error_exit, is_sorted, helpers
    └── checker/
        ├── checker.c             # reads operations from stdin and replays them
        ├── get_next_line.c
        └── get_next_line_utils.c
```

## Build

```bash
make          # ./push_swap
make bonus    # ./checker
make clean    # remove object files
make fclean   # remove object files and both binaries
make re       # fclean + all
```

Sources are compiled with `-Wall -Wextra -Werror`; both binaries are linked with `-fsanitize=address -g`.

## Usage

### push_swap
```bash
# Prints the operations, one per line
./push_swap 4 67 3 87 23

# Count the operations
./push_swap 4 67 3 87 23 | wc -l

# No arguments, or already sorted input: prints nothing
./push_swap
./push_swap 1 2 3

# Each of these prints "Error" to stderr
./push_swap 42 42          # duplicate
./push_swap 42 abc         # not an integer
./push_swap 2147483648     # out of int range
```

Each number must be its own argument; a single quoted string such as `"3 2 1"` is rejected. Only a leading `-` is accepted as a sign.

## Bonus: Checker Program

`checker` takes the same arguments as `push_swap`, reads operations from stdin one per line, applies them, and finally prints both stacks followed by `OK` (stack `a` sorted and `b` empty) or `KO`. An unknown operation prints `Error` to stderr. Because it reuses the shared operation functions, it also echoes each executed operation, so the verdict is the last line of output:

```bash
# Verify push_swap's output
./push_swap 4 67 3 87 23 | ./checker 4 67 3 87 23 | tail -n 1
# OK

# Incorrect sequence
printf "sa\nra\n" | ./checker 2 1 3 6 5 8 | tail -n 1
# KO

# Unknown operation
printf "invalid_op\n" | ./checker 3 2 1 0
# Error (on stderr)
```

## Implementation Details

### Data Structures
```c
typedef struct s_stack
{
    long    *arr;    // elements, indexed circularly from start
    int     start;   // index of the top element
    int     size;    // current number of elements
    int     run;     // unused
} t_stack;

typedef struct s_data
{
    t_stack a;
    t_stack b;
} t_data;
```

- **Circular indexing:** `ra` / `rra` only move `start`, so rotations are O(1); pushes shift the array with `memmove`.
- **Input validation:** values are parsed as `long` and rejected as soon as they leave the `int` range; duplicates are found by copying the input and sorting it with a quicksort.
- **Shared code:** parsing and stack operations are compiled into both `push_swap` and `checker`.

---

42 Berlin project by Nam Lap Vu ([42navalkrinzhaslattt](https://github.com/42navalkrinzhaslattt)), 2023.
