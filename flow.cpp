#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct Dinic{
	static const int MAXV = 10000;
	static const T INF = 1e9;
	struct Edge{
		int v;
		T f;
		int re;		
	};
	vector<Edge>E[MAXV];
	int n, s, t;
	int now[MAXV], level[MAXV];
	void init(int _n, int _s, int _t){
		n = _n,s = _s,t = _t;
		for(int i=0;i<=n;i++)E[i].clear();
	}
	void add_edge(int u, int v, int f){
		E[u].push_back({v,f,E[v].size()});
		E[v].push_back({u,0,E[u].size()-1});
		//if  (µL¦V¹Ï )
		//E[v].push_back({u,f,E[u].size()-1}); 
	}
	bool BFS(){
		fill(level,level+n,-1);
		queue<int>q;
		q.push(s);level[s] = 0;
		while(!q.empty()){
			int u = q.front();q.pop();
			Edge it;
			int i;
			for(i=0;i<E[u].size();i++){
				it = E[u][i];
				if(it.f > 0&&level[it.v]==-1){
					level[it.v] = level[u]+1;
					q.push(it.v);
				}
			}
		}
		return level[t]!=-1;
	}
	T DFS(int u,T nf){
		if(u==t)return nf;
		int res = 0;
		while(now[u]<E[u].size()){
			Edge &it=E[u][now[u]];
			if(it.f > 0&&level[it.v]==level[u]+1){
				int tf = DFS(it.v,min(nf,it.f));
				res += tf,it.f -= tf, nf -= tf;
				E[it.v][it.re].f += tf;
				if(nf==0)return res;
			}
			else
				now[u]++;
		}
		if(!res)level[u] = -1;
		return res;
	}
	T flow(T res = 0){
		while(BFS()){
			T temp;
			fill(now,now+n,0);
			while((temp=DFS(s,INF))){
				res+=temp;	
			}
		}
		return res;
	}
};

int main(){
	Dinic<int> ans;
	ans.init(8,0,7);
	int i;
//	for(i=0;i<3;i++)
//		ans.add_edge(0,i+1,ans.INF);
	for(i=0;i<3;i++)
		ans.add_edge(i+4,7,ans.INF);
	ans.add_edge(4,7,11);
	ans.add_edge(5,7,9);
	ans.add_edge(6,7,7);
	ans.add_edge(0,1,5);
	ans.add_edge(0,2,11);
	ans.add_edge(0,3,2);
	ans.add_edge(1,4,5);
	ans.add_edge(1,5,4);
	ans.add_edge(1,6,3);
	ans.add_edge(2,4,11);
	ans.add_edge(2,5,9);
	ans.add_edge(2,6,7);
	ans.add_edge(3,4,1);
	ans.add_edge(3,5,2);
	ans.add_edge(3,4,-2);
	cout << ans.flow();
}

