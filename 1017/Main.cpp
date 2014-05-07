#include <iostream>
#include <algorithm>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cctype>
using namespace std;

#define rep(i, n) for (int i=0; i<(n); ++i)
#define repf(i, a, b) for (int i=(a); i<=(b); ++i)
#define repd(i, a, b) for (int i=(a); i>=(b); --i)
#define clr(a, b) memset(a, b, sizeof(a))
#define sz(a) ((int)(a).size())
#define pb push_back
#define N 1000

int i,j,k,m,n,l;
int f[N+10];
bool v[N+10];

void init(){
	repf(i, 1, N) f[i]=i;
	repf(i, 2, N) if (!v[i])
		repf(j, 2, N/i)
			v[i*j]=1, f[i*j]/=i, f[i*j]*=(i-1);
	
}

int main(){
	init();

	int ts;
	scanf("%d", &ts);
	while (ts--){
		scanf("%d", &n);
		int ans=2;
		repf(i, 1, n-1) ans+=2*f[i];
		cout<<ans<<endl;
	}
	return 0;
}