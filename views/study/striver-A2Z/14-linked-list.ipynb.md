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
    version: 3.11.9
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 3.235833
    end_time: "2024-05-29T16:38:25.206891"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-29T16:38:21.971058"
    version: 2.6.0
---

<div id="05899396" class="cell markdown"
papermill="{&quot;duration&quot;:9.77e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.109434&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.099664&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Linked Lists

- For deleting nodes, it works best to have a prev, curr value and that
  way at any point if needed we can retreive it. It is also helpful to
  retreive the tail node instead of resorting to stopping 1 value short
  of null.
- Tortoise and hare algorithm has very important applications in
  detecting cycles, start of loop etc

</div>

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:7.935e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.125383&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.117448&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.142037Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.141822Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.497843Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.497290Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.365925,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.499215&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.133290&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
from typing import List, Optional, Generator
import pandas as pd
import numpy as np
import sqlite3
import re
import io
import math
import collections
import itertools
import functools
import random
import string
import tqdm
import bisect
import heapq
```

</div>

<div id="4d54d767" class="cell markdown"
papermill="{&quot;duration&quot;:7.964e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.515500&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.507536&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.532445Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.531941Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.538129Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.537665Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5849e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.539206&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.523357&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class ListNode:
    def __init__(self, val=0, next_=None):
        self.val = val
        self.next = next_

    def __str__(self):
        return str(self.val)

    def len(self) -> int:
        """
        If we used __len__, it would be run every time we do a bool check.
        Problematic when we have LL with cycles.
        """
        N, curr = 0, self
        while curr is not None:
            N, curr = N + 1, curr.next
        return N

    def tail(self) -> 'ListNode':
        prev, curr = None, self
        while curr is not None:
            prev, curr = curr, curr.next
        return prev or curr

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

<div id="8f195f7d" class="cell markdown"
papermill="{&quot;duration&quot;:7.963e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.555164&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.547201&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.571917Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.571758Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.577342Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.576820Z&quot;}"
papermill="{&quot;duration&quot;:1.5148e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.578393&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.563245&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class DLLNode:
    def __init__(self, val: int = 0, next_=None, prev = None):
        self.val = val
        self.next = next_
        self.prev = next_

    def __str__(self):
        return str(self.val)

    def __len__(self):
        N, curr = 0, self
        while curr is not None:
            N, curr = N + 1, curr.next
        return N

    @staticmethod
    def to_doubly_linked_list(nums: list[int]):
        head = prev = None
        for n in nums:
            curr = DLLNode(n)
            if prev:
                prev.next = curr
                curr.prev = prev
            else:
                head = curr
            prev = curr
        return head

    def to_list(self) -> list[int]:
        resultFwd = []
        prev, curr = None, self
        while curr:
            resultFwd.append(curr.val)
            prev, curr = curr, curr.next

        resultBwd = []
        prev, curr = None, prev # type: ignore
        while curr:
            resultBwd.append(curr.val)
            prev, curr = curr, curr.prev

        assert resultFwd == list(reversed(resultBwd)), "Not a valid DLL"
        return resultFwd
```

</div>

<div id="3bd55ce0" class="cell markdown"
papermill="{&quot;duration&quot;:7.837e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.594292&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.586455&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.611113Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.610688Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.614641Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.614094Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3336e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.615632&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.602296&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def constructLL(arr: list[int]) -> ListNode|None:
    head: "ListNode" | None = None
    tail = head

    for n in arr:
        curr = ListNode(n)
        if not tail:
            head = tail = curr
        else:
            tail.next = curr
            tail = curr

    return head
```

</div>

<div id="0c090b60" class="cell markdown"
papermill="{&quot;duration&quot;:8.019e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.631770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.623751&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.648630Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.648182Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.651911Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.651355Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3309e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.653010&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.639701&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def lengthOfLL(head: ListNode) -> int:
    curr = head
    count = 0
    while curr:
        curr = curr.next
        count += 1

    return count

# Testing the solution
assert lengthOfLL(ListNode.to_singly_linked_list([1,2,3,4,5])) == 5
```

</div>

<div id="bd9565da" class="cell markdown"
papermill="{&quot;duration&quot;:7.92e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.668969&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.661049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.685855Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.685534Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.688996Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.688579Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3168e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.690071&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.676903&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def searchInLinkedList(head: ListNode, k: int):
    curr = head
    while curr:
        if curr.val == k:
            return 1
        else:
            curr = curr.next

    return 0

# Testing the solution
assert searchInLinkedList(ListNode.to_singly_linked_list([1,2,3,4]), 4) == 1
```

</div>

<div id="73478462" class="cell markdown"
papermill="{&quot;duration&quot;:8.126e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.706486&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.698360&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.723407Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.723007Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.728074Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.727657Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4604e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.729122&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.714518&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def delNodePos(head: ListNode, k: int):
    if not head or k == 0:
        return head
    elif k == 1:
        return head.next
    else:
        count: int = 0
        prev: ListNode|None = None
        curr: ListNode|None = head

        while curr:
            count += 1
            if count == k and prev:
                prev.next = prev.next.next
                break
            else:
                prev, curr = curr, curr.next

        return head

# Testing the solution
assert delNodePos(ListNode.to_singly_linked_list([1,2]), 2).to_list() == [1]
assert delNodePos(ListNode.to_singly_linked_list([1,2]), 1).to_list() == [2]
assert delNodePos(ListNode.to_singly_linked_list([1]), 1) is None
assert delNodePos(ListNode.to_singly_linked_list([1]), 10).to_list() == [1]
assert delNodePos(ListNode.to_singly_linked_list([1,2,3]), 10).to_list() == [1,2,3]
```

</div>

<div id="6ea5a2c5" class="cell markdown"
papermill="{&quot;duration&quot;:8.063e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.745422&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.737359&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.762460Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.762061Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.767259Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.766735Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4888e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.768315&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.753427&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def delNodeVal(head: ListNode, val: int):
    if not head:
        return head
    elif head.val == val:
        return head.next
    else:
        prev: ListNode|None = None
        curr: ListNode|None = head
        while curr:
            if curr.val == val and prev:
                prev.next = prev.next.next
                break
            else:
                prev, curr = curr, curr.next

        return head

# Testing the solution
assert delNodeVal(ListNode.to_singly_linked_list([1,2]), 2).to_list() == [1]
assert delNodeVal(ListNode.to_singly_linked_list([1,2]), 1).to_list() == [2]
assert delNodeVal(ListNode.to_singly_linked_list([1]), 1) is None
assert delNodeVal(ListNode.to_singly_linked_list([1]), 10).to_list() == [1]
assert delNodeVal(ListNode.to_singly_linked_list([1,2,3]), 3).to_list() == [1,2]
```

</div>

<div id="53646359" class="cell markdown"
papermill="{&quot;duration&quot;:7.937e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.784269&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.776332&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.801133Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.800707Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.805363Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.804805Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4241e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.806478&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.792237&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def insertNode(head: ListNode, N: int, pos: int, val: int) -> ListNode:
    node = ListNode(val)
    if pos == 0:
        node.next = head
        return node
    else:
        prev: ListNode|None = None
        curr: ListNode|None = head

        count = 0
        while count < pos:
            count += 1
            if curr:
                prev, curr = curr, curr.next

        if prev:
            prev.next = node
            node.next = curr

        return head

# Testing the solution
assert insertNode(ListNode.to_singly_linked_list([1,2,3,4]), 4, 0, 0).to_list() == [0,1,2,3,4]
assert insertNode(ListNode.to_singly_linked_list([]), 0, 0, 0).to_list() == [0]
```

</div>

<div id="80af1929" class="cell markdown"
papermill="{&quot;duration&quot;:7.939e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.822469&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.814530&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.839491Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.839082Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.843083Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.842634Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3537e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.844125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.830588&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def constructDLL(arr: list[int]) -> DLLNode:
    head: DLLNode|None =  None
    prev: DLLNode|None =  None

    for n in arr:
        curr = DLLNode(n)
        if prev:
            prev.next = curr
            curr.prev = prev
        else:
            head = curr
        prev = curr

    return head # type: ignore

# Testing the solution
assert constructDLL([1,2,3,4,5]).to_list() == [1,2,3,4,5]
```

</div>

<div id="57e40a96" class="cell markdown"
papermill="{&quot;duration&quot;:7.948e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.860206&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.852258&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.877001Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.876649Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.880633Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.880193Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3555e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.881709&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.868154&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def addDLLNode(head: DLLNode, p: int, data: int) -> DLLNode:
    node: DLLNode = DLLNode(data)
    prev: DLLNode = head

    while p > 0:
        p -= 1
        prev = prev.next

    next_ = prev.next
    node.next = next_
    prev.next = node
    node.prev = prev

    if next_:
        next_.prev = node

    return head

# Testing the solution
assert addDLLNode(DLLNode.to_doubly_linked_list([2,4,5]), 2, 6).to_list() == [2,4,5,6]
```

</div>

<div id="4cebaf84" class="cell markdown"
papermill="{&quot;duration&quot;:7.943e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.897614&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.889671&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.914488Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.914003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.918657Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.918105Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.418e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.919704&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.905524&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def deleteDLLNode(head: DLLNode, p: int):
    curr: DLLNode = head

    count = p
    while count > 0:
        count -= 1
        curr = curr.next

    prev = curr.prev
    next_ = curr.next

    if prev:
        prev.next = next_
    if next_:
        next_.prev = prev

    return head if p > 0 else head.next

# Testing the solution
assert deleteDLLNode(DLLNode.to_doubly_linked_list([1,2]), 1).to_list() == [1]
assert deleteDLLNode(DLLNode.to_doubly_linked_list([1,2]), 0).to_list() == [2]
assert deleteDLLNode(DLLNode.to_doubly_linked_list([1]), 0) is None
```

</div>

<div id="dfa8d518" class="cell markdown"
papermill="{&quot;duration&quot;:7.864e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.935559&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.927695&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.952412Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.952094Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.956401Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.955857Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3958e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.957456&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.943498&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def reverseDLL(head: DLLNode) -> DLLNode:
    prev: DLLNode = None # type: ignore
    curr: DLLNode = head

    while curr:
        curr.next, curr.prev = prev, curr.next
        prev, curr = curr, curr.prev

    return prev

# Testing the solution
assert reverseDLL(DLLNode.to_doubly_linked_list([1,2])).to_list() == [2,1]
assert reverseDLL(DLLNode.to_doubly_linked_list([2])).to_list() == [2]
assert reverseDLL(DLLNode.to_doubly_linked_list([1,2,3,4])).to_list() == [4,3,2,1]
assert reverseDLL(DLLNode.to_doubly_linked_list([])) is None
```

</div>

<div id="5c7d5007" class="cell markdown"
papermill="{&quot;duration&quot;:7.96e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.973480&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.965520&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:23.990353Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:23.989988Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:23.995146Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:23.994595Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4776e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:23.996202&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:23.981426&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def addTwoNumbers(head1: ListNode, head2: ListNode) -> ListNode:
    n1, n2 = head1, head2
    sum_head: ListNode|None = None
    sum_node: ListNode|None = None
    carry_forward = 0

    # Carry_forward is kept here so that in cases where both are exhausted 
    # and we still have 1 (say 5 + 5, both are exhausted but carry exists)
    while n1 or n2 or carry_forward:
        sum_ = carry_forward

        if n1:
            sum_ += n1.val
            n1 = n1.next
        if n2:
            sum_ += n2.val
            n2 = n2.next

        sum_, carry_forward = sum_ % 10, sum_ // 10
        curr = ListNode(sum_)
        if not sum_node:
            sum_head = sum_node = curr
        else:
            sum_node.next = curr
            sum_node = curr

    return sum_head # type: ignore

# Testing the solution
assert addTwoNumbers(ListNode.to_singly_linked_list([2,4,6]), ListNode.to_singly_linked_list([3,8,7])).to_list() == [5,2,4,1]
assert addTwoNumbers(ListNode.to_singly_linked_list([3,5]), ListNode.to_singly_linked_list([4,5,9,9])).to_list() == [7,0,0,0,1]
```

</div>

<div id="0d492d94" class="cell markdown"
papermill="{&quot;duration&quot;:7.89e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.012119&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.004229&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.029029Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.028704Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.033487Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.032912Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.435e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.034473&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.020123&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/odd-even-linked-list/submissions/1268536963/
def oddEvenList(head: ListNode) -> ListNode:
    """
    The trick here lies in the fact that we should alter the links instead of
    trying to alter the values, since we need a O(1) Space, O(N) time complexity.
    """

    # Handling edge case
    if not head:
        return head

    # Split work into creating the even and odd LLs
    oddHead = odd = head
    evenHead = even = head.next

    # It is possible that we iterate until we reach either odd or even
    # Checking for even makes code simpler, odd makes it more messy
    while even and even.next:
        odd.next = odd.next.next
        even.next = even.next.next
        even, odd = even.next, odd.next

    # Once odd and even LL are constructed, odd next should point to evenHead
    odd.next = evenHead # type: ignore
    return oddHead

# Testing the solution
assert oddEvenList(ListNode.to_singly_linked_list([1,2,3,4,5])).to_list() == [1,3,5,2,4]
assert oddEvenList(ListNode.to_singly_linked_list([1,2,3,4])).to_list() == [1,3,2,4]
assert oddEvenList(ListNode.to_singly_linked_list([1,2])).to_list() == [1,2]
assert oddEvenList(ListNode.to_singly_linked_list([1])).to_list() == [1]
```

</div>

<div id="da1e9ff5" class="cell markdown"
papermill="{&quot;duration&quot;:8.031e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.065230&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.057199&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.082555Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.082153Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.087261Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.086750Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5028e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.088324&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.073296&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def sortList012Idea1(head: ListNode) -> ListNode:
    count0 = count1 = count2 = 0

    # Iterate and compute the counts
    curr = head
    while curr:
        if curr.val == 0:
            count0 += 1
        elif curr.val == 1:
            count1 += 1
        else:
            count2 += 1
        curr = curr.next

    # Replace the values
    curr = head
    while curr:
        if count0 > 0:
            curr.val, count0 = 0, count0 - 1
        elif count1 > 0:
            curr.val, count1 = 1, count1 - 1
        else:
            curr.val, count2 = 2, count2 - 1
        curr = curr.next

    return head

# Testing the solution
assert sortList012Idea1(ListNode.to_singly_linked_list([1,0,2,1,0,1,0,2])).to_list() == [0,0,0,1,1,1,2,2]
assert sortList012Idea1(ListNode.to_singly_linked_list([2,1])).to_list() == [1,2]
```

</div>

<div id="04a13e4d" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.105528Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.105011Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.109832Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.109302Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4478e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.110852&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.096374&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def sortList012Idea2(head: ListNode) -> ListNode:

    # Maintain position until which the LL is sorted
    sorted_end: ListNode = head

    # Sort 0s
    curr = sorted_end
    while curr:
        if curr.val == 0:
            sorted_end.val, curr.val = curr.val, sorted_end.val
            sorted_end = sorted_end.next
        curr = curr.next

    # Sort 1s
    curr = sorted_end
    while curr:
        if curr.val == 1:
            sorted_end.val, curr.val = curr.val, sorted_end.val
            sorted_end = sorted_end.next
        curr = curr.next

    return head

# Testing the solution
assert sortList012Idea2(ListNode.to_singly_linked_list([1,0,2,1,0,1,0,2])).to_list() == [0,0,0,1,1,1,2,2]
assert sortList012Idea2(ListNode.to_singly_linked_list([2,1])).to_list() == [1,2]
```

</div>

<div id="5b07c320" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.127965Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.127647Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.133629Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.133168Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5785e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.134732&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.118947&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Striver Idea 3: One pass solution, similar to odd even list problem
def sortList012Idea3(head: ListNode) -> ListNode:
    # Time: O(N), Space: O(1)
    head0: ListNode = None # type: ignore
    head1: ListNode = None # type: ignore
    head2: ListNode = None # type: ignore

    curr = head
    zero = one = two = None
    while curr:
        next_ = curr.next
        if curr.val == 0:
            if not zero:
                head0 = zero = curr
            else:
                zero.next = curr
                zero = curr
        elif curr.val == 1:
            if not one:
                head1 = one = curr
            else:
                one.next = curr
                one = curr
        else:
            if not two:
                head2 = two = curr
            else:
                two.next = curr
                two = curr

        curr.next, curr = None, next_

    if zero:
        zero.next = head1
    if one:
        one.next = head2

    return head0 if head0 else head1 if head1 else head2

# Testing the solution
assert sortList012Idea3(ListNode.to_singly_linked_list([1,0,2,1,0,1,0,2])).to_list() == [0,0,0,1,1,1,2,2]
assert sortList012Idea3(ListNode.to_singly_linked_list([2,1])).to_list() == [1,2]
assert sortList012Idea3(ListNode.to_singly_linked_list([1,0])).to_list() == [0,1]
```

</div>

<div id="5f9ff800" class="cell markdown"
papermill="{&quot;duration&quot;:8.016e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.150937&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.142921&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Remove Nth node from the end of the linked list Video Link:
<https://youtu.be/3kMKYQ2wNIU?si=njmZ0_XKAc1S0dZo> Ideas:

1.  Delete N - kth node
2.  Reverse the LL, delete kth node and reverse again
3.  Recursively assign numbers to node, while returning skip node if
    number == N - k
4.  Store all nodes into a hashmap. Compute len of LL, delete node and
    return head
5.  Striver's Approach

</div>

<div id="75b0f078" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.167922Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.167612Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.172649Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.172123Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4799e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.173780&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.158981&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions
def removeNthFromEndIdea1(head: ListNode, k: int) -> ListNode:
    # Compute the length
    N, curr = 0, head
    while curr:
        N, curr = N + 1, curr.next

    # Delete N - kth node
    count, prev, curr = 0, None, head
    while count < N - k:
        count += 1
        prev, curr = curr, curr.next

    # Delete 1st Node (idx - 0)
    if not prev:
        head = curr.next

    # Delete any other node
    else:
        prev.next = curr.next

    return head

# Testing the solution
assert removeNthFromEndIdea1(ListNode.to_singly_linked_list([1,2,3,4,5]), 2).to_list() == [1,2,3,5]
assert removeNthFromEndIdea1(ListNode.to_singly_linked_list([1,2,3,4,5]), 5).to_list() == [2,3,4,5]
assert removeNthFromEndIdea1(ListNode.to_singly_linked_list([1,2,3,4,5]), 1).to_list() == [1,2,3,4]
assert removeNthFromEndIdea1(ListNode.to_singly_linked_list([1]), 1) is None
```

</div>

<div id="7b9ce41b" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.191251Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.190801Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.195752Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.195311Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4913e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.196800&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.181887&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def removeNthFromEndIdea4(head: ListNode, k: int) -> ListNode:
    # Store the current, prev for all positions
    prevs: dict[int, tuple[ListNode|None, ListNode|None]] = dict()
    N, prev, curr = 0, None, head
    while curr:
        prevs[N] = prev, curr
        prev, curr, N = curr, curr.next, N + 1

    # Delete kth node from back => N - k from front
    prev, curr = prevs[N - k]
    if prev:
        prev.next = curr.next
    else:
        head = head.next

    return head

# Testing the solution
assert removeNthFromEndIdea4(ListNode.to_singly_linked_list([1,2,3,4,5]), 2).to_list() == [1,2,3,5]
assert removeNthFromEndIdea4(ListNode.to_singly_linked_list([1,2,3,4,5]), 5).to_list() == [2,3,4,5]
assert removeNthFromEndIdea4(ListNode.to_singly_linked_list([1,2,3,4,5]), 1).to_list() == [1,2,3,4]
assert removeNthFromEndIdea4(ListNode.to_singly_linked_list([1]), 1) is None
```

</div>

<div id="ca7f81f2" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.213691Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.213421Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.218431Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.217897Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4557e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.219443&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.204886&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/1269029952
def removeNthFromEndIdea5(head: ListNode, k: int) -> ListNode:
    """
    Target is to reach kth node from the end.
    [_, _, _, _, _], k = 2
              *

    Add a second pointer to the end.
    [_, _, _, _, _] _
              *     #

    Shift left until * reaches 0, we see a gap of k - 1.
    [_, _, _, _, _] _
     *     #

    Hence the idea:
        1. Iterate a fast pointer k times.
        2. Add a second slow pointer.
        3. Start iterating both the fast and slow pointers simaltaneously until fast reaches end.
        4. Slow pointer would now point at the node to be deleted.
    """

    # Iterate k times
    count = 0
    fast = head
    while count < k:
        count += 1
        fast = fast.next

    # Add a second pointer slow, move fast and slow together until fast hits end
    prev, slow = None, head
    while fast:
        prev, slow, fast = slow, slow.next, fast.next

    # Delete 1st Node (idx - 0)
    if not prev:
        head = head.next
    # Delete any other node
    else:
        prev.next = slow.next

    return head

# Testing the solution
assert removeNthFromEndIdea5(ListNode.to_singly_linked_list([1,2,3,4,5]), 2).to_list() == [1,2,3,5]
assert removeNthFromEndIdea5(ListNode.to_singly_linked_list([1,2,3,4,5]), 5).to_list() == [2,3,4,5]
assert removeNthFromEndIdea5(ListNode.to_singly_linked_list([1,2,3,4,5]), 1).to_list() == [1,2,3,4]
assert removeNthFromEndIdea5(ListNode.to_singly_linked_list([1]), 1) is None
```

</div>

<div id="b934ca84" class="cell markdown"
papermill="{&quot;duration&quot;:7.99e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.235574&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.227584&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a linked list Video Link:
<https://youtu.be/D2vI2DNJGd8?si=9usE4WRYEPSsmoPW>

</div>

<div id="8327b0f1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.252396Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.252078Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.256316Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.255858Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3787e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.257366&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.243579&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/reverse-linked-list/submissions/1269437666/
def reverseListRecurse(curr: ListNode) -> ListNode:
    """
    Time: O(N), Space: O(N)
    """
    # Store the next_ node for reversing in the future
    if not curr or not curr.next:
        return curr
    else:
        root = reverseListRecurse(curr.next)
        curr.next.next = curr
        curr.next = None
        return root

# Testing the solution
assert reverseListRecurse(ListNode.to_singly_linked_list([1,2,3,4,5])).to_list() == [5,4,3,2,1]
assert reverseListRecurse(ListNode.to_singly_linked_list([1])).to_list() == [1]
assert reverseListRecurse(ListNode.to_singly_linked_list([1,2])).to_list() == [2,1]
assert reverseListRecurse(ListNode.to_singly_linked_list([])) is None
```

</div>

<div id="edb937c7" class="cell code" execution_count="23"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.274432Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.274119Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.278199Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.277748Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3799e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.279285&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.265486&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/reverse-linked-list/submissions/1269442108/
def reverseListIter(head: ListNode) -> ListNode:
    """
    Time: O(N), Space: O(1)
    """
    prev: ListNode|None = None
    curr: ListNode|None = head
    while curr:
        next_ = curr.next
        curr.next = prev
        prev, curr = curr, next_

    return prev # type: ignore

# Testing the solution
assert reverseListIter(ListNode.to_singly_linked_list([1,2,3,4,5])).to_list() == [5,4,3,2,1]
assert reverseListIter(ListNode.to_singly_linked_list([1])).to_list() == [1]
assert reverseListIter(ListNode.to_singly_linked_list([1,2])).to_list() == [2,1]
assert reverseListIter(ListNode.to_singly_linked_list([])) is None
```

</div>

<div id="9fa31e87" class="cell markdown"
papermill="{&quot;duration&quot;:8.042e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.295513&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.287471&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Palindrome Linked List

</div>

<div id="c1bf8469" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.312563Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.312078Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.318139Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.317598Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.57e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.319233&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.303533&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/palindrome-linked-list/submissions/1269504641/
def isPalindromeIter(head: ListNode) -> bool:
    """
    Use slow and fast pointers to find the middle of LL.
    Make sure that we reverse the linkedlist as the slow pointer moves.

    Update post watching striver: Before returning the solution return the
    reversed portion back to normal (best practice)
    """
    if not head.next:
        return True
    else:
        slow = fast = head
        slow_prev: ListNode|None = None
        fast_prev: ListNode|None = None
        while fast and fast.next:
            # Fast pointer moves as usual
            fast_prev, fast = fast.next, fast.next.next

            # As slow moves along, reverse the LL
            slow_next = slow.next
            slow.next = slow_prev
            slow_prev, slow = slow, slow_next

        if fast: # odd length
            slow, fast = slow_prev, slow.next # type: ignore
        else: # even length
            slow, fast = slow_prev, slow # type: ignore

        while fast and slow:
            if fast.val != slow.val:
                return False
            else:
                fast, slow = fast.next, slow.next

        return True

# Testing the solution
assert isPalindromeIter(ListNode.to_singly_linked_list([1,2,3,2,1])) == True
assert isPalindromeIter(ListNode.to_singly_linked_list([1,2,3,4,1])) == False
assert isPalindromeIter(ListNode.to_singly_linked_list([1,2,2,1])) == True
assert isPalindromeIter(ListNode.to_singly_linked_list([1,2,2,2])) == False
assert isPalindromeIter(ListNode.to_singly_linked_list([1,2])) == False
assert isPalindromeIter(ListNode.to_singly_linked_list([1,1])) == True
```

</div>

<div id="a979ac07" class="cell code" execution_count="25"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.336388Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.335941Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.341765Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.341289Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.549e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.342866&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.327376&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/palindrome-linked-list/submissions/1269543768
def isPalindromeRecursive(head: ListNode) -> bool:
    curr_ = head
    def backtrack(curr: ListNode) -> bool:
        if not curr:
            return True
        else:
            nonlocal curr_
            result = backtrack(curr.next) and curr.val == curr_.val
            curr_ = curr_.next
            return result

    return backtrack(head)

# Testing the solution
assert isPalindromeRecursive(ListNode.to_singly_linked_list([1,2,3,2,1])) == True
assert isPalindromeRecursive(ListNode.to_singly_linked_list([1,2,3,4,1])) == False
assert isPalindromeRecursive(ListNode.to_singly_linked_list([1,2,2,1])) == True
assert isPalindromeRecursive(ListNode.to_singly_linked_list([1,2,2,2])) == False
assert isPalindromeRecursive(ListNode.to_singly_linked_list([1,2])) == False
assert isPalindromeRecursive(ListNode.to_singly_linked_list([1,1])) == True
```

</div>

<div id="d549ddf5" class="cell markdown"
papermill="{&quot;duration&quot;:7.964e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.358909&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.350945&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add one: <https://youtu.be/aXQWhbvT3w0?si=VxL8WQhPa15JP7Nl>

</div>

<div id="ec4aa5bd" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.375714Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.375512Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.379647Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.379214Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3735e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.380665&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.366930&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def addOneRecursive(head: ListNode) -> ListNode:
    def backtrack(curr: ListNode) -> int:
        if not curr:
            return 1
        else:
            value = curr.val + backtrack(curr.next)
            curr.val = value % 10
            return value // 10

    carry = backtrack(head)
    return ListNode(carry, head) if carry else head

# Testing the solution
assert addOneRecursive(ListNode.to_singly_linked_list([9])).to_list() == [1,0]
assert addOneRecursive(ListNode.to_singly_linked_list([0])).to_list() == [1]
```

</div>

<div id="7d6145a8" class="cell code" execution_count="27"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.397973Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.397495Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.402100Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.401635Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4376e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.403145&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.388769&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def addOneIter(head: ListNode) -> ListNode:
    def reverseLL(root: ListNode) -> ListNode:
        prev, curr = None, root
        while curr:
            next_ = curr.next
            curr.next = prev
            prev, curr = curr, next_

        return prev # type: ignore

    rev_head = curr = reverseLL(head)

    # Add 1 to reversed head and move forward
    prev, carry = None, 1
    while curr:
        value = curr.val + carry
        carry, curr.val = value // 10, value % 10
        prev, curr = curr, curr.next

    if carry and prev:
        prev.next = ListNode(carry)

    return reverseLL(rev_head)

# Testing the solution
assert addOneIter(ListNode.to_singly_linked_list([9])).to_list() == [1,0]
assert addOneIter(ListNode.to_singly_linked_list([0])).to_list() == [1]
```

</div>

<div id="f6fa4b2a" class="cell markdown"
papermill="{&quot;duration&quot;:8.029e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.419223&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.411194&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find intersection point of two linked lists:
<https://leetcode.com/problems/intersection-of-two-linked-lists/> Video
Link: <https://youtu.be/0DYoPz2Tpt4?si=Xb8Vkn3dRvw57Se8>

</div>

<div id="7e7a074f" class="cell markdown"
papermill="{&quot;duration&quot;:7.973e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.435228&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.427255&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Code snippet for generating test cases relevant to this problem

</div>

<div id="df06d967" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.452326Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.451983Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.456506Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.456078Z&quot;}"
papermill="{&quot;duration&quot;:1.4298e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.457601&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.443303&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def generateTestCasesForGetIntersectionNodes() -> tuple[ListNode, ListNode, ListNode]:
    """
    1. Generate a list of ListNodes
    2. Split the list into 3 groups (headA, headB, common)
    3. Tail of both headA and headB points to common
    """

    N = random.randint(5, 20)
    nodes = [random.randint(1, 100) for i in range(N)]
    common_length = random.randint(0, N - 2)
    lenA = random.randint(1, N - common_length - 1)
    lenB = N - common_length - lenA

    headA = ListNode.to_singly_linked_list(nodes[:lenA])
    headB = ListNode.to_singly_linked_list(nodes[lenA:lenA + lenB])
    common = ListNode.to_singly_linked_list(nodes[lenA + lenB:])

    if common:
        currA = headA
        while currA.next:
            currA = currA.next

        currB = headB
        while currB.next:
            currB = currB.next

        currA.next = currB.next = common

    return headA, headB, common
```

</div>

<div id="dc25919d" class="cell code" execution_count="29"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.474742Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.474314Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.479173Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.478656Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4503e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.480206&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.465703&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/intersection-of-two-linked-lists/submissions/1270019723
def getIntersectionNode(headA: ListNode, headB: ListNode) -> ListNode|None:
    """
    Compute the length of both nodes.
    The problem is the different sizes of the LL, so move the longer one until both lengths are equal.
    Start iterating and stop at the point where both nodes are the same.
    """
    # Compute lengths of both LL
    N1, curr = 0, headA
    while curr:
        N1, curr = N1 + 1, curr.next

    # Compute lengths of both LL
    N2, curr = 0, headB
    while curr:
        N2, curr = N2 + 1, curr.next

    # Start iterating until there is a match
    currA = headA
    currB = headB
    while currA != currB:
        if N1 == N2:
            currA, currB = currA.next, currB.next
        elif N1 > N2:
            currA = currA.next
            N1 -= 1
        else:
            currB = currB.next
            N2 -= 1

    return currA

# Testing the solution
for i in range(20):
    tempA, tempB, common = generateTestCasesForGetIntersectionNodes()
    assert getIntersectionNode(tempA, tempB) == common
```

</div>

<div id="ddbe2569" class="cell code" execution_count="30"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.497032Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.496876Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.501238Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.500737Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4165e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.502394&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.488229&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def getIntersectionNodeStriver(headA: ListNode, headB: ListNode) -> ListNode|None:
    """
    Iterate currA, currB simaltaneously
    If currA and currB reaches null together return null
    Otherwise move currA to beginning of headB when currA hits null else move currB to beginning of headA when currB hits null

    They align with shifting the pointers to the other LLs because:
        - Assume diff between the len as d
        - Shorter pointer will hit null first and reach the head of longer Linked list, longer pointer would still be d steps behind (at the longer LL).
        - By the time longer pointer hits the shorter LL's head, shorter pointer would have travelled d steps in the longer linked list thus aligning together.

    Time Complexity: O (M + N) (each pointer travels length of LL1 and LL2, but simaltaneously)
    Space Complexity: O(1)
    """
    currA, currB = headA, headB
    while currA or currB:
        if currA == currB:
            return currA
        elif not currA:
            currA = headB
        elif not currB:
            currB = headA
        else:
            currA, currB = currA.next, currB.next
    return None

# Testing the solution
for i in range(20):
    tempA, tempB, common = generateTestCasesForGetIntersectionNodes()
    assert getIntersectionNodeStriver(tempA, tempB) == common
```

</div>

<div id="cbf674eb" class="cell markdown"
papermill="{&quot;duration&quot;:8.028e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.518649&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.510621&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Middle of a linked list:
<https://leetcode.com/problems/middle-of-the-linked-list/> Video Link:
<https://youtu.be/7LjQ57RqgEc?si=5CaPgtXPsfwLGqPJ>

</div>

<div id="42d42838" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.535600Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.535244Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.539113Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.538675Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3467e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.540152&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.526685&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def middleNode(head: ListNode) -> ListNode:
    # Tortoise and hair algorithm
    slow = fast = head
    while fast and fast.next:
        slow, fast = slow.next, fast.next.next

    return slow

# Testing the solution
assert middleNode(ListNode.to_singly_linked_list([1,2,3,4])).val == 3
assert middleNode(ListNode.to_singly_linked_list([1,2,3])).val == 2
assert middleNode(ListNode.to_singly_linked_list([1])).val == 1
```

</div>

<div id="07ca0d01" class="cell markdown"
papermill="{&quot;duration&quot;:8.041e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.556322&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.548281&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle

</div>

<div id="a5f83af7" class="cell markdown"
papermill="{&quot;duration&quot;:8.044e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.572476&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.564432&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Function to generate test cases for LL with cycles

</div>

<div id="ccde5409" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.589502Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.589052Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.593312Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.592855Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3962e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.594400&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.580438&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def generateTestCasesForHasCycle() -> tuple[ListNode, bool, int]:
    cycle = random.random() > 0.5
    N = random.randint(2, 25)
    head = ListNode.to_singly_linked_list([random.randint(1, 50) for i in range(N)])

    if cycle:
        cycle_end = random.randint(0, N - 1)
        cycle_end_node = None
        count, prev, curr = 0, None, head
        while curr:
            if count == cycle_end:
                cycle_end_node = curr
            prev, curr = curr, curr.next
            count += 1
        prev.next = cycle_end_node # type: ignore

    else:
        cycle_end = N

    return head, cycle, N - cycle_end
```

</div>

<div id="6bf15063" class="cell code" execution_count="33"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.611651Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.611212Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.615069Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.614634Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3498e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.616088&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.602590&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/linked-list-cycle/submissions/1270124229/
def hasCycle(head: ListNode) -> bool:
    """
    Once inside cycle fast and slow will always collide, reason being
    At each step, slow is moving away from fast at rate of 1 unit distance. Fast is
    moving towards slow at a rate of 2 unit distances. Net diff is -1. Distance is slowly
    closed in by the fast pointer until they evenutally reach.

    This happens only because slow moves by 1 step and fast moves by 2 steps, so as to keep the
    net diff as 1.
    """
    slow = fast = head
    while slow and fast and fast.next:
        slow, fast = slow.next, fast.next.next
        if slow == fast:
            return True

    return False

# Testing the solution
for i in range(20):
    temp, result, _ = generateTestCasesForHasCycle()
    assert hasCycle(temp) == result
```

</div>

<div id="d4704b18" class="cell markdown"
papermill="{&quot;duration&quot;:8.01e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.632290&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.624280&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find the length of the LL Video Link:
<https://youtu.be/I4g1qbkTPus?si=GVUwRbb-TQ_Ko7md> Brute force: Store
node and time. When a node is revisited, return curr_time - past_time
for the length

</div>

<div id="c473e001" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.649268Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.648838Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.653333Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.652818Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4026e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.654338&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.640312&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def countNodesinLoop(head: ListNode) -> int:
    # Find a point of intersection
    slow = fast = head
    while fast and fast.next:
        slow, fast = slow.next, fast.next.next
        if slow == fast:
            break

    # Count number of nodes in loop
    if not fast or not fast.next:
        return 0
    else:
        count = 1
        curr = fast.next
        while curr != fast:
            curr, count = curr.next, count + 1
        return count

# Testing the solution
for i in range(20):
    temp, result, cycle_length = generateTestCasesForHasCycle()
    assert countNodesinLoop(temp) == cycle_length
```

</div>

<div id="3d4d86ad" class="cell markdown"
papermill="{&quot;duration&quot;:7.997e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.670376&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.662379&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete the middle node of a LL:
<https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/>
Video Link: <https://youtu.be/ePpV-_pfOeI?si=CrCPJnN2MA38JYZh>

</div>

<div id="ac21940a" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.687259Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.686927Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.691321Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.690823Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3989e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.692424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.678435&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/submissions/1270182161
def deleteMiddle(head: ListNode) -> ListNode:
    # Tortoise and hare to find the node's middle
    prev = None
    slow = fast = head
    while fast and fast.next:
        prev, slow, fast = slow, slow.next, fast.next.next

    # Delete the node
    if not prev:
        head = head.next
    else:
        prev.next = prev.next.next

    return head

# Testing the solution
assert deleteMiddle(ListNode.to_singly_linked_list([1,3,4,7,1,2,6])).to_list() == [1,3,4,1,2,6]
assert deleteMiddle(ListNode.to_singly_linked_list([1,2,3,4])).to_list() == [1,2,4]
assert deleteMiddle(ListNode.to_singly_linked_list([2,1])).to_list() == [2]
```

</div>

<div id="79fcca0d" class="cell markdown"
papermill="{&quot;duration&quot;:7.985e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.708614&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.700629&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find starting point of a loop / cycle Video Link:
<https://youtu.be/2Kd0KKmmHFc?si=9XzuefTJpWk7vgEI>

</div>

<div id="4ea0855f" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.725459Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.725301Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.728283Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.727867Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.263e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.729346&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.716716&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def detectCycleStartBrute(head: ListNode) -> ListNode|None:
    set_: set[ListNode] = set()
    curr = head
    while curr:
        if curr not in set_:
            set_.add(curr)
            curr = curr.next
        else:
            return curr
    return None
```

</div>

<div id="ceabaf44" class="cell code" execution_count="37"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.746739Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.746305Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.751170Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.750729Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.459e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.752205&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.737615&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/linked-list-cycle-ii/submissions/1270513369
def detectCycleStart(head: ListNode) -> ListNode|None:
    """
    1. Init fast and slow pointers, iterate until they collide
    2. Init a new pointer and move it simaltaneously along with the slow pointer until they both intersect. This would be the point of intersection.

    For intution watch the video from 16:00
    - When the slow pointer reaches the start of the loop (L distance), the fast pointer would have traversed L distance into the loop.
    - Assume distance between fast pointer and start of the loop is 'd'.
    - We iterate until fast and slow collide. When they collide, slow would have traversed 'd' units and fast would have traversed '2d' units, reason being the d distance is covered by slow pointer a ta pace of 1 unit at a time which fast moving 2 units at a time and takes 2 * d units of travel.
    - Total length of loop is L + d. At collision, slow pointer would be d units into the loop or in other words: L units away from the start of the loop.
    - We move slow (L units away from start of loop) and start iterating from the head (L units from start of loop).
    - They are at equal distance and would collide at start of the loop.
    """
    # Fast and slow pointer algorithm until collision
    slow = fast = head
    while fast and fast.next:
        slow, fast = slow.next, fast.next.next
        if slow == fast:
            break

    # We have reached an intersecting node, we iterate slow and new pointer at head until we intersect again
    if fast and fast.next:
        curr = head
        while curr != slow:
            curr, slow = curr.next, slow.next
        return curr
    else:
        return None

# Testing the solution
for i in range(20):
    temp, _, _ = generateTestCasesForHasCycle()
    detectCycleStartBrute(temp) == detectCycleStart(temp)
```

</div>

<div id="4a5b91af" class="cell markdown"
papermill="{&quot;duration&quot;:8.004e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.768306&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.760302&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete all occurances of key from DLL Video Link:
<https://youtu.be/Mh0NH_SD92k?si=EOHv42dLQgWo2hfo>

</div>

<div id="8afd6d09" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.785359Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.784922Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.789178Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.788726Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.39e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.790281&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.776381&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def deleteAllOccurrences(head: DLLNode, k: int) -> DLLNode:
    curr = head
    while curr:
        if curr.val == k:
            prev, next_ = curr.prev, curr.next
            if not prev:
                head = head.next
            if prev:
                prev.next = next_
            if next_:
                next_.prev = prev
        curr = curr.next

    return head

# Testing the solution
assert deleteAllOccurrences(DLLNode.to_doubly_linked_list([1,2,3,1,1,5,1]), 1).to_list() == [2,3,5]
assert deleteAllOccurrences(DLLNode.to_doubly_linked_list([1,1,5,1]), 1).to_list() == [5]
```

</div>

<div id="c24d725f" class="cell markdown"
papermill="{&quot;duration&quot;:7.968e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.806370&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.798402&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find all pairs that sum to pair Video Link:
<https://youtu.be/YitR4dQsddE?si=hKS4D96sIRLllVkU>

</div>

<div id="db9ee204" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.823295Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.822926Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.827395Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.826864Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4103e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.828479&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.814376&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def findPairsWithGivenSum(target: int, head: DLLNode) -> list[list[int]]:
    # Find the tail of the LL
    tail: DLLNode = head
    while tail.next:
        tail = tail.next

    # Two pointer traversal
    results: list[list[int]] = []
    left, right = head, tail
    while left.val < right.val:
        sum_ = left.val + right.val
        if sum_ == target:
            results.append([left.val, right.val])
            left, right = left.next, right.prev
        elif sum_ < target:
            left = left.next
        else:
            right = right.prev

    return results

# Testing the solution
assert findPairsWithGivenSum(7, DLLNode.to_doubly_linked_list([1,2,4,5,6,8,9])) == [[1,6], [2,5]]
```

</div>

<div id="03d3836e" class="cell markdown"
papermill="{&quot;duration&quot;:8.002e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.844624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.836622&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Remove duplicates from sorted DLL Video Link:
<https://youtu.be/YJKVTnOJXSY?si=iUsYyLyw32khR4qk>

</div>

<div id="96d1a14c" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.861883Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.861534Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.865663Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.865193Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3833e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.866691&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.852858&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def removeDuplicates(head: DLLNode) -> DLLNode:
    """
    Check if prev == curr. We would never face a situation where we have to del the head.
    Time: O(N), Space: O(1)
    """
    curr = head
    while curr:
        prev, next_ = curr.prev, curr.next
        if prev and prev.val == curr.val:
            prev.next = next_
            if next_:
                next_.prev = prev
        curr = curr.next

    return head

# Testing the solution
assert removeDuplicates(DLLNode.to_doubly_linked_list([1,2,2,2,3,3,3,3])).to_list() == [1,2,3]
```

</div>

<div id="0e87575b" class="cell markdown"
papermill="{&quot;duration&quot;:8.058e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.882860&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.874802&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse nodes in K group Video Link:
<https://youtu.be/lIar1skcQYI?si=iMT4yb5RPdSAKTGz>

</div>

<div id="a9d91617" class="cell code" execution_count="41"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.900063Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.899579Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.904937Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.904512Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5064e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.906048&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.890984&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/1271081842
def reverseKGroupBrute(head: ListNode, k: int) -> ListNode:
    "Time: O(2N), Space: O(1)"
    def reverseLL(start: ListNode, end: ListNode):
        """
        Reverses the LL from start to end: end -> ... start -> None
        """
        prev, curr = None, start
        while curr:
            next_ = curr.next if curr != end else None
            curr.next = prev
            prev, curr = curr, next_

    count, prev, curr = 1, None, head
    while curr:
        next_ = curr.next
        if count in [1, k]:
            if prev:
                prev.next = curr
            else:
                head = curr

            if count == 1:
                start = curr
            elif count == k:
                reverseLL(start, curr)
                prev, count = start, 0

        count, curr = count + 1, next_

    return head

# Testing the solution
assert reverseKGroupBrute(ListNode.to_singly_linked_list([1,2,3,4,5]), 2).to_list() == [2,1,4,3,5]
assert reverseKGroupBrute(ListNode.to_singly_linked_list([1,2,3,4,5]), 3).to_list() == [3,2,1,4,5]
```

</div>

<div id="31555836" class="cell markdown"
papermill="{&quot;duration&quot;:8.001e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.922161&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.914160&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Rotate Linked List: <https://leetcode.com/problems/rotate-list/> Video
Link: <https://youtu.be/uT7YI7XbTY8?si=oTcsMXbd4Ukx7peu>

</div>

<div id="21fcd05a" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.939312Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.938904Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.943429Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.942904Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4273e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.944521&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.930248&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/rotate-list/submissions/1271204624
def rotateRight(head: ListNode, k: int) -> ListNode:
    "Space: O(1), Time: O(2N)"
    # Base case
    if not head:
        return head

    else:
        # Rotations beyond N can be rounded off
        N = head.len()
        k = N - (k % N)

        # Link the tail node to the start
        tail = head.tail()
        tail.next = head

        # Remove the connection which needs removal
        prev, curr = tail, head
        while k > 0:
            k, prev, curr = k - 1, curr, curr.next
        prev.next = None

        return curr

# Testing the solution
assert rotateRight(ListNode.to_singly_linked_list([1,2,3,4,5]), 2).to_list() == [4,5,1,2,3]
assert rotateRight(ListNode.to_singly_linked_list([1,2,3,4,5]), 3).to_list() == [3,4,5,1,2]
```

</div>

<div id="b8060f9c" class="cell markdown"
papermill="{&quot;duration&quot;:8.001e-3,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.960617&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.952616&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Merge Two sorted linked lists:
<https://leetcode.com/problems/merge-two-sorted-lists/> Video Link:
<https://youtu.be/jXu-H7XuClE?si=cAYJXOGmugB-R1Jw>

</div>

<div id="9bda15a0" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-29T16:38:24.977748Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-29T16:38:24.977412Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-29T16:38:24.982102Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-29T16:38:24.981605Z&quot;}"
papermill="{&quot;duration&quot;:1.4542e-2,&quot;end_time&quot;:&quot;2024-05-29T16:38:24.983249&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-29T16:38:24.968707&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/merge-two-sorted-lists/submissions/1271581186
def mergeTwoLists(head1: ListNode, head2: ListNode) -> ListNode:
    # Keep a dummy node
    merged: ListNode = ListNode(val=999)

    # Iterate using standard two pointer approach
    curr, curr1, curr2 = merged, head1, head2
    while curr1 or curr2:
        if not curr2 or (curr1 and curr1.val < curr2.val):
            curr.next = curr1
            curr, curr1 = curr.next, curr1.next
        else:
            curr.next = curr2
            curr, curr2 = curr.next, curr2.next

    # Return merged list skipping our dummy
    return merged.next

# Testing the solution
assert mergeTwoLists(ListNode.to_singly_linked_list([1,2,4]), ListNode.to_singly_linked_list([1,3,4])).to_list() == [1,1,2,3,4,4]
assert mergeTwoLists(ListNode.to_singly_linked_list([1,1]), ListNode.to_singly_linked_list([1,2])).to_list() == [1,1,1,2]
```

</div>
