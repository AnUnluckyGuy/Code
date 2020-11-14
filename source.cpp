#include<bits/stdc++.h>
#define For(i, a, b)  for(int i = a; i <= b; ++i)
#define Ford(i, a, b) for(int i = a; i >= b; --i)
#define F             ""
#define READ          freopen(F".inp", "r", stdin)
#define WRITE         freopen(F".out", "w", stdout)
#define ll            long long
#define ld            long double
#define ull           unsigned long long
#define pb            push_back
#define X             first
#define Y             second

const int N = 1e6 + 7;
const int M = 1e5 + 7;
const double pi = atan(1.0) * 4;

using namespace std;

int pr[N >> 6], d;
#define turnOn(p) (pr[p >> 6] |= 1 << ((p >> 1) & 31))
#define get(p) (pr[p >> 6] & (1 << ((p >> 1) & 31)))
void Sieve()
{
    for(int i = 3; i * i <= N; i += 2)
    {
        if(!get(i))
        {
            d = i << 1;
            for(int j = i * i; j <= N; j += d) turnOn(j);
        }
    }
}

template <typename T> inline void Cin(T &x)
{
    char c;
    T sign = 1;
    x = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-') sign = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= sign;
}

template <typename T> inline void Out(T x)
{
    if (x == 0) return;
    Out(x / 10);
    putchar(x % 10 + '0');
}

template <typename T> inline void Cout(T x)
{
    if (x == 0)
    {
        putchar('0');
        return;
    }
    if (x < 0) putchar('-'), x = -x;
    Out(x);
}

ll Mul(ll x, ll y)
{
    x %= mod;
    y %= mod;
    ull q = (long double) x * y / mod;
    ll r = (ll)(x * y - q * mod) % (ll)mod;
    if (r < 0) r += mod;
    return r;
}

ll Power(ll a, ll b)
{
    if(b < 0) return 0;
    ll kq, tg;
    if (b == 0) return 1;
    else
    {
        tg = Power(a, b/2) % mod;
        if (b % 2 == 0) return Mul(tg,tg) % mod;
        else return Mul(Mul(tg,tg),a) % mod;
    }
}

void Sieve()
{
    for (int i = 2; i < N; ++i) pr[i] = i;
    for (int i = 2; i < N; ++i)
        if (pr[i] == i)
            for (int j = i * 2; j < N; j += i)
                if (i < pr[j]) pr[j] = i;
}

void Phi()
{
    for (int i = 1; i <= N; i++) phi[i] = i;
    for (int i = 2; i <= N; i++)
        if (phi[i] == i)
            for (int j = i; j <= N; j += i)
                phi[j] -= phi[j]/i;
}

void Mobius()
{
    mu[1] = 1;
    for (int i = 1; i <= N; i++)
        for (int j = 2*i; j <= N; j += i)
            mu[j] -= mu[i];
}

int main()
{
#ifdef BeztDonkey
    auto start = chrono::steady_clock::now();
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);

#ifdef BeztDonkey
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
#endif
    return 0;
}
//Geogrebra
//giao hai đoạn thẳng
//p x AB + q x CD = AC
//p = (AC x CD) / (AB x CD)
//AM = p * AB
//OM = OA + p * AB
//M = A + p(B - A)
//p = 0 => M = A
//p = 1 => M = B
//0 < p < 1 => M thuoc AB
