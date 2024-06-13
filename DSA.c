/*
 * This file contains all the helper methods, struct definitions that could be used for competitive programming.
 *
 * Data Structures
 * 1. Dynamic lists.
 * 2. Hashmaps, Hashsets
 * 3. Stacks, Queue
 * 4. Linked List Node, Doubly Linked list
 * 5. Heaps: Min heap, Max heap
 * 6. Disjoint Set data structure
 *
 * Algorithms
 * 1. Reading input from console.
 * 2. Construct binary tree from level order traversal.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Binary Tree Node
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
 * Reads a single line of string that is space seperated and returns an array of integers.
 * `n`: Length of the input must be predefined.
 */
int* readLineIntegers(int n) {

    // Init variables
    char inp[n + n];
    int* numbers = (int *) malloc(n * sizeof(int));
    int i = 0;

    // Read a single line
    fgets(inp, sizeof(inp), stdin);
    getchar();

    // Split based on space and cast to int
    char* num = strtok(inp, " ");
    while (num != NULL) {
        numbers[i++] = atoi(num);
        num = strtok(NULL, " ");
    }

    return numbers;
}
