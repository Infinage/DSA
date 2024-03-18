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
    version: 3.10.13
  nbformat: 4
  nbformat_minor: 5
  papermill:
    default_parameters: {}
    duration: 1.569136
    end_time: "2024-03-18T03:05:15.843896"
    environment_variables: {}
    input_path: study/striver-A2Z/05-sorting.ipynb
    output_path: study/striver-A2Z/05-sorting.ipynb
    parameters: {}
    start_time: "2024-03-18T03:05:14.274760"
    version: 2.4.0
---

<div id="7d2510f0" class="cell markdown"
papermill="{&quot;duration&quot;:4.041e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.427015&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.422974&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Video Link: <https://www.youtube.com/watch?v=HGk_ypEuS24&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=14>

</div>

<div id="dc9caee0" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.435637Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.434987Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.539597Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.538731Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:0.111327,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.541944&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.430617&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Necessary imports
import numpy as np
import random
```

</div>

<div id="6379e2eb" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.556256Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.555413Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.564215Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.563580Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.7021e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.565809&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.548788&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    assert selection_sort(arr) == sorted(arr)
```

</div>

<div id="23fba2fa" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.573665Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.573374Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.583243Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.582592Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.562e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.584816&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.569196&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Bubble Sort
def bubble_sort_1(arr: list[int]) -> list[int]:
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
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    assert bubble_sort_1(arr) == sorted(arr)
```

</div>

<div id="736c4faf" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.592883Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.592357Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.600289Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.599665Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.3728e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.602025&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.588297&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Insertion Sort
def insertion_sort_1(arr: list[int]) -> list[int]:
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
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    assert insertion_sort_1(arr) == sorted(arr)
```

</div>

<div id="bf92642e" class="cell markdown"
papermill="{&quot;duration&quot;:3.301e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.608685&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.605384&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Video Link: <https://www.youtube.com/watch?v=ogjf7ORKfd8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=14>

</div>

<div id="dca36744" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.616941Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.616221Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.625368Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.624765Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4946e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.626998&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.612052&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Merge Sort - With aux space, O(N log N)
# With O(N) space is possible, if we created a temp arr and assigned values from temp back to array
# At any point in time, we would only take up O(N) space
def merge_sort(arr: list[int]) -> list[int]:
    """
    Average, Best, Worst - O(N log N)
    Space complexity - O (N log N)

    Space complexity can be O(N) if we created a seperate func to merge that creates and deletes a
    temp arr. This array would not be stored in the stack space, at worst take up extra O(N) space.
    We would only be merging any two arrays at any point in time.

    Divide the array and merge.
    When merging ensure that the array is merged in correct order.
    """
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
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    assert merge_sort(arr) == sorted(arr)
```

</div>

<div id="5d0a6f92" class="cell markdown"
papermill="{&quot;duration&quot;:3.317e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.633762&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.630445&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Video Link: <https://www.youtube.com/watch?v=ogjf7ORKfd8&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=14&pp=iAQB>

</div>

<div id="db97aab6" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.641905Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.641242Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.650036Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.649390Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.4526e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.651648&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.637122&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Quick Sort - Aux space
def quick_sort_1(arr: list[int]) -> list[int]:
    """
    Time complexity - O(N log N)
    Space complexity - O(N log N)

    Take a random index, ensure that every other element is correctly ordered relative to chosen index
    Repeat same for the two sub arrays created.
    """
    N = len(arr)
    if N <= 1:
        return arr
    else:
        pivot = random.randint(0, N - 1)
        left = [arr[i] for i in range(N) if arr[i] < arr[pivot] and i != pivot]
        right = [arr[i] for i in range(N) if arr[i] >= arr[pivot] and i != pivot]
        merged = quick_sort_1(left) + [arr[pivot]] + quick_sort_1(right)
        return merged

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    assert quick_sort_1(arr) == sorted(arr)
```

</div>

<div id="41c03989" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.659982Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.659351Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.669316Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.668718Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.585e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.670981&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.655131&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Quick Sort - In place
def quick_sort_2(arr: list[int], low: int, high: int):
    """
    Time complexity - O (N log N)
    Space complexity - O (N)
    """
    def partition(arr: list[int], low: int, high: int):
        pivot = low
        i, j = low, high
        while i < j:
            # Move i right until we find an element greater than pivot
            while arr[i] <= arr[pivot] and i < high:
                i += 1

            # Move j left until we find an element lesser than pivot
            while arr[j] > arr[pivot] and j > low:
                j -= 1

            # Swap if i hasn't crossed j yet
            if i < j:
                arr[i], arr[j] = arr[j], arr[i]

        # j is the right position for our pivot
        arr[pivot], arr[j] = arr[j], arr[pivot]
        return j

    if low < high:
        partition_idx = partition(arr, low, high)
        quick_sort_2(arr, low, partition_idx - 1)
        quick_sort_2(arr, partition_idx + 1, high)

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    quick_sort_2(arr, 0, len(arr) - 1)
    for i in range(len(arr) - 1):
        assert arr[i] <= arr[i + 1]
```

</div>

<div id="05f27db5" class="cell markdown"
papermill="{&quot;duration&quot;:3.31e-3,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.677734&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.674424&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Let us try to solve the two extras on the website.

1.  Recursive bubble sort
2.  Recursive insertion sort

</div>

<div id="46792e3d" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.685666Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.685178Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.695055Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.694399Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.5654e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.696718&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.681064&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Recursive bubble sort
def bubble_sort_2(arr: list[int], end: int):
    if end == 0:
        return
    for i in range(end - 1):
        if arr[i] > arr[i + 1]:
            arr[i], arr[i + 1] = arr[i + 1], arr[i]
    bubble_sort_2(arr, end - 1)

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    bubble_sort_2(arr, len(arr))
    for i in range(len(arr) - 1):
        assert arr[i] <= arr[i + 1]
```

</div>

<div id="c854653d" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-03-18T03:05:15.707188Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-03-18T03:05:15.706467Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-03-18T03:05:15.721483Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-03-18T03:05:15.720746Z&quot;}"
papermill="{&quot;duration&quot;:2.1153e-2,&quot;end_time&quot;:&quot;2024-03-18T03:05:15.723048&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-03-18T03:05:15.701895&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Recursive insertion sort
def insertion_sort_2(arr: list[int], end: int):
    if end < len(arr):
        while end > 0 and arr[end - 1] > arr[end]:
            arr[end - 1], arr[end] = arr[end], arr[end - 1]
            end -= 1
        insertion_sort_2(arr, end + 1)

# Testing the algorithm
for _ in range(5):
    arr = np.random.randint(100, size=random.randint(50, 100)).tolist()
    insertion_sort_2(arr, 0)
    for i in range(len(arr) - 1):
        assert arr[i] <= arr[i + 1]
```

</div>
