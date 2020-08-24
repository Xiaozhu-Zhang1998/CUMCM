#include<iostream>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#define  inf  5000//无穷大
using namespace std;
int ons = 20, tws = 33, ths = 46; 
int pro[2] = {400,378};//加工时间,CNC1=455,CNC2=182 
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
class item{//运送的物料类 
	public: //CNC1编号，进入CNC1时间，出CNC1时间，进CNC2时间，出CNC2时间 
		int xuhao,CNC1,intime1,outtime1,CNC2,intime2,outtime2;
};
class error_{//错误类 
	public:
		int xuhao,NoCNC;//错误的物料序号，当前的CNC编号 
		int occ_time,fix_time;//错误开始时间，修复时间 
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
				//计算步长 
				L[k][i][j] = abs((j+1)/2 - (i+1)/2) ;
				if(L[k][i][j] == 1) L[k][i][j] = ons;
				else if(L[k][i][j] == 2) L[k][i][j] = tws;
				else if(L[k][i][j] == 3) L[k][i][j] = ths;
				//满载时不能去到相同类型的机器 
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
	cout<<"物料："<<endl; 
	for(int i=1;i<numit;i++){
		cout<<i<<","<<it[i].CNC1<<","<<it[i].intime1<<",";
		if(it[i].outtime1>0){
			cout<<it[i].outtime1<<","<<it[i].CNC2<<","<<it[i].intime2<<",";
			if(it[i].outtime2>0)
				cout<<it[i].outtime2;
		}
		cout<<endl;
	}
	cout<<"这八小时出现的故障有："<<endl; 
	for(int i=0;i<error_times;i++){
		cout<<error[i].xuhao<<" "<<error[i].NoCNC<<" "<<error[i].occ_time<<" "<<error[i].fix_time<<endl; 
	}
}
int full = 0,t_full;//0表示当前为空车 
int S[9] = {10000,0,0,0,0,0,0,0,0};//加工剩余时间
bool B[9] = {0,0,0,0,0,0,0,0,0};//是否有孰料
int num = 0;//成品数量 
int T[9] = {10000,0} ;//当前状态到达其他CNC加工台的代价 
//就近原则；
int min_index(int *T){
	int i=1,num=9;
	int min_ind = i;
	for(; i<num; i++ ){
		if(T[i] < T[min_ind]) min_ind = i;
	}	
	return min_ind;
}
void display(){
	cout<<"编号：";
	for(int i=1;i<9;i++)
	{
		cout<<hold_CNC[i]<<" ";
	}
	cout<<endl<<" 船"<<hold_RGV<<" 任务序号：";
	cout<<numit<<endl;
} 
void ifbreak(int next_pos,int time){	
	randnum = randuni();
 	breaktime = 600 + 600*randuni();
 	runtime = randuni()*pro[next_pos]; 	
	//发生故障 
	if(randnum<0.01){
		S[next_pos] = runtime+breaktime;//加工剩余时间
		B[next_pos] = 0;//是否有孰料
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
	int pos = 1,next_pos = 0;//小车起始位置 
	bool begin = 0;
	while(time<3600*8){
		/**********评估过程***********/ 
		for(int j=1;j<9;j++){
			T[j] = L[full][pos][j] + rep[j] + B[j]*type[j]*put_down ;
			if((S[j]-L[full][pos][j]) > 0){
				T[j] += inf; 
			}
			if(full == 0 && B[j]==0 && type[j]) {
				T[j] += inf;
			}
			//移动T + 上下料T + 清洗T + 假设不会提前过去等待 + 假设不会空着手去到空的CNC2中 
		}
		/**********选择过程***********/
		next_pos = min_index(T);//选择代价最小的
		if(T[next_pos] < inf) //若过去无需等待，并且当前小车状态允许过去，则选择 
		{
			for(int i=1;i<9;i++){
				S[i] -= T[next_pos];//选择后，在这一过程中,RGV无法做其他工作，所以下一次选择经过T[next_pos]时间 
			} 
			//若是CNC1 S = pro1,而 CNC2 S = pro2*full  - put_down*B
			if(type[next_pos] == 0){
				S[next_pos] = pro[0] ;		
			}
			else if(type[next_pos] == 1 && full==1) S[next_pos] = pro[1] - B[next_pos]*put_down;
		 	time+=T[next_pos];//时间需要延长这个过程的时间 
		 	cout<<time- type[next_pos]*B[next_pos]*put_down<<" : "<<pos<<"->"<<next_pos<<endl; 
		 	cout<<"now:"<<time<<" : " ;
		 	for(int j=1;j<9;j++) cout<<S[j] <<" ";
			cout<<endl<<"B: "; 	
			//交换；
			if(full == 1){
				//车上的清洗掉 
				if(B[next_pos])
					it[ hold_CNC[next_pos] ].outtime2 = time - type[next_pos]*B[next_pos]*put_down  - rep[next_pos];
				hold_CNC[next_pos] = hold_RGV;
				it[ hold_RGV ].intime2 = time - type[next_pos]*B[next_pos]*put_down  - rep[next_pos];
				it[ hold_RGV ].CNC2 = next_pos;
				hold_RGV = 0;
			} 
			else{
				//在CNN1 
				if(type[next_pos] == 0){
					if(B[next_pos] == 1){
						hold_RGV = hold_CNC[next_pos];
						hold_CNC[next_pos] = 0;
						it[hold_RGV].outtime1 = time - rep[next_pos];
					}		
					//不管内部有无半熟品，都会产生新的:
					numit++;
					hold_CNC[next_pos] = numit;
					it[numit].CNC1 = next_pos;
					it[numit].intime1 = time - rep[next_pos];	
				}
				else{
					//对于CNC2，仅仅拿下来做清洗 
					it[ hold_CNC[next_pos] ].outtime2 = time - type[next_pos]*B[next_pos]*put_down  - rep[next_pos];
					hold_CNC[next_pos] = 0;	 
				} 
			}
			display();
			num+= B[next_pos]*type[next_pos];
		 	pos = next_pos;//小车到达 
		 	t_full = full;
		 	full = B[next_pos] * not(type[next_pos]);//若CNC1有半孰料 
		 	if(type[next_pos] == 0) B[next_pos] = 1;//CNC1类型都会变为有加工产品 
		 	else B[next_pos] = t_full;  //经过CNC1装半数料后哦 
		 	for(int j=1;j<9;j++) cout<<B[j] <<" ";
			cout<<endl;
		 	ifbreak(next_pos,time); 
		 	begin = 1;
		 	cout<<full<<endl;
		}
		else{
			time++; 
			for(int i=1;i<9;i++){
				S[i] --;//此时若S为正，则说明CNC机器经过S[i]秒后可以加工下一任务;
				//若S为负，则说明CNC机器已经加工完毕，等待|S[i]|秒 	
			} 
			begin = 0;
		}
	}
	 outcome(); 
	return 0;
} 
