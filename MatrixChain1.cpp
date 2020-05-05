/*确定计算矩阵连乘积的计算次序，使得按照这一次序计算矩阵连乘积*/
#include<iostream>
#define MaxNum 11 //矩阵个数上限
using namespace std;
class MatrixChain{
private:
	int (*m)[MaxNum], (*s)[MaxNum]; //用来保存矩阵连乘最小值和断点位置
	int *p,n;  //矩阵的行列数，和矩阵个数
	int LookupChain(int i, int j);
	void Traceback(int i, int j);
public:
	MatrixChain(int N, int *P){
		n = N;
		p = new int[N+1];
		p = P;
		m = new int[n][MaxNum];
		s = new int[n][MaxNum];
	}
	void Matrixchain();
	void Traceback();
	void LookupChain();
};
void  MatrixChain::LookupChain(){
	cout << "最终求出最优解值为"<< LookupChain(0, n-1) << endl;
}
void MatrixChain::Traceback(){
	cout<< '(';
	Traceback(0, n-1);
	cout << ')';
}
void MatrixChain::Matrixchain(){
	for(int i = 0; i < n; i++){
		m[i][i]=0;
	}
	for(int r = 1; r < n; r++){
		for(int i = 0; i <= n-r; i++){
			int j = i + r;
			m[i][j] = m[i+1][j] + p[i]*p[i+1]*p[j+1]; // A[i]*A[i+1:j]
			s[i][j] = i;
			for(int k = i+1; k < j; k++){
				int temp = m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];
				if(temp < m[i][j]){
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}
	cout<<"最终求出最优解值为："<<m[0][n-1]<<endl; 
}
void MatrixChain::Traceback(int i, int j){
	if(i == j){
		cout << 'A' << i;
		return;
	}
	if(i < s[i][j]){
		cout << '(';
	}
	Traceback(i,s[i][j]);
	if(i < s[i][j]){
		cout << ')';
	}
	if(s[i][j] +1 <j){
		cout << '(';
	}
	Traceback(s[i][j]+1,j);
	if(s[i][j]+1<j){
		cout << ')';
	}
}
int  MatrixChain::LookupChain(int i, int j){
	if(i == j){  //对角线元素赋值0
		return 0;
	}
	if(m[i][j] > 0){
		return m[i][j];
	}
	int u = LookupChain(i+1,j) + p[i]*p[i+1]*p[j+1]; 
									//先将m[i][j]赋值为 A[i]*A[i+1:j]乘积
	s[i][j] = i;
	for(int k = i; k < j; k++){    //自顶向下递归
		int t = LookupChain(i, k) + LookupChain(k+1, j) + p[i]*p[k+1]*p[j+1];
		if(t < u){
			u = t;
			s[i][j] = k;
		}
	}
	m[i][j] = u;  //将最小的乘积填入m表
	return u;
}
int main(){
	int n,*p;
	cout << "输入连乘矩阵的个数：";
	cin >> n;
	p = new int[n+1];
	cout << "他们的维数顺序排列为：（相邻的行列长度只需要输入一次）";
	for(int i = 0; i <= n; i++){
		cin >> p[i];
	}
	MatrixChain matrix(n, p);
	//matrix.Matrixchain();
	matrix.LookupChain();
	matrix.Traceback();
	delete []p;
	return 0;
}
