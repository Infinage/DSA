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
    duration: 1.38951
    end_time: "2024-07-29T03:10:56.005403"
    environment_variables: {}
    input_path: study/striver-A2Z/19-range-query-DS.ipynb
    output_path: study/striver-A2Z/19-range-query-DS.ipynb
    parameters: {}
    start_time: "2024-07-29T03:10:54.615893"
    version: 2.6.0
---

<div id="127194e9" class="cell markdown"
papermill="{&quot;duration&quot;:2.747e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.750676&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.747929&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

### Segment Trees: <https://www.youtube.com/watch?v=NEG-SoyigGE&t=2s>

Segment trees have a build time of O(N) and can get query results in
O(log N) time.

</div>

<div id="8fc69bda" class="cell markdown"
papermill="{&quot;duration&quot;:2.025e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.754936&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.752911&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Import necessary packages

</div>

<div id="e6216c04" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-29T03:10:55.760539Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-29T03:10:55.760125Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-29T03:10:55.766767Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-29T03:10:55.766309Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0893e-2,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.767865&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.756972&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.938e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.771872&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.769934&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Leetcode Problem:
<https://leetcode.com/problems/range-sum-query-mutable/>

</div>

<div id="c4146656" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-29T03:10:55.777090Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-29T03:10:55.776580Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-29T03:10:55.786732Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-29T03:10:55.786318Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3962e-2,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.787824&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.773862&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.041e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.791945&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.789904&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Xenia & Bit Operations

</div>

<div id="968aa630" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-29T03:10:55.797161Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-29T03:10:55.796651Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-29T03:10:55.805223Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-29T03:10:55.804657Z&quot;}"
papermill="{&quot;duration&quot;:1.233e-2,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.806282&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.793952&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.973e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.810275&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.808302&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Sereja & Brackets

</div>

<div id="70243b1d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-29T03:10:55.816155Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-29T03:10:55.815716Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-29T03:10:55.824653Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-29T03:10:55.824216Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2706e-2,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.825741&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.813035&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:1.988e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.829765&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.827777&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Count Inverions

</div>

<div id="49795567" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-29T03:10:55.834911Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-29T03:10:55.834498Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-29T03:10:55.843578Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-29T03:10:55.843045Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2886e-2,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.844636&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.831750&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="7e7822d0" class="cell markdown"
papermill="{&quot;duration&quot;:1.937e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.848612&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.846675&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Range Query DS - 2 Video Link:
<https://www.youtube.com/watch?v=rXnXRU8yMF0&t=5s> Lazy propagation in
Segment trees: Instead of being given point updates, what if we are
given range updates?

1.  For every node in the corresponding segment tree, create a lazy node
    to store impending updates.
2.  For every update operation, if there are previous impending updates
    update node and propagate to children
3.  Check:
    - No overlap: return
    - Full overlap: update node (+val \* count of nodes responsible),
      lazy propagate to children (iff exists)
    - Partial overlap: Update left, update right return left + right

</div>

<div id="0ded5ae4" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-29T03:10:55.853762Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-29T03:10:55.853358Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-29T03:10:55.864691Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-29T03:10:55.864176Z&quot;}"
papermill="{&quot;duration&quot;:1.513e-2,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.865734&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.850604&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class RangeSumQueryLazy:
    def __init__(self, nums: list[int]) -> None:
        self.N = len(nums)
        self.nums = nums
        self.segment_tree = [0 for i in range(4 * self.N)]
        self.lazy = [0 for i in range(4 * self.N)]
        self.build(0, self.N - 1, 0)

    def build(self, low: int, high: int, idx: int) -> None:
        if low == high:
            self.segment_tree[idx] = self.nums[low]
        else:
            mid, left_idx, right_idx = (low + high) // 2, 2 * idx + 1, 2 * idx + 2
            self.build(low, mid, left_idx)
            self.build(mid + 1, high, right_idx)
            self.segment_tree[idx] = self.segment_tree[left_idx] + self.segment_tree[right_idx]

    def update(self, low: int, high: int, idx: int, left: int, right: int, val: int) -> None:
        # Update any impending updates
        left_idx, right_idx = 2 * idx + 1, 2 * idx + 2
        if self.lazy[idx] != 0:
            self.segment_tree[idx] = self.lazy[idx] * (high - low + 1)
            # If children exists, lazy propagate
            if low != high:
                self.lazy[left_idx] = self.lazy[right_idx] = self.lazy[idx]
            self.lazy[idx] = 0

        # Check overlap conditions
        if left <= low <= high <= right:
            self.segment_tree[idx] = val * (high - low + 1)
            # If children exists, lazy propagate
            if low != high:
                self.lazy[left_idx] = self.lazy[right_idx] = val

        elif high < left or right < low:
            return
        else:
            mid = (low + high) // 2
            self.update(low, mid, left_idx, left, right, val)
            self.update(mid + 1, high, right_idx, left, right, val)
            self.segment_tree[idx] = self.segment_tree[left_idx] + self.segment_tree[right_idx]

    def query(self, low: int, high: int, idx: int, left: int, right: int) -> int:
        # Update any impending updates
        left_idx, right_idx = 2 * idx + 1, 2 * idx + 2
        if self.lazy[idx] != 0:
            self.segment_tree[idx] = self.lazy[idx] * (high - low + 1)
            # If children exists, lazy propagate
            if low != high:
                self.lazy[left_idx] = self.lazy[right_idx] = self.lazy[idx]
            self.lazy[idx] = 0

        # Check overlap conditions
        if left <= low <= high <= right:
            return self.segment_tree[idx]
        elif high < left or right < low:
            return 0
        else:
            mid = (low + high) // 2
            return self.query(low, mid, left_idx, left, right) + self.query(mid + 1, high, right_idx, left, right)

# Testing the solution
rsql = RangeSumQueryLazy([1,4,2,1,3,1])
assert rsql.query(0, rsql.N - 1, 0, 0, 5) == 12
rsql.update(0, rsql.N - 1, 0, 2, 4, 5)
assert rsql.query(0, rsql.N - 1, 0, 0, 5) == 21
rsql.update(0, rsql.N - 1, 0, 0, 2, 2)
assert rsql.query(0, rsql.N - 1, 0, 0, 3) == 11
rsql.update(0, rsql.N - 1, 0, 2, 3, 4)
assert rsql.query(0, rsql.N - 1, 0, 3, 5) == 10
```

</div>

<div id="0f6193c8" class="cell markdown"
papermill="{&quot;duration&quot;:2.27e-3,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.870202&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.867932&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Codechef Flip Coins: <https://www.codechef.com/problems/FLIPCOIN>

</div>

<div id="a62a3890" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-29T03:10:55.875227Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-29T03:10:55.874841Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-29T03:10:55.887053Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-29T03:10:55.886570Z&quot;}"
papermill="{&quot;duration&quot;:1.5986e-2,&quot;end_time&quot;:&quot;2024-07-29T03:10:55.888174&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-29T03:10:55.872188&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
CoinTuple = collections.namedtuple('CoinTuple', ['heads', 'tails'])
class FlipCoins:
    def __init__(self, N: int) -> None:
        self.N = N
        self.coins: list[int] = [0 for i in range(N)]
        self.segment_tree: list[CoinTuple] = [CoinTuple(0, 0) for i in range(4 * N)]
        self.lazy: list[bool] = [False for i in range(4 * N)]
        self.build(0, self.N - 1, 0)

    def build(self, low: int, high: int, idx: int) -> None:
        if low == high:
            self.segment_tree[idx] = CoinTuple(0, 1)
        else:
            mid, left_idx, right_idx = (low + high) // 2, 2 * idx + 1, 2 * idx + 2
            self.build(low, mid, left_idx)
            self.build(mid + 1, high, right_idx)
            left_tuple = self.segment_tree[left_idx]
            right_tuple = self.segment_tree[right_idx]
            self.segment_tree[idx] = CoinTuple(left_tuple.heads + right_tuple.heads, left_tuple.tails + right_tuple.tails)

    def update(self, low: int, high: int, idx: int, left: int, right: int) -> None:
        left_idx, right_idx = 2 * idx + 1, 2 * idx + 2

        # Update if there are impending updates
        if self.lazy[idx]:
            self.segment_tree[idx] = CoinTuple(self.segment_tree[idx].tails, self.segment_tree[idx].heads)
            self.lazy[idx] = False
            if low != high:
                self.lazy[left_idx], self.lazy[right_idx] = not self.lazy[left_idx], not self.lazy[right_idx]

        # Check for overlaps
        if left <= low <= high <= right:
            self.segment_tree[idx] = CoinTuple(self.segment_tree[idx].tails, self.segment_tree[idx].heads)
            if low != high:
                self.lazy[left_idx], self.lazy[right_idx] = not self.lazy[left_idx], not self.lazy[right_idx]
        elif high < left or right < low:
            return
        else:
            mid = (low + high) // 2
            self.update(low, mid, left_idx, left, right)
            self.update(mid + 1, high, right_idx, left, right)
            left_tuple = self.segment_tree[left_idx]
            right_tuple = self.segment_tree[right_idx]
            self.segment_tree[idx] = CoinTuple(left_tuple.heads + right_tuple.heads, left_tuple.tails + right_tuple.tails)

    def query(self, low: int, high: int, idx: int, left: int, right: int) -> int:
        left_idx, right_idx = 2 * idx + 1, 2 * idx + 2

        # Update if there are impending updates
        if self.lazy[idx]:
            self.segment_tree[idx] = CoinTuple(self.segment_tree[idx].tails, self.segment_tree[idx].heads)
            self.lazy[idx] = False
            if low != high:
                self.lazy[left_idx], self.lazy[right_idx] = not self.lazy[left_idx], not self.lazy[right_idx]

        # Check overlaps
        if left <= low <= high <= right:
            return self.segment_tree[idx].heads
        elif right < low or high < left:
            return 0
        else:
            mid = (low + high) // 2
            return self.query(low, mid, left_idx, left, right) + self.query(mid + 1, high, right_idx, left, right)

# Testing the solution
fc = FlipCoins(4)
assert fc.query(0, fc.N - 1, 0, 0, 3) == 0
fc.update(0, fc.N - 1, 0, 1, 2)
assert fc.query(0, fc.N - 1, 0, 0, 1) == 1
assert fc.query(0, fc.N - 1, 0, 0, 0) == 0
fc.update(0, fc.N - 1, 0, 0, 3)
assert fc.query(0, fc.N - 1, 0, 0, 3) == 2
assert fc.query(0, fc.N - 1, 0, 3, 3) == 1
```

</div>
