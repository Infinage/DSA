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
    duration: 1.303426
    end_time: "2024-04-15T16:15:47.070485"
    environment_variables: {}
    input_path: study/striver-A2Z/11-binary-search-trees.ipynb
    output_path: study/striver-A2Z/11-binary-search-trees.ipynb
    parameters: {}
    start_time: "2024-04-15T16:15:45.767059"
    version: 2.5.0
---

<div id="5d747994" class="cell markdown"
papermill="{&quot;duration&quot;:3.151e-3,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.843807&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.840656&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.354e-3,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.848718&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.846364&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="4d1b31ca" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:46.855250Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:46.854469Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:46.864373Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:46.863634Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.509e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.866186&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.851096&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.345e-3,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.871011&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.868666&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="960d5afe" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:46.877323Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:46.876700Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:46.886482Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:46.885845Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4706e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.888081&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.873375&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.41e-3,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.892956&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.890546&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KcNt6v_56cc?si=5YR5-7IR1paMMiXK> Search in
a BST:
<https://leetcode.com/problems/search-in-a-binary-search-tree/submissions/1232647689>

</div>

<div id="09688508" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:46.899182Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:46.898631Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:46.909151Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:46.908310Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5485e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.910868&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.895383&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.136e-3,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.917487&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.914351&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KSsk8AhdOZA?si=2T66YUCRiC1Vr7Fs> Ceil in a
BST

</div>

<div id="519b483a" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:46.925823Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:46.925229Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:46.934509Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:46.933684Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5481e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.936258&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.920777&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:46.943089Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:46.942473Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:46.948403Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:46.947778Z&quot;}"
papermill="{&quot;duration&quot;:1.1117e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:46.950112&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:46.938995&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
