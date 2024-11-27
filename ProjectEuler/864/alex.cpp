#include <iostream>
#include <vector>
#include <cassert>
#include <map>
using namespace std;
using ll = long long;
const ll target = 123567101113;
//const ll target = 10000000;
const ll sqtarget = 5000000001;
//const ll target = 1000;
//const ll sqtarget = 1001;
using big = __int128;

vector<bool> prime;
vector<int> pfac;

struct gauss {
  ll real = 0, imag = 0;
  gauss(ll real, ll imag): real(real), imag(imag) {}
  gauss(ll real): real(real), imag(0) {}

  gauss(){}

  gauss operator*(gauss rhs) {
    return {real*rhs.real - imag*rhs.imag, real * rhs.imag + imag * rhs.real};
  }

  gauss conj() {
    return {real, -imag};
  }

  gauss operator/(gauss rhs) {
    gauss out = rhs.conj() * *this;
    ll mag = rhs.norm();
    return {(out.real)/mag, (out.imag)/mag};
  }

  gauss operator+(gauss rhs) {
    return {real+rhs.real, imag+rhs.imag};
  }

  gauss operator-() {
    return {-real, -imag};
  }

  gauss operator-(gauss rhs) {
    return *this + (-rhs);
  }

  bool operator==(gauss rhs) {
    return real == rhs.real && imag == rhs.imag;
  }

  ll norm() {
    return real*real + imag*imag;
  }
};

template<typename T>
T euclidean(T m, T n, T &a, T &b) {
  a = 0;
  b = 0;
  if (n == 0) {
    a = 1;
    b = 0;
    return m;
  }

  T quot = m/n;
  T rem = m - quot*n;

  T g = euclidean(n, rem, a, b);
  // g = an + b(m-n floor(m/n))
  // g = an + bm - b n floor (m/n)
  // g = (a - b floor (m/n)) n + bm
  T x = a - b * quot;
  a = b;
  b = x;

  return g;
}

template<typename T>
T euclidean(T m, T n) {
  T a, b;
  return euclidean(m, n, a, b);
}

ll modPow(ll n, ll p, ll mod) {
  ll out = 1, base = n;
  while (p) {
    if (p&1) out = (out*base)%mod;
    base = (base*base)%mod;
    p /= 2;
  }
  return out;
}

ll generator(ll p) {
  assert(prime[p]);
  ll guess = 1;
  while (true) {
    guess++;
    bool good = true;
    int cur = p-1;
    do {
      int a = pfac[cur];
      if (modPow(guess, (p-1)/a, p) == 1) good = false;
      while (cur%a == 0) cur /= a;
    } while (cur > 1);
    if (good) return guess;
  }
  assert(false);
}

gauss sosPrime(ll p) {
  if (p == 2) return {1,1};
  assert(p%4 == 1 && prime[p]);
  ll g = generator(p);

  ll gk = modPow(g, (p-1)/4, p);
  auto out = euclidean(gauss(gk, -1), gauss(p));
  return {abs(out.real), abs(out.imag)};
}

int main() {
  // assert(sqtarget*sqtarget > target);
  prime.resize(sqtarget);
  pfac.resize(sqtarget);
  cout << "allocated" << endl;
  for (ll i = 2; i < sqtarget; i++) prime[i] = true;
  for (ll i = 2; i < sqtarget; i++) {
    if (!prime[i]) continue;
    pfac[i] = i;
    for (ll j = 2*i; j < sqtarget; j+=i) {
      prime[j] = false;
      pfac[j] = i;
    }
  }

  ll total = (target+18)/25 + (target+7)/25;
  vector<ll> goodPrime = {5};
  for (ll x = 3; x < sqtarget; x++) {
    if (!prime[x] || x%4 == 3) continue;
    auto [u, v] = sosPrime(x);

    ll m = u*u - v*v, n = 2*u*v;
    ll minv, ninv;
    ll gcd = euclidean(m, n, minv, ninv);
    ninv = ((ninv)%m + m)%m;
    ll a = ninv;
    ll b = (1 - n*ninv)/m;
    auto val = gauss(a,b) * gauss(u,v) * gauss(u,v);
    if (val.real <= target) {
      //cout << x << " " << val.real << endl;
      goodPrime.push_back(x);
      cout << x << endl;
    }
    if (x == 5) {
      continue;
    }

    for (ll step : {-1, 1}) {
      for (ll k = step == -1 ? 0 : 1; ; k += step) {
        ll a = k*m + ninv;
        ll b = (1 - n*ninv)/m - n*k;
        // if (a*a + b*b) is divisible by the square of a smaller prime, this is bad
        auto val = gauss(a,b) * gauss(u,v) * gauss(u,v);
        // val is (a+i)(a-i)
        // where a^2 + 1 is a number divisible by x^2
        val.real = abs(val.real);
        if ((step == 1 && a > 0 && val.real > target) || (step == -1 && a < 0 && val.real > target)) break;
        if (val.real > target) continue;

        total++;
        if (x == 5) continue;
        big sq = (big)a*a + (big)b*b;
        for (ll p : goodPrime) {
          if (p >= x) break;
          if ((big)p*p > sq) break;
          if (sq % (p*p) == 0) {
            total--;
            break;
          }
        }
        if (k%10000000 == 0) {
          cout << k << " " << total << endl;
        }
      }
    }
  }
  cout << target-total << endl;
}
