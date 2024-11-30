# Analysis of Time Complexity vs. Observed Performance

## Binary Search Tree (BST)

### Expected Complexity:
- **Insert**: O(log n) (degrades to O(n) if unbalanced)
- **Search/Delete**: O(log n)

### Observed Performance:
- Insertion time increases significantly with dataset size, indicating unbalanced behavior, especially for larger datasets.
- Search and delete times align with expected O(log n) for smaller datasets but degrade for larger datasets due to imbalance.

### Conclusion:
BST behaves as expected for small datasets but shows degradation toward O(n) for large datasets, confirming it is not self-balancing.

---

## AVL Tree

### Expected Complexity:
- **Insert/Search/Delete**: O(log n)

### Observed Performance:
- All operations consistently exhibit logarithmic time growth.
- Insertions take slightly longer than BST due to rebalancing, but search and delete remain efficient.

### Conclusion:
AVL Tree matches the expected O(log n) complexity for all operations due to automatic balancing.

---

## B-Tree

### Expected Complexity:
- **Insert/Search/Delete**: O(log n)

### Observed Performance:
- Insertion times are slightly higher due to node splitting.
- Search and delete times remain consistently low, reflecting logarithmic complexity.

### Conclusion:
B-Tree performance is consistent with O(log n), but its insertions are more complex due to multi-way branching, making it slower than AVL for inserts.
