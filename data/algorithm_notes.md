# 🧮 Algorithmic Space Optimization Note

## The Challenge
The standard Longest Common Subsequence (LCS) algorithm relies on dynamic programming. For two sequences of lengths $m$ and $n$, it constructs a 2D matrix of size $(m+1) \times (n+1)$. 

In typical desktop environments, this is trivial. However, in embedded systems like the ATmega328P with only 2KB of SRAM, calculating the LCS for a 100-character string and a 120-character string requires `100 * 120 * 2 bytes = 24,000 bytes` (24KB), which results in an immediate memory crash.

## The Bitwise Solution
If we observe the DP state transition:
`L[i][j] = L[i-1][j-1] + 1` (if characters match)
`L[i][j] = max(L[i-1][j], L[i][j-1])` (if they don't match)

We realize that calculating the current row `i` ONLY requires the values from the current row `i` and the previous row `i-1`. The rest of the matrix is useless after the calculation moves forward.

By reducing the matrix to `L[2][n+1]` and using the bitwise AND operator `i & 1` to switch between row `0` and row `1`, we reduce the space complexity from $O(m \times n)$ to $O(\min(m, n))$.

This optimization allows the micro-controller to process much larger configuration files without exceeding its strict memory limits.
