// 절점
‪#‎include‬ <cstdio>
#include <vector>
#include <stack>
#include <functional>
#include <tuple>
#include <set>
#include <algorithm>
using namespace std;
set<int> cut;
vector<vector<int>> adj;
vector<bool> went;
vector<int> depth;
int dfs(int c)
{
	const auto &cd = depth[c];
	auto g = cd, cs = 0;
	went[c] = true;
	for (auto &x : adj[c])
	{
		if (!went[x])
		{
			cs++;
			depth[x] = cd + 1;
			auto y = dfs(x);
			g = min(g, y);
			if (y >= cd && cd)
			{
				cut.insert(c);
			}
		}
		g = min(g, depth[x]);
	}
	if (!cd && cs >= 2)
	{
		cut.insert(c);
	}
	return g;
}
int main()
{
	int v, e;
	scanf("%d%d", &v, &e);
	adj = vector<vector<int>>(v);
	for (int i = 0; i < e; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	went = vector<bool>(v);
	depth = vector<int>(v);
	for (int i = 0; i < v; i++)
	{
		if (went[i] == false)
		{
			dfs(i);
		}
	}
	printf("%d\n", cut.size());
	for (const auto &i : cut)
	{
		printf("%d ", i + 1);
	}
	printf("\n");
	return 0;
}