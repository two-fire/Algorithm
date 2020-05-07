/* 
 页面置换算法FIFO，先进先出
 计算缺页次数和缺页率
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define MLim 50 //设置内存中页表长度上限
#define Mnum 100 //设置所要访问的页面的最大个数
using namespace std;
int sum = 0; //缺页次数
int t = -1; //顺序
class FIFO{
public:
	FIFO(int page, int visit[], int nv):v(visit,visit + nv), time(nv,1000){
		plen =page;
	}
		
	int isInPage(int x); // 所要访问的页面x是否在内存中
	void PageFault(); // 缺页中断

private:
	vector<int> v; // 所要访问的页面
	vector<int> p; // 内存中页表
	vector<int> time; // 内存中页面进入的时间，越小进入的越早
	int plen; // 内存中页表长度
};
int FIFO::isInPage(int x){
	vector<int>::iterator it = find(p.begin(), p.end(), x); //返回查找的地址
	if(it != p.end()){
		return *it;
	}
	else{
		return -1;  //不在页表中
	}
}
void FIFO::PageFault(){
	int i,j;
	for(i = 0; i < v.size(); i++){
		if(isInPage(v[i]) == -1){
			sum++;
			if(p.size() < plen){  // 不在内存且页表有空
				p.push_back(v[i]);
				time[v[i]] = ++t;  //time下标为所要访问的按顺序的页面标号

			}
			else{  // 不在内存且页表满
				vector<int>::iterator minvalue = min_element(time.begin(), time.end());
				                              // 求最小的时间值
				for(j = 0; j < time.size(); j++){
					if(time[j] == *minvalue){
						break;
					}
				} //求最小时间值对应的time下标，即为需要被替换的页面标号
				vector<int>::iterator fir = find(p.begin(), p.end(), j);
				*fir = v[i]; // 替换页面标号
				*minvalue = 1000; 
				time[v[i]] = ++t;
			}
		}
	}
	cout << "缺页次数为：" << sum <<endl;
	cout << "缺页率为：" << sum*100.0/v.size() <<"%";
}

int main(){
	int visit[12] = {2,3,2,1,5,2,4,5,3,2,5,2};
	int page = 3;
	
	FIFO f(3, visit, 12);
	f.PageFault();
	return 0;
}
