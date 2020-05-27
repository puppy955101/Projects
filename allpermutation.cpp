#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<int>seller;
vector<vector<int>>buyer_price;
vector<vector<int>>buyer;
int n, m, Max;
vector<int>match;
vector<int>final_price;
vector<int>best_match;
vector<int>use;
void init(){
	Max = -1;
	match.clear();
	use.clear();
	buyer_price.clear();
	final_price.clear();
	buyer_price.resize(m);
	for(int i=0;i<m;i++)buyer_price[i].resize(n);
	final_price.resize(n);
	match.resize(m);
	for(int i=0;i<m;i++)match[i] = -1;
	use.resize(n);
	for(int i=0;i<n;i++)use[i] = -1;
	best_match.clear();
}

void input(){
	cin >> n;
	cout << n << '\n';
	seller.clear();
	int i, x, j;
	for(i=0;i<n;i++){
		cin >> x;
		cout << x*1000 << " \n"[i==n-1];
		seller.pb(x); 
	}
	buyer.clear();
	cin >> m;
	cout << m << '\n';
	for(i=0;i<m;i++){
		vector<int>tmp;
		tmp.clear();
		buyer.pb(tmp);
		for(j=0;j<n;j++){
			cin >> x;
			cout << x*1000 << " \n"[j==n-1];
			buyer[i].pb(x);	
		}
	}
}

void GAA(){
	int ok = 0, i, j, tc=0;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++){
			buyer_price[i][j] = seller[j];	//buyer want to pay the price
		}
	while(!ok){
//		tc++;
//		if(tc>100)break;
		for(i=0;i<m;i++){
			int tmp = -100000, choice=0;
			for(j=0;j<n;j++){
				if(tmp < buyer[i][j]-buyer_price[i][j])
					tmp = buyer[i][j]-buyer_price[i][j], choice = j;
			}
			if(final_price[choice] < buyer_price[i][choice]){
				if(use[choice]!=-1)match[use[choice]] = -1;
				match[i] = choice;
				use[choice] = i;
				final_price[choice] = buyer_price[i][choice];
			}
			else{
				buyer_price[i][choice]++;	
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
	int t, i;
	clock_t start, end;
	start = clock();
	cin >> t;
	cout << t << '\n';
	for(i=0;i<t;i++){
		input();
	}
}

int main(){
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	freopen("input.txt","r",stdin);
	freopen("TMP.txt","w",stdout);
	solve();
}

