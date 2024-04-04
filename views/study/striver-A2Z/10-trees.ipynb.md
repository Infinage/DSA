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
    duration: 1.353424
    end_time: "2024-04-04T01:09:46.460163"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-04T01:09:45.106739"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:4.379e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.184765&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.180386&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.45e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.191847&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.188397&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-04T01:09:46.200473Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-04T01:09:46.199677Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-04T01:09:46.215742Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-04T01:09:46.215128Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.2348e-2,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.217498&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.195150&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.33e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.224309&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.220979&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-04T01:09:46.232543Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-04T01:09:46.231856Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-04T01:09:46.238617Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-04T01:09:46.237974Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2712e-2,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.240343&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.227631&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.448e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.247181&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.243733&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-04T01:09:46.255314Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-04T01:09:46.254761Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-04T01:09:46.263698Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-04T01:09:46.263025Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4817e-2,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.265384&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.250567&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
    return (inorder_, preorder_ ,postorder_)

# Testing the solution
assert getTreeTraversal(BinaryTreeNode.from_array([1, 3, 4, 5, 2, 7, 6])) == ([5, 3, 2, 1, 7, 4, 6], [1, 3, 5, 2, 4, 7, 6], [5, 2, 3, 7, 6, 4, 1])
```

</div>

<div id="565ebd42" class="cell markdown"
papermill="{&quot;duration&quot;:3.266e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.272129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.268863&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-04T01:09:46.280001Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-04T01:09:46.279747Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-04T01:09:46.286609Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-04T01:09:46.285839Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2867e-2,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.288304&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.275437&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.522e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.295368&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.291846&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.267e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.302000&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.298733&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-04T01:09:46.310546Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-04T01:09:46.309932Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-04T01:09:46.316562Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-04T01:09:46.315764Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2934e-2,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.318305&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.305371&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.352e-3,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.325129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.321777&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-04T01:09:46.333520Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-04T01:09:46.332864Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-04T01:09:46.339113Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-04T01:09:46.338459Z&quot;}"
papermill="{&quot;duration&quot;:1.2302e-2,&quot;end_time&quot;:&quot;2024-04-04T01:09:46.340845&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-04T01:09:46.328543&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
