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
    duration: 4.075911
    end_time: "2024-04-13T17:24:05.874658"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-13T17:24:01.798747"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.61e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:02.880174&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:02.864074&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5135e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:02.910716&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:02.895581&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:02.942793Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:02.942168Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:02.952221Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:02.951457Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.843e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:02.954283&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:02.925853&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.505e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:02.985270&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:02.970220&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.017670Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.016930Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.026888Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.026106Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.83e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.028842&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.000542&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5085e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.059295&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.044210&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.091405Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.090759Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.097876Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.096802Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5201e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.099627&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.074426&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5061e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.130220&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.115159&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.162085Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.161346Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.171369Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.170735Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7876e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.173039&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.145163&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4899e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.203237&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.188338&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.235518Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.234898Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.242085Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.241365Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5161e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.243649&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.218488&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4959e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.273826&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.258867&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.4825e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.303539&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.288714&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.335467Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.334919Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.341506Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.340753Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4583e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.343221&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.318638&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5148e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.373680&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.358532&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.405616Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.405133Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.411533Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.410750Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4467e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.413172&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.388705&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5097e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.443899&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.428802&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.475852Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.475208Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.487666Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.486886Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0403e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.489349&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.458946&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5139e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.519755&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.504616&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.552143Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.551496Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.559814Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.559125Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6496e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.561512&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.535016&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5146e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.592053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.576907&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.624382Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.623620Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.629903Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.629248Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.438e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.631567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.607187&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.664185Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.663515Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.669453Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.668698Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4037e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.671080&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.647043&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.703553Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.702936Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.708350Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.707636Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3608e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.710095&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.686487&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5112e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.740631&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.725519&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.773400Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.772723Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.779457Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.778763Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4998e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.781087&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.756089&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5205e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.811746&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.796541&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.864770Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.864109Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.872254Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.871457Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:4.7115e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.874015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.826900&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5432e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.905131&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.889699&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:03.937986Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:03.937316Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:03.944924Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:03.944151Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6005e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.946578&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.920573&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5256e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:03.977351&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.962095&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.010186Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.009510Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.015998Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.015250Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4964e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.017684&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:03.992720&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5527e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.048934&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.033407&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.081536Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.080824Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.089654Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.088884Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7095e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.091396&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.064301&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.555e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.122931&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.107381&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.155636Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.154919Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.165686Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.165014Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8982e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.167341&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.138359&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5402e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.198526&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.183124&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.231503Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.230873Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.241103Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.240345Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8864e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.242973&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.214109&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5471e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.274184&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.258713&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.306967Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.306357Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.315418Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.314656Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7726e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.317298&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.289572&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5458e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.348671&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.333213&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.381398Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.380847Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.388334Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.387572Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5881e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.389995&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.364114&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5727e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.421324&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.405597&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.454256Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.453563Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.461225Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.460396Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6078e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.462983&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.436905&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.496191Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.495665Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.504535Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.503729Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7506e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.506324&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.478818&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.539536Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.538743Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.546101Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.545412Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5748e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.547877&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.522129&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5687e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.579542&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.563855&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.612522Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.611711Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.621852Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.621185Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8614e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.623675&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.595061&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5491e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.655062&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.639571&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fmflMqVOC7k?si=1AX2ea08UGtxw0mj> Print
Root to Node path in Binary Tree

</div>

<div id="f0244aad" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.688342Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.687678Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.696468Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.695657Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7658e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.698607&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.670949&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="26">

    [1, 2, 5, 7]

</div>

</div>

<div id="b7a03676" class="cell markdown"
papermill="{&quot;duration&quot;:1.554e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.730354&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.714814&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lowest common ancestor Video Link:
<https://youtu.be/_-QHfMDde90?si=3pJ5ysXG6FArt3Q3>

</div>

<div id="7a501b5a" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.763400Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.762798Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.769887Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.769101Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5767e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.771567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.745800&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.554e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.803060&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.787520&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum width of a binary Tree Video Link:
<https://youtu.be/ZbybYvcVLks?si=_r6ouO7uxfz3DI6I>

</div>

<div id="249090c8" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.835808Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.835186Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.842795Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.842025Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5837e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.844398&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.818561&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5672e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.875919&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.860247&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fnmisPM6cVo?si=gK9Xm0WNZQ6dqBk6> Check
children sum property in Binary Tree

</div>

<div id="e9c463d9" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.908828Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.908278Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.914796Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.914033Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.489e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.916425&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.891535&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5585e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.947779&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.932194&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maintain children sum property of a binary Tree

</div>

<div id="20d7e7dd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:04.981048Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:04.980436Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:04.988715Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:04.988034Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6977e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:04.990444&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:04.963467&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="bf9f3b28" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.023865Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.023150Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.031785Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.031127Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.733e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.033486&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.006156&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5703e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.065559&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.049856&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/i9ORlEy6EsI?si=GlIarkkKAHDMEXss> Print all
nodes at K distance from target in Binary Tree

</div>

<div id="af18ee1c" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.099188Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.098468Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.110469Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.109676Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1082e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.112115&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.081033&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5633e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.143795&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.128162&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/2r5wLmQfD6g?si=V-Tirx2isc0Mt7Qp> Time to
burn a Binary Tree

</div>

<div id="67ee9af0" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.177071Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.176457Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.186245Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.185554Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8346e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.187961&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.159615&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.5612e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.219510&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.203898&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/u-yWemKGWO0?si=-xcOq69rKzHwnkSC> Count
total nodes in a complete Binary Tree

</div>

<div id="dd5cd4ce" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.252832Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.252128Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.258829Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.258157Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5324e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.260597&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.235273&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.563e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.292085&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.276455&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Construct binary tree from preorder and inorder traversal Video Link:
<https://youtu.be/aZNaLrVebKQ?si=bSe8CP3Bxk0bM3nG>

</div>

<div id="62f3bcad" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.325301Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.324609Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.333732Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.332925Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.785e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.335557&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.307707&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="35">

    [10, 20, 30, 40, 50, 60, None, None, None, None, None, None, None]

</div>

</div>

<div id="878e7fa6" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.369672Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.368945Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.380454Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.379589Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0453e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.382219&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.351766&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="36">

    [10, 20, 30, 40, 50, 60, None, None, None, None, None, None, None]

</div>

</div>

<div id="c0d37bdc" class="cell markdown"
papermill="{&quot;duration&quot;:1.5988e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.414616&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.398628&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/LgLRTaEMRVc?si=AuIS8bfI3SLknUaS> Binary
Tree from Postorder and Inorder traversal

</div>

<div id="53e42711" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.448572Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.447842Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.457374Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.456509Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8395e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.459085&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.430690&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="37">

    [1, 2, 5, 3, 4, None, None, None, None, None, None]

</div>

</div>

<div id="2f83f35a" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.493826Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.493129Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.504361Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.503573Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.037e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.506029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.475659&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="38">

    [1, 2, 5, 3, 4, None, None, None, None, None, None]

</div>

</div>

<div id="4a30f23a" class="cell markdown"
papermill="{&quot;duration&quot;:2.1592e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.544677&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.523085&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-YbXySKJsX8?si=GF9GnCHLV1gDfcWK> Serialize
and Deserialize Binary Trees

</div>

<div id="b286bec0" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.579483Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.578916Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.591416Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.590730Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1856e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.593087&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.561231&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="ec2dd2db" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-13T17:24:05.627964Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-13T17:24:05.627643Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-13T17:24:05.638209Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-13T17:24:05.637454Z&quot;}"
papermill="{&quot;duration&quot;:2.9885e-2,&quot;end_time&quot;:&quot;2024-04-13T17:24:05.639845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-13T17:24:05.609960&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
