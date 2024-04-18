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
    duration: 4.500982
    end_time: "2024-04-18T14:41:37.414525"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-18T14:41:32.913543"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.8165e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:33.976270&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:33.958105&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.663e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.009914&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:33.993284&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.045072Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.044322Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.054696Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.053875Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0084e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.056615&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.026531&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7146e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.091605&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.074459&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.127292Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.126607Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.136439Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.135691Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9638e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.138250&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.108612&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.669e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.171828&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.155138&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.207053Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.206332Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.212881Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.212151Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5962e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.214475&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.188513&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6813e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.248207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.231394&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.284262Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.283567Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.292858Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.292077Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9193e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.294500&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.265307&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6464e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.327633&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.311169&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.362556Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.361823Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.368919Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.368302Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6302e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.370595&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.344293&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.656e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.403871&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.387311&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=Bfqd8BsPVuw&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=81>
Iterative Preorder traversal

</div>

<div id="6021695b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.438660Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.437950Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.444789Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.444157Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5865e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.446403&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.420538&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6628e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.480032&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.463404&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.514578Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.514288Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.520047Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.519293Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5009e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.521714&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.496705&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
    while curr or stack:
        if curr:
            stack.append(curr)
            curr = curr.left
        else:
            curr = stack.pop()
            result.append(curr.val)
            curr = curr.right

    return result

# Testing the solution
assert inorderIter(BinaryTreeNode.from_array([1, None, 2, 3])) == [1, 3 ,2]
```

</div>

<div id="bc03474b" class="cell markdown"
papermill="{&quot;duration&quot;:1.6466e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.555195&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.538729&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.590227Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.589529Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.596144Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.595382Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6171e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.598101&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.571930&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6576e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.631539&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.614963&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.666482Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.665840Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.677871Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.677137Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1211e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.679445&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.648234&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6804e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.713286&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.696482&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.748036Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.747418Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.755089Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.754464Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6682e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.756752&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.730070&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6831e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.790481&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.773650&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.825759Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.825070Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.831177Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.830543Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5306e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.832788&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.807482&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.867785Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.867537Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.873174Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.872405Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4988e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.874808&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.849820&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.910144Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.909522Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.914465Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.913820Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.436e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.916143&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.891783&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6837e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.950030&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.933193&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:34.985981Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:34.985294Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:34.992018Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:34.991293Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6706e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:34.993754&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:34.967048&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6864e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.047268&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.030404&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.083001Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.082258Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.091062Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.090421Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8569e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.092745&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.064176&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6859e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.126658&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.109799&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.161824Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.161365Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.168581Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.167928Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6719e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.170288&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.143569&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6816e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.204347&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.187531&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.239980Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.239682Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.246011Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.245331Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5982e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.247678&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.221696&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7042e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.281861&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.264819&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.317211Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.316760Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.324779Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.324050Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7635e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.326532&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.298897&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6907e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.360492&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.343585&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.395523Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.395248Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.405000Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.404349Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9138e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.406624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.377486&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7027e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.440903&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.423876&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.476041Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.475783Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.486087Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.485380Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9877e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.487795&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.457918&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6876e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.521770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.504894&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.557241Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.556619Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.564701Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.563994Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7463e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.566308&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.538845&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6935e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.600423&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.583488&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.636060Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.635282Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.643031Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.642405Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7374e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.644676&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.617302&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6987e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.679066&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.662079&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.714434Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.713764Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.721783Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.721145Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7532e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.723513&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.695981&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.759275Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.758569Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.766433Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.765817Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7481e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.768159&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.740678&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.804156Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.803595Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.810495Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.809707Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6535e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.812106&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.785571&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6908e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.846038&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.829130&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.881583Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.880903Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.890470Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.889732Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9139e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.892167&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.863028&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.6932e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.926435&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.909503&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fmflMqVOC7k?si=1AX2ea08UGtxw0mj> Print
Root to Node path in Binary Tree

</div>

<div id="f0244aad" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:35.961714Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:35.961075Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:35.969322Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:35.968562Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7517e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:35.970888&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.943371&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7529e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.005670&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:35.988141&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lowest common ancestor Video Link:
<https://youtu.be/_-QHfMDde90?si=3pJ5ysXG6FArt3Q3>

</div>

<div id="7a501b5a" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.042334Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.041977Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.048858Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.048115Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7028e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.050462&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.023434&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.704e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.084730&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.067690&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum width of a binary Tree Video Link:
<https://youtu.be/ZbybYvcVLks?si=_r6ouO7uxfz3DI6I>

</div>

<div id="249090c8" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.120210Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.119696Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.126926Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.126168Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6847e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.128614&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.101767&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7208e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.163296&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.146088&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fnmisPM6cVo?si=gK9Xm0WNZQ6dqBk6> Check
children sum property in Binary Tree

</div>

<div id="e9c463d9" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.198805Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.198282Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.204509Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.203862Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5691e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.206193&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.180502&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7194e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.240926&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.223732&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maintain children sum property of a binary Tree

</div>

<div id="20d7e7dd" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.277037Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.276346Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.284564Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.283901Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8044e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.286241&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.258197&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.321994Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.321490Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.329845Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.329046Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7898e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.331423&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.303525&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7135e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.365870&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.348735&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/i9ORlEy6EsI?si=GlIarkkKAHDMEXss> Print all
nodes at K distance from target in Binary Tree

</div>

<div id="af18ee1c" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.403527Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.402871Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.413818Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.413042Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.093e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.415539&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.384609&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7056e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.449984&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.432928&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/2r5wLmQfD6g?si=V-Tirx2isc0Mt7Qp> Time to
burn a Binary Tree

</div>

<div id="67ee9af0" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.485850Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.485284Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.494950Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.494304Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.9408e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.496564&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.467156&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7094e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.531050&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.513956&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/u-yWemKGWO0?si=-xcOq69rKzHwnkSC> Count
total nodes in a complete Binary Tree

</div>

<div id="dd5cd4ce" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.566558Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.566262Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.573029Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.572237Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6676e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.574845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.548169&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7075e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.609244&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.592169&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Construct binary tree from preorder and inorder traversal Video Link:
<https://youtu.be/aZNaLrVebKQ?si=bSe8CP3Bxk0bM3nG>

</div>

<div id="62f3bcad" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.646665Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.646070Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.655434Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.654714Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0652e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.657140&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.626488&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.694317Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.693590Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.704895Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.704165Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1564e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.706597&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.675033&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7429e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.741657&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.724228&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/LgLRTaEMRVc?si=AuIS8bfI3SLknUaS> Binary
Tree from Postorder and Inorder traversal

</div>

<div id="53e42711" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.778142Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.777571Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.786142Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.785362Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8677e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.787851&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.759174&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.824863Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.824256Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.834389Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.833669Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.0368e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.836025&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.805657&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7889e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.872052&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.854163&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/-YbXySKJsX8?si=GF9GnCHLV1gDfcWK> Serialize
and Deserialize Binary Trees

</div>

<div id="b286bec0" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.909352Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.908691Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.920449Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.919798Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.2069e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.922063&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.889994&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:36.960207Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:36.959758Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:36.970186Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:36.969372Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:3.1708e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:36.971845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.940137&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.9383e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:37.011584&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:36.992201&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Morris traversal of Binary Tree Video Link:
<https://youtu.be/80Zug6D1_r4?si=Npe19WIqtFI_aa5c> Advantage is that
while it consumes O(N) time, it only takes up O(1) space

</div>

<div id="22ad4618" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:37.049397Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:37.048629Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:37.055827Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:37.055080Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8292e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:37.057725&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:37.029433&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:37.095284Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:37.094641Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:37.102014Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:37.101365Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7796e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:37.103610&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:37.075814&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.7615e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:37.139049&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:37.121434&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/sWf7k1x9XR4?si=6Fdn4oo2ryFIdqpg> Flatten a
binary tree into a linked list

</div>

<div id="023ec163" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:37.176256Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:37.175705Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:37.184544Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:37.183807Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.931e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:37.186248&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:37.156938&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:37.223706Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:37.223054Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:37.231304Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:37.230609Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.8518e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:37.232946&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:37.204428&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-18T14:41:37.270643Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-18T14:41:37.270039Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-18T14:41:37.278236Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-18T14:41:37.277523Z&quot;}"
papermill="{&quot;duration&quot;:2.8712e-2,&quot;end_time&quot;:&quot;2024-04-18T14:41:37.279891&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-18T14:41:37.251179&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
