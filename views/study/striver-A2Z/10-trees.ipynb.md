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
    duration: 3.106422
    end_time: "2024-04-11T17:11:50.407168"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-11T17:11:47.300746"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.319e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.385381&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.372191&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1999e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.409635&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.397636&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.435554Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.434859Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.445032Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.444270Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5371e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.446939&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.421568&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2535e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.471708&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.459173&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.497934Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.497108Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.507573Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.506895Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5469e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.509240&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.483771&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.197e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.533389&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.521419&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.559109Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.558369Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.565251Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.564490Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1827e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.567118&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.545291&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2073e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.591331&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.579258&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.617346Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.616665Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.627142Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.626351Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5266e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.628843&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.603577&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1922e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.653057&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.641135&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.678333Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.677971Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.685266Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.684546Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2114e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.687053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.664939&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1793e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.710854&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.699061&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1698e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.734507&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.722809&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.760477Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.759760Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.766401Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.765719Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1592e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.768124&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.746532&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1758e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.792017&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.780259&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.817754Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.817070Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.823440Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.822772Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1205e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.825125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.803920&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2009e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.849299&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.837290&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.875260Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.874587Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.887105Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.886262Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.7489e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.888868&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.861379&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2085e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.913266&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.901181&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.939557Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.938830Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:48.947432Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:48.946774Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3701e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.949156&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.925455&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1977e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:48.973354&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.961377&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:48.999921Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:48.999115Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.005552Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.004895Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1663e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.007329&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:48.985666&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.033459Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.032932Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.039050Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.038302Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1021e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.040685&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.019664&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.067145Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.066421Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.071663Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.070891Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0438e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.073457&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.053019&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1984e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.097788&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.085804&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.124276Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.123786Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.130345Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.129571Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1682e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.131985&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.110303&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2125e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.156467&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.144342&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.182713Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.181965Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.189996Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.189249Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3064e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.191697&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.168633&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2157e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.238209&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.226052&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.264806Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.264147Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.271932Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.271152Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.303e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.273610&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.250580&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2148e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.298071&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.285923&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.324486Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.323909Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.330460Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.329679Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1821e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.332204&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.310383&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.242e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.357008&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.344588&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.383859Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.383172Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.392001Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.391218Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4193e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.393629&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.369436&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2198e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.418311&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.406113&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.444732Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.444055Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.454198Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.453530Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5242e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.455894&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.430652&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2341e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.480807&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.468466&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.507787Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.507291Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.517684Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.516897Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.6055e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.519423&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.493368&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2105e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.543939&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.531834&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.570233Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.569614Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.578883Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.578091Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4414e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.580586&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.556172&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2225e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.605572&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.593347&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.632380Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.631648Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.639176Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.638402Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2913e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.640890&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.617977&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.218e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.665546&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.653366&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.691837Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.691199Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.698598Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.697831Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2503e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.700301&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.677798&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.726783Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.726421Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.735179Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.734394Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.42e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.736911&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.712711&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.763696Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.763134Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.770193Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.769435Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2421e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.771944&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.749523&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2139e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.796490&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.784351&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.822490Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.821957Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.831977Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.831246Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4906e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.833664&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.808758&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2307e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.858469&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.846162&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fmflMqVOC7k?si=1AX2ea08UGtxw0mj> Print
Root to Node path in Binary Tree

</div>

<div id="f0244aad" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.885159Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.884428Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.893234Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.892472Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4153e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.895001&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.870848&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.258e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.920415&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.907835&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lowest common ancestor Video Link:
<https://youtu.be/_-QHfMDde90?si=3pJ5ysXG6FArt3Q3>

</div>

<div id="7a501b5a" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:49.947750Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:49.946918Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:49.954041Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:49.953358Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.283e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.955787&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.932957&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.3496e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:49.982003&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.968507&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum width of a binary Tree Video Link:
<https://youtu.be/ZbybYvcVLks?si=_r6ouO7uxfz3DI6I>

</div>

<div id="249090c8" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:50.009058Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:50.008427Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:50.016200Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:50.015493Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3339e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:50.017934&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:49.994595&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2433e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:50.043015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:50.030582&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fnmisPM6cVo?si=gK9Xm0WNZQ6dqBk6> Check
children sum property in Binary Tree

</div>

<div id="e9c463d9" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:50.069905Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:50.069163Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:50.076337Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:50.075659Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.251e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:50.078009&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:50.055499&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.2425e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:50.103161&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:50.090736&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maintain children sum property of a binary Tree

</div>

<div id="20d7e7dd" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:50.130753Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:50.130029Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:50.138892Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:50.138183Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4541e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:50.140624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:50.116083&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-11T17:11:50.167611Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-11T17:11:50.166886Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-11T17:11:50.175374Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-11T17:11:50.174716Z&quot;}"
papermill="{&quot;duration&quot;:2.3695e-2,&quot;end_time&quot;:&quot;2024-04-11T17:11:50.177031&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-11T17:11:50.153336&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
