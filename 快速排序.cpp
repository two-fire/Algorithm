//ʹ�÷��η��Ŀ��������㷨��ʵ�ֶԳ�ʼ���е�����
#include<iostream>
using namespace std;
class SortableList{
private:
	int *l;
	int maxSize;
	//int n;
	void Swap(int i, int j); 
	void QuickSort(int left, int right);
	int Partition(int left, int right);
public:
	SortableList(int mSize){
		maxSize = mSize;
		l = new int[mSize];
		//n=0; //����������Ԫ�ظ���
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
	cout<<"������������飺";
	while(i<maxSize){
		cin>>l[i++];
		
	}
}
void SortableList::Output(){
	cout<<"����֮������飺";
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
		int m = Partition(left, right);//������l[left:right]ͨ�����ֲ����ֳ���������
		QuickSort(left,m-1);  //����߽���һ�˻��ֲ���
		QuickSort(m+1,right); //���ұ߽���һ�˻��ֲ���
	}
}
int SortableList::Partition(int left, int right){ //���ֲ���
	int i=left+1;
	int j=right;
	do{
		while(i<=right){
			if(l[i]>=l[left]) break;  //i����ָ��Ȼ�׼Ԫ�ش������ȵ�Ԫ���±�
			i++;
		}
		while(j>left){
			if(l[j]<=l[left]) break;  //j����ָ��Ȼ�׼Ԫ��С������ȵ�Ԫ���±�
			j--;
		}
		if(i<j) Swap(i,j);
	}while(i<j);
	Swap(left,j);
	return j;
}
int main(){
	int n;
	cout<<"����Ԫ�ظ�����";
	cin>>n;
	SortableList list(n);
	list.Input();
	list.QuickSort();
	list.Output();
	return 0;
}




	
