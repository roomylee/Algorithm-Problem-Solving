// SCC
‪#‎include‬ <cstdio>
#include <vector>
#include <stack>
#include <functional>
#include <tuple>
#include <algorithm>
using namespace std;
int main()
{
	int v, e;
	scanf("%d%d", &v, &e);
	vector<vector<int>> adj(v);
	for (int i = 0; i < e; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		a--;
		b--;
		adj[a].push_back(b);
	}
	int counter = 0;
	stack<int> log;
	vector<int> index(v, -1);
	vector<int> lowlink(v);
	vector<bool> onStack(v);
	vector<vector<int>> scc;
	vector<int> sccIndex(v);
	function<void(int)> tarjan = [&](int current)
	{
		lowlink[current] = index[current] = counter++;
		log.push(current);
		onStack[current] = true;
		for (const auto &next : adj[current])
		{
			if (index[next] < 0)
			{
				tarjan(next);
				lowlink[current] = min(lowlink[current], lowlink[next]);
			}
			else if (onStack[next])
			{
				lowlink[current] = min(lowlink[current], index[next]);
			}
		}
		if (lowlink[current] == index[current])
		{
			vector<int> comp;
			int w;
			do
			{
				w = log.top();
				log.pop();
				onStack[w] = false;
				comp.push_back(w);
				sccIndex[w] = scc.size();
			} while (w != current);
			scc.emplace_back(comp);
		}
	};
	for (int i = 0; i < v; i++)
	{
		if (index[i] < 0)
		{
			tarjan(i);
		}
	}
	printf("%d\n", scc.size());
	for (auto &s : scc)
	{
		sort(s.begin(), s.end());
	}
	sort(scc.begin(), scc.end(), [](const vector<int> &s, const vector<int> &p) { return s.front() < p.front(); });
	for (auto &s : scc)
	{
		for (auto &i : s)
		{
			printf("%d ", i + 1);
		}
		printf("-1\n");
	}
	return 0;
}