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
mt19937 seed(2020);
int randint(int lb, int ub) { // [lb, ub]
	return uniform_int_distribution<int>(lb,ub)(seed);
}

void input(){
//	cin >> n;
	n = randint(2,10);
	cout << n << '\n';
	int k = 10000;
	seller.clear();
	int i, x, j;
	for(i=0;i<n;i++){
//		cin >> x;
		x = randint(10,100);
		cout << x << " \n"[i==n-1];
		seller.pb(x); 
	}
	buyer.clear();
	m = randint(2,10);
	if(n==m)m++;
	cout << m << '\n';
	for(i=0;i<m;i++){
		vector<int>tmp;
		tmp.clear();
		buyer.pb(tmp);
		for(j=0;j<n;j++){
			x = randint(10,100);
			cout << x << " \n"[j==n-1];
			buyer[i].pb(x);	
		}
	}
}

void solve(){
	int t, i;
	t = 10;
	cout << t << '\n';
	for(i=0;i<t;i++){
		input();
	}
}

int main(){
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	for(int i=0;i<5;i++){
		string s;
		s = "./testcase/testcase_";
		s = s + char('0'+i);
		s = s + ".txt";
		freopen(s.c_str(),"w",stdout);
		solve();
	}
}

