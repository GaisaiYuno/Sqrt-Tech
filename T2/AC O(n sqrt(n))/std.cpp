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
struct FK1{
	ull sum[MAXN],tag[MAXN];
	void Update(int i,int v){
		int id=pos[i],rb=min(id*Size,n);
		for (int j=i;j<=rb;++j) sum[j]+=v;
		for (int j=id+1;j<=pos[n];++j) tag[j]+=v;
	}
	ull GetVal(int i){
		return sum[i]+tag[pos[i]];
	}
	ull Sum(int l,int r){
		return GetVal(r)-GetVal(l-1);
	}
}Kaffu;
struct FK2{
	int sum[MAXN],tag[MAXN];
	void BF(int l,int r,int v){
		for (int j=l;j<=r;++j) sum[j]+=v;
	}
	void Update(int l,int r,int v){
		int lid=pos[l],rid=pos[r];
		if (lid==rid) return BF(l,r,v),void();
		int rb=min(lid*Size,n),lb=(rid-1)*Size+1;
		BF(l,rb,v),BF(lb,r,v);
		for (int i=lid+1;i<=rid-1;++i) tag[i]+=v;
	}
	int GetVal(int i){
		return sum[i]+tag[pos[i]];
	}
}Chino[MAXM];
int cnt[MAXM][MAXN];
ull val[MAXM];
int L[MAXN],R[MAXN];
void Init(){
	for (int i=1;i<=pos[n];++i){
		int lb=(i-1)*Size+1,rb=min(i*Size,n);
		for (int j=lb;j<=rb;++j) Chino[i].Update(L[i],R[i],1);
	}
}
void Rebuild(int index,int v){
	for (int i=1;i<=pos[n];++i) val[i]+=1ull*v*Chino[i].GetVal(index);
	Kaffu.Update(index,v);
}
void UpdateInterval(int index,int l,int r){
	int id=pos[index];
	val[id]-=Kaffu.Sum(L[index],R[index]);
	val[id]+=Kaffu.Sum(l,r);
	Chino[id].Update(L[index],R[index],-1);
	Chino[id].Update(l,r,1);
	L[index]=l,R[index]=r;
}
ull BF(int l,int r){
	ull ans=0;
	for (int i=l;i<=r;++i) ans+=Kaffu.Sum(L[i],R[i]);
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
			int p=read(),x=read();
			Rebuild(p,x-a[p]);
			a[p]=x;
		}
		else if (opr==2){
			int l=read(),r=read();
			printf("%llu\n",Query(l,r));
		}
		else {
			int p=read(),l=read(),r=read();
			UpdateInterval(p,l,r);
		}
	}
}
