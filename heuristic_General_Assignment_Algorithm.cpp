#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<LL>seller;
vector<vector<LL>>buyer_price;
vector<vector<LL>>buyer;
LL n, m, Max, nc, mc;
vector<LL>match;
vector<LL>final_price;
vector<LL>best_match;
vector<LL>use;
void init(){
	Max = -1;
	match.clear();
	use.clear();
	for(int i=0;i<buyer_price.size();i++)buyer_price[i].clear();
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
	cin >> nc;
	seller.clear();
	LL i, x, j, k;
	for(i=0;i<n;i++){
		cin >> x;
		seller.pb(x); 
	}
	for(i=0;i<nc-1;i++)
		for(j=0;j<n;j++)
			seller.pb(seller[j]);
	for(i=0;i<buyer.size();i++)buyer[i].clear();
	buyer.clear();
	cin >> m;
	cin >> mc;
	for(i=0;i<m;i++){
		vector<LL>tmp;
		tmp.clear();
		buyer.pb(tmp);
		for(j=0;j<n;j++){
			cin >> x;
			buyer[i].pb(x);	
		}
		for(k=0;k<nc-1;k++)
			for(j=0;j<n;j++)
				buyer[i].pb(buyer[i][j]);
	}
	for(i=0;i<mc-1;i++)
		for(j=0;j<m;j++)
			buyer.pb(buyer[j]);
	n *= nc;
	m *= mc;
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
	for(int i=0;i<5;i++){
		string input = "testcase_0.txt";
		input[9] = '0'+i;
		string output = "HGAA_" + input;
		input = "./testcase/" + input;
		output = "./testcase/" + output;
		freopen(input.c_str(),"r",stdin);
		freopen(output.c_str(),"w",stdout);
	//	freopen("input.txt","r",stdin);
	//	freopen("HGAA_output.txt","w",stdout);
		solve();
	}
}

