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

//startsnippet:graph_articulation_points
//https://github.com/stjepang/snippets/blob/master/articulation_points.cpp
struct ArticulationPoints
{
    int n,m;
    vii g;
    int tick = 1;
    vi discovery;
    vb articulation;

    int dfs(int x, int dad)
    {
        discovery[x] = ++tick;
        int low = discovery[x];

        articulation[x] = false;
        int children = 0;

        for (int y : g[x])
        {
            if (y == dad)
                continue;

            if (discovery[y] < 0)
            {
                ++children;
                int w = dfs(y, x);

                if (w >= discovery[x])
                    articulation[x] = true;
                low = min(low, w);
            }
            else
            {
                low = min(low, discovery[y]);
            }
        }
        if (dad == -1)
            articulation[x] = children > 1;

        return low;
    }
    ArticulationPoints(int iN, int iM, vii &iG) : n(iN), m(iM), g(iG)
    {
        articulation.assign(n,false);
        discovery.assign(n,-1);
        forp(i,0,n){
            if (discovery[i]==-1) dfs(i,-1);
        }
    }
        //usage.
        //  ArticulationPoints cps(n,m,gr.g);
        // cout << count(cps.articulation.begin(), cps.articulation.end(), true)<< '\n';
};
//endsnippet:graph articulation points

//startsnippet:graph_cutpoints
struct CutPoints
{
    vb visited;
    vii g;
    int n, m;
    vi tin, low;
    int timer;
    set<int> cutpoints;

    void dfs(int v, int p = -1)
    {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        int children = 0;
        for (int to : g[v])
        {
            if (to == p)
                continue;
            if (visited[to])
            {
                low[v] = min(low[v], tin[to]);
            }
            else
            {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p != -1)
                    cutpoints.insert(v);
                ++children;
            }
        }
        if (p == -1 && children > 1)
            cutpoints.insert(v);
    }

    CutPoints(int iN, int iM, vii &iG) : n(iN), m(iM), g(iG)
    {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
                dfs(i);
        }
    }
    //usage
    // CutPoints cps(n, m, gr.g);
    // cout << cps.cutpoints.size() << endl;
};

//endsnippet:cutpoints

//startsnippet:input_graph_adj_undirected
struct GraphAdjReader
{
    vii g, gt;
    int n, m;
    int one = 1; //default to one based?
    bool directed = false;

    GraphAdjReader(int iN, int iM, bool oneBased, bool directed) : n(iN), m(iM), directed(directed)
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
        if (item.directed)
        {
            item.gt[b - one].emplace_back(a - one);
        }
        else
        {
            item.g[b - one].emplace_back(a - one);
        }
    }
    return input;
}

//endsnippet:input graph reader directed undirected

int main()
{
    // freopen("spojSUBMERGE.01.inp","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    ioinit();

    while (1)
    {
        ioline();
        is >> n >> m;
        if (n == 0 && m == 0)
            return 0;
        GraphAdjReader gr(n, m, true, false);
        cin >> gr;

        // CutPoints cps(n, m, gr.g);
        // cout << cps.cutpoints.size() << endl;

        ArticulationPoints cps(n,m,gr.g);
        cout << count(cps.articulation.begin(), cps.articulation.end(), true)<< '\n';
    }
    return 0;
}