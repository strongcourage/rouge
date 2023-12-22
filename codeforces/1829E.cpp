#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int traverse(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int r, int c) {
  int n = matrix.size();
  int m = matrix[0].size();
  visited[r][c] = true;
  int area = matrix[r][c];

  for (const auto& [dr, dc] : directions) {
    int nr = r + dr;
    int nc = c + dc;
    if (nr >= 0 && nr < n && nc >= 0 && nc < m && matrix[nr][nc] != 0 && !visited[nr][nc]) {
      area += traverse(matrix, visited, nr, nc);
    }
  }

  return area;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;

  while (t--) {
    int n, m; cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> matrix[i][j];      
      }
    }

    int max_area = 0;
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < m; ++c) {
        if (matrix[r][c] > 0 && !visited[r][c]) {
          max_area = max(max_area, traverse(matrix, visited, r, c));
        }
      }
    }
    cout << max_area << endl;
  }
}
