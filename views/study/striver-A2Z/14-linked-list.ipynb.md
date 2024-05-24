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
    duration: 1.824549
    end_time: "2024-05-24T15:47:39.158405"
    environment_variables: {}
    input_path: study/striver-A2Z/14-linked-list.ipynb
    output_path: study/striver-A2Z/14-linked-list.ipynb
    parameters: {}
    start_time: "2024-05-24T15:47:37.333856"
    version: 2.6.0
---

<div id="7bb754d1" class="cell markdown"
papermill="{&quot;duration&quot;:4.487e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.507883&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.503396&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Useful imports

</div>

<div id="9ca3a0e7" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-24T15:47:38.512858Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-24T15:47:38.512587Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-24T15:47:38.894394Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-24T15:47:38.893788Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.386448,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.895997&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.509549&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.41e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.899175&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.897765&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Helper for Singly Linked lists

</div>

<div id="db8c5b93" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-24T15:47:38.903237Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-24T15:47:38.902686Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-24T15:47:38.907544Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-24T15:47:38.907093Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.122e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.908655&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.900533&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.349e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.911399&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.910050&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Convert an array to Linked list

</div>

<div id="59dfeb8f" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-24T15:47:38.915310Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-24T15:47:38.914830Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-24T15:47:38.918413Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-24T15:47:38.917990Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.834e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.919577&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.912743&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.394e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.922394&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.921000&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Length of LL

</div>

<div id="d41e087f" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-24T15:47:38.926418Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-24T15:47:38.925899Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-24T15:47:38.929331Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-24T15:47:38.928855Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:6.617e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.930429&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.923812&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.454e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.933324&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.931870&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Search in a linked list

</div>

<div id="1137b6e9" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-05-24T15:47:38.937406Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-05-24T15:47:38.936858Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-05-24T15:47:38.940368Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-05-24T15:47:38.939918Z&quot;}"
papermill="{&quot;duration&quot;:6.764e-3,&quot;end_time&quot;:&quot;2024-05-24T15:47:38.941552&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-05-24T15:47:38.934788&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
