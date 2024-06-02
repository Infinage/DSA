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
    duration: 1.504733
    end_time: "2024-06-02T17:58:18.739105"
    environment_variables: {}
    input_path: study/striver-A2Z/15-math.ipynb
    output_path: study/striver-A2Z/15-math.ipynb
    parameters: {}
    start_time: "2024-06-02T17:58:17.234372"
    version: 2.6.0
---

<div id="3ad0b29c" class="cell markdown"
papermill="{&quot;duration&quot;:3.923e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.365285&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.361362&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

#### Useful imports, functions

</div>

<div id="9961e56c" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.372400Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.372058Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.377485Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.377056Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0238e-2,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.378602&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.368364&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.385677Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.385288Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.390914Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.390393Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0243e-2,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.391941&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.381698&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.001e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.397896&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.394895&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Print all divisors of a number Video Link:
<https://youtu.be/Ae_Ag_saG9s?si=ehTTFV59EVSKChY2>

</div>

<div id="fec7e081" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.404688Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.404417Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.407980Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.407522Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.261e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.409114&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.400853&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.417065Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.416639Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.421260Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.420765Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.366e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.422383&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.413017&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:3.022e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.428424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.425402&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Check if number is prime or not Video Link:
<https://youtu.be/MJcckSfoYdI?si=AkCS-hvE9foXQ0KX>

</div>

<div id="823de68c" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.435411Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.434968Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.439143Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.438712Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.86e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.440250&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.431390&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.914e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.446243&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.443329&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Print all prime factors of a number Video Link:
<https://youtu.be/LT7XhVdeRyg?si=OTryhgbEtQODhgBJ>

</div>

<div id="0f0aa99e" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.453476Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.453037Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.457954Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.457484Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.636e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.459033&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.449397&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.465939Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.465556Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.469308Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.468793Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.348e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.470346&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.461998&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.477474Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.477134Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.480984Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.480572Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.63e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.482047&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.473417&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
papermill="{&quot;duration&quot;:2.979e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.488053&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.485074&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Pow (x, n): <https://leetcode.com/problems/powx-n/description> Video
Link: <https://youtu.be/hFWckDXE-K8?si=LH7JBhjzO3jP8NyC>

</div>

<div id="4c3c0361" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.495064Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.494632Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.498535Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.498098Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.601e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.499605&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.491004&quot;,&quot;status&quot;:&quot;completed&quot;}"
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
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.509175Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.508708Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.512771Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.512220Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.133e-2,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.513944&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.502614&quot;,&quot;status&quot;:&quot;completed&quot;}"
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

<div id="11ca53d4" class="cell markdown"
papermill="{&quot;duration&quot;:3.332e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.520482&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.517150&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Print all primes uptil N Video link:
<https://youtu.be/g5Fuxn_AvSk?si=cwI7gb6AFroVePX9>

</div>

<div id="27f1cd7f" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.528122Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.527735Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.532500Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.532005Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.879e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.533597&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.523718&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllPrimesBrute(N: int) -> list[int]:
    # Time: O(N x sqrt N)
    def _is_prime(num: int) -> bool:
        cnt, i = 0, 1
        while i * i <= num:
            if num % i == 0:
                cnt += 1 if i == num // i else 2
            i += 1

        return cnt == 2

    # Iterate through all and check for primality
    result: list[int] = []
    for n in range(2, N + 1):
        if _is_prime(n):
            result.append(n)
    return result

# Testing the solution
assert printAllPrimesBrute(50) == [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
assert printAllPrimesBrute(20) == [2,3,5,7,11,13,17,19]
```

</div>

<div id="a90bd365" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.540742Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.540472Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.545017Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.544404Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.271e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.546059&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.536788&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllPrimesBetter(N: int) -> list[int]:
    primes: dict[int, bool] = dict()
    i = 2
    while i <= N:
        if primes.get(i, True):
            primes[i] = True
            j = 2
            while i * j <= N:
                primes[i * j] = False
                j += 1
        i += 1

    return [i for i in primes if primes[i]]

# Testing the solution
assert printAllPrimesBetter(50) == [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
assert printAllPrimesBetter(20) == [2,3,5,7,11,13,17,19]
```

</div>

<div id="ce654373" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.553071Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.552632Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.557494Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.557059Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.452e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.558527&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.549075&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def printAllPrimesOptimal(N: int) -> list[int]:
    """
    When i = 2, we can run j = 2 all the way until i * j > N.
    When i = 3, we don't have to start from j = 2 since it would have already been marked.
    Whhen i = 5, we don't have to start from j = 2, 3, 4 since they would have already been marked in the previous iterations.
    Therefore for any outer loop i, j can start with j = i => i = 3, j = 3; i = 7, j = 7, etc

    We run the outer loop until i <= N and inner loop until i * j <= N. Say N = 30, when i becomes 6 we already start at a point 6 * 6 = 36 > 30.
    Therefore we don't have to iterate beyond sqrt N in the outer loop
    """
    # O(N)
    primes: list[bool] = [True for i in range(N + 1)]
    primes[0] = primes[1] = False

    # O(N log (log N))
    i = 2
    while i * i <= N: # Optimized
        if primes[i]:
            j = i # Optimized
            while i * j <= N:
                primes[i * j] = False
                j += 1
        i += 1

    # O(N)
    return [i for i in range(N + 1) if primes[i]]

# Testing the solution
assert printAllPrimesOptimal(50) == [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
assert printAllPrimesOptimal(20) == [2,3,5,7,11,13,17,19]
```

</div>

<div id="6873f617" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.565963Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.565529Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.569883Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.569427Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:9.347e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.570927&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.561580&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# https://leetcode.com/problems/count-primes/submissions/1275281461/
def printAllPrimes(N: int) -> list[int]:
    # O(N) Storage space to store precomputed primality results
    soe: list[bool] = [True] * (N + 1)
    soe[0] = soe[1] = False

    i = 2
    while i * i <= N:
        if soe[i]: # Python specific optimization
            soe[i*i:N+1:i] = [False] * len(soe[i*i:N+1:i])
        i += 1

    return [i for i in range(N + 1) if soe[i]]

# Testing the solution
assert printAllPrimes(50) == [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
assert printAllPrimes(20) == [2,3,5,7,11,13,17,19]
```

</div>

<div id="55ffb714" class="cell markdown"
papermill="{&quot;duration&quot;:3.041e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.577120&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.574079&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Count number of primes between range Video Link:
<https://youtu.be/os82DjD2-MA?si=SB7Htn3Y9JjmuPyP>

</div>

<div id="b2cac251" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.584019Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.583815Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.589420Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.589001Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.0322e-2,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.590424&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.580102&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def countPrimesInRange(queries: list[tuple[int, int]]) -> list[int]:
    """
    Brute: For each q, iterate between L and R and count primes: O(Q x R x sqrt R)
    Better: Precompute primes using SOE reducing the sqrt R part: O(Q x R) + O(R log log R)

    Optimal solution is a combination of using prefix sum and seive of erastosthenes
    Time: O(Q) + O(R log log R) + O(R) + O(Q)
    """

    # max_ value of right range
    max_ = max(map(lambda x: x[1], queries))

    # Compute the primes using Seive of erastosthenes
    primes: list[int] = [True] * (max_ + 1)
    primes[0] = primes[1] = False
    i = 2
    while i * i <= max_:
        if primes[i]:
            primes[i*i::i] = [False] * len(primes[i*i::i])
        i += 1

    # Use prefix sum to compute the right
    cnt, right = 0, []
    for i in range(max_ + 1):
        cnt += primes[i]
        right.append(cnt)

    # Prefix sum
    result: list[int] = []
    for L, R in queries:
        result.append(right[R] - (right[L - 1] if L > 0 else 0))

    return result

# Testing the solution
assert countPrimesInRange([(1,10),(5,10),(9,50),(30,50),(3,7),(0,10)]) == [4,2,11,5,3,4]
```

</div>

<div id="73b1d0d4" class="cell markdown"
papermill="{&quot;duration&quot;:2.993e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.596443&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.593450&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Prime factorisation of a number Video Link:
<https://youtu.be/glKWkmKFlMw?si=q6r9kMg3FDzfebGo>

</div>

<div id="6cd6e86e" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.603323Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.602985Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.607141Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.606702Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:8.806e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.608251&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.599445&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def prime_factorise_better(queries: list[int]) -> list[list[int]]:
    results: list[list[int]] = []
    for N in queries:
        result: list[int] = []
        i = 2
        while i * i <= N:
            while N % i == 0:
                result.append(i)
                N //= i
            i += 1

        if N != 1:
            result.append(N)

        results.append(result)

    return results

# Testing the solution
assert prime_factorise_better([36, 45]) == [[2,2,3,3], [3,3,5]]
```

</div>

<div id="65fb7ed1" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-06-02T17:58:18.615178Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-06-02T17:58:18.614894Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-06-02T17:58:18.619643Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-06-02T17:58:18.619180Z&quot;}"
papermill="{&quot;duration&quot;:9.352e-3,&quot;end_time&quot;:&quot;2024-06-02T17:58:18.620678&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-06-02T17:58:18.611326&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
def prime_factorise_optimal(queries: list[int]) -> list[list[int]]:
    """
    Optimal solution involves using an approach similar to seive of erastosthenes.

    Time: O(N log log N) + O(Q * log N)
    Space: O(N)
    """
    # Compute the SPF (Smallest Prime factor)
    max_ = max(queries)
    SPF: list[int] = [i for i in range(max_ + 1)]
    i = 2
    while i * i <= max_:
        if SPF[i] == i:
            j = i
            while i * j <= max_:
                if SPF[i * j] == i * j:
                    SPF[i * j] = i
                j += 1
        i += 1

    # Iterate through the queries and store the results
    # Using SPF lets us find the smallest factor in O(1) time.
    # As we continue dividing the number we don't have to iterate through
    # non divisible numbers
    results: list[list[int]] = []
    for N in queries:
        result: list[int] = []
        while N > 1:
            result.append(SPF[N])
            N //= SPF[N]
        results.append(result)

    return results

# Testing the solution
assert prime_factorise_optimal([36, 45, 46]) == [[2,2,3,3], [3,3,5], [2,23]]
```

</div>
