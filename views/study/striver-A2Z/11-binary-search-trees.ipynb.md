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
    duration: 1.615155
    end_time: "2024-04-16T03:00:04.226619"
    environment_variables: {}
    input_path: study/striver-A2Z/11-binary-search-trees.ipynb
    output_path: study/striver-A2Z/11-binary-search-trees.ipynb
    parameters: {}
    start_time: "2024-04-16T03:00:02.611464"
    version: 2.5.0
---

<div id="5d747994" class="cell markdown"
papermill="{&quot;duration&quot;:4.618e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.676040&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.671422&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/p7-9UvDQZ3w?si=YlQ8vk0wODSic1Hr>
Properties of Binary Search Trees

1.  Left node \< Root node \< Right node.
2.  Left subtree, Right subtree should itself be a BST.
3.  Ideally there are no duplicates. However to allow duplicates, we can
    modify the condition to something like: Left \<= Root \< Right.
    Alternatively we could save a tuple of values (value, freq).
4.  Balanced BST search: O(log N)

</div>

<div id="a1a768de" class="cell markdown"
papermill="{&quot;duration&quot;:3.959e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.912567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.908608&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="4d1b31ca" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:03.921577Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:03.921265Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:03.931830Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:03.931176Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7192e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.933501&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.916309&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.691e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.941013&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.937322&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="960d5afe" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:03.949618Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:03.949366Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:03.959262Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:03.958500Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6217e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.960928&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.944711&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.683e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.968331&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.964648&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KcNt6v_56cc?si=5YR5-7IR1paMMiXK> Search in
a BST:
<https://leetcode.com/problems/search-in-a-binary-search-tree/submissions/1232647689>

</div>

<div id="09688508" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:03.977038Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:03.976499Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:03.986536Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:03.985874Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6141e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.988153&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.972012&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.812e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:03.995825&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.992013&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KSsk8AhdOZA?si=2T66YUCRiC1Vr7Fs> Ceil in a
BST

</div>

<div id="519b483a" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:04.004832Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:04.004169Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:04.010664Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:04.009925Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2715e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.012297&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:03.999582&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:04.021498Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:04.021205Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:04.027287Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:04.026538Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2637e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.028965&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:04.016328&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.83e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.036772&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:04.032942&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Floor in a BST Video Link:
<https://youtu.be/xm_W1ub-K-w?si=ay4JzgX4mwb1RkBM>

</div>

<div id="1674c736" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:04.045718Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:04.045442Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:04.051511Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:04.050847Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2579e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.053231&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:04.040652&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.865e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.061116&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:04.057251&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Insert node into BST Video Link:
<https://youtu.be/FiFiNvM29ps?si=gLkHgOWwfsCsZYiC>

</div>

<div id="2980e200" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:04.070318Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:04.069682Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:04.075602Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:04.074968Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2356e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.077276&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:04.064920&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.819e-3,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.085161&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:04.081342&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node:
<https://leetcode.com/problems/delete-node-in-a-bst/submissions/1233565259>
Video Link: <https://youtu.be/kouxiP_H5WE?si=-J0yCkif1y5T8lLB>

</div>

<div id="7aa66408" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-16T03:00:04.094390Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-16T03:00:04.093838Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-16T03:00:04.103710Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-16T03:00:04.103065Z&quot;}"
papermill="{&quot;duration&quot;:1.6227e-2,&quot;end_time&quot;:&quot;2024-04-16T03:00:04.105350&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-16T03:00:04.089123&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
