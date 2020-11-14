#include <bits/stdc++.h>
using namespace std;
// Tên chương trình
const string NAME = "testinp";
const string NAME1 = "test2";
const string NAME2 = "test_trau";
// Số test kiểm tra
const int NTEST = 200;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

long long Rand(long long l, long long h) {
    assert(l <= h);
    return l + rd() * 1LL * rd() % (h - l + 1);
}

int p[100];

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp((NAME + ".inp").c_str());
        inp<<11<<'\n';
        for(int i=1;i<=11;++i)p[i]=i;
        int ti=rd()%300;
        for(int i=1;i<=ti;++i)next_permutation(p+1,p+12);
        for(int i=1;i<=11;++i)inp<<p[i]<<" ";
        inp.close();
        system((NAME1 + ".exe").c_str());
        system((NAME2 + ".exe").c_str());
        if (system(("fc " +  NAME + ".out " + NAME + ".ans").c_str()) != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}
