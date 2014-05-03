#include <iostream>
#include <cstring>
#define MAX_SIZE 51
using namespace std;
int f[2*MAX_SIZE+1][MAX_SIZE][MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE];
int m,n;
int max(int a,int b)
{
	if(a>b)
		return a;
	return b;
}
void execute()
{
	if(m==1||n==1)
	{
		cout<<0<<endl;
		return ;
	}
	memset(f,0,sizeof(f));
	int k,i,j;
	for(k=3;k<m+n;k++)
	{
		for(i=2;i<k&&i<=m;i++)
		{
			if(k-i>=n)
				continue;
			for(j=1;j<=k+1&&j<=m-1;j++)
			{
				if(i==j)
					continue;
				f[k][i][j]=max(max(f[k-1][i-1][j],f[k-1][i-1][j-1]),max(f[k-1][i][j-1],f[k-1][i][j]));
				f[k][i][j]=f[k][i][j]+a[i][k-i]+a[j][k-j];
			}
		}
	}
	int ans=f[m+n-1][m][m-1]+a[m][n];
	cout<<ans<<endl;

}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>m>>n;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				cin>>a[i][j];
		execute();
	}
	return 0;
}        