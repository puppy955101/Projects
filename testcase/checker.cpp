#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
vector<string>input;
int tk, ts;
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
	int i=0, k=0;
	while(getline(cin,s)){
//		cout << s << '\n';
		int ok=1;
		if(s!=input[i]){
			k++;
			cout << "error: line " << i << "\n\t";
			cout << A << ": " << input[i] << "\n\t";
			cout << B << ": " << s << '\n'; 
			ok = 0;
		}
		i++;
		getline(cin,s);
//		cout << s << '\n';
		if(!ok&&s!=input[i]){
			k++;
			cout << "error: line " << i << "\n\t";
			cout << A << ": " << input[i] << "\n\t";
			cout << B << ": " << s << '\n'; 
		}
		i++;
		getline(cin,s);
//		cout << s << '\n';
		getline(cin,s);
//		cout << s << '\n';
	}
	tk += k;
	ts += input.size();
	cout << B << "(" << k << " / " << input.size() << ")\n";
	fclose(op);
}
void diff(string A, string B){
	input.clear();
	in(A);
//	cout << B <<'\n';
	FILE *op;
	string s;
	op = freopen(B.c_str(),"r",stdin);
    std::cin.clear();
//    std::cin.ignore(0x7fffffffffffffff, '\n');
	int i=0, k=0;
	while(getline(cin,s)){
//		cout << s << '\n';
		int ok=1;
		if(s!=input[i]){
			k++;
			cout << "error: line " << i << "\n\t";
			cout << A << ": " << input[i] << "\n\t";
			cout << B << ": " << s << '\n'; 
			ok = 0;
		}
		i++;
		getline(cin,s);
//		cout << s << '\n';
		i++;
		getline(cin,s);
//		cout << s << '\n';
		getline(cin,s);
//		cout << s << '\n';
	}
	tk += k;
	ts += input.size();
	cout << B << "(" << k << " / " << input.size() << ")\n";
	fclose(op);
}
int main(){
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);
	freopen("diff.txt","w",stdout);
	tk = ts = 0;
	for(int i=0;i<5;i++){
		string A = "testcase_0.txt";
		A[9] = '0'+i;
		string B = "GAA_" + A;
		string C = "HGAA_" + A;
		string D = "KM_" + A;
		A = "BF_" + A;
		solve(A,B);
		solve(A,C);
		solve(A,D);
	}
	cout << "Total(" << tk << " / " << ts << ")\n";
}

