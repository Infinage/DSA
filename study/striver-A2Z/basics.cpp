#include <functional>
#include <iostream>
#include <ranges>
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
#include <tuple>
#include <format>

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

/*****************************************************************************/
/******************** Competitive Programming helpers ************************/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val, ListNode* next = nullptr): val(val), next(next) {}

    static ListNode* from(const std::vector<int>& nums) {
        if (nums.size() == 0)
            return nullptr;

        else {
            ListNode* head = new ListNode(nums[0]);
            ListNode* curr = head;
            for (std::size_t i = 1; i < nums.size(); i++) {
                ListNode* next = new ListNode(nums[i]);
                curr->next = next;
                curr = next;
            }
            return head;
        }
    }

    static void destroy(ListNode* head) {
        while (head != nullptr) {
            ListNode* next = head->next;
            delete head;
            head = next;
        }
    }

    static void print(ListNode* head) {
        ListNode *curr = head;
        std::cout << "[";
        while (curr != nullptr) {
            std::cout << curr->val << ",";
            curr = curr->next;
        }
        std::cout << (head == nullptr? "]\n": "\b]\n");
    }
};

struct BinaryTreeNode {
    int val;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(int val, BinaryTreeNode* left = nullptr, BinaryTreeNode* right = nullptr):
        val(val), left(left), right(right) {};

    static BinaryTreeNode* from(std::vector<std::string>& nums) {
        int idx = -1;
        bool isLeft = false;
        std::vector<BinaryTreeNode*> nodes;
        for (std::string num: nums) {
            // Trim any whitespace
            num.erase(num.begin(), std::ranges::find_if_not(num, [](char ch) { return std::isspace(ch); }));
            num.erase(std::ranges::find_if_not(num | std::views::reverse, [](char ch) { return std::isspace(ch); }).base(), num.end());

            // Check only nums and +/- signs
            bool isNum = (
                num.size() > 0 && (num[0] == '-' || num[0] == '+' || std::isdigit(num[0]))
                && std::ranges::all_of(num | std::ranges::views::drop(1), [](char ch) { return std::isdigit(ch);} )
            );

            BinaryTreeNode* node = isNum? new BinaryTreeNode(std::stoi(num)): nullptr;
            if (idx >= 0) {
                if (isLeft)
                    nodes[(std::size_t) idx]->left = node;
                else
                    nodes[(std::size_t) idx]->right = node;
            }
            nodes.push_back(node);
            idx += isLeft? 0: 1;
            isLeft = !isLeft;
        }

        return nums.size() > 0? nodes[0]: nullptr;
    }

    static void print(BinaryTreeNode* root) {
        std::queue<BinaryTreeNode*> queue({root});
        std::cout << "[";
        while (!queue.empty()) {
            BinaryTreeNode* curr = queue.front();
            queue.pop();
            if (curr == nullptr)
                std::cout << -1 << ",";
            else {
                std::cout << curr->val << ",";
                queue.push(curr->left);
                queue.push(curr->right);
            }
        }
        std::cout << (root == nullptr? "]\n": "\b]\n");
    }

    static void destroy(BinaryTreeNode* root) {
        std::queue<BinaryTreeNode*> queue;
        if (root != nullptr)
            queue.push(root);

        while (!queue.empty()) {
            BinaryTreeNode* curr = queue.front();
            queue.pop();
            if (curr->left != nullptr)
                queue.push(curr->left);
            if (curr->right != nullptr)
                queue.push(curr->right);
            delete curr;
        }
    }
};

struct pair_hash {
    /*
     * Struct for using Pairs inside unordered_set, unordered_maps
     * Use this as a template argument when declaring the unordered_*
     *
     * unordered_set<pair<int, int>, pair_hash> hs;
     */
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return (v.first * 31) + v.second;
    }
};

struct hash_tuple {
    /*
     * Can be used during initialization like this:
     * unordered_set<tuple<int, int>, hash_tuple> hs;
     */
    inline std::size_t operator()(const std::tuple<int,int>& v) const {
        return (std::get<0>(v) * 31) + std::get<1>(v);
    }
};

struct hash_vector {
    /*
     * Can be used during initialization like this:
     * unordered_set<vector<int>, hash_tuple> hs;
     */
    std::size_t operator() (const std::vector<int>& vec) const {
        std::size_t seed = vec.size();
        for (int n: vec) {
            n ^= ((n >> 16) ^ n) * 0x45d9f3b;
            n ^= ((n >> 16) ^ n) * 0x45d9f3b;
            n ^= ((n >> 16) ^ n);
            seed ^= n + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

std::vector<int> parseListInt() {
    /*
     * Parse 1D list from std input, leetcode style
     * For eg: [1,2,3,10,20,1002]
     */
    std::string buffer;
    getline(std::cin, buffer);
    std::vector<int> nums;
    std::string acc = "";
    for (char ch: buffer) {
        if (isdigit(ch))
            acc += ch;
        else if (ch == ',' || ch == ']') {
            nums.push_back(std::stoi(acc));
            acc = "";
        }

    }
    return nums;
}

std::vector<std::string> parseListString() {
    /*
     * Parse 1D list from std input, leetcode style
     * For eg: ["we", "say", ":", "yes"]
     * WARNING: We assume that the input string does not contain double quotes in them ('"')
     */
    std::string buffer;
    std::getline(std::cin, buffer);
    buffer = buffer.substr(1, buffer.size() - 2);

    std::vector<std::string> result;
    std::string acc {""};
    bool flag = false;
    for (char ch: buffer) {
        if (ch == '"') {
            if (!flag)
                flag = true;
            else {
                result.push_back(acc);
                acc = "";
                flag = false;
            }
        } else if (flag) {
            acc += ch;
        }
    }
    return result;
}

std::vector<std::vector<int>> parse2DList() {
    /*
     * Parse 2D list from std input, leetcode style
     * For eg: [[1,2,3],[1,2,301,1]]
     */
    std::vector<std::vector<int>> result;
    std::string buffer, acc = "";
    getline(std::cin, buffer);
    buffer = buffer.substr(1, buffer.size() - 2);
    for (char ch: buffer) {
        if (ch == '[') {
            result.push_back(std::vector<int>());
            acc = "";
        } else if (isdigit(ch)) {
            acc += ch;
        } else if ((ch == ',' || ch == ']') && acc.size() >= 1) {
            result.back().push_back(std::stoi(acc));
            acc = "";
        }
    }
    return result;
}

void print2DList(std::vector<std::vector<int>>& nums, int numWidth = 5) {
    for(std::vector<int>& row: nums) {
        std::cout << "[";
        for (int n: row)
            std::cout << std::format("{:>{}}", n, numWidth) << " ";
        std::cout << "\b]\n";
    }
}

class Trie{
public:
    int wordCount, prefixCount;
    std::array<Trie*, 26> next;

    Trie() {
        std::ranges::fill(next, nullptr);
        wordCount = 0;
        prefixCount = 0;
    }

    static std::size_t ord(char ch) {
        return (std::size_t) ch - 'a';
    }

    void insert(std::string &word){
        prefixCount++;
        Trie *curr = this;
        for (char ch: word) {
            if (curr->next[ord(ch)] == nullptr)
                curr->next[ord(ch)] = new Trie();
            curr = curr->next[ord(ch)];
            curr->prefixCount++;
        }
        curr->wordCount++;
    }

    void erase(std::string &word){
        Trie *curr = this;
        std::stack<std::pair<char, Trie*>> stk({{'*', curr}});
        for (char ch: word) {
            if (curr == nullptr)
                return;
            curr = curr->next[ord(ch)];
            stk.push({ch, curr});
        }

        if (curr != nullptr && !stk.empty() && curr->wordCount > 0) {
            stk.top().second->wordCount--;
            while (!stk.empty()) {
                auto &[ch, curr] = stk.top();
                stk.pop();
                curr->prefixCount--;
                if (curr->prefixCount == 0 && std::ranges::all_of(curr->next, [](Trie *t) { return t == nullptr; }) && ch != '*') {
                    stk.top().second->next[ord(ch)] = nullptr;
                    delete curr;
                }
            }
        }
    }

    static Trie *iterate(std::string &word, Trie *start) {
        Trie *curr = start;
        for (char ch: word) {
            if (curr->next[ord(ch)] == nullptr)
                return nullptr;
            curr = curr->next[ord(ch)];
        }
        return curr;
    }

    int countWordsEqualTo(std::string &word){
        Trie *endNode = iterate(word, this);
        return endNode == nullptr? 0: endNode->wordCount;
    }

    int countWordsStartingWith(std::string &word){
        Trie *endNode = iterate(word, this);
        return endNode == nullptr? 0: endNode->prefixCount;
    }

    static void destroy(Trie *root) {
        std::stack<Trie*> stk({root});
        while (!stk.empty()) {
            Trie *curr = stk.top();
            stk.pop();
            for (Trie *nxt: curr->next)
                if (nxt != nullptr)
                    stk.push(nxt);
            delete curr;
        }
    }
};

class BitFrequency {
    private:
        using FREQ_T = std::array<int, 64>;
        FREQ_T freq;

    public:
        BitFrequency() { freq.fill(0); }

        void operator+=(const int n) {
            for (std::size_t i {0}; i < 64; i++)
                freq[i] += (n >> i) & 1;
        }

        void operator-=(const int n) {
            for (std::size_t i {0}; i < 64; i++)
                freq[i] -= (n >> i) & 1;
        }
        
        int getValue() {
            int result{0};
            for (std::size_t i{0}; i < 64; i++)
                result |= ((freq[i] > 0? 1: 0) << i); 
            return result;
        }
};

/*****************************************************************************/


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
    for(int n: v)
        std::cout << n << ", ";
    std::cout << "\n";

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
