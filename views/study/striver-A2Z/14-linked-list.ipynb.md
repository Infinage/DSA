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
    duration: 2.779616
    end_time: "2024-05-28T07:43:39.091448"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-28T07:43:36.311832"
    version: 2.6.0
---

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:7.112e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.452153&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.445041&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:37.467230Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:37.466800Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:37.840100Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:37.839558Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.38295,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.841609&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.458659&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.696e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.855424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.848728&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:37.870168Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:37.869448Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:37.875577Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:37.875036Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4707e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.876754&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.862047&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.508e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.890004&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.883496&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:37.904203Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:37.903812Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:37.908403Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:37.907957Z&quot;}"
papermill="{&quot;duration&quot;:1.306e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.909567&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.896507&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.398e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.922439&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.916041&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:37.936718Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:37.936215Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:37.939922Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:37.939484Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2092e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.940993&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.928901&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.469e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.954046&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.947577&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:37.968414Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:37.968017Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:37.971582Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:37.971115Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1956e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.972618&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.960662&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.489e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:37.985670&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.979181&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:37.999778Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:37.999323Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.003261Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.002705Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2181e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.004299&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:37.992118&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.441e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.017325&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.010884&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.031521Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.031057Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.036651Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.036113Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.397e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.037801&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.023831&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.463e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.050740&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.044277&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.064772Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.064291Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.069533Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.069032Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3394e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.070571&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.057177&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.648e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.083851&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.077203&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.097986Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.097442Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.102399Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.101931Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3149e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.103446&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.090297&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.388e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.116409&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.110021&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.130287Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.129991Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.133883Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.133401Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2134e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.135008&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.122874&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.456e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.148059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.141603&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.162445Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.161947Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.166185Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.165621Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2762e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.167358&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.154596&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.466e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.180630&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.174164&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.195022Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.194698Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.199218Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.198675Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3092e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.200366&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.187274&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.445e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.213498&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.207053&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.227444Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.227173Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.231350Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.230921Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2427e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.232385&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.219958&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.348e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.245210&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.238862&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.259194Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.258734Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.263882Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.263419Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3327e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.264943&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.251616&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.423e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.277951&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.271528&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.292064Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.291606Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.296775Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.296302Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3462e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.297892&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.284430&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.675e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.311229&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.304554&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.325347Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.324920Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.329933Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.329445Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3263e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.330971&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.317708&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.362249Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.361786Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.366587Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.366119Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3424e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.367704&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.354280&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.381886Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.381425Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.387219Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.386758Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4055e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.388338&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.374283&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.521e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.401591&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.395070&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.415876Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.415476Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.420565Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.420126Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3646e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.421769&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.408123&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.436434Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.436178Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.441302Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.440842Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3815e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.442428&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.428613&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.456961Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.456495Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.462244Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.461678Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4234e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.463398&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.449164&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.487e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.476596&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.470109&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a linked list Video Link:
<https://youtu.be/D2vI2DNJGd8?si=9usE4WRYEPSsmoPW>

</div>

<div id="8327b0f1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.490825Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.490291Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.494939Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.494388Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3001e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.496129&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.483128&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.510377Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.509963Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.514191Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.513658Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2528e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.515288&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.502760&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.453e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.528363&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.521910&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Palindrome Linked List

</div>

<div id="c1bf8469" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.542890Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.542448Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.548537Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.548123Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4498e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.549650&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.535152&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.563459Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.563287Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.568035Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.567576Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2858e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.569047&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.556189&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.471e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.582121&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.575650&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add one: <https://youtu.be/aXQWhbvT3w0?si=VxL8WQhPa15JP7Nl>

</div>

<div id="ec4aa5bd" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.596222Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.595995Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.600173Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.599715Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2394e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.601207&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.588813&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.615167Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.614787Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.619506Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.619059Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2743e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.620514&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.607771&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.484e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.633663&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.627179&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find intersection point of two linked lists:
<https://leetcode.com/problems/intersection-of-two-linked-lists/> Video
Link: <https://youtu.be/0DYoPz2Tpt4?si=Xb8Vkn3dRvw57Se8>

</div>

<div id="7e7a074f" class="cell markdown"
papermill="{&quot;duration&quot;:6.585e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.646831&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.640246&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Code snippet for generating test cases relevant to this problem

</div>

<div id="df06d967" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.661101Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.660720Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.665538Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.665057Z&quot;}"
papermill="{&quot;duration&quot;:1.3311e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.666612&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.653301&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.680841Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.680386Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.685318Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.684793Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3152e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.686369&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.673217&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.700338Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.700016Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.704441Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.704013Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2602e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.705505&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.692903&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.471e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.718530&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.712059&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Middle of a linked list:
<https://leetcode.com/problems/middle-of-the-linked-list/> Video Link:
<https://youtu.be/7LjQ57RqgEc?si=5CaPgtXPsfwLGqPJ>

</div>

<div id="42d42838" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.732893Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.732392Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.736430Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.735930Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.244e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.737522&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.725082&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.638e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.750850&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.744212&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle

</div>

<div id="a5f83af7" class="cell markdown"
papermill="{&quot;duration&quot;:6.543e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.763925&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.757382&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Function to generate test cases for LL with cycles

</div>

<div id="ccde5409" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.778533Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.778041Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.782630Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.782090Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3178e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.783706&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.770528&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.798293Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.797876Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.801914Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.801433Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2425e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.802958&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.790533&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.618e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.816366&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.809748&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find the length of the LL Video Link:
<https://youtu.be/I4g1qbkTPus?si=GVUwRbb-TQ_Ko7md> Brute force: Store
node and time. When a node is revisited, return curr_time - past_time
for the length

</div>

<div id="c473e001" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.830551Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.830364Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.834707Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.834254Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2713e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.835790&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.823077&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:6.581e-3,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.849257&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.842676&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete the middle node of a LL:
<https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/>
Video Link: <https://youtu.be/ePpV-_pfOeI?si=CrCPJnN2MA38JYZh>

</div>

<div id="ac21940a" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-28T07:43:38.864067Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-28T07:43:38.863603Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-28T07:43:38.868078Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-28T07:43:38.867611Z&quot;}"
papermill="{&quot;duration&quot;:1.3105e-2,&quot;end_time&quot;:&quot;2024-05-28T07:43:38.869151&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-28T07:43:38.856046&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
