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
    duration: 1.391972
    end_time: "2024-04-05T01:28:46.216985"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-05T01:28:44.825013"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:5.153e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.862555&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.857402&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="c70ac08c" class="cell markdown"
papermill="{&quot;duration&quot;:4.173e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.871141&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.866968&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:45.880899Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:45.880276Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:45.895825Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:45.895210Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2319e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.897513&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.875194&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.035e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.905688&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.901653&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:45.915223Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:45.914729Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:45.921336Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:45.920711Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3205e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.922982&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.909777&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.039e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.931145&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.927106&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:45.940646Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:45.940111Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:45.949342Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:45.948699Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5743e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.950961&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.935218&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.018e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.959157&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.955139&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:45.968265Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:45.968031Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:45.974955Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:45.974318Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3367e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.976605&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.963238&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.207e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.985053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.980846&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.021e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:45.993169&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.989148&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:46.002865Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:46.002215Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:46.008860Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:46.008228Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3274e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:46.010527&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:45.997253&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.039e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:46.018739&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:46.014700&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:46.028322Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:46.027722Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:46.033969Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:46.033357Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2835e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:46.035662&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:46.022827&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.071e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:46.043848&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:46.039777&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:46.053289Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:46.052687Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:46.065501Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:46.064756Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9257e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:46.067199&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:46.047942&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div class="output execute_result" execution_count="7">

    [6, 5, 4, 3, 2, 8, 7, 1]

</div>

</div>

<div id="cd401b3e" class="cell markdown"
papermill="{&quot;duration&quot;:4.223e-3,&quot;end_time&quot;:&quot;2024-04-05T01:28:46.075750&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:46.071527&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-05T01:28:46.085874Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-05T01:28:46.085215Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-05T01:28:46.093683Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-05T01:28:46.093051Z&quot;}"
papermill="{&quot;duration&quot;:1.5329e-2,&quot;end_time&quot;:&quot;2024-04-05T01:28:46.095340&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-05T01:28:46.080011&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

temp = BinaryTreeNode.from_array([1, 3, 4, 5, 2, 7, 6])
assert getTreeTraversal(temp) == getTreeTraversal_single_traversal(temp)
```

</div>
