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
    duration: 2.411088
    end_time: "2024-04-09T14:59:34.280926"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-09T14:59:31.869838"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.0955e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:32.939249&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:32.928294&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

##### Types of binary trees (<https://youtu.be/_ANrF3FJm7I?si=DZzUQr9F7dexWewB>)

1.  Full Binary Tree: Each node has 0 or 2 children.
2.  Complete Binary Tree: All levels are completely filled except the
    last, which is filled as left as possible.
3.  Perfect Binary Tree: All leaf nodes are of the same level (all nodes
    have 2 children except the leaf).
4.  Balanced Binary Tree: Height of the left and right subtree of any
    node differ by not more than 1 / Max height of tree is log (no of
    nodes).
5.  Degenerate Binary Tree: Every node has a singe children except the
    leaf node (left skewed or right skewed).

##### Binary Tree Traversals (<https://youtu.be/jmy0LaGET1I?si=1o8rYIcijmpRxZHq>)

###### Depth First Search Traversal Techniques

Hint 1: Pre - Root first, Post: Root last, In: Root middle <BR> Hint 2:
Left, Right order is preserved for all traversals

1.  In-Order Traversal: Left, Root, Right
2.  Pre-Order Traversal: Root, Left, Right
3.  Post-Order Traversal: Left, Right, Root

###### Breadth First Search

1.  Level Order Traversal: All nodes of same level are iterated through
    before moving to the next level.
2.  Boundary Traversal: Left boundary (left nodes excluding leaf), Leaf
    nodes, Right boundary nodes (right nodes excluding leaf).
3.  Diagnoal Traversal: Nodes of same diagnol are traversed one after
    another.

##### Some properties of Binary Trees

- Max nodes at any level: 2 \*\* (N - 1)

</div>

<div id="3d2598bc" class="cell markdown"
papermill="{&quot;duration&quot;:9.938e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:32.959388&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:32.949450&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:32.981069Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:32.980436Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:32.990305Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:32.989591Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2696e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:32.992048&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:32.969352&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
import bisect
import heapq
```

</div>

<div id="c70ac08c" class="cell markdown"
papermill="{&quot;duration&quot;:9.654e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.011684&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.002030&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.033533Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.032904Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.043104Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.042460Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2765e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.044822&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.022057&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="b18d099c" class="cell markdown"
papermill="{&quot;duration&quot;:9.702e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.064478&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.054776&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.086685Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.086065Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.092831Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.092082Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9449e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.094659&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.075210&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return str(self.val)

    @staticmethod
    def to_singly_linked_list(nums: list[int]):
        root = prev = None
        for n in nums:
            curr = ListNode(n)
            # Init once
            if not root:
                root = curr
            if prev:
                prev.next = curr
            prev = curr

        return root

    def to_list(self) -> list[int]:
        result = []
        curr = self
        while curr:
            result.append(curr.val)
            curr = curr.next
        return result
```

</div>

<div id="d43fd3d0" class="cell markdown"
papermill="{&quot;duration&quot;:9.618e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.114060&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.104442&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.135413Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.134830Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.144273Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.143648Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2258e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.145968&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.123710&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def getTreeTraversal(root: BinaryTreeNode) -> tuple[list[int], list[int], list[int]]:
    inorder_: list[int] = []
    def inorder(root: BinaryTreeNode) -> None:
        if not root:
            return
        else:
            inorder(root.left)
            inorder_.append(root.val)
            inorder(root.right)

    preorder_: list[int] = []
    def preorder(root: BinaryTreeNode) -> None:
        if not root:
            return
        else:
            preorder_.append(root.val)
            preorder(root.left)
            preorder(root.right)

    postorder_: list[int] = []
    def postorder(root: BinaryTreeNode) -> None:
        if not root:
            return
        else:
            postorder(root.left)
            postorder(root.right)
            postorder_.append(root.val)

    # Traverse & save the order op to a list, print it
    inorder(root)
    preorder(root)
    postorder(root)
    return (preorder_, inorder_, postorder_)
    return (inorder_, preorder_, postorder_)

# Testing the solution
assert getTreeTraversal(BinaryTreeNode.from_array([1, 3, 4, 5, 2, 7, 6])) == ([1, 3, 5, 2, 4, 7, 6], [5, 3, 2, 1, 7, 4, 6], [5, 2, 3, 7, 6, 4, 1])
```

</div>

<div id="565ebd42" class="cell markdown"
papermill="{&quot;duration&quot;:9.674e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.165737&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.156063&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.186967Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.186424Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.193642Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.192894Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9854e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.195286&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.175432&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def levelOrder(root: BinaryTreeNode) -> list[list[int]]:
    next_: list[BinaryTreeNode] = [root]
    traversed: list[list[int]] = []
    while next_:
        traversed.append([])
        temp: list[BinaryTreeNode] = []
        for curr in next_:
            if curr:
                temp.append(curr.left)
                temp.append(curr.right)
                traversed[-1].append(curr.val)
        if not traversed[-1]:
            traversed.pop()
        next_ = temp

    return traversed

# Testing the solution
assert levelOrder(BinaryTreeNode.from_array([3,9,20,None,None,15,7])) == [[3], [9, 20], [15, 7]]
assert levelOrder(BinaryTreeNode.from_array([1])) == [[1]]
```

</div>

<div id="d59819aa" class="cell markdown"
papermill="{&quot;duration&quot;:9.741e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.214891&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.205150&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=Bfqd8BsPVuw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=81>
Iterative Preorder traversal

# %%

def preorderIter(root: BinaryTreeNode) -\> list\[int\]: """ Root, Left,
Right. The idea is the push right first and then the left, since stack
only works when we are popping -1 at each step.

    Time: O(N), Space: O(Height of Binary Tree)
    """
    result: list[int] = []
    stack: list[BinaryTreeNode] = [root]
    while stack:
        curr = stack.pop()
        if curr:
            result.append(curr.val)
            stack.append(curr.right)
            stack.append(curr.left)

    return result

Testing the solution assert preorderIter(BinaryTreeNode.from_array(\[1,
None, 2, 3\])) == \[1, 2, 3\] assert
preorderIter(BinaryTreeNode.from_array(\[1, 2, 7, 3, 4, None, None,
None, None, 5, 6\])) == \[1, 2, 3, 4, 5, 6, 7\]

</div>

<div id="3a949dc1" class="cell markdown"
papermill="{&quot;duration&quot;:9.641e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.234283&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.224642&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.255508Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.254855Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.261337Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.260690Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.914e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.263075&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.243935&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def inorderIter(root: BinaryTreeNode) -> list[int]:
    """
    Left, Root, Right.

    If curr is not null, move to its left and append curr to the stack.
    Else pop the last item from stack, print it and move to right of the popped element.
    """
    result: list[int] = []
    stack: list[BinaryTreeNode] = []
    curr = root
    while True:
        if curr:
            stack.append(curr)
            curr = curr.left
        else:
            if stack:
                curr = stack.pop()
                result.append(curr.val)
                curr = curr.right
            else:
                break

    return result

# Testing the solution
assert inorderIter(BinaryTreeNode.from_array([1, None, 2, 3])) == [1, 3 ,2]
```

</div>

<div id="bc03474b" class="cell markdown"
papermill="{&quot;duration&quot;:9.798e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.282812&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.273014&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.303999Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.303543Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.309944Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.309140Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9288e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.311855&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.292567&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def postorderIter(root: BinaryTreeNode) -> list[int]:
    """
    Left, Right, Root.

    Go root, right, left similar to how we do preorder and reverse the result.
    """
    stack1: list[BinaryTreeNode] = [root]
    stack2: list[int] = []
    while stack1:
        curr = stack1.pop()
        if curr:
            stack2.append(curr.val)
            stack1.append(curr.left)
            stack1.append(curr.right)

    stack2.reverse()
    return stack2

# Testing the solution
assert postorderIter(BinaryTreeNode.from_array([1, 2, 3, 4, 5, 6, None, None, None, None, None, None, 7])) == [4, 5, 2, 7, 6, 3, 1]
```

</div>

<div id="c2506b05" class="cell markdown"
papermill="{&quot;duration&quot;:9.821e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.331532&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.321711&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.352742Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.352204Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.364582Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.363780Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5215e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.366553&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.341338&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def postorderIter_single_stack(root: BinaryTreeNode) -> list[int]:
    "Time: O(2N), Space: O(N)"
    result: list[int] = []
    stack: list[BinaryTreeNode] = []
    curr = root
    while curr or stack:
        if curr:
            stack.append(curr)
            curr = curr.left
        else:
            temp = stack[-1].right
            if not temp:
                temp = stack.pop()
                result.append(temp.val)
                while stack and temp == stack[-1].right:
                    temp = stack.pop()
                    result.append(temp.val)
            else:
                curr = temp

    return result

# Testing the solution
postorderIter_single_stack(BinaryTreeNode.from_array([1, 2, 7, 3, None, 8, None, None, 4, None, None, None, 5, None, 6]))
```

<div class="output execute_result" execution_count="8">

    [6, 5, 4, 3, 2, 8, 7, 1]

</div>

</div>

<div id="cd401b3e" class="cell markdown"
papermill="{&quot;duration&quot;:1.0094e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.386853&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.376759&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.408263Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.407665Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.415564Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.414795Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0563e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.417337&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.396774&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def getTreeTraversal_single_traversal(root: BinaryTreeNode) -> tuple[list[int], list[int], list[int]]:
    "Time: O(3N), Space: O(1)"

    preorder: list[int] = []
    inorder: list[int] = []
    postorder: list[int] = []

    stack: list[tuple[BinaryTreeNode, int]] = [(root, 1)]
    while stack:
        curr, op = stack.pop()
        if curr and op == 1:
            preorder.append(curr.val)
            stack.append((curr, op + 1))
            stack.append((curr.left, 1))
        elif curr and op == 2:
            inorder.append(curr.val)
            stack.append((curr, op + 1))
            stack.append((curr.right, 1))
        else:
            if curr:
                postorder.append(curr.val)

    return preorder, inorder, postorder

# Testing the solution
temp = BinaryTreeNode.from_array([1, 3, 4, 5, 2, 7, 6])
assert getTreeTraversal(temp) == getTreeTraversal_single_traversal(temp)
```

</div>

<div id="5689f6ec" class="cell markdown"
papermill="{&quot;duration&quot;:9.876e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.437226&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.427350&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.458582Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.458093Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.464009Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.463247Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8778e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.465866&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.447088&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Level Order Traversal
def maxDepthIter(root: BinaryTreeNode) -> int:
    "Time: O(N), Space: O(N)"

    to_traverse: list[BinaryTreeNode] = [root]
    height = 0
    while to_traverse:
        height += 1
        next_: list[BinaryTreeNode] = []
        for node in to_traverse:
            if node:
                next_.append(node.left)
                next_.append(node.right)
        to_traverse = next_

    return height - 1

# Testing the solution
assert maxDepthIter(BinaryTreeNode.from_array([3,9,20,None,None,15,7])) == 3
```

</div>

<div id="ad1799a0" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.487992Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.487329Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.493231Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.492487Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8676e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.494848&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.476172&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def maxDepthRecursive(root: BinaryTreeNode) -> int:

    max_: int = 0
    def backtrack(curr: BinaryTreeNode, height: int = 0):
        nonlocal max_
        if not curr:
            max_ = max(max_, height)
            return
        else:
            backtrack(curr.left, height + 1)
            backtrack(curr.right, height + 1)

    backtrack(root)
    return max_

# Testing the solution
assert maxDepthRecursive(BinaryTreeNode.from_array([3,9,20,None,None,15,7])) == 3
```

</div>

<div id="593ac16d" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.516451Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.515903Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.520859Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.520120Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7663e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.522679&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.505016&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def maxDepthStriver(root: BinaryTreeNode) -> int:
    if not root:
        return 0
    else:
        left = maxDepthStriver(root.left)
        right = maxDepthStriver(root.right)
        return 1 + max(left, right)

# Testing the solution
assert maxDepthStriver(BinaryTreeNode.from_array([3,9,20,None,None,15,7])) == 3
```

</div>

<div id="83812466" class="cell markdown"
papermill="{&quot;duration&quot;:9.843e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.542425&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.532582&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.563516Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.563070Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.569423Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.568674Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8943e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.571121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.552178&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isBalanced(root: BinaryTreeNode) -> bool:
    def checkHeight(curr: BinaryTreeNode) -> int:
        if not curr:
            return 0
        else:
            left = checkHeight(curr.left)
            if left == -1:
                return -1
            right = checkHeight(curr.right)
            if right == -1:
                return -1
            if abs(left - right) > 1:
                return -1
            else:
                return 1 + max(left, right)

    return checkHeight(root) != -1

# Testing the solution
assert isBalanced(BinaryTreeNode.from_array([1,2,2,3,3,None,None,4,4])) == False
```

</div>

<div id="77ff8f23" class="cell markdown"
papermill="{&quot;duration&quot;:9.918e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.591015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.581097&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.612301Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.611696Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.619852Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.619201Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0684e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.621503&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.600819&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def diameterOfBinaryTree(root: BinaryTreeNode) -> int:

    diameter: int = 0
    def checkHeight(curr: BinaryTreeNode) -> int:
        nonlocal diameter
        if not curr:
            return 0
        else:
            left = checkHeight(curr.left)
            right = checkHeight(curr.right)
            diameter = max(diameter, left + right)
            return 1 + max(left, right)

    checkHeight(root)
    return diameter

# Testing the solution
diameterOfBinaryTree(BinaryTreeNode.from_array([1,2,3,4,5]))
```

<div class="output execute_result" execution_count="14">

    3

</div>

</div>

<div id="089181e0" class="cell markdown"
papermill="{&quot;duration&quot;:1.0105e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.641954&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.631849&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.663418Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.662902Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.670343Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.669505Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0046e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.671960&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.651914&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def maxPathSum(root: BinaryTreeNode) -> float:
    max_sum: float = -math.inf
    def backtrack(curr: BinaryTreeNode) -> float:
        nonlocal max_sum
        if not curr:
            return 0
        else:
            left = max(0, backtrack(curr.left))
            right = max(0, backtrack(curr.right))
            max_sum = max(max_sum, left + right + curr.val)
            return curr.val + max(left, right)

    backtrack(root)
    return max_sum

# Testing the solution
assert maxPathSum(BinaryTreeNode.from_array([-10,9,20,None,None,15,7])) == 42
assert maxPathSum(BinaryTreeNode.from_array([1, -2, 3])) == 4
assert maxPathSum(BinaryTreeNode.from_array([9,6,-3,None,None,-6,2,None,None,2,None,-6,-6,-6])) == 16
```

</div>

<div id="0bdad953" class="cell markdown"
papermill="{&quot;duration&quot;:1.0138e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.692487&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.682349&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.714488Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.713866Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.720551Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.719835Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9692e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.722282&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.702590&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isSameTree(p: BinaryTreeNode, q: BinaryTreeNode) -> bool:
    def backtrack(curr1: BinaryTreeNode, curr2: BinaryTreeNode) -> bool:
        if not curr1 or not curr2:
            return curr1 == curr2
        else:
            return curr1.val == curr2.val and backtrack(curr1.left, curr2.left) and backtrack(curr1.right, curr2.right)

    return backtrack(p, q)

# Testing the solution
assert isSameTree(BinaryTreeNode.from_array([1, 2, 3]), BinaryTreeNode.from_array([1, 2, 3])) == True
assert isSameTree(BinaryTreeNode.from_array([1, 2]), BinaryTreeNode.from_array([1, None, 2])) == False
```

</div>

<div id="6f64cc1b" class="cell markdown"
papermill="{&quot;duration&quot;:1.0097e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.742719&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.732622&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.764099Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.763818Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.772434Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.771650Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1461e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.774154&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.752693&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Leetcode Medium: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/submissions/1225227141
def zigzagLevelOrder(root: BinaryTreeNode) -> list[list[int]]:
    """
    Perform a level order traversal, store the results into a deque.
    Based on level#, traverse from left node to right or vice versa.
    """
    to_visit: list[BinaryTreeNode] = [root]
    result: list[list[int]] = []
    level = 1
    while to_visit:
        next_: list[BinaryTreeNode] = []
        result.append([])
        for curr in to_visit:
            if curr:
                result[-1].append(curr.val)
                next_.append(curr.left)
                next_.append(curr.right)

        if not result[-1]:
            result.pop()
        elif level % 2 == 0:
            result[-1].reverse()

        to_visit = next_
        level += 1

    return result

# Testing the solution
assert zigzagLevelOrder(BinaryTreeNode.from_array([3,9,20,None,None,15,7])) == [[3],[20,9],[15,7]]
assert zigzagLevelOrder(BinaryTreeNode.from_array([1,2,3,4,None,None,5])) == [[1],[3,2],[4,5]]
```

</div>

<div id="83e73a04" class="cell markdown"
papermill="{&quot;duration&quot;:1.0087e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.794394&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.784307&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.816436Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.815895Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.825997Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.825232Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.323e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.827726&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.804496&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def traverseBoundary(root: BinaryTreeNode) -> list[int]:
    """
    Left boundary excluding leaves, Leaf nodes, Right Boundary excluding leaves
    """

    left: list[int] = []
    curr = root.left
    while curr and (curr.left or curr.right):
        left.append(curr.val)
        curr = curr.left if curr.left else curr.right

    boundary: list[int] = []
    def getLeaves(curr: BinaryTreeNode):
        nonlocal boundary
        if not curr:
            return
        else:
            if not curr.left and not curr.right:
                boundary.append(curr.val)
            getLeaves(curr.left)
            getLeaves(curr.right)

    right: list[int] = []
    curr = root.right
    while curr and (curr.left or curr.right):
        right.append(curr.val)
        curr = curr.right if curr.right else curr.left
    right.reverse()

    getLeaves(root)
    return [root.val] + left + boundary + right

# Testing the solution
assert traverseBoundary(BinaryTreeNode.from_array([10, 5, 20, 3, 8, 18, 25, None, None, 7, None, None, None, None, None, None, None])) == [10, 5, 3, 7, 18, 25, 20]
assert traverseBoundary(BinaryTreeNode.from_array([100, 50, 150, 25, 75, 140, 200, None, 30, 70, 80, None, None, None, None, None, 35, None, None, None, None, None, None])) == [100, 50, 25, 30, 35, 70, 80, 140, 200, 150]
```

</div>

<div id="48a971f2" class="cell markdown"
papermill="{&quot;duration&quot;:1.0068e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.849896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.839828&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.871147Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.870895Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.880867Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.880126Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2723e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.882606&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.859883&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Problem Link: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/submissions/1226266467
def verticalTraversal(root: BinaryTreeNode) -> list[list[int]]:
    """
    Time: O(N log N), Space: O(N)
    """

    # Time: O(N)
    ordering: list[tuple[int, int, int]] = []
    def backtrack(curr: BinaryTreeNode, i: int, j: int):
        nonlocal ordering
        if not curr:
            return
        else:
            ordering.append((curr.val, i, j))
            backtrack(curr.left, i + 1, j - 1)
            backtrack(curr.right, i + 1, j + 1)

    # Time: O(N log N)
    backtrack(root, 0, 0)
    ordering.sort(key=lambda x: (x[2], x[1], x[0]))

    # Time: O(N)
    result: list[list[int]] = []
    prev = ordering[0][2] - 1
    for k, i, j in ordering:
        if j != prev:
            result.append([])
            prev = j
        result[-1].append(k)

    return result

# Testing the solution
assert verticalTraversal(BinaryTreeNode.from_array([3,9,20,None,None,15,7])) == [[9], [3, 15], [20], [7]]
assert verticalTraversal(BinaryTreeNode.from_array([1, 2, 3, 4, 5, 6, 7])) == [[4], [2], [1,5,6], [3], [7]]
assert verticalTraversal(BinaryTreeNode.from_array([1, 2, 3, 4, 6, 5, 7])) == [[4], [2], [1, 5, 6], [3], [7]]
```

</div>

<div id="5a99a217" class="cell markdown"
papermill="{&quot;duration&quot;:1.0008e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.902682&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.892674&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.924384Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.923871Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.932753Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.932093Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1786e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.934453&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.912667&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def topViewBinaryTree(root: BinaryTreeNode) -> list[int]:
    topView: dict[int, int] = dict()

    # Level Order Traversal
    stack: list[tuple[BinaryTreeNode, int]] = [(root, 0)]
    while stack:
        next_: list[tuple[BinaryTreeNode, int]] = []
        for curr, j in stack:
            if curr:
                if j not in topView:
                    topView[j] = curr.val
                next_.append((curr.left, j - 1))
                next_.append((curr.right, j + 1))

        stack = next_

    result: list[int] = []
    for k, v in sorted(topView.items(), key=lambda x: x[0]):
        result.append(v)

    return result

# Testing the result
assert topViewBinaryTree(BinaryTreeNode.from_array([1, 2, 3, 4, 5, None, 6, None, 7, None, None, 8, None, 9, None, None, 11, 10, None, None, None, None, None])) == [10, 4,  2, 1, 3, 6]
```

</div>

<div id="b62cb1a9" class="cell markdown"
papermill="{&quot;duration&quot;:1.0347e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.955073&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.944726&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:33.977014Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:33.976423Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:33.983948Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:33.983231Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0479e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:33.985661&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.965182&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def bottomView(root: BinaryTreeNode) -> list[int]:
    ordering: dict[int, int] = dict()
    stack: list[tuple[BinaryTreeNode, int]] = [(root, 0)]
    while stack:
        next_: list[tuple[BinaryTreeNode, int]] = []
        for curr, j in stack:
            if curr:
                ordering[j] = curr.val
                next_.append((curr.left, j - 1))
                next_.append((curr.right, j + 1))

        stack = next_

    result: list[int] = []
    for k in sorted(ordering.keys()):
        result.append(ordering[k])

    return result

# Testing the solution
assert bottomView(BinaryTreeNode.from_array([1, 2, 3, None, None, 5, 6, 7, 8, None, None, None, None, None, None])) == [7, 5, 8, 6]
```

</div>

<div id="262c0c19" class="cell markdown"
papermill="{&quot;duration&quot;:9.974e-3,&quot;end_time&quot;:&quot;2024-04-09T14:59:34.005783&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:33.995809&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:34.027976Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:34.027196Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:34.034597Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:34.033811Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0357e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:34.036284&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:34.015927&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Right Side View: Time - O(N)
def rightSideView(root: BinaryTreeNode) -> list[int]:
    ordering: dict[int, int] = dict()
    def inOrder(curr: BinaryTreeNode, i: int = 0):
        nonlocal ordering
        if not curr:
            return
        else:
            ordering[i] = curr.val
            inOrder(curr.left, i + 1)
            inOrder(curr.right, i + 1)

    # Backtrack and store the results
    inOrder(root)
    result: list[int] = []
    for k in sorted(ordering.keys()):
        result.append(ordering[k])

    return result

# Testing the solution
assert rightSideView(BinaryTreeNode.from_array([1, 2, 3, None, 5, None, 4])) == [1, 3, 4]
assert rightSideView(BinaryTreeNode.from_array([1, 2, 3, 4])) == [1, 3, 4]
```

</div>

<div id="367ea6a3" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:34.059165Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:34.058496Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:34.067193Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:34.066447Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.206e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:34.068867&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:34.046807&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]" title="Left Side View: Time - O(N)">

``` python
def leftSideView(root: BinaryTreeNode) -> list[int]:
    ordering: dict[int, int] = dict()
    def backtrack(curr: BinaryTreeNode, i: int = 0):
        nonlocal ordering
        if not curr:
            return
        else:
            ordering[i] = curr.val
            backtrack(curr.right, i + 1)
            backtrack(curr.left, i + 1)

    # Backtrack and store the results
    backtrack(root)
    result: list[int] = []
    for k in sorted(ordering.keys()):
        result.append(ordering[k])

    return result

# Testing the solution
assert leftSideView(BinaryTreeNode.from_array([1, 2, 3, None, 5, None, 4])) == [1, 2, 5]
assert leftSideView(BinaryTreeNode.from_array([1, 2, 3, 4])) == [1, 2, 4]
```

</div>

<div id="40a6b0a2" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:34.091423Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:34.090778Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:34.097846Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:34.097075Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0177e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:34.099483&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:34.079306&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better solution from Striver
def rightSideViewStriver(root: BinaryTreeNode) -> list[int]:
    result: list[int] = []
    def backtrack(curr: BinaryTreeNode, level: int = 1):
        """
        Modified preorder traversal - RRL.
        We insert to our result only when we are coming the level for the first time.
        """
        nonlocal result
        if not curr:
            return
        else:
            if level > len(result):
                result.append(curr.val)
            backtrack(curr.right, level + 1)
            backtrack(curr.left, level + 1)

    # Recurse and save the results
    backtrack(root)
    return result

# Testing the solution
assert rightSideViewStriver(BinaryTreeNode.from_array([1, 2, 3, None, 5, None, 4])) == [1, 3, 4]
assert rightSideViewStriver(BinaryTreeNode.from_array([1, 2, 3, 4])) == [1, 3, 4]
```

</div>

<div id="3d234569" class="cell markdown"
papermill="{&quot;duration&quot;:1.0246e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:34.120222&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:34.109976&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-09T14:59:34.142527Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-09T14:59:34.141819Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-09T14:59:34.151485Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-09T14:59:34.150719Z&quot;}"
papermill="{&quot;duration&quot;:2.2859e-2,&quot;end_time&quot;:&quot;2024-04-09T14:59:34.153313&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-09T14:59:34.130454&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isSymmetric(root: BinaryTreeNode) -> bool:
    def backtrack(left: BinaryTreeNode, right: BinaryTreeNode) -> bool:
        if not left or not right:
            return left == right
        else:
            return left.val == right.val and backtrack(left.left, right.right) and backtrack(left.right, right.left)

    def isPalindrome(arr: list[BinaryTreeNode]) -> bool:
        N = len(arr)
        i, j = 0, N - 1
        while i < j:
            left, right = arr[i].val if arr[i] else None, arr[j].val if arr[j] else None
            i, j = i + 1, j - 1
            if left != right:
                return False
        return True

    def iterate() -> bool:
        stack: list[BinaryTreeNode] = [root]
        while stack:
            next_: list[BinaryTreeNode] = []
            for curr in stack:
                if curr:
                    next_.append(curr.left)
                    next_.append(curr.right)

            if not isPalindrome(next_):
                return False
            else:
                stack = next_
        else:
            return True

    # return backtrack(root.left, root.right)
    return iterate()

# Testing the solution
assert isSymmetric(BinaryTreeNode.from_array([1, 2, 2, None, 3, None, 3])) == False
assert isSymmetric(BinaryTreeNode.from_array([1, 2, 2, None, 3, 3, None])) == True
```

</div>
