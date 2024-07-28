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
    duration: 1.360082
    end_time: "2024-07-28T15:14:57.497046"
    environment_variables: {}
    input_path: study/striver-A2Z/19-range-query-DS.ipynb
    output_path: study/striver-A2Z/19-range-query-DS.ipynb
    parameters: {}
    start_time: "2024-07-28T15:14:56.136964"
    version: 2.6.0
---

<div id="127194e9" class="cell markdown"
papermill="{&quot;duration&quot;:2.947e-3,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.298087&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.295140&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Segment Trees: <https://www.youtube.com/watch?v=NEG-SoyigGE&t=2s>

Segment trees have a build time of O(N) and can get query results in
O(log N) time.

</div>

<div id="8fc69bda" class="cell markdown"
papermill="{&quot;duration&quot;:1.482e-3,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.301334&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.299852&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Import necessary packages

</div>

<div id="e6216c04" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-28T15:14:57.305479Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-28T15:14:57.305125Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-28T15:14:57.311551Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-28T15:14:57.311020Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.863e-3,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.312667&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.302804&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import random
import collections
import functools
import bisect
import heapq
import typing
import math
```

</div>

<div id="99cdcc6c" class="cell markdown"
papermill="{&quot;duration&quot;:1.53e-3,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.315670&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.314140&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Leetcode Problem:
<https://leetcode.com/problems/range-sum-query-mutable/>

</div>

<div id="c4146656" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-28T15:14:57.319712Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-28T15:14:57.319274Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-28T15:14:57.329262Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-28T15:14:57.328740Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3371e-2,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.330514&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.317143&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class RangeSumQuery:
    def __init__(self, nums: list[int]):
        self.nums = nums
        self.N = len(nums)
        self.segment_tree = [0 for i in range(4 * self.N)]
        self.build_segment_tree(0, self.N - 1, 0)

    def build_segment_tree(self, low: int, high: int, idx: int) -> None:
        if low == high:
            self.segment_tree[idx] = self.nums[low]
        else:
            mid = (low + high) // 2
            left_idx, right_idx = 2 * idx + 1, 2 * idx + 2
            self.build_segment_tree(low, mid, left_idx)
            self.build_segment_tree(mid + 1, high, right_idx)
            self.segment_tree[idx] = self.segment_tree[left_idx] + self.segment_tree[right_idx]

    def update_segment_tree(self, low: int, high: int, segment_idx: int, num_idx: int, val: int) -> None:
        if low == high:
            self.segment_tree[segment_idx] = val
        else:
            mid = (low + high) // 2
            left_idx, right_idx = 2 * segment_idx + 1, 2 * segment_idx + 2
            if num_idx <= mid:
                self.update_segment_tree(low, mid, left_idx, num_idx, val)
            else:
                self.update_segment_tree(mid + 1, high, right_idx, num_idx, val)
            self.segment_tree[segment_idx] = self.segment_tree[left_idx] + self.segment_tree[right_idx]

    def update(self, index: int, val: int) -> None:
        self.nums[index] = val
        self.update_segment_tree(0, self.N - 1, 0, index, val)

    def range_query(self, low: int, high: int, idx: int, left: int, right: int) -> int:
        """
        Case 1: Full overlap => Return seg[idx]
        Case 2: No overlap => Return 0
        Case 3: Partial overlap => sum of range_query on left and right subtree
        """
        if left <= low <= high <= right:
            return self.segment_tree[idx]
        elif right < low or high < left:
            return 0
        else:
            mid = (low + high) // 2
            left_idx, right_idx = 2 * idx + 1, 2 * idx + 2
            left_sum = self.range_query(low, mid, left_idx, left, right)
            right_sum = self.range_query(mid + 1, high, right_idx, left, right)
            return left_sum + right_sum

    def sumRange(self, left: int, right: int) -> int:
        return int(self.range_query(0, self.N - 1, 0, left, right))

# Testing the solution
# Test 1
RSQ = RangeSumQuery([1,3,5])
assert RSQ.sumRange(0, 2) == 9
RSQ.update(1, 2)
assert RSQ.sumRange(0, 2) == 8

# Test 2
RSQ = RangeSumQuery([9,-8])
RSQ.update(0, 3)
assert RSQ.sumRange(1, 1) == -8
assert RSQ.sumRange(0, 1) == -5
RSQ.update(1, -3)
assert RSQ.sumRange(0, 1) == 0
```

</div>

<div id="f24409ee" class="cell markdown"
papermill="{&quot;duration&quot;:1.471e-3,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.333502&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.332031&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Xenia & Bit Operations

</div>

<div id="968aa630" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-28T15:14:57.337423Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-28T15:14:57.337096Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-28T15:14:57.345185Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-28T15:14:57.344759Z&quot;}"
papermill="{&quot;duration&quot;:1.1172e-2,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.346226&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.335054&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class XeniaArray:
    def __init__(self, N: int, nums: list[int]) -> None:
        self.N = 2 ** N
        self.nums = nums
        self.segment_tree: list[int] = [1 for i in range(4 * self.N)]
        self.build(0, self.N - 1, 0)

    def build(self, low: int, high: int, idx: int) -> bool:
        if low == high:
            self.segment_tree[idx] = self.nums[low]
            return True
        else:
            mid = (low + high) // 2
            left_idx, right_idx = 2 * idx + 1, 2 * idx + 2
            op = self.build(low, mid, left_idx)
            op = self.build(mid + 1, high, right_idx)
            self.segment_tree[idx] = (self.segment_tree[left_idx] | self.segment_tree[right_idx]) if op else (self.segment_tree[left_idx] ^ self.segment_tree[right_idx])
            return not op

    def update_and_query(self, idx: int, val: int) -> int:
        self.update(0, self.N - 1, 0, idx - 1, val)
        return self.segment_tree[0]

    def update(self, low: int, high: int, segment_idx: int, num_idx: int, val: int) -> bool:
        if low == high:
            self.segment_tree[segment_idx] = val
            self.nums[num_idx] = val
            return True
        else:
            mid = (low + high) // 2
            left_idx, right_idx = 2 * segment_idx + 1, 2 * segment_idx + 2
            op: bool
            if num_idx <= mid:
                op = self.update(low, mid, left_idx, num_idx, val)
            else:
                op = self.update(mid + 1, high, right_idx, num_idx, val)
            self.segment_tree[segment_idx] = (self.segment_tree[left_idx] | self.segment_tree[right_idx]) if op else (self.segment_tree[left_idx] ^ self.segment_tree[right_idx])
            return not op

# Testing the solution
xa = XeniaArray(2, [1,6,3,5])
assert [xa.update_and_query(1,4), xa.update_and_query(3,4), xa.update_and_query(1,2), xa.update_and_query(1,2)] == [1,3,3,3]
```

</div>

<div id="1e17895d" class="cell markdown"
papermill="{&quot;duration&quot;:1.549e-3,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.349350&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.347801&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sereja & Brackets

</div>

<div id="70243b1d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-28T15:14:57.354342Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-28T15:14:57.354004Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-28T15:14:57.362672Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-28T15:14:57.362211Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1948e-2,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.363712&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.351764&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
SBTuple = collections.namedtuple("SBTuple", ['size', 'open', 'close'])

class SerejaBrackets:
    def __init__(self, brackets: str) -> None:
        self.N = len(brackets)
        self.brackets: str = brackets
        self.segment_tree: list[SBTuple] = [SBTuple(0, 0, 0) for i in range(4 * self.N)]
        self.build(0, self.N - 1, 0)

    def build(self, low: int, high: int, idx: int) -> SBTuple:
        if low == high:
            self.segment_tree[idx] = SBTuple(0, 0, 1) if self.brackets[low] == ')' else SBTuple(0, 1, 0)
        else:
            mid = (low + high) // 2
            left_idx, right_idx = 2 * idx + 1, 2 * idx + 2
            left_tuple = self.build(low, mid, left_idx)
            right_tuple = self.build(mid + 1, high, right_idx)
            match = min(left_tuple.open, right_tuple.close)
            self.segment_tree[idx] = SBTuple(left_tuple.size + right_tuple.size + 2 * match, left_tuple.open + right_tuple.open - match, left_tuple.close + right_tuple.close - match)
        return self.segment_tree[idx]

    def query(self, low: int, high: int, idx: int, L: int, R: int) -> SBTuple:
        # Complete overlap
        if L <= low <= high <= R:
            return self.segment_tree[idx]
        # No overlap
        elif high < L or R < low:
            return SBTuple(0, 0, 0)
        else:
            mid = (low + high) // 2
            left_idx, right_idx = 2 * idx + 1, 2 * idx + 2
            left_tuple = self.query(low, mid, left_idx, L, R)
            right_tuple = self.query(mid + 1, high, right_idx, L, R)
            match = min(left_tuple.open, right_tuple.close)
            return SBTuple(left_tuple.size + right_tuple.size + 2 * match, left_tuple.open + right_tuple.open - match, left_tuple.close + right_tuple.close - match)

    def process_query(self, L: int, R: int) -> int:
        return self.query(0, self.N - 1, 0, L - 1, R - 1).size

# Testing the solution
sb = SerejaBrackets("())(())(())()")
assert [sb.process_query(1,1), sb.process_query(2,3), sb.process_query(1,2), sb.process_query(1,12), sb.process_query(8,12), sb.process_query(5,11), sb.process_query(2,10)] == [0, 0, 2, 10, 4, 6, 6]
```

</div>

<div id="c520ca5c" class="cell markdown"
papermill="{&quot;duration&quot;:1.543e-3,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.366786&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.365243&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Count Inverions

</div>

<div id="49795567" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-28T15:14:57.371005Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-28T15:14:57.370497Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-28T15:14:57.379402Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-28T15:14:57.378884Z&quot;}"
papermill="{&quot;duration&quot;:1.2148e-2,&quot;end_time&quot;:&quot;2024-07-28T15:14:57.380496&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-28T15:14:57.368348&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class InversionCount:
    def __init__(self, nums: list[int]) -> None:
        self.N = max(nums) + 1
        self.freq: list[int] = [0 for i in range(self.N)]
        for n in nums:
            self.freq[n] += 1
        self.segment_tree: list[int] = [0 for i in range(4 * self.N)]
        self.build(0, self.N - 1, 0)

    def build(self, low: int, high: int, idx: int) -> None:
        if low == high:
            self.segment_tree[idx] = self.freq[low]
        else:
            mid, left_idx, right_idx = (low + high) // 2, 2 * idx + 1, 2 * idx + 2
            self.build(low, mid, left_idx)
            self.build(mid + 1, high, right_idx)
            self.segment_tree[idx] = self.segment_tree[left_idx] + self.segment_tree[right_idx]

    def update(self, low: int, high: int, segment_idx: int, num_idx: int, val: int) -> None:
        if low == high:
            self.freq[num_idx] = val
            self.segment_tree[segment_idx] = val
        else:
            mid, left_idx, right_idx = (low + high) // 2, 2 * segment_idx + 1, 2 * segment_idx + 2
            if num_idx <= mid:
                self.update(low, mid, left_idx, num_idx, val)
            else:
                self.update(mid + 1, high, right_idx, num_idx, val)
            self.segment_tree[segment_idx] = self.segment_tree[left_idx] + self.segment_tree[right_idx]

    def query(self, low: int, high: int, idx: int, left: int, right: int) -> int:
        if left <= low <= high <= right:
            return self.segment_tree[idx]
        elif high < left or right < low:
            return 0
        else:
            mid, left_idx, right_idx = (low + high) // 2, 2 * idx + 1, 2 * idx + 2
            return self.query(low, mid, left_idx, left, right) + self.query(mid + 1, high, right_idx, left, right)

def countInverions(arr: list[int], N: int) -> int:
    ia = InversionCount(arr)
    counts = 0
    for n in arr:
        freq = ia.freq[n]
        ia.update(0, ia.N - 1, 0, n, freq - 1)
        counts += ia.query(0, ia.N - 1, 0, 0, n - 1)
    return counts

# Testing the solution
assert countInverions([2,5,1,3,4], 5) == 4
```

</div>
