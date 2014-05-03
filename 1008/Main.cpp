#include <iostream>
#include <cstring>
using namespace std;
int n,m;
long long int f[111][111][2];
void init()
{
	memset(f,0,sizeof(f));
	int i,j;
	for(i=1;i<=100;i++)
		f[i][i+1][1]=1;
	f[0][1][0]=1;
	f[0][1][1]=1;
	for(i=2;i<=100;i++)
	{
		f[0][i][0]=f[0][i-1][0]+f[0][i-1][1];
		f[0][i][1]=f[0][i-1][0];
	}
	for(i=1;i<=100;i++)
		for(j=i+2;j<=100;j++)
		{
			f[i][j][0]=f[i][j-1][1]+f[i][j-1][0];
			f[i][j][1]=f[i][j-1][0]+f[i-1][j-1][1];
		}
}
int main()
{
	init();
	int T;
	cin>>T;
	while(T--)
	{
		while(cin>>n>>m)
			cout<<f[m][n][0]+f[m][n][1]<<endl;
	}
	return 0;
}        

