#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<int>seller;
vector<vector<int>>buyer;
int n, m, Max;
vector<int>match;
vector<int>best_match;
vector<int>use;
LL tc = 0;
void init(){
	Max = -1;
	match.clear();
	use.clear();
	match.resize(m);
	use.resize(n);
	best_match.clear();
	tc = 0;
}

void input(){
	cin >> n;
	seller.clear();
	int i, x, j;
	for(i=0;i<n;i++){
		cin >> x;
		seller.pb(x); 
	}
	buyer.clear();
	cin >> m;
	for(i=0;i<m;i++){
		vector<int>tmp;
		tmp.clear();
		buyer.pb(tmp);
		for(j=0;j<n;j++){
			cin >> x;
			buyer[i].pb(x);	
		}
	}
}

int total(){
	int i, re=0;
	for(i=0;i<match.size();i++){
		if(match[i]!=-1)
			re += buyer[i][match[i]]-seller[match[i]];
	}
	return re;
}

void DFS(int pos){
	if(pos==m){
		tc++;
//		for(int j=0;j<match.size();j++)cout << match[j]+1 << " ";
//		cout << '\n';
		int tmp = total();
		if(Max < tmp){
			Max = tmp;
			best_match = match;
		}
		return;	
	}
	int i;
	match[pos] = -1;
	DFS(pos+1);
	for(i=0;i<n;i++){
		if(!use[i]){
			use[i] = 1;
			match[pos] = i;
			DFS(pos+1);
			use[i] = 0;
		}
	}
}
void solve(){
	int t, i;
	clock_t start, end;
	start = clock();
	cin >> t;
	for(i=0;i<t;i++){
		input();
		init();	
		DFS(0);
		cout << Max << '\n';
//		cout << tc << '\n';
		int j;
		for(j=0;j<best_match.size();j++)cout << best_match[j]+1 << " ";
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
	string output = "BF_" + input;
	input = "./testcase/" + input;
	output = "./testcase/" + output;
	freopen(input.c_str(),"r",stdin);
	freopen(output.c_str(),"w",stdout);
	solve();
}

