#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<LL>seller;
vector<vector<LL>>buyer_price;
vector<vector<LL>>buyer;
LL n, m, Max, mn, N;
LL nc, mc;
vector<LL>match;
vector<LL>final_price;
vector<LL>best_match;
vector<LL>use;
#define MAXN 1010
#define INF INT_MAX
int g[MAXN][MAXN],lx[MAXN],ly[MAXN],slack_y[MAXN];
int match_y[MAXN];
bool vx[MAXN],vy[MAXN];
bool dfs(int x){
	if(vx[x])return 0;
	vx[x]=1;
	for(int y=0,t;y<N;++y){
		if(vy[y])continue;
		t=lx[x]+ly[y]-g[x][y];
		if(t==0){
			vy[y]=1;
			if(match_y[y]==-1||dfs(match_y[y])){
				match_y[y]=x;
				return 1;
			}
		}else if(slack_y[y]>t)slack_y[y]=t;
	}
	return 0;
}
void out(){
	int i;
	cout << "lx: ";
	for(i=0;i<N;i++)cout << lx[i] << ' ';
	cout << "\nly: ";
	for(i=0;i<N;i++)cout << ly[i] << ' ';	
	cout << "\nslack_y: ";
	for(i=0;i<N;i++)cout << slack_y[i] << ' ';
	cout << "\nmatch_y: ";	
	for(i=0;i<N;i++)cout << match_y[i] << ' ';
	cout << "\n";	
}
inline int km(){
	memset(ly,0,sizeof(int)*N);
	memset(match_y,-1,sizeof(int)*N);
	for(int x=0;x<N;++x){
		lx[x]=-INF;
		for(int y=0;y<N;++y){
			lx[x]=max(lx[x],g[x][y]);
		}
	}
	for(int x=0;x<N;++x){
		for(int y=0;y<N;++y)slack_y[y]=INF;
		for(;;){
			memset(vx,0,sizeof(bool)*N);
			memset(vy,0,sizeof(bool)*N);
//			cout << x << ": \n";
//			out();
			if(dfs(x))break;
//			out();
			int cut=INF;
			for(int y=0;y<N;++y){
				if(!vy[y]&&cut>slack_y[y])cut=slack_y[y];
			}
			for(int j=0;j<N;++j){
				if(vx[j])lx[j]-=cut;
				if(vy[j])ly[j]+=cut;
				else slack_y[j]-=cut;
			}
		}
	}
	int ans=0;
	for(int y=0;y<n;++y)if(g[match_y[y]][y]!=-INF)ans+=g[match_y[y]][y];
	return ans;
}
inline void init(){
	Max = -1;
	match.clear();
	use.clear();
	match.resize(m);
	for(LL i=0;i<m;i++)match[i] = -1;
	use.resize(n);
	for(LL i=0;i<n;i++)use[i] = -1;
	best_match.clear();
}

void input(){
	cin >> n;
	cin >> nc;
	seller.clear();
	for(int i=0;i<MAXN;i++)
		for(int j=0;j<MAXN;j++){
			g[i][j] = 0;
		}
	LL i, x, j, k;
	for(i=0;i<n;i++){
		cin >> x;
		seller.pb(x); 
	}
	for(i=0;i<nc-1;i++)
		for(j=0;j<n;j++)
			seller.pb(seller[j]);
	for(i=0;i<buyer.size();i++){
		buyer[i].clear();
	}
	buyer.clear();
	cin >> m;
	cin >> mc;
	for(i=0;i<m;i++){
		vector<LL>tmp;
		tmp.clear();
		buyer.pb(tmp);
		for(j=0;j<n;j++){
			cin >> x;
			g[i][j] = x-seller[j];
			buyer[i].pb(x);	
		}
	}
	for(i=0;i<mc-1;i++)
		for(j=0;j<m;j++)
			buyer.pb(buyer[j]);
	for(i=0;i<m*mc;i++)
		for(j=0;j<n*nc;j++)
			g[i][j] = buyer[i][j%n]-seller[j];
	n *= nc;
	m *= mc;
}
void solve(){
	LL t, i;
	clock_t start, end;
	start = clock();
	cin >> t;
	for(i=0;i<t;i++){
		input();
		init();
		LL j;
		mn = 0;
		N = max(m,n)+3;
		km();
		Max = 0;
		for(j=0;j<N;j++){
			if(match_y[j]!=-1&&match_y[j]<match.size())
				match[match_y[j]] = j;
		}
		n /= nc;
		m /= mc;
		for(j=0;j<match.size();j++){
			if(match[j]!=-1 && match[j] < n*nc && buyer[j][match[j]%n]-seller[match[j]]>0)
				Max += buyer[j][match[j]%n]-seller[match[j]];
			else
				match[j] = -1;
		}
		if(n < m)
			mn = 1;
		cout << Max << '\n';
		for(j=0;j<match.size();j++)cout << match[j]+1 << " ";
		cout << "\n" << m << ' ' << n << "\n";
		end = clock();
		cout << "Time: " << ((double)(end-start))/CLOCKS_PER_SEC << "s\n";
		start = clock();
	}
}

int main(){
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	for(int i=0;i<5;i++){
		string input = "testcase_0.txt";
		input[9] = '0'+i;
		string output = "KM_" + input;
		input = "./testcase/" + input;
//		input = "inputtmp.txt";
		output = "./testcase/" + output;
		freopen(input.c_str(),"r",stdin);
		freopen(output.c_str(),"w",stdout);
		solve();
	}
}

