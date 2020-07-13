#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


bool next_combination(vector<int>& vec, int n)
{
	int k = vec.size() - 1;
	for (; k >= 0; k--) {
		if (vec[k] < n + k - vec.size() + 1) break;
	}
	if (k < 0) return 0;
	vec[k]++;
	for (int i = k + 1; i < vec.size(); i++)
	{
		vec[k + 1] = vec[k] + 1;
	}
	return 1;
}

int main() {
	int n, k;
	//scanf("%d%d", &n, &k);
	n = 10;
	k = 4;
	vector<int> vec, vec2, dir;
	for (int i = 1; i <= k; i++) {
		vec.push_back(i);
	}
	do {
		for (int i = 0; i < vec.size(); i++) {
			printf("%d ", vec[i]);
		}
		printf("\n");
	} while (next_combination(vec, n));
	system("pause");
}