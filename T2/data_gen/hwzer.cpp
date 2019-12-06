#include<cstdio>
#include<cmath>
#include<iostream>
#define ll unsigned long long
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch>'9'||ch<'0')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
ll ans[505],t[100005];
int n,q,blo,cnt;
int bl[505],l[505],r[505];
int c[505][100005];
ll a[100005];
int S[100005],T[100005];
void add(int x,int val)
{
	for(int i=x;i<=n;i+=i&-i)
		t[i]+=val;
}
ll query(int x)
{
	ll tmp=0;
	for(int i=x;i;i-=i&-i)
		tmp+=t[i];
	return tmp;
}
void insert(int t)
{
	add(S[t],1);add(T[t]+1,-1);
}
void del(int t)
{
	add(S[t],-1);add(T[t]+1,1);
}
void pre()
{
	for(int i=1;i<=cnt;i++)
	{
		for(int j=l[i];j<=r[i];j++)
			insert(j);
		for(int j=1;j<=n;j++)
		{
			c[i][j]=query(j);
			ans[i]+=a[j]*c[i][j];
		}
		for(int j=l[i];j<=r[i];j++)
			del(j);
	}
}
ll query(int x,int y)
{
	ll tmp=0;
	int L=bl[x],R=bl[y];
	for(int i=L+1;i<R;i++)
		tmp+=ans[i];
	if(bl[x]==bl[y])
		for(int i=x;i<=y;i++)
			tmp+=query(T[i])-query(S[i]-1);
	else 
	{
		for(int i=x;i<=r[L];i++)
			tmp+=query(T[i])-query(S[i]-1);
		for(int i=l[R];i<=y;i++)
			tmp+=query(T[i])-query(S[i]-1);
	}
	return tmp;
}
int main()
{
	freopen("FNCS2.in","r",stdin);
	freopen("FNCS2.ans","w",stdout);
	n=read();
	blo=sqrt(n);
	cnt=n/blo+(n%blo!=0);
	for(int i=1;i<=n;i++)
	{
		bl[i]=(i-1)/blo+1;
		if(!l[bl[i]])l[bl[i]]=i;
		r[bl[i]]=i;
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)
		S[i]=read(),T[i]=read();
	pre();
	for(int i=1;i<=n;i++)add(i,a[i]);
	q=read();
	while(q--)
	{
		int opt=read(),x=read(),y=read();
		if(opt==1)
		{
			add(x,y-a[x]);
			for(int i=1;i<=cnt;i++)
				ans[i]+=c[i][x]*(y-a[x]);
			a[x]=y;
		}
		else 
			printf("%llu\n",query(x,y));
	}
	return 0;
}
