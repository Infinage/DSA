---
jupyter:
  kernelspec:
    display_name: Python 3 (ipykernel)
    language: python
    name: python3
  language_info:
    codemirror_mode:
      name: ipython
      version: 3
    file_extension: .py
    mimetype: text/x-python
    name: python
    nbconvert_exporter: python
    pygments_lexer: ipython3
    version: 3.10.14
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 1.517167
    end_time: "2024-04-17T16:25:33.437242"
    environment_variables: {}
    input_path: study/striver-A2Z/11-binary-search-trees.ipynb
    output_path: study/striver-A2Z/11-binary-search-trees.ipynb
    parameters: {}
    start_time: "2024-04-17T16:25:31.920075"
    version: 2.5.0
---

<div id="5d747994" class="cell markdown"
papermill="{&quot;duration&quot;:5.51e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.001948&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:32.996438&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/p7-9UvDQZ3w?si=YlQ8vk0wODSic1Hr>
Properties of Binary Search Trees

1.  Left node \< Root node \< Right node.
2.  Left subtree, Right subtree should itself be a BST.
3.  Ideally there are no duplicates. However to allow duplicates, we can
    modify the condition to something like: Left \<= Root \< Right.
    Alternatively we could save a tuple of values (value, freq).
4.  Balanced BST search: O(log N)
5.  Inorder traversal of a BST is always in a sorted order.

</div>

<div id="a1a768de" class="cell markdown"
papermill="{&quot;duration&quot;:4.747e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.011711&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.006964&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="4d1b31ca" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.022993Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.022257Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.032237Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.031591Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7664e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.034040&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.016376&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
import bisect
import heapq
```

</div>

<div id="558424e6" class="cell markdown"
papermill="{&quot;duration&quot;:4.635e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.043772&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.039137&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="960d5afe" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.055063Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.054414Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.064571Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.063893Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7808e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.066251&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.048443&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class BinaryTreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def to_list(self):
        to_visit = [self]
        visited = []
        while len(to_visit) > 0:
            curr = to_visit.pop(0)
            if curr:
                to_visit.append(curr.left)
                to_visit.append(curr.right)
                visited.append(curr.val)
            else:
                visited.append(curr)

        while visited and not visited[-1]:
            visited.pop()

        return visited

    def __str__(self):
        return str(self.val)

    @staticmethod
    def from_array(nums: list[int|None]):
        '''Create a Tree from a list of nums. Returns the root node.'''
        if len(nums) == 0:
            return None
        elif len(nums) == 1:
            return BinaryTreeNode(nums[0])
        else:
            forest = [BinaryTreeNode(nums[0])]
            parent_idx = -1
            for i in range(1, len(nums)):

                curr = None
                if nums[i] is not None:
                    curr = BinaryTreeNode(nums[i])
                    forest.append(curr)

                if i % 2 == 1:
                    parent_idx += 1
                    forest[parent_idx].left = curr
                else:
                    forest[parent_idx].right = curr

        return forest[0]
```

</div>

<div id="3fccb5da" class="cell markdown"
papermill="{&quot;duration&quot;:4.654e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.075985&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.071331&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KcNt6v_56cc?si=5YR5-7IR1paMMiXK> Search in
a BST:
<https://leetcode.com/problems/search-in-a-binary-search-tree/submissions/1232647689>

</div>

<div id="09688508" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.086888Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.086425Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.096636Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.095794Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7624e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.098338&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.080714&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def searchBST(root: BinaryTreeNode, val: int) -> BinaryTreeNode:
    "Time: O(log N)"
    if not root or root.val == val:
        return root
    elif root.val < val:
        return searchBST(root.right, val)
    else:
        return searchBST(root.left, val)

# Testing the solution
searchBST(BinaryTreeNode.from_array([4,2,7,1,3]), 2).to_list()
```

<div class="output execute_result" execution_count="3">

    [2, 1, 3]

</div>

</div>

<div id="051180ef" class="cell markdown"
papermill="{&quot;duration&quot;:4.797e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.108275&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.103478&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KSsk8AhdOZA?si=2T66YUCRiC1Vr7Fs> Ceil in a
BST

</div>

<div id="519b483a" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.120028Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.119359Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.126348Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.125563Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.475e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.127947&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.113197&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Recursive solution
def findCeilRecurse(root: BinaryTreeNode, x: int) -> int:
    "Smallest value greater than or equal to target."
    ceil = -1
    def backtrack(curr: BinaryTreeNode):
        nonlocal ceil
        if not curr:
            return
        elif curr.val >= x:
            ceil = curr.val
            backtrack(curr.left)
        else:
            backtrack(curr.right)

    backtrack(root)
    return ceil

# Testing the solution
assert findCeilRecurse(BinaryTreeNode.from_array([8,5,10,2,6,None,None,None,None,None,7,None,None]), 9) == 10
assert findCeilRecurse(BinaryTreeNode.from_array([10,5,13,3,6,11,14,2,4,None,9]), 11) == 11
```

</div>

<div id="96103462" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.139202Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.138574Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.144774Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.144018Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3813e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.146707&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.132894&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Iterative solution
def findCeilIter(root: BinaryTreeNode, x: int) -> int:
    "Smallest value greater than or equal to target."
    curr, ceil = root, -1
    while curr:
        if curr.val >= x:
            ceil = curr.val
            curr = curr.left
        else:
            curr = curr.right

    return ceil

# Testing the solution
assert findCeilIter(BinaryTreeNode.from_array([8,5,10,2,6,None,None,None,None,None,7,None,None]), 9) == 10
assert findCeilIter(BinaryTreeNode.from_array([10,5,13,3,6,11,14,2,4,None,9]), 11) == 11
```

</div>

<div id="2c170dfe" class="cell markdown"
papermill="{&quot;duration&quot;:4.729e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.156319&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.151590&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Floor in a BST Video Link:
<https://youtu.be/xm_W1ub-K-w?si=ay4JzgX4mwb1RkBM>

</div>

<div id="1674c736" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.167687Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.166924Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.173292Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.172661Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3857e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.175022&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.161165&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def findFloor(root: BinaryTreeNode, key: int) -> int:
    curr, floor = root, -1
    while curr:
        if curr.val <= key:
            floor = curr.val
            curr = curr.right
        else:
            curr = curr.left

    return floor

# Testing the solution
assert findFloor(BinaryTreeNode.from_array([8,5,10,2,6,None,None,None,None,None,7,None,None]), 9) == 8
assert findFloor(BinaryTreeNode.from_array([10,5,13,3,6,11,14,2,4,None,9]), 11) == 11
```

</div>

<div id="f882be29" class="cell markdown"
papermill="{&quot;duration&quot;:4.798e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.184726&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.179928&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Insert node into BST Video Link:
<https://youtu.be/FiFiNvM29ps?si=gLkHgOWwfsCsZYiC>

</div>

<div id="2980e200" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.196161Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.195490Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.201167Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.200553Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3107e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.202804&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.189697&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def insertIntoBST(root: BinaryTreeNode, val: int) -> BinaryTreeNode:
    prev: BinaryTreeNode|None = None
    curr: BinaryTreeNode|None = root

    while curr:
        prev = curr
        if curr.val > val:
            curr = curr.left
        else:
            curr = curr.right

    curr = BinaryTreeNode(val)
    if prev:
        if prev.val > val:
            prev.left = curr
        else:
            prev.right = curr

    return root if prev else curr
```

</div>

<div id="d29f77f3" class="cell markdown"
papermill="{&quot;duration&quot;:4.842e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.212735&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.207893&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node:
<https://leetcode.com/problems/delete-node-in-a-bst/submissions/1233565259>
Video Link: <https://youtu.be/kouxiP_H5WE?si=-J0yCkif1y5T8lLB>

</div>

<div id="7aa66408" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.224446Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.223828Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.233951Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.233209Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8104e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.235890&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.217786&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def deleteNode(root: BinaryTreeNode, key: int) -> BinaryTreeNode|None:
    """
    Time: O(Height), Space: O(1)
    1. Find curr such that curr.val = key (curr is node to be deleted)
    2. curr.right would become the new curr. curr.right.left should point to curr.left
    3. curr.left's rightmost node's right should point to curr.right.left
    """
    def delete(parent: BinaryTreeNode|None, node: BinaryTreeNode):
        if node.right and node.left:
            # Find rightmost node in node.left
            left: BinaryTreeNode = node.left
            while left.right:
                left = left.right
            left.right = node.right.left
            node.right.left = node.left

        # Updated curr node post node deletion
        post_delete = node.right if node.right else node.left

        # If parent exists, modify parent right pointer to skip node being deleted
        if parent:
            if parent.val < node.val:
                parent.right = post_delete
            else:
                parent.left = post_delete

        # If parent doesn't exist, node is root. We return new root
        else:
            nonlocal root
            root = post_delete

    prev: BinaryTreeNode|None = None
    curr: BinaryTreeNode|None = root

    while curr:
        if curr.val == key:
            delete(prev, curr)
            break
        elif curr.val < key:
            prev, curr = curr, curr.right
        else:
            prev, curr = curr, curr.left

    return root

# Testing the solution
assert deleteNode(BinaryTreeNode.from_array([5,3,6,2,4,None,7]), 3).to_list() == [5,4,6,2,None,None,7]
assert deleteNode(BinaryTreeNode.from_array([2,1]), 2).to_list() == [1]
assert deleteNode(BinaryTreeNode.from_array([3,2,4,1]), 2).to_list() == [3,1,4]
```

</div>

<div id="bef16c0a" class="cell markdown"
papermill="{&quot;duration&quot;:4.797e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.246960&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.242163&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Kth Smallest element in BST:
<https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/1234432057/>
Video Link: <https://youtu.be/9TJYWh0adfk?si=J5aaXBmrPA5E6LGC>

</div>

<div id="ce588656" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.257946Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.257445Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.264013Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.263282Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3895e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.265698&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.251803&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def kthSmallest(root: BinaryTreeNode, k: int) -> int:
    """
    Do an inorder traversal, storing the elements into an array. Return kth element.

    Time: O(N), Space: O(N)
    To eliminate space: O(N), we can use Morris Inorder traversal
    """

    stack: list[BinaryTreeNode] = []
    curr: BinaryTreeNode = root
    while curr or stack:
        if curr:
            stack.append(curr)
            curr = curr.left
        else:
            if stack:
                curr = stack.pop()
                if k == 1:
                    return curr.val
                else:
                    curr = curr.right
                    k -= 1

    return -1

# Testing the solution
for i in range(1, 8):
    assert kthSmallest(BinaryTreeNode.from_array([1,None,2,None,3,None,4,None,5,None,6,None,7]), i) == i
```

</div>

<div id="e1c64a13" class="cell markdown"
papermill="{&quot;duration&quot;:4.802e-3,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.276399&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.271597&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/f-sj7I5oXEI?si=Pz_LGZrgKIHXQxi4> Validate
a BST

</div>

<div id="e1f9a579" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.287752Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.287154Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.293475Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.292741Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3846e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.295193&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.281347&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/validate-binary-search-tree/submissions/1234444341
def isValidBST(root: BinaryTreeNode) -> bool:
    """
    Do an inorder traversal, if at any point curr < prev it is not a valid BST.

    Time: O(N), Space: O(N)
    """

    prev = -math.inf
    stack: list[BinaryTreeNode] = []
    curr: BinaryTreeNode = root
    while stack or curr:
        if curr:
            stack.append(curr)
            curr = curr.left
        else:
            curr = stack.pop()
            if curr.val <= prev:
                return False
            else:
                prev = curr.val
                curr = curr.right

    return True

# Testing the solution
assert isValidBST(BinaryTreeNode.from_array([5,4,6,None,None,3,7])) == False
assert isValidBST(BinaryTreeNode.from_array([2,2,2])) == False
```

</div>

<div id="142f7fb4" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-17T16:25:33.307535Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-17T16:25:33.306899Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-17T16:25:33.313307Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-17T16:25:33.312462Z&quot;}"
papermill="{&quot;duration&quot;:1.4021e-2,&quot;end_time&quot;:&quot;2024-04-17T16:25:33.315050&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-17T16:25:33.301029&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/validate-binary-search-tree/submissions/1234448368
def isValidBST_striver(root: BinaryTreeNode, min_: float= -math.inf, max_: float = math.inf) -> bool:
    # Time: O(N), Space: O(1)
    if not root:
        return True
    else:
        return min_ < root.val < max_ and isValidBST_striver(root.left, min_, root.val) and isValidBST_striver(root.right, root.val, max_)

# Testing the solution
assert isValidBST_striver(BinaryTreeNode.from_array([5,4,6,None,None,3,7])) == False
assert isValidBST_striver(BinaryTreeNode.from_array([2,2,2])) == False
```

</div>
