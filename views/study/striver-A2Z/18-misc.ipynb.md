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
    duration: 1.285275
    end_time: "2024-07-10T02:40:16.881821"
    environment_variables: {}
    input_path: study/striver-A2Z/18-misc.ipynb
    output_path: study/striver-A2Z/18-misc.ipynb
    parameters: {}
    start_time: "2024-07-10T02:40:15.596546"
    version: 2.6.0
---

<div id="7dfdcaf8" class="cell markdown"
papermill="{&quot;duration&quot;:1.486e-3,&quot;end_time&quot;:&quot;2024-07-10T02:40:16.746321&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T02:40:16.744835&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Useful imports

</div>

<div id="c52ade4f" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-10T02:40:16.749096Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-10T02:40:16.748735Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-10T02:40:16.753922Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-10T02:40:16.753423Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.698e-3,&quot;end_time&quot;:&quot;2024-07-10T02:40:16.754960&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T02:40:16.747262&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:7.49e-4,&quot;end_time&quot;:&quot;2024-07-10T02:40:16.756523&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T02:40:16.755774&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Segmented Seive of Erastosthenes Video Link:
<https://www.youtube.com/watch?v=MY0fXk-3BVQ>

</div>

<div id="14c65855" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-07-10T02:40:16.759177Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-07-10T02:40:16.758764Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-07-10T02:40:16.764824Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-07-10T02:40:16.764321Z&quot;}"
papermill="{&quot;duration&quot;:8.532e-3,&quot;end_time&quot;:&quot;2024-07-10T02:40:16.765834&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-07-10T02:40:16.757302&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
