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
    duration: 4.474944
    end_time: "2024-04-15T16:15:45.153879"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-15T16:15:40.678935"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.7706e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:41.746825&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.729119&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

- Max nodes at any level: 2 \*\* (N - 1) Requirements to construct an
  unique binary tree: We must have the inorder traversal to know what
  comes to the left and to the right of root.

</div>

<div id="3d2598bc" class="cell markdown"
papermill="{&quot;duration&quot;:1.6513e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:41.780283&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.763770&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:41.815197Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:41.814394Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:41.824672Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:41.824043Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9624e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:41.826418&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.796794&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6795e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:41.860669&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.843874&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:41.895757Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:41.895123Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:41.904737Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:41.904072Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8957e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:41.906452&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.877495&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6467e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:41.939580&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.923113&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:41.974131Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:41.973468Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:41.980169Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:41.979509Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5797e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:41.981784&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.955987&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6574e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.015234&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:41.998660&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.049919Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.049208Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.058432Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.057774Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8334e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.060167&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.031833&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6343e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.093346&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.077003&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.127523Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.127285Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.134112Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.133355Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5999e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.135910&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.109911&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6574e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.169212&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.152638&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=Bfqd8BsPVuw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=81>
Iterative Preorder traversal

</div>

<div id="6021695b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.203764Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.203075Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.209798Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.209149Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5765e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.211526&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.185761&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def preorderIter(root: BinaryTreeNode) -> list[int]:
    """
    Root, Left, Right. The idea is the push right first and then the left,
    since stack only works when we are popping -1 at each step.

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

# Testing the solution
assert preorderIter(BinaryTreeNode.from_array([1, None, 2, 3])) == [1, 2, 3]
assert preorderIter(BinaryTreeNode.from_array([1, 2, 7, 3, 4, None, None, None, None, 5, 6])) == [1, 2, 3, 4, 5, 6, 7]
```

</div>

<div id="3a949dc1" class="cell markdown"
papermill="{&quot;duration&quot;:1.6473e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.244811&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.228338&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.279111Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.278817Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.284925Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.284270Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5331e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.286700&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.261369&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6607e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.320074&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.303467&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.354914Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.354251Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.360854Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.360090Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.591e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.362722&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.336812&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6602e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.396121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.379519&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.430356Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.430063Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.442587Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.441735Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1561e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.444223&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.412662&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="9">

    [6, 5, 4, 3, 2, 8, 7, 1]

</div>

</div>

<div id="cd401b3e" class="cell markdown"
papermill="{&quot;duration&quot;:1.6702e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.477955&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.461253&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.512101Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.511864Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.519678Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.519027Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6802e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.521382&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.494580&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6558e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.554570&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.538012&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.589806Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.589162Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.594992Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.594313Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5029e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.596607&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.571578&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="ad1799a0" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.631413Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.631122Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.636870Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.636219Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5067e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.638557&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.613490&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="593ac16d" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.673575Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.672954Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.677925Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.677260Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4222e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.679635&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.655413&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6705e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.713191&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.696486&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.748272Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.747589Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.753971Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.753315Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5654e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.755698&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.730044&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6682e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.807055&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.790373&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.842288Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.841944Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.850040Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.849319Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7883e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.851724&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.823841&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="15">

    3

</div>

</div>

<div id="089181e0" class="cell markdown"
papermill="{&quot;duration&quot;:1.693e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.885679&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.868749&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.921007Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.920300Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:42.927504Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:42.926739Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6553e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.929159&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.902606&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6857e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:42.963145&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.946288&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:42.998806Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:42.998203Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.004676Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.004012Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6087e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.006390&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:42.980303&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6953e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.040411&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.023458&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.076402Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.075755Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.084101Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.083467Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8247e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.085833&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.057586&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6951e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.119909&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.102958&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.155498Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.154801Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.165302Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.164678Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0257e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.167161&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.136904&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6961e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.201212&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.184251&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.236487Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.235807Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.246039Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.245400Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9754e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.247804&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.218050&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6853e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.281517&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.264664&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.316444Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.316205Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.324051Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.323375Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7224e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.325748&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.298524&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6728e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.359385&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.342657&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.394249Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.393990Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.401201Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.400441Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6577e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.402825&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.376248&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6858e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.436701&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.419843&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.471883Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.471236Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.478902Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.478095Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6925e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.480461&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.453536&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="367ea6a3" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.515743Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.515044Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.522823Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.522135Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7115e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.524444&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.497329&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="40a6b0a2" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.560303Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.559676Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.566830Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.566059Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6753e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.568442&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.541689&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6759e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.602212&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.585453&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.637416Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.636846Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.646287Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.645629Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8908e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.648072&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.619164&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="3d1fac60" class="cell markdown"
papermill="{&quot;duration&quot;:1.6862e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.682004&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.665142&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fmflMqVOC7k?si=1AX2ea08UGtxw0mj> Print
Root to Node path in Binary Tree

</div>

<div id="f0244aad" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.717177Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.716543Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.725000Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.724350Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7886e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.726745&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.698859&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def rootToNodePath(root: BinaryTreeNode, target: int) -> list[int]:
    "Time: O(N), Space: O(H)"
    path: list[int] = []
    def backtrack(curr: BinaryTreeNode) -> bool:
        if not curr:
            return False
        else:
            path.append(curr.val)
            result = curr.val == target or backtrack(curr.left) or backtrack(curr.right)
            if not result:
                path.pop()

            return result

    backtrack(root)
    return path


# Testing the solution
rootToNodePath(BinaryTreeNode.from_array([1, 2, 3, 4, 5, None, None, None, None, 6, 7]), 7)
```

<div class="output execute_result" execution_count="27">

    [1, 2, 5, 7]

</div>

</div>

<div id="b7a03676" class="cell markdown"
papermill="{&quot;duration&quot;:1.7167e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.761150&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.743983&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lowest common ancestor Video Link:
<https://youtu.be/_-QHfMDde90?si=3pJ5ysXG6FArt3Q3>

</div>

<div id="7a501b5a" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.796388Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.796150Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.802814Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.801924Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6125e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.804517&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.778392&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Problem Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/submissions/1228152859
def lowestCommonAncestor(root: BinaryTreeNode, p: BinaryTreeNode, q: BinaryTreeNode) -> BinaryTreeNode:
    def backtrack(curr: BinaryTreeNode) -> BinaryTreeNode:
        if not curr:
            return curr
        else:
            left = backtrack(curr.left)
            right = backtrack(curr.right)
            if left and right:
                return curr
            elif curr in (p, q):
                return curr
            else:
                return left if left else right

    return backtrack(root)

# Testing the solution
temp: BinaryTreeNode = BinaryTreeNode.from_array([3,5,1,6,2,0,8,None,None,7,4])
assert lowestCommonAncestor(temp, p=temp.left, q=temp.left.right.right).val == 5
```

</div>

<div id="8415d919" class="cell markdown"
papermill="{&quot;duration&quot;:1.7123e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.838817&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.821694&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum width of a binary Tree Video Link:
<https://youtu.be/ZbybYvcVLks?si=_r6ouO7uxfz3DI6I>

</div>

<div id="249090c8" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.874648Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.873966Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.881084Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.880331Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6766e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.882710&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.855944&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Problem Link: https://leetcode.com/problems/maximum-width-of-binary-tree/submissions/1228981858
def widthOfBinaryTree(root: BinaryTreeNode) -> int:
    """
    1. 0 Based indexing:
        - Left of any node: (2 * i + 1)
        - Right of any node: (2 * i + 2)

    2. 1 Based indexing:
        - Left of any node: (2 * i)
        - Right of any node: (2 * i + 1)
    """

    max_width: int = 0
    queue: list[tuple[BinaryTreeNode, int]] = [(root, 0)]
    while queue:
        max_width = max(max_width, queue[-1][1] - queue[0][1] + 1)
        next_: list[tuple[BinaryTreeNode, int]] = []
        min_idx = queue[0][1] # i - min_idx is done to prevent buffer overflow in languages like C, C++
        for curr, i in queue:
            if curr.left:
                next_.append((curr.left, 2 * (i - min_idx) + 1))
            if curr.right:
                next_.append((curr.right, 2 * (i - min_idx) + 2))

        queue = next_

    return max_width

# Testing the solution
assert widthOfBinaryTree(BinaryTreeNode.from_array([1,3,2,5,3,None,9])) == 4
```

</div>

<div id="db8bdc78" class="cell markdown"
papermill="{&quot;duration&quot;:1.7018e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.917060&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.900042&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fnmisPM6cVo?si=gK9Xm0WNZQ6dqBk6> Check
children sum property in Binary Tree

</div>

<div id="e9c463d9" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:43.952635Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:43.951955Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:43.958129Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:43.957385Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5612e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.959729&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.934117&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isParentSum(curr: BinaryTreeNode) -> bool:
    if not curr or (not curr.left and not curr.right): # Leaf node
        return True
    else:
        curr_parent_sum = (curr.val == ((curr.left.val if curr.left else 0) + (curr.right.val if curr.right else 0)))
        return curr_parent_sum and isParentSum(curr.left) and isParentSum(curr.right)

# Testing the solution
assert isParentSum(BinaryTreeNode.from_array([5, 3, 2, 3, None, None, None, None, None])) == True
assert isParentSum(BinaryTreeNode.from_array([7, 3, 4, 3, None, 2, 3, None, None, None, None, None, None])) == False
```

</div>

<div id="6315a3c1" class="cell markdown"
papermill="{&quot;duration&quot;:1.7484e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:43.994382&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:43.976898&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maintain children sum property of a binary Tree

</div>

<div id="20d7e7dd" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.030494Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.029784Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.038056Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.037396Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8028e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.039742&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.011714&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def restoreChildrenSumProperty(root: BinaryTreeNode) -> BinaryTreeNode:
    "In languages such as C, this might cause buffer overflow, see striver sol below"
    max_ = 0
    def postOrder(curr: BinaryTreeNode) -> int:
        nonlocal max_
        max_ = max(max_, curr.val if curr else 0)
        if not curr.left and not curr.right:
            assert curr.val < max_, f"Can only increment, {curr.val} cannot become {max_}"
            curr.val = max_
            return curr.val
        else:
            left_ = postOrder(curr.left) if curr.left else 0
            right_ = postOrder(curr.right) if curr.right else 0
            assert curr.val < left_ + right_, f"Can only increment, {curr.val} cannot become {left_ + right_}"
            curr.val = left_ + right_
            return left_ + right_

    postOrder(root)
    return root

# Testing the solution
assert isParentSum(restoreChildrenSumProperty(BinaryTreeNode.from_array([2, 35, 10, 2, 3, 5, 2])))
assert isParentSum(restoreChildrenSumProperty(BinaryTreeNode.from_array([50, 7, 2, 3, 5, 1, 30])))
assert isParentSum(restoreChildrenSumProperty(BinaryTreeNode.from_array([7, 3, 4, 3, None, 2, 3, None, None, None, None, None, None])))
```

</div>

<div id="bf9f3b28" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.075623Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.075332Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.083504Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.082830Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8133e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.085135&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.057002&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def restoreChildrenSumProperty_striver(root: BinaryTreeNode) -> BinaryTreeNode:
    def postOrder(curr: BinaryTreeNode) -> int:
        if not curr.left and not curr.right:
            return curr.val
        else:
            if curr.val > (curr.left.val if curr.left else 0) + (curr.right.val if curr.right else 0):
                if curr.left:
                    curr.left.val = curr.val
                if curr.right:
                    curr.right.val = curr.val

            left = postOrder(curr.left) if curr.left else 0
            right = postOrder(curr.right) if curr.right else 0
            curr.val = left + right
            return curr.val

    postOrder(root)
    return root

# Testing the solution
assert isParentSum(restoreChildrenSumProperty_striver(BinaryTreeNode.from_array([2, 35, 10, 2, 3, 5, 2])))
assert isParentSum(restoreChildrenSumProperty_striver(BinaryTreeNode.from_array([50, 7, 2, 3, 5, 1, 30])))
assert isParentSum(restoreChildrenSumProperty_striver(BinaryTreeNode.from_array([7, 3, 4, 3, None, 2, 3, None, None, None, None, None, None])))
```

</div>

<div id="d81de678" class="cell markdown"
papermill="{&quot;duration&quot;:1.704e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.119259&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.102219&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/i9ORlEy6EsI?si=GlIarkkKAHDMEXss> Print all
nodes at K distance from target in Binary Tree

</div>

<div id="af18ee1c" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.155146Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.154480Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.165454Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.164664Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0692e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.167112&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.136420&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def distanceK(root: BinaryTreeNode, target: int, k: int) -> list[int]:
    "Time: O(N), Space: O(N)"
    adl: dict[int, set[int]] = dict()
    def createGraph(curr: BinaryTreeNode):
        nonlocal adl
        if curr:
            curr_neighbours = adl.get(curr.val, set())
            if curr.left:
                curr_neighbours.add(curr.left.val)
                left_neighbours = adl.get(curr.left.val, set())
                left_neighbours.add(curr.val)
                adl[curr.left.val] = left_neighbours
                createGraph(curr.left)
            if curr.right:
                curr_neighbours.add(curr.right.val)
                right_neighbours = adl.get(curr.right.val, set())
                right_neighbours.add(curr.val)
                adl[curr.right.val] = right_neighbours
                createGraph(curr.right)
            adl[curr.val] = curr_neighbours

    # Create a graph adjacency list
    createGraph(root)

    # Do a BFS until distance is reached
    queue: list[int] = [target]
    visited: set[int] = set([target])
    while k > 0:
        next_: list[int] = []
        for curr in queue:
            for neighbour in adl.get(curr, set()):
                if neighbour not in visited:
                    visited.add(neighbour)
                    next_.append(neighbour)

        queue = next_
        k -= 1

    return queue

# Testing the solution
assert sorted(distanceK(BinaryTreeNode.from_array([3,5,1,6,2,0,8,None,None,7,4]), 5, 2)) == [1, 4, 7]
assert sorted(distanceK(BinaryTreeNode.from_array([3,5,1,6,2,0,8,None,None,7,4]), 4, 2)) == [5, 7]
```

</div>

<div id="db756dd0" class="cell markdown"
papermill="{&quot;duration&quot;:1.707e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.201402&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.184332&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/2r5wLmQfD6g?si=V-Tirx2isc0Mt7Qp> Time to
burn a Binary Tree

</div>

<div id="67ee9af0" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.237221Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.236548Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.246221Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.245463Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9513e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.248001&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.218488&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def timeToBurnTree(root: BinaryTreeNode, start: int):
    "Time: O(N), Space: O(N)"
    adl: dict[int, set[int]] = dict()
    def createGraph(curr: BinaryTreeNode):
        if curr:
            curr_neighbours = adl.get(curr.val, set())
            if curr.left:
                curr_neighbours.add(curr.left.val)
                adl[curr.left.val] = set([curr.val])
                createGraph(curr.left)
            if curr.right:
                curr_neighbours.add(curr.right.val)
                adl[curr.right.val] = set([curr.val])
                createGraph(curr.right)
            adl[curr.val] = curr_neighbours

    # Create an adjacency list
    createGraph(root)

    # Do a BFS traversal and compute the max levels
    k = 0
    queue: list[int] = [start]
    visited: set[int] = set([start])
    while queue:
        next_: list[int] = []
        for curr in queue:
            for neighbour in adl.get(curr, set()):
                if neighbour not in visited:
                    visited.add(neighbour)
                    next_.append(neighbour)

        queue = next_
        k += 1

    return k - 1

# Testing the solution
assert timeToBurnTree(BinaryTreeNode.from_array([3,5,1,6,2,0,8,None,None,7,4]), 5) == 3
assert timeToBurnTree(BinaryTreeNode.from_array([3,5,1,6,2,0,8,None,None,7,4]), 4) == 5
```

</div>

<div id="d4e4fad8" class="cell markdown"
papermill="{&quot;duration&quot;:1.7013e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.282268&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.265255&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/u-yWemKGWO0?si=-xcOq69rKzHwnkSC> Count
total nodes in a complete Binary Tree

</div>

<div id="dd5cd4ce" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.317602Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.317082Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.323700Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.323024Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6125e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.325405&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.299280&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Problem Link: https://leetcode.com/problems/count-complete-tree-nodes/submissions/1229957492
def countNodes(root: BinaryTreeNode) -> int:
    """
    For each node, compute the left height and right height
    If left height == right height:
        Count nodes with formula = 2 ^ (h - 1)
    Else:
        Count of nodes = 1 + left_count + right_count

    Computing height takes O(log N) time. At each step, either left would be a
    full binary tree or the right would be: O(log N) nodes to travel

    Time: O(log N * log N), Space: O(log N)
    """

    if not root:
        return 0

    # Compute left height
    curr, lh = root, 0
    while curr:
        curr = curr.left
        lh += 1

    # Compute right height
    curr, rh = root, 0
    rh = 0
    while curr:
        curr = curr.right
        rh += 1

    if lh == rh:
        return 2 ** lh - 1
    else:
        return 1 + countNodes(root.left) + countNodes(root.right)

# Testing the solution
assert countNodes(BinaryTreeNode.from_array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11])) == 11
```

</div>

<div id="51889e6d" class="cell markdown"
papermill="{&quot;duration&quot;:1.6973e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.359538&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.342565&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Construct binary tree from preorder and inorder traversal Video Link:
<https://youtu.be/aZNaLrVebKQ?si=bSe8CP3Bxk0bM3nG>

</div>

<div id="62f3bcad" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.395243Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.394698Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.403399Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.402622Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8398e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.405127&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.376729&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better solution
# Problem Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/1230758214
def buildTreeFromPreorderBetter(preorder: list[int], inorder: list[int]) -> BinaryTreeNode|None:
    """
    Preorder can be used to figure out the root.
    Inorder can be used to figure out which of the nodes come to left and to the right of root.
    """
    root = BinaryTreeNode(preorder[0]) if preorder else None
    if root and len(inorder) > 1:
        idx = inorder.index(root.val)
        root.left = buildTreeFromPreorderBetter(preorder[1: idx + 1], inorder[:idx])
        root.right = buildTreeFromPreorderBetter(preorder[idx + 1:], inorder[idx + 1:])

    return root

# Testing the Solution
buildTreeFromPreorderBetter(inorder=[40, 20, 50, 10, 60, 30], preorder=[10, 20, 40, 50, 30, 60]).to_list()
```

<div class="output execute_result" execution_count="36">

    [10, 20, 30, 40, 50, 60, None, None, None, None, None, None, None]

</div>

</div>

<div id="878e7fa6" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.440953Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.440657Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.451242Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.450492Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.039e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.452902&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.422512&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/1230767142/
def buildTreeFromPreorderOptimal(preorder: list[int], inorder: list[int]) -> BinaryTreeNode|None:
    """
    Use hashmap to save the idx positions of inorder.
    Time: O(N), Space: O(N)
    """
    N = len(preorder)
    inorder_hm = dict()
    for i, n in enumerate(inorder):
        inorder_hm[n] = i

    def helper(inorder_start: int, inorder_end: int, preorder_start: int, preorder_end: int) -> BinaryTreeNode|None:
        N_ = preorder_end - preorder_start
        root = BinaryTreeNode(preorder[preorder_start]) if N_ >= 0 else None
        if root and N_ > 0:
            idx = inorder_hm[root.val]
            root.left = helper(inorder_start, idx - 1, preorder_start + 1, preorder_start + idx - inorder_start)
            root.right = helper(idx + 1, inorder_end, preorder_start + 1 + idx - inorder_start, preorder_end)

        return root

    return helper(0, N - 1, 0, N - 1)

# Testing the Solution
buildTreeFromPreorderOptimal(inorder=[40, 20, 50, 10, 60, 30], preorder=[10, 20, 40, 50, 30, 60]).to_list()
```

<div class="output execute_result" execution_count="37">

    [10, 20, 30, 40, 50, 60, None, None, None, None, None, None, None]

</div>

</div>

<div id="c0d37bdc" class="cell markdown"
papermill="{&quot;duration&quot;:1.7253e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.487439&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.470186&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/LgLRTaEMRVc?si=AuIS8bfI3SLknUaS> Binary
Tree from Postorder and Inorder traversal

</div>

<div id="53e42711" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.523657Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.522996Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.532072Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.531300Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.888e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.533758&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.504878&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Better: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/submissions/1230771756/
def buildTreeFromPostorderBetter(inorder: list[int], postorder: list[int]) -> BinaryTreeNode|None:
    """
    Same logic as previous question, we could technically call buildTreeFromPreorder(inorder, postorder[::-1]).
    Instead of assigning first value as root, here we assign last value as root and backtrack.
    """
    root = BinaryTreeNode(postorder[-1]) if postorder else None
    if root and len(postorder) > 1:
        idx = inorder.index(root.val)
        root.left = buildTreeFromPostorderBetter(inorder[:idx], postorder[:idx])
        root.right = buildTreeFromPostorderBetter(inorder[idx + 1:], postorder[idx: -1])

    return root

# Testing the Solution
buildTreeFromPostorderBetter(inorder=[3, 2, 4, 1, 5], postorder=[3, 4, 2, 5, 1]).to_list()
```

<div class="output execute_result" execution_count="38">

    [1, 2, 5, 3, 4, None, None, None, None, None, None]

</div>

</div>

<div id="2f83f35a" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.570654Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.570041Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.580245Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.579476Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0521e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.581956&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.551435&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Optimal: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/submissions/1230778263/
def buildTreeFromPostorderOptimal(inorder: list[int], postorder: list[int]) -> BinaryTreeNode|None:
    """
    Same logic as above, use a hashmap to precompute the indices for inorder.
    """
    N = len(inorder)
    hm: dict[int, int] = dict()
    for i, n in enumerate(inorder):
        hm[n] = i

    def helper(iStart: int, iEnd: int, pStart, pEnd: int) -> BinaryTreeNode|None:
        root = BinaryTreeNode(postorder[pEnd]) if pStart <= pEnd else None
        if root and pStart < pEnd:
            idx = hm[root.val]
            root.left = helper(iStart, idx - 1, pStart, pStart + idx - iStart - 1)
            root.right = helper(idx + 1, iEnd, pStart + idx - iStart, pEnd - 1)
        return root

    return helper(0, N - 1, 0, N - 1)

# Testing the solution
buildTreeFromPostorderOptimal(inorder=[3, 2, 4, 1, 5], postorder=[3, 4, 2, 5, 1]).to_list()
```

<div class="output execute_result" execution_count="39">

    [1, 2, 5, 3, 4, None, None, None, None, None, None]

</div>

</div>

<div id="4a30f23a" class="cell markdown"
papermill="{&quot;duration&quot;:1.8381e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.618133&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.599752&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-YbXySKJsX8?si=GF9GnCHLV1gDfcWK> Serialize
and Deserialize Binary Trees

</div>

<div id="b286bec0" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.656250Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.655657Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.667362Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.666698Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1932e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.669015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.637083&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/1230819565
class Codec:
    def serialize(self, root: BinaryTreeNode) -> str:
        """Encodes a tree to a single string."""
        def helper(curr: BinaryTreeNode) -> str:
            if not curr:
                return "*"
            else:
                return f"{curr.val}({helper(curr.left)},{helper(curr.right)})"

        result = helper(root)
        return result

    def deserialize(self, data: str) -> BinaryTreeNode|None:
        """Decodes your encoded data to tree."""
        def createTree(prev: BinaryTreeNode|str|None) -> BinaryTreeNode|None:
            if type(prev) == str:
                return BinaryTreeNode(int(prev)) if prev.isdigit() or prev[0] == '-' else None
            else:
                return prev # type: ignore

        stack: list[str|None|BinaryTreeNode] = []
        for ch in data:
            if ch.isdigit() and stack and type(stack[-1]) == str and (stack[-1].isdigit() or stack[-1][0] == '-'):
                stack[-1] += ch
            else:
                stack.append(ch)
                if ch == ')':
                    stack.pop() # )
                    right = createTree(stack.pop())
                    stack.pop() # ,
                    left = createTree(stack.pop())
                    stack.pop() # (
                    root = createTree(stack.pop())
                    if root:
                        root.left = left
                        root.right = right
                    stack.append(root)

        return stack[0] if type(stack[0]) != str else None

# Your Codec object will be instantiated and called as such:
ser = Codec()
out = ser.deserialize(ser.serialize(BinaryTreeNode.from_array([1,2,-13,None,None,4,25])))
out_lst = out.to_list() if out is not None else []
while out_lst and out_lst[-1] is None: out_lst.pop()
assert out_lst == [1,2,-13,None,None,4,25]
```

</div>

<div id="ec2dd2db" class="cell code" execution_count="41"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.705843Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.705183Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.715574Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.714925Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.059e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.717321&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.686731&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Problem link: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/1231115438/
class CodecStriver:
    def serialize(self, root: BinaryTreeNode) -> str:
        all_nodes: list[str] = []
        queue: list[BinaryTreeNode] = [root]
        while queue:
            next_: list[BinaryTreeNode] = []
            for curr in queue:
                all_nodes.append(str(curr.val) if curr else '*')
                if curr:
                    next_.append(curr.left)
                    next_.append(curr.right)

            queue = next_

        return ','.join(all_nodes)

    def deserialize(self, data: str) -> BinaryTreeNode|None:
        all_nodes: list[BinaryTreeNode] = []
        idx: float = -1
        for curr_val in data.split(','):
            curr = BinaryTreeNode(int(curr_val)) if curr_val != '*' else None
            if curr:
                all_nodes.append(curr)
            if idx == -1:
                idx += 1
            elif int(idx) == idx:
                all_nodes[int(idx)].left = curr
                idx += 0.5
            else:
                all_nodes[int(idx)].right = curr
                idx += 0.5

        return all_nodes[0] if all_nodes else None

# Your Codec object will be instantiated and called as such:
ser_ = CodecStriver()
out = ser_.deserialize(ser_.serialize(BinaryTreeNode.from_array([1,2,-13,None,None,4,25])))
out_lst = out.to_list() if out is not None else []
while out_lst and out_lst[-1] is None: out_lst.pop()
assert out_lst == [1,2,-13,None,None,4,25]
```

</div>

<div id="611bda3a" class="cell markdown"
papermill="{&quot;duration&quot;:1.7667e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.752943&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.735276&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Morris traversal of Binary Tree Video Link:
<https://youtu.be/80Zug6D1_r4?si=Npe19WIqtFI_aa5c> Advantage is that
while it consumes O(N) time, it only takes up O(1) space

</div>

<div id="22ad4618" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.789701Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.789118Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.796030Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.795323Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7051e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.797706&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.770655&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def morris_preorder(root: BinaryTreeNode) -> list[int]:
    curr: BinaryTreeNode = root
    preorder: list[int] = []
    while curr:
        # We are at root node
        if not curr.left:
            preorder.append(curr.val)
            curr = curr.right

        # Create a thread on the right most guy in the left subtree to point to curr
        else:
            prev: BinaryTreeNode = curr.left
            while prev.right and prev.right != curr:
                prev = prev.right

            # Thread doesn't already exist, create a thread add curr to stack and move left
            if not prev.right:
                prev.right = curr
                preorder.append(curr.val)
                curr = curr.left

            # Thread already exists, remove thread and move to right
            else:
                prev.right = None
                curr = curr.right

    return preorder

# Testing the solution
temp = BinaryTreeNode.from_array([1, 2, 3, 4, None, 5, 6])
assert preorderIter(temp) == morris_preorder(temp)
```

</div>

<div id="f115e204" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.834493Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.834221Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.840957Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.840294Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7034e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.842665&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.815631&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def morris_inorder(root: BinaryTreeNode) -> list[int]:
    curr: BinaryTreeNode = root
    inorder: list[int] = []
    while curr:
        if not curr.left:
            inorder.append(curr.val)
            curr = curr.right
        else:
            prev: BinaryTreeNode = curr.left
            while prev.right and prev.right != curr:
                prev = prev.right

            if not prev.right:
                prev.right = curr
                curr = curr.left
            else:
                prev.right = None
                inorder.append(curr.val)
                curr = curr.right

    return inorder

# Testing the solution
temp = BinaryTreeNode.from_array([1, None, 2, 3, 4, 5, None, None, None, 3])
assert inorderIter(temp) == morris_inorder(temp)
```

</div>

<div id="d5feea81" class="cell markdown"
papermill="{&quot;duration&quot;:1.7534e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.877894&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.860360&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/sWf7k1x9XR4?si=6Fdn4oo2ryFIdqpg> Flatten a
binary tree into a linked list

</div>

<div id="023ec163" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.914551Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.914170Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.923215Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.922570Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9085e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.924832&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.895747&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Problem Link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/submissions/1231697617
def flatten(root: BinaryTreeNode) -> None:
    def backtrack(curr: BinaryTreeNode) -> tuple[BinaryTreeNode|None, BinaryTreeNode|None]:
        "Flattens and returns root and the right most node"
        if not curr:
            return (None, None)
        else:
            left_root, left_right = backtrack(curr.left)
            right_root, right_right = backtrack(curr.right)
            curr.left = None
            if left_root and left_right:
                curr.right = left_root
                left_right.right = right_root

            return curr, right_right if right_root else left_right if left_root else curr

    backtrack(root)

# Testing the solution
temp = BinaryTreeNode.from_array([1,2,5,3,4,None,6])
flatten(temp)
temp.to_list()
```

<div class="output execute_result" execution_count="44">

    [1, None, 2, None, 3, None, 4, None, 5, None, 6, None, None]

</div>

</div>

<div id="49e59c7c" class="cell code" execution_count="45"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:44.962063Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:44.961445Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:44.969426Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:44.968684Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8355e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:44.971174&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.942819&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/flatten-binary-tree-to-linked-list/submissions/1232051009
def flattenStriverBacktrack(root: BinaryTreeNode):
    """
    Idea is to use a reverse post order: Right, Left, Root.
    Prev variable contains the right node connection for curr node to make.
    """
    def backtrack(curr: BinaryTreeNode, prev: BinaryTreeNode):
        if curr:
            prev = backtrack(curr.right, prev)
            prev = backtrack(curr.left, prev)
            curr.left = None
            curr.right = prev

        return curr if curr else prev

    backtrack(root, None)

# Testing the solution
temp = BinaryTreeNode.from_array([1,2,5,3,4,None,6])
flattenStriverBacktrack(temp)
temp.to_list()
```

<div class="output execute_result" execution_count="45">

    [1, None, 2, None, 3, None, 4, None, 5, None, 6, None, None]

</div>

</div>

<div id="e4a662da" class="cell code" execution_count="46"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-15T16:15:45.008974Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-15T16:15:45.008350Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-15T16:15:45.016608Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-15T16:15:45.015927Z&quot;}"
papermill="{&quot;duration&quot;:2.9177e-2,&quot;end_time&quot;:&quot;2024-04-15T16:15:45.018312&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-15T16:15:44.989135&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def flattenStriverIter(root: BinaryTreeNode):
    "Same as code above but using stack"
    stack: list[BinaryTreeNode] = [root]
    while stack:
        curr = stack.pop()
        if curr.right:
            stack.append(curr.right)
        if curr.left:
            stack.append(curr.left)
        curr.left = None
        if stack:
            curr.right = stack[-1]

# Testing the solution
temp = BinaryTreeNode.from_array([1,2,5,3,4,None,6])
flattenStriverIter(temp)
temp.to_list()
```

<div class="output execute_result" execution_count="46">

    [1, None, 2, None, 3, None, 4, None, 5, None, 6, None, None]

</div>

</div>
