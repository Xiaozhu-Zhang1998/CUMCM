#include<iostream>
#define  inf  5000//�����
using namespace std;
int ons = 23, tws = 41, ths = 59; 
int pro = 580;//�ӹ�ʱ�� 
int rep[9] = {0,30,35,30,35,30,35,30,35}; 
int put_down = 30;
int L[9][9] = {
0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
0 ,0 ,0 ,23 ,23 ,41 ,41 ,59 ,59,
0 ,0 ,0 ,23 ,23 ,41 ,41 ,59 ,59,
0 ,23 ,23 ,0 ,0 ,23 ,23 ,41 ,41,
0 ,23 ,23 ,0 ,0 ,23 ,23 ,41 ,41,
0 ,41 ,41 ,23 ,23 ,0 ,0 ,23 ,23,
0 ,41 ,41 ,23 ,23 ,0 ,0 ,23 ,23,
0 ,59 ,59 ,41 ,41 ,23 ,23 ,0 ,0,
0 ,59 ,59 ,41 ,41 ,23 ,23 ,0 ,0
};
int S[9] = {0,0,0,0,0,0,0,0,0};//�ӹ�ʣ��ʱ��
bool B[9] = {0,0,0,0,0,0,0,0,0};//�Ƿ�������
int endtime[9][10000]={0}; //��¼ʱ��
int numm[9]={0}; 
int num = 0;//��Ʒ���� 
int T[9] ;//��ǰ״̬��������CNC�ӹ�̨�Ĵ��� 
void out(int endtime[9][10000]){
 	for(int ii=1;ii<9;ii++){
		for(int jj=0;jj<1000;jj++){
			if(endtime[ii][jj]!=0){
				cout<<ii<<"  :  "<<endtime[ii][jj]<<" ";
				cout<<endl;
			}		
		}
	}
}
//�ͽ�ԭ��
int min_index(int *T){
	int i=1,num=9;
	int min_ind = i;
	
	for(; i<num; i++ ){
		if(T[i] < T[min_ind]) min_ind = i;
	}
	
	return min_ind;
}
//�ȴ�����ԭ�� 
//int min_index(int *T){
//	int i=1,num=9;
//	int min_T_ind = i;
//	int min_S_ind = i;
//	
//	for(; i<num; i++ ){
//		if(T[i] < T[min_T_ind]) min_T_ind = i;
//		if(S[i] < S[min_S_ind]) min_S_ind = i; 
//	}
//	
//	if(S[min_S_ind] < 0) return min_S_ind; 
//	return min_T_ind; 
//}
//����ԭ�� 
//int min_index(int *T){
//	int temp[9];
//	int max_ind = 1;
//	int num = 9;
//	for(int i=1; i<num; i++ ){	 
//		if(T[i] < inf)//ȷ��S<0,����T��ʱ����� 
//			temp[i] = (-S[i] + T[i]) / T[i];//�ȴ�ʱ��Խ�������ȼ�Խ�ߣ�  ����ԽС�����ȼ�Խ�ߡ�	
//		else temp[i] = -1;
//	} 
//	for(int i=1; i<num; i++ ){
//		if(temp[max_ind] < temp[i]) max_ind = i; 
//	} 
//	return max_ind; 
//
//}
int main(){
	int time = 0;
	int pos = 1,next_pos = 0;//С����ʼλ�� 
	bool begin = 0;
	while(time<3600*8){
		/**********��������***********/ 
		for(int j=1;j<9;j++){
			T[j] = L[pos][j] + rep[j] + B[j]*put_down ;
			if((S[j]-L[pos][j]) > 0)
				T[j] += (S[j]-L[pos][j])*inf; 
			//�ƶ�T + ������T + ��ϴT + ���費����ǰ��ȥ�ȴ� 
		}
		/**********ѡ�����***********/
		next_pos = min_index(T);//ѡ�������С��
		if(T[next_pos] < inf) //����ȥ����ȴ�����ѡ��
		{
			for(int i=1;i<9;i++){
				S[i] -= T[next_pos];//ѡ�������һ������,RGV�޷�������������������һ��ѡ�񾭹�T[next_pos]ʱ�� 
				//��ʱ��SΪ������˵��CNC��������S[i]�����Լӹ���һ����;
				//��SΪ������˵��CNC�����Ѿ��ӹ���ϣ��ȴ�|S[i]|�� 
			} 
			S[next_pos] = pro -  B[next_pos]*put_down;
		 	time+=T[next_pos];//ʱ����Ҫ�ӳ�������̵�ʱ�� 
		 	endtime[next_pos][numm[next_pos]]=time-B[next_pos]*put_down-rep[next_pos];
			numm[next_pos]++;
			num+= B[next_pos];	 
		 	pos = next_pos;
		 	B[next_pos] = 1;
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
	out(endtime);
	 cout<<num<<endl;
	return 0;
} 
