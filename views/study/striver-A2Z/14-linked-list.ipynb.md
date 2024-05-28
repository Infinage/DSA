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
    duration: 2.918945
    end_time: "2024-05-28T16:42:56.782264"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-28T16:42:53.863319"
    version: 2.6.0
---

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:8.691e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.008739&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.000048&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.024410Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.023999Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.390213Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.389677Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.375865,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.391721&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.015856&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.028e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.405967&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.398939&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.420916Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.420434Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.425672Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.425235Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3861e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.426688&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.412827&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.072e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.440881&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.433809&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.455947Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.455647Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.460780Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.460357Z&quot;}"
papermill="{&quot;duration&quot;:1.4027e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.461778&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.447751&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.887e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.475627&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.468740&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.490520Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.490058Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.493632Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.493069Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2175e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.494685&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.482510&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.038e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.508797&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.501759&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.523628Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.523386Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.526855Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.526422Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2272e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.527926&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.515654&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.939e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.541981&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.535042&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.557315Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.556797Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.560516Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.559986Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2725e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.561642&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.548917&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.952e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.575696&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.568744&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.590900Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.590408Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.595884Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.595429Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4311e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.596940&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.582629&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.228e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.611377&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.604149&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.626515Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.626073Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.631163Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.630634Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3994e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.632292&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.618298&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.848e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.646159&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.639311&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.661239Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.660812Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.665457Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.665016Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3408e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.666538&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.653130&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.921e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.680404&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.673483&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.695295Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.695010Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.698592Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.698179Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2363e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.699691&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.687328&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.036e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.713803&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.706767&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.728654Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.728254Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.732373Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.731950Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2617e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.733371&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.720754&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.912e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.747274&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.740362&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.762098Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.761709Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.766058Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.765621Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.288e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.767064&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.754184&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.89e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.780936&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.774046&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.795729Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.795540Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.799728Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.799288Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2865e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.800779&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.787914&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.048e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.814937&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.807889&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.830881Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.830405Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.835838Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.835309Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4733e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.836906&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.822173&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.954e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.850861&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.843907&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.866084Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.865608Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.870792Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.870339Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4029e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.871873&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.857844&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.902e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.885831&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.878929&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.916539Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.916041Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.921215Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.920777Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4157e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.922310&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.908153&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.937753Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.937387Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.941913Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.941409Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3475e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.943029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.929554&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.958060Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.957732Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.963549Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.962987Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4497e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.964564&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.950067&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.962e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.978575&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.971613&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:55.993516Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:55.993179Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:55.998672Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:55.998173Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4225e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:55.999787&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:55.985562&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.015260Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.014730Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.020140Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.019664Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4359e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.021209&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.006850&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.036393Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.036051Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.041230Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.040717Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4018e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.042334&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.028316&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.25e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.056833&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.049583&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a linked list Video Link:
<https://youtu.be/D2vI2DNJGd8?si=9usE4WRYEPSsmoPW>

</div>

<div id="8327b0f1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.072091Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.071644Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.076180Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.075651Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.344e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.077259&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.063819&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.092776Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.092407Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.096787Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.096274Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3428e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.097847&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.084419&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.117e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.112159&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.105042&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Palindrome Linked List

</div>

<div id="c1bf8469" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.127411Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.127164Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.133036Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.132577Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4899e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.134100&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.119201&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.149386Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.148982Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.153533Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.153107Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3321e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.154580&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.141259&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.254e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.169019&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.161765&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add one: <https://youtu.be/aXQWhbvT3w0?si=VxL8WQhPa15JP7Nl>

</div>

<div id="ec4aa5bd" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.184011Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.183664Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.187740Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.187221Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2844e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.188808&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.175964&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.203952Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.203628Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.208196Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.207687Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3242e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.209219&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.195977&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.883e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.223128&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.216245&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find intersection point of two linked lists:
<https://leetcode.com/problems/intersection-of-two-linked-lists/> Video
Link: <https://youtu.be/0DYoPz2Tpt4?si=Xb8Vkn3dRvw57Se8>

</div>

<div id="7e7a074f" class="cell markdown"
papermill="{&quot;duration&quot;:6.947e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.237044&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.230097&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Code snippet for generating test cases relevant to this problem

</div>

<div id="df06d967" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.252167Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.251738Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.256367Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.255878Z&quot;}"
papermill="{&quot;duration&quot;:1.3446e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.257414&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.243968&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.272760Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.272345Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.277138Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.276637Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3656e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.278210&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.264554&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.293317Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.292918Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.297256Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.296850Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.305e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.298311&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.285261&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.066e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.312534&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.305468&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Middle of a linked list:
<https://leetcode.com/problems/middle-of-the-linked-list/> Video Link:
<https://youtu.be/7LjQ57RqgEc?si=5CaPgtXPsfwLGqPJ>

</div>

<div id="42d42838" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.328024Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.327561Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.331370Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.330901Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2849e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.332447&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.319598&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.089e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.346767&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.339678&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle

</div>

<div id="a5f83af7" class="cell markdown"
papermill="{&quot;duration&quot;:7.042e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.360937&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.353895&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Function to generate test cases for LL with cycles

</div>

<div id="ccde5409" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.376574Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.376119Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.380609Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.380145Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3619e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.381657&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.368038&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.396891Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.396499Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.400580Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.400073Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2898e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.401677&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.388779&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.051e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.415758&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.408707&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find the length of the LL Video Link:
<https://youtu.be/I4g1qbkTPus?si=GVUwRbb-TQ_Ko7md> Brute force: Store
node and time. When a node is revisited, return curr_time - past_time
for the length

</div>

<div id="c473e001" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.430845Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.430454Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.435245Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.434764Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3587e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.436301&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.422714&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.02e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.450513&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.443493&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete the middle node of a LL:
<https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/>
Video Link: <https://youtu.be/ePpV-_pfOeI?si=CrCPJnN2MA38JYZh>

</div>

<div id="ac21940a" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.465629Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.465250Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.469799Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.469276Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.326e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.470799&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.457539&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.139e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.485125&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.477986&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find starting point of a loop / cycle Video Link:
<https://youtu.be/2Kd0KKmmHFc?si=9XzuefTJpWk7vgEI>

</div>

<div id="4ea0855f" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.500345Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.499888Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.503167Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.502720Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2075e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.504229&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.492154&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.519472Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.519077Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.523895Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.523467Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3578e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.524927&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.511349&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.033e-3,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.539131&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.532098&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete all occurances of key from DLL Video Link:
<https://youtu.be/Mh0NH_SD92k?si=EOHv42dLQgWo2hfo>

</div>

<div id="8afd6d09" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T16:42:56.554384Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T16:42:56.553903Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T16:42:56.558333Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T16:42:56.557783Z&quot;}"
papermill="{&quot;duration&quot;:1.3182e-2,&quot;end_time&quot;:&quot;2024-05-28T16:42:56.559372&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T16:42:56.546190&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
