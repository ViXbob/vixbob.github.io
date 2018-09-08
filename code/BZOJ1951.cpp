#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e4 + 5;
const int P[5] = {999911659, 2, 3, 4679, 35617};

int fac[5][maxn], G, N, num[maxn], a[5];

inline int read(){
	char ch = getchar(); int u = 0, f = 1;
	while(!isdigit(ch)){if(ch == '-')f = -1; ch = getchar();}
	while(isdigit(ch)){u = u * 10 + ch - 48; ch = getchar();} return u * f;
}

inline int ksm(int x, int k, int mod){
	if(x == mod)return 0;
	int cnt = 1;
	while(k){
		if(k & 1)cnt = 1ll * cnt * x % mod;
		x = 1ll * x * x % mod; k >>= 1;
	} return cnt;
}

inline int com(int n, int m, int k){
	if(m > n)return 0;
	return (int)(1ll * fac[k][n] * ksm(fac[k][n - m], P[k] - 2, P[k]) % P[k] * ksm(fac[k][m], P[k] - 2, P[k]) % P[k]);
}

inline int C(int n, int m, int k){
	if(m == 0 || n == 0)return 1;
	return (int)(1ll * C(n / P[k], m / P[k], k) * com(n % P[k], m % P[k], k) % P[k]);
}

inline int exgcd(int a, int b, int &x, int &y){
	if(b == 0){x = 1; y = 0; return a;}
	int x0 = 0, y0 = 0;
	int d = exgcd(b, a % b, y0, x0);
	x = x0; y = y0 - ((a / b) * x0);
	return d;
}

inline int china(int *a, const int *m, int n){
	int A = 0, M = 1, tmp;
	for(register int i = 1; i <= n; i++)M *= m[i];
	for(register int i = 1; i <= n; i++){
		int Mi = M / m[i], inv;
		exgcd(Mi, m[i], inv, tmp);
		A = (A + 1ll * a[i] * Mi * inv) % M;
	} return (A % M + M) % M;
}

int main(){
	N = read(); G = read();
	for(register int i = 1; i * i <= N; i++)
		if(N % i == 0){
			num[++num[0]] = i;
			if(i * i != N)num[++num[0]] = N / i;
		}
	for(register int k = 1; k < 5; k++){
		fac[k][0] = 1;
		for(register int i = 1; i < maxn; i++)
			fac[k][i] = 1ll * fac[k][i - 1] * i % P[k];
	}
	for(register int k = 1; k < 5; k++)
		for(register int i = 1; i <= num[0]; i++)
			a[k] = (a[k] + C(N, num[i], k)) % P[k];
	/*for(register int i = 1; i <= num[0]; i++)
		cout << "num[" << i << "] = " << num[i] << endl;
	for(register int i = 1; i < 5; i++)
		cout << "a[" << i << "] = " << a[i] << endl;
	int o = china(a, P, 4);
	cout << "P = " << o << endl;
	cout << "G = " << G << endl;*/
	cout << ksm(G, china(a, P, 4), P[0]);
	return 0;
}
