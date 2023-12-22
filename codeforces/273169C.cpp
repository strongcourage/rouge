/**
 *    author: martin_nguyen (strongcourage)
**/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n, m;
const int maxn = 100010;
vector<ll> arr(maxn);
vector<pair<ll, int>> segment_tree(maxn * 4);

void build(int id, int l, int r) {
  if (l == r) {
    segment_tree[id] = {arr[l], 1};
    // cout << id << " " << l << " " << r << " " << segment_tree[id].first << " " << segment_tree[id].second << endl;
    return;
  } 

  int mid = (l + r) / 2;
  build(id * 2, l, mid);
  build(id * 2 + 1, mid + 1, r);
  auto s1 = segment_tree[id * 2];
  auto s2 = segment_tree[id * 2 + 1];
  ll min_val = min(s1.first, s2.first);
  int count = 0;
  if (min_val == s1.first) count += s1.second; 
  if (min_val == s2.first) count += s2.second; 
  segment_tree[id] = {min_val, count};
  // cout << id << " " << l << " " << r << " " << segment_tree[id].first << " " << segment_tree[id].second << endl;
}

pair<ll, int> get(int id, int l, int r, int u, int v) {
  if (r < u || v < l) return {LLONG_MAX, 0};
  if (u <= l && r <= v) return segment_tree[id];

  int mid = (l + r) / 2;
  auto s1 = get(id * 2, l, mid, u, v);
  auto s2 = get(id * 2 + 1, mid + 1, r, u, v);
  ll min_val = min(s1.first, s2.first);
  int count = 0;
  if (min_val == s1.first) count += s1.second;
  if (min_val == s2.first) count += s2.second;
  return {min_val, count};
}

void update(int id, int l, int r, int pos, ll val) {
  if (pos < l || r < pos) return;
  if (l == r) { // l = r = pos
    segment_tree[id] = {val, 1};
    return;
  }

  int mid = (l + r) / 2;
  update(id * 2, l, mid, pos, val);
  update(id * 2 + 1, mid + 1, r, pos, val);
  auto s1 = segment_tree[id * 2];
  auto s2 = segment_tree[id * 2 + 1];
  ll min_val = min(s1.first, s2.first);
  int count = 0;
  if (min_val == s1.first) count += s1.second; 
  if (min_val == s2.first) count += s2.second; 
  segment_tree[id] = {min_val, count};
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
    if (t == 2) {
      auto s = get(1, 0, n - 1, u, v - 1);
      cout << s.first << " " << s.second << endl;
    }
  } 
}
