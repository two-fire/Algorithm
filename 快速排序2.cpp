//使用分治法的快速排序算法，实现对初始序列的排序
#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
class SortableList{
private:
	int *l;
	int maxSize;
	//int n;
	void Swap(int i, int j); 
	void QuickSort(int left, int right);
	int Partition(int left, int right);
	int RandomizedPartition(int left, int right);
public:
	SortableList(int mSize){
		maxSize = mSize;
		l = new int[mSize];
		//n=0; //数组中已有元素个数
	}
	~SortableList(){
		delete []l;
	}
	void QuickSort();
	void Input();
	void Output();
	
};
void SortableList::QuickSort(){
	QuickSort(0,maxSize-1);
}
void SortableList::Input(){
	int i=0;
	cout<<"输入待排序数组：";
	while(i<maxSize){
		cin>>l[i++];
		
	}
}
void SortableList::Output(){
	cout<<"排序之后的数组：";
	for(int i=0;i<maxSize;i++)
		cout<<l[i]<<" ";
}
void SortableList::Swap(int i, int j){
	int m = l[i];
	l[i] = l[j];
	l[j] = m;
}
void SortableList::QuickSort(int left, int right){
	if(left<right){
		int m=RandomizedPartition(left,right); //调用 RandomizedPartition 函数 
		QuickSort(left,m-1);  //对左边进行一趟划分操作
		QuickSort(m+1,right); //对右边进行一趟划分操作
	}
}
int SortableList::RandomizedPartition(int left, int right) {       
	srand((unsigned)time(NULL)); //用当前时间作为种子 
	int i = rand()%(right-left+1) +left; //产生一个 left~right范围内的随机数 
	Swap(i, left);
	return Partition(left, right);
}
int SortableList::Partition(int left, int right){ //划分操作
	int i=left+1;
	int j=right;
	do{
		while(i<=right){
			if(l[i]>=l[left]) break;  //i最终指向比基准元素大或者相等的元素下标
			i++;
		}
		while(j>left){
			if(l[j]<=l[left]) break;  //j最终指向比基准元素小或者相等的元素下标
			j--;
		}
		if(i<j) Swap(i,j);
	}while(i<j);
	Swap(left,j);
	return j;
}
int main(){
	int n;
	cout<<"输入元素个数：";
	cin>>n;
	SortableList list(n);
	list.Input();
	list.QuickSort();
	list.Output();
	return 0;
}




	
