/*
 Optimal最佳置换算法（理论）
 置换以后不再被访问，或者在将来最迟才回被访问的页面，缺页中断率最低
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int sum = 0; //缺页次数
class OPT{
public:
	OPT(int page, int visit[], int nv):v(visit, visit+nv){
		plen = page;
	}
	int isInPage( int);  //是否在内存页表中，在返回页表中的页号,否则-1
	void PageFault();  //缺页中断

private:
	vector<int>p; // 内存中的页表
	vector<int>v;  // 所要访问的页面
	int plen; // 内存中页表长度
};
int OPT::isInPage(int x){
	vector<int>::iterator it = find(p.begin(), p.end(), x);
	if(it != p.end()){
		return *it;
	}
	else{
		return -1;
	}
}
void OPT::PageFault(){
	int i, j;
	for(i = 0; i < v.size(); i++){
		if(isInPage(v[i]) == -1){  //不在页表中
			sum++;
			if(p.size() < plen){ //页表为空
				p.push_back(v[i]);
			}
			else{  //页表满
				int index; //被置换的页号
				vector<int>::iterator far = v.begin()+i;
				for(j = 0; j < p.size(); j++){
					vector<int>::iterator temp = find(v.begin()+i, v.end(), p[j]);
											//从下一个开始遍历，查找最远访问的页面
					if(far < temp ){
						far = temp;
						index = j;
					}
				}
				p[index] = v[i];
			}
		}
	}
	cout << "缺页次数为：" << sum <<endl;
	cout << "缺页率为：" << sum*100.0/v.size() <<"%";
}
int main(){
	int visit[12] = {2,3,2,1,5,2,4,5,3,2,5,2};
	int page = 3;
	
	OPT f(3, visit, 12);
	f.PageFault();
	return 0;
}
