#pragma once
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
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

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) :val(x), next(nullptr) {}
};

class Solution {
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (t1 == nullptr)
			return t2;
		if (t2 == nullptr)
			return t1;
		auto merge = new TreeNode(t1->val + t2->val);
		merge->left = mergeTrees(t1->left, t2->left);
		merge->right = mergeTrees(t1->right, t2->right);
		return merge;
	}

	/*int mctFromLeafValues(vector<int>& arr) {
		int n = arr.size();
		vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>({ n,{INT_MAX,0} }));
		for (int i = 0; i < n; ++i) {
			dp[i][i].first = 0;
			dp[i][i].second = arr[i];
		}
		for (int len = 1; len < n; ++len) {
			for (int i = 0,j; i + len < n; ++i) {
				for (int k = i; k < j; ++k) {
					j = len + i;
					if (dp[i][j].first > dp[i][k].first + dp[k + 1][j].first + dp[i][k].second * dp[k + 1][j].second) {
						dp[i][j].first = dp[i][k].first + dp[k + 1][j].first + dp[i][k].second * dp[k + 1][j].second;
						dp[i][j].second = fmax(dp[i][k].second, dp[k + 1][j].second);
					}
				}
			}
		}
		return dp[0][n - 1].first;
	}*/

	bool isSubPath(ListNode* head, TreeNode* root) {
		if (head == nullptr) return true;
		if (root == nullptr) return false;
		return isSubPathHelp(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
	}

	bool isSubPathHelp(ListNode* head, TreeNode* node) {
		if (head == nullptr) return true;
		if (node == nullptr) return false;
		if (head->val != node->val) return false;
		return isSubPathHelp(head->next, node->left) || isSubPathHelp(head->next, node->right);
	}

	bool checkSubTree(TreeNode* t1, TreeNode* t2) {
		if (t2 == nullptr)
			return true;
		if (t1 == nullptr)
			return false;
		if (t1->val != t2->val) {
			return checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
		}
		else if (isSameTree(t1->left, t2->left) && isSameTree(t1->right, t2->right)) {
			return true;
		}

		return checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
	}

	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == nullptr && q == nullptr) {
			return true;
		}
		else if (p == nullptr || q == nullptr) {
			return false;
		}
		else {
			return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
		}
	}

	vector<int> postOrder;
	vector<int> inOrder;
	map<int, int> idxMap;
	int postIdx;

	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		this->postOrder = postorder;
		this->inOrder = inorder;
		postIdx = postorder.size() - 1;
		int idx = 0;
		for (auto val : inorder) {
			idxMap[val] = idx++;
		}
		return buildTreeHelper(0, inorder.size() - 1);
	}

	TreeNode* buildTreeHelper(int left, int right) {
		if (left > right)
			return nullptr;
		int rootVal = postOrder[postIdx];
		TreeNode* root = new TreeNode(rootVal);
		int idx = idxMap[rootVal];
		postIdx--;
		root->right = buildTreeHelper(idx + 1, right);
		root->left = buildTreeHelper(left, idx - 1);
		return root;
	}

	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		if (n == 0)
			return 0;
		int minPrice = prices[0];
		vector<int> dp(n, 0);
		for (int i = 1; i < n; i++) {
			minPrice = fmin(minPrice, prices[i]);
			dp[i] = fmax(dp[i - 1], prices[i] - minPrice);
		}
		return dp[n - 1];
	}

	int maxProfitWithFee(vector<int>& prices, int fee) {
		int n = prices.size();
		vector<vector<int>> dp(n,vector<int>(2,0));
		dp[0][0] = 0;
		dp[0][1] = -prices[0];
		for (int i = 1; i < n; i++) {
			dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
			dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return fmax(dp[n - 1][0], dp[n - 1][1]);
	}

	int maxProfitWithFreeze(vector<int>& prices) {
		int len = prices.size();
		if (len < 2)
			return 0;
		vector<vector<int>> dp(len, vector<int>(3, 0));
		dp[0][0] = 0;
		dp[0][1] = -prices[0];
		dp[0][2] = 0;
		for (int i = 1; i < len; ++i) {
			dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][2] - prices[i]);
			dp[i][2] = dp[i - 1][0];
		}
		return fmax(dp[len - 1][0], dp[len - 1][2]);
	}

	int maxProfit1(vector<int>& prices) {
		auto len = prices.size();
		if (!len)
			return 0;
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] = 0;
		dp[0][1] = -prices[0];
		for (auto i = 1; i < len; ++i) {
			dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = fmax(dp[i - 1][1], -prices[i]);
		}
		return dp[len-1][0];
	}

	int maxProfit2(vector<int>& prices) {
		auto len = prices.size();
		if (!len)
			return 0;
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] = 0;
		dp[0][1] = -prices[0];
		for (auto i = 1; i < len; ++i) {
			dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return dp[len - 1][0];
	}

	int maxProfitk2(vector<int>& prices) {
		if (prices.size() == 0)
			return 0;
		auto len = prices.size();
		vector<vector<vector<int>>> dp(len, vector<vector<int>>(3, vector<int>(2, 0)));
		dp[0][1][0] = 0;
		dp[0][1][1] = -prices[0];
		dp[0][2][0] = 0;
		dp[0][2][1] = -prices[0];
		for (auto i = 1; i < len; ++i) {
			dp[i][2][0] = fmax(dp[i - 1][2][0], dp[i - 1][2][1] + prices[i]);
			dp[i][2][1] = fmax(dp[i - 1][2][1], dp[i - 1][1][0] - prices[i]);
			dp[i][1][0] = fmax(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
			dp[i][1][1] = fmax(dp[i - 1][1][1], dp[i - 1][0][0] - prices[i]);
		}
		return dp[len - 1][2][0];
	}

	int maxProfitanyK(int k, vector<int>& prices) {
		if (prices.size() == 0)
			return 0;
		auto len = prices.size();
		if (k >= len / 2) {
			return maxProfitanyKHelp(prices);
		}
		vector<vector<vector<int>>> dp(len, vector<vector<int>>(k + 1, vector<int>(2, 0)));
		for (auto i = 1; i <= k; i++) {
			dp[0][i][0] = 0;
			dp[0][i][1] = -prices[0];
		}
		for (auto i = 1; i < len; ++i) {
			for (auto j = k; j > 0; --j) {
				dp[i][j][0] = fmax(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
				dp[i][j][1] = fmax(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
			}
		}
		return dp[len - 1][k][0];
	}

	int maxProfitanyKHelp(vector<int>& prices) {
		if (prices.size() == 0)
			return 0;
		auto len = prices.size();
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] = 0;
		dp[0][1] = -prices[0];
		for (auto i = 1; i < len; ++i) {
			dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i]);
		}
		return dp[len - 1][0];
	}

	int maxProfitWithCold(vector<int>& prices) {
		if (prices.size() == 0)
			return 0;
		auto len = prices.size();
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] = 0;
		dp[0][1] = -prices[0];
		for (auto i = 1; i < len; ++i) {
			dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = fmax(dp[i - 1][1], (i >= 2 ? dp[i - 2][0] : 0) - prices[i]);
		}
		return dp[len - 1][0];
	}

	int maxProfitFee(vector<int>& prices, int fee) {
		if (prices.size() == 0) {
			return 0;
		}
		auto len = prices.size();
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] = 0;
		dp[0][1] = -prices[0] - fee;
		for (auto i = 1; i < len; ++i) {
			dp[i][0] = fmax(dp[i - 1][0], dp[i - 1][1] + prices[i]);
			dp[i][1] = fmax(dp[i - 1][1], dp[i - 1][0] - prices[i] - fee);
		}
		return dp[len - 1][0];
	}

	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<int> path;
		vector<vector<int>> res;
		pathSumHelp(root, sum, path, res);
		return res;
	}

	void pathSumHelp(TreeNode* root, int sum, vector<int>& path,vector<vector<int>>& res) {
		if (root == nullptr)
			return;
		path.push_back(root->val);
		sum -= root->val;
		if (root->left == nullptr && root->right == nullptr && sum == 0) {
			res.push_back(path);
		}
		pathSumHelp(root->left, sum, path, res);
		pathSumHelp(root->right, sum, path, res);
		path.pop_back();
	}

	string simplifyPath(string path) {
		stringstream is{ path };
		vector<string> s;
		string res = "", tmp = "";
		while (getline(is, tmp, '/')) {
			if (tmp == "" || tmp == ".") {
				continue;
			}
			else if (tmp == ".." && !s.empty())
				s.pop_back();
			else if (tmp != "..") {
				s.push_back(tmp);
			}
		}
		for (string str : s) {
			res += "/" + str;
		}
		if (res.empty()) {
			return "/";
		}
		return res;
	}

	int game(vector<int>& guess, vector<int>& answer) {
		int ans = 0;
		for (int i = 0; i < guess.size(); i++) {
			if (guess[i] == answer[i])
				ans++;
		}
		return ans;
	}

	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> ans;
		vector<int> path;
		vector<bool> visited(nums.size(), false);
		permuteHelp(nums, ans, path, visited);
		return ans;
	}

	void permuteHelp(vector<int>& nums, vector<vector<int>>& ans, vector<int>& path,vector<bool>& visited) {
		if (path.size() == nums.size()) {
			ans.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); i++) {
			if (visited[i] == false) {
				visited[i] = true;
				path.push_back(nums[i]);
				permuteHelp(nums, ans, path, visited);
				path.pop_back();
				visited[i] = false;
			}
		}
	}

	vector<int> grayCode(int n) {
		vector<int> res;
		res.push_back(0);
		for (int i = 0; i < n; ++i) {
			int add = 1 << i;
			for (int j = res.size() - 1; j >= 0; --j) {
				res.push_back(res[j] + add);
			}
		}
		return res;
	}

	vector<int> grayCode2(int n) {
		vector<int> res(1<<n);
		for (int i = 0; i < 1 << n; ++i) {
			res[i]=(i ^ (i >> 1));
		}
		return res;
	}

	ListNode* sortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return head;
		}
		ListNode* fast = head->next, *slow = head;
		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		ListNode* tmp = slow->next;
		slow->next = nullptr;
		ListNode* left = sortList(head);
		ListNode* right = sortList(tmp);
		ListNode* h = new ListNode(0);
		ListNode* res = h;
		while (left != nullptr && right != nullptr) {
			if (left->val < right->val) {
				h->next = left;
				left = left->next;
			}
			else {
				h->next = right;
				right = right->next;
			}
			h = h->next;
		}
		h->next = left != nullptr ? left : right;
		return res->next;
	}

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root->val > p->val && root->val > q->val) {
			return lowestCommonAncestor(root->left, p, q);
		}
		if (root->val < p->val && root->val < q->val) {
			return lowestCommonAncestor(root->right, p, q);
		}
		return root;
	}

	TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == nullptr || root == q || root == p) {
			return root;
		}
		TreeNode* left = lowestCommonAncestor2(root->left, p, q);
		TreeNode* right = lowestCommonAncestor2(root->right, p, q);
		if (left == nullptr)
			return right;
		if (right == nullptr)
			return left;
		return root;
	}

	Node* connect(Node* root) {
		if (!root)
			return nullptr;
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			auto n = q.size();
			Node* last = nullptr;
			for (int i = 1; i <= n; ++i) {
				Node* f = q.front();
				q.pop();
				if (f->left)
					q.push(f->left);
				if (f->right)
					q.push(f->right);
				if (i != 1) {
					last->next = f;
				}
				last = f;
			}
		}
		return root;
	}

	bool isConvex(vector<vector<int>>& points) {
		int pre = 0;
		long cur = 0;
		auto size = points.size();
		for (int i = 0; i < size; ++i) {
			int x1 = points[(i + 1) % size][0] - points[i][0];
			int x2 = points[(i + 2) % size][0] - points[i][0];
			int y1 = points[(i + 1) % size][1] - points[i][1];
			int y2 = points[(i + 2) % size][1] - points[i][1];
			cur = x1 * y2 - x2 * y1;
			if (cur != 0) {
				if (cur * pre < 0)
					return false;
				else
					pre = cur;
			}
		}
		return true;
	}

	int videoStitching(vector<vector<int>>& clips, int T) {
		
	}

	string decodeString(string s) {
		stack<pair<int, string>> sta;
		int num = 0;
		string res{};
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] >= '0' && s[i] <= '9') {
				num *= 10;
				num += (s[i] - '0');
			}
			else if (s[i] == '[') {
				sta.push(make_pair(num, res));
				num = 0;
				res = "";
			}
			else if (s[i] == ']') {
				int n = sta.top().first;
				string a = sta.top().second;
				sta.pop();
				for (int j = 0; j < n; ++j) {
					a += res;
				}
				res = a;
			}
			else {
				res += s[i];
			}
		}
		return res;
	}

	int climbStairs(int n) {
		if (n == 1)
			return 1;
		vector<int> dp(n + 1, 0);
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; ++i) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}

	int lengthOfLongestSubstring(string s) {
		if (s.size() == 0)
			return 0;
		unordered_set<char> lookup;
		int maxStr = 0;
		int left = 0;
		for (auto i = 0; i < s.size(); ++i) {
			while (lookup.find(s[i]) != lookup.end()) {
				lookup.erase(s[left]);
				++left;
			}
			maxStr = max(maxStr, i - left + 1);
			lookup.insert(s[i]);
		}
		return maxStr;
	}

	bool isPossibleDivide(vector<int>& nums, int k) {
		map<int, int> s;
		for (int num : nums) {
			++s[num];
		}
		for (auto iter = s.begin(); iter != s.end(); ++iter) {
			int num = iter->first;
			int occ = iter->second;
			if (occ > 0) {
				auto it = next(iter);
				for (auto i = 1; i < k; ++i, ++it) {
					if (it != s.end() && it->first == num + i && it->second >= occ)
						it->second -= occ;
					else
						return false;
				}
			}
		}
		return true;
	}

	int minCost(vector<vector<int>>& costs) {
		if (!costs.size())
			return 0;
		int len = costs.size();
		vector<vector<int>> dp(len, vector<int>(3, 0));
		dp[0][0] = costs[0][0];
		dp[0][1] = costs[0][1];
		dp[0][2] = costs[0][2];
		for (int i = 1; i < len; ++i) {
			for (int j = 0; j < 3; ++j) {
				dp[i][j] = costs[i][j] + fmin(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
			}
		}
		return fmin(dp[len - 1][0], fmin(dp[len - 1][1], dp[len - 1][2]));
	}

	int balancedString(string s) {
		vector<char> chars{ 'Q', 'W', 'E', 'R' };
		unordered_map<char, int> cnt;
		for (char ch : s)
			++cnt[ch];
		int exception = s.size() / 4;
		bool balance = true;
		for (char ch : chars) {
			if (cnt[ch] != exception)
				balance = false;
			cnt[ch] -= exception;
		}
		if (balance == true)
			return 0;
		int left = 0, right = 0, n = s.size(), ans = n;
		while (left <= right && right < n) {
			--cnt[s[right]];
			bool find = true;
			while (find) {

			}z
		}
	}

	bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
		vector<vector<int>> p{ p1,p2,p3,p4 };
		sort(p.begin(), p.end(), [](const auto& p1,const auto& p2) {
			return p1[0] == p2[0] ? p1[1] < p2[1] : p1[0] < p2[0];
		});
		return dist(p[0], p[1]) != 0 && dist(p[0], p[1]) == dist(p[1], p[3]) && dist(p[1], p[3]) == dist(p[3], p[2]) && dist(p[3], p[2]) == dist(p[2], p[0]) && dist(p[0], p[3]) == dist(p[1], p[2]);
	}

	double dist(const vector<int>& p1, const vector<int>& p2) {
		return (p2[1] - p1[1]) * (p2[1] - p1[1]) + (p2[0] - p1[0]) * (p2[0] - p1[0]);
	}

	TreeNode* insertIntoBST(TreeNode* root, int val) {
		if (root == nullptr)
			return new TreeNode(val);
		TreeNode* pos = root;
		while (pos != nullptr) {
			if (val < pos->val) {
				if (pos->left == nullptr) {
					pos->left = new TreeNode(val);
					break;
				}
				else {
					pos = pos->left;
				}
			}
			else {
				if (pos->right == nullptr) {
					pos->right = new TreeNode(val);
					break;
				}
				else {
					pos = pos->right;
				}
			}
		}
		return root;
	}

	string tictactoe(vector<string>& board) {
		int len = board.size();
		int left = 0, right = 0, ver = 0, hor = 0;
		bool flag = false;
		for (auto i = 0; i < len; ++i) {
			ver = 0, hor = 0;
			for (auto j = 0; j < len; ++j) {
				hor += (int)board[i][j];
				ver += (int)board[j][i];
				if (board[i][j] == ' ') flag = true;
			}
			if (hor == (int)'X' * len || ver == (int)'X' * len) return "X";
			if (hor == (int)'O' * len || ver == (int)'O' * len) return "O";

			left += (int)board[i][i];
			right += (int)board[i][len - i - 1];
		}
		if (left == (int)'X' * len || right == (int)'X' * len) return "X";
		if (left == (int)'O' * len || right == (int)'O' * len) return "O";
		if (flag) return "Pending";
		return "Draw";
	}

	int minimumOperations(string leaves) {

	}

	void sortColors(vector<int>& nums) {
		int p0 = 0, cur = 0;
		int p2 = nums.size() - 1;
		while (cur <= p2) {
			if (nums[cur] == 0) {
				swap(nums[cur++], nums[p0++]);
			}
			else if (nums[cur] == 2) {
				swap(nums[cur], nums[p2--]);
			}
			else {
				cur++;
			}
		}
	}
	                                                                                  
	bool canJump(vector<int>& nums) {
		int n = nums.size();
		int right = 0;
		for (int i = 0; i < n; ++i) {
			if (i <= right) {
				right = max(right, i + nums[i]);
				if (right >= n - 1)
					return true;
			}
		}
		return false;
	}

	int jump(vector<int>& nums) {
		int maxPos = 0, n = nums.size(), end = 0, step = 0;
		for (int i = 0; i < n - 1; ++i) {
			if (maxPos >= i) {
				maxPos = max(maxPos, i + nums[i]);
				if (i == end) {
					end = maxPos;
					++step;
				}
			}
		}
		return step;
	}

	int minAddToMakeValid(string S) {
		stack<char> stk;
		for (auto c : S) {
			if (c == '(') {
				stk.push(c);
			}
			else {
				if (stk.empty()||stk.top()!='(') {
					stk.push(c);
				}
				else {
					stk.pop();
				}
			}
		}
		return stk.size();
	}

	int longestSubstring(string s, int k) {
		unordered_map<char, int> ch;
		for (auto c : s) {
			++ch[c];
		}
		vector<int> split;
		for (auto i = 0; i < s.size(); ++i) {
			if (ch[s[i]] < k)
				split.push_back(i);
		}
		if (split.size() == 0)
			return s.length();
		int ans = 0, left = 0;
		split.push_back(s.length());
		for (auto i = 0; i < split.size(); ++i) {
			int len = split[i] - left;
			if (len > ans)
				ans = max(ans, longestSubstring(s.substr(left, len), k));
			left = split[i] + 1;
		}
		return ans;
	}

	vector<TreeNode*> generateTrees(int n) {
		vector<TreeNode*> ans;
		if (n == 0)
			return ans;
		return generateTreesHelp(1, n);
	}

	vector<TreeNode*> generateTreesHelp(int start, int end) {
		vector<TreeNode*> ans;
		if (start > end) {
			ans.emplace_back(nullptr);
			return ans;
		}
		if (start == end) {
			TreeNode* root = new TreeNode(start);
			ans.emplace_back(root);
			return ans;
		}
		for (auto i = start; i <= end; ++i) {
			vector<TreeNode*> left = generateTreesHelp(start, i - 1);
			vector<TreeNode*> right = generateTreesHelp(i + 1, end);
			for (auto l : left) {
				for (auto r : right) {
					TreeNode* root = new TreeNode(i);
					root->left = l;
					root->right = r;
					ans.emplace_back(root);
				}
			}
		}
		return ans;
	}

	int numJewelsInStones(string J, string S) {
		int res = 0;
		for (auto c : S) {
			if (J.find(c)!=J.npos) {
				res++;
			}
		}
		return res;
	}

	int maxScoreSightseeingPair(vector<int>& A) {
		int ans = 0, mx = A[0] + 0;
		for (int j = 1; j < A.size(); ++j) {
			ans = max(ans, mx + A[j] - j);
			mx = max(mx, A[j] + j);
		}
		return ans;
	}

	int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
		int res = 0;
		for (int i = 0; i < customers.size(); ++i) {
			if (grumpy[i] == 0) {
				res += customers[i];
				customers[i] = 0;
			}
		}
		int sum = accumulate(customers.begin(), customers.begin() + X, 0);
		int tmp = sum;
		for (int i = 1; i < customers.size() - X + 1; ++i) {
			tmp = tmp + customers[i + X - 1] - customers[i - 1];
			sum = max(sum, tmp);
		}
		return sum + res;
	}

	int movingCount(int m, int n, int k) {

	}

	vector<int> smallestK(vector<int>& arr, int k) {
		vector<int> ans;
		priority_queue<int> q;
		for (int a : arr) {
			q.push(a);
			if (q.size() > k)
				q.pop();
		}
		while (!q.empty()) {
			ans.push_back(q.top());
			q.pop();
		}
		return ans;
	}

	int numOfSubarrays(vector<int>& arr, int k, int threshold) {
		int res = 0;
		int sum = accumulate(arr.cbegin(), arr.cbegin() + k, 0);
		int tar = threshold * k;
		if (sum >= tar)
			res++;
		for (int i = 1; i < arr.size() - k + 1; ++i) {
			sum = sum + arr[i + k - 1] - arr[i - 1];
			if (sum > tar)
				res++;
		}
		return res;
	}
};