//����ʱ���ڣ��������б��ҵ���kС��Ԫ�ء�
#include<iostream>
using namespace std;
class SortableList{
private:
	int *l;
	int maxSize;
	int k; //��kС��Ԫ��
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
	cout<<"�����ʼ���飺";
	while(i<maxSize){
		cin>>l[i++];
	}
	cout<<"����Ҫ���ҵĵ�kС��Ԫ�أ�k=";
	cin>>k;
}
void SortableList::Swap(int i, int j){  //�����±�Ϊi��j��Ԫ��
	int m = l[i];
	l[i] = l[j];
	l[j] = m;
}
void SortableList::InsertSort(int left,int right){ //ֱ�Ӳ�������
	int i, j, m;
	for(i = left+1; i <= right; i++){ 
		                //�ӵڶ�������ʼ����ǰ�����źõ�������бȽϲ���
		m = l[i];
		for(j = i-1; j >= left; j--){
			           //������ǰ��Ƚϣ�ֱ����һ����
			if(l[j] > m) //�����Ҫ�������������ƶ�һλ���ó�λ��
				l[j+1] = l[j];
			else   //����Ҫ���������Ӧ����l[j]����һλ
				break;
		}  
		l[j+1] = m;  //��m�ŵ��ճ���λ����
	}
}
int SortableList::Partition(int left, int right){ 
	                                   //ִ����vΪ�ֽ��ߵĻ��ֲ���
	int v_value = l[left];
	int div = right; //���ٷֽ����±�
	for(int i = right; i >= left; i--){
		if(l[i] > v_value){
			Swap(div, i);
			div--; 
		}
	}
	Swap(div, left); //ʹv�����ȫС��v���ұ�ȫ����v
	return div;  //���ش�ʱv_value���±�
}
int SortableList::Select(int k,int left,int right,int r) {
	                             //ÿ������r��Ԫ�أ�Ѱ�ҵ�kСԪ�� 
	int n = right - left + 1;
	if(n <= r){
		InsertSort(left,right);
		return left + k - 1;  //�����㹻С��ֱ�Ӳ������򣬷����±�
	}
	for(int i = 1; i <= n/r ; i++){
		InsertSort(left+(i-1)*r, left+i*r-1);
		                                //������ÿ����м�Ԫ
		Swap(left+i-1, left+(i-1)*r+(int)ceil(r/2.0)-1);
			                           //���м�Ԫ�ŵ����鿪ͷ
	}                                  
	int j = Select((int)ceil(n/r/2.0),left, left+n/r-1, r);
										//���м�Ԫ���м�Ԫ���±�
	Swap(left, j);  //���м�Ԫ���м�Ԫ�ŵ���λ
	j = Partition(left, right);
	if(k == j-left+1) return j;  //��kС���±����õ��ڷֽ����±�
	else if(k < j-left+1){  //�ڷֽ�����߲��ҵ�kС��Ԫ��
		return Select(k,left,j-1,r);
	}
	else{
		return  Select(k-(j-left+1),j+1,right,r); 
		                     //�ұ߲��ҵ� k-(j-left+1) С��Ԫ��
	}
}
void SortableList::Select(){
	int index = Select(k, 0, maxSize-1, 5);
	cout<<"��"<<k<<"С��Ԫ��Ϊ��"<<l[index]<<endl;
		
}

int main(){
	int n;
	cout<<"����Ԫ�ظ�����";
	cin>>n;
	SortableList list(n);
 	list.Input();
	list.Select();
	return 0;
}
