 
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#define INF 0x7FFFFFFF
using namespace std;
struct tt
{
	int x,y;
	int lx,rx;
}a[1001];
int n,r,ans;
int comp(const void *x,const void *y)
{
	return (*(tt *)x).lx>(*(tt *)y).lx?1:-1;
}
void execute()
{
	int i;
	int m=-INF;
	ans=0;
	for(i=0;i<n;i++)
	{
		if(a[i].rx>m)
		{
			ans++;
			m=a[i].lx;
		}
	}
	cout<<ans<<endl;
}
int main()
{
	int T;
	cin>>T;
	int x,y;
	while(T--)
	{
		cin>>n>>r;
		for(int i=0;i<n;i++)
		{
			cin>>a[i].x>>a[i].y;
			a[i].lx=a[i].x+sqrt(r*r-a[i].y*a[i].y);
			a[i].rx=a[i].x-sqrt(r*r-a[i].y*a[i].y);
		}
		qsort(a,n,sizeof(a[0]),comp);
		execute();
	}
	return 0;
}        