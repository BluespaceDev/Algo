#include <cstdio>

#define MAX_G	100000

int G, P;
int uf[MAX_G+1];

int find(int a) {
	while (a != uf[a]) {
		uf[a] = uf[uf[a]];
		a = uf[a];
	}
	return a;
}
bool pushable(int a) {
	a = find(a);
	if (a > 0) {
		uf[a] = a - 1;
		return true;
	}
	return false;
}

int main() {
	scanf("%d %d\n", &G, &P);

	for (int i = 0; i <= G; ++i)
		uf[i] = i;

	int p;
	for (p = 0; p < P; ++p) {
		int a;
		scanf("%d\n", &a);
		if (!pushable(a)) break;
	}
	printf("%d\n", p);

	return 0;
}
