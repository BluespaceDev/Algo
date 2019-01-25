#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100000;

struct edge{
	int v;
	int w;
};

vector<edge> adj[MAX + 1];
int depth[MAX + 1];
int parent[MAX + 1];
int dist[MAX + 1];
int p[MAX + 1][20];
int min_d[MAX + 1][20];
int max_d[MAX + 1][20];

void dfs(int u, int w = 0, int dep = 0){
	depth[u] = dep;
	dist[u] = w;
	for (int i = 0; i < adj[u].size(); ++i){
		int v = adj[u][i].v;
		if (parent[v] == -1){
			parent[v] = u;
			dfs(v, adj[u][i].w, dep + 1);
		}
	}
}

int lca_min(int u, int v){
	if (depth[u] < depth[v])
		swap(u, v);
	int ret_min = 999999999;
	int log = 1;
	for (log = 1; (1 << log) <= depth[u]; log++);
	log -= 1;
	for (int i = log; i >= 0; i--) {
		if (depth[u] - (1 << i) >= depth[v]) {
			if (ret_min > min_d[u][i])
				ret_min = min_d[u][i];

			u = p[u][i];
		}
	}
	if (u == v)
		return ret_min;
	else {
		for (int i = log; i >= 0; i--) {
			if (p[u][i] != 0 && p[u][i] != p[v][i]) {
				if (ret_min > min_d[u][i])
					ret_min = min_d[u][i];
				if (ret_min > min_d[v][i])
					ret_min = min_d[v][i];
				u = p[u][i];
				v = p[v][i];
			}
		}
		if (ret_min > min_d[u][0])
			ret_min = min_d[u][0];
		
		if (ret_min > min_d[v][0])
			ret_min = min_d[v][0];

		return ret_min;
	}
}
int lca_max(int u, int v) {
	if (depth[u] < depth[v])
		swap(u, v);

	int log;
	for (log = 1; (1 << log) <= depth[u]; log++);
	log--;

	int max_edge = 0;
	for (int i = log; i >= 0; --i){
		if (depth[u] - (1 << i) >= depth[v]){
			max_edge = max(max_edge, max_d[u][i]);
			u = p[u][i];
		}
	}

	if (u == v){
		return max_edge;
	}

	for (int i = log; i >= 0; --i){
		if (p[u][i] != 0 && p[u][i] != p[v][i]){
			max_edge = max(max_edge, max_d[u][i]);
			max_edge = max(max_edge, max_d[v][i]);
			u = p[u][i];
			v = p[v][i];
		}
	}

	max_edge = max(max_edge, max_d[u][0]);
	max_edge = max(max_edge, max_d[v][0]);

	return max_edge;
}

int main()
{
	int n;
	scanf("%d", &n);

	int u, v, w;
	for (int i = 0; i < n - 1; ++i){
		scanf("%d %d %d", &u, &v, &w);
		adj[u].push_back({ v, w });
		adj[v].push_back({ u, w });
	}
	memset(parent, -1, sizeof(parent));
	parent[1] = 0;
	dfs(1);

	for (int i = 1; i <= n; ++i){
		p[i][0] = parent[i];
		min_d[i][0] = dist[i];
		max_d[i][0] = dist[i];
	}
	for (int j = 1; (1 << j) < n; j++) {
		for (int i = 1; i <= n; i++) {
			if (p[i][j - 1] != 0) {
				p[i][j] = p[p[i][j - 1]][j - 1];
				min_d[i][j] = min_d[i][j - 1];
				if (p[i][j] != 0){
					min_d[i][j] = min(min_d[i][j - 1], min_d[p[i][j - 1]][j - 1]);
				}
			}
		}
	}
	for (int j = 1; (1 << j) < n; ++j) {
		for (int i = 1; i <= n; ++i) {
			if (p[i][j - 1] != 0){
				max_d[i][j] = max(max_d[i][j - 1], max_d[p[i][j - 1]][j - 1]);
			}
		}
	}

	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i){
		scanf("%d %d", &u, &v);
		printf("%d %d\n", lca_min(u, v), lca_max(u, v));
	}

	return 0;
}
