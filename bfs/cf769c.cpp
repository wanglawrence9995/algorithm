#include <bits/stdc++.h>
using namespace std;

#define what_is(x) cerr << #x << " is " << x << endl;
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define forp(i, start, end) for (__typeof(end) i = start; i < end; ++i)
using ull = unsigned long long;
using vull = vector<ull>;
using vullull = vector<vull>;
using ll = long long;
using vll = vector<ll>;
using vllll = vector<vll>;
using vi = vector<int>;
using vii = vector<vi>;
using vc = vector<char>;
using vcc = vector<vc>;
using vb = vector<bool>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;
using ps = pair<string, string>;
using vps = vector<ps>;
#define ioinit() \
    string s;    \
    istringstream is;
#define ioline()     \
    getline(cin, s); \
    is = istringstream(s);
#define outv(v) copy(begin(v), end(v), out_iter)
#define inputv(v, dtype)   \
    getline(cin, s);       \
    is = istringstream(s); \
    vector<dtype> v((istream_iterator<dtype>(is)), istream_iterator<dtype>());
#define sortv(v) sort(begin(v), end(v));

auto out_iter(ostream_iterator<int>(std::cout, " "));
//startsnippet:bfs_basic
struct bfs
{
    vii adj; // adjacency list representation
    int n;                   // number of nodes
    int s;                   // source vertex

    queue<int> q;
    vb used;
    vi d, p;
    int s;
    bfs(int iN, int iS, vii &iG) : n(iN), s(iS), adj(iG)
    {
        used = vb(n);
        d = vi(n);
        p = vi(n);
        q.push(s);
        used[s] = true;
        p[s] = -1;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int u : adj[v])
            {
                if (!used[u])
                {
                    used[u] = true;
                    q.push(u);
                    d[u] = d[v] + 1;
                    p[u] = v;
                }
            }
        }
    }
};
//endsnippet:bfs basic
int main()
{
    //freopen("cf769c.01.inp","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}