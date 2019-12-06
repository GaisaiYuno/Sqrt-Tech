#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 405
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
int RandInt(){
	return (rand()<<15)|rand();
}
int Rand(int l,int r){
	return RandInt()%(r-l+1)+l;
}
int main(){
	srand(time(NULL));
	//freopen("stars10.in","w",stdout);
	int n=5;
	printf("%d\n",n);
	for (int i=1;i<=n;++i){
		printf("%d\n",Rand(1,20));
	}
	for (int i=1;i<=n;++i){
		int l=Rand(1,n),r=Rand(1,n);
		if (l>r) swap(l,r);
		printf("%d %d\n",l,r);
	}
	int q=6;
	printf("%d\n",q);
	for (int i=1;i<=q;++i){
		int opr=Rand(1,3);
		printf("%d ",opr);
		if (opr==1) printf("%d %d\n",Rand(1,n),Rand(1,20));
		else if (opr==2) {
			int l=Rand(1,n),r=Rand(1,n);
			if (l>r) swap(l,r);
			printf("%d %d\n",l,r);
		}
		else {
			int l=Rand(1,n),r=Rand(1,n);
			if (l>r) swap(l,r);
			printf("%d %d %d\n",Rand(1,n),l,r);
		}
	}
}
