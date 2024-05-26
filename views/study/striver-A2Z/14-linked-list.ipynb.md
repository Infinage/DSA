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
    duration: 1.937029
    end_time: "2024-05-26T14:16:32.955268"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-26T14:16:31.018239"
    version: 2.6.0
---

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:4.04e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.037678&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.033638&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.045762Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.045399Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.398848Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.398364Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.35894,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.400136&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.041196&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.74e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.407669&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.403929&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.415787Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.415283Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.419850Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.419446Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.793e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.420920&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.411127&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.215e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.428673&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.424458&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.436710Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.436398Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.441007Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.440497Z&quot;}"
papermill="{&quot;duration&quot;:9.83e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.442022&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.432192&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.468e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.449017&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.445549&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.457054Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.456646Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.459860Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.459447Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.365e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.460903&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.452538&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.54e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.468013&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.464473&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.476030Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.475547Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.478966Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.478552Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.515e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.480029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.471514&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.563e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.487197&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.483634&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.495383Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.494928Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.498365Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.497831Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.992e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.499755&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.490763&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.65e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.508151&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.504501&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.516258Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.515804Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.521555Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.521006Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0838e-2,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.522552&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.511714&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.579e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.529813&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.526234&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.537975Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.537528Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.542254Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.541838Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.927e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.543340&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.533413&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.614e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.550541&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.546927&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.558654Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.558212Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.562785Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.562351Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.644e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.563778&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.554134&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.594e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.570911&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.567317&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.578613Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.578453Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.582028Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.581598Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.634e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.583070&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.574436&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.488e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.590125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.586637&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.598259Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.597799Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.601529Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.601086Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.884e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.602567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.593683&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.721e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.610056&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.606335&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.618242Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.617789Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.622163Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.621627Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.569e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.623171&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.613602&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.567e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.630391&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.626824&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.638588Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.638182Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.642248Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.641717Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.345e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.643390&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.634045&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.699e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.650769&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.647070&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.659050Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.658634Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.663435Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.663033Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0096e-2,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.664529&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.654433&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.697e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.671983&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.668286&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.680299Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.679947Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.684946Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.684524Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0394e-2,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.686033&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.675639&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.672e-3,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.693449&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.689777&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.701910Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.701442Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.706172Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.705720Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0023e-2,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.707191&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.697168&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.716147Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.715619Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.720056Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.719639Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0058e-2,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.721149&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.711091&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-26T14:16:32.729828Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-26T14:16:32.729346Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-26T14:16:32.735343Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-26T14:16:32.734791Z&quot;}"
papermill="{&quot;duration&quot;:1.1493e-2,&quot;end_time&quot;:&quot;2024-05-26T14:16:32.736456&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-26T14:16:32.724963&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
