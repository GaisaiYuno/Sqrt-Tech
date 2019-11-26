#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9'){
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+(ch^'0');
		ch=getchar();
	}
	return x*f;
}
int dep[MAXN],to[MAXN];//预处理一个点跳多少步能跳出这个块，跳到哪里
int n,Size;
int a[MAXN],pos[MAXN];
void Rebuild(int p,int id){//p是很屑的优化
	int l=(id-1)*Size,r=min(p,id*Size-1);
	for (int i=r;i>=l;--i){//倒着搞
		if (pos[a[i]]!=pos[i]) dep[i]=1,to[i]=a[i];
		else dep[i]=dep[a[i]]+1,to[i]=to[a[i]];
	}
}
int Query(int x){
	int ans=0;
	while (true){
		ans+=dep[x],x=to[x];
		if (pos[x]==0) return ans;
	}
	return -1;
}
int main(){
	n=read();
	for (int i=0;i<n;++i) a[i]=i+read();//弹到哪个位置
	Size=sqrt(n);
	for (int i=0;i<n;++i) pos[i]=i/Size+1;
	for (int i=1;i<=pos[n-1];++i) Rebuild(0x7fffffff,i);
	int m=read();
	while (m--){
		int opr=read(),i=read();
		if (opr==1){
			printf("%d\n",Query(i));
		}
		else {
			a[i]=i+read();
			Rebuild(i,pos[i]);
		}
	}
}
