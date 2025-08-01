# Push_swap

*"Because Swap_push doesn't feel as natural"*

## Table of Contents
- [Project Overview](#project-overview)
- [The Challenge](#the-challenge)
- [Algorithm Overview](#algorithm-overview)
- [My Solution: Greedy Algorithm](#my-solution-greedy-algorithm)
- [Operations](#operations)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Usage](#usage)
- [Performance Benchmarks](#performance-benchmarks)
- [Bonus: Checker Program](#bonus-checker-program)
- [Implementation Details](#implementation-details)

## Project Overview

Push_swap is an algorithmic challenge from 42 School that focuses on sorting data efficiently using a limited set of operations. The goal is to sort a stack of integers using the minimum number of operations possible.

This project teaches:
- Algorithm optimization and complexity analysis
- Data structure manipulation (stacks)
- Problem-solving with constraints
- Performance optimization

## The Challenge

You have two stacks named `a` and `b`:
- **Stack a**: Initially contains a random number of unique integers
- **Stack b**: Initially empty
- **Goal**: Sort stack `a` in ascending order (smallest number at the top)

### Constraints
- Only specific operations are allowed
- Must achieve sorting with the minimum number of operations
- No global variables allowed
- Must handle all edge cases and errors

## Algorithm Overview

My implementation uses a **Greedy Algorithm** approach, which is efficient for medium to large datasets and consistently performs well within the required benchmarks.

### Algorithm Strategy:
1. **Initial Setup**: Push first 2 elements from stack `a` to stack `b`
2. **Greedy Selection**: For each remaining element in stack `a`, calculate the cost of moving it to its optimal position in stack `b`
3. **Cost Optimization**: Choose the element with the minimum movement cost
4. **Efficient Rotation**: Use combined rotations (`rr`, `rrr`) when both stacks need rotation in the same direction
5. **Final Sorting**: Sort the remaining 3 elements in stack `a` using optimized swaps and rotations
6. **Push Back**: Push all elements from stack `b` back to stack `a` in the correct order

## My Solution: Greedy Algorithm

### Core Functions:

#### `greedy_sort()`
The main sorting function that orchestrates the entire process:
- Handles initial pushes to stack `b` 
- Implements the greedy selection loop
- Calls helper functions for final sorting and cleanup

#### `count_rotates()`
Calculates the minimum cost to move an element from stack `a` to its correct position in stack `b`:
- Considers 4 different rotation strategies:
  1. Both stacks rotate forward (`rr`)
  2. Both stacks rotate backward (`rrr`) 
  3. Stack `a` forward, stack `b` backward
  4. Stack `a` backward, stack `b` forward
- Selects the strategy with minimum total operations

#### `count_position()`
Finds the optimal insertion position for an element in stack `b`:
- Maintains stack `b` in descending order
- Handles edge cases (largest/smallest elements)
- Returns the index where the element should be inserted

#### `push_sorted_elem()`
Executes the calculated rotations and pushes the element:
- Optimizes by using combined operations (`rr`, `rrr`) when possible
- Performs individual rotations when stacks need opposite directions

### Key Optimizations:

1. **Combined Rotations**: Uses `rr` and `rrr` to rotate both stacks simultaneously when beneficial
2. **Smart Position Finding**: Maintains stack `b` in descending order for efficient insertion
3. **Minimal Operations for Small Sets**: Special handling for 2-3 elements in stack `a`
4. **Efficient Push-back**: Optimized algorithm to push elements back from stack `b` to stack `a`

## Operations

The following operations are available:

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
│   ├── push_swap.h      # Main program headers
│   ├── checker.h        # Bonus program headers
│   ├── shared.h         # Shared structures and functions
│   └── get_next_line.h  # GNL for bonus
├── srcs/
│   ├── push_swap/
│   │   ├── push_swap.c           # Main program entry point
│   │   ├── greedy_sort.c         # Core greedy algorithm
│   │   └── greedy_sort_utils.c   # Helper functions
│   ├── shared/
│   │   ├── check_input.c         # Input validation and parsing
│   │   ├── operations.c          # Stack operations implementation
│   │   └── utils.c              # Utility functions
│   └── checker/
│       ├── checker.c            # Bonus program
│       ├── get_next_line.c      # Read instructions from stdin
│       └── get_next_line_utils.c
└── README.md
```

## Compilation

```bash
# Compile the main program
make

# Compile the bonus checker
make bonus

# Clean object files
make clean

# Full clean (remove executables)
make fclean

# Recompile everything
make re
```

## Usage

### Push_swap Program
```bash
# Basic usage
./push_swap 4 67 3 87 23

# Example output
pb
ra
pb
rr
sa
pa
pa

# Check number of operations
./push_swap 4 67 3 87 23 | wc -l

# No arguments (outputs nothing)
./push_swap

# Error cases
./push_swap 42 42          # Duplicates
./push_swap 42 abc         # Invalid input
./push_swap 2147483648     # Integer overflow
```

### Checker Program (Bonus)
```bash
# Verify a solution
./push_swap 4 67 3 87 23 | ./checker 4 67 3 87 23
# Output: OK

# Manual verification
./checker 3 2 1 0
rra
pb
sa
rra
pa
# Output: OK

# Invalid operations
./checker 3 2 1 0
invalid_op
# Output: Error
```

## Performance Benchmarks

My implementation consistently meets the required performance standards:

### Required Performance:
- **100 numbers**: < 700 operations (for 100% score)
- **500 numbers**: < 5500 operations (for 100% score)

### Minimum Acceptable Performance:
- **100 numbers**: < 1100 operations (for 80% score)
- **500 numbers**: < 8500 operations (for 80% score)

### Algorithm Complexity:
- **Time Complexity**: O(n²) - Each element requires checking positions in the other stack
- **Space Complexity**: O(n) - Two stacks containing all elements
- **Operation Count**: Typically achieves well within benchmark requirements

## Bonus: Checker Program

The bonus `checker` program validates whether a sequence of operations correctly sorts the stack:

### Features:
- Reads stack from command line arguments
- Accepts operations from standard input
- Validates each operation
- Checks if final result is correctly sorted
- Comprehensive error handling

### Usage Example:
```bash
# Test with known good solution
echo -e "sa\npb\npb\npb\nsa\npa\npa\npa" | ./checker 2 1 3 6 5 8
# Output: OK

# Test with incorrect solution
echo -e "sa\nra" | ./checker 2 1 3 6 5 8
# Output: KO
```

## Implementation Details

### Data Structures
```c
typedef struct s_stack
{
    long    *arr;    // Array to store stack elements
    int     start;   // Index of the top element (circular buffer)
    int     size;    // Current number of elements
    int     run;     // Maximum capacity
} t_stack;

typedef struct s_data
{
    t_stack a;       // Stack A
    t_stack b;       // Stack B
} t_data;
```

### Key Features:
- **Circular Buffer Implementation**: Efficient rotation operations without data movement
- **Long Integer Storage**: Prevents overflow during input validation
- **Memory Management**: Proper allocation and deallocation
- **Error Handling**: Comprehensive input validation and error reporting
- **Modular Design**: Separate files for different functionalities

### Algorithm Efficiency:
The greedy approach ensures that each decision is locally optimal, leading to consistently good global performance. While not always producing the absolute minimum number of operations, it reliably performs within the required benchmarks and handles all edge cases effectively.

---

**Author**: nam-vu (42Berlin)  
**Project**: push_swap (42 School)  
**Language**: C  
**Completion**: 2023
