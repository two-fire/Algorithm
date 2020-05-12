/*
 任何两个皇后都不在同一行、同一列或同一斜线上。
 请输出 8 皇后问题的所有可行解。 
*/
#include<iostream>
#define Max_n 100 // 最大求解Max_n 皇后问题
using namespace std;
int sum = 0;
class n_queens{
public:
	n_queens(int N){
		n = N;
		s = new int[N];
		memset(s, 0, sizeof(int)*N); // 以0初始化
	}
	void IBacktrack(); // 迭代回溯
private:
	int n; // n皇后
	int *s; // 存放第i行皇后所放的列号
	void IBacktrack(int i); // 迭代回溯
	bool isPlace(int i, int j); // i行皇后是否可以放在j列处
};
bool n_queens::isPlace(int i, int j){
	for(int k = 0; k < i; k++){
		if(s[k] == j || abs(s[k] - j) == abs(k - i)){
			return false;
		}
	}
	return true;
}
void n_queens::IBacktrack(int i){
	/* 写法一：
	for(int k = 0; k < n; k++){
		if(isPlace(i, k)){ 
			s[i] = k;
			IBacktrack(i+1); // 深度遍历
		}
	}
	if(s[n-1] > 0){
		for(int k = 0; k < n; k++)
			cout << s[k] << ' ';
		cout << endl;
		s[n-1] = 0;
	} */
	for(int k = 0; k < n; k++){
		if(isPlace(i, k)){ 
			s[i] = k;
			if(i == n-1){
				sum++;
				for(int k = 0; k < n; k++){
					cout << s[k] << ' ';
				}
				cout << endl;
			}
			if(sum ==1)break;
			else{
				IBacktrack(i+1);
			}
		}
	}
}
void n_queens::IBacktrack(){
	IBacktrack(0);
	cout <<sum;
}
int main(){
	int N = 8;  // 8皇后问题
	n_queens q(N);
	q.IBacktrack();
	return 0;
}
		

