#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define ll long long int
#define ull unsigned long long int
#define ld long double

int n;
vector<vector<int>> arr(n + 1);
vector<bool> vis(n + 1);
int cnt;

void dfs(int v) {
  vis[v] = true;
  for (int i = 1; i < n + 1; i++) {
    if (vis[i] == false && arr[v][i] == 1) {
      dfs(i);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int m, a, b;
  cin >> n >> m;
  for (int i = 1; i < n + 1; i++) {
    vector<int> ar(n + 1, 0);
    arr.pb(ar);
    vis[i] = false;
  }
  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    arr[a][b] = 1;
    arr[b][a] = 1;
  }
  cnt = 0;
  for (int i = 1; i < n + 1; i++) {
    if (!vis[i]) {
      cnt += 1;
      dfs(i);
    }
  }
  cout << cnt - 1;
  return 0;
}