#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

/*
 * C++ STL:
 *
 * 1. Containers
 * 2. Iterators
 * 3. Functions
 * 4. Algorithms
 *
 */

void doSomething(int &a) {
    a += 1;
}

void printVector(vector<int> v) {
    for (auto i: v)
        cout << i << " ";
    cout << endl;
}

int main() {

    /************************* Pairs *************************/
    // Lies inside the utility library
    pair <int, pair <int, double>> p = {1, {1, 2.5}};
    cout << p.first << " " << p.second.first << " " << p.second.second << endl;

    /************************* Vectors *************************/
    // Vector - size, value
    vector <int> v(3, 100);
    for (auto i: v) cout << i << " ";
    cout << endl;
    
    // Inserting into vector
    cout << "Size before insertion " << v.size() << endl;
    v.push_back(10);
    cout << "Size after insertion " << v.size() << endl;
    int prev = v[v.size() - 1];
    cout << "Last element popped: " << prev << endl;
    v.pop_back();
    cout << "Size after pop " << v.size() << endl;

    // Iterators
    cout << "Printing with the help of iterators =>\n";
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        *it = *it + (it - v.begin());
        cout << *it << " ";
    }
    cout << endl;

    // For each loop
    cout << "Printing with for each loop =>\n";
    for (auto i: v)
        cout << i << " ";
    cout << endl;

    // Delete element from vector at a particular index
    v.insert(v.end(), {1, 2, 3}); // 100 101 102 1 2 3
    v.insert(v.begin(), 3, 50); // 50 50 50 100 101 102 1 2 3
    v.erase(v.begin()); // delete single element from start
    v.erase(v.begin(), v.begin() + 2); // Delete multiple: 1, 2, 3
    printVector(v);

    /************************* List *************************/
    // Implemented with the help of a linked list, does not support subscript operator
    // Guaranteed constant insertion and deletion ops at the begin/end
    list<int> l = {1, 2, 3};
    l.push_back(4); // 1 2 3 4
    l.push_front(0); // 0 1 2 3 4
    l.pop_back(); // 0 1 2 3
    l.pop_front(); // 1 2 3
    cout << "Back List: " << l.back() << endl; // 3
    cout << "Front List: " << l.front() << endl; // 1

    /************************* List *************************/
    // Implemented as a dynamic array
    deque<int> d = {1, 2, 3};
    d.push_back(4); // 1 2 3 4
    d.push_front(0); // 0 1 2 3 4
    d.pop_back(); // 0 1 2 3
    d.pop_front(); // 1 2 3
    cout << "Back Deque: " << d.back() << endl; // 3
    cout << "Front Deque: " << d.front() << endl; // 1
    cout << "We have " << d[0] << " at index 0" << endl;

    /************************* Stack *************************/
    stack<int>s;
    s.push(1); // 1
    s.push(2); // 1 2
    s.push(3); // 1 2 3
    cout << "Top of stack: " << s.top() << endl; // 3
    s.pop();
    cout << "Size of stack: " << s.size() << endl; // 2

    /************************* Queue *************************/
    queue<int> q;
    q.push(1); // 1
    q.push(2); // 2, 1
    q.push(3); // 3, 2, 1
    cout << "Top of queue: " << q.back() << endl; // 3
    q.pop();
    cout << "Size of stack: " << q.size() << endl; // 2

    /************************* Priority Queue *************************/
    // Implemented internally with the help of a tree
    // priority_queue<int, vector<int>, greater<int>> pq; // min heap
    priority_queue<int, vector<int>, less<int>> pq; // max heap
    pq.push(2);
    pq.push(1);
    pq.push(0);
    pq.push(4);
    pq.pop(); // 0 is removed
    while (!pq.empty()) {
        int i = pq.top();
        pq.pop();
        cout << i << " ";
    }
    cout << endl;

    /************************* Set *************************/
    // Internally implemented with the help of a tree
    // Everything is sorted, all elements are unique
    set<int> st;
    st.insert(2);
    st.insert(1);
    st.insert(2);
    st.insert(4);
    st.insert(5);

    // Iterate through the set
    for (auto i: st) cout << i << " "; 
    cout << endl;

    // Find returns an iterator that points to the node (if found)
    set<int>::iterator it = st.find(2);
    cout << "2 is present in set: " << (it != st.end()? 1: 0) << endl;

    // Count will return 0 or 1
    cout << "9 is present in set: " << (st.count(9)) << endl;

    // Set erase can delete multiple operators (end not included)
    st.erase(st.find(2), st.find(5)); // 1 5

    // More useful op is the ability to find the lower bound and upper bound
    cout << "Lower bound of 1: " << *st.lower_bound(1) << endl; // 1
    cout << "Upper bound of 1: " << *st.upper_bound(1) << endl; // 1

    /************************* Unordered Set *************************/
    // Same as Set, does not contain lower / upper bounds. Takes O(1) time
    unordered_set<int> ust = {2, 1, 1, 2, 4, 5};
    for (auto it = ust.begin(); it != ust.end(); it++)
        cout << *it << " ";
    cout << endl;

    /************************* Other Datastructures *************************/
    // Ordered version of Map datastructure
    map<int, int> mp;

    unordered_map<string, int> ump;
    ump.insert({"abc", 1});
    ump.insert({"def", 5});
    ump.insert({"xyz", 0});
    ump.erase("xyz"); // returns 1
    for (auto it: ump) {
        cout << "Key: " << it.first << "; Value: " << it.second << endl;
    }
    ump.erase("xyz"); // returns 0

    /************************* Useful Algorithms *************************/
    // Sorting
    int arr[10] = {3, 1, 2, 3, 2, 3, 1, 9, 8, 9};
    sort(arr, arr+3); // sort only first 3 elements (start, end, comparator)
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << endl;

    // Next permutation
    string str = "213";
    do {
        cout << str << endl;
    } while (next_permutation(str.begin(), str.end()));

    return 0;
}
