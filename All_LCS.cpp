/*、最长公共子序列（Longest Common Subsequence,LCS）问题是：给定两个字符序列
X={x1,x2,……,xm}和 Y={y1,y2,……,yn}，
要求找出 A 和 B 的所有最长公共子序列。*/

#include<iostream>
#define MaxLength 11
using namespace std;
class LCS{
private:
	char *a, *b; //数组a，b
	int m, n;  //数组a，b的长度
	int (*c)[MaxLength], (*s)[MaxLength]; 
			 //c[i][j]存放最长公共子序列长度，s[i][j]记录当前解分量
	void CLCS(int ,int);
public:
	LCS(int na, int nb, char *x,char *y){
		m = na;
		n = nb;
		a = new char[m+2];
		b = new char[n+2];
		memset(a, 0, m+2);
		memset(b, 0, n+2);
		a = x;
		b = y;
		c = new int[MaxLength][MaxLength];
		s = new int[MaxLength][MaxLength];
		for(int i = 0; i <= m; i++){
			c[i][0] = 0;
			s[i][0] = 0;
		}
		for(int i = 0; i <= n; i++){
			c[0][i] = 0;
			s[i][0] = 0;
		}
	}

	void CLCS(); //最长公共子序列分量
	int LCSLength();  //最长公共子序列长度
};
void  LCS::CLCS(){
	CLCS(m,n);
	cout << endl;
}
 void LCS::CLCS(int i, int j){ 
	if(i ==0 || j == 0 || s[i][j] == 0) return;
	if(s[i][j] == 1){ //左上搜索
		cout << a[i];
		CLCS(i-1,j-1);
	}
	else if(s[i][j] == 2){  //向上搜索
		CLCS(i-1,j);
	}
	else if(s[i][j] == 3){  //向左搜索
		CLCS(i,j-1);
	}
	else if(s[i][j] == 4){  //如果为4，就从左，上两个方向搜索
		CLCS(i-1, j);
		cout<<endl;
		CLCS(i, j-1);
	}
	
}
int LCS::LCSLength(){
	for(int i = 1; i <= m; i++){
		for(int j = 1; j <= n; j++){
			if(a[i] == b[j]){
				c[i][j] = c[i-1][j-1] + 1;
				s[i][j] = 1;
			}
			else{
				if(c[i-1][j]== c[i][j-1]){
					c[i][j] = c[i-1][j];
					s[i][j] = 4;
				}
				else{
					if(c[i-1][j]> c[i][j-1]){ //取上面的值时，s为2
						c[i][j] = c[i-1][j];
						s[i][j] = 2;
					}
					else{
						c[i][j] = c[i][j-1];
						s[i][j] = 3;
					}
				}
			}
		}
	}
	return c[m][n];
}
int main(){
	int nx, ny;
	char *x, *y;
	cout << "输入两个字符串长度:" ;
	cin >> nx >> ny;
	x = new char[nx+2];
	y = new char[ny+2];
	cout << "分别输入两个字符串:" ;
	x[nx+1] = '/0';
	y[ny+1] = '/0';
	for(int i = nx; i >= 1; i--){
		cin >> x[i];
	}
	for(int i = ny; i >= 1; i--){
		cin >> y[i];
	}
	LCS lcs(nx,ny,x, y);
	cout << "两个字符串最长公共子序列长度:" << lcs.LCSLength() << endl;
	cout << "最长公共子序列为："<< endl;
	lcs.CLCS();
	delete []x;
	delete []y;
	system("pause");
	return 0;
}
