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
    duration: 1.782059
    end_time: "2024-04-18T02:45:55.860159"
    environment_variables: {}
    input_path: study/striver-A2Z/11-binary-search-trees.ipynb
    output_path: study/striver-A2Z/11-binary-search-trees.ipynb
    parameters: {}
    start_time: "2024-04-18T02:45:54.078100"
    version: 2.5.0
---

<div id="5d747994" class="cell markdown"
papermill="{&quot;duration&quot;:6.906e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.154928&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.148022&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.903e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.166896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.160993&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="4d1b31ca" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.180487Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.179832Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.189695Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.189067Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.852e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.191346&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.172826&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.959e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.203340&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.197381&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="960d5afe" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.217152Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.216392Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.227290Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.226505Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0001e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.229202&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.209201&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.84e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.241189&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.235349&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KcNt6v_56cc?si=5YR5-7IR1paMMiXK> Search in
a BST:
<https://leetcode.com/problems/search-in-a-binary-search-tree/submissions/1232647689>

</div>

<div id="09688508" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.254727Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.254207Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.265091Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.264226Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9733e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.266876&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.247143&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.197e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.279487&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.273290&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KSsk8AhdOZA?si=2T66YUCRiC1Vr7Fs> Ceil in a
BST

</div>

<div id="519b483a" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.293220Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.292714Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.299536Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.298869Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5587e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.301101&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.285514&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.314900Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.314253Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.320768Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.320017Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5149e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.322397&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.307248&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.935e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.334366&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.328431&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Floor in a BST Video Link:
<https://youtu.be/xm_W1ub-K-w?si=ay4JzgX4mwb1RkBM>

</div>

<div id="1674c736" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.347995Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.347355Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.353453Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.352798Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4842e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.355157&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.340315&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.182e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.369221&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.363039&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Insert node into BST Video Link:
<https://youtu.be/FiFiNvM29ps?si=gLkHgOWwfsCsZYiC>

</div>

<div id="2980e200" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.383277Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.382567Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.388586Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.387834Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5082e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.390504&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.375422&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.041e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.404513&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.398472&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node:
<https://leetcode.com/problems/delete-node-in-a-bst/submissions/1233565259>
Video Link: <https://youtu.be/kouxiP_H5WE?si=-J0yCkif1y5T8lLB>

</div>

<div id="7aa66408" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.418230Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.417680Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.427894Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.427142Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9233e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.429876&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.410643&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.534e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.442698&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.436164&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Kth Smallest element in BST:
<https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/1234432057/>
Video Link: <https://youtu.be/9TJYWh0adfk?si=J5aaXBmrPA5E6LGC>

</div>

<div id="ce588656" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.456675Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.456068Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.463133Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.462235Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6519e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.465421&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.448902&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.982e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.477563&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.471581&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/f-sj7I5oXEI?si=Pz_LGZrgKIHXQxi4> Validate
a BST

</div>

<div id="e1f9a579" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.491798Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.491056Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.498138Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.497475Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5997e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.499852&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.483855&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.513649Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.512972Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.519052Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.518416Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4749e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.520734&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.505985&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.2e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.533180&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.526980&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/cX_kPV_foZc?si=YCFaerCUNhJwiPEV> LCA in
Binary Search Tree:
<https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/>

</div>

<div id="8233e212" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.547363Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.546757Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.553157Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.552388Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5582e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.554882&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.539300&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.325e-3,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.567446&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.561121&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Construct BST from Preorder Traversal Video Link:
<https://youtu.be/UmJT3j26t1I?si=bZOGcW7usou-7xFK>

</div>

<div id="87fe0260" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.581495Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.580975Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.588127Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.587359Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6109e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.589845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.573736&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.604202Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.603543Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.611780Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.611153Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7097e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.613435&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.596338&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T02:45:55.627685Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T02:45:55.627078Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T02:45:55.635147Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T02:45:55.634406Z&quot;}"
papermill="{&quot;duration&quot;:1.6879e-2,&quot;end_time&quot;:&quot;2024-04-18T02:45:55.636836&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T02:45:55.619957&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
