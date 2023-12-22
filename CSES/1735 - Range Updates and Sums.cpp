/**
 *    author: martin_nguyen (strongcourage)
 *    Range Updates and Sums
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 200010;
vector<ll> arr(MAXN);

struct Node {
  ll sum;
  ll lazyAdd; // for add()
  ll lazySet; // for update()
};

Node segtree[4 * MAXN];

void pushup(int id) {
  segtree[id].sum = segtree[id * 2].sum + segtree[id * 2 + 1].sum;
}

void pushdown(int id, int l, int mid, int r) {
  int lid = id << 1;
  int rid = (id << 1) + 1;
  if (segtree[id].lazySet != 0) {
    segtree[lid].lazySet = segtree[rid].lazySet = segtree[id].lazySet;
    
    segtree[lid].sum = (mid - l + 1) * segtree[id].lazySet;
    segtree[rid].sum = (r - mid) * segtree[id].lazySet;
    
    segtree[lid].lazyAdd = segtree[rid].lazyAdd = 0;
    segtree[id].lazySet = 0;
  } else if (segtree[id].lazyAdd != 0) {
    if (segtree[lid].lazySet == 0) segtree[lid].lazyAdd += segtree[id].lazyAdd;
    else {
      segtree[lid].lazySet += segtree[id].lazyAdd;
      segtree[lid].lazyAdd = 0;
    }

    if (segtree[rid].lazySet == 0) segtree[rid].lazyAdd += segtree[id].lazyAdd;
    else {
      segtree[rid].lazySet += segtree[id].lazyAdd;
      segtree[rid].lazyAdd = 0;
    }

    segtree[lid].sum += (mid - l + 1) * segtree[id].lazyAdd;
    segtree[rid].sum += (r - mid) * segtree[id].lazyAdd;
    segtree[id].lazyAdd = 0;
  }
}

void build(int id, int l, int r) {
  segtree[id].lazyAdd = segtree[id].lazySet = 0; 

  if (l == r) {
    segtree[id].sum = arr[l];
    return;
  }

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  pushup(id);
}


ll get(int id, int l, int r, int u, int v) {
  if (v < l || r < u) return 0;
  if (u <= l && r <= v) return segtree[id].sum;

  int mid = (l + r) / 2;
  pushdown(id, l, mid, r);
  return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

void add(int id, int l, int r, int u, int v, ll val) {
  if (v < l || r < u) return;
  if (u <= l && r <= v) {
    segtree[id].sum += (r - l + 1) * val;
    
    if (segtree[id].lazySet == 0) segtree[id].lazyAdd += val;
		else segtree[id].lazySet += val;
    
    return;
  }
  
  int mid = (l + r) / 2;
  pushdown(id, l, mid, r);
  add(id * 2, l, mid, u, v, val);
  add(id * 2 + 1, mid + 1, r, u, v, val);
  pushup(id);
}

void update(int id, int l, int r, int u, int v, ll val) {
  if (v < l || r < u) return;
  if (u <= l && r <= v) {
    segtree[id].sum = (r - l + 1) * val;
    
    segtree[id].lazyAdd = 0;
		segtree[id].lazySet = val;

    return;
  }
  
  int mid = (l + r) / 2;
  pushdown(id, l, mid, r);
  update(id * 2, l, mid, u, v, val);
  update(id * 2 + 1, mid + 1, r, u, v, val);
  pushup(id);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> arr[i];
  build(1, 1, n);
  for (int i = 1; i <= q; ++i) {
    int t; cin >> t;
    if (t == 1) {
      int a, b; ll x; cin >> a >> b >> x;
      add(1, 1, n, a, b, x);
    }
    if (t == 2) {
      int a, b; ll x; cin >> a >> b >> x;
      update(1, 1, n, a, b, x);
    }
    if (t == 3) {
      int a, b; cin >> a >> b;
      cout << get(1, 1, n, a, b) << endl;
    }
  }
}
