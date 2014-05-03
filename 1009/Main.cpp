 
#include <iostream>
#include <cstring>
using namespace std;
int a[1001];
int n,m;
int f[1001];
void execute()
{
	memset(f,0x7E,sizeof(f));
	int i,j;
	f[0]=m;
	for(i=1;i<=n;i++)
		f[i]=f[i-1]+a[i];
	for(i=2;i<=n;i++)
	{
		for(j=1;j<=i;j++)
		{
			if(f[i]>f[j]+f[i-j]+m)
				f[i]=f[j]+f[i-j]+m;
		}
	}
	cout<<f[n]<<endl;
}
int main()
{
	int i;
	int T;
	cin>>T;
	while(T--&&cin>>n>>m)
	{
		for(i=1;i<=n;i++)
			cin>>a[i];
		execute();
	}
	return 0;
}        