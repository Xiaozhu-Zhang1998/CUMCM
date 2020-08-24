#include<iostream>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#define  inf  5000//�����
using namespace std;
int ons = 20, tws = 33, ths = 46; 
int pro[2] = {400,378};//�ӹ�ʱ��,CNC1=455,CNC2=182 
int rep[9] = {0,28,31,28,31,28,31,28,31}; 
bool type[9] = {0,0,1,0,1,0,1,0,1};
int put_down = 25; 
int L[2][9][9] = {0};
double randnum=0;
double breaktime = 0; 
double runtime = 0;
double randuni(){
	return rand()*1.0/(RAND_MAX*1.0);
}
class item{//���͵������� 
	public: //CNC1��ţ�����CNC1ʱ�䣬��CNC1ʱ�䣬��CNC2ʱ�䣬��CNC2ʱ�� 
		int xuhao,CNC1,intime1,outtime1,CNC2,intime2,outtime2;
};
class error_{//������ 
	public:
		int xuhao,NoCNC;//�����������ţ���ǰ��CNC��� 
		int occ_time,fix_time;//����ʼʱ�䣬�޸�ʱ�� 
};
error_ error[20];
int error_times = 0;
item it[500];
int hold_CNC[9] = {0};
int hold_RGV;
int numit = 0;
void init(){
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
void outcome(){
	cout<<"���ϣ�"<<endl; 
	for(int i=1;i<numit;i++){
		cout<<i<<","<<it[i].CNC1<<","<<it[i].intime1<<",";
		if(it[i].outtime1>0){
			cout<<it[i].outtime1<<","<<it[i].CNC2<<","<<it[i].intime2<<",";
			if(it[i].outtime2>0)
				cout<<it[i].outtime2;
		}
		cout<<endl;
	}
	cout<<"���Сʱ���ֵĹ����У�"<<endl; 
	for(int i=0;i<error_times;i++){
		cout<<error[i].xuhao<<" "<<error[i].NoCNC<<" "<<error[i].occ_time<<" "<<error[i].fix_time<<endl; 
	}
}
int full = 0,t_full;//0��ʾ��ǰΪ�ճ� 
int S[9] = {10000,0,0,0,0,0,0,0,0};//�ӹ�ʣ��ʱ��
bool B[9] = {0,0,0,0,0,0,0,0,0};//�Ƿ�������
int num = 0;//��Ʒ���� 
int T[9] = {10000,0} ;//��ǰ״̬��������CNC�ӹ�̨�Ĵ��� 
//�ͽ�ԭ��
int min_index(int *T){
	int i=1,num=9;
	int min_ind = i;
	for(; i<num; i++ ){
		if(T[i] < T[min_ind]) min_ind = i;
	}	
	return min_ind;
}
void display(){
	cout<<"��ţ�";
	for(int i=1;i<9;i++)
	{
		cout<<hold_CNC[i]<<" ";
	}
	cout<<endl<<" ��"<<hold_RGV<<" ������ţ�";
	cout<<numit<<endl;
} 
void ifbreak(int next_pos,int time){	
	randnum = randuni();
 	breaktime = 600 + 600*randuni();
 	runtime = randuni()*pro[next_pos]; 	
	//�������� 
	if(randnum<0.01){
		S[next_pos] = runtime+breaktime;//�ӹ�ʣ��ʱ��
		B[next_pos] = 0;//�Ƿ�������
		cout<<next_pos<<" break!!"<<hold_CNC[next_pos] <<endl; 
		cout<<"now:"<<time<<" : " ;
		for(int j=1;j<9;j++) cout<<S[j] <<" ";
		cout<<endl<<"B: "; 
		for(int j=1;j<9;j++) cout<<B[j] <<" ";
		cout<<endl; 
		error[error_times].xuhao = hold_CNC[next_pos];
		error[error_times].NoCNC = next_pos;
		error[error_times].occ_time = runtime + time;
		error[error_times++].fix_time = time+runtime +breaktime;
	}
} 
int main(){
	srand(time(NULL));
	init(); 
	print(); 
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
			} 
			//����CNC1 S = pro1,�� CNC2 S = pro2*full  - put_down*B
			if(type[next_pos] == 0){
				S[next_pos] = pro[0] ;		
			}
			else if(type[next_pos] == 1 && full==1) S[next_pos] = pro[1] - B[next_pos]*put_down;
		 	time+=T[next_pos];//ʱ����Ҫ�ӳ�������̵�ʱ�� 
		 	cout<<time- type[next_pos]*B[next_pos]*put_down<<" : "<<pos<<"->"<<next_pos<<endl; 
		 	cout<<"now:"<<time<<" : " ;
		 	for(int j=1;j<9;j++) cout<<S[j] <<" ";
			cout<<endl<<"B: "; 	
			//������
			if(full == 1){
				//���ϵ���ϴ�� 
				if(B[next_pos])
					it[ hold_CNC[next_pos] ].outtime2 = time - type[next_pos]*B[next_pos]*put_down  - rep[next_pos];
				hold_CNC[next_pos] = hold_RGV;
				it[ hold_RGV ].intime2 = time - type[next_pos]*B[next_pos]*put_down  - rep[next_pos];
				it[ hold_RGV ].CNC2 = next_pos;
				hold_RGV = 0;
			} 
			else{
				//��CNN1 
				if(type[next_pos] == 0){
					if(B[next_pos] == 1){
						hold_RGV = hold_CNC[next_pos];
						hold_CNC[next_pos] = 0;
						it[hold_RGV].outtime1 = time - rep[next_pos];
					}		
					//�����ڲ����ް���Ʒ����������µ�:
					numit++;
					hold_CNC[next_pos] = numit;
					it[numit].CNC1 = next_pos;
					it[numit].intime1 = time - rep[next_pos];	
				}
				else{
					//����CNC2����������������ϴ 
					it[ hold_CNC[next_pos] ].outtime2 = time - type[next_pos]*B[next_pos]*put_down  - rep[next_pos];
					hold_CNC[next_pos] = 0;	 
				} 
			}
			display();
			num+= B[next_pos]*type[next_pos];
		 	pos = next_pos;//С������ 
		 	t_full = full;
		 	full = B[next_pos] * not(type[next_pos]);//��CNC1�а����� 
		 	if(type[next_pos] == 0) B[next_pos] = 1;//CNC1���Ͷ����Ϊ�мӹ���Ʒ 
		 	else B[next_pos] = t_full;  //����CNC1װ�����Ϻ�Ŷ 
		 	for(int j=1;j<9;j++) cout<<B[j] <<" ";
			cout<<endl;
		 	ifbreak(next_pos,time); 
		 	begin = 1;
		 	cout<<full<<endl;
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
	 outcome(); 
	return 0;
} 
