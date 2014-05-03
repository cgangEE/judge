#include <iostream>
#include <cstring>
using namespace std;
int a[14];
int flag[14];
int n;
void execute()
{
	if(n==1)
	{
		cout<<1<<endl;
		return ;
	}
	memset(flag,0,sizeof(flag));
	int i,len=0,t=1,k=0,sum=0;
	while(len<n)
	{
		while(sum!=t+1)
		{
			k++;
			if(k==n+1)
				k=1;
			if(flag[k]==0)
				sum++;
		}
		a[k]=t;
		flag[k]=1;
		t++;
		sum=0;
		len++;
	}
	for(i=1;i<n;i++)
		cout<<a[i]<<' ';
	cout<<a[n]<<endl;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		execute();
	}
	return 0;
}        