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
    duration: 3.261608
    end_time: "2024-04-12T01:54:32.444360"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-12T01:54:29.182752"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.4274e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.232244&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.217970&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3114e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.258878&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.245764&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.286718Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.286045Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.295642Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.295038Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5378e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.297382&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.272004&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3459e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.324101&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.310642&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.351602Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.351057Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.360803Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.360159Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5288e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.362490&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.337202&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.308e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.389143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.376063&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.416628Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.416072Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.422512Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.421813Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1988e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.424214&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.402226&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2858e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.450263&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.437405&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.477852Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.477328Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.486226Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.485617Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4374e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.487814&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.463440&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2989e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.514002&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.501013&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.541407Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.540782Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.547564Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.546937Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2244e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.549208&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.526964&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3063e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.575471&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.562408&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2897e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.601479&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.588582&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.628803Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.628556Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.634684Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.634032Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1853e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.636422&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.614569&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2905e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.662450&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.649545&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.690283Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.689692Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.696020Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.695410Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1902e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.697707&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.675805&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2895e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.723683&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.710788&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.751154Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.750543Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.763132Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.762398Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8099e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.764844&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.736745&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.31e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.791167&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.778067&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.818843Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.818367Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.826142Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.825534Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3526e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.827816&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.804290&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.314e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.854262&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.841122&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.882362Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.881720Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.887778Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.887127Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1829e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.889426&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.867597&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.917769Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.917213Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.922883Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.922118Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1315e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.924511&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.903196&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:30.952509Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:30.951780Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:30.956741Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:30.955985Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0526e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.958301&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.937775&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3234e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:30.984869&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.971635&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.012802Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.012159Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.018323Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.017593Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1855e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.019983&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:30.998128&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3066e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.046259&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.033193&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.074206Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.073642Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.081070Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.080237Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3177e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.082770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.059593&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3267e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.129581&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.116314&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.158108Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.157395Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.165092Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.164442Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3692e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.166733&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.143041&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3385e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.193596&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.180211&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.221810Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.221281Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.227327Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.226576Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2112e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.229072&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.206960&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3358e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.255857&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.242499&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.284381Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.283719Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.292545Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.291905Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4819e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.294231&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.269412&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.338e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.321059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.307679&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.349062Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.348499Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.358753Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.358014Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6233e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.360624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.334391&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3371e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.387489&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.374118&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.415979Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.415330Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.425502Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.424875Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6084e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.427106&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.401022&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3292e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.453823&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.440531&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.482295Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.481709Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.490252Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.489511Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.457e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.492005&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.467435&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.334e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.518833&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.505493&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.547328Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.546656Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.553769Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.553020Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3235e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.555655&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.532420&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3196e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.582439&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.569243&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.610536Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.609870Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.616871Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.616113Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2731e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.618481&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.595750&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.647229Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.646568Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.655039Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.654300Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4637e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.656666&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.632029&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.685252Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.684666Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.691295Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.690564Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2606e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.692866&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.670260&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3269e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.719536&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.706267&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.747820Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.747128Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.756758Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.755989Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5525e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.758458&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.732933&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3427e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.785499&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.772072&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fmflMqVOC7k?si=1AX2ea08UGtxw0mj> Print
Root to Node path in Binary Tree

</div>

<div id="f0244aad" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.813353Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.812948Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.821497Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.820689Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4282e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.823135&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.798853&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3231e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.849949&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.836718&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lowest common ancestor Video Link:
<https://youtu.be/_-QHfMDde90?si=3pJ5ysXG6FArt3Q3>

</div>

<div id="7a501b5a" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.878180Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.877688Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.884256Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.883570Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2461e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.885858&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.863397&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.353e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.913144&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.899614&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum width of a binary Tree Video Link:
<https://youtu.be/ZbybYvcVLks?si=_r6ouO7uxfz3DI6I>

</div>

<div id="249090c8" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:31.941650Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:31.941118Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:31.948125Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:31.947502Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3073e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.949766&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.926693&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3573e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:31.976978&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.963405&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fnmisPM6cVo?si=gK9Xm0WNZQ6dqBk6> Check
children sum property in Binary Tree

</div>

<div id="e9c463d9" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:32.005650Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:32.004890Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:32.011281Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:32.010660Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2349e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.012932&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:31.990583&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3539e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.040124&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.026585&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maintain children sum property of a binary Tree

</div>

<div id="20d7e7dd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:32.068645Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:32.068045Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:32.076320Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:32.075672Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4309e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.077933&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.053624&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:32.106439Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:32.105850Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:32.113884Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:32.113152Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.418e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.115713&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.091533&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3479e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.142879&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.129400&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/i9ORlEy6EsI?si=GlIarkkKAHDMEXss> Print all
nodes at K distance from target in Binary Tree

</div>

<div id="af18ee1c" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:32.171663Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:32.171002Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:32.181838Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:32.181100Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6837e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.183463&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.156626&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3462e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.210620&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.197158&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/2r5wLmQfD6g?si=V-Tirx2isc0Mt7Qp> Time to
burn a Binary Tree

</div>

<div id="67ee9af0" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:32.239228Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:32.238700Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:32.248083Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:32.247446Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5513e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.249764&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.224251&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3763e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.277326&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.263563&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/u-yWemKGWO0?si=-xcOq69rKzHwnkSC> Count
total nodes in a complete Binary Tree

</div>

<div id="dd5cd4ce" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-12T01:54:32.305909Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-12T01:54:32.305646Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-12T01:54:32.312300Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-12T01:54:32.311576Z&quot;}"
papermill="{&quot;duration&quot;:2.2909e-2,&quot;end_time&quot;:&quot;2024-04-12T01:54:32.313987&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-12T01:54:32.291078&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
