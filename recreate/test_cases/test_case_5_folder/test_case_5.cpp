#include <bits/stdc++.h>
#define ll long long
const int md = 1000000007;
#define pb push_back
#define g(v, i, j) get<i>(v[j])
#define co(v, x) count(v.begin(), v.end(), x)
#define mxe(v) *max_element(v.begin(), v.end())
#define mne(v) *min_element(v.begin(), v.end())
#define vi vector<int>
#define vll vector<ll>
#define srt(v) sort(v.begin(), v.end())
#define rsrt(v) sort(v.begin(), v.end(), greater<int>())
/* INPUT/OUTPUT*/
#define pr printf
#define sc scanf
#define pi(a) printf("%d\\n", a)
#define pll(a) printf("%lld\\n", a)
#define si(a) scanf("%d", &a)
#define sll(a) scanf("%lld", &a)
/* LOOPS*/
#define fi(i, a, b) for (int i = a; i < b; i++)
#define fll(i, a, b) for (ll i = a; i < b; i++)
using namespace std;
using namespace std::chrono;
ll pw(ll a, ll b) {
  ll c = 1, m = a;
  while (b) {
    if (b & 1)
      c = (c * m);
    m = (m * m);
    b /= 2;
  }
  return c;
}
ll pwmd(ll a, ll b) {
  ll c = 1, m = a;
  while (b) {
    if (b & 1)
      c = (c * m) % md;
    m = (m * m) % md;
    b /= 2;
  }
  return c;
}
ll modinv(ll n) { return pwmd(n, md - 2); }
ll inverse(ll i) {
  if (i == 1)
    return 1;
  return (md - ((md / i) * inverse(md % i)) % md + md) % md;
}
ll ceel(ll a, ll b) {
  if (a % b == 0)
    return a / b;
  else
    return a / b + 1;
}
ll my_log(ll n, ll b) {
  ll i = 1;
  ll ans = 0;
  while (1) {
    if (i > n) {
      ans--;
      break;
    }
    if (i == n)
      break;
    i *= b;
    ans++;
  }
  return ans;
}
bool sortbysec(const pair<ll, ll> &a, const pair<ll, ll> &b) {
  return (a.second < b.second);
}
/* auto start = high_resolution_clock::now();
 auto stop = high_resolution_clock::now();
 auto duration = duration_cast<microseconds>(stop - start);
 cerr << "Time taken: "
      << duration.count()<< "ms" <<"\\n";*/
ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
vector<char> capl = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                     'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                     'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
vector<char> sml = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
string conv(ll a) {
  string b;
  ll e = 2;
  ll c = my_log(a, e);
  c++;
  b = '1';
  for (int i = 0; i < c - 1; i++) {
    ll k = a >> (c - 2 - i);
    if (k & 1)
      b += '1';
    else
      b += '0';
  }
  if (a == 0)
    return "0";
  return b;
}
ll mysqt(ll a) {
  ll ans = 1;
  while (ans * ans <= a)
    ans++;
  ans--;
  return ans;
}
bool isprime(int p) {
  int i = 2;
  while (i <= sqrt(p)) {
    if (p % i == 0) {
      return false;
    }
    i++;
  }
  return true;
}
int main() {

  int n = 1000;
  int cnt = 0, i = 1;
  while (i < n) {
    int j = 1;
    int p = n - i;
    while (j <= sqrt(p)) {
      if (p % j == 0) {
        cnt += 2;
        if (j == sqrt(p))
          cnt--;
      }
      j++;
    }
    i++;
  }
  cout << cnt;
}
