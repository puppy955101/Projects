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

void GAA(){
	LL ok = 0, i, j, tc=0;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++){
			buyer_price[i][j] = seller[j];	//buyer want to pay the price
		}
	while(!ok){
		tc++;
//		if(tc>10000)break;
		for(i=0;i<m;i++){
			LL tmp = -1, choice=-1;
			for(j=0;j<n;j++){
				if(tmp < buyer[i][j]-buyer_price[i][j])
					tmp = buyer[i][j]-buyer_price[i][j], choice = j;
			}
			if(choice!=-1&&(match[i]==choice||final_price[choice] < buyer_price[i][choice])){
				if(match[i]==choice&&i==0)ok = 1;
				if(match[i]==choice)ok*=1;
				else ok = 0;
//				if(tc>10000)
//					cout << i << ' ' << ok << '\n';
				if(use[choice]!=-1)match[use[choice]] = -1;
				match[i] = choice;
				use[choice] = i;
				final_price[choice] = buyer_price[i][choice];
			}
			else if(choice!=-1){
				buyer_price[i][choice]++;
				ok = 0;	
			}
			else{
				if(match[i]!=-1)use[match[i]] = -1;
				match[i] = choice;
				if(i==0)ok = 1;
//				break;	
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
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string input = "testcase_0.txt";
	string output = "GAA_" + input;
	input = "./testcase/" + input;
	output = "./testcase/" + output;
	freopen(input.c_str(),"r",stdin);
	freopen(output.c_str(),"w",stdout);
	solve();
}

