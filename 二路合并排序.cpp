#include<iostream>
using namespace std;
class SortableList{
private:
	int *l;
	int maxSize;
	int n;
	void MergeSort(int left,int right);
	void Merge(int left,int mid,int right);
public:
	SortableList(int mSize){
		maxSize=mSize;
		l=new int[maxSize];
		//n=0;  ����������Ԫ�ظ���
	}
	~SortableList(){
		delete[]l;
	}
	void Input();
	void Output();
	void MergeSort();

};
void SortableList::Input(){
		for(int i=0;i<maxSize;i++)
		cin>>l[i];
}
void SortableList::Output(){
	for(int i=0;i<maxSize;i++)
		cout<<l[i]<<" ";
}
void SortableList::MergeSort(){
	MergeSort(0,maxSize-1);
}
void SortableList::MergeSort(int left,int right){ //������ͨ�����ַ��ֽ�
	if(left<right){
		int mid=(left+right)/2;
		MergeSort(left,mid);
		MergeSort(mid+1,right);
		Merge(left,mid,right);
	}
}
void SortableList::Merge(int left,int mid,int right){  //�����ϲ�
	int *temp=new int[right-left+1];
	int i=left,j=mid+1,k=0;
	while(i<=mid&&j<=right)
		if(l[i]<=l[j]) temp[k++]=l[i++];
		else temp[k++]=l[j++];
	while(j<=right) temp[k++]=l[j++];
	while(i<=mid) temp[k++]=l[i++];
	for(k=left,i=0;k<=right;) l[k++]=temp[i++];
	delete[]temp;
}

int main(){
	int n;
	cout<<"���������еĳ��ȣ�";
	cin>>n;
	SortableList list(n);
	cout<<"���������У�";
	list.Input();
	list.MergeSort();
	list.Output();
	return 0;
}