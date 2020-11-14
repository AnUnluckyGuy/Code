struct Node {
    int left, right;    // ID of left child & right child
    long long ln;       // Max value of node
    Node() {}
    Node(long long ln, int left, int right) : ln(ln), left(left), right(right) {}
} it[11000111];         // Each node has a position in this array, called ID
int nNode;

int ver[MN];            // ID of root in each version

// Update max value of a node
inline void refine(int cur) {
    it[cur].ln = max(it[it[cur].left].ln, it[it[cur].right].ln);
}

// Update a range, and return new ID of node
int update(int l, int r, int u, int x, int oldId) {
    if (l == r) {
        ++nNode;
        it[nNode] = Node(x, 0, 0);
        return nNode;
    }

    int mid = (l + r) >> 1;
    int cur = ++nNode;

    if (u <= mid) {
        it[cur].left = update(l, mid, u, x, it[oldId].left);
        it[cur].right = it[oldId].right;
        refine(cur);
    }
    else {
        it[cur].left = it[oldId].left;
        it[cur].right = update(mid+1, r, u, x, it[oldId].right);
        refine(cur);
    }

    return cur;
}

// Get max of range. Same as usual IT
int get(int nodeId, int l, int r, int u, int v) {
    if (v < l || r < u) return -1;
    if (u <= l && r <= v) return it[nodeId].ln;

    int mid = (l + r) >> 1;
    return max(get(it[nodeId].left, l, mid, u, v), get(it[nodeId].right, mid+1, r, u, v));
}


// When update:
    ++nVer;
    ver[nVer] = update(1, n, u, x, ver[nVer-1]);

// When query:
    res = get(ver[t], 1, n, u, v);

///////////////////
#define _(x) (x & (-(x)))

// Persistent BIT
vector< pair<int,int> > bit[4100][4100];

// Add val to cell (x, y) at time = time
void update(int x, int y, int val, int time) {
    for(int u = x; u <= 4096; u += _(u))
        for(int v = y; v <= 4096; v += _(v)) {
            if (bit[u][v].empty()) {
                bit[u][v].push_back(make_pair(time, val));
            }
            else {
                int cur = bit[u][v][bit[u][v].size()-1].second;
                bit[u][v].push_back(make_pair(time, cur + val));
            }
        }
}

// Get the sum of square (1,1) --> (x, y) at time = time
int get(int time, int x, int y) {
    int res = 0;
    for(int u = x; u > 0; u -= _(u))
        for(int v = y; v > 0; v -= _(v)) {
            if (bit[u][v].empty()) {
            }
            else if (bit[u][v][bit[u][v].size()-1].first <= time) {
                res += bit[u][v][bit[u][v].size()-1].second;
            }
            else {
                int pos = upper_bound(bit[u][v].begin(), bit[u][v].end(), make_pair(time, 2000111000))
                        - bit[u][v].begin() - 1;
                if (pos >= 0)
                    res += bit[u][v][pos].second;
            }
        }
    return res;
}
