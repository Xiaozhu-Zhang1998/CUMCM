#include<iostream>
#include<cmath>
#define  inf  5000//�����
using namespace std;
//���ڲ�ͬ���ֻ��Ҫ�޸����³�ֵ�� 
int ons = 20, tws = 33, ths = 46; 
int pro[2] = {400,378};//�ӹ�ʱ��,CNC1=455,CNC2=182 
int rep[9] = {0,28,31,28,31,28,31,28,31}; 
bool type[9]; 
int put_down = 25; 
/*
int ons = 18, tws = 32, ths = 46; 
int pro[2] = {455,182};//�ӹ�ʱ��,CNC1=455,CNC2=182 
int rep[9] = {0,27,32,27,32,27,32,27,32}; 
bool type[9]; 
int put_down = 25;*/ 
int L[2][9][9] = {0};
int full = 0,t_full;//0��ʾ��ǰΪ�ճ� 
int S[9] = {10000,0,0,0,0,0,0,0,0};//�ӹ�ʣ��ʱ��
bool B[9] = {0,0,0,0,0,0,0,0,0};//�Ƿ�������
int num = 0;//��Ʒ���� 
int T[9] = {10000,0} ;//��ǰ״̬��������CNC�ӹ�̨�Ĵ��� 
void init();
void print(); 
/*�ͽ�ԭ��*/
//int min_index(int *T){
//	int i=1,num=9;
//	int min_ind = i;
//	for(; i<num; i++ ){
//		if(T[i] < T[min_ind]) min_ind = i;
//	}
//	return min_ind;
//}


//FIFOԭ�� 
//int min_index(int *T){
//	int i=1,num=9;
//	int min_T_ind = 0;
//	int min_S_ind = 0;
//	bool temp = 0; //temp = 1����ʾ������Ϊ��һ��ѡ�� 
//	for(; i<num; i++ ){
//		if(T[i] < T[min_T_ind]) min_T_ind = i;
//		temp = 0;
//		if(full == 1 && type[i]==1)  
//				temp = 1;
//			else if(full == 0){
//				if(type[i]&&B[i] || not(type[i]))
//					temp = 1;
//		}
//		
//		if( S[i] < S[min_S_ind] && temp){
//			//if(full == 1 && type[i] == 1  || full == 0)  //�������а����ϣ������ȥCNC2���ճ���ȥ�ȵ���õ�CNC1 �� ��CNC2
////			if(type[i]&&B[i]  || not(type[i]))
////				min_S_ind = i;
//			if(full == 1 && type[i]==1)  
//				min_S_ind = i;
//			else if(full == 0){
//				if(type[i]&&B[i] || not(type[i]))
//					min_S_ind = i;
//			}
//				
//		}  
//	}
//	
//	if(S[min_S_ind] < 0) return min_S_ind; 
//	return min_T_ind; 
//
//}

////HRRNԭ�� 
int min_index(int *T){
	int temp[9]; 
	int max_ind = 1;
	int num = 9;
	for(int i=1; i<num; i++ ){
		 
		if(T[i] < inf)//ȷ��S<0,����T��ʱ����� 
			temp[i] = (-S[i] + T[i]) / T[i];//�ȴ�ʱ��Խ�������ȼ�Խ�ߣ�  ����ԽС�����ȼ�Խ�ߡ�	
		else temp[i] = -1;
	} 
	
	for(int i=1; i<num; i++ ){
		if(temp[max_ind] < temp[i]) max_ind = i; 
	} 
	return max_ind; 

}

int main(){
	num=0;
	for(int i1=0;i1<2;i1++)
		for(int i2=0;i2<2;i2++)
			for(int i3=0;i3<2;i3++)
				for(int i4=0;i4<2;i4++)
					for(int i5=0;i5<2;i5++)
						for(int i6=0;i6<2;i6++)
							for(int i7=0;i7<2;i7++)
								for(int i8=0;i8<2;i8++){
	type[1] = i1; 	type[2] = i2; 	type[3] = i3;  	type[4] = i4;  	type[5] = i5;
	type[6] = i6;   type[7] = i7;   type[8] = i8;  
	init(); 
	int time = 0;
	int pos = 1,next_pos = 0;//С����ʼλ�� 
	bool begin = 0;
	while(time<3600*8){
		/**********��������***********/ 
		for(int j=1;j<9;j++){
			T[j] = L[full][pos][j] + rep[j] + B[j]*type[j]*put_down ;
			if((S[j]-L[full][pos][j]) > 0){
				T[j] += inf; 
			} 
			if(full == 0 && B[j]==0 && type[j]) {
				T[j] += inf;
			}	 
			//�ƶ�T + ������T + ��ϴT + ���費����ǰ��ȥ�ȴ� + ���費�������ȥ���յ�CNC2�� 
		}
		/**********ѡ�����***********/
		next_pos = min_index(T);//ѡ�������С��
		if(T[next_pos] < inf) //����ȥ����ȴ������ҵ�ǰС��״̬�����ȥ����ѡ�� 
		{
			for(int i=1;i<9;i++){
				S[i] -= T[next_pos];//ѡ�������һ������,RGV�޷�������������������һ��ѡ�񾭹�T[next_pos]ʱ�� 
				//��ʱ��SΪ������˵��CNC��������S[i]�����Լӹ���һ����;
				//��SΪ������˵��CNC�����Ѿ��ӹ���ϣ��ȴ�|S[i]|�� 
			} 
			//����CNC1 S = pro1,�� CNC2 S = pro2*full  - put_down*B
			if(type[next_pos] == 0)
				S[next_pos] = pro[0] ;
			else if(type[next_pos] == 1 && full==1) S[next_pos] = pro[1] - B[next_pos]*put_down;
		 	time+=T[next_pos];//ʱ����Ҫ�ӳ�������̵�ʱ�� 
			num+= B[next_pos]*type[next_pos];
		 	pos = next_pos;//С������ 
		 	t_full = full;
		 	full = B[next_pos] * not(type[next_pos]);//��CNC1�а����� 
		 	if(type[next_pos] == 0) B[next_pos] = 1;//CNC1���Ͷ����Ϊ�мӹ���Ʒ 
		 	else B[next_pos] = t_full;  //����CNC1װ�����Ϻ�Ŷ 
		 	begin = 1;
		}
		else{
			time++; 
			for(int i=1;i<9;i++){
				S[i] --;//��ʱ��SΪ������˵��CNC��������S[i]�����Լӹ���һ����;
				//��SΪ������˵��CNC�����Ѿ��ӹ���ϣ��ȴ�|S[i]|�� 
			} 
			begin = 0;
		}	 
	}
	//i1...i8���ֱ�������CNC���������ͣ���ik=1��ʾ��k������Ϊ����2 
//	cout<<i1<<" "<<i2<<" "<<i3<<" "<<i4<<" "<<i5<<" "<<i6<<" "<<i7<<" "<<i8<<"�����£������Ϊ��"<<num<<endl; 
	cout<<num<<endl;
	}
	return 0;
} 
void init(){
	//���ɾ���L 
	for(int k=0;k<2;k++){
		for(int i=1;i<9;i++){
			for(int j=1;j<9;j++){
				//���㲽�� 
				L[k][i][j] = abs((j+1)/2 - (i+1)/2) ;
				if(L[k][i][j] == 1) L[k][i][j] = ons;
				else if(L[k][i][j] == 2) L[k][i][j] = tws;
				else if(L[k][i][j] == 3) L[k][i][j] = ths;
				//����ʱ����ȥ����ͬ���͵Ļ��� 
				if(k==1 && type[i]==type[j]) 	L[k][i][j]=inf;
			}
		}
	}
	full = 0,t_full=0;//0��ʾ��ǰΪ�ճ� 
	for(int i=1;i<9;i++){ 
		S[i] = 0;//�ӹ�ʣ��ʱ��
		B[i] = 0;//�Ƿ�������
		T[i] = 0;//��ǰ״̬��������CNC�ӹ�̨�Ĵ��� 
	} 
	num = 0;//��Ʒ���� 
}
void print(){
	for(int k=0;k<2;k++){
		for(int i=1;i<9;i++){
			for(int j=1;j<9;j++){
				cout<<L[k][i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl<<endl;
	}
}
