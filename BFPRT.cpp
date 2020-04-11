//线性时间内，从无序列表找到第k小的元素。
#include<iostream>
using namespace std;
class SortableList{
private:
	int *l;
	int maxSize;
	int k; //第k小的元素
	void Swap(int i, int j); 
	int Partition(int left, int right);
	void InsertSort(int left,int right); 
	int Select(int k,int left,int right,int r);
public:
	SortableList(int mSize){
		maxSize = mSize;
		l = new int[mSize];
	}
	~SortableList(){
		delete []l;
	}
	void Input();
	void Select();
};

void SortableList::Input(){
	int i=0;
	cout<<"输入初始数组：";
	while(i<maxSize){
		cin>>l[i++];
	}
	cout<<"输入要查找的第k小的元素：k=";
	cin>>k;
}
void SortableList::Swap(int i, int j){  //交换下标为i，j的元素
	int m = l[i];
	l[i] = l[j];
	l[j] = m;
}
void SortableList::InsertSort(int left,int right){ //直接插入排序
	int i, j, m;
	for(i = left+1; i <= right; i++){ 
		                //从第二个数开始，与前面已排好的数组进行比较插入
		m = l[i];
		for(j = i-1; j >= left; j--){
			           //依次于前面比较，直到第一个数
			if(l[j] > m) //如果比要插入的数大，向后移动一位，让出位置
				l[j+1] = l[j];
			else   //否则要插入的数就应该在l[j]后面一位
				break;
		}  
		l[j+1] = m;  //把m放到空出的位置上
	}
}
int SortableList::Partition(int left, int right){ 
	                                   //执行以v为分界线的划分操作
	int v_value = l[left];
	int div = right; //跟踪分界线下标
	for(int i = right; i >= left; i--){
		if(l[i] > v_value){
			Swap(div, i);
			div--; 
		}
	}
	Swap(div, left); //使v的左边全小于v，右边全大于v
	return div;  //返回此时v_value的下标
}
int SortableList::Select(int k,int left,int right,int r) {
	                             //每个分组r个元素，寻找第k小元素 
	int n = right - left + 1;
	if(n <= r){
		InsertSort(left,right);
		return left + k - 1;  //问题足够小，直接插入排序，返回下标
	}
	for(int i = 1; i <= n/r ; i++){
		InsertSort(left+(i-1)*r, left+i*r-1);
		                                //排序获得每组的中间元
		Swap(left+i-1, left+(i-1)*r+(int)ceil(r/2.0)-1);
			                           //将中间元放到数组开头
	}                                  
	int j = Select((int)ceil(n/r/2.0),left, left+n/r-1, r);
										//求中间元的中间元的下标
	Swap(left, j);  //将中间元的中间元放到首位
	j = Partition(left, right);
	if(k == j-left+1) return j;  //第k小的下标正好等于分界线下标
	else if(k < j-left+1){  //在分界线左边查找第k小的元素
		return Select(k,left,j-1,r);
	}
	else{
		return  Select(k-(j-left+1),j+1,right,r); 
		                     //右边查找第 k-(j-left+1) 小的元素
	}
}
void SortableList::Select(){
	int index = Select(k, 0, maxSize-1, 5);
	cout<<"第"<<k<<"小的元素为："<<l[index]<<endl;
		
}

int main(){
	int n;
	cout<<"输入元素个数：";
	cin>>n;
	SortableList list(n);
 	list.Input();
	list.Select();
	return 0;
}
