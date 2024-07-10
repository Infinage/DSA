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
    duration: 1.261252
    end_time: "2024-07-10T15:49:31.412680"
    environment_variables: {}
    input_path: study/striver-A2Z/18-misc.ipynb
    output_path: study/striver-A2Z/18-misc.ipynb
    parameters: {}
    start_time: "2024-07-10T15:49:30.151428"
    version: 2.6.0
---

<div id="7dfdcaf8" class="cell markdown"
papermill="{&quot;duration&quot;:1.542e-3,&quot;end_time&quot;:&quot;2024-07-10T15:49:31.276017&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T15:49:31.274475&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Useful imports

</div>

<div id="c52ade4f" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-10T15:49:31.279468Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-10T15:49:31.279048Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-10T15:49:31.284702Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-10T15:49:31.284274Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.709e-3,&quot;end_time&quot;:&quot;2024-07-10T15:49:31.285807&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T15:49:31.277098&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import math
import typing
import functools
import itertools
import heapq
import bisect
import collections
```

</div>

<div id="6271cefc" class="cell markdown"
papermill="{&quot;duration&quot;:8.81e-4,&quot;end_time&quot;:&quot;2024-07-10T15:49:31.287561&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T15:49:31.286680&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Segmented Seive of Erastosthenes Video Link:
<https://www.youtube.com/watch?v=MY0fXk-3BVQ>

</div>

<div id="14c65855" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-10T15:49:31.290202Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-10T15:49:31.289887Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-10T15:49:31.296010Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-10T15:49:31.295575Z&quot;}"
papermill="{&quot;duration&quot;:8.648e-3,&quot;end_time&quot;:&quot;2024-07-10T15:49:31.297083&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T15:49:31.288435&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def segmented_seive_of_erastosthenes(low: int, high: int) -> list[int]:
    """
    1. Generate primes till sqrt(high)
    2. For each generated prime, repeat same logic - (i * i, end, i), instead of starting at i * i start at first position within range [low, high].
    """

    # Step 1
    sqrt = int(math.sqrt(high))
    seive: list[bool] = [True for i in range(sqrt + 1)]
    seive[0], seive[1], i = False, False, 2
    while i * i <= sqrt:
        if seive[i]:
            seive[i*i::i] = [False] * len(seive[i*i::i])
        i += 1

    primes_below: list[int] = [i for i in range(sqrt + 1) if seive[i]]

    # Step 2
    seive = [True for i in range(low, high + 1)]
    for prime in primes_below:
        # Always start at n * n and if that is smaller, we check for the 1st num in range
        start = max(prime * prime, math.ceil(low / prime) * prime)
        seive[start - low::prime] = [False] * len(seive[start - low::prime])

    primes: list[int] = [i for i in range(low, high + 1) if seive[i - low] and i != 1]

    return primes

# Testing the solution
assert segmented_seive_of_erastosthenes(100, 125) == [101, 103, 107, 109, 113]
assert segmented_seive_of_erastosthenes(1, 10) == [2, 3, 5, 7]
```

</div>
