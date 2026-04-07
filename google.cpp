#include <deque>
#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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
    ListNode* deleteDuplicates(ListNode* head) {
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
};

int main() {
    cout << "Hello, world." << endl;
    return 0;
}
