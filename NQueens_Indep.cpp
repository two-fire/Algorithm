/* 
 编程实现从 n-皇后问题的所有 92 种可行解中筛选出 12 种独立解，
 而其余的解都可以由这些独立解利用对称性或旋转而得到
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX_n 1000
int sum = 0;
class NQueens{
public:
	NQueens(int N):s(N){
		n = N;
	}
	bool isPlace(int i, int j); //第i行皇后是否能放第j列
	void RBacktrack();
	bool exist(vector<int> s); //判断是否可以通过变换而成为现有解
	bool test(vector<int> s, vector<vector<int>> solution); 
	                                         //判断变换后的s是否与现有解相同
private:
	vector<int> s; //存放第i行皇后放在哪一列
	int n; //n皇后
	vector<vector<int>> solution; //存放保存的独立解
	void RBacktrack(int i);
};
void NQueens::RBacktrack(){
	RBacktrack(0);
	cout <<sum;
}
bool NQueens::isPlace(int i, int j){
	for(int k = 0; k < i; k++){
		if(s[k] == j || abs(s[k] - j) == abs(k - i)){
			return false;
		}
	}
	return true;
}
void NQueens::RBacktrack(int i){
	for(int j = 0; j < n; j++){
		if(isPlace(i,j)){
			s[i] = j;
			if(i == n-1){
				if(exist(s) == false){ //不是已有的独立解，则输出
					sum++;
					for(int k = 0; k < n; k++){
						cout << s[k] << ' ';
					}
					cout << endl;
					solution.push_back(s);
				}
				else{
					continue;
				}
			}
			else{
				RBacktrack(i+1); //深度搜索
			}
		}
	}
}
bool NQueens::exist(vector<int> s){
	vector<int> temp(n);
	//上下对称
	for(int i = n - 1; i >= 0; i--){
		temp[n-1-i] = s[i];
	}
	if(test(temp,solution))
		return true;

	//左右对称
	for(int i = 0; i < n; i++){
		temp[i] = n-1-s[i];
	}
	if(test(temp,solution))
		return true;

	//左上到右下对角线对称
	for(int i = 0; i < n; i++){
		temp[s[i]] = i;
	}
	if(test(temp,solution))
		return true;
	//右上到左下对角线对称
	for(int i = 0; i < n; i++){
		temp[n-1-s[i]] = n-1-i;  // 行号其实为：n-1-i-s[i]+i,列号为n-1-i-s[i]+s[i]
	}
	if(test(temp,solution))
		return true;
	//顺时针旋转90°
	for(int j = 0; j < n; j++){
		int res = find(s.begin(), s.end(), j) - s.begin(); //j在s数组中的下标
		temp[j] = n - 1 - res;
	}
	if(test(temp,solution))
		return true;

	//顺时针旋转180°
	/*for(int j = 0; j < n; j++){
		int res = find(temp.begin(), temp.end(), j) - temp.begin();
		temp[j] = n-1-res;
	}
	if(test(temp,solution))
		return true;*/ //错误
	for(int i = n - 1; i >= 0; i--){
		temp[n-1-i] = n-1-s[i];
	}
	if(test(temp,solution))
		return true;

	//逆时针旋转90°
	for(int j = n-1; j >= 0; j--){
		int res = find(s.begin(), s.end(), j) - s.begin();
		temp[n-1-j] = res;
	}
	if(test(temp,solution))
		return true;
	return false;
}
bool NQueens::test(vector<int> s, vector<vector<int>> solution){
	for(int i = 0; i < solution.size(); i++){
		if(s == solution[i]){
			return true;
		}
	}
	return false;
}
int main(){
	int N=8;
	NQueens q(N);
	q.RBacktrack();
	return 0;
}
	
