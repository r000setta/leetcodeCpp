#pragma once
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include <list>
#include <queue>
#include <stack>
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

	int flipgame(vector<int>& fronts, vector<int>& backs) {

	}
};