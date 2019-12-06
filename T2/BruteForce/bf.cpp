#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 405
#define ull unsigned long long
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
int a[MAXN],Size,pos[MAXN],n;
int L[MAXN],R[MAXN];
int main(){
	n=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=1;i<=n;++i) L[i]=read(),R[i]=read();
	int q=read();
	while (q--){
		int opr=read();
		if (opr==1){
			int p=read(),x=read();
			a[p]=x;
		}
		else if (opr==2){
			int l=read(),r=read();
			ull ans=0;
			for (int i=l;i<=r;++i){
				for (int j=L[i];j<=R[i];++j){
					ans+=a[j];
				}
			}
			printf("%llu\n",ans);
		}
		else {
			int p=read(),l=read(),r=read();
			L[p]=l,R[p]=r;
		}
	}
}

/*
5
1 2 3 4 5
1 3
2 5
4 5
3 5
1 2
6
2 1 4
3 3 1 5
1 3 7
2 1 4
3 4 2 3
2 3 5
*/
