//#include <stdio.h>
//
//#define MAX_N 100001
//#define INT_MAX       2147483647    // maximum (signed) int value
//
//int N, Q, arg1, arg2, R, RES[MAX_N], STREE[2 * MAX_N];
//char code;
//
//int min(int a, int b) { return a <= b ? a : b; }
//
//void init()
//{	
//	for (int i = N - 1; i > 0; --i) {
//		//printf(">>init: tree[nodeid=%d]=%d, tree[lchildID=%d]=%d, tree[rchildID=%d]=%d\n", i, STREE[i], i<<1, STREE[i<<1], i<<1|1,STREE[i<<1|1]);
//		STREE[i] = min(STREE[i << 1], STREE[i << 1 | 1]);
//		//printf("<<init: tree[nodeid=%d]=%d, tree[lchildID=%d]=%d, tree[rchildID=%d]=%d\n", i, STREE[i], i << 1, STREE[i << 1], i << 1 | 1, STREE[i << 1 | 1]);
//	}
//}
//
//void update(int index, int value) {
//	//printf("[update]: STREE[index=%d]=%d, new_value=%d", index, STREE[index + N], value);
//	STREE[index+N] = value;
//	for (int i = index + N; i > 1; i >>= 1) {
//		//printf(">>update: tree[nodeid=%d]=%d, tree[lchildID=%d]=%d, tree[rchildID=%d]=%d\n", i>>1, STREE[i>>1], i, STREE[i], i^1, STREE[i^1]);
//		STREE[i>>1] = min(STREE[i], STREE[i^1]);
//		//printf("<<update: tree[nodeid=%d]=%d, tree[lchildID=%d]=%d, tree[rchildID=%d]=%d\n", i >> 1, STREE[i >> 1], i, STREE[i], i ^ 1, STREE[i ^ 1]);
//	}
//}
//
//int query(int qs, int qe) {
//	int res = INT_MAX;
//	//printf("[query]: qs=%d, qe=%d", qs, qe);
//	for (int l = qs + N, r = qe + N; l < r; l >>= 1, r >>= 1) {
//		if (l & 1) { res = min(res, STREE[l++]); }
//		if (r & 1) { res = min(res, STREE[--r]); }
//	}
//	return res;
//}
//
//int main() {
//	freopen("unit_test_input.txt", "r", stdin);
//	freopen("unit_test_output.txt", "w", stdout);
//
//	scanf("%d %d\n", &N, &Q);
//	for (int i = N; i < 2*N; i++) { scanf("%d", &STREE[i]); }
//	scanf("\n");
//
//	init();
//
//	R = 0;
//	for (int i = 0; i < Q; i++) {
//		scanf("%c %d %d\n", &code, &arg1, &arg2);
//		//printf("trace: %d %d\n", arg1, arg2);
//		if (code == 'u') { update(arg1 - 1, arg2); }
//		else if (code == 'q') {
//			RES[R++] = query(arg1 - 1, arg2);
//			//printf("%d (%c %d %d)\n", RES[R - 1], code, arg1, arg2);
//		}
//	}
//
//	for (int i = 0; i < R; i++)printf("%d\n", RES[i]);
//
//	return 0;
//}