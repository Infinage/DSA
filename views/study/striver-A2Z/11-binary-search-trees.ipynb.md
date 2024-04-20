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
    duration: 2.195359
    end_time: "2024-04-20T14:34:43.750138"
    environment_variables: {}
    input_path: study/striver-A2Z/11-binary-search-trees.ipynb
    output_path: study/striver-A2Z/11-binary-search-trees.ipynb
    parameters: {}
    start_time: "2024-04-20T14:34:41.554779"
    version: 2.5.0
---

<div id="5d747994" class="cell markdown"
papermill="{&quot;duration&quot;:9.434e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.624084&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.614650&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.559e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.641338&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.632779&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="4d1b31ca" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.659860Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.659514Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.669957Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.669305Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.194e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.671722&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.649782&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.315e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.688477&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.680162&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="960d5afe" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.706881Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.706544Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.717207Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.716471Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2044e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.718826&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.696782&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.512e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.735896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.727384&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KcNt6v_56cc?si=5YR5-7IR1paMMiXK> Search in
a BST:
<https://leetcode.com/problems/search-in-a-binary-search-tree/submissions/1232647689>

</div>

<div id="09688508" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.754824Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.754178Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.764636Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.763963Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1987e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.766373&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.744386&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.64e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.783580&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.774940&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KSsk8AhdOZA?si=2T66YUCRiC1Vr7Fs> Ceil in a
BST

</div>

<div id="519b483a" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.802684Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.801908Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.809277Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.808626Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8985e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.811074&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.792089&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.830647Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.830030Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.836929Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.836226Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8365e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.838617&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.820252&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.677e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.856207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.847530&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Floor in a BST Video Link:
<https://youtu.be/xm_W1ub-K-w?si=ay4JzgX4mwb1RkBM>

</div>

<div id="1674c736" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.874741Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.874191Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.880636Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.879847Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7784e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.882409&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.864625&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.577e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.901108&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.892531&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Insert node into BST Video Link:
<https://youtu.be/FiFiNvM29ps?si=gLkHgOWwfsCsZYiC>

</div>

<div id="2980e200" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.919897Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.919238Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.925171Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.924515Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7376e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.926874&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.909498&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.392e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.943962&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.935570&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node:
<https://leetcode.com/problems/delete-node-in-a-bst/submissions/1233565259>
Video Link: <https://youtu.be/kouxiP_H5WE?si=-J0yCkif1y5T8lLB>

</div>

<div id="7aa66408" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:42.963210Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:42.962485Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:42.972927Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:42.972170Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2189e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.974826&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.952637&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.531e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:42.991924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:42.983393&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Kth Smallest element in BST:
<https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/1234432057/>
Video Link: <https://youtu.be/9TJYWh0adfk?si=J5aaXBmrPA5E6LGC>

</div>

<div id="ce588656" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.011192Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.010332Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.017838Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.017185Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9314e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.019734&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.000420&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.556e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.037234&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.028678&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/f-sj7I5oXEI?si=Pz_LGZrgKIHXQxi4> Validate
a BST

</div>

<div id="e1f9a579" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.056733Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.055912Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.063153Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.062462Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9104e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.064920&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.045816&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.083812Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.083336Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.089283Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.088503Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7307e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.091051&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.073744&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="46ae2541" class="cell markdown"
papermill="{&quot;duration&quot;:8.497e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.108251&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.099754&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/cX_kPV_foZc?si=YCFaerCUNhJwiPEV> LCA in
Binary Search Tree:
<https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/>

</div>

<div id="8233e212" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.127168Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.126584Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.133611Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.132589Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9412e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.136148&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.116736&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/submissions/1235328177/
def lowestCommonAncestor(root: BinaryTreeNode, p: BinaryTreeNode, q: BinaryTreeNode) -> BinaryTreeNode:
    """
    Striver's Approach, simplified version of my approach.
    Time: O(log N), Space: O(1)
    """

    curr = root
    while curr:
        if curr.val < p.val and curr.val < q.val:
            curr = curr.right
        elif curr.val > p.val and curr.val > q.val:
            curr = curr.left
        else:
            break

    return curr

# Testing the solution
temp: BinaryTreeNode = BinaryTreeNode.from_array([6,2,8,0,4,7,9,None,None,3,5])
assert lowestCommonAncestor(temp, p=temp.left, q=temp.right).val == 6
```

</div>

<div id="538229a8" class="cell markdown"
papermill="{&quot;duration&quot;:8.51e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.153515&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.145005&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Construct BST from Preorder Traversal Video Link:
<https://youtu.be/UmJT3j26t1I?si=bZOGcW7usou-7xFK>

</div>

<div id="87fe0260" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.172217Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.171849Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.179060Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.178230Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8639e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.180778&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.162139&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/submissions/1235338251
def bstFromPreorderBrute(preorder: list[int]) -> BinaryTreeNode|None:
    "Time: O(N^2), Space: O(N)"
    def insert(curr: BinaryTreeNode|None, value: int) -> BinaryTreeNode:
        if not curr:
            return BinaryTreeNode(value)
        elif curr.val < value:
            curr.right = insert(curr.right, value)
            return curr
        else:
            curr.left = insert(curr.left, value)
            return curr

    root: BinaryTreeNode|None = None
    for value in preorder:
        root = insert(root, value)

    return root

# Testing the solution
assert bstFromPreorderBrute([8,5,1,7,10,12]).to_list() == [8,5,10,1,7,None,12]
assert bstFromPreorderBrute([1,3]).to_list() == [1,None,3]
```

</div>

<div id="cea4e83a" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.199666Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.199100Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.207151Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.206357Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9403e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.208845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.189442&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/submissions/1235351347
def bstFromPreorderBetter(preorder: list[int]) -> BinaryTreeNode|None:
    "Time: O(N log N) Space: O(N)"
    N = len(preorder)
    inorder = sorted(preorder)
    inorder_indices = {n: i for i, n in enumerate(inorder)}
    def createBT(pStart: int, pEnd: int, iStart: int, iEnd: int) -> BinaryTreeNode|None:
        if iEnd - iStart < 0:
            return None
        else:
            curr = BinaryTreeNode(preorder[pStart])
            idx = inorder_indices[curr.val]
            curr.left = createBT(pStart + 1, pStart + idx - iStart, iStart, idx - 1)
            curr.right = createBT(pStart + idx - iStart + 1, pEnd, idx + 1, iEnd)
            return curr

    return createBT(0, N - 1, 0, N - 1)

# Testing the solution
assert bstFromPreorderBetter([8,5,1,7,10,12]).to_list() == [8,5,10,1,7,None,12]
assert bstFromPreorderBetter([1,3]).to_list() == [1,None,3]
```

</div>

<div id="ac30bb42" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.227395Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.226747Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.235135Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.234339Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9474e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.236786&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.217312&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/submissions/1235363303/
def bstFromPreorderOptimal(preorder: list[int]) -> BinaryTreeNode:
    """
    Time: O(N), Space: O(N).
    0. Initialize stack containing tuple of nodes and upper bound values.
    1. We insert left if value to be inserted is less than last element in stack.
    2. We insert right if value to be inserted is less than the lower bound of last element in stack.
    3. If neither of above two holds, pop last element or recurse backwards.
    """
    root: BinaryTreeNode = BinaryTreeNode(preorder[0])
    stack: list[tuple[BinaryTreeNode, float]] = [(root, math.inf)]
    for value in preorder[1:]:
        curr = BinaryTreeNode(value)
        while stack:
            if value < stack[-1][0].val:
                stack[-1][0].left = curr
                stack.append((curr, stack[-1][0].val))
                break
            elif value < stack[-1][1]:
                stack[-1][0].right = curr
                stack.append((curr, stack[-1][1]))
                break
            else:
                stack.pop()

    return root

# Testing the solution
assert bstFromPreorderOptimal([8,5,1,7,10,12]).to_list() == [8,5,10,1,7,None,12]
assert bstFromPreorderOptimal([1,3]).to_list() == [1,None,3]
```

</div>

<div id="f916088f" class="cell markdown"
papermill="{&quot;duration&quot;:8.484e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.254100&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.245616&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder successor and predecessor of a BST Video Link:
<https://youtu.be/SXKAD2svfmI?si=MakIY0IWCvpCbHWB>

</div>

<div id="1d877037" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.273042Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.272378Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.278353Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.277528Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.737e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.279996&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.262626&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def predecessorSuccessor(root: BinaryTreeNode, key: int):
    """
    Find the floor, ceil of key.
    Time: O(H), Space: O(1)
    """
    # Find LB
    LB, curr = -1, root
    while curr:
        if curr.val < key:
            LB = curr.val
            curr = curr.right
        else:
            curr = curr.left

    # Find UB
    UB, curr = -1, root
    while curr:
        if curr.val > key:
            UB = curr.val
            curr = curr.left
        else:
            curr = curr.right

    return LB, UB
```

</div>

<div id="bee8b153" class="cell markdown"
papermill="{&quot;duration&quot;:8.381e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.297015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.288634&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

BST Iterator:
<https://leetcode.com/problems/binary-search-tree-iterator/submissions/1236174700/>
Video Link: <https://youtu.be/D2jMcmxU4bs?si=D8QZ784vB5u0LLPv>

</div>

<div id="350f423a" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.315803Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.315150Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.321448Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.320696Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7664e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.323313&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.305649&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class BSTIterator:
    """
    Space: O(H)
    Time: N spread over entire iteration O(N / N) ~ O(1) on average
    """
    def __init__(self, root: BinaryTreeNode):
        self.root = root

        self.stack: list[BinaryTreeNode] = []
        self.populateStack(self.root)

    def populateStack(self, curr: BinaryTreeNode):
        while curr:
            self.stack.append(curr)
            curr = curr.left

    def next(self) -> int:
        curr = self.stack.pop()
        if curr.right:
            self.populateStack(curr.right)

        return curr.val

    def hasNext(self) -> bool:
        return len(self.stack) > 0
```

</div>

<div id="59bb5f1f" class="cell markdown"
papermill="{&quot;duration&quot;:8.566e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.340346&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.331780&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ssL3sHwPeb4?si=Z4999grCFeuGVqKW> Two Sum
IV: BST Input

</div>

<div id="3d15c521" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.360175Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.359486Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.367397Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.366580Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9497e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.369131&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.349634&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/two-sum-iv-input-is-a-bst/submissions/1236189602/
def findTargetBrute(root: BinaryTreeNode, k: int) -> bool:
    "Time: O(N * log N), Space: O(1)"
    def find(target: int) -> bool:
        curr = root
        while curr:
            if curr.val == target:
                return True
            elif curr.val < target:
                curr = curr.right
            else:
                curr = curr.left
        return False

    queue: list[BinaryTreeNode] = [root]
    while queue:
        curr = queue.pop()
        if curr:
            if curr.val * 2 != k and find(k - curr.val):
                return True
            else:
                queue.append(curr.left)
                queue.append(curr.right)

    return False

# Testing the solution
assert findTargetBrute(BinaryTreeNode.from_array([5,3,6,2,4,None,7]), 10) == True
assert findTargetBrute(BinaryTreeNode.from_array([1]), 2) == False
```

</div>

<div id="8a27d83e" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.388155Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.387567Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.398103Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.397424Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1969e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.399847&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.377878&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/two-sum-iv-input-is-a-bst/submissions/1236198223/
def findTarget(root: BinaryTreeNode, k: int) -> bool:
    """
    Idea is to create a BST Iterator that yields the smallest and largest element respectively.
    Do a two pointer approach to two sum.

    Time: O(N), Space: O(H)
    """
    class BSTIterator:
        def __init__(self, root_: BinaryTreeNode):
            self.root = root_

            self.stack: list[BinaryTreeNode] = []
            self.populate(self.root, reverse=False)

            self.rstack: list[BinaryTreeNode] = []
            self.populate(self.root, reverse=True)

        def populate(self, curr: BinaryTreeNode, reverse: bool):
            while curr:
                if not reverse:
                    self.stack.append(curr)
                    curr = curr.left
                else:
                    self.rstack.append(curr)
                    curr = curr.right

        def next(self, reverse: bool) -> int:
            curr = self.stack.pop() if not reverse else self.rstack.pop()
            if not reverse and curr.right:
                self.populate(curr.right, reverse)
            elif reverse and curr.left:
                self.populate(curr.left, reverse)

            return curr.val

    bstIter = BSTIterator(root)
    l, r = bstIter.next(False), bstIter.next(True)
    while l < r:
        k_ = l + r
        if k_ == k:
            return True
        elif k_ < k:
            l = bstIter.next(False)
        else:
            r = bstIter.next(True)

    return False

# Testing the solution
assert findTarget(BinaryTreeNode.from_array([5,3,6,2,4,None,7]), 10) == True
assert findTarget(BinaryTreeNode.from_array([1]), 2) == False
```

</div>

<div id="db9c51ed" class="cell markdown"
papermill="{&quot;duration&quot;:8.671e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.417238&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.408567&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ZWGW7FminDM?si=fA6cUWtX4QjfjP6R> Recover
BST

</div>

<div id="d03db7ee" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.436077Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.435597Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.443761Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.443100Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9574e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.445414&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.425840&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def recoverTree(root: BinaryTreeNode) -> None:
    """
    Do an inorder traversal, mark violating nodes (curr < prev)
    If two matches found, swap and break. (Non adjacent swaps: [1, 3, 2, 4, 5])
    Else swap first match with next node. (Adjacent swaps: [1, 4, 3, 2, 5])

    Time: O(N), Space: O(H)
    """
    stack: list[BinaryTreeNode] = []
    prev: BinaryTreeNode|None = None
    curr: BinaryTreeNode|None = root
    first: BinaryTreeNode|None = None
    middle: BinaryTreeNode|None = None
    while curr or stack:
        if curr:
            stack.append(curr)
            curr = curr.left
        else:
            curr = stack.pop()
            if prev and curr.val < prev.val:
                if not first: # First violation
                    first = prev
                    middle = curr

                else: # Second violation
                    first.val, curr.val = curr.val, first.val
                    break

            prev = curr
            curr = curr.right

    else: # Second violation not found
        if first and middle:
            first.val, middle.val = middle.val, first.val

# Testing the solution
temp = BinaryTreeNode.from_array([1,3,None,None,2])
recoverTree(temp)
assert temp.to_list() == [3,1,None,None,2]
```

</div>

<div id="ac910fc7" class="cell markdown"
papermill="{&quot;duration&quot;:8.495e-3,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.462683&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.454188&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/X0oXMdtUDwo?si=z3aO6Q8fi6awJ9Th> Largest
BST in Binary Tree

</div>

<div id="f808ec64" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.481650Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.480898Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.488918Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.488147Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9403e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.490628&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.471225&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def largestBSTBrute(root: BinaryTreeNode) -> int:
    def isValid(curr: BinaryTreeNode, min_: float = -math.inf, max_: float = math.inf) -> int:
        if not curr:
            return 0
        else:
            left = isValid(curr.left, min_, curr.val)
            right = isValid(curr.right, curr.val, max_)
            if min_ < curr.val < max_ and left != -1 and right != -1:
                return 1 + left + right
            else:
                return -1

    # Do a level order traversal
    queue: list[BinaryTreeNode] = [root]
    result: int = -1
    while queue:
        next_: list[BinaryTreeNode] = []
        for curr in queue:
            if curr:
                result = max(result, isValid(curr))
                next_.append(curr.left)
                next_.append(curr.right)

        queue = next_

    return result

# Testing the solution
assert largestBSTBrute(BinaryTreeNode.from_array([5,2,4,1,3,None,None])) == 3
```

</div>

<div id="4a705ce6" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-20T14:34:43.509686Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-20T14:34:43.509002Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-20T14:34:43.520558Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-20T14:34:43.519784Z&quot;}"
papermill="{&quot;duration&quot;:2.3028e-2,&quot;end_time&quot;:&quot;2024-04-20T14:34:43.522408&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-20T14:34:43.499380&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def largestBST(root: BinaryTreeNode) -> float:
    """
    Do a post order traversal, returning size, min, max.

    - Curr is valid if maximum on left < curr < minimum on right.
    - Size: 1 + left_size + right_size

    If child is not a valid BST, parent is not a valid BST as well.

    Time: O(N), Space: O(H)
    """

    largest = -math.inf
    def postOrder(curr: BinaryTreeNode) -> tuple[int, float, float]:
        if not curr:
            return 0, math.inf, -math.inf
        else:

            left = postOrder(curr.left)
            right = postOrder(curr.right)

            # If valid BST
            if left[0] != -1 and right[0] != - 1 and left[2] < curr.val < right[1]:
                nonlocal largest
                largest = max(largest, 1 + left[0] + right[0])
                return 1 + left[0] + right[0], min(curr.val, left[1], right[1]), max(curr.val, left[2], right[2])

            # If invalid BST, upper recursive calls should fail as well. Use size = -1 as indicator
            else:
                return -1, 0, 0

    postOrder(root)
    return largest

# Testing the solution
assert largestBST(BinaryTreeNode.from_array([5,2,4,1,3,None,None])) == 3
largestBST(BinaryTreeNode.from_array([20,15,40,14,18,30,60,None,17,16,19,None,None,50]))
```

<div class="output execute_result" execution_count="22">

    4

</div>

</div>
