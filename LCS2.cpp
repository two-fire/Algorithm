/*如果只需计算最长公共子序列的长度，而无须构造最优解，O(min{m,n})。 
计算 c[i][j]仅用到第 i 行和第 i-1 行元素。
因此，只需两行元素空间就可计算最长 公共子序列的长度。
并且选用序列长度较短的一个作为 y 序列，可以缩短每行元素的个数， 
从而进一步减少空间复杂*/
#include<iostream>
#define MaxLength 11
using namespace std;
class LCS{
private:
	char *a, *b; //数组a，b
	int *c1,*c2; //计算LCS用到的两行元素
	int l,s;	//数组a，b的长度小的放在s	 
public:
	LCS(int na, int nb, char *x,char *y){
		a = new char[na+2];
		b = new char[nb+2];
		a = x;
		b = y;
		if(na > nb){ 
			s = nb;
			l = na;
		}
		else{
			s = na;
			l = nb;
		}
		c1=new int[s+1];
		c2=new int[s+1]; 
		memset(c1,0,sizeof(c1));
		memset(c2,0,sizeof(c2)); 
	}
	int LCSLength();  //最长公共子序列长度
};
int LCS::LCSLength(){
	for(int i = 1; i <= l; i++){
		c1 = c2;
		memset(c2, 0, sizeof(c2));
		for(int j = 1; j <= s; j++){
			if(a[i] == b[j]){
				c2[j] = c1[j-1] + 1;
			}
			else{
				if(c2[j-1] >= c1[j]){
					c2[j] = c2[j-1];
				}
				else{
					c2[j] = c1[j];
				}
			}
		}
		
	}
	return c2[s];  //返回最优解值 
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
	for(int i = 1; i <= nx; i++){
		cin >> x[i];
	}
	for(int i = 1; i <= ny; i++){
		cin >> y[i];
	}
	LCS lcs(nx,ny,x, y);
	cout << "两个字符串最长公共子序列长度:" << lcs.LCSLength() << endl;
	delete []x;
	delete []y;
	system("pause");
	return 0;
}
