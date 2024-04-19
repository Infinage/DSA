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
    duration: 1.864363
    end_time: "2024-04-19T15:53:11.524564"
    environment_variables: {}
    input_path: study/striver-A2Z/11-binary-search-trees.ipynb
    output_path: study/striver-A2Z/11-binary-search-trees.ipynb
    parameters: {}
    start_time: "2024-04-19T15:53:09.660201"
    version: 2.5.0
---

<div id="5d747994" class="cell markdown"
papermill="{&quot;duration&quot;:8.155e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.710795&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.702640&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.25e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.725536&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.718286&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="4d1b31ca" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:10.741924Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:10.741246Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:10.751330Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:10.750668Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0222e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.752961&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.732739&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.108e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.767316&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.760208&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="960d5afe" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:10.783175Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:10.782631Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:10.792758Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:10.792097Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9982e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.794357&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.774375&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.184e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.808764&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.801580&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KcNt6v_56cc?si=5YR5-7IR1paMMiXK> Search in
a BST:
<https://leetcode.com/problems/search-in-a-binary-search-tree/submissions/1232647689>

</div>

<div id="09688508" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:10.824486Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:10.823940Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:10.834154Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:10.833413Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9879e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.835793&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.815914&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.47e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.850813&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.843343&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KSsk8AhdOZA?si=2T66YUCRiC1Vr7Fs> Ceil in a
BST

</div>

<div id="519b483a" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:10.867096Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:10.866337Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:10.873022Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:10.872284Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6537e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.874654&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.858117&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:10.891048Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:10.890312Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:10.896487Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:10.895748Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6119e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.898248&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.882129&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.848e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.915916&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.908068&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Floor in a BST Video Link:
<https://youtu.be/xm_W1ub-K-w?si=ay4JzgX4mwb1RkBM>

</div>

<div id="1674c736" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:10.932387Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:10.931725Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:10.938070Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:10.937235Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6481e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.939805&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.923324&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.382e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.955556&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.948174&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Insert node into BST Video Link:
<https://youtu.be/FiFiNvM29ps?si=gLkHgOWwfsCsZYiC>

</div>

<div id="2980e200" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:10.973387Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:10.972701Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:10.978583Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:10.977937Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.592e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.980231&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.964311&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.337e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:10.996470&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:10.989133&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node:
<https://leetcode.com/problems/delete-node-in-a-bst/submissions/1233565259>
Video Link: <https://youtu.be/kouxiP_H5WE?si=-J0yCkif1y5T8lLB>

</div>

<div id="7aa66408" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.012743Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.012167Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.022331Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.021572Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.013e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.024063&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.003933&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.413e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.038993&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.031580&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Kth Smallest element in BST:
<https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/1234432057/>
Video Link: <https://youtu.be/9TJYWh0adfk?si=J5aaXBmrPA5E6LGC>

</div>

<div id="ce588656" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.055421Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.054786Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.061548Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.060790Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6911e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.063265&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.046354&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.313e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.078328&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.071015&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/f-sj7I5oXEI?si=Pz_LGZrgKIHXQxi4> Validate
a BST

</div>

<div id="e1f9a579" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.094666Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.094074Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.100774Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.100029Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6867e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.102520&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.085653&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.119097Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.118385Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.124332Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.123586Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5937e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.125923&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.109986&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.418e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.140961&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.133543&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/cX_kPV_foZc?si=YCFaerCUNhJwiPEV> LCA in
Binary Search Tree:
<https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/>

</div>

<div id="8233e212" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.157743Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.157052Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.163622Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.162849Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.687e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.165311&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.148441&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.409e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.180366&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.172957&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Construct BST from Preorder Traversal Video Link:
<https://youtu.be/UmJT3j26t1I?si=bZOGcW7usou-7xFK>

</div>

<div id="87fe0260" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.196803Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.196138Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.203206Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.202544Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.704e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.204810&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.187770&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.221161Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.220513Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.228181Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.227548Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7541e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.229806&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.212265&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.246064Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.245437Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.253927Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.253184Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8349e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.255582&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.237233&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.231e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.270333&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.263102&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder successor and predecessor of a BST Video Link:
<https://youtu.be/SXKAD2svfmI?si=MakIY0IWCvpCbHWB>

</div>

<div id="1d877037" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.287341Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.286625Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.292442Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.291680Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6211e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.294109&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.277898&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.386e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.309067&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.301681&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

BST Iterator:
<https://leetcode.com/problems/binary-search-tree-iterator/submissions/1236174700/>
Video Link: <https://youtu.be/D2jMcmxU4bs?si=D8QZ784vB5u0LLPv>

</div>

<div id="350f423a" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.325399Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.324851Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.331213Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.330466Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6243e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.332814&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.316571&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.437e-3,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.347775&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.340338&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ssL3sHwPeb4?si=Z4999grCFeuGVqKW> Two Sum
IV: BST Input

</div>

<div id="3d15c521" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.364190Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.363563Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.371067Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.370331Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7516e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.372750&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.355234&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-19T15:53:11.389604Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-19T15:53:11.388993Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-19T15:53:11.399100Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-19T15:53:11.398470Z&quot;}"
papermill="{&quot;duration&quot;:2.0258e-2,&quot;end_time&quot;:&quot;2024-04-19T15:53:11.400803&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-19T15:53:11.380545&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
