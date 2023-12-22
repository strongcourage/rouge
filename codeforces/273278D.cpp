/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

const int MAXN = 100010;
vector<ll> arr(MAXN), max_arr(MAXN * 4);

void build(int id, int l, int r) {
  if (l == r) {
    max_arr[id] = arr[l];
    return;
  } 

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  max_arr[id] = max(max_arr[id * 2], max_arr[id * 2 + 1]);
}

int get(int id, int l, int r, ll x, int min_index) {
  if (max_arr[id] < x) return -1;
  if (r < min_index) return -1;
  if (l == r) return l;

  int mid = (l + r) / 2;
  int res = get(id * 2, l, mid, x, min_index);
  if (res == -1) {
    res = get(id * 2 + 1, mid + 1, r, x, min_index);
  }
  return res;
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) { // l = r = pos
    arr[l] = val;
    max_arr[id] = val;
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  max_arr[id] = max(max_arr[id * 2], max_arr[id * 2 + 1]);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  build(1, 0, n - 1);
  for (int i = 0; i < m; ++i) {
    int t; cin >> t;
    if (t == 1) {
      int u; ll v; cin >> u >> v;
      update(1, 0, n - 1, u, v);
    }
    if (t == 2) {
      ll x; int l; cin >> x >> l;
      cout << get(1, 0, n - 1, x, l) << endl;
    }
  } 
}
