/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n, m;
const int maxn = 100010;
vector<ll> arr(maxn), min_arr(maxn * 4);

void build(int id, int l, int r) {
  if (l == r) {
    min_arr[id] = arr[l];
    cout << id << " " << l << " " << r << " " << min_arr[id] << endl;
    return;
  } 

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  min_arr[id] = min(min_arr[id * 2], min_arr[id * 2 + 1]);
  cout << id << " " << l << " " << r << " " << min_arr[id] << endl;
}

ll get(int id, int l, int r, int u, int v) {
  if (r < u || v < l) return LLONG_MAX;
  if (u <= l && r <= v) return min_arr[id];

  int mid = (l + r) / 2;
  ll s1 = get(id * 2, l, mid, u, v);
  ll s2 = get(id * 2 + 1, mid + 1, r, u, v);
  return min(s1, s2);
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) { // l = r = pos
    min_arr[id] = val;
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  min_arr[id] = min(min_arr[id * 2], min_arr[id * 2 + 1]);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  build(1, 0, n - 1);
  for (int i = 0; i < m; ++i) {
    int t; ll u, v;
    cin >> t >> u >> v;
    if (t == 1) update(1, 0, n - 1, u, v);
    if (t == 2) cout << get(1, 0, n - 1, u, v - 1) << endl;
  } 
}
