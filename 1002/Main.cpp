#include<stdio.h>
#define N 1005
int a[N];
int main()
{
    int t,k,n,i,j,s,max,u;
    scanf("%d",&t);
    while(t--)
    {
      scanf("%d%d",&k,&n);
      for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
        max=-1;
      for(i=1;i<=n+1-k;i++)
      {
         s=0;
        for(j=i;j<=i+k-1;j++)
        {
            s+=a[j];
        }
        if(s>max)
          {
              max=s;
              u=i;
          }
      }
      if(max<0)
         printf("0
");
    else
       printf("%d
",u);
    }
    return 0;
}
