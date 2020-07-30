#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<LL>seller;
vector<vector<LL>>buyer_price;
vector<vector<LL>>buyer;
LL n, m, Max, mn, N;
vector<LL>match;
vector<LL>final_price;
vector<LL>best_match;
vector<LL>use;
#define MAXN 100
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
//				if(g[x][y]<0)return 0;
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
	if(mn==1){
		for(int i=0;i<m;i++)
			for(int j=i+1;j<n;j++)
				swap(g[i][j],g[j][i]);	
	}
	for(int x=0;x<N;++x){
		lx[x]=-INF;
		for(int y=0;y<N;++y){
			lx[x]=max(lx[x],g[x][y]);
		}
	}
	for(int x=0;x<N;++x){
//		if(lx[x]<0)continue;
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
//	cout << "1";
	Max = -1;
	match.clear();
	use.clear();
//	cout << "1";
//	for(int i=0;i<buyer_price.size();i++){
//		buyer_price[i].clear();
//	}
//	buyer_price.clear();
//	final_price.clear();
//	cout << "1";
//	buyer_price.resize(m);
//	for(LL i=0;i<m;i++)buyer_price[i].resize(n);
//	final_price.resize(n);
	match.resize(m);
	for(LL i=0;i<m;i++)match[i] = -1;
	use.resize(n);
	for(LL i=0;i<n;i++)use[i] = -1;
	best_match.clear();
//	n = 3;
//	int tmp[3][3] = {{23,26,20},{22,24,21},{21,22,17}};
//	for(int i=0;i<100;i++)
//		for(int j=0;j<100;j++){
//			g[i][j] = 0;
////			cout << tmp[i][j]  << '\n';
//		}
}

void input(){
	cin >> n;
	seller.clear();
	for(int i=0;i<100;i++)
		for(int j=0;j<100;j++){
			g[i][j] = 0;
//			cout << tmp[i][j]  << '\n';
		}
	LL i, x, j;
	for(i=0;i<n;i++){
		cin >> x;
		seller.pb(x); 
	}
	for(i=0;i<buyer.size();i++){
		buyer[i].clear();
	}
	buyer.clear();
	cin >> m;
//	cout << n << '\n';
	for(i=0;i<m;i++){
//		cout << i << '\n';
		vector<LL>tmp;
		tmp.clear();
		buyer.pb(tmp);
		for(j=0;j<n;j++){
//			cout << i << ' ' << j << '\n';
			cin >> x;
			g[i][j] = x-seller[j];
			buyer[i].pb(x);	
		}
	}
}
bool can_buy(LL i, LL choice){
	if(choice==-1)return 0;
	if(match[i]==choice||final_price[choice] < buyer_price[i][choice]||(final_price[choice] == buyer_price[i][choice]&&i<use[choice]))
		return 1;
	return 0;
}
bool cmp(pair<LL,LL> a, pair<LL,LL> b){
	if(a.first!=b.first)return a.first > b.first;
	return a.second < b.second;	
}
void GAA(){
	LL ok = 0, i, j, tc=0;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++){
			buyer_price[i][j] = seller[j];	//buyer want to pay the price
		}
	while(!ok){
		tc++;
//		if(tc>100000)cout << "success ";
//		if(tc>100000)break;
		for(i=0;i<m;i++){
			LL tmp = -100000, choice=-1;
			vector<pair<LL,LL>> V;
			V.clear();
			V.pb({0,-1});
			for(j=0;j<n;j++){
				tmp = buyer[i][j]-buyer_price[i][j];
				V.pb({tmp,j});
			}
			sort(V.begin(),V.end(),cmp);
			for(j=0;j<V.size();j++){
				choice = V[j].second;
				if(can_buy(i,V[j].second)){
					if(match[i]==choice&&i==0)ok = 1;
					if(match[i]==choice)ok*=1;
					else ok = 0;
					if(use[choice]!=-1)match[use[choice]] = -1;
//					if(tc>10000){
//						cout << i << ' ' << ok << '\n';
//						cout << "success ";
//						cout << tc << ' ' << i << ' ' << choice << '\n';
//						cout << j << ' ' << V[j].first << '\n';
//					}
					match[i] = choice;
					use[choice] = i;
					final_price[choice] = buyer_price[i][choice];
					break;
				}
				else if(choice!=-1){
//					cout << tc << ' ';
//					cout << tmp << ' ';
//					cout << match[i] << ' ';
//					cout << choice << ' ';
					tmp = 0;
					if(j+1<V.size())tmp = V[j+1].first;
					if(tmp==0)tmp = buyer[i][choice];
					buyer_price[i][choice] = max(final_price[choice]+1,buyer[i][choice]-tmp-1);
//					cout << i << ' ';
//					cout << final_price[choice] << ' ';	
//					cout << buyer[i][choice]-tmp << '\n';
					ok = 0;
					break;
				}
				else{
					if(match[i]!=-1)use[match[i]] = -1;
					match[i] = choice;
					if(i==0)ok = 1;
					break;	
				}
			}
		}
//		for(i=0;i<n;i++)if(use[i]==-1)break;
//		if(i==n)ok = 1;
//		for(i=0;i<m;i++)if(match[i]==-1)break;
//		if(i==m)ok = 1;
//		for(j=0;j<match.size();j++)cout << match[j]+1 << " ";
//		cout << '\n';
//		for(j=0;j<final_price.size();j++)cout << final_price[j] << " ";
//		cout << '\n';
	}
	Max = 0;
	for(i=0;i<match.size();i++){
		if(match[i]!=-1 && buyer[i][match[i]]-seller[match[i]]>0)
			Max += buyer[i][match[i]]-seller[match[i]];
	}
	best_match = match;
}
void solve(){
	LL t, i;
	clock_t start, end;
	start = clock();
	cin >> t;
	for(i=0;i<t;i++){
		input();
		init();
//		GAA();
//		cout << Max << '\n';
		LL j;
//		for(j=0;j<best_match.size();j++)cout << best_match[j]+1 << " ";
//		cout << '\n';
//		for(j=0;j<final_price.size();j++)cout << final_price[j] << " ";
//		cout << '\n';
//		cout << n << ' ' << m << '\n';
		mn = 0;
		N = max(m,n)+2;
//		if(n < m){
//			mn = 1;
////			cout << n << ' ' << m << '\n';
//			swap(m,n);
//			Max = km();
////			cout << "\n\n\n\n";
////			continue;
//		}
//		else
			km();
		Max = 0;
		for(j=0;j<N;j++){
			if(mn==1)
				match[j] = match_y[j];
			else if(match_y[j]!=-1&&match_y[j]<match.size())
				match[match_y[j]] = j;
		}
		for(j=0;j<match.size();j++){
			if(match[j]!=-1 && match[j] < n && buyer[j][match[j]]-seller[match[j]]>0)
				Max += buyer[j][match[j]]-seller[match[j]];
			else
				match[j] = -1;
		}
		if(n < m)
			mn = 1;
		cout << Max << '\n';
//		if(mn==1)
//			for(j=0;j<n;j++)cout << match_y[j]+1 << " ";
//		else
		for(j=0;j<match.size();j++)cout << match[j]+1 << " ";
		cout << "\n" << mn << "\n";
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
	//	freopen("input.txt","r",stdin);
	//	freopen("HGAA_output.txt","w",stdout);
		solve();
	}
}

