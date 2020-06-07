#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<string>input;
void in(string A){
	string s;
	FILE *op;
	op = freopen(A.c_str(),"r",stdin);
    std::cin.clear();
	while(getline(cin,s)){
//		cout << s << '\n';
		input.pb(s);
		getline(cin,s);
//		cout << s << '\n';
		input.pb(s);
		getline(cin,s);
	}
	fclose(op);
}
void solve(string A, string B){
	input.clear();
	in(A);
//	cout << B <<'\n';
	FILE *op;
	string s;
	op = freopen(B.c_str(),"r",stdin);
    std::cin.clear();
//    std::cin.ignore(0x7fffffffffffffff, '\n');
	int i=0;
	while(getline(cin,s)){
//		cout << s << '\n';
		if(s!=input[i]){
			cout << "error: line " << i << "\n";
			cout << A << ": " << input[i] << '\n';
			cout << B << ": " << s << '\n'; 
		}
		i++;
		getline(cin,s);
//		cout << s << '\n';
		if(s!=input[i]){
			cout << "error: line " << i << "\n";
			cout << A << ": " << input[i] << '\n';
			cout << B << ": " << s << '\n'; 
		}
		i++;
		getline(cin,s);
//		cout << s << '\n';
		getline(cin,s);
//		cout << s << '\n';
	}
	fclose(op);
}
int main(){
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	freopen("diff.txt","w",stdout);
	for(int i=0;i<5;i++){
		string A = "testcase_0.txt";
		A[9] = '0'+i;
		string B = "GAA_" + A;
		string C = "HGAA_" + A;
		A = "BF_" + A;
		solve(A,B);
		solve(A,C);
	}
}

