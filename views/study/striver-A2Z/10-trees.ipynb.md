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
    duration: 2.712875
    end_time: "2024-04-10T11:14:42.130472"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-10T11:14:39.417597"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:1.1842e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.481855&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.470013&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0688e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.503528&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.492840&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.526693Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.526060Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.536889Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.536252Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4345e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.538583&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.514238&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1149e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.560688&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.549539&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.583635Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.582998Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.592508Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.591880Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2895e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.594244&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.571349&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0723e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.615872&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.605149&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.638557Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.638057Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.644543Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.643848Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9709e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.646169&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.626460&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0542e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.667442&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.656900&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.689994Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.689410Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.698335Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.697599Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2212e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.700227&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.678015&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0594e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.721986&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.711392&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.744575Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.743982Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.750969Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.750289Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0392e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.752886&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.732494&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0825e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.774467&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.763642&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0567e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.795750&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.785183&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.818447Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.817856Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.824175Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.823403Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9572e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.825876&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.806304&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0851e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.847589&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.836738&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.870334Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.869730Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.877081Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.876309Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0746e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.878878&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.858132&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0625e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.900234&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.889609&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.922504Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.922256Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.934592Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.933775Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.5562e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.936345&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.910783&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0695e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.958090&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.947395&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:40.980840Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:40.980267Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:40.987892Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:40.987137Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0799e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:40.989654&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:40.968855&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0674e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.011201&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.000527&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.034225Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.033543Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.039334Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.038567Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9194e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.041111&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.021917&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.064353Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.063732Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.069353Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.068623Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8884e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.071037&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.052153&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.094018Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.093528Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.098621Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.097955Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8432e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.100399&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.081967&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0713e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.121948&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.111235&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.144901Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.144269Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.151013Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.150332Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9985e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.152709&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.132724&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0782e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.174583&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.163801&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.198084Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.197432Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.205454Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.204692Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1852e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.207246&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.185394&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0972e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.229431&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.218459&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.253323Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.252759Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.260316Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.259550Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1508e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.261931&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.240423&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1101e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.284461&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.273360&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.307874Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.307515Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.314102Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.313259Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0383e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.315828&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.295445&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1009e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.338050&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.327041&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.362025Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.361391Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.369881Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.369241Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2462e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.371725&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.349263&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0942e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.393924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.382982&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.417415Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.416835Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.427303Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.426621Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4199e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.429103&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.404904&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1056e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.451503&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.440447&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/q_a6lpbKJdw?si=d1p9utIGRbbi7q84> Vertial
order traversal of Binary Tree

</div>

<div id="584c0df0" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.475693Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.474946Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.485231Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.484487Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.4582e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.487178&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.462596&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1062e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.509456&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.498394&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/Et9OCDNvJ78?si=JB9v3iN8uhAELNkl> Top view
of a Binary Tree

</div>

<div id="fbf1035d" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.552897Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.552400Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.561366Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.560615Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2968e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.563145&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.540177&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0969e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.585124&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.574155&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0FtVY6I4pB8?si=pBJ-JgXeSz_WxjCs> Bottom
view of a Binary tree

</div>

<div id="f1b0d9dd" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.608556Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.607933Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.615228Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.614543Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0784e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.616933&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.596149&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1071e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.639233&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.628162&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/KV4mRzTjlAk?si=lzQH9S7GrgZKUjMj> Right /
Left view of a Binary Tree

</div>

<div id="8d6decb1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.662445Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.661921Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.669026Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.668311Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0611e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.670756&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.650145&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.694576Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.694027Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.702342Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.701604Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2173e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.704089&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.681916&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.727897Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.727256Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.734196Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.733576Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0649e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.736000&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.715351&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.104e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.758182&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.747142&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/nKggNAiEpBE?si=abzPcl6pKzyFpJ2i> Problem
Link:
<https://leetcode.com/problems/symmetric-tree/submissions/1227182868>

</div>

<div id="7dae62c7" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.781553Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.780944Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.791084Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.790403Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3661e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.792835&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.769174&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0914e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.814837&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.803923&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/fmflMqVOC7k?si=1AX2ea08UGtxw0mj> Print
Root to Node path in Binary Tree

</div>

<div id="f0244aad" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.838252Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.837684Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.845944Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.845155Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1969e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.847779&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.825810&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.1158e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.870468&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.859310&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lowest common ancestor Video Link:
<https://youtu.be/_-QHfMDde90?si=3pJ5ysXG6FArt3Q3>

</div>

<div id="7a501b5a" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-10T11:14:41.894330Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-10T11:14:41.893741Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-10T11:14:41.900782Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-10T11:14:41.900021Z&quot;}"
papermill="{&quot;duration&quot;:2.0911e-2,&quot;end_time&quot;:&quot;2024-04-10T11:14:41.902532&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-10T11:14:41.881621&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
