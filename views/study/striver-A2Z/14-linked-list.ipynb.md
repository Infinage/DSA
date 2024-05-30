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
    duration: 3.54919
    end_time: "2024-05-30T16:12:47.949853"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-30T16:12:44.400663"
    version: 2.6.0
---

<div id="05899396" class="cell markdown"
papermill="{&quot;duration&quot;:1.0385e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:45.540015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:45.529630&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.671e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:45.557446&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:45.548775&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:45.576107Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:45.575862Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:45.931479Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:45.930914Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.366811,&quot;end_time&quot;:&quot;2024-05-30T16:12:45.932826&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:45.566015&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0731e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:45.952833&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:45.942102&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:45.972958Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:45.972360Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:45.978958Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:45.978457Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.733e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:45.980117&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:45.962787&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.593e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:45.997420&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:45.988827&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.015566Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.015345Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.020977Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.020539Z&quot;}"
papermill="{&quot;duration&quot;:1.6032e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.022054&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.006022&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.585e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.039330&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.030745&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.057634Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.057348Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.060951Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.060435Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4053e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.062052&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.047999&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.795e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.079733&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.070938&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.098203Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.097819Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.101445Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.100996Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3964e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.102462&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.088498&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.658e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.119888&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.111230&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.138413Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.137940Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.141622Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.141163Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4013e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.142658&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.128645&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.662e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.160129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.151467&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.178432Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.178019Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.183469Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.182956Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5744e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.184523&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.168779&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.671e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.201876&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.193205&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.220482Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.219974Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.225219Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.224786Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5707e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.226260&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.210553&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.59e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.243595&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.235005&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.262328Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.261878Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.266466Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.266033Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5196e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.267530&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.252334&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.606e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.284903&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.276297&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.302810Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.302645Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.306194Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.305768Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3675e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.307220&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.293545&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.704e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.324706&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.316002&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.343023Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.342654Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.346695Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.346138Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4373e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.347764&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.333391&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.763e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.365320&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.356557&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.383738Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.383402Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.387796Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.387222Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4864e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.388806&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.373942&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.564e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.406059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.397495&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.424298Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.423879Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.427960Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.427485Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.434e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.429008&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.414668&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.673e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.446470&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.437797&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.481203Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.480720Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.485927Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.485414Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6151e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.487080&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.470929&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.72e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.504632&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.495912&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.522907Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.522642Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.527313Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.526751Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4968e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.528340&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.513372&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.815e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.546005&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.537190&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.564612Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.564287Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.569178Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.568666Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5412e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.570193&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.554781&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.588866Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.588474Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.592767Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.592333Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4652e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.593798&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.579146&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.612681Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.612161Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.618037Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.617597Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6473e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.619115&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.602642&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.728e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.636789&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.628061&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.655601Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.655081Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.660092Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.659649Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5626e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.661130&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.645504&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.679667Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.679457Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.684497Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.684072Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5635e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.685542&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.669907&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.704326Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.704003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.709239Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.708708Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5865e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.710309&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.694444&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.798e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.727876&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.719078&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a linked list Video Link:
<https://youtu.be/D2vI2DNJGd8?si=9usE4WRYEPSsmoPW>

</div>

<div id="8327b0f1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.746350Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.745976Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.750167Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.749741Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.459e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.751207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.736617&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.769697Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.769283Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.773457Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.772948Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4422e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.774478&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.760056&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.802e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.792133&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.783331&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Palindrome Linked List

</div>

<div id="c1bf8469" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.811508Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.810965Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.817377Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.816836Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7301e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.818468&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.801167&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.837498Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.837120Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.842019Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.841505Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5644e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.843167&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.827523&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.719e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.860870&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.852151&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add one: <https://youtu.be/aXQWhbvT3w0?si=VxL8WQhPa15JP7Nl>

</div>

<div id="ec4aa5bd" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.879668Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.879136Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.883459Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.882989Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4918e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.884538&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.869620&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.903716Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.903338Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.908009Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.907560Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.543e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.909098&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.893668&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.778e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.926883&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.918105&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find intersection point of two linked lists:
<https://leetcode.com/problems/intersection-of-two-linked-lists/> Video
Link: <https://youtu.be/0DYoPz2Tpt4?si=Xb8Vkn3dRvw57Se8>

</div>

<div id="7e7a074f" class="cell markdown"
papermill="{&quot;duration&quot;:8.609e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.944221&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.935612&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Code snippet for generating test cases relevant to this problem

</div>

<div id="df06d967" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.962974Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.962463Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.967259Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.966724Z&quot;}"
papermill="{&quot;duration&quot;:1.5364e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.968277&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.952913&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:46.986497Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:46.986287Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:46.991400Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:46.990917Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.547e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:46.992422&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:46.976952&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.011071Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.010655Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.015112Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.014610Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4988e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.016228&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.001240&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.004e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.034298&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.025294&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Middle of a linked list:
<https://leetcode.com/problems/middle-of-the-linked-list/> Video Link:
<https://youtu.be/7LjQ57RqgEc?si=5CaPgtXPsfwLGqPJ>

</div>

<div id="42d42838" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.053078Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.052821Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.056754Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.056300Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4738e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.057869&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.043131&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.155e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.076213&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.067058&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle

</div>

<div id="a5f83af7" class="cell markdown"
papermill="{&quot;duration&quot;:8.681e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.093664&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.084983&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Function to generate test cases for LL with cycles

</div>

<div id="ccde5409" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.112513Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.112191Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.116579Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.116115Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5171e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.117629&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.102458&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.136948Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.136529Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.140672Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.140156Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5106e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.141752&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.126646&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.745e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.159279&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.150534&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find the length of the LL Video Link:
<https://youtu.be/I4g1qbkTPus?si=GVUwRbb-TQ_Ko7md> Brute force: Store
node and time. When a node is revisited, return curr_time - past_time
for the length

</div>

<div id="c473e001" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.178116Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.177485Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.182217Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.181805Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5301e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.183304&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.168003&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.687e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.200835&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.192148&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete the middle node of a LL:
<https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/>
Video Link: <https://youtu.be/ePpV-_pfOeI?si=CrCPJnN2MA38JYZh>

</div>

<div id="ac21940a" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.219279Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.218886Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.223425Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.222860Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.488e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.224447&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.209567&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.862e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.242206&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.233344&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find starting point of a loop / cycle Video Link:
<https://youtu.be/2Kd0KKmmHFc?si=9XzuefTJpWk7vgEI>

</div>

<div id="4ea0855f" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.260552Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.260235Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.263551Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.263020Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3752e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.264661&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.250909&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.283136Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.282682Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.287545Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.287074Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5163e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.288562&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.273399&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.653e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.306027&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.297374&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete all occurances of key from DLL Video Link:
<https://youtu.be/Mh0NH_SD92k?si=EOHv42dLQgWo2hfo>

</div>

<div id="8afd6d09" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.324433Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.324084Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.328459Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.327983Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.475e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.329495&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.314745&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.882e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.347296&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.338414&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find all pairs that sum to pair Video Link:
<https://youtu.be/YitR4dQsddE?si=hKS4D96sIRLllVkU>

</div>

<div id="db9ee204" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.365778Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.365495Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.369921Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.369415Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5051e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.371044&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.355993&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.868e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.388705&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.379837&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Remove duplicates from sorted DLL Video Link:
<https://youtu.be/YJKVTnOJXSY?si=iUsYyLyw32khR4qk>

</div>

<div id="96d1a14c" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.407139Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.406631Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.410766Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.410330Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4421e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.411837&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.397416&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.913e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.430247&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.421334&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse nodes in K group Video Link:
<https://youtu.be/lIar1skcQYI?si=iMT4yb5RPdSAKTGz>

</div>

<div id="a9d91617" class="cell code" execution_count="41"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.448751Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.448481Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.453807Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.453298Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5918e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.454950&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.439032&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.724e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.472695&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.463971&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Rotate Linked List: <https://leetcode.com/problems/rotate-list/> Video
Link: <https://youtu.be/uT7YI7XbTY8?si=oTcsMXbd4Ukx7peu>

</div>

<div id="21fcd05a" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.490905Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.490651Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.495036Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.494532Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4673e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.496069&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.481396&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:8.788e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.513680&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.504892&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Merge Two sorted linked lists:
<https://leetcode.com/problems/merge-two-sorted-lists/> Video Link:
<https://youtu.be/jXu-H7XuClE?si=cAYJXOGmugB-R1Jw>

</div>

<div id="9bda15a0" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.532141Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.531824Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.536388Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.535873Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4989e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.537510&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.522521&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="635b1ce4" class="cell markdown"
papermill="{&quot;duration&quot;:8.87e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.555303&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.546433&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Flattening a linked list Video Link:
<https://youtu.be/ykelywHJWLg?si=xEMHwY-n0wADGYA6>

</div>

<div id="8e34e33f" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.573830Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.573314Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.577527Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.576988Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4498e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.578547&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.564049&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class GFGFlattenLLNode:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.bottom = None

    def __repr__(self):
        return str(self.data)

    def to_list(self) -> list[int]:
        result: list[int] = []
        horizontal = self
        while horizontal:
            vertical = horizontal
            while vertical:
                result.append(vertical.data)
                vertical = vertical.bottom
            horizontal = horizontal.next
        return result
```

</div>

<div id="6f6d740f" class="cell code" execution_count="45"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.597267Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.596860Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.605009Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.604472Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8691e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.606145&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.587454&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def generateTestCasesForGFGFlattenLL(N: int, heights: list[int], values: list[int]) -> GFGFlattenLLNode:
    nested: list[GFGFlattenLLNode] = []
    i = 0
    for height in heights:
        nested.append(GFGFlattenLLNode(-1))
        curr = nested[-1]
        while height > 0:
            curr.bottom = GFGFlattenLLNode(values[i])
            curr, i, height = curr.bottom, i + 1, height - 1
        nested[-1] = nested[-1].bottom

    prev = nested[0]
    for i in range(1, N):
        curr = nested[i]
        prev.next = curr
        prev = curr

    return nested[0]

# Testing the test case generator ;)
generateTestCasesForGFGFlattenLL(4, [4,2,3,4], [5,7,8,30,10,20,19,22,50,28,35,40,45]).to_list()
```

<div class="output execute_result" execution_count="45">

    [5, 7, 8, 30, 10, 20, 19, 22, 50, 28, 35, 40, 45]

</div>

</div>

<div id="7db963ef" class="cell code" execution_count="46"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.625509Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.625105Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.630423Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.629993Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6324e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.631543&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.615219&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def GFGflattenLL(root) -> GFGFlattenLLNode:
    """
    Time: O(N) + O(N x N x M) ~ O(N x N x M)
    Space: O(N)
    """
    # Store all the top level nodes
    curr: GFGFlattenLLNode = root
    heads: set[GFGFlattenLLNode] = set()
    while curr:
        next_ = curr.next
        heads.add(curr)
        curr.next = None
        curr = next_

    # Create a dummy node of ease of ops
    merged = GFGFlattenLLNode(0)
    mh = merged
    while heads:
        min_ = GFGFlattenLLNode(math.inf)
        for curr in heads:
            if curr.data < min_.data:
                min_ = curr

        heads.remove(min_)
        mh.bottom = min_
        mh, min_ = mh.bottom, min_.bottom
        if min_:
            heads.add(min_)

    return merged.bottom

# Testing the solution
assert GFGflattenLL(generateTestCasesForGFGFlattenLL(4, [4,2,3,4], [5,7,8,30,10,20,19,22,50,28,35,40,45])).to_list() == [5,7,8,10,19,20,22,28,30,35,40,45,50]
assert GFGflattenLL(generateTestCasesForGFGFlattenLL(4, [4,1,3,1], [5,7,8,30,10,19,22,50,28])).to_list() == [5,7,8,10,19,22,28,30,50]
```

</div>

<div id="0af56f93" class="cell code" execution_count="47"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.650631Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.650253Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.656660Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.656152Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7001e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.657736&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.640735&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def GFGflattenLLStriver(root) -> GFGFlattenLLNode:
    """
    Instead of iterating through all N for every iteration, we can try
    joining two heads at a time for better runtime.

    Time: O(N) + O(N x 2M) ~ O(NM)
    Space: O(N)
    """
    def mergeGFGNodes(head1: GFGFlattenLLNode, head2: GFGFlattenLLNode) -> GFGFlattenLLNode:
        merged: GFGFlattenLLNode = GFGFlattenLLNode(-1)
        mh, curr1, curr2 = merged, head1, head2
        while curr1 or curr2:
            if not curr2 or (curr1 and curr1.data < curr2.data):
                mh.bottom = curr1
                mh, curr1 = mh.bottom, curr1.bottom
            else:
                mh.bottom = curr2
                mh, curr2 = mh.bottom, curr2.bottom

        return merged.bottom

    # Store all the top level nodes
    curr: GFGFlattenLLNode = root
    heads: set[GFGFlattenLLNode] = set()
    while curr:
        next_ = curr.next
        heads.add(curr)
        curr.next = None
        curr = next_

    while len(heads) > 1:
        heads.add(mergeGFGNodes(heads.pop(), heads.pop()))

    return heads.pop()

# Testing the solution
assert GFGflattenLLStriver(generateTestCasesForGFGFlattenLL(4, [4,2,3,4], [5,7,8,30,10,20,19,22,50,28,35,40,45])).to_list() == [5,7,8,10,19,20,22,28,30,35,40,45,50]
assert GFGflattenLLStriver(generateTestCasesForGFGFlattenLL(4, [4,1,3,1], [5,7,8,30,10,19,22,50,28])).to_list() == [5,7,8,10,19,22,28,30,50]
```

</div>

<div id="372da5f1" class="cell markdown"
papermill="{&quot;duration&quot;:9.099e-3,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.675939&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.666840&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Merge K sorted Lists:
<https://leetcode.com/problems/merge-k-sorted-lists/> Video Link:
<https://youtu.be/1zktEppsdig?si=o9ttliAfO99YDin8>

</div>

<div id="0c98d074" class="cell code" execution_count="48"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.694811Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.694463Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.699426Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.698949Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5651e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.700501&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.684850&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/merge-k-sorted-lists/submissions/1272090418
def mergeKLists(lists: list[ListNode]) -> ListNode:
    """
    Time: O(2N + 3N .. KN) ~ O(N x K ** 2) ~ O(N ** 3)
    Space: O(1)
    """
    def merge(head1: ListNode, head2: ListNode) -> ListNode:
        merged: ListNode = ListNode(-1)
        mh, curr1, curr2 = merged, head1, head2
        while curr1 or curr2:
            if not curr2 or (curr1 and curr1.val < curr2.val):
                mh.next = curr1
                mh, curr1 = mh.next, curr1.next
            else:
                mh.next = curr2
                mh, curr2 = mh.next, curr2.next
        return merged.next

    while len(lists) > 1:
        lists.append(merge(lists.pop(), lists.pop()))

    return lists.pop() if lists else None

# Testing the solution
assert mergeKLists([ListNode.to_singly_linked_list([1,4,5]),ListNode.to_singly_linked_list([1,3,4]),ListNode.to_singly_linked_list([2,6])]).to_list() == [1,1,2,3,4,4,5,6]
```

</div>

<div id="3cb0bb18" class="cell code" execution_count="49"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-30T16:12:47.719503Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-30T16:12:47.719154Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-30T16:12:47.724216Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-30T16:12:47.723746Z&quot;}"
papermill="{&quot;duration&quot;:1.5676e-2,&quot;end_time&quot;:&quot;2024-05-30T16:12:47.725244&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-30T16:12:47.709568&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/merge-k-sorted-lists/submissions/1272122618/
def mergeKListsStriver(lists: list[ListNode]) -> ListNode:
    """
    Instead of iterating through pairs of heads, we use a min heap data structure.
    Initially add all heads to heap. Get the min, add to the merged list and add the next_ back to heap.

    Time: O(N x N x log N) (Total Nodes: N x N)
    Space: O(N)
    """

    heads: list[ListNode] = [node for node in lists]
    heap: list[tuple[int, int]] = [(heads[i].val, i) for i in range(len(heads)) if heads[i]]
    heapq.heapify(heap)

    merged: ListNode = ListNode(-1)
    mh = merged
    while heap:
        min_idx = heapq.heappop(heap)[1]
        min_ = heads[min_idx]
        mh.next = min_
        mh = mh.next
        if min_.next:
            heapq.heappush(heap, (min_.next.val, min_idx))
            heads[min_idx] = min_.next

    return merged.next

# Testing the solution
assert mergeKListsStriver([ListNode.to_singly_linked_list([1,4,5]),ListNode.to_singly_linked_list([1,3,4]),ListNode.to_singly_linked_list([2,6])]).to_list() == [1,1,2,3,4,4,5,6]
```

</div>
