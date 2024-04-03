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
    duration: 1.281826
    end_time: "2024-04-03T02:22:54.536468"
    environment_variables: {}
    input_path: study/striver-A2Z/10-trees.ipynb
    output_path: study/striver-A2Z/10-trees.ipynb
    parameters: {}
    start_time: "2024-04-03T02:22:53.254642"
    version: 2.5.0
---

<div id="b29f23a5" class="cell markdown"
papermill="{&quot;duration&quot;:2.793e-3,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.334019&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.331226&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.234e-3,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.338759&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.336525&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Binary tree problems

</div>

<div id="4c5d251b" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-03T02:22:54.344723Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-03T02:22:54.344189Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-03T02:22:54.358777Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-03T02:22:54.358179Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9435e-2,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.360439&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.341004&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.19e-3,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.364911&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.362721&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="f4314d5d" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-03T02:22:54.370470Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-03T02:22:54.370204Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-03T02:22:54.376702Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-03T02:22:54.375959Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1266e-2,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.378377&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.367111&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.058e-3,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.384098&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.381040&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inorder, Postorder, Preorder

</div>

<div id="17b6ec0d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-03T02:22:54.389690Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-03T02:22:54.389456Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-03T02:22:54.398117Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-03T02:22:54.397450Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3281e-2,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.399719&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.386438&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.311e-3,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.404381&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.402070&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Level Order Traversal

</div>

<div id="88639bd0" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-04-03T02:22:54.410048Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-04-03T02:22:54.409791Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-04-03T02:22:54.416399Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-04-03T02:22:54.415617Z&quot;}"
papermill="{&quot;duration&quot;:1.1309e-2,&quot;end_time&quot;:&quot;2024-04-03T02:22:54.418002&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-04-03T02:22:54.406693&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
