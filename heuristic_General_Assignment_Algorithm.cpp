#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<LL>seller;
vector<vector<LL>>buyer_price;
vector<vector<LL>>buyer;
LL n, m, Max;
vector<LL>match;
vector<LL>final_price;
vector<LL>best_match;
vector<LL>use;
void init(){
	Max = -1;
	match.clear();
	use.clear();
	buyer_price.clear();
	final_price.clear();
	buyer_price.resize(m);
	for(LL i=0;i<m;i++)buyer_price[i].resize(n);
	final_price.resize(n);
	match.resize(m);
	for(LL i=0;i<m;i++)match[i] = -1;
	use.resize(n);
	for(LL i=0;i<n;i++)use[i] = -1;
	best_match.clear();
}

void input(){
	cin >> n;
	seller.clear();
	LL i, x, j;
	for(i=0;i<n;i++){
		cin >> x;
		seller.pb(x); 
	}
	buyer.clear();
	cin >> m;
	for(i=0;i<m;i++){
		vector<LL>tmp;
		tmp.clear();
		buyer.pb(tmp);
		for(j=0;j<n;j++){
			cin >> x;
			buyer[i].pb(x);	
		}
	}
}
bool can_buy(LL i, LL choice){
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
		if(tc>10000)break;
		for(i=0;i<m;i++){
			LL tmp = -100000, choice=0;
			vector<pair<LL,LL>> V;
			V.clear();
			for(j=0;j<n;j++){
				tmp = buyer[i][j]-buyer_price[i][j];
				V.pb({tmp,j});
			}
			sort(V.begin(),V.end(),cmp);
			for(j=0;j<V.size();j++){
				choice = V[j].second;
				if(can_buy(i,V[j].second)){
					if(use[choice]!=-1)match[use[choice]] = -1;
//					cout << "success ";
//					cout << tc << ' ' << i << ' ' << choice << '\n';
					match[i] = choice;
					use[choice] = i;
					final_price[choice] = buyer_price[i][choice];
					break;
				}
				else{
//					cout << tc << ' ';
//					cout << tmp << ' ';
//					cout << match[i] << ' ';
//					cout << choice << ' ';
					tmp = 0;
					if(j+1<V.size())tmp = V[j+1].first;
					if(tmp==0)tmp = buyer[i][choice];
					buyer_price[i][choice] = max(final_price[choice]+1,buyer[i][choice]-tmp);
//					cout << i << ' ';
//					cout << final_price[choice] << ' ';	
//					cout << buyer[i][choice]-tmp << '\n';
					break;
				}
			}
		}
		for(i=0;i<n;i++)if(match[i]==-1)break;
		if(i==n)ok = 1;
//		for(j=0;j<match.size();j++)cout << match[j]+1 << " ";
//		cout << '\n';
//		for(j=0;j<final_price.size();j++)cout << final_price[j] << " ";
//		cout << '\n';
	}
	Max = 0;
	for(i=0;i<match.size();i++){
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
		GAA();
		cout << Max << '\n';
		LL j;
		for(j=0;j<best_match.size();j++)cout << best_match[j]+1 << " ";
		cout << '\n';
		for(j=0;j<final_price.size();j++)cout << final_price[j] << " ";
		cout << '\n';
		end = clock();
		cout << "Time: " << ((double)(end-start))/CLOCKS_PER_SEC << "s\n";
		start = clock();
	}
}

int main(){
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	freopen("input.txt","r",stdin);
	freopen("HGAA_output.txt","w",stdout);
	solve();
}

