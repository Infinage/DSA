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
    version: 3.11.5
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 1.662091
    end_time: "2024-02-29T03:17:30.303673"
    environment_variables: {}
    input_path: 05-sorting.ipynb
    output_path: 05-sorting.ipynb
    parameters: {}
    start_time: "2024-02-29T03:17:28.641582"
    version: 2.4.0
---

<div id="7d2510f0" class="cell markdown"
papermill="{&quot;duration&quot;:8.801e-3,&quot;end_time&quot;:&quot;2024-02-29T03:17:29.907712&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:29.898911&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Video Link: <https://www.youtube.com/watch?v=HGk_ypEuS24&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=14>

</div>

<div id="dc9caee0" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:29.932257Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:29.930851Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:30.018112Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:30.017263Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.100705,&quot;end_time&quot;:&quot;2024-02-29T03:17:30.019922&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:29.919217&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Necessary imports
import numpy as np
```

</div>

<div id="6379e2eb" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:30.026056Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:30.025312Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:30.031989Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:30.031212Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.2038e-2,&quot;end_time&quot;:&quot;2024-02-29T03:17:30.033866&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:30.021828&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Selection Sort
def selection_sort(arr: list[int]) -> list[int]:
    """
    Avg, Best, Worst Complexity - O(N^2)

    For each index: 0 - (N - 1)
        For each slice from index till array end
            Select the minimum and put it at index (or beginning of the slice)
    """

    N = len(arr)
    result = [*arr]
    for i in range(N - 1):
        min_idx = i
        for j in range(i + 1, N):
            if result[min_idx] > result[j]:
                min_idx = j
        result[i], result[min_idx] = result[min_idx], result[i]
    return result

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=50).tolist()
    assert selection_sort(arr) == sorted(arr)
```

</div>

<div id="23fba2fa" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:30.038464Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:30.038085Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:30.044255Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:30.043490Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0151e-2,&quot;end_time&quot;:&quot;2024-02-29T03:17:30.045673&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:30.035522&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Bubble Sort
def bubble_sort(arr: list[int]) -> list[int]:
    """
    Avg, Best, Worst Time - O(N^2)

    Best can be an avg O(N) if we optimized by breaking out
    if didn't swap for one outer iteration - already sorted

    Pushes the maximum to the last index of slice by adjacent swaps
    """
    N = len(arr)
    result = [*arr]
    for i in range(N):
        didSwap: bool = False
        for j in range(N - i - 1):
            if result[j] > result[j + 1]:
                result[j], result[j + 1] = result[j + 1], result[j]
                didSwap = True

        # Optimizing by early breaking
        if not didSwap:
            break
    return result

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=50).tolist()
    assert bubble_sort(arr) == sorted(arr)
```

</div>

<div id="736c4faf" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:30.050353Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:30.050007Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:30.062378Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:30.061599Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.6954e-2,&quot;end_time&quot;:&quot;2024-02-29T03:17:30.064271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:30.047317&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Insertion Sort
def insertion_sort(arr: list[int]) -> list[int]:
    """
    Best Case - O(N) - Already sorted
    Worst Case - O(N^2)

    Takes an element and ensure that it is put
    in the correct order
    """
    N = len(arr)
    result = [*arr]
    for i in range(1, N):
        curr = result[i]
        for j in range(i - 1, -1, -1):
            if result[j] > curr:
                result[j + 1] = result[j]
                result[j] = curr
    return result

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=50).tolist()
    assert insertion_sort(arr) == sorted(arr)
```

</div>

<div id="bf92642e" class="cell markdown"
papermill="{&quot;duration&quot;:3.136e-3,&quot;end_time&quot;:&quot;2024-02-29T03:17:30.070491&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:30.067355&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Video Link: <https://www.youtube.com/watch?v=ogjf7ORKfd8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=14>

</div>

<div id="dca36744" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-29T03:17:30.075693Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-29T03:17:30.075087Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-29T03:17:30.081854Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-29T03:17:30.080938Z&quot;}"
papermill="{&quot;duration&quot;:1.1242e-2,&quot;end_time&quot;:&quot;2024-02-29T03:17:30.083381&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-29T03:17:30.072139&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Merge Sort
def merge_sort(arr: list[int]) -> list[int]:
    N = len(arr)
    if N <= 1:
        return arr
    else:
        mid = N // 2
        left = merge_sort(arr[:mid])
        right = merge_sort(arr[mid:])
        left_idx = right_idx = 0
        result: list[int] = []
        while left_idx < mid or right_idx < N - mid:
            if (right_idx >= N - mid) or (left_idx < mid and left[left_idx] < right[right_idx]):
                result.append(left[left_idx])
                left_idx += 1
            else:
                result.append(right[right_idx])
                right_idx += 1
        return result

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=50).tolist()
    assert merge_sort(arr) == sorted(arr)
```

</div>
