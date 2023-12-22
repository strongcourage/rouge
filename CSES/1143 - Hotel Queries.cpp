/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 200010;
vector<ll> hotels(MAXN), rooms(MAXN), segtree(MAXN * 4);

void build(int id, int l, int r) {
  if (l == r) {
    segtree[id] = hotels[l];
    return;
  }

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  segtree[id] = max(segtree[id * 2], segtree[id * 2 + 1]);
}

ll get(int id, int l, int r, ll x) {
  if (segtree[id] < x) return 0;
  if (l == r) return l;

  int mid = (l + r) / 2;
  int res = get(id * 2, l, mid, x);
  if (res == 0) {
    res = get(id * 2 + 1, mid + 1, r, x);
  }
  return res;
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) {
    hotels[pos] = val;
    segtree[id] = val;
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  segtree[id] = max(segtree[id * 2], segtree[id * 2 + 1]);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> hotels[i];
  build(1, 1, n);
  for (int i = 1; i <= m; ++i) cin >> rooms[i];
  for (int i = 1; i <= m; ++i) {
    int res = get(1, 1, n, rooms[i]);
    cout << res << endl;
    if (res > 0) update(1, 1, n, res, hotels[res] - rooms[i]);
  }
}
