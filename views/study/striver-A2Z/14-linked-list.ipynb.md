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
    duration: 4.174794
    end_time: "2024-05-31T17:28:18.086017"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-31T17:28:13.911223"
    version: 2.6.0
---

<div id="05899396" class="cell markdown"
papermill="{&quot;duration&quot;:1.1541e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.091543&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.080002&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.706e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.111105&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.101399&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.131906Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.131448Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.507305Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.506683Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.388169,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.508861&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.120692&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.827e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.528970&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.519143&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.550488Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.549899Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.557075Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.556619Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.9023e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.558153&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.539130&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.584e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.577797&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.568213&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Doubly Linked lists

</div>

<div id="7d9ad38e" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.600217Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.599695Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.606037Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.605579Z&quot;}"
papermill="{&quot;duration&quot;:1.88e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.607216&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.588416&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.635e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.626782&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.617147&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.647920Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.647411Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.651184Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.650625Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5649e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.652277&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.636628&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.735e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.671898&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.662163&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.692862Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.692260Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.696233Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.695702Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5859e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.697462&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.681603&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.625e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.717185&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.707560&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.738035Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.737552Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.741438Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.740875Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.557e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.742477&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.726907&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.831e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.762448&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.752617&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete a node from linked list
<https://www.geeksforgeeks.org/problems/delete-a-node-in-single-linked-list/1>

</div>

<div id="5bd512fc" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.783037Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.782729Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.788254Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.787700Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7151e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.789299&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.772148&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.593e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.808721&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.799128&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete node by value

</div>

<div id="420f38cf" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.830413Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.829780Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.835195Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.834710Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7743e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.836276&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.818533&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.988e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.856320&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.846332&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a linked list

</div>

<div id="9de3ec91" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.879226Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.878766Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.883833Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.883206Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8007e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.885031&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.867024&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.057e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.906280&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.895710&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Doubly Linked List

Construct doubly linked list from array

</div>

<div id="1d2d3de2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.928368Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.927925Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.931972Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.931417Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6024e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.933063&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.917039&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.917e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.952953&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.943036&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Inserting into a Doubly linked list

</div>

<div id="eeae0793" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:15.973869Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:15.973370Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:15.977500Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:15.977070Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.589e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.978556&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.962666&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.911e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:15.998571&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:15.988660&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Deleting from a doubly linked list

    Easier way still would be to write all edge cases specifically
    If curr is null (and prev, next are null), we have no nodes to delete
    If prev and next is null, we have only 1 node to delete
    If prev is null, we are to delete the head node
    If next is null, we are to delete the tail node

</div>

<div id="5e1cf229" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.019499Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.019005Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.023576Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.023111Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6347e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.024627&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.008280&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.685e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.044229&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.034544&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a DLL Video Link:
<https://youtu.be/u3WUW2qe6ww?si=80DlW_QGoHKnBDjY>

</div>

<div id="aac2ae31" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.064995Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.064505Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.069035Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.068579Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6166e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.070047&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.053881&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.716e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.089783&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.080067&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add two numbers Video Link:
<https://youtu.be/XmRrGzR6udg?si=0Wc8Sp_7v8a_2kPp>

</div>

<div id="2a271620" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.128833Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.128306Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.133539Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.133019Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7282e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.134732&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.117450&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.833e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.154705&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.144872&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Odd Even Linked List:
<https://leetcode.com/problems/odd-even-linked-list/description/> Video
Link: <https://youtu.be/qf6qp7GzD5Q?si=f0kxJQ7bJ8JSSZGe>

</div>

<div id="ed28b236" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.176030Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.175482Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.180934Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.180383Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7466e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.182066&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.164600&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.668e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.201707&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.192039&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sorted linked list of 0s, 1s, 2s

</div>

<div id="283f2b99" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.222411Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.221925Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.227181Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.226681Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6883e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.228264&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.211381&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.249691Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.249176Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.254110Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.253659Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6814e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.255213&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.238399&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.276187Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.275657Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.281696Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.281260Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7685e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.282701&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.265016&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.688e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.302343&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.292655&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.323438Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.322957Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.328335Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.327871Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7218e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.329407&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.312189&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.350616Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.350065Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.355434Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.354997Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7068e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.356475&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.339407&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.377668Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.377202Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.382706Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.382146Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.736e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.383826&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.366466&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.591e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.403278&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.393687&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse a linked list Video Link:
<https://youtu.be/D2vI2DNJGd8?si=9usE4WRYEPSsmoPW>

</div>

<div id="8327b0f1" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.424002Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.423503Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.428163Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.427627Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6273e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.429204&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.412931&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.450320Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.450048Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.454625Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.454160Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6598e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.455763&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.439165&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0979e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.477372&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.466393&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Palindrome Linked List

</div>

<div id="c1bf8469" class="cell code" execution_count="24"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.498727Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.498233Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.504633Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.504168Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8229e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.505693&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.487464&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.526949Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.526506Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.531607Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.531042Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7015e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.532756&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.515741&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.631e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.552399&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.542768&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Add one: <https://youtu.be/aXQWhbvT3w0?si=VxL8WQhPa15JP7Nl>

</div>

<div id="ec4aa5bd" class="cell code" execution_count="26"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.573076Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.572632Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.576961Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.576506Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5927e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.577990&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.562063&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.599234Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.598713Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.603489Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.602990Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6536e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.604554&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.588018&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.79e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.624280&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.614490&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find intersection point of two linked lists:
<https://leetcode.com/problems/intersection-of-two-linked-lists/> Video
Link: <https://youtu.be/0DYoPz2Tpt4?si=Xb8Vkn3dRvw57Se8>

</div>

<div id="7e7a074f" class="cell markdown"
papermill="{&quot;duration&quot;:9.817e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.643924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.634107&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Code snippet for generating test cases relevant to this problem

</div>

<div id="df06d967" class="cell code" execution_count="28"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.664977Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.664488Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.669299Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.668862Z&quot;}"
papermill="{&quot;duration&quot;:1.6673e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.670365&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.653692&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.691560Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.691051Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.696204Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.695678Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7065e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.697377&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.680312&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.719801Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.719256Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.724828Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.724169Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.801e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.726012&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.708002&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0027e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.746417&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.736390&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Middle of a linked list:
<https://leetcode.com/problems/middle-of-the-linked-list/> Video Link:
<https://youtu.be/7LjQ57RqgEc?si=5CaPgtXPsfwLGqPJ>

</div>

<div id="42d42838" class="cell code" execution_count="31"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.768340Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.767938Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.772227Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.771755Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6614e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.773328&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.756714&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.0143e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.793983&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.783840&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Detect cycle

</div>

<div id="a5f83af7" class="cell markdown"
papermill="{&quot;duration&quot;:1.0128e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.814272&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.804144&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Function to generate test cases for LL with cycles

</div>

<div id="ccde5409" class="cell code" execution_count="32"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.837464Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.837023Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.841559Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.841095Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7871e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.842636&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.824765&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.863646Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.863261Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.867589Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.867076Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6255e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.868646&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.852391&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.703e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.888216&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.878513&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find the length of the LL Video Link:
<https://youtu.be/I4g1qbkTPus?si=GVUwRbb-TQ_Ko7md> Brute force: Store
node and time. When a node is revisited, return curr_time - past_time
for the length

</div>

<div id="c473e001" class="cell code" execution_count="34"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.909085Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.908584Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.913333Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.912822Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6561e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.914489&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.897928&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.711e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.934069&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.924358&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete the middle node of a LL:
<https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/>
Video Link: <https://youtu.be/ePpV-_pfOeI?si=CrCPJnN2MA38JYZh>

</div>

<div id="ac21940a" class="cell code" execution_count="35"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:16.955319Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:16.954774Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:16.959492Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:16.958965Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6718e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.960637&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.943919&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.858e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:16.980536&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.970678&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find starting point of a loop / cycle Video Link:
<https://youtu.be/2Kd0KKmmHFc?si=9XzuefTJpWk7vgEI>

</div>

<div id="4ea0855f" class="cell code" execution_count="36"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.001628Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.001128Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.004833Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.004263Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5691e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.006012&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:16.990321&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.028152Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.027554Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.033470Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.032895Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8729e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.034770&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.016041&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.841e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.055047&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.045206&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Delete all occurances of key from DLL Video Link:
<https://youtu.be/Mh0NH_SD92k?si=EOHv42dLQgWo2hfo>

</div>

<div id="8afd6d09" class="cell code" execution_count="38"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.076242Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.075828Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.080569Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.080117Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6792e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.081726&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.064934&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.893e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.101682&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.091789&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Find all pairs that sum to pair Video Link:
<https://youtu.be/YitR4dQsddE?si=hKS4D96sIRLllVkU>

</div>

<div id="db9ee204" class="cell code" execution_count="39"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.122749Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.122219Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.127416Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.126945Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6998e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.128482&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.111484&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.78e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.148355&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.138575&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Remove duplicates from sorted DLL Video Link:
<https://youtu.be/YJKVTnOJXSY?si=iUsYyLyw32khR4qk>

</div>

<div id="96d1a14c" class="cell code" execution_count="40"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.169199Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.168816Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.172975Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.172514Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5961e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.174029&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.158068&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.844e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.194407&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.184563&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Reverse nodes in K group Video Link:
<https://youtu.be/lIar1skcQYI?si=iMT4yb5RPdSAKTGz>

</div>

<div id="a9d91617" class="cell code" execution_count="41"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.215495Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.214944Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.220981Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.220437Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7979e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.222122&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.204143&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.798e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.241945&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.232147&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Rotate Linked List: <https://leetcode.com/problems/rotate-list/> Video
Link: <https://youtu.be/uT7YI7XbTY8?si=oTcsMXbd4Ukx7peu>

</div>

<div id="21fcd05a" class="cell code" execution_count="42"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.262933Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.262400Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.267611Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.267043Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6971e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.268712&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.251741&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.73e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.288446&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.278716&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Merge Two sorted linked lists:
<https://leetcode.com/problems/merge-two-sorted-lists/> Video Link:
<https://youtu.be/jXu-H7XuClE?si=cAYJXOGmugB-R1Jw>

</div>

<div id="9bda15a0" class="cell code" execution_count="43"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.309420Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.308888Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.313930Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.313483Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6816e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.315004&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.298188&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.726e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.334716&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.324990&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Flattening a linked list Video Link:
<https://youtu.be/ykelywHJWLg?si=xEMHwY-n0wADGYA6>

</div>

<div id="8e34e33f" class="cell code" execution_count="44"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.356038Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.355489Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.359874Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.359337Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6454e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.360947&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.344493&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.382248Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.381703Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.390294Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.389744Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0334e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.391445&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.371111&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.413252Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.412760Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.418578Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.418135Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7913e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.419698&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.401785&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.441522Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.441093Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.447847Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.447292Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8885e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.448924&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.430039&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:9.97e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.469157&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.459187&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Merge K sorted Lists:
<https://leetcode.com/problems/merge-k-sorted-lists/> Video Link:
<https://youtu.be/1zktEppsdig?si=o9ttliAfO99YDin8>

</div>

<div id="0c98d074" class="cell code" execution_count="48"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.490539Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.490090Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.495478Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.495036Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7393e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.496550&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.479157&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.517599Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.517204Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.522667Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.522144Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7318e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.523870&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.506552&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="77ed623c" class="cell markdown"
papermill="{&quot;duration&quot;:1.0337e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.544435&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.534098&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sort a linked List: <https://leetcode.com/problems/sort-list/> Video
Link: <https://youtu.be/8ocB7a_c-Cc?si=JfJceeGOqxqhlaV0>

</div>

<div id="055682d7" class="cell code" execution_count="50"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.566077Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.565578Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.572920Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.572225Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:2.0389e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.574749&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.554360&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/sort-list/submissions/1272831788/
def sortList(head: ListNode, end: ListNode) -> ListNode:
    """
    Time: O(N log N), Space: O(log N)
    """
    # If len <= 1
    if not head or not head.next:
        return head

    else:
        # Find the middle node for split
        prev, slow, fast = None, head, head
        while fast and fast.next:
            prev, slow, fast = slow, slow.next, fast.next.next

        prev.next = None # type: ignore

        # Sort left, right
        left = sortList(head, None) # type: ignore
        right = sortList(slow, end)

        # Merge left and right
        merged: ListNode = ListNode(-1)
        mh, curr1, curr2 = merged, left, right
        while curr1 or curr2:
            if not curr2 or (curr1 and curr1.val < curr2.val):
                mh.next = curr1
                mh, curr1 = mh.next, curr1.next
            else:
                mh.next = curr2
                mh, curr2 = mh.next, curr2.next

        # Skip dummy head
        return merged.next

# Testing the solution
assert sortList(ListNode.to_singly_linked_list([1,3,4,1,2,3,8,5]), None).to_list() == [1,1,2,3,3,4,5,8] # type: ignore
assert sortList(ListNode.to_singly_linked_list([3,1,2]), None).to_list() == [1,2,3] # type: ignore
assert sortList(ListNode.to_singly_linked_list([3,1]), None).to_list() == [1,3] # type: ignore
assert sortList(ListNode.to_singly_linked_list([3]), None).to_list() == [3] # type: ignore
```

</div>

<div id="de4a441d" class="cell markdown"
papermill="{&quot;duration&quot;:1.2974e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.601898&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.588924&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Copy list with random pointer Video Link:
<https://youtu.be/q570bKdrnlw?si=psXR0pw8TtHK_wu_>

</div>

<div id="089d0d42" class="cell code" execution_count="51"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.623262Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.622987Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.629713Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.629195Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.8834e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.630877&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.612043&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class RandomPointerLLNode:
    def __init__(self, val: int, next_ = None, random = None):
        self.val = val
        self.next = next_
        self.random = random

    @staticmethod
    def to_random_pointer_ll(arr: list[tuple[int, int|None]]) -> 'RandomPointerLLNode|None':
        # Compute total length
        N = len(arr)

        # Create nodes for linkage
        nodes: list['RandomPointerLLNode'] = [RandomPointerLLNode(arr[i][0]) for i in range(N)]

        # Set the pointers
        for i, (_, rand_idx) in enumerate(arr):
            nodes[i].next = nodes[i + 1] if i + 1 < N else None
            if rand_idx is not None:
                nodes[i].random = nodes[rand_idx]

        return nodes[0] if nodes else None

    def to_list(self) -> list[tuple[int, int|None]]:
        # Store the results
        result: list[tuple[int, int|None]] = []

        # Create a dictionary of nodes-indices pairs
        i, curr = 0, self
        nodes_dict: dict['RandomPointerLLNode', int] = {}
        while curr:
            nodes_dict[curr] = i
            i, curr = i + 1, curr.next

        # Store the results
        curr = self
        while curr:
            result.append((curr.val, curr.random and nodes_dict[curr.random]))
            curr = curr.next

        return result

# Testing the Random LL Node code
assert RandomPointerLLNode.to_random_pointer_ll([(7,None),(13,0),(11,4),(10,2),(1,0)]).to_list() == [(7,None),(13,0),(11,4),(10,2),(1,0)]
```

</div>

<div id="feef787a" class="cell code" execution_count="52"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.652319Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.651814Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.656764Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.656240Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.693e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.657917&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.640987&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/copy-list-with-random-pointer/submissions/1273432189
def copyRandomList(head: RandomPointerLLNode|None) ->  RandomPointerLLNode|None:
    """
    Time: O(N), Space: O(N)
    """
    node_mapping: dict[RandomPointerLLNode, RandomPointerLLNode] = dict()
    def clone(curr: RandomPointerLLNode|None):
        if not curr:
            return curr
        elif curr in node_mapping:
            return node_mapping[curr]
        else:
            node = RandomPointerLLNode(curr.val)
            node_mapping[curr] = node
            node.next = clone(curr.next)
            node.random = clone(curr.random)
            return node

    return clone(head)

# Testing the solution
assert copyRandomList(RandomPointerLLNode.to_random_pointer_ll([(7,None),(13,0),(11,4),(10,2),(1,0)])).to_list() == [(7,None),(13,0),(11,4),(10,2),(1,0)]
```

</div>

<div id="83e57137" class="cell code" execution_count="53"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.679451Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.679003Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.684061Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.683541Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6941e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.685115&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.668174&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/copy-list-with-random-pointer/submissions/1273461946/
def copyRandomListStriver(head: RandomPointerLLNode|None) ->  RandomPointerLLNode|None:
    """
    1. Insert nodes in between.
    2. Connect the random pointers.
    3. Connect the next pointers.

    Time: O(N), Space: O(1) (ignoring the extra space to return output)
    """

    # Insert nodes in between
    curr = head
    while curr:
        node = RandomPointerLLNode(curr.val)
        next_ = curr.next
        curr.next, node.next = node, next_
        curr = curr.next.next

    # Connect the random pointers
    curr = head
    while curr:
        curr.next.random = curr.random and curr.random.next
        curr = curr.next.next

    # Connect the next pointers
    curr = head
    while curr and curr.next.next:
        next_old = curr.next.next
        curr.next.next = next_old.next
        curr = next_old

    return head and head.next

# Testing the solution
assert copyRandomListStriver(RandomPointerLLNode.to_random_pointer_ll([(7,None),(13,0),(11,4),(10,2),(1,0)])).to_list() == [(7,None),(13,0),(11,4),(10,2),(1,0)]
```

</div>

<div id="bcb1cd09" class="cell markdown"
papermill="{&quot;duration&quot;:9.978e-3,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.705337&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.695359&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Design browser history:
<https://leetcode.com/problems/design-browser-history/description/>
Video Link: <https://youtu.be/mG3KLugbOdc?si=qZFXTEnbaYpgkD93>

</div>

<div id="d4b50d7b" class="cell code" execution_count="54"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.726476Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.726045Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.729383Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.728878Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5129e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.730404&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.715275&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class BrowserHistoryNode:
    def __init__(self, url: str, prev = None, next_ = None):
        self.url = url
        self.next = next_
        self.prev = prev
```

</div>

<div id="332b79a0" class="cell code" execution_count="55"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-31T17:28:17.751627Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-31T17:28:17.751369Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-31T17:28:17.757822Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-31T17:28:17.757381Z&quot;}"
papermill="{&quot;duration&quot;:1.847e-2,&quot;end_time&quot;:&quot;2024-05-31T17:28:17.758956&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-31T17:28:17.740486&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/design-browser-history/submissions/1273489626/
class BrowserHistory:

    def __init__(self, homepage: str):
        self.dll = BrowserHistoryNode(homepage)
        self.curr = self.dll

    @staticmethod
    def clear(head: BrowserHistoryNode) -> None:
        curr = head
        while curr:
            next_ = curr.next
            curr.prev = curr.next = None
            curr = next_

    def visit(self, url: str) -> None:
        node = BrowserHistoryNode(url)
        BrowserHistory.clear(self.curr.next)
        self.curr.next, node.prev = node, self.curr
        self.curr = self.curr.next

    def back(self, steps: int) -> str:
        while steps > 0 and self.curr.prev:
            steps, self.curr = steps - 1, self.curr.prev
        return self.curr.url

    def forward(self, steps: int) -> str:
        while steps > 0 and self.curr.next:
            steps, self.curr = steps - 1, self.curr.next
        return self.curr.url

# Testing the solution
bh = BrowserHistory("leetcode.com")
bh.visit("google.com")
bh.visit("facebook.com")
bh.visit("youtube.com")
assert bh.back(1) == "facebook.com"
assert bh.back(1) == "google.com"
assert bh.forward(1) == "facebook.com"
bh.visit("linkedin.com")
assert bh.forward(2) == "linkedin.com"
assert bh.back(2) == "google.com"
assert bh.back(7) == "leetcode.com"
```

</div>
