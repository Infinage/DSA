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
    duration: 2.034934
    end_time: "2024-04-08T01:59:46.138742"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-08T01:59:44.103808"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:9.133e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.146113&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.136980&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.372e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.163130&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.154758&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.181224Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.180619Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.189783Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.189051Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0184e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.191602&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.171418&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.36e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.208504&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.200144&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.226599Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.226105Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.235726Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.235031Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0537e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.237421&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.216884&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.219e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.253923&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.245704&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.272058Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.271503Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.277896Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.277158Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7308e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.279587&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.262279&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.653e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.296609&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.287956&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.314270Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.314038Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.322878Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.322228Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9611e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.324543&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.304932&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.244e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.341212&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.332968&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.358993Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.358709Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.365628Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.364983Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7805e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.367290&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.349485&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.602e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.384474&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.375872&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.273e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.401554&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.393281&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.419828Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.419254Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.425555Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.424919Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.744e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.427333&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.409893&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.169e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.443969&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.435800&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.461938Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.461349Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.467685Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.467039Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6988e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.469319&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.452331&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.378e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.486179&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.477801&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.504047Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.503473Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.516109Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.515363Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3348e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.517765&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.494417&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.371e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.534786&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.526415&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.553071Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.552559Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.560247Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.559506Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8661e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.561905&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.543244&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.381e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.578858&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.570477&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.597200Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.596912Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.602874Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.602220Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6852e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.604447&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.587595&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.622849Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.622259Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.628046Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.627270Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6636e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.629606&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.612970&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.648172Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.647510Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.652761Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.652145Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6185e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.654352&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.638167&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.416e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.671323&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.662907&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.689440Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.688868Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.694975Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.694239Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7002e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.696706&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.679704&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.387e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.713721&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.705334&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.732139Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.731595Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.739248Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.738465Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8672e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.740898&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.722226&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.534e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.758047&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.749513&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.776457Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.775935Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.782954Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.782232Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8054e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.784681&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.766627&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.611e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.802142&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.793531&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.820861Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.820396Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.826480Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.825733Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7208e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.828091&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.810883&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.454e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.845314&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.836860&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.863875Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.863293Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.871638Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.870880Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9363e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.873295&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.853932&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.625e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.890494&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.881869&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.909146Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.908548Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.918296Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.917568Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0754e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.920053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.899299&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.614e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.937522&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.928908&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:45.956210Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:45.955613Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:45.965525Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:45.964787Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1137e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.967262&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.946125&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.544e-3,&quot;end_time&quot;:&quot;2024-04-08T01:59:45.984525&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.975981&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-08T01:59:46.003254Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-08T01:59:46.002644Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-08T01:59:46.011289Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-08T01:59:46.010528Z&quot;}"
papermill="{&quot;duration&quot;:1.9775e-2,&quot;end_time&quot;:&quot;2024-04-08T01:59:46.012995&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-08T01:59:45.993220&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
