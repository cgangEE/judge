#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main ()
{
    int K,N,L,i,j,k,n,m,max,maxpos;
    int a[1000],b[6];
    scanf("%d",&K);
    for(n=0;n<K;n++)
    {
	 max=0;/*重置*/ 
	 maxpos=0;/*重置maxpos的值为零，为下一组数据做准备*/ 
	 scanf("%d%d",&L,&N);
	 for(i=0;i<N;i++)
	   scanf("%d",&a[i]);
	 for(j=0;j<N-L+1;j++)
	   {
	    m=0;/*重置*/
		for(k=0;k<L;k++)
		 m=a[j+k]+m;
	    if(m>max)
	  	 {max=m;
	  	  maxpos=j+1; 
		 }
	   }
	 b[n]=maxpos;
    }
	for(k=0;k<K;k++)
	 printf("%d
",b[k]);
	system("pause");
	return 0;  
}