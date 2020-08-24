#include<iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;
#define  inf  5000//�����
int pro = 560;//�ӹ�ʱ�� 
int rep[9] = {0,28,31,28,31,28,31,28,31}; 
int put_down = 25;
int L[9][9] = {
0, 0, 0, 0,   0,  0,  0,  0,  0, 
0, 0, 0, 20, 20, 33, 33, 46, 46,
0, 0, 0, 20, 20, 33, 33, 46, 46,
0, 20, 20, 0, 0, 20, 20, 33, 33,
0, 20, 20, 0, 0, 20, 20, 33, 33,
0, 33, 33, 20, 20, 0, 0, 20, 20,
0, 33, 33, 20, 20, 0, 0, 20, 20,
0, 46, 46, 33, 33, 20, 20, 0, 0,
0, 46, 46, 33, 33, 20, 20, 0, 0};
int S[9] = {0,0,0,0,0,0,0,0,0};//�ӹ�ʣ��ʱ��
bool B[9] = {0,0,0,0,0,0,0,0,0};//�Ƿ�������
int num = 0;//��Ʒ���� 
int T[9] ;//��ǰ״̬��������CNC�ӹ�̨�Ĵ��� 
int endtime[9][10000]={0}; //��¼ʱ��
int error[9][1000]={0};
int numm[9]={0}; 
int breakNo[100],breakBeT[100],breakEnT[100],breakPos[100],numBR = 0; //��¼���� 
void out(int endtime[9][10000]){
	for(int ii=1;ii<8;ii++){
		numm[1]+=numm[ii+1];
	}
	cout<<"ALL"<<numm[1]<<endl<<endl;
 	for(int ii=1;ii<9;ii++){
		for(int jj=0;jj<1000;jj++){
			if(endtime[ii][jj]!=0){
				cout<<ii<<" "<<endtime[ii][jj]<<" "<<endtime[ii][jj+1]<<" error? "<<error[ii][jj];
				cout<<endl;
			}		
		}
	}
	cout<<"��ǰ�����У�"<<endl; 
	for(int i=0;i<numBR;i++){ //��ʼʱ�䣬����ʱ�䣬������� 
		cout<<breakBeT[i]<<" "<<breakEnT[i] <<" "<<breakPos[i] <<endl;
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
double randuni(){
	return rand()*1.0/(RAND_MAX*1.0);
}
double	randnum	, breaktime, runtime;//�����ʡ� ά��ʱ�䡢 �������������ʱ�� 
void ifbreak(int next_pos){
	randnum = randuni();
 	breaktime = 600 + 600*randuni();
 	runtime = randuni();
	//�������� 
	if(randnum<=0.01){
		S[next_pos] = breaktime + runtime;//�ӹ�ʣ��ʱ��
		B[next_pos] = 0;//�Ƿ�������
		cout<<next_pos<<" break!!"<<endl; 
		cout<<"now:"<<time<<" : " ; 
		for(int j=1;j<9;j++) cout<<S[j] <<" ";
		cout<<endl<<"B: "; 
		for(int j=1;j<9;j++) cout<<B[j] <<" ";
		cout<<endl; 
	}
} 
int main(){
	srand(time(NULL));
	int time = 0;
	int pos = 0,next_pos = 0;//С����ʼλ�� 
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
		 	cout<<time-B[next_pos]*put_down<<" : "<<pos<<"->"<<next_pos<<endl; 
		 	cout<<"now:"<<time<<" S : " ;
		 	for(int j=1;j<9;j++) cout<<S[j] <<" ";
			cout<<endl; 
			num+= B[next_pos];
		 	pos = next_pos;
		 	B[next_pos] = 1;
		 	ifbreak(next_pos);
			if(B[next_pos] == 0){
				error[next_pos][numm[next_pos]] = 1;
				breakBeT[numBR] = time;
				breakEnT[numBR] = time+breaktime;
				breakPos[numBR] = next_pos;
				numBR++; 
			}
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
