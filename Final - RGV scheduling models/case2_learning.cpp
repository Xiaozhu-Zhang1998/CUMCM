#include<iostream>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#define  inf  5000//�����
using namespace std;
int ons = 18, tws = 32, ths = 46; 
int pro[2] = {455,182};//�ӹ�ʱ��,CNC1=455,CNC2=182 
int rep[9] = {0,27,32,27,32,27,32,27,32}; 
bool type[9] = {0, 1, 0, 1, 0, 1, 0, 0, 0 }; //{0, 1,1,1, 2,1,2,1,2 };
int put_down = 25; 
int L[2][9][9] = {0};
int endtime1[9][100]={0}; //��¼ʱ��
int endtime2[9][200]={0};
int numm1[9]={0}; 
int numm2[9]={0};
 

int full = 0,t_full;//0��ʾ��ǰΪ�ճ� 
int S[9] = {10000,0,0,0,0,0,0,0,0};//�ӹ�ʣ��ʱ��
bool B[9] = {0,0,0,0,0,0,0,0,0};//�Ƿ�������
int num = 0;//��Ʒ���� 
int T[9] = {10000,0} ;//��ǰ״̬��������CNC�ӹ�̨�Ĵ��� 

//Ƶ��ͳ�ƾ��� 
int P[9][9]={0};
int max_P[9][9]={//Ƶ������ 
0,0,1,0,0,0,0,0,0,
0,0,14,15,16,0,13,14,1,
0,15,0,14,1,15,0,0,0,
0,0,14,0,14,15,16,14,14,
0,14,0,15,0,14,1,0,0,
0,1,15,0,14,0,14,15,28,
0,14,0,14,0,15,0,1,0,
0,15,0,14,0,14,0,0,1,
0,14,1,15,0,14,0,0,0};
int max_num = 210;//����֮ǰ��ߵĳ�Ʒ���� 
int max_endtime1[9][100]={0}, max_endtime2[9][200]={0}; 
int max_numm1[9]={0}, max_numm2[9]={0};
void init1();//��ʼ�� L����
void init2();//��ԭ�������� 
void print(); 
void out(int);//���� 
/////����ԭ�� 
double randuni(){
	return rand()*1.0/(RAND_MAX*1.0);
}
int min_index(int *T,int pos){
	int temp[9]={0}; 
	int max_ind = 1;
	int n = 0;//��ʾ��Ƶ�� 
	double rand, K=0;
	for(int i=1; i<9; i++ ){	 
		if(T[i] < inf)//ȷ��S<0,����T��ʱ����� 
		{
			if(max_P[pos][i] < 0 ) max_P[pos][i] = 0;
			temp[i] = max_P[pos][i];//�ȴ�ʱ��Խ�������ȼ�Խ�ߣ�  ����ԽС�����ȼ�Խ�ߡ�
			if(max_P[pos][i] == 0) temp[i]+=5;	
			n+=temp[i];
		}
	} 
	rand = randuni();
	K=0;
	for(int i=1; i<9; i++ ){
		K = K+ 1.0*temp[i]/n;
		if(K>rand) return i;
	}
	return 1; 
}

int main(){
	init1(); 
	print(); 
	srand(time(NULL));
int repeat = 100000;
while(repeat--){
	int time = 0;
	int pos = 1,next_pos = 0;//С����ʼλ�� 
	bool begin = 0;
	init2();
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
		}
		/**********ѡ�����***********/
		next_pos = min_index(T,pos);//ѡ�������С��
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
			if(type[next_pos] == 0){
					endtime1[next_pos][numm1[next_pos]]=time - rep[next_pos];
					numm1[next_pos]++;
			}
			if(type[next_pos] == 1&&full==1){
					endtime2[next_pos][numm2[next_pos]]=pos;
					numm2[next_pos]++;
					endtime2[next_pos][numm2[next_pos]]=time-B[next_pos]*put_down-rep[next_pos];
					numm2[next_pos]++;	
			}
			else if(type[next_pos] == 1&&full==0){
					endtime2[next_pos][numm2[next_pos]]=-1;
					numm2[next_pos]++;
					endtime2[next_pos][numm2[next_pos]]=pos;
					numm2[next_pos]++;
					endtime2[next_pos][numm2[next_pos]]=time-B[next_pos]*put_down-rep[next_pos];
					numm2[next_pos]++;
			}
			P[pos][next_pos]++;//���ߴ���
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
	if(num>max_num){
		out(-1); 
	 	print();
	}
	else if(num<max_num){
		out(max_num-num);
	}
}
print();
	return 0;
} 
void init1(){
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
}
void init2(){
	full = 0,t_full=0;//0��ʾ��ǰΪ�ճ� 
	for(int i=1;i<9;i++){ 
		S[i] = 0;//�ӹ�ʣ��ʱ��
		B[i] = 0;//�Ƿ�������
		T[i] = 0;//��ǰ״̬��������CNC�ӹ�̨�Ĵ��� 
		numm1[i] = 0; //������������ 
		numm2[i] = 0; 
	} 
	num = 0;//��Ʒ���� 
	for(int i=1;i<9;i++)
		for(int j=1;j<9;j++)
			P[i][j]=0; 
}
void print(){
	cout<<"*************MAX��"<<max_num<<endl; 
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)
			cout<<max_P[i][j]<<","; 
		cout<<endl;
	}
	for(int ii=1;ii<9;ii++){
		for(int jj=0;jj<100;jj++){
			if(endtime1[ii][jj]!=0){
			
				cout<<ii<<"  :  "<<endtime1[ii][jj]<<" ";
				cout<<endl;
			}		
		}
	}	
	for(int ii=1;ii<9;ii++){
		for(int jj=0;jj<200;jj+=2){
			if(endtime2[ii][jj]!=0&&endtime2[ii][jj]!=-1){
			
				cout<<ii<<"  :  "<<endtime2[ii][jj]<<" "<<endtime2[ii][jj+1]<<" ";
				cout<<endl;
			}
			else if(endtime2[ii][jj]==-1){
				
				cout<<ii<<"  :  "<<endtime2[ii][jj]<<" "<<endtime2[ii][jj+1]<<" "<<endtime2[ii][jj+2];
				jj++; 
				cout<<endl;
			}		
		}
	}
}
void out(int worse){//���excel�н�� 
	if(worse == -1){
			max_num = num;	
 			for(int ii=1;ii<9;ii++){
				for(int jj=0;jj<100;jj++){
					max_endtime1[ii][jj] =  endtime1[ii][jj];
				}
			}
			for(int ii=1;ii<9;ii++){
				for(int jj=0;jj<200;jj+=1){
					max_endtime2[ii][jj] =  endtime2[ii][jj];
				}
			}
			for(int i=1;i<9;i++){ 
				max_numm1[i] = numm1[i];
				max_numm2[i] = numm2[i]; 
			} 
			for(int i=1;i<9;i++)
			{
				for(int j=1;j<9;j++){
					max_P[i][j] = 0.8*P[i][j] + 0.5*max_P[i][j];
				}
			}
	}
	
}
