#include <memory>
#include <cstdio>

typedef struct EDGE {
	int srcNode;	// �G�b�W�̎n�_
	int dstNode;	// �G�b�W�̏I�_
	int cost;		// �G�b�W�̃R�X�g
} Edge;

int calcMinimumCost(Edge *edges, int n, int m, int start, int goal);

int main() {
	int n, m, s, g;

	while (scanf("%d%d%d%d", &n, &m, &s, &g) == 4 && n > 0 && m > 0 && s > 0 && g > 0) {
		// �O���t�̏��̓ǂݍ���
		s--;	// 0�I���W����
		g--;

		Edge *edges = (Edge *)malloc(sizeof(Edge) * m);

		for (int i = 0; i < m; i++) {
			int x1, x2, c;
			scanf("%d%d%d", &x1, &x2, &c);
			x1--;	// 0�I���W����
			x2--;
			edges[i].srcNode = x1;
			edges[i].dstNode = x2;
			edges[i].cost = c;
		}

		// �ŏ��R�X�g�a�̌v�Z
		printf("%d\n", calcMinimumCost(edges, n, m, s, g));

		// �������̉��
		free(edges);
	}
	return 0;
}

int calcMinimumCost(Edge *edges, int n, int m, int start, int goal) {
	Edge *edge = NULL;
	int *states = NULL;			// -1: ���K��, 0: �K��ς�, 1: �m��ς�
	int *minCosts = NULL;
	int nextNode = 0;
	int cost = 0;
	int result = 0;

	// 0. ������
	states = (int *)malloc(sizeof(int) * n);
	minCosts = (int *)malloc(sizeof(int) * n);
	for (int node = 0; node < n; node++) {
		states[node] = -1;
		minCosts[node] = -1;
	}

	// 1. start�m�[�h�ւ̍ŒZ������0�ɂ��m�肷��
	minCosts[start] = 0;
	states[start] = 1;
	int recentlyFixedNode = start;
	while (recentlyFixedNode != goal) {
		// 2. �m�肵�����_�̊e�אڒ��_�܂ł̋������X�V����
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
		// 3. �K��ςݒ��_�̒��ŋ����ŒZ�̂��̂����߂�
		int minCost = -1;
		int minNode = -1;
		for (int node = 0; node < n; node++) {
			if (states[node] == 0 && (minCost == -1 || minCosts[node] < minCost)) {
				minCost = minCosts[node];
				minNode = node;
			}
		}
		// 4. �����ŒZ�̂��̂��m�肷��
		states[minNode] = 1;
		recentlyFixedNode = minNode;
	}
	result = minCosts[goal];
	free(minCosts);
	free(states);
	return result;
}
