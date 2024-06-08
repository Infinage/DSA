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
    duration: 1.42637
    end_time: "2024-06-08T18:11:47.609742"
    environment_variables: {}
    input_path: study/striver-A2Z/17-greedy.ipynb
    output_path: study/striver-A2Z/17-greedy.ipynb
    parameters: {}
    start_time: "2024-06-08T18:11:46.183372"
    version: 2.6.0
---

<div id="76cb4635" class="cell markdown"
papermill="{&quot;duration&quot;:3.099e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.319455&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.316356&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Useful imports

</div>

<div id="d45ec848" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.325938Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.325468Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.330928Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.330490Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.968e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.332051&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.322083&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import heapq
import bisect
import collections
import itertools
import functools
import math
```

</div>

<div id="a2f52f24" class="cell markdown"
papermill="{&quot;duration&quot;:2.466e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.336964&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.334498&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Assign cookies: <https://leetcode.com/problems/assign-cookies/> Video
Link: <https://youtu.be/DIX2p7vb9co?si=-lYoEBkNX6G40Tpo>

</div>

<div id="8016e3c9" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.343050Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.342662Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.347785Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.347335Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.52e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.348860&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.339340&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/assign-cookies/submissions/1280845661
def findContentChildren(g: list[int], s: list[int]) -> int:
    """
    For each child we assign cookies that only require as much to satisfy their greed.
    For a child with greed of 3, we assign the minimum cookie left to satisfy condition: s[k] >= 3
    """
    # Sort in ASC order since we need to find the max
    # number of content children possible
    g.sort()
    s.sort()

    # Have pointers for greed and cookies arrary
    g_length, s_length = len(g), len(s)
    content_children = g_idx = s_idx = 0

    # Iterate until either of the arrays are exhausted
    while g_idx < g_length and s_idx < s_length:
        if s[s_idx] >= g[g_idx]:
            content_children, s_idx, g_idx = content_children + 1, s_idx + 1, g_idx + 1
        else:
            s_idx += 1

    return content_children

# Testing the solution
assert findContentChildren([1,2,3], [1,1,1]) == 1
assert findContentChildren([1,2], [1,2,3]) == 2
assert findContentChildren([1,2,3], [1,2]) == 2
```

</div>

<div id="f911a310" class="cell markdown"
papermill="{&quot;duration&quot;:2.528e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.353861&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.351333&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Shortest job first CPU scheduling Video Link:
<https://youtu.be/3-QbX1iDbXs?si=oh3KUu3zLd08uDZ7>

</div>

<div id="1e00764f" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.359690Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.359215Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.363359Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.362812Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.239e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.364417&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.356178&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def SJF(bt: list[int]) -> float:
    """Time: O(N), Space: O(N)"""

    # Heapify to convert into a min heap
    heapq.heapify(bt)

    N = len(bt)
    curr_time = total_time = 0
    while bt:
        runtime = heapq.heappop(bt)
        total_time += curr_time
        curr_time += runtime

    avg_wait = total_time // N
    return avg_wait

# Testing the solution
assert SJF([4,3,7,1,2]) == 4
assert SJF([1,2,3,4]) == 2
```

</div>

<div id="e8d91515" class="cell markdown"
papermill="{&quot;duration&quot;:2.307e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.369828&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.367521&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Lemonade change:
<https://leetcode.com/problems/lemonade-change/description/> Video link:
<https://youtu.be/n_tmibEhO6Q?si=bqyD-xTjBPIG9scO>

</div>

<div id="726bd349" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.375516Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.375187Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.379800Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.379389Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.69e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.380849&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.372159&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/lemonade-change/submissions/1281069969
def lemonadeChange(bills: list[int]) -> bool:
    change5 = change10 = 0
    for bill in bills:
        if bill == 5:
            change5 += 1
        elif bill == 10:
            change10 += 1
            change5 -= 1
        else:
            # Try to change with 10 if available
            if change10 > 0:
                change5, change10 = change5 - 1, change10 - 1
            # Else we can change with 5
            else:
                change5 -= 3

        # Reason this is added here and not at the end: [10,5]
        if change5 < 0 or change10 < 0:
            return False

    else:
        return True

# Testing the solution
assert lemonadeChange([5,5,10,10,20]) == False
assert lemonadeChange([10,5]) == False
assert lemonadeChange([5,10,20]) == False
assert lemonadeChange([5,5,5,20]) == True
```

</div>

<div id="bf923f2c" class="cell markdown"
papermill="{&quot;duration&quot;:2.376e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.385634&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.383258&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Jump game: <https://leetcode.com/problems/jump-game/> Video Link:
<https://youtu.be/tZAa_jJ3SwQ?si=PUeiia1qBXmvfk_C>

</div>

<div id="d487decb" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.391335Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.390928Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.395031Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.394621Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.112e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.396107&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.387995&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def canJumpBrute(nums: list[int]) -> bool:
    N = len(nums)
    good_indices: collections.deque = collections.deque([N - 1])
    for i in range(N - 2, -1, -1):
        for good_idx in good_indices:
            if i + nums[i] >= good_idx:
                good_indices.appendleft(i)
                break

    return good_indices[0] == 0

# Testing the solution
assert canJumpBrute([2,3,1,1,4]) == True
assert canJumpBrute([3,2,1,0,4]) == False
assert canJumpBrute([2,0,2,0,0]) == True
```

</div>

<div id="4b59da66" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.401970Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.401551Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.406020Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.405484Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.566e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.407109&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.398543&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game/submissions/1281092917
def canJump(nums: list[int]) -> bool:
    """
    We can notice that if the latest good index was reachable, then every other good index beyond would
    have been reachable as well.

    On the contrary if the latest good index (nearest to current) was not reachable, then no index beyond would be reachable.

    Time: O(N), Space: O(1)
    """
    N = len(nums)
    good_idx: int = N - 1
    for i in range(N - 2, -1, -1):
        if i + nums[i] >= good_idx:
            good_idx = i

    return good_idx == 0

# Testing the solution
assert canJump([2,3,1,1,4]) == True
assert canJump([3,2,1,0,4]) == False
assert canJump([2,0,2,0,0]) == True
```

</div>

<div id="da43a335" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.412953Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.412609Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.416928Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.416397Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.373e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.417948&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.409575&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game/submissions/1281113037
def canJumpStriver(nums: list[int]) -> bool:
    """
    If there were no 0's we would always be able to reach the destination.
    In other cases it may or may not be possible.

    Time: O(N), Space: O(1)
    """
    N, max_idx = len(nums), 0
    for i in range(N):
        if i <= max_idx:
            max_idx = max(max_idx, nums[i] + i)
        else:
            return False

    return True

# Testing the solution
assert canJumpStriver([2,3,1,1,4]) == True
assert canJumpStriver([3,2,1,0,4]) == False
assert canJumpStriver([2,0,2,0,0]) == True
```

</div>

<div id="7d2a5ae9" class="cell markdown"
papermill="{&quot;duration&quot;:2.351e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.422858&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.420507&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Jump Game - II: <https://leetcode.com/problems/jump-game-ii/> Video
Link: <https://youtu.be/7SBVnw7GSTk?si=UDZojaM70TuG0XgY>

</div>

<div id="bcdd786f" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.429167Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.428743Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.433320Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.432794Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.999e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.434443&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.425444&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def jump2Recursive(nums: list[int]) -> int:
    @functools.cache
    def backtrack(i: int) -> int:
        if i == N - 1:
            return 0
        else:
            min_ = N
            for jump in range(nums[i]):
                min_ = min(min_, backtrack(i + jump + 1))
            return 1 + min_

    N = len(nums)
    return backtrack(0)

# Testing the solution
assert jump2Recursive([2,3,1,1,4]) == 2
assert jump2Recursive([2,3,0,1,4]) == 2
```

</div>

<div id="7b38a2b6" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.440417Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.439947Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.444716Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.444214Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.925e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.445807&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.436882&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game-ii/submissions/1281812619/
def jump2Tab(nums: list[int]) -> int:
    # Time: O(N ** 2), Space: O(N)
    N = len(nums)
    dp: list[int] = [N if i < N - 1 else 0 for i in range(N)]
    for i in range(N - 2, -1, -1):
        for j in range(i + 1, min(N, i + 1 + nums[i])):
            dp[i] = min(dp[i], 1 + dp[j])

    return dp[0]

# Testing the solution
assert jump2Tab([2,3,1,1,4]) == 2
assert jump2Tab([2,3,0,1,4]) == 2
```

</div>

<div id="7336f2b2" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.451533Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.451258Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.455407Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.454969Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.138e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.456424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.448286&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/jump-game-ii/submissions/1281839417
def jump2Striver(nums: list[int]) -> int:
    """
    Instead of iterating through all indices that we can jump to,
    we keep track of the range.
    For each range
        - Figure out the maximum idx we can jump to
        - jumps = jumps + 1
    Iterate until we reach the last index, ans would be the value of jumps variable

    Time: O(N), Space: O(1)
    """
    N = len(nums)
    jumps = l = r = 0
    while r < N - 1:
        farthest = 0
        for i in range(l, r + 1):
            farthest = max(farthest, i + nums[i])
        l, r, jumps = r + 1, farthest, jumps + 1

    return jumps

# Testing the solution
assert jump2Striver([2,3,1,1,4]) == 2
assert jump2Striver([2,3,0,1,4]) == 2
```

</div>

<div id="52b5429b" class="cell markdown"
papermill="{&quot;duration&quot;:2.418e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.461291&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.458873&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Job sequencing Problem:
<https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1>
Video Link: <https://youtu.be/QbwltemZbRg?si=R93V-44Jyr37Il4L>

</div>

<div id="c804e410" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.467264Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.466846Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.472866Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.472324Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0208e-2,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.473909&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.463701&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def jobScheduling(jobs: list[tuple[int, int, int]], N: int) -> tuple[int, int]:
    """
    Start with the jobs with highest profit, try to push the start time as close as possible to the deadline
    being super lazy about it.

    Time: O(N log N) + O(N x max deadline)
    Space: O(N)

    We can optimize the inner loop (deadline -> 0) further with the use of DSU (Disjoint set union)
    """
    jobs_start: set[int] = set()
    jobs_sorted: list[tuple[int, int]] = sorted(map(lambda x: (x[2], x[1]), jobs), reverse=True)
    job_count = total_profit = 0
    for profit, deadline in jobs_sorted:
        for start in range(deadline - 1, -1, -1):
            if start not in jobs_start:
                jobs_start.add(start)
                job_count, total_profit = job_count + 1, total_profit + profit
                break

    return job_count, total_profit

# Testing the solution
assert jobScheduling([(1,2,100),(2,1,19),(3,2,27),(4,1,25),(5,1,15)], 5) == (2, 127)
assert jobScheduling([(1,4,20),(2,1,10),(3,1,40),(4,1,30)], 5) == (2, 60)
assert jobScheduling([(1,4,50),(2,1,50)], 2) == (2, 100)
assert jobScheduling([(1,4,60),(2,1,50)], 2) == (2, 110)
```

</div>

<div id="2835d225" class="cell markdown"
papermill="{&quot;duration&quot;:2.436e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.478959&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.476523&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

N meetings in one room:
<https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1>
Video Link: <https://youtu.be/mKfhTotEguk?si=gTVT-RsSg0PR9RPP>

</div>

<div id="7fe0aed4" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-08T18:11:47.485338Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-08T18:11:47.484858Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-08T18:11:47.490019Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-08T18:11:47.489569Z&quot;}"
papermill="{&quot;duration&quot;:9.655e-3,&quot;end_time&quot;:&quot;2024-06-08T18:11:47.491096&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-08T18:11:47.481441&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def maximumMeetings(N: int, start: list[int], end: list[int]) -> int:
    """
    Sort based on end time, we need to find meetings that finish sooner.
    Simply iterate through the sorted meeting in order and check if it is possible to host the meeting

    Time: O(N log N)
    Space: O(N)
    """

    # Sort meeting based on the end time
    meetings: list[tuple[int, int, int]] = [(start[i], end[i], i) for i in range(N)]
    meetings.sort(key=lambda x: x[1])

    order: list[int] = []
    meeting_count = free_at = 0
    for stime, etime, idx in meetings:
        if stime > free_at:
            order.append(idx)
            meeting_count, free_at = meeting_count + 1, etime

    # If needed, to return the order in which the meetings could be conducted,
    # we can make use of the `meeting_count` variable

    return meeting_count

# Testing the solution
assert maximumMeetings(6, [1,3,0,5,8,5], [2,4,6,7,9,9]) == 4
assert maximumMeetings(3, [1,4,6], [5,6,10]) == 2
```

</div>
