#include<cstdio>
#include<cctype>
#include<cstring>
#include<cmath>
using namespace std;

inline long long read()
{
    long long x = 0, flag = 1;
    char c;
    while(! isdigit(c = getchar()))
        if(c == '-')
            flag *= - 1;
    while(isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    return x * flag;
}

void println(long long x)
{
    if(x < 0)
        putchar('-'), x *= - 1;
    if(x == 0)
        putchar('0');
    long long ans[1 << 5], top = 0;
    while(x)
        ans[top ++] = x % 10, x /= 10;
    for(; top; top --)
        putchar(ans[top - 1] + '0');
    putchar('\n');
}

const long long N = 1 << 17;

long long n;

long long a[N];
long long L[N], R[N];
long long T[N];

inline void modify(long long u, long long x)
{
    for(; u <= n; u += u & - u)
        T[u] += (long long)x;
}

long long unit, num;

long long cnt[1 << 9][N];
long long sum[1 << 9];

void update(long long x, long long y)
{
    for(long long i = 0; i < num; i ++)
        sum[i] += (long long)cnt[i][x] * (y - a[x]);
        
    modify(x, y - a[x]);
    a[x] = y;
}

inline long long query(long long u)
{
    long long ret = 0;
    
    for(; u; u -= u & - u)
        ret += T[u];
        
    return ret;
}

long long ask(long long _L, long long _R)
{
    long long lBlock = _L / unit, rBlock = _R / unit;
    long long ret = 0;
    
    if(lBlock == rBlock){
		//printf("In same block %d %d\n",_L,_R);
        for(long long i = _L; i <= _R; i ++)
            ret += query(R[i]) - query(L[i] - 1);
	}
    else
    {
        
        for(long long i = _L; i < (lBlock + 1) * unit; i ++)
            ret += query(R[i]) - query(L[i] - 1);
            
        for(long long i = unit * rBlock; i <= _R; i ++)
            ret += query(R[i]) - query(L[i] - 1);
		
		//printf("------\nPart 1=%d\n",ret);

        for(long long i = lBlock + 1; i < rBlock; i ++)
            ret += sum[i];
    }
    
    return ret;
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
    freopen("std.out", "w", stdout);
    #endif
    
    n = read();
    memset(T, 0, sizeof(T));
    
    for(long long i = 1; i <= n; i ++)
        modify(i, a[i] = read());
    
    for(long long i = 0; i < n; i ++)
        L[i] = read(), R[i] = read();
        
    unit = (long long)sqrt(n);
    long long cur = - 1;
    
    memset(cnt, 0, sizeof(cnt));
    
    for(long long i = 0; i < n; i ++)
    {
        if(i % unit == 0)
            cur ++;
        
        cnt[cur][L[i]] ++, cnt[cur][R[i] + 1] --;
    }
    
    num = cur + 1;
    
    memset(sum, 0, sizeof(sum));
    
    for(long long i = 0; i < num; i ++)
        for(long long j = 1; j <= n; j ++)
        {
            cnt[i][j] += cnt[i][j - 1];
            sum[i] += (long long)cnt[i][j] * a[j];
        }
        
    long long m = read();
    
    for(long long i = 0; i < m; i ++)
    {
         long long opt = read(), x = read(), y = read();
         
         if(opt == 1)
            update(x, y);
        else
            println(ask(x - 1, y - 1));
    }
}