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
    duration: 2.029483
    end_time: "2024-05-27T04:16:32.528099"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-27T04:16:30.498616"
    version: 2.6.0
---

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:4.816e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.523241&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.518425&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:31.532582Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:31.532225Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:31.881712Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:31.881249Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.355598,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.883113&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.527515&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.204e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.891863&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.887659&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:31.901464Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:31.900860Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:31.905896Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:31.905380Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0885e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.906927&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.896042&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class ListNode:
    def __init__(self, val=0, next_=None):
        self.val = val
        self.next = next_

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

<div id="8f195f7d" class="cell markdown"
papermill="{&quot;duration&quot;:4.103e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.915823&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.911720&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:31.925140Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:31.924686Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:31.929167Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:31.928673Z&quot;}"
papermill="{&quot;duration&quot;:1.0258e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.930245&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.919987&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class DLLNode:
    def __init__(self, val: int = 0, next_=None, prev = None):
        self.val = val
        self.next = next_
        self.prev = next_

    def __str__(self):
        return str(self.val)

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
        result = []
        curr = self
        while curr:
            result.append(curr.val)
            curr = curr.next
        return result
```

</div>

<div id="3bd55ce0" class="cell markdown"
papermill="{&quot;duration&quot;:4.095e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.938520&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.934425&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:31.947742Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:31.947271Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:31.950732Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:31.950224Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.093e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.951739&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.942646&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.114e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.959962&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.955848&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:31.969060Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:31.968777Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:31.971930Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:31.971514Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.949e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.973028&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.964079&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.131e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.981320&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.977189&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:31.990593Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:31.990138Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:31.993529Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:31.992996Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.699e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:31.995172&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.985473&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.191e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.004174&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:31.999983&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.013349Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.013003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.018536Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.018122Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1308e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.019628&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.008320&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.09e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.027905&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.023815&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.036937Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.036616Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.041572Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.041045Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0752e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.042705&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.031953&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.118e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.050982&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.046864&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.060350Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.059874Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.064428Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.063976Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0399e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.065518&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.055119&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.081e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.073699&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.069618&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.083012Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.082551Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.086589Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.086062Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.896e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.087760&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.077864&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.14e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.096115&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.091975&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.105721Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.105222Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.109300Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.108753Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0032e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.110394&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.100362&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.108e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.118693&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.114585&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.128109Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.127635Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.131802Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.131391Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0058e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.132888&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.122830&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.111e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.141299&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.137188&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.150604Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.150135Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.154172Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.153733Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.772e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.155231&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.145459&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.088e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.163422&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.159334&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.172670Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.172249Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.177251Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.176724Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.084e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.178348&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.167508&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.089e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.186656&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.182567&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.195823Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.195364Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.200402Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.199890Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0815e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.201541&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.190726&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.122e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.209822&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.205700&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.219045Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.218589Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.223430Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.222997Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0502e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.224473&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.213971&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.233833Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.233409Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.237916Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.237473Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.04e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.239011&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.228611&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.248312Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.247948Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.253581Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.253132Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1396e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.254605&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.243209&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.13e-3,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.262953&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.258823&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.272365Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.271860Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.276936Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.276399Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1043e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.278155&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.267112&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.287601Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.287156Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.292383Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.291879Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1069e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.293492&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.282423&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T04:16:32.302994Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T04:16:32.302583Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T04:16:32.307722Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T04:16:32.307239Z&quot;}"
papermill="{&quot;duration&quot;:1.1005e-2,&quot;end_time&quot;:&quot;2024-05-27T04:16:32.308766&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T04:16:32.297761&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
