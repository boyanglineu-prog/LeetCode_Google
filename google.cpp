#include <algorithm>
#include <deque>
#include <iostream>
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
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
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

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
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
};

int main() {
    cout << "Hello, world." << endl;
    return 0;
}
