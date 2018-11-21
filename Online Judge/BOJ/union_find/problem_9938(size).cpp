// 

#include <cstdio>
#include <cstring>

#define MAX_L	300000

int N, L;
int uf[MAX_L+1];
int uf_size[MAX_L+1];
int uf_count[MAX_L+1];

int root(int a) {
	while (a != uf[a]) {
		uf[a] = uf[uf[a]];
		a = uf[a];
	}
	return a;
}
bool merge(int a, int b) {
	a = root(a);
	b = root(b);
	if (a != b) {
		uf[a] = b;
		uf_size[b] += uf_size[a];
		uf_count[b] += uf_count[a];
	}
	if(uf_size[b] > uf_count[b]){
		++uf_count[b];
		return true;
	}
	return false;
}

int main() {
	scanf("%d %d\n", &N, &L);

	memset(uf_count, 0, sizeof(uf_size));
	for (int i = 0; i < L; ++i) {
		uf[i] = i;
		uf_size[i] = 1;
	}

	for (int i = 0; i < N; ++i) {
		int a, b;
		scanf("%d %d\n", &a, &b);
		printf("%s\n", merge(a, b) ? "LADICA" : "SMECE");
	}
	
	return 0;
}
