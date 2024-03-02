---
jupyter:
  kernelspec:
    display_name: Python 3 (ipykernel)
    language: python
    name: python3
  nbformat: 4
  nbformat_minor: 2
---

<div id="27a4537d" class="cell code">

``` python
import math
```

</div>

<div id="29de74db" class="cell markdown">

Video link:
<https://www.youtube.com/watch?v=37E9ckMDdTk&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=17>

</div>

<div id="8c59ddec" class="cell code">

``` python
# Largest element of an array
arr: list[int] = [1, 2, 3, 1, 2, 3, 4, 0, 3]
max_ = 0
for i in arr:
    if i > max_:
        max_ = i
max_
```

</div>

<div id="c2ef97bb" class="cell code">

``` python
# Second largest element of an array - 2 passes
arr: list[int] = [1, 2, 3, 1, 2, 4, 4, 0, 3]
N = len(arr)

# Find the max index, this way if the Q requires that 2nd 
# largest be a diff number or simply a diff index
# we can accomodate both
max_, second_max_ = 0, 0
for i in range(N):
    if arr[i] > arr[max_]:
        max_ = i

# Variable to ensure that we return -1 if there is no 2nd largest
found = False
for i in range(N):
    if arr[i] > arr[second_max_] and arr[i] != arr[max_]:
        second_max_ = i
        found = True

arr[second_max_] if found else -1
```

</div>

<div id="64ecf17d" class="cell code">

``` python
# Second largest  and secod largest of an array - 1 pass
arr: list[int] = [1, 2, 3, 1, 2, 4, 4, 2, 3]
N = len(arr)
max_, second_max_ = arr[0], -math.inf
min_, second_min_ = arr[0], math.inf
for i in arr:
    if i >= max_:
        max_ = i
    elif i > second_max_:
        second_max_ = i

    if i <= min_:
        min_ = i
    elif i < second_min_:
        second_min_ = i

second_max_, second_min_
```

</div>

<div id="710a5862" class="cell code">

``` python
# Check if the array is sorted
arr: list[int] = [1, 2, 3, 1, 2, 4, 4, 2, 3]
arr.sort()
for i in range(len(arr) - 1):
    if arr[i] > arr[i + 1]:
        print("False")
        break
else:
    print("True")
```

</div>

<div id="41548461" class="cell code" lines_to_next_cell="1">

``` python
# Remove duplicates in place from a sorted array
arr: list[int | None] = [1, 1, 2, 2, 2, 3, 3, 4]

N = len(arr)
i, j = 0, 1

while j < N:
    if arr[i] != arr[j]:
        arr[i + 1] = arr[j]
        i += 1
    j += 1
i += 1

while i < N:
    arr[i] = None
    i += 1

print(arr)
```

</div>

<div id="4db22eb4" class="cell code">

``` python
# Left rotate array by one place
def left_rotate_inplace(arr_: list[int]):
    j, N = arr_[0], len(arr_)
    for i in range(0, N - 1):
        arr_[i] = arr_[i + 1]
    arr_[-1] = j

arr: list[int] = [1, 2, 3, 4, 5]
left_rotate_inplace(arr)
print(arr)
```

</div>

<div id="2517ddfb" class="cell code" lines_to_next_cell="1">

``` python
# Left rotate array by K places (in place)
# Time - O(KN), Space - O(1)
arr: list[int] = [1, 2, 3, 4, 5]
k = 4

N = len(arr)
k = k % N
for i in range(k):
    left_rotate_inplace(arr)

print(arr)
```

</div>

<div id="9e70b54b" class="cell code" lines_to_next_cell="1">

``` python
# Left rotate array by K places 
# Time - O(N), Space - O(N)
def left_rotate_(arr_: list[int], k: int):
    N = len(arr)
    k = k % N

    result: list[int] = []
    for i in range(k, N):
        result.append(arr[i])
    for i in range(k):
        result.append(arr[i])

    return result

left_rotate_([1, 2, 3, 4, 5], 4)
```

</div>

<div id="9c704e76" class="cell code" lines_to_next_cell="1">

``` python
# Left rotate array in O(N) with O(1) space
def left_rotate(arr_: list[int], k: int):
    def reverse(start: int, end: int):
        while start < end:
            arr_[start], arr_[end] = arr_[end], arr_[start]
            start, end = start + 1, end - 1

    N = len(arr_)
    k = k % N

    reverse(0, k - 1)
    reverse(k, N - 1)
    reverse(0, N - 1)

arr: list[int] = [1, 2, 3, 4, 5]
left_rotate(arr, 2)
print(arr)
```

</div>

<div id="10d38f9b" class="cell code">

``` python
# Right rotate array in O(N) with O(1) space
def right_rotate(arr_: list[int], k: int):
    def reverse(start: int, end: int):
        while start < end:
            arr_[start], arr_[end] = arr_[end], arr_[start]
            start, end = start + 1, end - 1

    N = len(arr_)
    k = k % N

    reverse(0, N - 1)
    reverse(0, k - 1)
    reverse(k, N - 1)

arr: list[int] = [1, 2, 3, 4, 5]
right_rotate(arr, 3)
print(arr)
```

</div>

<div id="398a6e6d" class="cell code">

``` python
# Move zeros to end of the array
arr: list[int] = [0, 0, 1, 0, 8, 3, 0, 2, 5, 3, 0]
N = len(arr)
i, j = 0, 1
while j < N:
    if arr[i] != 0:
        i += 1
    elif arr[i] == 0 and arr[j] != 0:
        arr[i], arr[j] = arr[j], arr[i]
        i += 1
    j += 1

print (arr)
```

</div>

<div id="5955b7ea" class="cell code">

``` python
# Linear search
arr: list[int] = [1, 2, 1, 3, 5, 4, 3]
j = 9
for i in range(len(arr)):
    if arr[i] == j:
        break
i if arr[i] == j else -1
```

</div>

<div id="7c8a52b8" class="cell code">

``` python
# Union of two sorted arrays - same order without repetitions
# Time complexity - O(N1 + N2)
arr1: list[int] = [1, 1, 2, 3, 4, 5]
arr2: list[int] = [2, 3, 4, 4, 5, 6]

N1, N2 = len(arr1), len(arr2)
arr: list[int] = []

i, j = 0, 0
while i < N1 or j < N2:
    if j >= N2 or (i < N1 and arr1[i] < arr2[j]):
        if not arr or arr[-1] < arr1[i]:
            arr.append(arr1[i])
        i += 1
    else:
        if not arr or arr[-1] < arr2[j]:
            arr.append(arr2[j])
        j += 1

print(arr)
```

</div>

<div id="25ae4174" class="cell code">

``` python
# Intersection of two sorted arrays
# Time complexity - O(min(N1, N2))
arr1: list[int] = [1, 1, 2, 3, 4, 5]
arr2: list[int] = [2, 3, 4, 4, 5, 6]

N1, N2 = len(arr1), len(arr2)
arr: list[int] = []

i = j = 0
while i < N1 and j < N2:
    if arr1[i] == arr2[j]:
        arr.append(arr1[i])
        i += 1
        j += 1
    elif arr1[i] < arr2[j]:
        i += 1
    else:
        j += 1

assert arr == [2, 3, 4, 5]
```

</div>
