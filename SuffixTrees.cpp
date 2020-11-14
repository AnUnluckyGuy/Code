/*
Input:
BANANA@
Output:
Suffix array:
6 5 3 1 0 4 2
LCP array:
0 0 1 3 0 0 2
Suffix tree:
~ROOT
{
  ~@
  ~A
  {
    ~@
    ~NA
    {
      ~@
      ~NA@
    }
  }
  ~BANANA@
  ~NA
  {
    ~@
    ~NA@
  }
}
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
const int maxN = 1e5;
using TArray = int[maxN];
string t;
int n;
TArray a, b, key, l;
int head[maxN], apos[maxN];
bool mark[maxN];
using PNode = struct TNode*;
struct TNode
{
    int ibegin, iend, depth;
    PNode parent;
    vector<PNode> children;
};
PNode root, leaf;

void ReadInput()
{
    getline(cin, t);
    n = t.length();
}

int modn(int i)
{
    i %= n;
    return i >= 0 ? i : i + n;
}

void BuildSuffixArray()
{
    //mark: đánh dấu những vị trí trong suffix array a mà khóa sơ cấp tăng lên
    //head[k]: Vị trí đầu tiên của dải khóa sơ cấp = k

    for(int i=0;i<n;++i)a[i]=i;

    sort(a,a+n,[](int i,int j)
    {
        return t[i] < t[j];
    });

    mark[0]=true;
    for (int i=1;i<n;++i)
        mark[i]=t[a[i]]!=t[a[i-1]];


    for(int len=1;len<=n;len*=2)
    {
        int nkeys=0;
        head[0]=0;
        for (int i=0;i<n;++i)
        {
            //b là vị trí đứng trước a[i] len bước
            b[i]=modn(a[i]-len);

            if(mark[i])head[nkeys++]=i;

            key[a[i]]=nkeys-1;
        }

        if(nkeys==n)break;

        for(int i=0;i<n;++i)
        {
            //a[head[key[b[i]]]++] = b[i];

            int keyval=key[b[i]];
            //key[b[i]] là khóa sơ cấp của b[i];
            //key[a[i]] là khóa thứ cấp của b[i];

            //ở đây đã có sắp xếp theo khóa thứ cấp tăng dần nên ta chỉ cần điền b[i] vào các vị trí có key = khóa sơ cấp
            //các vị trí j mà head[i]<= j <head[j+1] thì đều mang key là i nên sau mỗi lần
            //tăng head vừa được điền thì ta sẽ diền được hết n vị trí do
            //các vị trí trước j hoặc là có khóa sơ cấp nhỏ hơn (ta không quan tâm đã được hết chưa)
            //hoặc là có khóa sơ cấp bằng nhưng khóa thứ cấp nhỏ hơn (key[a[i]]<=key[a[i+1]]) nên đã được điền trước(ta duyệt i từ 0>n-1)
            a[head[keyval]]=b[i];

            ++head[keyval];
        }

        //bây giờ a là dãy hậu tố xếp theo 2*len ký tự đầu, cập nhật mảng mark
        //Chú ý những chỗ đã đánh dấu ứng với khóa sơ cấp khác nhau
        //Chỉ đánh đấu những chỗ ứng với khóa thứ cấp khác nhau nữa thôi

        for(int i=1;i<n;++i)
            if(key[modn(a[i]+len)]!=key[modn(a[i-1]+len)])mark[i]=true;
    }
}

void BuildLCPArray()
{
    for (int i = 0; i < n; ++i)
        apos[a[i]] = i;
    int q = 0;
    l[0] = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        int j = a[apos[i] - 1];
        while (t[i + q] == t[j + q]) ++q;
        l[apos[i]] = q;
        if (q > 0) --q;
    }
}

void InsertSuffix(int i, int lcp)
{
    PNode u = leaf, v;
    while (u->depth > lcp)
    {
        v = u;
        u = u->parent;
    }
    if (u->depth < lcp)
    {
        PNode w = new TNode
        {
            ibegin:v->ibegin,
            iend:v->iend - (v->depth - lcp),
            depth:lcp,
            parent:u
        };
        u->children.pop_back();
        u->children.push_back(w);
        v->ibegin = w->iend;
        v->parent = w;
        w->children.push_back(v);
        u = w;
    }
    leaf = new TNode
    {
        ibegin:i + lcp,
        iend:n,
        depth:n - i,
        parent:u
    };
    u->children.push_back(leaf);
}

void BuildSuffixTree()
{
    root = new TNode{ibegin:0, iend:0, depth:0, parent:nullptr};
    leaf = root;
    for (int i = 0; i < n; ++i)
        InsertSuffix(a[i], l[i]);
}

void WriteBlank(int indent)
{
    for (int i = 0; i < indent; ++i)
        cout << "  ";
}

void ShowTree(PNode x, int level)
{
    WriteBlank(level);
    if (x == root)
        cout << "~ROOT\n";
    else
        cout << "~" << t.substr(x->ibegin, x->iend - x->ibegin) << '\n';
    if (x->children.empty()) return;
    WriteBlank(level);
    cout << "{\n";
    for (PNode y: x->children)
        ShowTree(y, level + 1);
    WriteBlank(level);
    cout << "}\n";
}

void Print()
{
    cout << "Suffix array: \n";
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << '\n';
    /*cout << "LCP array: \n";
    for (int i = 0; i < n; ++i)
        cout << l[i] << ' ';
    cout << '\n';
    cout << "Suffix tree:\n";
    ShowTree(root, 0);*/
}

int main()
{
    ReadInput();
    BuildSuffixArray();
    //BuildLCPArray();
    //BuildSuffixTree();
    Print();
}
