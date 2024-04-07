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
    duration: 2.040428
    end_time: "2024-04-07T14:55:23.811300"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-07T14:55:21.770872"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:8.611e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.854275&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.845664&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.48e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.870031&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.862551&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Some useful imports

</div>

<div id="b692ea03" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:22.886983Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:22.886283Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:22.896697Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:22.895959Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0915e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.898467&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.877552&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import collections
import itertools
```

</div>

<div id="c70ac08c" class="cell markdown"
papermill="{&quot;duration&quot;:7.393e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.913508&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.906115&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:22.930014Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:22.929416Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:22.939163Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:22.938466Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9863e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.940785&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.920922&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.382e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.955773&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.948391&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:22.972726Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:22.972003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:22.978875Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:22.978180Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7088e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.980548&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.963460&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.45e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:22.995716&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:22.988266&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.012770Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.012125Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.021351Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.020589Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9569e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.023209&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.003640&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.474e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.038154&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.030680&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.054237Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.053976Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.061145Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.060391Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.717e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.062760&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.045590&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.526e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.078135&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.070609&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.368e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.092958&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.085590&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=lxTGsVXjwvM&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=82>
Iterative Inorder traversal

</div>

<div id="f322e25b" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.109686Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.109051Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.115749Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.114960Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6933e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.117370&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.100437&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.529e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.132754&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.125225&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=2YBhNLodD8Q&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=83>
Iterative post order traversal

</div>

<div id="a728f1cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.149459Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.149095Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.155615Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.154844Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6947e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.157268&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.140321&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.362e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.172365&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.165003&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link:
<https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=84>
Iterative post order traversal using single stack From striver: "This
topic is bit tricky, so try to dry run some trees. Its kinda algorithm
that you need to remember. Cannot help"

</div>

<div id="b8f98a3a" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.189636Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.188943Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.201435Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.200682Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.3106e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.203115&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.180009&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.749e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.218730&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.210981&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/ySp2epYvgTE?si=TItCZRCbbFnyQlyi> Post
Order, In Order, Pre Order Traversal in one iteration

</div>

<div id="ac069236" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.235848Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.235136Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.243462Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.242787Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8837e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.245174&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.226337&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.553e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.260554&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.253001&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Maximum Depth of a Binary Tree:
<https://www.youtube.com/watch?v=eD3tmO66aBA&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=86>

</div>

<div id="77506355" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.277743Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.277043Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.283603Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.282837Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7065e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.285218&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.268153&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.302391Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.301741Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.307666Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.306899Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6168e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.309271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.293103&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.326394Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.325737Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.330997Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.330216Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5518e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.332684&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.317166&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.803e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.348304&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.340501&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check for balanced Binary Tree:
<https://youtu.be/Yt50Jfbd8Po?si=pqjd9p-_S-9vRrmG>

</div>

<div id="fc21bd9b" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.365507Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.364958Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.371758Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.371022Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7372e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.373479&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.356107&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.509e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.388920&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.381411&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Diameter of Binary Tree:
<https://youtu.be/Rezetez59Nk?si=9WeCIb_ik5elrVZm>

</div>

<div id="ce78d08b" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.405979Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.405421Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.413381Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.412606Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8443e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.415096&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.396653&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.746e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.430743&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.422997&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/WszrfSwMz58?si=daE6TYubT_j5MKuT> Maximum
Path Sum:
<https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1224438073>

</div>

<div id="4192b725" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.448323Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.447746Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.455184Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.454374Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8063e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.456915&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.438852&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.779e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.472696&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.464917&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if two trees are identical or not Video Link:
<https://youtu.be/BhuvF_-PWS0?si=C1iPAcpAICZHWRSr>

</div>

<div id="7a2627c8" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.490030Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.489446Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.496150Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.495455Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7338e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.497825&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.480487&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.96e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.513977&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.506017&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/3OXWEdlIGl4?si=prGw3PDHdgEpFJgj> Zig Zag /
Spiral Traversal in a Binary Tree

</div>

<div id="220a0708" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.531493Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.530790Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.539513Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.538710Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9335e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.541194&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.521859&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.807e-3,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.557049&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.549242&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video Link: <https://youtu.be/0ca1nvR0be4?si=Er0-Y8gxhnKlWt6-> Boundary
Traversal in a Binary Tree

</div>

<div id="3e63f2c1" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-07T14:55:23.574627Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-07T14:55:23.573872Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-07T14:55:23.584319Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-07T14:55:23.583654Z&quot;}"
papermill="{&quot;duration&quot;:2.0968e-2,&quot;end_time&quot;:&quot;2024-04-07T14:55:23.585975&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-07T14:55:23.565007&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
