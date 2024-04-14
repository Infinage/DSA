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
    duration: 4.64859
    end_time: "2024-04-14T10:25:13.561598"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-14T10:25:08.913008"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.7516e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.035147&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.017631&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6413e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.068226&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.051813&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.102711Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.102385Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.112717Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.112063Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9812e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.114469&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.084657&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6346e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.147739&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.131393&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.182725Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.182163Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.192449Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.191548Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9792e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.194215&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.164423&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6787e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.227716&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.210929&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.262652Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.262342Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.269522Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.268704Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6925e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.271252&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.244327&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6681e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.304636&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.287955&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.339321Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.338617Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.348009Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.347318Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8711e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.349789&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.321078&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6236e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.382820&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.366584&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.417818Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.417085Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.424991Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.424298Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7438e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.426711&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.399273&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6655e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.460066&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.443411&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=Bfqd8BsPVuw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=81>
Iterative Preorder traversal

</div>

<div id="6021695b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.494712Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.493941Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.501339Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.500672Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6574e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.503065&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.476491&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6796e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.536869&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.520073&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.571889Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.571173Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.577935Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.577196Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6188e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.579641&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.553453&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6588e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.612976&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.596388&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.648547Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.647842Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.654525Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.653811Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6375e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.656215&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.629840&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6527e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.689434&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.672907&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.724664Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.723947Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.736559Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.735816Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2168e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.738230&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.706062&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.653e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.771651&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.755121&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.806474Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.805807Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.814170Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.813448Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7823e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.815895&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.788072&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6666e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.849524&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.832858&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.884803Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.884170Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.890552Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.889842Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6144e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.892271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.866127&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.927465Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.926781Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.933044Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.932234Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5811e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.934740&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.908929&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:10.970523Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:10.969737Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:10.975177Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:10.974528Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5031e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:10.976860&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.951829&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6695e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.010708&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:10.994013&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.046066Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.045323Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.052150Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.051333Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6418e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.053856&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.027438&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.8817e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.109527&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.070710&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.145167Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.144528Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.152476Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.151666Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7792e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.154217&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.126425&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6738e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.187972&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.171234&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.223367Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.222717Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.230369Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.229591Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7326e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.232114&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.204788&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6985e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.266184&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.249199&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.301905Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.301121Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.308215Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.307408Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.692e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.309914&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.282994&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6727e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.343663&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.326936&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.379352Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.378656Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.387479Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.386797Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8589e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.389203&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.360614&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6671e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.422942&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.406271&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.458321Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.457636Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.467545Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.466891Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9578e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.469271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.439693&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7086e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.503663&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.486577&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.540073Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.539301Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.549636Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.548957Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0531e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.551403&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.520872&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7051e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.585635&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.568584&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.621578Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.621191Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.630885Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.630102Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9811e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.632817&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.603006&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7019e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.667149&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.650130&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.702812Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.702121Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.709725Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.708933Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7303e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.711393&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.684090&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6937e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.745789&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.728852&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.781834Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.781460Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.790422Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.789655Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9361e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.792311&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.762950&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.828125Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.827451Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.834804Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.834053Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6905e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.836477&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.809572&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.872923Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.872280Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.879439Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.878649Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7312e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.881175&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.853863&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6984e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.915770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.898786&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:11.952158Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:11.951379Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:11.961481Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:11.960682Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0533e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.963249&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.932716&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8417e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:11.999323&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:11.980906&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fmflMqVOC7k?si=1AX2ea08UGtxw0mj> Print
Root to Node path in Binary Tree

</div>

<div id="f0244aad" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.035172Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.034466Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.043072Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.042284Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8623e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.044873&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.016250&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7076e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.079415&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.062339&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lowest common ancestor Video Link:
<https://youtu.be/_-QHfMDde90?si=3pJ5ysXG6FArt3Q3>

</div>

<div id="7a501b5a" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.118304Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.117978Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.125077Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.124145Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.999e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.126894&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.096904&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7288e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.161824&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.144536&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum width of a binary Tree Video Link:
<https://youtu.be/ZbybYvcVLks?si=_r6ouO7uxfz3DI6I>

</div>

<div id="249090c8" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.197998Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.197465Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.204994Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.204179Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7631e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.206758&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.179127&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7837e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.242289&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.224452&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fnmisPM6cVo?si=gK9Xm0WNZQ6dqBk6> Check
children sum property in Binary Tree

</div>

<div id="e9c463d9" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.278575Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.277824Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.285047Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.284348Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.72e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.286680&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.259480&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8341e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.322263&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.303922&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maintain children sum property of a binary Tree

</div>

<div id="20d7e7dd" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.358632Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.357930Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.366696Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.365945Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8969e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.368565&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.339596&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.405635Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.405024Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.414289Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.413552Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.992e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.416084&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.386164&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7152e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.450765&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.433613&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/i9ORlEy6EsI?si=GlIarkkKAHDMEXss> Print all
nodes at K distance from target in Binary Tree

</div>

<div id="af18ee1c" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.487508Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.486678Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.498172Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.497376Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1844e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.500112&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.468268&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.734e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.535098&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.517758&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/2r5wLmQfD6g?si=V-Tirx2isc0Mt7Qp> Time to
burn a Binary Tree

</div>

<div id="67ee9af0" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.571461Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.570773Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.580832Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.580166Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0166e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.582544&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.552378&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7649e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.617996&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.600347&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/u-yWemKGWO0?si=-xcOq69rKzHwnkSC> Count
total nodes in a complete Binary Tree

</div>

<div id="dd5cd4ce" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.654748Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.654068Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.661666Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.660981Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7831e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.663321&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.635490&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6955e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.697509&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.680554&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Construct binary tree from preorder and inorder traversal Video Link:
<https://youtu.be/aZNaLrVebKQ?si=bSe8CP3Bxk0bM3nG>

</div>

<div id="62f3bcad" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.734003Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.733367Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.743055Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.742250Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0147e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.744923&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.714776&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.781970Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.781305Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.792785Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.792000Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1721e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.794407&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.762686&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7844e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.830124&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.812280&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/LgLRTaEMRVc?si=AuIS8bfI3SLknUaS> Binary
Tree from Postorder and Inorder traversal

</div>

<div id="53e42711" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.867218Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.866589Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.875904Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.875049Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9776e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.877684&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.847908&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.915074Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.914402Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:12.924844Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:12.924052Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.112e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.926658&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.895538&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7553e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:12.962155&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.944602&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-YbXySKJsX8?si=GF9GnCHLV1gDfcWK> Serialize
and Deserialize Binary Trees

</div>

<div id="b286bec0" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:12.999978Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:12.999139Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:13.011565Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:13.010865Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.3352e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.013217&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:12.979865&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:13.051106Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:13.050464Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:13.061063Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:13.060285Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1325e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.062770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:13.031445&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7808e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.098517&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:13.080709&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Morris traversal of Binary Tree Video Link:
<https://youtu.be/80Zug6D1_r4?si=Npe19WIqtFI_aa5c> Advantage is that
while it consumes O(N) time, it only takes up O(1) space

</div>

<div id="22ad4618" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:13.136409Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:13.135704Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:13.143021Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:13.142205Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8232e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.144748&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:13.116516&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:13.183044Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:13.182322Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:13.189895Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:13.189128Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8799e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.191625&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:13.162826&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.8046e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.228173&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:13.210127&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/sWf7k1x9XR4?si=6Fdn4oo2ryFIdqpg> Flatten a
binary tree into a linked list

</div>

<div id="023ec163" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:13.266594Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:13.265959Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:13.275586Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:13.274811Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0747e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.277399&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:13.246652&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-14T10:25:13.315755Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-14T10:25:13.315106Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-14T10:25:13.323414Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-14T10:25:13.322614Z&quot;}"
papermill="{&quot;duration&quot;:2.9344e-2,&quot;end_time&quot;:&quot;2024-04-14T10:25:13.325137&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-14T10:25:13.295793&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/flatten-binary-tree-to-linked-list/submissions/1232051009
def flattenStriver(root: BinaryTreeNode):
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
flattenStriver(temp)
temp.to_list()
```

<div class="output execute_result" execution_count="45">

    [1, None, 2, None, 3, None, 4, None, 5, None, 6, None, None]

</div>

</div>
