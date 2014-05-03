#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;
int max(int x,int y){return x>y?x:y;}
int head[505],val[10010],next[10010],key[10010];
int e[5005];
bool vis[505];
int lft,rht,maxv,minv;
int start,end,n,cnt,num;
int gcd(int a,int b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
void add(int u,int v,int w)
{
	val[num]=w;
	next[num]=head[u];
	key[num]=v;
	head[u]=num++;
}
bool dfs(int u)
{
	vis[u]=true;
	if(u==end)
		return true;
	for(int i=head[u];i!=-1;i=next[i])
	{
		int u=key[i];
		if(!vis[u]&&val[i]>=lft&&val[i]<=rht)
		{
			if(dfs(u))
				return true;
		}
	}
	return false;
}
bool solve(double t)
{
	for(int i=0;i<cnt;++i)
	{
		memset(vis,0,sizeof(vis));
		lft=e[i];
		rht=e[i]*t;
		if(dfs(start))
			return true;
	}
	return false;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int m,i,u,v,w;
		scanf("%d%d",&n,&m);
		num=0,cnt=1;
		memset(head,-1,sizeof(head));
		memset(next,-1,sizeof(next));
		int temp=0;
		for(i=0;i<m;++i)
		{
			scanf("%d%d%d",&u,&v,&w);
			e[i]=w;
			add(u,v,w);
			add(v,u,w);
		}
		scanf("%d%d",&start,&end);
		sort(e,e+m);
		for(i=1;i<m;++i)
			if(e[i]!=e[cnt-1])e[cnt++]=e[i];
		double l=1,r=(double)e[cnt-1]/e[0]+1;
		while(r-l>1e-4)
		{
			double m=(r+l)/2;
			if(solve(m))
				r=m;
			else
				l=m;
		}
		solve(r);
		maxv=rht;minv=lft;
		if(maxv%minv)
		{
			int temp=gcd(maxv,minv);
			printf("%d/%d\n",maxv/temp,minv/temp);
		}
		else
			printf("%d\n",maxv/minv);
	}
	return 0;
}