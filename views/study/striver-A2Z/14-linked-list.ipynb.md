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
    duration: 1.816931
    end_time: "2024-05-25T16:09:03.454394"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-25T16:09:01.637463"
    version: 2.6.0
---

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:2.875e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:02.759262&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:02.756387&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:02.764727Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:02.764293Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.132583Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.131969Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.372879,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.134205&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:02.761326&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.153e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.138521&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.136368&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:03.143586Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:03.143027Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.148429Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.147807Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.302e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.149702&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.140400&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="3bd55ce0" class="cell markdown"
papermill="{&quot;duration&quot;:1.868e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.153690&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.151822&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:03.158866Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:03.158326Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.162123Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.161655Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.529e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.163210&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.155681&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.914e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.167050&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.165136&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:03.172013Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:03.171513Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.174974Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.174544Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.079e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.176029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.168950&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.983e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.180037&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.178054&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:03.185528Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:03.184969Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.188754Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.188207Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.763e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.189863&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.182100&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.953e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.194540&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.192587&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:03.199564Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:03.199072Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.205224Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.204664Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.943e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.206422&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.196479&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.052e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.210471&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.208419&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:03.215472Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:03.215022Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.219931Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.219404Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.105e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.221545&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.212440&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.969e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.226362&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.224393&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-25T16:09:03.231348Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-25T16:09:03.230884Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-25T16:09:03.235480Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-25T16:09:03.235045Z&quot;}"
papermill="{&quot;duration&quot;:8.243e-3,&quot;end_time&quot;:&quot;2024-05-25T16:09:03.236624&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-25T16:09:03.228381&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
