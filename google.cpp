#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class MinStack {
   private:
    list<int> lst;
    list<int>::iterator minVal;

    void updateMin() {
        int tempMin = INT_MAX;
        for (int val : lst) {
            tempMin = min(tempMin, val);
        }
        minVal = find(lst.begin(), lst.end(), tempMin);
    }

   public:
    MinStack() {}

    void push(int val) {
        if (lst.empty()) {
            lst.push_back(val);
            minVal = lst.begin();
            return;
        }
        // if the list is not empty
        lst.push_back(val);
        if (val < *minVal) {
            minVal = prev(lst.end());
        }
        return;
    }

    void pop() {
        lst.erase(prev(lst.end()));
        updateMin();
    }

    int top() { return *prev(lst.end()); }

    int getMin() { return *minVal; }
};

class MyStack {
   private:
    queue<int> q;

   public:
    MyStack() {};

    void push(int x) {
        q.push(x);
        int currentSize = q.size();
        for (size_t i = 0; i < currentSize - 1; ++i) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int topElement = q.front();
        q.pop();
        return topElement;
    }

    int top() { return q.front(); }

    bool empty() { return q.empty(); }
};

class MyQueue {
   private:
    stack<int> s;

   public:
    MyQueue() {}

    void push(int x) {
        stack<int> temp;
        while (!s.empty()) {
            temp.push(s.top());
            s.pop();
        }
        s.push(x);
        while (!temp.empty()) {
            s.push(temp.top());
            temp.pop();
        }
    }

    int pop() {
        int topElem = s.top();
        s.pop();
        return topElem;
    }

    int peek() { return s.top(); }

    bool empty() { return s.empty(); }
};

class MovingAverage {
   private:
    int windowSize;
    deque<int> dq;
    int runningSum{};
    int count{};

   public:
    MovingAverage(int size) { windowSize = size; }

    double next(int val) {
        if (count < windowSize) {
            dq.push_back(val);
            runningSum += val;
            ++count;
            return (double)runningSum / count;
        }
        runningSum -= dq.front();
        dq.pop_front();
        runningSum += val;
        dq.push_back(val);
        return (double)runningSum / count;
    }
};

class Logger {
   private:
    unordered_map<string, int> m;  // {message, lastSeen}

   public:
    Logger() {}

    bool shouldPrintMessage(int timestamp, string message) {
        auto item = m.find(message);
        if (item == m.end()) {
            m.insert({message, timestamp});
            return true;
        } else if (item->second > timestamp - 10) {
            return false;
        } else {
            item->second = timestamp;
            return true;
        }
    }
};

class RecentCounter {
   private:
    deque<int> dq;
    int count{};

   public:
    RecentCounter() {}
    int ping(int t) {
        ++count;
        dq.push_back(t);
        int start = t - 3000;
        while (!dq.empty()) {
            if (dq.front() < start) {
                dq.pop_front();
                --count;
                continue;
            }
            break;
        }
        return count;
    }
};
class LRUCache {
   private:
    int cap;
    list<int> q;
    unordered_map<int, pair<int, list<int>::iterator>> mp;

    void makeMostRecent(int key) {
        q.erase(mp[key].second);
        q.push_back(key);
        mp[key].second = prev(q.end());
    }

   public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (mp.find(key) == mp.end()) return -1;
        makeMostRecent(key);
        return mp[key].first;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            mp[key].first = value;
            makeMostRecent(key);
            return;
        }
        if (mp.size() == cap) {
            int lru = q.front();
            mp.erase(lru);
            q.pop_front();
        }
        q.push_back(key);
        mp[key] = {value, prev(q.end())};
    }
};

class BSTIterator {
   private:
    vector<int> toList;

    int pos{};

    void dfs(TreeNode* node) {
        if (node == NULL) return;
        dfs(node->left);
        this->toList.push_back(node->val);
        dfs(node->right);
        return;
    }

   public:
    BSTIterator(TreeNode* root) { dfs(root); }

    int next() { return toList[pos++]; }

    bool hasNext() { return pos < toList.size(); }
};

class Trie {
   private:
    struct TrieNode {
        char val;
        bool end;
        TrieNode* next[26];
        TrieNode() {
            this->val = 0;
            this->end = false;
            for (int i = 0; i < 26; ++i) this->next[i] = nullptr;
        }
    };
    TrieNode* root;

   public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->next[c - 'a'] == nullptr) {
                TrieNode* new_node = new TrieNode();
                new_node->val = c;
                node->next[c - 'a'] = new_node;
            }
            node = node->next[c - 'a'];
        }
        // every letter is there, then set the end as true;
        node->end = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->next[c - 'a'] == nullptr) return false;
            node = node->next[c - 'a'];
        }
        return node->end;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->next[c - 'a'] == nullptr) return false;
            node = node->next[c - 'a'];
        }
        return node != nullptr;
    }
};

class Codec {
   private:
    char delimiter;

   public:
    Codec() { this->delimiter = 2; }

    string encode(vector<string>& strs) {
        string ans = "";
        for (const auto& s : strs) {
            ans += s;
            ans += this->delimiter;
        }
        ans.back() = '\0';
        return ans;
    }

    vector<string> decode(string s) {
        vector<string> ans;
        int l{};
        int r{};
        for (; r < s.size(); ++r) {
            if (s[r] != this->delimiter) continue;
            ans.push_back(s.substr(l, r - l));
            l = r + 1;
        }
        ans.push_back(s.substr(l, r - l));
        return ans;
    }
};

class NumMatrix {
   private:
    vector<vector<int>> prefixSum;

   public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        this->prefixSum.assign(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= m; ++i) prefixSum[i][0] = 0;
        for (int j = 0; j <= n; ++j) prefixSum[0][j] = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] -
                                  prefixSum[i - 1][j - 1] +
                                  matrix[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefixSum[row2 + 1][col2 + 1] - prefixSum[row2 + 1][col1] -
               prefixSum[row1][col2 + 1] + prefixSum[row1][col1];
    }
};

class HitCounter {
   private:
    vector<int> stamps;
    int curLeft;
    int curRight;

   public:
    HitCounter() {
        this->curLeft = 0;
        this->curRight = -1;
    }

    void hit(int timestamp) {
        this->stamps.push_back(timestamp);
        ++this->curRight;
    }

    int getHits(int timestamp) {
        while (this->curLeft <= this->curRight &&
               this->stamps[this->curLeft] <= timestamp - 300) {
            ++this->curLeft;
        }
        return this->curRight - this->curLeft + 1;
    }
};

class RandomizedSet {
   private:
    vector<int> vals;
    unordered_map<int, int> mp;  // val: index

   public:
    RandomizedSet() {}

    bool insert(int val) {
        if (mp.contains(val)) return false;
        vals.push_back(val);
        mp[val] = vals.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (!mp.contains(val)) return false;
        mp[vals.back()] = mp[val];
        swap(vals[mp[val]], vals[vals.size() - 1]);
        vals.pop_back();
        mp.erase(val);
        return true;
    }

    int getRandom() { return vals[rand() % vals.size()]; }
};

class google {
   public:
    ListNode* deleteDuplicates_(ListNode* head) {
        ListNode* l = head;
        if (l == NULL) return head;
        ListNode* r = head->next;
        while (r != NULL) {
            if (l->val == r->val) {
                l->next = r->next;
                r->next = NULL;
                r = l->next;
            } else {
                l = r;
                r = r->next;
            }
        }
        return head;
    }

    bool canAttendMeetings(vector<vector<int>>& intervals) {
        // SORT CAN BE FASTER, EVEN PLUS THE SORT TIME
        // int n = intervals.size();
        // for (int j = 1; j < n; ++j) {
        //     for (int i = 0; i < j; ++i) {
        //         int start = intervals[j][0];
        //         int end = intervals[j][1];
        //         int ss = intervals[i][0];
        //         int ee = intervals[i][1];
        //         if (!(end <= ss || start >= ee)) return false;
        //     }
        // }
        // return true;
        int n = intervals.size();
        if (n <= 1) return true;
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < n - 1; ++i) {
            if (intervals[i + 1][0] < intervals[i][1]) return false;
        }
        return true;
    }

    bool areSentencesSimilar(vector<string>& sentences1,
                             vector<string>& sentences2,
                             vector<vector<string>>& similarPairs) {
        int n = sentences1.size();
        if (n != sentences2.size()) return false;
        unordered_map<string, vector<string>> map;
        for (vector<string>& v : similarPairs) {
            map[v[0]].push_back(v[1]);
            map[v[1]].push_back(v[0]);
        }
        for (int i = 0; i < n; ++i) {
            if (sentences1[i] == sentences2[i]) continue;
            auto item = map.find(sentences1[i]);
            if (item == map.end()) return false;
            if ((find(item->second.begin(), item->second.end(),
                      sentences2[i])) != item->second.end())
                continue;
            return false;
        }
        return true;
    }

    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int n = candies.size();
        vector<bool> ans(n, false);
        int maxCandy{};
        for (int i : candies) maxCandy = max(maxCandy, i);
        for (int i = 0; i < n; ++i)
            if (candies[i] + extraCandies >= maxCandy) ans[i] = true;
        return ans;
    }

    bool kLengthApart(vector<int>& nums, int k) {
        int l{};
        while (l < nums.size() && nums[l] == 0) ++l;
        int r = l + 1;
        for (; r < nums.size(); ++r) {
            if (nums[r] == 0) continue;
            if (r - l - 1 < k) return false;
            l = r;
        }
        return true;
    }

    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(n * 2);
        for (int i = 0; i < n; ++i) {
            ans[i * 2] = nums[i];
            ans[i * 2 + 1] = nums[n + i];
        }
        return ans;
    }

    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            int j = i + 1;
            for (; j < n; ++j) {
                if (prices[j] > prices[i]) continue;
                ans[i] = prices[i] - prices[j];
                break;
            }
            if (j == n) ans[i] = prices[i];
        }
        return ans;
    }

    bool check(vector<int>& nums) {
        int n = nums.size();
        int i{};
        for (; i < n - 1; ++i) {
            if (nums[i + 1] < nums[i]) break;
        }
        if (i == n - 1) return true;
        ++i;
        for (; i < n - 1; ++i) {
            if (nums[i + 1] < nums[i]) break;
        }
        if (i != n - 1) return false;
        return nums[n - 1] <= nums[0];
    }

    bool checkOnesSegment(string s) {
        bool seeZero{};
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == '0') {
                seeZero = true;
                continue;
            }
            if (seeZero && s[i] == '1') return false;
        }
        return true;
    }

    bool canBeEqual(string s1, string s2) {
        return ((s1[0] == s2[0] && s1[2] == s2[2]) ||
                (s1[0] == s2[2] && s1[2] == s2[0])) &&
               ((s1[1] == s2[1] && s1[3] == s2[3]) ||
                (s1[1] == s2[3] && s1[3] == s2[1]));
    }

    int scoreOfString(string s) {
        int ans{};
        for (int i = 0; i < s.length() - 1; ++i) ans += abs(s[i] - s[i + 1]);
        return ans;
    }

    int minimumOperations(vector<int>& nums) {
        int ans{};
        for (int num : nums) {
            ans += num % 3 != 0 ? 1 : 0;
        }
        return ans;
    }

    vector<int> getSneakyNumbers(vector<int>& nums) {
        vector<bool> seen(nums.size(), false);
        vector<int> ans;
        ans.reserve(2);
        for (int num : nums) {
            if (seen[num] == true)
                ans.push_back(num);
            else
                seen[num] = true;
        }
        return ans;
    }

    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n - 2 * k + 1; ++i) {
            bool one = true;
            for (int j = i; j < i + k - 1; ++j) {
                if (nums[j + 1] <= nums[j]) {
                    one = false;
                    break;
                }
            }
            if (one) {
                bool two = true;
                for (int j = i + k; j < i + k + k - 1; ++j) {
                    if (nums[j + 1] <= nums[j]) {
                        two = false;
                        break;
                    }
                }
                if (two) return true;
            }
        }
        return false;
    }

    int minOperations(vector<int>& nums, int k) {
        int sum{};
        for (int num : nums) sum += num;
        return sum % k;
    }

    int smallestIndex(vector<int>& nums) {
        auto digitSum = [](int num) -> int {
            int sum{};
            while (num != 0) {
                sum += num % 10;
                num /= 10;
            }
            return sum;
        };
        for (int i = 0; i < nums.size(); ++i) {
            if (digitSum(nums[i]) == i) return i;
        }
        return -1;
    }

    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        int cur{};
        while (cur < n - 1) {
            if (nums[cur + 1] == nums[cur]) return false;
            if (nums[cur + 1] < nums[cur]) break;
            ++cur;
        }
        if (cur == 0) return false;
        if (cur == n - 1) return false;
        while (cur < n - 1) {
            if (nums[cur + 1] == nums[cur]) return false;
            if (nums[cur + 1] > nums[cur]) break;
            ++cur;
        }
        if (cur == n - 1) return false;
        while (cur < n - 1) {
            if (nums[cur + 1] == nums[cur]) return false;
            if (nums[cur + 1] < nums[cur]) break;
            ++cur;
        }
        if (cur != n - 1) return false;
        return true;
    }

    vector<int> findMissingElements(vector<int>& nums) {
        int mini = INT_MAX;
        int maxi = INT_MIN;
        for (int num : nums) {
            mini = min(mini, num);
            maxi = max(maxi, num);
        }
        vector<bool> seen(maxi - mini + 1, false);
        for (int num : nums) {
            seen[num - mini] = true;
        }
        vector<int> ans;
        for (int i = 0; i < maxi - mini + 1; ++i) {
            if (seen[i] == false) ans.push_back(i + mini);
        }
        return ans;
    }

    int residuePrefixes(string s) {
        int ans{};
        int uniq{};
        vector<bool> seen(26, false);
        for (int i = 0; i < s.length(); ++i) {
            if (seen[s[i] - 'a'] == false) {
                seen[s[i] - 'a'] = true;
                ++uniq;
            }
            if (uniq == (i + 1) % 3) ans++;
        }
        return ans;
    }

    bool uniformArray(vector<int>& nums) { return true; }

    int maxSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.rbegin(), nums.rend());
        auto lar = [](int num) -> int {
            int ans{};
            while (num != 0) {
                ans = max(ans, num % 10);
                num /= 10;
            }
            return ans;
        };
        int ans = -1;
        vector<vector<int>> indices(10, vector<int>());
        for (int i = 0; i < n; ++i) {
            int digit = lar(nums[i]);
            indices[digit].push_back(i);
            if (indices[digit].size() == 2)
                ans =
                    max(ans, nums[indices[digit][0]] + nums[indices[digit][1]]);
        }
        return ans;
    }

    int reverse(int x) {
        if (x < 10 && x > -10) return x;
        if (x == INT_MIN) return 0;  // otherwise abs() will fail
        bool positive = x > 0;
        int num = abs(x);
        int newNum{};
        while (num != 0) {
            int digit = num % 10;
            num /= 10;
            if (INT_MAX / 10 < newNum) return 0;
            if (INT_MAX - newNum * 10 < digit) return 0;
            newNum = newNum * 10 + digit;
        }
        return positive ? newNum : -newNum;
    }

    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        // the first swap is a bit different
        ListNode* b = head->next;
        head->next = b->next;
        b->next = head;
        head = b;
        auto swapAfter = [](ListNode* node) -> void {
            ListNode* a = node->next;
            ListNode* b = node->next->next;
            a->next = b->next;
            b->next = a;
            node->next = b;
        };
        ListNode* node = head->next;
        while (node->next != NULL && node->next->next != NULL) {
            swapAfter(node);
            node = node->next->next;
        }
        return head;
    }

    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN) {
            if (divisor == 1) return INT_MIN;
            if (divisor == -1) return INT_MAX;
            if (divisor == INT_MIN) return 1;
        }
        if (divisor == INT_MIN) return 0;
        if (divisor == 1) return dividend;
        if (divisor == -1) return -dividend;
        bool positive{};
        if (dividend >= 0 && divisor > 0)
            positive = true;
        else if (dividend < 0 && divisor < 0)
            positive = true;
        else
            positive = false;
        int count{};
        if (dividend != INT_MIN) {
            dividend = abs(dividend);
            divisor = abs(divisor);
            while (dividend >= divisor) {
                ++count;
                dividend -= divisor;
            }
        } else if (dividend == INT_MIN) {
            dividend = INT_MAX;
            divisor = abs(divisor);
            ++count;
            dividend -= divisor;
            ++dividend;
            while (dividend >= divisor) {
                ++count;
                dividend -= divisor;
            }
        }
        return positive ? count : -count;
    }

    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double ans = 1.0;
        double unitProduct = x;
        while (N > 0) {
            if (N % 2 == 1) {
                // if odd, push one unitProduct to ans;
                ans *= unitProduct;
            }
            // remaining part can use binary product
            unitProduct *= unitProduct;
            N /= 2;
        }
        return ans;
    }

    int maxSubArray(vector<int>& nums) {
        // KADANE'S ALGORITHM
        int curMax{};
        int maxSoFar = INT_MIN;
        for (int num : nums) {
            curMax = max(num, curMax + num);
            maxSoFar = max(maxSoFar, curMax);
        }
        return maxSoFar;
    }

    vector<vector<int>> insert(vector<vector<int>>& intervals,
                               vector<int>& newInterval) {
        // TOO MANY PUSH_BACK AND POP_BACK, CAN IN ONE GO
        int n = intervals.size();
        if (n == 0) {
            intervals.push_back(newInterval);
            return intervals;
        }
        if (newInterval[1] < intervals[0][0]) {
            intervals.insert(intervals.begin(), newInterval);
            return intervals;
        }
        if (newInterval[0] > intervals[n - 1][1]) {
            intervals.push_back(newInterval);
            return intervals;
        }
        auto hasOverlap = [&](vector<int>& a, vector<int>& b) -> bool {
            if (b[0] <= a[0] && b[1] >= a[0] || b[0] <= a[1] && b[1] >= a[1] ||
                b[0] >= a[0] && b[1] <= a[1]) {
                return true;
            }
            return false;
        };
        auto combineIntervals = [&](vector<int>& a,
                                    vector<int>& b) -> vector<int> {
            int l = min(a[0], b[0]);
            int r = max(a[1], b[1]);
            return {l, r};
        };
        vector<vector<int>> ans;
        int i{};
        for (; i < n; ++i) {
            if (hasOverlap(intervals[i], newInterval)) {
                ans.push_back(combineIntervals(intervals[i], newInterval));
                ++i;
                break;
            }
            if (intervals[i][0] > newInterval[1]) {
                ans.push_back(newInterval);
                ans.push_back(intervals[i]);
                ++i;
                break;
            }
            ans.push_back(intervals[i]);
        }
        for (; i < n; ++i) {
            vector<int> temp = ans.back();
            if (hasOverlap(temp, intervals[i])) {
                ans.pop_back();
                ans.push_back(combineIntervals(intervals[i], temp));
                continue;
            }
            ans.push_back(intervals[i]);
        }
        return ans;
    }

    int uniquePaths(int m, int n) {
        // BT IS SLOW, DP SHOULD WORK
        // int count{};
        // auto bt = [&](auto& self, int row, int col) -> void {
        //     if (row == m - 1 && col == n - 1) {
        //         ++count;
        //     } else if (row == m || col == n) {
        //     } else {
        //         self(self, row + 1, col);
        //         self(self, row, col + 1);
        //     }
        //     return;
        // };
        // bt(bt, 0, 0);
        // return count;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) dp[i][0] = 1;
        for (int j = 0; j < n; ++j) dp[0][j] = 1;
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    int removeDuplicates(vector<int>& nums) {
        // TWO POINTERS
        int n = nums.size();
        if (n <= 2) return n;
        int write = 2;
        int read = 2;
        for (; read < n; ++read) {
            if (nums[read] == nums[write - 2]) {
                // bad read, continue read, but write stays
                continue;
            } else {
                // good read;
                nums[write++] = nums[read];
            }
        }
        return write;
        // take away:
        // 1. the key point is WHY read is compared against write - 2?
        // if read == write, it's ok, write doesn't matter at all
        // if read == write - 1, it's ok, it means this number appeared at least
        // once if read == write - 2, it's NO ok, because now write - 1 and
        // write - 2 are already this number, we can not assign this number to
        // write again the logic flow is, we have a new number coming, we need
        // to check if current position, aka write, can hold this new number or
        // not, the cretiria is, "already two same numbers?" if can, assign and
        // move on, both if cannot, just read forward, while write stays
    }

    ListNode* deleteDuplicates(ListNode* head) {
        auto nextDistinct = [&](auto& self) -> ListNode* {
            // if already to the end;
            ListNode* ans;
            if (head == NULL || head->next == NULL) {
                ans = head;
                head = NULL;  // this is a MUST! otherwise the last node return
                              // but not move forward
                return ans;
            }
            int tempVal = head->val;
            // if next val is different, this node is good
            if (head->next->val != tempVal) {
                ans = head;
                head = head->next;
                return ans;
            }
            // if have duplicate value
            while (head != NULL && head->val == tempVal) {
                head = head->next;
            }
            // if reach here, we have a different val,
            // BUT we can not return yet, because this new value may have
            // duplicate behind
            return self(self);
        };
        ListNode preHead(0);
        ListNode* cur = &preHead;
        while ((cur->next = nextDistinct(nextDistinct))) cur = cur->next;
        return preHead.next;
    }

    ListNode* partition(ListNode* head, int x) {
        if (head == NULL) return NULL;
        ListNode preHead1(0);
        ListNode preHead2(0);
        ListNode* end1 = &preHead1;
        ListNode* end2 = &preHead2;
        auto processNode = [&]() -> void {
            if (head->val < x) {
                end1->next = head;
                end1 = end1->next;
            } else {
                end2->next = head;
                end2 = end2->next;
            }
            head = head->next;
        };
        while (head) {
            processNode();
        }
        end1->next = preHead2.next;
        end2->next = NULL;
        return preHead1.next;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) return head;
        ListNode preHead(0);
        preHead.next = head;
        ListNode* cur = &preHead;
        for (int i = 0; i < left - 1; ++i) cur = cur->next;
        ListNode* leftEnd = cur;
        ListNode* start = leftEnd->next;
        for (int i = 0; i < right - left + 1; ++i) cur = cur->next;
        ListNode* end = cur;
        ListNode* rightStart = cur->next;
        auto reverseList = [&]() -> void {
            ListNode* back = start;
            ListNode* mid = back->next;
            if (mid == end) {
                mid->next = back;
                return;
            }
            ListNode* front = mid->next;
            while (front != end) {
                mid->next = back;
                back = mid;
                mid = front;
                front = front->next;
            }
            // now front == end;
            mid->next = back;
            front->next = mid;
        };
        reverseList();
        leftEnd->next = end;
        start->next = rightStart;
        return preHead.next;
    }

    vector<TreeNode*> generateTrees(int n) {
        // TRAVERSE, PARTITION, AND COMBINE
        if (n == 1) return {new TreeNode(1)};
        auto buildTree = [](auto& self, int start,
                            int end) -> vector<TreeNode*> {
            if (start > end) return {NULL};
            vector<TreeNode*> allTreesForThisLevel;
            for (int i = start; i <= end; ++i) {
                vector<TreeNode*> leftSubTrees = self(self, start, i - 1);
                vector<TreeNode*> rightSubTrees = self(self, i + 1, end);
                for (TreeNode* left : leftSubTrees) {
                    for (TreeNode* right : rightSubTrees) {
                        TreeNode* root = new TreeNode(i);
                        root->left = left;
                        root->right = right;
                        allTreesForThisLevel.push_back(root);
                    }
                }
            }
            return allTreesForThisLevel;
        };
        return buildTree(buildTree, 1, n);
    }

    bool isValidBST(TreeNode* root) {
        // auto bst = [](auto& self, TreeNode* root) -> bool {
        //     if (root == NULL) return true;
        //     return (root->left == NULL || root->left->val < root->val) &&
        //            (root->right == NULL || root->right->val > root->val) &&
        //            self(self, root->left) && self(self, root->right);
        // };
        // return bst(bst, root);
        vector<int> flat;
        auto dfs = [&](auto& self, TreeNode* node) -> void {
            if (node == NULL) return;
            self(self, node->left);
            flat.push_back(node->val);
            self(self, node->right);
            return;
        };
        dfs(dfs, root);
        if (flat.size() <= 1) return true;
        for (int i = 1; i < flat.size(); ++i) {
            if (flat[i] <= flat[i - 1]) return false;
        }
        return true;
    }

    void recoverTree(TreeNode* root) {
        // FIND FIRST, THEN RECOVER
        vector<int> flat;
        auto dfsFind = [&](auto& self, TreeNode* node) -> void {
            if (node == NULL) return;
            self(self, node->left);
            flat.push_back(node->val);
            self(self, node->right);
            return;
        };
        dfsFind(dfsFind, root);
        // step 1, find the samll
        int n = flat.size();
        int small{};
        int big{};
        for (int i = n - 1; i > 0; --i) {
            // backward, because there are two "drops" in the list,
            // what we need is the later one
            if (flat[i] < flat[i - 1]) {
                small = flat[i];
                break;
            }
        }
        for (int i = 1; i < n; ++i) {
            // backward, because there are two "drops" in the list,
            // what we need is the later one
            if (flat[i] < flat[i - 1]) {
                big = flat[i - 1];
                break;
            }
        }
        // step 3, recover
        bool flagSmall{};
        bool flagBig{};
        auto dfsRecover = [&](auto& self, TreeNode* node) -> void {
            if (node == NULL) return;
            if (flagSmall && flagBig) return;
            if (node->val == small) {
                node->val = big;
                flagSmall = true;
                if (flagBig) return;
            } else if (node->val == big) {
                node->val = small;
                flagBig = true;
                if (flagSmall) return;
            }
            self(self, node->left);
            self(self, node->right);
        };
        dfsRecover(dfsRecover, root);
        return;
        // BST? Flatten it!
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        // BFS, BUT WITH MUTIPLE QUEUE
        if (root == NULL) return {};
        vector<vector<TreeNode*>> q;
        vector<vector<int>> ans;
        q.push_back({root});
        int level{};
        while (true) {
            // start this level
            ans.push_back({});  // this level
            q.push_back({});    // next level
            for (TreeNode* node : q[level]) {
                ans[level].push_back(node->val);
                if (node->left) q[level + 1].push_back(node->left);
                if (node->right) q[level + 1].push_back(node->right);
            }
            ++level;
            if (q[level].size() == 0) break;
        }
        return ans;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == NULL) return {};
        vector<vector<TreeNode*>> q;
        vector<vector<int>> ans;
        q.push_back({root});
        int level{};
        while (true) {
            // start this level
            vector<int> thisLevel;
            q.push_back({});  // next level
            for (TreeNode* node : q[level]) {
                thisLevel.push_back(node->val);
                if (node->left) q[level + 1].push_back(node->left);
                if (node->right) q[level + 1].push_back(node->right);
            }
            if (level % 2 == 1)
                std::reverse(thisLevel.begin(), thisLevel.end());
            ans.push_back(thisLevel);
            ++level;
            if (q[level].size() == 0) break;
        }
        return ans;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // PREIDX ++, AMAZING, MUST LEFT FIRST
        int n = preorder.size();
        unordered_map<int, int> inMap;
        for (int i = 0; i < n; ++i) inMap[inorder[i]] = i;
        int preIdx{};
        auto build = [&](auto& self, int left, int right) -> TreeNode* {
            if (left > right) return NULL;
            int rootVal = preorder[preIdx++];
            TreeNode* root = new TreeNode(rootVal);
            int split = inMap[rootVal];
            root->left = self(self, left, split - 1);
            root->right = self(self, split + 1, right);
            return root;
        };
        return build(build, 0, n - 1);
        // take away:
        // 1. use inorder to partition
        // 2. use preorder to find root
        // must process left first,
        // so that preIdx++ logic reains valid
    }

    TreeNode* sortedListToBST(ListNode* head) {
        // BUILD = PARTITION +  RECUSION
        if (head == NULL) return NULL;
        ListNode* cur = head;
        int n{};
        while (cur != NULL) {
            cur = cur->next;
            ++n;
        }
        cur = head;
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = cur->val;
            cur = cur->next;
        }
        //  now I have a sorted list;
        auto build = [&](auto& self, int left, int right) -> TreeNode* {
            if (left > right) return NULL;
            int mid = left + (right - left) / 2;
            TreeNode* root = new TreeNode(nums[mid]);
            TreeNode* leftChild = self(self, left, mid - 1);
            TreeNode* rightChild = self(self, mid + 1, right);
            root->left = leftChild;
            root->right = rightChild;
            return root;
        };
        return build(build, 0, n - 1);
    }

    vector<vector<int>> pathSum_0(TreeNode* root, int targetSum) {
        int sum{};
        vector<int> run;
        vector<vector<int>> ans;
        auto bt = [&](auto& self, TreeNode* node) -> void {
            if (node == NULL) return;
            run.push_back(node->val);
            sum += node->val;
            if (node->left == NULL && node->right == NULL && sum == targetSum) {
                vector<int> good(run);
                ans.push_back(good);
            }
            self(self, node->left);
            self(self, node->right);
            sum -= node->val;
            run.pop_back();
            return;
        };
        bt(bt, root);
        return ans;
    }

    Node* connect(Node* root) {
        if (root == NULL) return root;
        vector<vector<Node*>> layers;
        layers.push_back({root});
        int level = 0;
        while (level < layers.size()) {
            vector<Node*> nextLevel;
            vector<Node*>& thisLevel = layers[level];
            int n = thisLevel.size();
            for (int i = 0; i < n - 1; ++i) {
                thisLevel[i]->next = thisLevel[i + 1];
                if (thisLevel[i]->left != NULL) {
                    nextLevel.push_back(thisLevel[i]->left);
                    nextLevel.push_back(thisLevel[i]->right);
                }
            }
            thisLevel[n - 1]->next = NULL;
            if (thisLevel[n - 1]->left != NULL) {
                nextLevel.push_back(thisLevel[n - 1]->left);
                nextLevel.push_back(thisLevel[n - 1]->right);
            }
            if (nextLevel.size() != 0) layers.push_back(nextLevel);
            ++level;
        }
        return root;
    }

    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> memo;
        memo.push_back(triangle[0]);
        for (int i = 1; i < n; ++i) {
            int m = triangle[i].size();
            vector<int> layer(m);
            layer[0] = triangle[i][0] + memo[i - 1][0];
            for (int j = 1; j < m - 1; ++j)
                layer[j] =
                    triangle[i][j] + min(memo[i - 1][j - 1], memo[i - 1][j]);
            layer[m - 1] = triangle[i][m - 1] + memo[i - 1][m - 2];
            memo.push_back(layer);
        }
        int ans = INT_MAX;
        for (int num : memo[n - 1]) ans = min(ans, num);
        return ans;
    }

    int sumNumbers(TreeNode* root) {
        int ans{};
        int running{};
        auto bt = [&](auto& self, TreeNode* node) -> void {
            if (node == NULL) return;
            running *= 10;
            running += node->val;
            if (node->left == NULL && node->right == NULL) {
                ans += running;
            }
            self(self, node->left);
            self(self, node->right);
            running /= 10;
            return;
        };
        bt(bt, root);
        return ans;
    }

    Node* cloneGraph(Node* node) {
        // CLONE A GRAPH USUALLY USE NODE-TO-NODE MAP, BUT I DIDN'T
        if (node == NULL) return NULL;
        int count{};
        unordered_set<int> visited;
        auto dfsCount = [&](auto& self, Node* root) -> void {
            if (root == NULL) return;
            if (visited.contains(root->val)) return;
            visited.insert(root->val);
            count = max(count, root->val);
            for (Node* nd : root->neighbors) {
                self(self, nd);
            }
            return;
        };
        dfsCount(dfsCount, node);
        vector<Node*> pool(count);
        for (int i = 0; i < count; ++i) {
            pool[i] = new Node(i + 1);
        }
        visited.clear();
        auto dfsConnect = [&](auto& self, Node* root) -> void {
            if (root == NULL) return;
            if (visited.contains(root->val)) return;
            visited.insert(root->val);
            for (Node* nd : root->neighbors) {
                pool[root->val - 1]->neighbors.push_back(pool[nd->val - 1]);
                self(self, nd);
            }
            return;
        };
        dfsConnect(dfsConnect, node);
        return pool[node->val - 1];
    }

    int singleNumber_0(vector<int>& nums) {
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            int bitCount = 0;
            for (int num : nums) {
                if ((num >> i) & 1) {
                    bitCount++;
                }
            }
            if (bitCount % 3 != 0) {
                result |= (1 << i);
            }
        }
        return result;
    }

    void reorderList(ListNode* head) {
        // REVERSE AND MERGE
        if (head == NULL || head->next == NULL) return;
        // find the middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // now slow is at the last node of left part
        // reverse the right half
        ListNode* rightHead = slow->next;
        slow->next = NULL;  // clean up tail
        // auto reverseList = [](ListNode* node) -> ListNode* {
        //     ListNode* prev = NULL;
        //     ListNode* cur = node;
        //     while (cur) {
        //         ListNode* nextNode = cur->next;
        //         cur->next = prev;
        //         prev = cur;
        //         cur = nextNode;
        //     }
        //     return prev;
        //     // prev is the new head, while cur is at NULL
        // };
        // rightHead = reverseList(rightHead);
        auto reverseList = [&](auto& self, ListNode* prev,
                               ListNode* cur) -> void {
            if (cur->next) self(self, cur, cur->next);
            if (!cur->next) rightHead = cur;
            cur->next = prev;
            return;
        };
        reverseList(reverseList, NULL, rightHead);
        // merger
        auto combineList = [](ListNode* left, ListNode* right) {
            while (right) {
                ListNode* nextLeft = left->next;
                ListNode* nextRight = right->next;
                left->next = right;
                right->next = nextLeft;
                left = nextLeft;
                right = nextRight;
            }
        };
        combineList(head, rightHead);
        return;
    }

    ListNode* sortList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        vector<ListNode*> nodes;
        ListNode* cur = head;
        while (cur) {
            nodes.push_back(cur);
            cur = cur->next;
        }
        sort(nodes.begin(), nodes.end(),
             [](ListNode* a, ListNode* b) { return a->val < b->val; });
        int i = 0;
        for (; i < nodes.size() - 1; ++i) {
            nodes[i]->next = nodes[i + 1];
        }
        nodes[i]->next = NULL;
        return nodes[0];
    }

    ListNode* sortList_merge_sort(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto getMid = [](ListNode* node) -> ListNode* {
            ListNode* slow = node;
            ListNode* fast = node->next;
            while (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;
            }
            return slow;
        };
        ListNode* mid = getMid(head);
        ListNode* right = mid->next;
        ListNode* left = head;
        mid->next = nullptr;  // clean up tail
        left = sortList_merge_sort(left);
        right = sortList_merge_sort(right);
        auto merge = [](ListNode* l1, ListNode* l2) {
            ListNode preHead(0);
            ListNode* curr = &preHead;
            while (l1 != nullptr && l2 != nullptr) {
                if (l1->val <= l2->val) {
                    curr->next = l1;
                    l1 = l1->next;
                } else {
                    curr->next = l2;
                    l2 = l2->next;
                }
                curr = curr->next;
            }
            curr->next = (l1 != nullptr) ? l1 : l2;
            return preHead.next;
        };
        return merge(left, right);
    }

    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        int a{};
        int b{};
        for (string s : tokens) {
            if (s == "+") {
                b = stk.top();
                stk.pop();
                a = stk.top();
                stk.pop();
                stk.push(a + b);
            } else if (s == "-") {
                b = stk.top();
                stk.pop();
                a = stk.top();
                stk.pop();
                stk.push(a - b);
            } else if (s == "*") {
                b = stk.top();
                stk.pop();
                a = stk.top();
                stk.pop();
                stk.push(a * b);
            } else if (s == "/") {
                b = stk.top();
                stk.pop();
                a = stk.top();
                stk.pop();
                stk.push(a / b);
            } else {
                stk.push(stoi(s));
            }
        }
        return stk.top();
    }

    int maxProduct(vector<int>& nums) {
        // TWO PASS, SMART
        int n = nums.size();
        long long max_prod = nums[0];
        long long left_prod = 0;
        long long right_prod = 0;
        for (int i = 0; i < n; ++i) {
            left_prod = (left_prod == 0 ? 1 : left_prod) * nums[i];
            right_prod = (right_prod == 0 ? 1 : right_prod) * nums[n - 1 - i];
            max_prod = max({max_prod, left_prod, right_prod});
        }
        return (int)max_prod;
    }

    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        string ans = "";
        long long n = (long long)numerator;
        long long d = (long long)denominator;
        if (n > 0 && d < 0 || n < 0 && d > 0) ans += '-';
        n = abs(n);
        d = abs(d);
        long long quo = n / d;
        ans += to_string(quo);
        long long rem = n % d;
        if (rem == 0) return ans;
        ans += ".";
        vector<int> digits;
        unordered_map<long long, long long> mp;  // {rem: index};
        long long ix{};
        while (true) {
            if (rem == 0) break;
            if (mp.find(rem) != mp.end()) break;
            // if this rem no happend yet
            mp[rem] = ix++;
            rem *= 10;
            quo = rem / d;
            rem = rem % d;
            digits.push_back(quo);
        }
        if (rem == 0) {
            for (long long i = 0; i < ix; ++i) ans += digits[i] + '0';
            return ans;
        }
        for (long long i = 0; i < mp[rem]; ++i) ans += digits[i] + '0';
        ans += '(';
        for (long long i = mp[rem]; i < ix; ++i) ans += digits[i] + '0';
        ans += ')';
        return ans;
    }

    int trailingZeroes(int n) {
        // FIND OUT HOW MANY 5s
        if (n < 5) return 0;
        int ans{};
        auto fives = [](int num) -> int {
            int count{};
            while (num % 5 == 0) {
                ++count;
                num /= 5;
            }
            return count;
        };
        for (int num = 5; num <= n; ++num) {
            ans += fives(num);
        }
        return ans;
    }

    int rob0(vector<int>& nums) {
        // BT IS ALWAYS SLOW
        // int n = nums.size();
        // int ans{};
        // int sum{};
        // auto bt = [&](auto& self, int pos) -> void {
        //     if (pos >= n) {
        //         ans = max(ans, sum);
        //         return;
        //     }
        //     sum += nums[pos];
        //     self(self, pos + 2);
        //     sum -= nums[pos];
        //     self(self, pos + 1);
        //     return;
        // };
        // bt(bt, 0);
        // return ans;
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        vector<int> memoWith(n, -1);
        vector<int> memoWithout(n, -1);
        memoWith[0] = nums[0];
        memoWithout[0] = 0;
        memoWith[1] = nums[1];
        memoWithout[1] = nums[0];
        for (int i = 2; i < n; ++i) {
            memoWith[i] = memoWithout[i - 1] + nums[i];
            memoWithout[i] = max(memoWithout[i - 1], memoWith[i - 1]);
        }
        return max(memoWith[n - 1], memoWithout[n - 1]);
        // take away:
        // can be more elegant
        // int prev1 = 0; // dp[i-1]
        // int prev2 = 0; // dp[i-2]
        // for(int num : nums) {
        //     int curr = max(prev1, prev2 + num);
        //     prev2 = prev1;
        //     prev1 = curr;
        // }
        // return prev1;
    }

    vector<int> rightSideView(TreeNode* root) {
        if (root == NULL) return {};
        vector<vector<TreeNode*>> layers;
        layers.push_back({root});
        int level = 0;
        while (level < layers.size()) {
            vector<TreeNode*> nextLayer;
            for (TreeNode* node : layers[level]) {
                if (node->left) nextLayer.push_back(node->left);
                if (node->right) nextLayer.push_back(node->right);
            }
            if (nextLayer.empty()) break;
            layers.push_back(nextLayer);
            ++level;
        }
        vector<int> ans(layers.size());
        for (int i = 0; i < layers.size(); ++i) {
            ans[i] = layers[i].back()->val;
        }
        return ans;
    }

    int countPrimes(int n) {
        if (n == 0) return 0;
        if (n == 1) return 0;
        if (n == 2) return 0;
        vector<bool> isPrime(n, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (int num = 2; num < n; ++num) {
            if (!isPrime[num]) continue;
            for (long mul = num * num; mul < n; mul += num) {
                isPrime[mul] = false;
            }
        }
        int count{};
        for (bool b : isPrime) count += b ? 1 : 0;
        return count;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // AS LONG AS THERE IS NO CYCLE
        int n = numCourses;
        vector<vector<int>> adj(n, vector<int>());
        for (const vector<int>& v : prerequisites) adj[v[0]].push_back(v[1]);
        vector<int> status(n, 0);
        // 0 = unvisited, 1 = visiting, 2 = finihsed safe
        auto hasCycle = [&](auto& self, int node) -> bool {
            status[node] = 1;  // mark as visiting;
            for (int next : adj[node]) {
                //  if next is visited and safe
                if (status[next] == 2) continue;
                // if next is right now being visited
                if (status[next] == 1) return true;
                // if new node and has a cycle
                if (status[next] == 0 && self(self, next)) return true;
                // if new node but no cycle, just continnue;
            }
            // all connections visited, no cycle
            status[node] = 2;
            return false;
        };
        for (int i = 0; i < n; ++i) {
            if (hasCycle(hasCycle, i)) return false;
        }
        return true;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // PUT ALL THE PARENTS TOGETHER AS A LIST, NOT THE CHILDREN
        int n = numCourses;
        vector<vector<int>> dep(n);
        vector<int> in(n, 0);
        for (auto v : prerequisites) {
            dep[v[1]].push_back(v[0]);
            // this is the KEY
            // pre -> all courses that depend on this pre
            in[v[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in[i] == 0) q.push(i);
        }
        vector<int> ans;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            ans.push_back(cur);
            for (int next : dep[cur]) {
                if (--in[next] == 0) q.push(next);
                // next is zero in now
            }
        }
        if (ans.size() == n) return ans;
        return {};
        // take away:
        // 1. put all the parents together as a list, not the children
        // because I want to know, for each new zero, who will be next zeros
        // aka, if a course is found zero, then its parents are unlocked by one
        // degree
        // otherwise if let the parent be head and followed by a list of
        // children if a children is freed, I have to scan all the parents to
        // see who has this children
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        vector<int> memo1(n);  // rob first
        vector<int> memo2(n);  // not rob first
        memo1[0] = nums[0];
        memo1[1] = nums[0];
        memo2[0] = 0;
        memo2[1] = nums[1];
        for (int i = 2; i < n - 1; ++i) {
            memo1[i] = max(memo1[i - 2] + nums[i], memo1[i - 1]);
            memo2[i] = max(memo2[i - 2] + nums[i], memo2[i - 1]);
        }
        // for memo1, the last elem don't need to consider
        memo1[n - 1] = memo1[n - 2];
        memo2[n - 1] = max(memo2[n - 3] + nums[n - 1], memo2[n - 2]);
        return max(memo1[n - 1], memo2[n - 1]);
    }

    int findKthLargest(vector<int>& nums, int k) {
        int maxNum = INT_MIN;
        int minNum = INT_MAX;
        for (int num : nums) {
            maxNum = max(maxNum, num);
            minNum = min(minNum, num);
        }
        // for the Kth largest, at most (k-1) numbers greater
        // so iterate the numbers, count the greaters
        // once I pass a number that the strick greater just jump above k-1
        // that very number is what I am looking for
        int l = minNum;
        int r = maxNum;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            int count{};
            for (int num : nums)
                if (num > mid) ++count;
            if (count <= k - 1) {
                // this mid is big but not at the very edge yet.
                // so it can be smaller, until we try out a "error", so that we
                // know we just passed the right answer
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        // after this binary search, l is at the insert point
        // which is the first place that used to belongs to r
        // in this case, count <= k -1
        // which also means, this number is part of the original list,
        // because smaller than this number, there will be more greater numbers
        // it is right because this number becomes a greater for that
        // "one-smaller" number
        return l;
    }

    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1,
                    int bx2, int by2) {
        vector<int> ax = {min(ax1, ax2), max(ax1, ax2)};
        vector<int> ay = {min(ay1, ay2), max(ay1, ay2)};
        vector<int> bx = {min(bx1, bx2), max(bx1, bx2)};
        vector<int> by = {min(by1, by2), max(by1, by2)};
        int areaA = (ax[1] - ax[0]) * (ay[1] - ay[0]);
        int areaB = (bx[1] - bx[0]) * (by[1] - by[0]);
        if (ax[1] <= bx[0] || ax[0] >= bx[1] || ay[1] <= by[0] ||
            ay[0] >= by[1])
            // means no overlap
            return areaA + areaB;
        // otherwise, there is overlap
        // both x and y must both have overlap
        // so among the four x-coordinates, pick the inner two
        vector<int> x = {ax1, ax2, bx1, bx2};
        vector<int> y = {ay1, ay2, by1, by2};
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        return areaA + areaB - (x[2] - x[1]) * (y[2] - y[1]);
    }

    int kthSmallest(TreeNode* root, int k) {
        // BST, LET'S FLATTEN IT
        vector<int> nums;
        auto dfs = [&](auto& self, TreeNode* node) -> void {
            if (node == NULL) return;
            self(self, node->left);
            nums.push_back(node->val);
            self(self, node->right);
            return;
        };
        dfs(dfs, root);
        return nums[k - 1];
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // THE KEY IS "EITHER"
        if (root == NULL || root == p || root == q) return root;
        // as long as seen some one, return
        // it is kind of early return, no need to check the other node
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        // because this is early return, we are not sure if left or right has
        // met one or both but we can leverage condition to make decision if
        // both met some one, then current root must be the ancestor
        if (left != NULL && right != NULL) return root;
        // if not, means only one met both, than the other node must return
        // NULL, even though we are not explicitly told that the node met two
        // rather then one
        return (left != NULL) ? left : right;
        // take away:
        // 1. if root is NULL, return NULL, that is obvious, but why p || q not
        // p && q ? It is smart, it's a early return strategy, which leverage
        // the "vague" return
    }

    void deleteNode(ListNode* node) {
        ListNode* cur = node;
        while (cur->next->next) {
            cur->val = cur->next->val;
            cur = cur->next;
        }
        cur->val = cur->next->val;
        cur->next = NULL;
        return;
    }

    vector<vector<string>> groupStrings(vector<string>& strings) {
        int n = strings.size();
        vector<int> root(n);
        for (int i = 0; i < n; ++i) root[i] = i;
        auto find = [&](auto& self, int i) -> int {
            if (i == root[i]) return i;
            return root[i] = self(self, root[i]);
        };
        auto unite = [&](int a, int b) -> void {
            int rootA = find(find, a);
            int rootB = find(find, b);
            if (rootA != rootB) root[rootA] = rootB;
        };
        auto match = [&](int a, int b) -> bool {
            int len = strings[a].size();
            if (len != strings[b].size()) return false;
            int offset = (strings[a][0] - strings[b][0] + 26) % 26;
            for (int i = 1; i < len; ++i) {
                if ((strings[a][i] - strings[b][i] + 26) % 26 != offset)
                    return false;
            }
            return true;
        };
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (match(i, j)) unite(i, j);
            }
        }
        unordered_map<int, vector<string>> mp;
        for (int i = 0; i < n; ++i) {
            mp[find(find, i)].push_back(std::move(strings[i]));
        }
        vector<vector<string>> ans;
        ans.reserve(mp.size());
        for (const auto& [key, val] : mp) {
            ans.push_back(std::move(val));
        }
        return ans;
    }

    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const auto& o1, const auto& o2) -> bool {
                 return o1[0] < o2[0];
             });
        vector<int> ends;
        for (auto& v : intervals) {
            int i = 0;
            for (; i < ends.size(); ++i) {
                if (ends[i] > v[0]) continue;
                ends[i] = v[1];  // update the end time
                break;
            }
            if (i == ends.size()) {
                // means vavant room not found
                // open a new room
                ends.push_back(v[1]);
            }
            sort(ends.begin(), ends.end());
        }
        return ends.size();
    }

    vector<int> singleNumber(vector<int>& nums) {
        // DIFF BIT IS KEY
        long long totalXOR{};
        for (int num : nums) totalXOR ^= num;
        int diffBit = (int)(totalXOR & -totalXOR);
        int a{};
        int b{};
        for (int num : nums) {
            if (num & diffBit)
                a ^= num;
            else
                b ^= num;
        }
        return {a, b};
        // take away:
        // 1. -totalXOR is "reverse then plus one"
        // after reverse, xor ^ reversed xor = 0
        // then plus one...
        // it is hard to describe but easy to just try it
        // if I don't know the & - trick, I can just ues /= 2 to find which
        // digit is different, then use that digit to generate a diffNumber
    }

    int numSquares(int n) {
        // DP + MIN
        vector<int> dp(n + 1, n);
        dp[0] = 0;  // number 0 needs 0 perfect squares
        for (int i = 0; i <= n; ++i) {
            // by default any number is composed of n ones but it can also be
            // added by a perfect square from another number so we try all the
            // possible "another numbers",and min it
            for (int j = 0; j * j <= i; ++j) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }

    void wallsAndGates(vector<vector<int>>& rooms) {
        // MULTI SOURCE BFS. PROCESS ON PUSH? PROCESS ON POP?
        int INF = 2147483647;
        int m = rooms.size();
        if (m == 0) return;
        int n = rooms[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rooms[i][j] == 0) q.push({i, j});
            }
        }
        vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (auto d : dirs) {
                int nr = r + d.first;
                int nc = c + d.second;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                    rooms[nr][nc] == INF) {
                    rooms[nr][nc] = rooms[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
        return;
        // take away:
        // 1. what are we queuing? pos processed? or pos not yet?
        // if we queue new pos, one we pop the pos, we have no idea what the
        // current or previous dist is. because we lose the link to its
        // prescendent. So, we must process before we queue the pos.
    }

    int maxProfit(vector<int>& prices) {
        // FSM +  DP = PARALLEL UNIVERSE
        // int n = prices.size();
        // if (n == 0) return 0;
        // // four memos, but no need the entire memo, we only need yesterday,
        // // so we just keep the fringe
        // // the names suggests the action of today, the value is the profit
        // right
        // // after today's operation
        // int hold = -prices[0];  // have a stock at hand
        // int sold = 0;           // sold
        // int empty = 0;          // protfolio is empty
        // for (int i = 1; i < n; ++i) {
        //     int prevHold = hold;
        //     int prevSold = sold;
        //     int prevEmpty = empty;
        //     // If I want to become/keep "hold" today, yesterday I must be
        //     hold
        //     // or empty. Yesterday I cannot be sold, because of cool down
        //     hold = max(prevHold, prevEmpty - prices[i]);
        //     // If I want to become "sold" today, I must came from "hold"
        //     // yesterday
        //     sold = prevHold + prices[i];
        //     // If I want to become/keep "empty" today, I must came from
        //     "empty"
        //     // or "sold" yesterday
        //     empty = max(prevEmpty, prevSold);
        // }
        // return max(sold, empty);
        int n = prices.size();
        if (n <= 1) return 0;
        int buy = -prices[0];
        int sell = 0;
        int hold = -prices[0];
        int empty = 0;
        for (int i = 1; i < n; ++i) {
            int prevBuy = buy;
            int prevSell = sell;
            int prevHold = hold;
            int prevEmpty = empty;
            // prevEmpty -> buy
            buy = prevEmpty - prices[i];
            // prevBuy -> sell, prevHold -> sell
            sell = max(prevBuy, prevHold) + prices[i];
            // prevBuy -> hold, prevHold -> hold
            hold = max(prevBuy, prevHold);
            // prevEmpth -> empty, prevSell -> empty
            empty = max(prevEmpty, prevSell);
        }
        return max(sell, empty);
        // take away:
        // 1. FSM + DP
        // buy, sell, hold, empty
        // prevBuy, prevSell, prevHold, prevEmpty
        // prevEmpty -> buy
        // prevBuy -> sell, prevHold -> sell
        // prevBuy -> hold, prevHold -> hold
        // prevEmpth -> empty, prevSell -> empty
    }

    int bulbSwitch(int n) {
        // AHA!!!!!!!
        return (int)sqrt(n);
    }

    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        sort(coins.begin(), coins.end());
        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            // current number must be from some old number plus a coin
            // so try every coin
            int minNumCoins = INT_MAX;
            for (int coin : coins) {
                if (i - coin < 0) {
                    // if this coin is already too big, no need to continue
                    break;
                }
                if (dp[i - coin] == -1) {
                    // means that number cann'e be reached
                    continue;
                }
                minNumCoins = min(minNumCoins, dp[i - coin]);
            }
            if (minNumCoins != INT_MAX) dp[i] = minNumCoins + 1;
        }
        return dp[amount];
    }

    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = -1;  // unused
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            // i = a + b
            for (int a = 1; a <= i / 2; ++a) {
                int b = i - a;
                dp[i] = max(dp[i], max(a, dp[a]) * max(b, dp[b]));
            }
        }
        return dp[n];
    }

    int rob(TreeNode* root) {
        // POST ORDER DFS + PARALLEL DP
        auto postOrderDFS = [](auto& self, TreeNode* node) -> pair<int, int> {
            // first is rob this node
            // second is not rob this node
            if (!node) return {0, 0};
            auto [leftRob, leftNotRob] = self(self, node->left);
            auto [rightRob, rightNotRob] = self(self, node->right);
            int robThis = node->val + leftNotRob + rightNotRob;
            int notRobThis =
                max(leftRob, leftNotRob) + max(rightRob, rightNotRob);
            return {robThis, notRobThis};
        };
        pair<int, int> ans = postOrderDFS(postOrderDFS, root);
        return max(ans.first, ans.second);
        // take away:
        // 1. DP is intuitive, in this case we only track the end result of each
        // step, it is Greedy at the same time.
        // 2. But why POST ORDER DFS?
        // It is tempting to pre order dfs, but we must keep track of pre, cur,
        // and left/right, three levels in total, which is complicated.
        // Additionaly, when traversal ends, there is a big number(partial
        // result) at the end of EACH LEAF NODE, which introduces another
        // complecity to calc the global result. Post order has a very natual
        // "sum-up" property, which reslve all the concerns above.
    }

    int numberOfPatterns(int m, int n) {
        // BT + SKIP MATRIX
        // {1,3,7,9}, {2,4,6,8}, {5}, by symmetricity, 3 distinct case in total
        int total{};
        int len = 0;
        int skip[10][10] = {0};
        skip[1][3] = skip[3][1] = 2;
        skip[3][9] = skip[9][3] = 6;
        skip[9][7] = skip[7][9] = 8;
        skip[7][1] = skip[1][7] = 4;
        skip[1][9] = skip[9][1] = 5;
        skip[2][8] = skip[8][2] = 5;
        skip[3][7] = skip[7][3] = 5;
        skip[4][6] = skip[6][4] = 5;
        vector<bool> used(10, false);
        used[0] = true;
        auto bt = [&](auto& self, int prev, int cur) -> void {
            // too long, no good
            if (len >= n) return;
            // repeat, no good
            if (used[cur]) return;
            // invalid middle, no good
            if (!used[skip[prev][cur]]) return;
            // else, good current number, accept
            // start bt
            used[cur] = true;
            ++len;
            if (len >= m && len <= n) total++;
            for (int next = 1; next <= 9; ++next) {
                self(self, cur, next);
            }
            --len;
            used[cur] = false;
            // end bt
            return;
        };
        bt(bt, 0, 1);
        bt(bt, 0, 2);
        total *= 4;
        bt(bt, 0, 5);
        return total;
    }

    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        // ZIPPER
        int n = nums.size();
        vector<int> ans;
        ans.reserve(n);
        if (a == 0) {
            for (int num : nums) ans.push_back(b * num + c);
            if (b < 0) std::reverse(ans.begin(), ans.end());
            return ans;
        }
        double axis = (double)-b / (2 * a);
        int l{};
        int r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] >= axis)
                r = mid - 1;
            else
                l = mid + 1;
        }  // l is at first r zone
        int left = l - 1;
        int right = l;
        while (left >= 0 || right < n) {
            double distL = left >= 0 ? axis - nums[left] : INT_MAX;
            double distR = right < n ? nums[right] - axis : INT_MAX;
            if (distL <= distR) {
                ans.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                --left;
            } else {
                ans.push_back(a * nums[right] * nums[right] + b * nums[right] +
                              c);
                ++right;
            }
        }
        if (a < 0) std::reverse(ans.begin(), ans.end());
        return ans;
    }

    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // UPDATE DP, AND TRACK PARENT
        int n = nums.size();
        if (n == 0) return {};
        // sort makes things easier
        sort(nums.begin(), nums.end());
        int maxIndex{};  // the biggest value is not necessarily the last value
        vector<int> dp(n, 1);  // length of largest subset TILL nums[i] and
                               // INCLUDES the nums[i]
        vector<int> parent(n, -1);
        for (int i = 1; i < n; ++i) {
            // scan every previous number
            for (int j = 0; j < i; ++j) {
                // if divisible, it is possible that group[i] is just gourp[j]
                // plus nums[i] as long as group[j] is big enough
                // if that is the case, new largest group found!
                // update dp[i] ofcourse, and more importantly, track which
                // parent group does this new largest group come from
                if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
            // dp[i] done
            // the biggest value is not necessarily the last value
            if (dp[i] > dp[maxIndex]) maxIndex = i;
        }
        // now find the maxIndex
        vector<int> ans;
        int cur = maxIndex;
        while (cur >= 0) {
            ans.push_back(nums[cur]);
            cur = parent[cur];
        }
        return ans;
        // take away:
        // 1. As we move along the nums, we use dp to track and update "what is
        // the biggest length till now AND INCLUDE this number?" Note that the
        // biggest value is not necessarily the last element. The easy part is,
        // go back to check: which gourp can I join? The tricker part is
        // remember which group I joined. If not, even though I have the largest
        // length, I can't reconstruct the exact group. That is where parent[]
        // come into place.
    }

    int getSum(int a, int b) {
        // SUM_WITHOUT_CARYY + CARRY
        while (b != 0) {
            int sumWithoutCarry = a ^ b;
            int carry = (unsigned int)(a & b) << 1;
            // only 1 and 1 generates carry, and carry belongs to left digit,
            // that's why << 1
            a = sumWithoutCarry;
            b = carry;
            // if there is still carry, need to repeat, until there is no carry
        }
        return a;
    }

    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                       int k) {  // 2D MONOTONIC
        // int m = nums1.size();
        // int n = nums2.size();
        // vector<vector<int>> ans;
        // // for each number in nums1, we track "which number in nums2 has
        // being
        // // paired? What is the fringe?"
        // vector<int> surfaceM_N(m, 0);
        // // iniitally, all numbers in nums1 is ready to pair with the first
        // elem
        // // in nums2.
        // // Scan all fringes, see which one is the samllest
        // for (int _ = 0; _ < k; ++_) {
        //     int minSum = INT_MAX;
        //     int ix1{};
        //     int ix2{};
        //     for (int i = 0; i < m; ++i) {
        //         // scan all m lines
        //         // if this line is fully paired, continue;
        //         if (surfaceM_N[i] == n) continue;
        //         // if not, there will be a valid fringe
        //         int tempSum = nums1[i] + nums2[surfaceM_N[i]];
        //         if (tempSum < minSum) {
        //             // update
        //             minSum = tempSum;
        //             ix1 = i;
        //             ix2 = surfaceM_N[i];
        //         }
        //     }
        //     // after the loop, the smallest sum found
        //     ans.push_back({nums1[ix1], nums2[ix2]});
        //     ++surfaceM_N[ix1];
        // }
        // return ans;
        int m = nums1.size();
        int n = nums2.size();
        vector<vector<int>> ans;
        using T = tuple<int, int, int>;  // {sum, i, j}
        priority_queue<T, vector<T>, greater<T>> minHeap;
        // greater<T> for min_heap, auto compare the first elem in tuple
        for (int i = 0; i < min(m, k); ++i) {
            minHeap.push({nums1[i] + nums2[0], i, 0});
        }
        while (k-- && !minHeap.empty()) {
            auto [sum, i, j] = minHeap.top();
            minHeap.pop();
            ans.push_back({nums1[i], nums2[j]});
            if (j < n - 1) minHeap.push({nums1[i] + nums2[j + 1], i, j + 1});
        }
        return ans;
        // take away:
        // 1. Since this is a 2-D monotonicity, we can't find a definitive
        // "direction" to search the matrix.
        // 2. Use minHeap to be faster
    }

    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        vector<unsigned int> dp(target + 1, 0);
        dp[0] = 1;
        for (int t = 1; t <= target; ++t) {
            // fix the sum that we are building toward
            for (int num : nums) {
                // try every number as the last one added to permutation
                if (t >= num) {
                    // if this is the last number, in this very case, the
                    // possibilities are dp[t-num], for the target t, increse
                    // the total possibilities by such amount
                    dp[t] += dp[t - num];
                }
            }
        }
        return (int)dp[target];
        // take away:
        // 1. Why dp on increasing target, not dp on expanding array?
        // nums outer → "what items are in my pool?"    → order ignored
        // (combinations)
        // target outer → "what's the last item added?" → order tracked
        // (permutations)
        // 2. Number out, means number is a one way iteration, no back and
        // forth, this prevent the "premutation" form happening. While target
        // out, the number is checked again and again, it may appear at any
        // position, that is exactly premutation.
    }

    vector<int> lexicalOrder(int n) {
        vector<int> ans;
        ans.reserve(n);
        auto pushNumbers = [&](auto& self, int num) -> void {
            // first push this number
            if (num > n) return;
            ans.push_back(num);
            for (int nextDigit = 0; nextDigit <= 9; ++nextDigit) {
                self(self, num * 10 + nextDigit);
            }
        };
        for (int i = 1; i <= min(9, n); ++i) {
            pushNumbers(pushNumbers, i);
        }
        return ans;
    }

    int maxRotateFunction(vector<int>& nums) {
        // ROTATION IS MATH_ABLE
        int n = nums.size();
        int baseSum{};
        int baseIncre{};
        int mul{};
        for (int num : nums) {
            baseSum += mul++ * num;
            baseIncre += num;
        }
        int maxAns = baseSum;
        for (int i = 0; i < n - 1; ++i) {
            baseSum += baseIncre - (n * nums[n - 1 - i]);
            maxAns = max(maxAns, baseSum);
        }
        return maxAns;
    }

    string removeKdigits(string num, int k) {
        // MONOTONIC STACK, ONE BY ONE
        int n = num.size();
        if (n == k) return "0";
        string stack;
        for (char c : num) {
            // see how many digits can be replaced by this c
            while (k > 0 && !stack.empty() && stack.back() > c) {
                stack.pop_back();
                --k;
            }
            stack.push_back(c);
        }
        // all digits added to stack now
        // if still have quota, kick out
        while (k-- > 0) stack.pop_back();
        while (stack[0] == '0') stack.erase(0, 1);
        if (stack.empty()) return "0";
        return stack;
        // int n = num.size();
        // vector<int> digits(n, -1);
        // for (int i = 0; i < n; ++i) digits[i] = num[i] - '0';
        // int left{};
        // while (k != 0) {
        //     if (n - left == k) {
        //         // all the remaining digits can be deleted;
        //         for (int i = left; i < n; ++i) digits[i] = -1;
        //         break;
        //     }
        //     int minVal = 10;
        //     int minIdx = n;
        //     for (int i = 0; i <= k; ++i) {
        //         // starting from left, scan k + 1 positions
        //         // find the smallest digit
        //         if (digits[left + i] < minVal) {
        //             minVal = digits[left + i];
        //             minIdx = left + i;
        //         }
        //     }
        //     // we find the smallest digits, we need to delete something
        //     for (int j = left; j < minIdx; ++j) digits[j] = -1;
        //     k -= minIdx - left;
        //     left = minIdx + 1;
        // }
        // string ans = "";
        // for (int d : digits) {
        //     if (d == -1) continue;
        //     ans += d + '0';
        // }
        // while (ans[0] == '0') ans.erase(0, 1);
        // if (ans.size() == 0) return "0";
        // return ans;
        // take away:
        // 1. My initial algorithm make it too complicated.
        // To form a as-small-as-possible number, we need the front digits to be
        // "asap". So we use the quota as front as possible. So greedyly kick
        // out the larger digits as long as their is quota. So the flow is: scan
        // the entire array, as long as have quota, replace greedily; if no
        // quora, just add. After the scanning, trim the string.
    }

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // AS CURTAIN IS FALLING DOWN, WE SEE MORE SHORTER GUYS
        sort(people.begin(), people.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] == b[0]) return a[1] < b[1];
                 return a[0] > b[0];  // descending height
             });
        vector<vector<int>> ans;
        for (auto& p : people)
            ans.insert(ans.begin() + p[1], p);  // insert at index k
        return ans;
        // int n = people.size();
        // auto cmp = [](vector<int> o1, vector<int> o2) -> bool {
        //     if (o1[0] == o2[0]) return o1[1] < o2[1];
        //     return o1[0] < o2[0];
        // };
        // sort(people.begin(), people.end(), cmp);
        // vector<vector<int>> ans(n);
        // vector<bool> occupied(n, false);
        // int currentGroup = INT_MIN;
        // vector<int> tempPos;
        // for (auto v : people) {
        //     if (v[0] != currentGroup) {
        //         // new height coming
        //         // wrap up last round, fill all the pos of prev round
        //         for (int pos : tempPos) occupied[pos] = true;
        //         tempPos.clear();
        //         currentGroup = v[0];
        //     }
        //     int pos{};
        //     int numSkips = v[1];  // [4,4]
        //     while (numSkips) {
        //         if (occupied[pos] == false) --numSkips;
        //         ++pos;
        //     }
        //     while (occupied[pos]) ++pos;
        //     // now, good pos found
        //     ans[pos] = v;
        //     tempPos.push_back(pos);
        // }
        // return ans;
    }

    bool canPartition(vector<int>& nums) {
        // KNAPSACK, ITEMS OUTER, R->L
        int total{};
        for (int num : nums) total += num;
        if (total % 2 == 1) return false;
        int target = total / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums) {
            for (int t = target; t >= num; --t) {
                dp[t] = dp[t] || dp[t - num];
            }
        }
        return dp[target];
        // int n = nums.size();
        // int total{};
        // sort(nums.begin(), nums.end());
        // for (int num : nums) total += num;
        // if (total % 2 == 1) return false;
        // int target = total / 2;
        // int sum{};
        // auto bt = [&](auto& self, int i) -> bool {
        //     if (sum == target) return true;
        //     if (i >= n) return false;
        //     if (nums[i] > target) return false;
        //     sum += nums[i];
        //     if (self(self, i + 1)) return true;
        //     sum -= nums[i];
        //     if (self(self, i + 1)) return true;
        //     return false;
        // };
        // return bt(bt, 0);
        // take away:
        // 1. Back tracking TLE, of course.
        // BT is for counting, but not for checking.
    }

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n == 1) return 0;
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& o1, const vector<int>& o2) {
                 return o1[0] < o2[0];
             });
        int fringe = intervals[0][1];  // current right end
        int count{};
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] < fringe) {
                // if overlap, keep the smaller end one
                fringe = min(fringe, intervals[i][1]);
                ++count;
            } else {
                fringe = intervals[i][1];
            }
        }
        return count;
    }

    int pathSum(TreeNode* root, int targetSum) {
        // BT + PREFIX, MAP CAN BE FASTER
        vector<long long> prefixSum;
        prefixSum.push_back(0);
        int ans{};
        auto count = [&]() -> void {
            int n = prefixSum.size();
            int r = n - 1;  // the end is fixed
            for (int l = 0; l < n - 1; ++l) {
                if (prefixSum[r] - prefixSum[l] == targetSum) ++ans;
            }
            return;
        };
        auto bt = [&](auto& self, TreeNode* node) -> void {
            if (node == NULL) return;
            // add this cal to prefix
            prefixSum.push_back(prefixSum.back() + node->val);
            // can this cal be the last elem in a path?
            count();
            self(self, node->left);
            self(self, node->right);
            prefixSum.pop_back();
            return;
        };
        bt(bt, root);
        return ans;
        // take away:
        // 1. cannot count after the leaf node, because some parent paths might
        // be double counted. So for each node, ask "can this be the last elem"
    }

    int compress(vector<char>& chars) {
        // TWO POINTERS
        int n = chars.size();
        int l{};
        int r{};
        int idx{};
        while (r <= n) {  // including r == n, consolidate the end case
            if (r == n || chars[r] != chars[l]) {
                chars[idx++] = chars[l];
                int count = r - l;
                if (count != 1) {
                    vector<int> digits;
                    while (count != 0) {
                        digits.push_back(count % 10);
                        count /= 10;
                    }
                    for (int i = digits.size() - 1; i >= 0; --i)
                        chars[idx++] = digits[i] + '0';
                }
                l = r;
            }
            ++r;
        }
        return idx;
    }

    bool sequenceReconstruction(vector<int>& nums,
                                vector<vector<int>>& sequences) {
        // DEPENDENCY, WHO IS THE LEADER?
        int n = nums.size();
        vector<vector<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);
        for (auto& seq : sequences) {
            for (int i = 0; i + 1 < seq.size(); ++i) {
                int u = seq[i];
                int v = seq[i + 1];
                graph[u].push_back(v);
                // this is important, what I need to know, is if a node is
                // freed, whose indegree will --? That's why use graph[u] rather
                // then graph[v]
                indegree[v]++;
                // This is also important, I need to know the indegree of each
                // node, but I don't need to know who exactly are they
            }
        }
        queue<int> q;  // though a queue, expected to be only one item
        for (int i = 1; i <= n; ++i) {
            if (indegree[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            if (q.size() > 1) return false;  // not unique
            int node = q.front();
            q.pop();
            for (int nei : graph[node]) {
                if (--indegree[nei] == 0) q.push(nei);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (indegree[i] != 0) return false;
        }
        return true;
        // take away:
        // 1. track indegree, but no need to know who are they
        // 2. use graph to track who are they
        // int n = nums.size();
        // vector<vector<bool>> depend(n + 1, vector<bool>(n + 1, false));
        // vector<int> count(n + 1, 0);
        // for (auto& v : sequences) {
        //     for (int l = 0; l < v.size(); ++l) {
        //         for (int r = l + 1; r < v.size(); ++r) {
        //             if (depend[v[r]][v[l]] == false) {
        //                 depend[v[r]][v[l]] = true;
        //                 ++count[v[r]];
        //             }
        //         }
        //     }
        // }
        // auto nextIndex = [&]() -> int {
        //     // if good, return next index
        //     // if multiple independent, return 0
        //     // if no independent, return -1
        //     int ans{};
        //     bool already{};
        //     for (int i = 1; i <= n; ++i) {
        //         if (count[i] == 0) {
        //             if (already) return 0;
        //             ans = i;
        //             already = true;
        //         }
        //     }
        //     if (already) return ans;
        //     return -1;
        // };
        // int next{};
        // while ((next = nextIndex()) != -1) {
        //     // this number is added to the final sequence
        //     if (next == 0) return false;
        //     // means too many independent, leads to un-unique
        //     // else, good next
        //     count[next] = -1;
        //     // means that this number is done processing
        //     for (int i = 1; i <= n; ++i) {
        //         if (depend[i][next] == true) {
        //             depend[i][next] = false;
        //             count[i]--;
        //         }
        //     }
        //     // remove this next from dependent
        // }
        // // done processing
        // // check the count, if have unprocessed, no good, means cycle
        // for (int i = 1; i <= n; ++i)
        //     if (count[i] != -1) return false;
        // return true;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // STACK!!! + PREPEND!!!
        stack<int> s1, s2;
        while (l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        int carry{};
        ListNode* cur = NULL;
        while (!s1.empty() || !s2.empty() || carry) {
            int sum = carry;
            if (!s1.empty()) {
                sum += s1.top();
                s1.pop();
            }
            if (!s2.empty()) {
                sum += s2.top();
                s2.pop();
            }
            ListNode* node = new ListNode();
            node->val = sum % 10;
            carry = sum /= 10;
            node->next = cur;
            cur = node;
        }
        return cur;
        // vector<int> v1;
        // vector<int> v2;
        // ListNode* cur = l1;
        // while (cur) {
        //     v1.push_back(cur->val);
        //     cur = cur->next;
        // }
        // cur = l2;
        // while (cur) {
        //     v2.push_back(cur->val);
        //     cur = cur->next;
        // }
        // int n1 = v1.size();
        // int n2 = v2.size();
        // if (n1 == 1 && l1->val == 0) return l2;
        // if (n2 == 1 && l2->val == 0) return l1;
        // int n = max(n1, n2);
        // vector<int> digits(n, 0);
        // int carry{};
        // for (int i = 0; i < n; ++i) {
        //     int d1 = (i < n1) ? v1[n1 - 1 - i] : 0;
        //     int d2 = (i < n2) ? v2[n2 - 1 - i] : 0;
        //     int sum = carry + d1 + d2;
        //     digits[n - 1 - i] = sum % 10;
        //     carry = sum / 10;
        // }
        // ListNode* preRoot = new ListNode();
        // cur = preRoot;
        // if (carry == 1) {
        //     cur->next = new ListNode();
        //     cur = cur->next;
        //     cur->val = carry;
        //     cur->next = NULL;
        // }
        // for (int i = 0; i < n; ++i) {
        //     cur->next = new ListNode();
        //     cur = cur->next;
        //     cur->val = digits[i];
        //     cur->next = NULL;
        // }
        // return preRoot->next;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        // SWAP AND RECURSIVELY DELETE
        // base case;
        if (!root) return NULL;
        if (key < root->val) {
            // if on left branch
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            // if on right branch
            root->right = deleteNode(root->right, key);
        } else {
            // found the node
            if (!root->left) return root->right;
            if (!root->right) return root->left;
            // else, if the root has both children
            TreeNode* successor = root->right;
            // go to the smallest of right child
            // this will be the next number
            while (successor->left) successor = successor->left;
            root->val = successor->val;
            root->right = deleteNode(root->right, successor->val);
        }
        return root;
        // take away:
        // 1. try utilize recursion, try NOT to track too many layers
        // "RETURN ROOT IS THE KEY"
        // 2. swap value with successor, then recursively delete successor
    }

    int findMinArrowShots(vector<vector<int>>& points) {
        // SORT + GREEDY
        if (points.size() == 0) return 0;
        if (points.size() == 1) return 1;
        sort(points.begin(), points.end());
        // use the first point (safe) to be the base case, avoid certain edge
        // case
        int left = points[0][0];
        int right = points[0][1];
        int count = 1;
        for (auto& p : points) {
            if (p[0] > right) {
                // if out of the prev overlap area, a new arrow needed.
                ++count;
                left = p[0];
                right = p[1];
            } else {
                // shrink the overalp interval
                left = p[0];  // the vector is already sorted on the [0]
                right = min(right, p[1]);
            }
        }
        return count;
        // take away:
        // 1. this algorithm is greedy: I will use as few arrows as possible
        // 2. left is never used, drop it
    }

    string validIPAddress(string queryIP) {
        if (queryIP.find('.') != string::npos) {
            // IPv4
            vector<string> parts;
            int l{};
            int r{};
            while (r < queryIP.size()) {
                if (queryIP[r] >= 'a' && queryIP[r] <= 'z' ||
                    queryIP[r] >= 'A' && queryIP[r] <= 'Z')
                    return "Neither";
                if (queryIP[r] == '.') {
                    if (r - l == 0) return "Neither";
                    if (r - l > 3) return "Neither";
                    parts.push_back(queryIP.substr(l, r - l));
                    l = r + 1;
                }
                ++r;
            }
            if (r - l == 0) return "Neither";
            if (r - l > 3) return "Neither";
            parts.push_back(queryIP.substr(l, r - l));
            if (parts.size() != 4) return "Neither";
            // all parts ready
            for (auto& p : parts) {
                if (p[0] == '0' && p.size() != 1) return "Neither";
                int temp{};
                for (char c : p) temp = temp * 10 + c - '0';
                if (temp > 255) return "Neither";
            }
            return "IPv4";
        } else {
            // IPv6
            vector<string> parts;
            int l{};
            int r{};
            while (r < queryIP.size()) {
                if (queryIP[r] == ':') {
                    if (r - l == 0) return "Neither";
                    if (r - l > 4) return "Neither";
                    parts.push_back(queryIP.substr(l, r - l));
                    l = r + 1;
                }
                ++r;
            }
            if (r - l == 0) return "Neither";
            if (r - l > 4) return "Neither";
            parts.push_back(queryIP.substr(l, r - l));
            if (parts.size() != 8) return "Neither";
            // all parts ready
            for (auto& p : parts) {
                for (char c : p) {
                    if (c > 'f' && c <= 'z' || c > 'F' && c <= 'Z')
                        return "Neither";
                }
            }
            return "IPv6";
        }
        return "Neither";
    }

    vector<int> nextGreaterElements(vector<int>& nums) {
        // MONOTONIC STACK IS GREAT FOR "NEXT BIGGER" QUESTIONS
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> indices;  // if a number is smaller than prev, it(index) will
                             // be pushed into the stadk, as a result, the stadk
                             // is monotonic small
        for (int i = 0; i < 2 * n; ++i) {
            // for  each number, check if it can free any previous numbers
            while (!indices.empty()) {
                // as long as the stack is not empty, which means there is some
                // number haven't found next greater yet
                if (nums[i % n] <= nums[indices.top()]) break;
                // if greater
                ans[indices.top()] = nums[i % n];
                indices.pop();
            }
            // if this number has found his next greater, no need to add to
            // stack
            if (i < n) indices.push(i);
        }
        return ans;
        // take away:
        // 1. use i < 2 * n to achieve the circular, but need a extra check
    }
};

int main() {
    cout << "Hello, world." << endl;
    google obj;
    return 0;
}
