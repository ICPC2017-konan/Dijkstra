#include <memory>
#include <cstdio>

typedef struct EDGE {
	int srcNode;	// エッジの始点
	int dstNode;	// エッジの終点
	int cost;		// エッジのコスト
} Edge;

int calcMinimumCost(Edge *edges, int n, int m, int start, int goal);

int main() {
	int n, m, s, g;

	while (scanf("%d%d%d%d", &n, &m, &s, &g) == 4 && n > 0 && m > 0 && s > 0 && g > 0) {
		// グラフの情報の読み込み
		s--;	// 0オリジンに
		g--;

		Edge *edges = (Edge *)malloc(sizeof(Edge) * m);

		for (int i = 0; i < m; i++) {
			int x1, x2, c;
			scanf("%d%d%d", &x1, &x2, &c);
			x1--;	// 0オリジンに
			x2--;
			edges[i].srcNode = x1;
			edges[i].dstNode = x2;
			edges[i].cost = c;
		}

		// 最小コスト和の計算
		printf("%d\n", calcMinimumCost(edges, n, m, s, g));

		// メモリの解放
		free(edges);
	}
	return 0;
}

int calcMinimumCost(Edge *edges, int n, int m, int start, int goal) {
	Edge *edge = NULL;
	int *states = NULL;			// -1: 未訪問, 0: 訪問済み, 1: 確定済み
	int *minCosts = NULL;
	int nextNode = 0;
	int cost = 0;
	int result = 0;

	// 0. 初期化
	states = (int *)malloc(sizeof(int) * n);
	minCosts = (int *)malloc(sizeof(int) * n);
	for (int node = 0; node < n; node++) {
		states[node] = -1;
		minCosts[node] = -1;
	}

	// 1. startノードへの最短距離を0にし確定する
	minCosts[start] = 0;
	states[start] = 1;
	int recentlyFixedNode = start;
	while (recentlyFixedNode != goal) {
		// 2. 確定した頂点の各隣接頂点までの距離を更新する
		for (int edge = 0; edge < m; edge++) {
			if (edges[edge].srcNode == recentlyFixedNode) {
				nextNode = edges[edge].dstNode;
			} else if (edges[edge].dstNode == recentlyFixedNode) {
				nextNode = edges[edge].srcNode;
			} else continue;
			cost = edges[edge].cost;
			
			if (states[nextNode] == -1 || minCosts[nextNode] > minCosts[recentlyFixedNode] + cost) {
				minCosts[nextNode] = minCosts[recentlyFixedNode] + cost;
				if (states[nextNode] == -1) {
					states[nextNode] = 0;
				}
			}
		}
		// 3. 訪問済み頂点の中で距離最短のものを求める
		int minCost = -1;
		int minNode = -1;
		for (int node = 0; node < n; node++) {
			if (states[node] == 0 && (minCost == -1 || minCosts[node] < minCost)) {
				minCost = minCosts[node];
				minNode = node;
			}
		}
		// 4. 距離最短のものを確定する
		states[minNode] = 1;
		recentlyFixedNode = minNode;
	}
	result = minCosts[goal];
	free(minCosts);
	free(states);
	return result;
}
