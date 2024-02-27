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
    duration: 1.702755
    end_time: "2024-02-26T10:07:32.926524"
    environment_variables: {}
    input_path: string-patterns.ipynb
    output_path: string-patterns.ipynb
    parameters: {}
    start_time: "2024-02-26T10:07:31.223769"
    version: 2.4.0
---

<div id="d50974a9" class="cell markdown"
papermill="{&quot;duration&quot;:4.463e-3,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.144353&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.139890&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

Video link:
<https://www.youtube.com/watch?v=tNm_NNSB3_w&list=PLgUwDviBIf0oF6QL8m22w1hIDC1vJ_BHz&index=4>

</div>

<div id="5c29f379" class="cell code" execution_count="1"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.329057Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.328508Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.337395Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.336228Z&quot;}"
papermill="{&quot;duration&quot;:3.5264e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.338911&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.303647&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 1
N = 7
for i in range(N):
    for j in range(N):
        print ("*", end=" ")
    print()
```

<div class="output stream stdout">

    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 
    * * * * * * * 

</div>

</div>

<div id="73698c67" class="cell code" execution_count="2"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.402281Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.402058Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.406833Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.405977Z&quot;}"
papermill="{&quot;duration&quot;:1.1301e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.408586&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.397285&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 2
N = 7
for i in range(N):
    for j in range(i + 1):
        print ("*", end=" ")
    print()
```

<div class="output stream stdout">

    * 
    * * 
    * * * 
    * * * * 
    * * * * * 
    * * * * * * 
    * * * * * * * 

</div>

</div>

<div id="7ea9a66d" class="cell code" execution_count="3"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.416678Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.415964Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.420304Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.419455Z&quot;}"
papermill="{&quot;duration&quot;:1.0261e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.421808&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.411547&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 3
N = 7
for i in range(N):
    for j in range(1, i + 2):
        print (j, end=" ")
    print()
```

<div class="output stream stdout">

    1 
    1 2 
    1 2 3 
    1 2 3 4 
    1 2 3 4 5 
    1 2 3 4 5 6 
    1 2 3 4 5 6 7 

</div>

</div>

<div id="3d16bd53" class="cell code" execution_count="4"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.429489Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.429263Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.434254Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.433401Z&quot;}"
papermill="{&quot;duration&quot;:1.1701e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.436290&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.424589&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 4
N = 7
for i in range(1, N + 1):
    for j in range(1, i + 1):
        print(i, end=" ")
    print()
```

<div class="output stream stdout">

    1 
    2 2 
    3 3 3 
    4 4 4 4 
    5 5 5 5 5 
    6 6 6 6 6 6 
    7 7 7 7 7 7 7 

</div>

</div>

<div id="cdb9bcd3" class="cell code" execution_count="5"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.443766Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.443541Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.448597Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.447577Z&quot;}"
papermill="{&quot;duration&quot;:1.1026e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.450195&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.439169&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 5
N = 7
for i in range(N):
    for j in range(N - i):
        print ("*", end=" ")
    print()
```

<div class="output stream stdout">

    * * * * * * * 
    * * * * * * 
    * * * * * 
    * * * * 
    * * * 
    * * 
    * 

</div>

</div>

<div id="6c3168cd" class="cell code" execution_count="6"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.458246Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.457438Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.462706Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.461838Z&quot;}"
papermill="{&quot;duration&quot;:1.1125e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.464214&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.453089&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 6
N = 7
for i in range(N):
    for j in range(1, N - i + 1):
        print (j, end=" ")
    print()
```

<div class="output stream stdout">

    1 2 3 4 5 6 7 
    1 2 3 4 5 6 
    1 2 3 4 5 
    1 2 3 4 
    1 2 3 
    1 2 
    1 

</div>

</div>

<div id="554c463b" class="cell code" execution_count="7"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.471322Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.471095Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.477000Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.476130Z&quot;}"
papermill="{&quot;duration&quot;:1.1662e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.478732&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.467070&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 7
N = 7
for i in range(1, N + 1):
    for j in range(N - i):
        print("", end=" ")
    for j in range((2 * i) - 1):
        print("*", end="")
    for j in range(N - i):
        print("", end=" ")
    print()
```

<div class="output stream stdout">

          *      
         ***     
        *****    
       *******   
      *********  
     *********** 
    *************

</div>

</div>

<div id="378ca824" class="cell code" execution_count="8"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.487420Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.486499Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.492773Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.491919Z&quot;}"
papermill="{&quot;duration&quot;:1.2893e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.494611&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.481718&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 8
N = 7
for i in range(N, 0, -1):
    for j in range(N - i):
        print("", end=" ")
    for j in range((2 * i) - 1):
        print("*", end="")
    for j in range(N - i):
        print("", end=" ")
    print()
```

<div class="output stream stdout">

    *************
     *********** 
      *********  
       *******   
        *****    
         ***     
          *      

</div>

</div>

<div id="df22abe8" class="cell code" execution_count="9"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.503287Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.502180Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.508862Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.507999Z&quot;}"
papermill="{&quot;duration&quot;:1.2991e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.510653&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.497662&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 9
N = 7
for i in range(1, 2 * N + 1):
    if i <= N:
        for j in range(N - i):
            print ("", end=" ")
        for j in range(i * 2 - 1):
            print ("*", end="")
        for j in range(N - i):
            print ("", end=" ")
    else:
        i_ = (2 * N) - i + 1
        for j in range(N - i_):
            print ("", end=" ")
        for j in range(i_ * 2 - 1):
            print ("*", end="")
        for j in range(N - i_):
            print ("", end=" ")
    print()
```

<div class="output stream stdout">

          *      
         ***     
        *****    
       *******   
      *********  
     *********** 
    *************
    *************
     *********** 
      *********  
       *******   
        *****    
         ***     
          *      

</div>

</div>

<div id="74011d5f" class="cell code" execution_count="10"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.518683Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.518461Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.523751Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.522905Z&quot;}"
papermill="{&quot;duration&quot;:1.1752e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.525687&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.513935&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 10
N = 7
result = []
for i in range(1, N + 1):
    row = []
    for j in range(i):
        row.append("*")
    result.append(" ".join(row))
result = result + result[-2::-1]
print("\n".join(result))
```

<div class="output stream stdout">

    *
    * *
    * * *
    * * * *
    * * * * *
    * * * * * *
    * * * * * * *
    * * * * * *
    * * * * *
    * * * *
    * * *
    * *
    *

</div>

</div>

<div id="13b266fb" class="cell code" execution_count="11"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.533141Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.532913Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.538103Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.537267Z&quot;}"
papermill="{&quot;duration&quot;:1.0959e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.539792&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.528833&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 11
N = 7
for i in range(1, N + 1):
    for j in range(1, i + 1):
        if i % 2 == 0:
            print (1 if j % 2 == 0 else 0, end=" ")
        else:
            print (0 if j % 2 == 0 else 1, end=" ")
    print()
```

<div class="output stream stdout">

    1 
    0 1 
    1 0 1 
    0 1 0 1 
    1 0 1 0 1 
    0 1 0 1 0 1 
    1 0 1 0 1 0 1 

</div>

</div>

<div id="e65cda14" class="cell code" execution_count="12"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.547419Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.547191Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.553043Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.552187Z&quot;}"
papermill="{&quot;duration&quot;:1.1707e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.554663&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.542956&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 12
N = 7
for i in range(1, N + 1):
    for j in range(1, i + 1):
        print (j, end="")
    for j in range((N - i) * 2):
        print ("", end=" ")
    for j in range(i, 0, -1):
        print (j, end="")
    print()
```

<div class="output stream stdout">

    1            1
    12          21
    123        321
    1234      4321
    12345    54321
    123456  654321
    12345677654321

</div>

</div>

<div id="a8369219" class="cell code" execution_count="13"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.562143Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.561917Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.566515Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.565657Z&quot;}"
papermill="{&quot;duration&quot;:1.0741e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.568540&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.557799&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 13
N = 7
rowCount, curr = 1, 1
while rowCount <= N:
    for i in range(curr, curr + rowCount):
        print (i, end=" ")
    print()
    rowCount += 1
    curr = i + 1
```

<div class="output stream stdout">

    1 
    2 3 
    4 5 6 
    7 8 9 10 
    11 12 13 14 15 
    16 17 18 19 20 21 
    22 23 24 25 26 27 28 

</div>

</div>

<div id="0ae579b2" class="cell code" execution_count="14"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.577132Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.576887Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.581752Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.580875Z&quot;}"
papermill="{&quot;duration&quot;:1.1583e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.583271&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.571688&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 14
N = 7
for i in range(1, N + 1):
    for j in range(ord("A"), ord("A") + i):
        print (chr(j), end=" ")
    print()
```

<div class="output stream stdout">

    A 
    A B 
    A B C 
    A B C D 
    A B C D E 
    A B C D E F 
    A B C D E F G 

</div>

</div>

<div id="c93c8fe8" class="cell code" execution_count="15"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.590816Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.590592Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.595023Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.594157Z&quot;}"
papermill="{&quot;duration&quot;:1.0092e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.596556&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.586464&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 15
N = 7
for i in range(N):
    for j in range(N - i):
        print(chr(ord("A") + j), end=" ")
    print()
```

<div class="output stream stdout">

    A B C D E F G 
    A B C D E F 
    A B C D E 
    A B C D 
    A B C 
    A B 
    A 

</div>

</div>

<div id="f3424ddb" class="cell code" execution_count="16"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.604747Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.604527Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.609330Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.608456Z&quot;}"
papermill="{&quot;duration&quot;:1.1036e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.610830&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.599794&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 16
N = 7
for i in range(N):
    for j in range(i + 1):
        print(chr(ord("A") + i), end="")
    print()
```

<div class="output stream stdout">

    A
    BB
    CCC
    DDDD
    EEEEE
    FFFFFF
    GGGGGGG

</div>

</div>

<div id="5c35d73e" class="cell code" execution_count="17"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.619785Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.619082Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.624951Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.624048Z&quot;}"
papermill="{&quot;duration&quot;:1.2082e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.626408&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.614326&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 17
N = 7
for i in range(1, N + 1):
    for j in range(N - i):
        print ("", end=" ")

    curr = 0
    for j in range(i * 2 - 1):
        print (chr(ord("A") + curr), end="")
        if j < i - 1:
            curr += 1
        else:
            curr -= 1

    for j in range(N - i):
        print ("", end=" ")
    print()
```

<div class="output stream stdout">

          A      
         ABA     
        ABCBA    
       ABCDCBA   
      ABCDEDCBA  
     ABCDEFEDCBA 
    ABCDEFGFEDCBA

</div>

</div>

<div id="a59d7343" class="cell code" execution_count="18"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.634147Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.633922Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.638227Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.637334Z&quot;}"
papermill="{&quot;duration&quot;:1.0074e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.639746&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.629672&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 18
N = 7
for i in range(N):
    for j in range(N - i - 1, N):
        print (chr(ord("A") + j), end=" ")
    print()
```

<div class="output stream stdout">

    G 
    F G 
    E F G 
    D E F G 
    C D E F G 
    B C D E F G 
    A B C D E F G 

</div>

</div>

<div id="060aa997" class="cell code" execution_count="19"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.648901Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.648388Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.654241Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.653319Z&quot;}"
papermill="{&quot;duration&quot;:1.2806e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.655986&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.643180&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 19
N = 7
for i in range(2 * N):
    if i < N:
        i_ = i
    else:
        i_ = (2 * N) - i - 1

    for j in range(N - i_):
        print("*", end="")
    for j in range(i_ * 2):
        print(" ", end="")
    for j in range(N - i_):
        print("*", end="")
    print()
```

<div class="output stream stdout">

    **************
    ******  ******
    *****    *****
    ****      ****
    ***        ***
    **          **
    *            *
    *            *
    **          **
    ***        ***
    ****      ****
    *****    *****
    ******  ******
    **************

</div>

</div>

<div id="ae396acb" class="cell code" execution_count="20"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.664173Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.663950Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.669202Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.668325Z&quot;}"
papermill="{&quot;duration&quot;:1.1456e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.670917&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.659461&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 20
N = 7
for i in range(1, 2 * N):
    if i <= N:
        i_ = i
    else:
        i_ = (2 * N) - i 

    for j in range(i_):
        print("*", end="")
    for j in range(2 * (N - i_)):
        print (" ", end="")
    for j in range(i_):
        print("*", end="")
    print()
```

<div class="output stream stdout">

    *            *
    **          **
    ***        ***
    ****      ****
    *****    *****
    ******  ******
    **************
    ******  ******
    *****    *****
    ****      ****
    ***        ***
    **          **
    *            *

</div>

</div>

<div id="f6cec386" class="cell code" execution_count="21"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.679468Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.678924Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.683816Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.682963Z&quot;}"
lines_to_next_cell="1"
papermill="{&quot;duration&quot;:1.1516e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.685791&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.674275&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 21
N = 7
for i in range(N):
    if i == 0 or i == N - 1:
        for j in range(N):
            print ("*", end="")
    else:
        print ("*", end="")
        for j in range(N - 2):
            print(" ", end="")
        print ("*", end="")
    print()
```

<div class="output stream stdout">

    *******
    *     *
    *     *
    *     *
    *     *
    *     *
    *******

</div>

</div>

<div id="5c65598f" class="cell code" execution_count="22"
execution="{&quot;iopub.execute_input&quot;:&quot;2024-02-26T10:07:32.693891Z&quot;,&quot;iopub.status.busy&quot;:&quot;2024-02-26T10:07:32.693666Z&quot;,&quot;iopub.status.idle&quot;:&quot;2024-02-26T10:07:32.700968Z&quot;,&quot;shell.execute_reply&quot;:&quot;2024-02-26T10:07:32.700111Z&quot;}"
papermill="{&quot;duration&quot;:1.3558e-2,&quot;end_time&quot;:&quot;2024-02-26T10:07:32.702943&quot;,&quot;exception&quot;:false,&quot;start_time&quot;:&quot;2024-02-26T10:07:32.689385&quot;,&quot;status&quot;:&quot;completed&quot;}"
tags="[]">

``` python
# Pattern - 22
def pattern22(N: int):
    """
    0 - [[]]
    1 - [[1]]
    2 - [[2,2,2],[2,1,2],[2,2,2]]
    3 - [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
    """

    def backtrack(n: int) -> list[list[str]]:
        if n == 1:
            return [['1'.zfill(max_char_length)]]
        else:
            prev = backtrack(n - 1)
            curr, length = str(n).zfill(max_char_length), 2 * n - 1
            curr_row = [curr for _ in range(length)]
            next_: list[list[str]] = []

            next_.append(curr_row)
            pad_length = (length - len(prev[0])) // 2
            for row in prev:
                next_.append([curr for _ in range(pad_length)] + row + [curr for _ in range(pad_length)])
            next_.append(curr_row)

            return next_

    max_char_length = len(str(N))
    result = backtrack(N)
    for row in result:
        print(" ".join(row))
    print()

# Testing the function
pattern22(7)
```

<div class="output stream stdout">

    7 7 7 7 7 7 7 7 7 7 7 7 7
    7 6 6 6 6 6 6 6 6 6 6 6 7
    7 6 5 5 5 5 5 5 5 5 5 6 7
    7 6 5 4 4 4 4 4 4 4 5 6 7
    7 6 5 4 3 3 3 3 3 4 5 6 7
    7 6 5 4 3 2 2 2 3 4 5 6 7
    7 6 5 4 3 2 1 2 3 4 5 6 7
    7 6 5 4 3 2 2 2 3 4 5 6 7
    7 6 5 4 3 3 3 3 3 4 5 6 7
    7 6 5 4 4 4 4 4 4 4 5 6 7
    7 6 5 5 5 5 5 5 5 5 5 6 7
    7 6 6 6 6 6 6 6 6 6 6 6 7
    7 7 7 7 7 7 7 7 7 7 7 7 7

</div>

</div>
