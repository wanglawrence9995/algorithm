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
//startsnippet:scc_basic
struct SCC
{
    vii g, gt; // template
    int nVertex;
    vi order; // order number for dfs1
    vb visited;
    vi comp; //comp index from

    //Get certain number
    void dfs1(int s)
    {
        visited[s] = true;
        for (auto v : g[s])
        {
            if (!visited[v])
            {
                dfs1(v);
            }
        }
        order.emplace_back(s);
    }

    void dfs2(int s, int icomp)
    {
        comp[s] = icomp;
        for (auto v : gt[s])
        {
            if (comp[v] == -1)
            {
                dfs2(v, icomp);
            }
        }
    }

    bool solve()
    {
        int i, j = 0;
        for (i = 0; i < nVertex; ++i)
        {
            dfs1(i);
        }
        for (i = 0, j = 0; i < nVertex; ++i)
        {

            if (comp[i] == -1)
            {
                int v = order[nVertex - i - 1];
                dfs2(v, j);
                j++;
            }
        }

        return false;
    }

    SCC(vii &inGraph, vii &inGraphT, int inVarNum) : g(inGraph), gt(inGraphT), nVertex(inVarNum)
    {
        comp.assign(nVertex, -1);
        visited.assign(nVertex, false);
        solve();
    };
};

ostream &operator<<(ostream &output, SCC &scc)
{
    //print component only
    output << *max_element(begin(scc.comp), end(scc.comp)) + 1 << endl;
    return output;
};
//endsnippet:scc basic

//startsnippet:input_graph_adj
struct GraphAdjReader
{
    vii g, gt;
    int n, m;
    int one = 1; //default to one based?

    GraphAdjReader(int iN, int iM, bool oneBased) : n(iN), m(iM)
    {
        g.assign(n, vi());
        gt.assign(n, vi());
        one = oneBased ? 1 : 0;
    };
};

// read format like four numbers each line. each line have a index, negative as 0
ostream &operator<<(ostream &output, GraphAdjReader &item)
{
    int i = 0;
    for (auto &it : item.g)
    {
        for (auto adj : it)
        {
            output << i + item.one << " " << adj + item.one << endl;
        }
        i++;
    }
    return output;
}
// The original form should also be shown to be verified
istream &operator>>(istream &input, GraphAdjReader &item)
{
    int a, b;
    int one = item.one;
    ioinit();
    forp(e, 0, item.m)
    {
        ioline();
        is >> a >> b;
        item.g[a - one].emplace_back(b - one);
        item.gt[b - one].emplace_back(a - one);
    }
    return input;
}

//endsnippet:graph adj input
int main()
{
    //freopen("spojCCOMPS.01.inp","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    ioinit();
    ioline();
    is >> n >> m;
    GraphAdjReader gr(n, m, true);
    cin >> gr;
    SCC scc(gr.g, gr.gt, gr.n);
    cout << scc;
    // cout << gr;
    return 0;
}