/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n, m;
const int maxn = 100010;
vector<ll> arr(maxn), sum(maxn * 4);

void build(int id, int l, int r) {
  if (l == r) {
    sum[id] = arr[l];
    cout << id << " " << l << " " << r << " " << sum[id] << endl;
    return;
  } 

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  sum[id] = sum[id * 2] + sum[id * 2 + 1];
  cout << id << " " << l << " " << r << " " << sum[id] << endl;
}

ll get(int id, int l, int r, int u, int v) {
  if (r < u || v < l) return 0;
  if (u <= l && r <= v) return sum[id];

  int mid = (l + r) / 2;
  ll s1 = get(id * 2, l, mid, u, v);
  ll s2 = get(id * 2 + 1, mid + 1, r, u, v);
  return s1 + s2;
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) { // l = r = pos
    sum[id] = val;
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  sum[id] = sum[id * 2] + sum[id * 2 + 1];
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
