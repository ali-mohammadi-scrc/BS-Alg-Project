//IN THE NAME OF GOD :)

// BY ALI MOHAMMADI GHANATGHESTANI SCRC

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <stack>
#include <cctype>
#include <map>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <functional>
#include <time.h>
#include <cstring>

using namespace std;
typedef vector<int> vin;
typedef vector<pair <int , int> > vpin;
typedef pair<int , int> pin;
typedef set<int> stin;
typedef set<pair <int , int> > stpin;
typedef queue<int> qin;
typedef stack<int> scin;
typedef long long unsigned llu;
typedef long long ll;
typedef map<int , int> mpin;
typedef priority_queue<int> pqin;
const int MAXn = 1000 * 1000 + 96;
#define endl '\n'

ofstream fout ("my_output-1.txt");
ofstream sout ("my_output-2.txt");
ofstream tout ("my_output-3.txt");
#define fout cout
#define sout cout
#define tout cout
int n, m, *time_limit, cities_num, *city, Time, *visit_time, delays, q, *qs, *queries[3], *Distance, heap_size, *Heap, *heap_place, ntargets;
double delay;
vpin *gr;
mpin *weight;
string *name;
map <string, int> name_map;
bool *mark, *dij_mark, *targets;
scin dfs_stack;
vector <pair <pair <int, int>, int> > *sorted_edges;
clock_t timeB, timeF;

void DFS (int p, int v){
	visit_time[v] = ++Time;
	mark[v] = true;
	dfs_stack.push (v);
	for (int i = 0; i < gr[v].size (); i++){
		int u = gr[v][i].first;
		if (!visit_time[u])
			DFS (v, u);
		if (mark[u])
			visit_time[v] = min (visit_time[v], visit_time[u]);
	}
	if (p < 0 || visit_time[p] < visit_time[v]){
		if (cities_num != 0)
			fout <<"---"<<endl;
		int u;
		while (dfs_stack.top () != v){
			u = dfs_stack.top ();
			dfs_stack.pop ();
			city[u] = cities_num;
			mark[u] = false;
			fout <<name[u]<<endl;
		}
		dfs_stack.pop ();
		city[v] = cities_num++;
		mark[v] = false;
		fout <<name[v]<<endl;
	}
}

void scc (){
	city = new int[n];
	visit_time = new int[n];
	mark = new bool[n];
	memset (mark, false, n * sizeof (bool));
	for (int i = 0; i < n; i++)
		if (!visit_time[i])
			DFS (-1, i);
}

void delete_heap (){
	if (heap_size == 1){
		heap_place[Heap[1]] = 0;
		heap_size--;
		return ;
	}
	heap_place[Heap[1]] = 0;
	Heap[1] = Heap[heap_size--];
	heap_place[Heap[1]] = 1;
	int place = 1;
	while (true){
		if (place * 2 > heap_size) break;
		if (place * 2 + 1 > heap_size){
			if (Distance[Heap[place]] > Distance[Heap[place * 2]]){
				swap (Heap[place], Heap[place * 2]);
				swap (heap_place[Heap[place]], heap_place[Heap[place * 2]]);
			}
			break;
		}
		if (Distance[Heap[2 * place]] < Distance[Heap[place]] && Distance[Heap[place * 2]] <= Distance[Heap[place * 2 + 1]]){
			swap (Heap[place], Heap[place * 2]);
			swap (heap_place[Heap[place]], heap_place[Heap[place * 2]]);
			place *= 2;
		}
		else if (Distance[Heap[2 * place + 1]] < Distance[Heap[place]]){
			swap (Heap[place], Heap[place * 2 + 1]);
			swap (heap_place[Heap[place]], heap_place[Heap[place * 2 + 1]]);
			place = 2 * place + 1;
		}
		else break;
	}
}

void add_heap (int element){
	if (!heap_place[element]){
		Heap[++heap_size] = element;
		heap_place[element] = heap_size;
	}
	int place = heap_place[element];
	while (place != 1 && Distance[element] < Distance[Heap[place/2]]){
		swap (heap_place[Heap[place/2]], heap_place[element]);
		swap (Heap[place], Heap[place/2]);
		place /= 2;
	}
}

int pop_min (){
	int heap_min = Heap[1];
	delete_heap ();
	return heap_min;
}

void heap_empty (){
	for (int i = 1; i <= heap_size; i++)
		heap_place[Heap[i]] = 0;
	heap_size = 0;
}

void dijkstra (int v, int min_component){
	heap_empty ();
	memset (Distance, -1, sizeof (int) * n);
	memset (dij_mark, false, sizeof (bool) * n);
	Distance[v] = 0;
	add_heap (v);
	while (heap_size){
		int min_v = pop_min ();
		dij_mark[min_v] = true;
		if (targets[min_v]){
			targets[min_v] = false;
			ntargets--;
			if (!ntargets) return;
		}
		for (int i = 0; i < gr[min_v].size (); i++){
			int u = gr[min_v][i].first, w = gr[min_v][i].second;
			if (!dij_mark[u] && city[u] >= min_component && (Distance[u] == -1 || Distance[min_v] + w < Distance[u])){
				Distance[u] = Distance[min_v] + w;
				add_heap (u);
			}
		}
	}
}

bool q_compare (int a, int b){
	return (queries[0][a] < queries[0][b]);
}

void find_shortest_path (){	
	sort (qs, qs + q, q_compare);
	int fp = 0, sp = 0;
	while (sp >= fp && sp < q && fp < q){
		if (sp >= q || queries[0][qs[sp]] != queries[0][qs[fp]]) fp = sp;
		int min_city = cities_num;
		while (sp < q && queries[0][qs[sp]] == queries[0][qs[fp]]){
			if (city[queries[0][qs[sp]]] < city[queries[1][qs[sp]]]) queries[2][qs[sp++]] = -1;
			else {
				if (!targets[queries[1][qs[sp]]]) {
					ntargets++;
					targets[queries[1][qs[sp]]] = true;
				}
				min_city = min (min_city, city[queries[1][qs[sp++]]]);
			}
		}
		sp = fp;
		if (fp < q)
			dijkstra (queries[0][qs[fp]], min_city);
		while (sp < q && queries[0][qs[sp]] == queries[0][qs[fp]]) queries[2][qs[sp]] = Distance[queries[1][qs[sp++]]];
	}	
}

int *parent, *rank, *d_set_size;

void make_set (int v){
	parent[v] = -1;
	rank[v] = 0;
	d_set_size[v] = 1;
}

int find_root (int v){
	int v_root = v;
	while (parent[v_root] != -1)
		v_root = parent[v_root];
	return v_root;
}

int join (int v, int u){
	int v_root = find_root (v);
	int u_root = find_root (u);
	int dly;
	if (v_root == u_root)
		return -1;
	dly = d_set_size[v_root] * d_set_size[u_root];
	if (rank[v_root] < rank[u_root]){
		parent[v_root] = u_root;
		d_set_size[u_root] += d_set_size[v_root];
	}
	else {
		parent[u_root] = v_root;
		d_set_size[v_root] += d_set_size[u_root];
	}
	if (rank[u_root] == rank[v_root]) rank[v_root]++;
	return dly;
}

void kruskal (){
	parent = new int[cities_num];
	rank = new int[cities_num];
	d_set_size = new int[cities_num];
	for (int i = 0; i < cities_num; i++)
		make_set (i);
	for (int i = 0; i < delays; i++)
		for (int j = 0; j < sorted_edges[i].size (); j++){
			int w = sorted_edges[i][j].second, v = sorted_edges[i][j].first.first, u = sorted_edges[i][j].first.second, d = join (v, u);
			if (d > -1)
				delay += d * w;
		}
	delay *= 2;
	delay /= cities_num - 1;
	delay /= cities_num;
	int DelaY = (int) delay, length = 0;
	while (DelaY){
		length++;
		DelaY /= 10;
	}
	tout <<setprecision (length + 6)<<delay<<endl;
}

int main ()
{
	ios::sync_with_stdio(0);
	cin.tie();
//	timeB = clock ();
	cin >>n>>m;
	// making graph
	weight = new mpin[n];
	gr = new vpin[n];
	name = new string[n];
	for (int i = 0; i < n;i++){
		cin >>name[i];
		name_map[name[i]] = i;
	}
	for (int i = 0; i < m; i++){
		int v, u, w;
		string ver_v, ver_u;
		cin >>ver_v>>ver_u>>w;
		v = name_map[ver_v];
		u = name_map[ver_u];
		if (v == u)
			continue;
		if (weight[v].find (u) == weight[v].end ()){
			gr[v].push_back (make_pair (u, w));
			weight[v][u] = w;
		}
		else if (w < weight[v][u])
			weight[v][u] = w;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < gr[i].size (); j++)
			gr[i][j].second = weight[i][gr[i][j].first];
	// part I
//	timeF = clock ();
//	cerr <<"pre proccess time = "<<timeF - timeB<<endl;
//	timeB = clock ();
	scc ();
//	timeF = clock ();
//	cerr <<"part I time = "<<timeF - timeB<<endl;
//	timeB = clock ();
	// part II
	cin >>q;
	Heap = new int[n];
	heap_place = new int [n];	
	queries[0] = new int[q];
	queries[1] = new int[q];
	queries[2] = new int[q];
	Distance = new int[n];
	dij_mark = new bool[n];
	targets = new bool[n];
	qs = new int[q];
	for (int i = 0; i < q; i++){
		string first, second;
		cin >>first>>second;
		queries[0][i] = name_map[first];
		queries[1][i] = name_map[second];
		qs[i] = i;
	}
	find_shortest_path ();
	for (int i = 0; i < q; i++)
		if (queries[2][i] >= 0)
			sout <<queries[2][i]<<endl;
		else
			sout <<"Impossible"<<endl;
//	timeF = clock ();
//	cerr <<"part II time = "<<timeF - timeB<<endl;
//	timeB = clock ();
	// part III
	time_limit = new int[cities_num];
	weight = new mpin[cities_num];
	vpin *old_gr = new vpin[cities_num];
	swap (old_gr, gr);
	stin delay_set;
	for (int i = 0; i < cities_num; i++){
		int v, w;
		string ver_v, ver_u;
		cin >>ver_v>>w;
		v = name_map[ver_v];
		int cityN = city[v];
		time_limit[cityN] = w;
		delay_set.insert (w);
	}
	delays = delay_set.size ();
	mpin Delays;
	sorted_edges = new vector <pair <pair <int, int>, int> >[delays];
	int i_temp = 0;
	while (delay_set.size () != 0){
		int w = *delay_set.rbegin ();
		Delays[w] = i_temp++;
		delay_set.erase (w);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < old_gr[i].size (); j++){
			int v = city[i], u = city[old_gr[i][j].first];
			if (u == v)
				continue ;
			if (u < v)
				swap (v, u);
			if (weight[v].find (u) == weight[v].end ()){
				int w = min (time_limit[v], time_limit[u]);
				weight[v][u] = w;
				gr[v].push_back (make_pair (u, w));
				gr[u].push_back (make_pair (v, w));
				sorted_edges[Delays[w]].push_back (make_pair (make_pair (v, u), w));
			}
		}
	kruskal ();
//	timeF = clock ();
//	cerr <<"part III time = "<<timeF - timeB<<endl;
	return 0;
}
