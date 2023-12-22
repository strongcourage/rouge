/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n, m;
const int maxn = 100010;
vector<ll> arr(maxn), sum(maxn * 4), max_pref(maxn * 4), max_suff(maxn * 4), max_sum(maxn * 4);

void build(int id, int l, int r) {
  if (l == r) {
    sum[id] = arr[l];
    max_pref[id] = max(0LL, arr[l]);
    max_suff[id] = max(0LL, arr[l]);
    max_sum[id] = max(0LL, arr[l]);
    return;
  } 

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  sum[id] = sum[id * 2] + sum[id * 2 + 1];
  max_pref[id] = max({0LL, max_pref[id * 2], max_pref[id * 2 + 1] + sum[id * 2]});
  max_suff[id] = max({0LL, max_suff[id * 2] + sum[id * 2 + 1], max_suff[id * 2 + 1]});
  max_sum[id] = max({0LL, max_sum[id * 2], max_suff[id * 2] + max_pref[id * 2 + 1], max_sum[id * 2 + 1]});
}

ll get(int id, int l, int r, int u, int v) {
  if (r < u || v < l) return 0LL;
  if (u <= l && r <= v) return max(0LL, max_sum[id]);

  int mid = (l + r) / 2;
  ll s1 = get(id * 2, l, mid, u, v);
  ll s2 = get(id * 2 + 1, mid + 1, r, u, v);

  return max({0LL, s1, s2, max_suff[id * 2] + max_pref[id * 2 + 1]});
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) { // l = r = pos
    sum[id] = val;
    max_pref[id] = max(0LL, val);
    max_suff[id] = max(0LL, val);
    max_sum[id] = max(0LL, val);
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  sum[id] = sum[id * 2] + sum[id * 2 + 1];
  max_pref[id] = max({0LL, max_pref[id * 2], max_pref[id * 2 + 1] + sum[id * 2]});
  max_suff[id] = max({0LL, max_suff[id * 2] + sum[id * 2 + 1], max_suff[id * 2 + 1]});
  max_sum[id] = max({0LL, max_sum[id * 2], max_suff[id * 2] + max_pref[id * 2 + 1], max_sum[id * 2 + 1]});
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> arr[i];
  build(1, 0, n - 1);
  vector<pair<ll, ll>> uv(m);
  for (int i = 0; i < m; ++i) {
    cin >> uv[i].first >> uv[i].second;
  }
  cout << get(1, 0, n - 1, 0, n - 1) << endl;
  for (int i = 0; i < m; ++i) {
    ll u = uv[i].first;
    ll v = uv[i].second;
    update(1, 0, n - 1, u, v);
    cout << get(1, 0, n - 1, 0, n - 1) << endl;
  }
}
