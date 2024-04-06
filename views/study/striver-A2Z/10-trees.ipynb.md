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
    duration: 1.71338
    end_time: "2024-04-06T02:18:23.906831"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-06T02:18:22.193451"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:7.337e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.250318&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.242981&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.434e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.263450&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.257016&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.277585Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.276955Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.286629Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.286003Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9321e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.289091&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.269770&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
```

</div>

<div id="c70ac08c" class="cell markdown"
papermill="{&quot;duration&quot;:6.418e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.302098&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.295680&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.316787Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.316173Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.325386Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.324760Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8934e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.327611&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.308677&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.293e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.340290&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.333997&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.354616Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.353878Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.361162Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.360459Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6669e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.363397&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.346728&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.519e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.376386&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.369867&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.390557Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.389885Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.400000Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.399371Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9693e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.402434&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.382741&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.384e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.415391&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.409007&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.429193Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.428934Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.436220Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.435322Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6748e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.438461&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.421713&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.269e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.451215&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.444946&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.33e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.463916&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.457586&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.479198Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.478610Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.485127Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.484443Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5866e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.486733&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.470867&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.181e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.499297&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.493116&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.513706Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.513071Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.519251Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.518585Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5264e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.520921&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.505657&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.261e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.533588&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.527327&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.547653Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.546977Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.559260Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.558619Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.1061e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.560980&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.539919&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.344e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.573786&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.567442&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.588366Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.587773Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.595573Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.594908Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6818e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.597252&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.580434&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.364e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.610128&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.603764&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.624417Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.623849Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.629560Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.628832Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4609e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.631229&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.616620&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.645758Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.645119Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.651113Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.650469Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5065e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.652837&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.637772&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.667495Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.666805Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.672157Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.671495Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4293e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.673802&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.659509&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.674e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.687275&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.680601&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.701953Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.701347Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.707924Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.707214Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5658e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.709595&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.693937&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.508e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.722818&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.716310&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.737493Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.736887Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.744637Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.743981Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6747e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.746333&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.729586&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.709e-3,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.759923&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.753214&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-06T02:18:23.775180Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-06T02:18:23.774596Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-06T02:18:23.781697Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-06T02:18:23.780933Z&quot;}"
papermill="{&quot;duration&quot;:1.6306e-2,&quot;end_time&quot;:&quot;2024-04-06T02:18:23.783297&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-06T02:18:23.766991&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
