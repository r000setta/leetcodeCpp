#include <iostream>
#include <vector>
using namespace std;
void f(vector<int>& v) {
	v[0] = 1;
}
int main() {
	vector<int> v{ 4,2,3 };
	f(v);
	cout << v[0] << endl;
}