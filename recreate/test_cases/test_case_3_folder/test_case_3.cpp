#include <bits/stdc++.h>

using namespace std;

#define tr(c, i)                                                               \\
  for (__typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define ipr pair<int, int>
#define pb push_back
#define ff first
#define ss second
#define fill(a, b) memset(a, b, sizeof(a))
#define fr(i, j, k) for (int i = j; i < k; i++)
#define rf(i, j, k) for (int i = j; i >= k; i--)
#define int long long int
#define ll unsigned long long
#define ld long double
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mp make_pair
#define L(x) ('a' <= x && x <= 'z')
#define inf INT_MAX
#define read_file()                                                            \\
  ;                                                                            \\
  freopen("input.txt", "r", stdin);                                            \\
  freopen("output.txt", "w", stdout);
#define IOS                                                                    \\
  std::ios::sync_with_stdio(false);                                            \\
  cin.tie(NULL);                                                               \\
  cout.tie(NULL);

const int Maxn = 200 * 1000 + 1;
const ld pi = acos(-1);
const int mod = 1000000007;
const double epsilon = 1e-9;

template <class T> ostream &operator<<(ostream &out, vector<T> &A) {
  for (auto x : A)
    out << x << " ";
  return out;
}
template <class T> ostream &operator<<(ostream &out, set<T> &A) {
  for (auto x : A)
    out << x << " ";
  return out;
}
template <class T> ostream &operator<<(ostream &out, unordered_set<T> &A) {
  for (auto x : A)
    out << x << " ";
  return out;
}
template <class T1, class T2> T1 powr(T1 a, T2 b) {
  T1 res = 1;
  fr(i, 1, b + 1) res = res * a;
  return res;
}

int binpow(int a, int b) {
  a = a % mod;

  int res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return (res + mod) % mod;
}

int32_t main() {
  IOS;

  int t;
  // cin>>t;
  t = 1;
  while (t--) {

    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 1; i < n; i++) {
      int x = n - i;

      for (int j = 1; j * j <= x; j++) {
        if (x % j == 0) {
          if (x / j != j)
            cnt += 2;
          else
            cnt++;
        }
      }
    }
    cout << cnt << endl;
  }
}