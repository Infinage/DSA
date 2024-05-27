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
    duration: 2.514262
    end_time: "2024-05-27T16:47:23.233824"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-27T16:47:20.719562"
    version: 2.6.0
---

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:6.24e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:21.863188&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:21.856948&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:21.875728Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:21.875282Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.265138Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.264542Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.397844,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.266590&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:21.868746&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.457e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.278730&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.273273&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.290397Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.289767Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.294906Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.294444Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2229e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.295978&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.283749&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.009e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.306224&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.301215&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.317869Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.317314Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.322344Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.321888Z&quot;}"
papermill="{&quot;duration&quot;:1.2185e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.323392&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.311207&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.028e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.333360&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.328332&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.344829Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.344224Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.347918Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.347486Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0769e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.349076&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.338307&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.005e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.359100&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.354095&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.370733Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.370123Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.374033Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.373574Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1012e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.375061&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.364049&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.126e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.385297&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.380171&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.396533Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.395958Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.399797Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.399251Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1395e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.401527&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.390132&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.047e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.411867&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.406820&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.422987Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.422712Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.429219Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.428715Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3575e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.430365&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.416790&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.02e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.440444&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.435424&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.451908Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.451340Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.456832Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.456259Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2545e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.457924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.445379&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.022e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.467957&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.462935&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.479324Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.478791Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.483829Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.483296Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.218e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.485059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.472879&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.321e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.495510&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.490189&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.506855Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.506302Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.510406Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.509960Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.107e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.511464&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.500394&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.992e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.521483&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.516491&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.532812Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.532369Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.536652Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.536204Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1367e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.537801&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.526434&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.951e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.547698&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.542747&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.558835Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.558339Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.562852Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.562323Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1286e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.563879&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.552593&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:4.912e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.573634&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.568722&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.584651Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.584156Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.588424Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.587963Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0965e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.589497&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.578532&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.174e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.599881&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.594707&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.610903Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.610643Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.616104Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.615572Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2381e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.617177&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.604796&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.036e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.627326&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.622290&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.638902Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.638422Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.644154Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.643659Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3109e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.645391&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.632282&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.004e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.655469&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.650465&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.667028Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.666488Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.671831Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.671254Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2649e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.673043&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.660394&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.684788Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.684226Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.689332Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.688870Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2289e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.690507&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.678218&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.702944Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.702474Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.708985Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.708442Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4127e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.710172&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.696045&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.095e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.720688&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.715593&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.732275Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.731672Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.737351Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.736843Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2822e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.738504&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.725682&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.750497Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.749858Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.755345Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.754817Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2669e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.756413&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.743744&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.768034Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.767787Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.773472Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.772941Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2787e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.774556&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.761769&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.097e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.784790&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.779693&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a linked list Video Link:
<https://youtu.be/D2vI2DNJGd8?si=9usE4WRYEPSsmoPW>

</div>

<div id="8327b0f1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.796127Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.795865Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.800546Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.800012Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1965e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.801777&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.789812&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.813731Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.813472Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.818053Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.817585Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1869e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.819098&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.807229&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.228e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.829637&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.824409&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Palindrome Linked List

</div>

<div id="c1bf8469" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.841393Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.840918Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.847227Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.846772Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3627e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.848328&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.834701&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/palindrome-linked-list/submissions/1269504641/
def isPalindromeIter(head: ListNode) -> bool:
    """
    Use slow and fast pointers to find the middle of LL.
    Make sure that we reverse the linkedlist as the slow pointer moves.
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.860299Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.859849Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.865097Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.864536Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2496e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.866207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.853711&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:5.312e-3,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.876834&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.871522&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add one: <https://youtu.be/aXQWhbvT3w0?si=VxL8WQhPa15JP7Nl>

</div>

<div id="ec4aa5bd" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.888698Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.888330Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.893054Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.892496Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2098e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.894142&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.882044&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-27T16:47:22.906249Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-27T16:47:22.905865Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-27T16:47:22.911144Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-27T16:47:22.910667Z&quot;}"
papermill="{&quot;duration&quot;:1.2743e-2,&quot;end_time&quot;:&quot;2024-05-27T16:47:22.912225&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-27T16:47:22.899482&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
