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
    duration: 1.382589
    end_time: "2024-06-01T15:54:48.699579"
    environment_variables: {}
    input_path: study/striver-A2Z/15-math.ipynb
    output_path: study/striver-A2Z/15-math.ipynb
    parameters: {}
    start_time: "2024-06-01T15:54:47.316990"
    version: 2.6.0
---

<div id="3ad0b29c" class="cell markdown"
papermill="{&quot;duration&quot;:2.23e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.470961&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.468731&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Useful imports, functions

</div>

<div id="9961e56c" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.475692Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.475261Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.480423Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.480007Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.598e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.481489&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.472891&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
import bisect
import collections
import itertools
import math
import heapq
```

</div>

<div id="386bad8d" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.486073Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.485678Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.491270Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.490845Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.044e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.492337&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.483293&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
class ListNode:
    def __init__(self, val: int, next_=None):
        self.val = val
        self.next = next_

    def __str__(self):
        return str(self.val)

    def len(self) -> int:
        N, curr = 0, self
        while curr is not None:
            N, curr = N + 1, curr.next
        return N

    def tail(self) -> 'ListNode':
        prev, curr = None, self
        while curr:
            prev, curr = curr, curr.next
        return prev or curr

    def to_list(self) -> list[int]:
        result: list[int] = []
        curr = self
        while curr:
            result.append(curr.val)
            curr = curr.next

        return result

    @staticmethod
    def to_singly_linked_list(nodes: list[int]) -> 'ListNode|None':
        head = curr = None
        for n in nodes:
            node = ListNode(n)
            if not head:
                head = curr = node
            else:
                curr.next = node
                curr = curr.next

        return head
```

</div>

<div id="96923fbe" class="cell markdown"
papermill="{&quot;duration&quot;:1.807e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.495921&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.494114&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Print all divisors of a number Video Link:
<https://youtu.be/Ae_Ag_saG9s?si=ehTTFV59EVSKChY2>

</div>

<div id="fec7e081" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.500368Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.499947Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.503555Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.503040Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.015e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.504691&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.497676&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllDivisorsBrute(N: int) -> list[int]:
    result: list[int] = []
    for i in range(1, N + 1):
        if N % i == 0:
            result.append(i)

    return result

# Testing the solution
assert printAllDivisorsBrute(10) == [1, 2, 5, 10]
```

</div>

<div id="8383037d" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.509342Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.508939Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.513341Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.512923Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.885e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.514419&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.506534&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllDivisorsBetter(N: int) -> list[int]:
    result: ListNode = ListNode(-1)
    i, curr = 1, result
    while i * i <= N:
        if N % i == 0:
            if i != N // i:
                div1, div2 = ListNode(i), ListNode(N // i)
                next_ = curr.next
                curr.next, div1.next, div2.next = div1, div2, next_
            else:
                div = ListNode(i)
                next_ = curr.next
                curr.next, div.next = div, next_

            curr = curr.next

        i += 1

    return result.next.to_list() if result.next else []

# Testing the solution
assert printAllDivisorsBetter(10) == [1, 2, 5, 10]
assert printAllDivisorsBetter(25) == [1,5,25]
```

</div>

<div id="812f02d7" class="cell markdown"
papermill="{&quot;duration&quot;:2.663e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.518906&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.516243&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if number is prime or not Video Link:
<https://youtu.be/MJcckSfoYdI?si=AkCS-hvE9foXQ0KX>

</div>

<div id="823de68c" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.523562Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.523137Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.527138Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.526616Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.574e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.528293&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.520719&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def isPrime(N: int) -> bool:
    """
    A number is prime if it is divisible by 1 and itself
    and the total number of divisors is exactly 2.
    """
    cnt, i = 0, 1
    while i * i <= N:
        if N % i == 0:
            if i == N // i:
                cnt += 1
            else:
                cnt += 2
        i += 1

    return cnt == 2

# Testing the solution
assert all([isPrime(11), isPrime(2), isPrime(3)])
assert not any([isPrime(1), isPrime(4), isPrime(6)])
```

</div>

<div id="4951373b" class="cell markdown"
papermill="{&quot;duration&quot;:1.868e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.532035&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.530167&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Print all prime factors of a number Video Link:
<https://youtu.be/LT7XhVdeRyg?si=OTryhgbEtQODhgBJ>

</div>

<div id="0f0aa99e" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.536740Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.536321Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.540971Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.540413Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.084e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.542013&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.533929&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllPrimeFactorsBrute(N: int) -> list[int]:
    """
    Time: O(sqrt(N) x sqrt(N)) ~ O(N), Space: Depends on problem
    """
    def _isPrime(n: int) -> bool:
        divisor_count, i = 0, 1
        while i * i <= n:
            if n % i == 0:
                divisor_count += 1 if i == n // i else 2
            i += 1
        return divisor_count == 2

    result: list[int] = []
    i = 1
    while i * i <= N:
        if N % i == 0:
            if _isPrime(i):
                result.append(i)
            if _isPrime(N // i):
                if not result or result[-1] != N // i:
                    result.append(N // i)
        i += 1

    return result

# Testing the solution
assert printAllPrimeFactorsBrute(100) == [2, 5]
assert printAllPrimeFactorsBrute(20) == [2, 5]
```

</div>

<div id="8541747e" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.546705Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.546334Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.549975Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.549539Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.117e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.551061&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.543944&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllPrimeFactorsBetter(N: int) -> list[int]:
    """
    Following the method of Prime Factorisation.

    1. Iterate from 2 -> N
    2. If i is divisible, add to list of primes and N until it is no longer divisible.
    3. Repeat until N becomes 1.

    Time: O(N x log N) for prime numbers otherwise O(sqrt N x log N)
    We say log N due to the division part
    """
    result: list[int] = []
    i = 2
    while i <= N:
        if N % i == 0:
            result.append(i)
            while N % i == 0:
                N //= i
        i += 1

    return result

# Testing the solution
assert printAllPrimeFactorsBetter(100) == [2, 5]
assert printAllPrimeFactorsBetter(20) == [2, 5]
```

</div>

<div id="0e4148f1" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.555765Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.555395Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.559393Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.558875Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.57e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.560516&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.552946&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllPrimeFactorsOptimal(N: int) -> list[int]:
    """
    Instead of running the loop N times as previously in the worst case scenarios, we run it for sqrt N time only.
    Time: O(sqrt N x log N)
    """
    result: list[int] = []
    i = 2
    while i * i <= N:
        if N % i == 0:
            result.append(i)
            while N % i == 0:
                N //= i
        i += 1

    # If N is not 1, means that it is a prime and it is only divisible by itself
    if N != 1:
        result.append(N)

    return result

# Testing the solution
assert printAllPrimeFactorsOptimal(100) == [2, 5]
assert printAllPrimeFactorsOptimal(20) == [2, 5]
```

</div>

<div id="edf4e63b" class="cell markdown"
papermill="{&quot;duration&quot;:1.864e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.564339&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.562475&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Pow (x, n): <https://leetcode.com/problems/powx-n/description> Video
Link: <https://youtu.be/hFWckDXE-K8?si=LH7JBhjzO3jP8NyC>

</div>

<div id="4c3c0361" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.569112Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.568694Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.572255Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.571843Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:7.027e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.573284&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.566257&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def myPowRecursive(x: float, n: int) -> float:
    """
    If n is odd, we make sure that it is even by multiplying result with x and decreasing n by 1.
    If n is even, square x and divide n by 2. For eg: 2 ** 10 => (2 * 2) ** 5

    Go until n == 0

    Time: O (log N)
    """
    if n == 0:
        return 1
    elif n < 0:
        return 1/myPowRecursive(x, -n)
    elif n % 2:
        return x * myPowRecursive(x, n - 1)
    else:
        return myPowRecursive(x * x, n // 2)

# Testing the solution
assert myPowRecursive(2, -3) == 0.125
```

</div>

<div id="e9038b75" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-01T15:54:48.578534Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-01T15:54:48.578055Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-01T15:54:48.581806Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-01T15:54:48.581241Z&quot;}"
papermill="{&quot;duration&quot;:7.407e-3,&quot;end_time&quot;:&quot;2024-06-01T15:54:48.582837&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-01T15:54:48.575430&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/powx-n/submissions/1274302653
def myPow(x: float, n: int) -> float:
    initial, n = n, abs(n)
    result: float = 1
    while n > 0:
        # Odd
        if n % 2 == 1:
            result *= x
            n -= 1
        # Even
        else:
            x *= x
            n //= 2

    return result if initial > 0 else 1 / result

# Testing the solution
assert myPow(2, -3) == pow(2, -3)
```

</div>
