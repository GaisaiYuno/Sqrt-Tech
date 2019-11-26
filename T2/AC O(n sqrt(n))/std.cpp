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
namespace alb{
	ull sum[MAXN],tag[MAXN];
	void Update(int i,int delta){
		int id=pos[i],rb=min(id*Size,n);
		for (int j=i;j<=rb;++j) sum[j]+=delta;
		for (int j=id+1;j<=pos[n];++j) tag[j]+=delta;
	}
	ull GetVal(int i){
		return sum[i]+tag[pos[i]];
	}
	ull Sum(int l,int r){
		return GetVal(r)-GetVal(l-1);
	}
}
using namespace alb;
int cnt[MAXM][MAXN];
ull val[MAXM];
int L[MAXN],R[MAXN];
void Init(){
	for (int i=1;i<=pos[n];++i){
		int lb=(i-1)*Size+1,rb=min(i*Size,n);
		for (int j=lb;j<=rb;++j) cnt[i][L[j]]++,cnt[i][R[j]+1]--;
		for (int j=1;j<=n;++j) cnt[i][j]+=cnt[i][j-1];
	}
}
void Rebuild(int index,int delta){
	for (int i=1;i<=pos[n];++i) val[i]+=1ull*delta*cnt[i][index];
	Update(index,delta);
}
ull BF(int l,int r){
	ull ans=0;
	for (int i=l;i<=r;++i) ans+=Sum(L[i],R[i]);
	return ans;
}
ull Query(int l,int r){
	if (pos[l]==pos[r]){
		return BF(l,r);
	}
	int lid=pos[l],rid=pos[r];
	int rb=min(lid*Size,n),lb=(rid-1)*Size+1;
	ull ans=BF(l,rb)+BF(lb,r);
	for (int i=lid+1;i<=rid-1;++i) ans+=val[i];
	return ans;
}
int main(){
	n=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=1;i<=n;++i){L[i]=read();R[i]=read();}
	Size=sqrt(n);
	for (int i=1;i<=n;++i) pos[i]=(i-1)/Size+1;
	Init();
	for (int i=1;i<=n;++i) Rebuild(i,a[i]);
	int q=read();
	while (q--){
		int opr=read();
		if (opr==1){
			int x=read(),y=read();
			Rebuild(x,y-a[x]);
			a[x]=y;
		}
		else {
			int l=read(),r=read();
			printf("%llu\n",Query(l,r));
		}
	}
}
