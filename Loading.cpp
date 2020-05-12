/*
 有 n 个集装箱要装上 2 艘载重分别为 c1 和 c2的轮船，
 其中集装箱 i 的重量为 wi（1≤ i ≤ n），且∑𝑛 𝑖=1 𝑤𝑖 ≤ 𝑐1 + 𝑐2 。
 问是否有一个合理 的装载方案可以将这 n 个集装箱装上这 2 艘轮船？
 如果有，请给出装载方案。
*/
#include<iostream>
using namespace std;
template<class T>
class Load{
public:
	Load(int *W, int Wn, T C1, T C2){
		n =Wn;
		x = new int[Wn];
		bestx = new int[Wn];
		c1 = C1;
		c2 = C2;
		w = new T[Wn];
		w = W;
		total = 0;
		for(int i = 0; i < n; i++)
			total += w[i];
		cw = 0;
		bestw = 0;
		r = total;
	}
	//~Load(){};
	void Sort(); //w从小到大排序
	void RBacktrack(int i); //找到最接近第一艘轮船载重c1的最佳装载方案，       
						//最优载重值bestw，   
	void Show();//输出整个装载方案 		
private:
	int n; //集装箱个数
	int *x; //当前解 
	int *bestx; //当前第一艘船的最优解数组bestx
	T c1, c2; // 轮船载重
	T *w; //集装箱重量
	T total; //所有集装箱重量之和
	T cw,bestw; //cw为当前实际载重量，bestw为当前最优载重量
	T r; //剩余集装箱总重量				
};
/*template<class T>
void Load<T>::Sort(){
	for(int i = 0; i < n-1; i++){
		for(int j = i; j < n; j++){
			int temp;
			if(w[i] > w[j]){
				temp = w[i];
				w[i] = w[j];
				w[j] = temp;
			}
		}
	}
}*/
template<class T>
void Load<T>::RBacktrack(int i){ //第i层
	if(i > n-1){ //如果进入最后一层结点
		if(cw > bestw){
			for(int j = 0; j < n; j++){
				bestx[j] = x[j];
			}
			bestw =cw;
		}
		return;
	}
	//左子树
	r -= w[i-1];
	if(cw + w[i-1] <= c1){
		x[i-1] = 1;
		cw += w[i-1];
		RBacktrack(i+1);
		cw -= w[i-1];
	}
	//右子树
	if(r + cw > bestw){
		x[i-1] = 0;
		RBacktrack(i+1);
	}
	r += w[i-1];
}
template<class T>
void Load<T>::Show(){
	if(r > c2){
		cout << "不能装入！"<< endl;
	}
	else{
		cout << "船1装入的货物为：";
		for(int i = 0; i < n; i++){
			if(bestx[i] == 1){
				cout << w[i] << " ";
			}
		}
		cout << endl;
		cout << "船1装入的货物为：";
		for(int i = 0; i < n; i++){
			if(bestx[i] == 0){
				cout << w[i] << " ";
			}
		}
		cout << endl;
	}
}
int main(){
	int *W, Wn, C1, C2;
	cout << "分别输入两艘船的核定载重量：";
	cin >> C1 >> C2;
	cout << "输入集装箱的个数：";
	cin >> Wn;
	W = new int[Wn];
	cout << "输入集装箱的重量：";
	for(int i = 0; i < Wn; i++){
		cin >> W[i];
	}
	Load<int> ld(W, Wn, C1, C2);
	ld.RBacktrack(1);
	ld.Show();
	delete W;
	system("pause");
	return 0;
}
