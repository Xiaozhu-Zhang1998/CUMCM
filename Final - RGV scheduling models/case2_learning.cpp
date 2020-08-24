#include<iostream>
#include<cmath>
#include<ctime>
#include<stdlib.h>
#define  inf  5000//无穷大
using namespace std;
int ons = 18, tws = 32, ths = 46; 
int pro[2] = {455,182};//加工时间,CNC1=455,CNC2=182 
int rep[9] = {0,27,32,27,32,27,32,27,32}; 
bool type[9] = {0, 1, 0, 1, 0, 1, 0, 0, 0 }; //{0, 1,1,1, 2,1,2,1,2 };
int put_down = 25; 
int L[2][9][9] = {0};
int endtime1[9][100]={0}; //记录时间
int endtime2[9][200]={0};
int numm1[9]={0}; 
int numm2[9]={0};
 

int full = 0,t_full;//0表示当前为空车 
int S[9] = {10000,0,0,0,0,0,0,0,0};//加工剩余时间
bool B[9] = {0,0,0,0,0,0,0,0,0};//是否有孰料
int num = 0;//成品数量 
int T[9] = {10000,0} ;//当前状态到达其他CNC加工台的代价 

//频数统计矩阵 
int P[9][9]={0};
int max_P[9][9]={//频数矩阵 
0,0,1,0,0,0,0,0,0,
0,0,14,15,16,0,13,14,1,
0,15,0,14,1,15,0,0,0,
0,0,14,0,14,15,16,14,14,
0,14,0,15,0,14,1,0,0,
0,1,15,0,14,0,14,15,28,
0,14,0,14,0,15,0,1,0,
0,15,0,14,0,14,0,0,1,
0,14,1,15,0,14,0,0,0};
int max_num = 210;//储存之前最高的成品数量 
int max_endtime1[9][100]={0}, max_endtime2[9][200]={0}; 
int max_numm1[9]={0}, max_numm2[9]={0};
void init1();//初始化 L矩阵
void init2();//还原各个数据 
void print(); 
void out(int);//储存 
/////优先原则 
double randuni(){
	return rand()*1.0/(RAND_MAX*1.0);
}
int min_index(int *T,int pos){
	int temp[9]={0}; 
	int max_ind = 1;
	int n = 0;//表示总频数 
	double rand, K=0;
	for(int i=1; i<9; i++ ){	 
		if(T[i] < inf)//确保S<0,并且T是时间代价 
		{
			if(max_P[pos][i] < 0 ) max_P[pos][i] = 0;
			temp[i] = max_P[pos][i];//等待时间越长，优先级越高；  代价越小，优先级越高。
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
	int pos = 1,next_pos = 0;//小车起始位置 
	bool begin = 0;
	init2();
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
		}
		/**********选择过程***********/
		next_pos = min_index(T,pos);//选择代价最小的
		if(T[next_pos] < inf) //若过去无需等待，并且当前小车状态允许过去，则选择 
		{
			for(int i=1;i<9;i++){
				S[i] -= T[next_pos];//选择后，在这一过程中,RGV无法做其他工作，所以下一次选择经过T[next_pos]时间 
				//此时若S为正，则说明CNC机器经过S[i]秒后可以加工下一任务;
				//若S为负，则说明CNC机器已经加工完毕，等待|S[i]|秒 
			} 
			//若是CNC1 S = pro1,而 CNC2 S = pro2*full  - put_down*B
			if(type[next_pos] == 0)
				S[next_pos] = pro[0] ;
			else if(type[next_pos] == 1 && full==1) S[next_pos] = pro[1] - B[next_pos]*put_down;
		 	time+=T[next_pos];//时间需要延长这个过程的时间 
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
			P[pos][next_pos]++;//将边存入
			num+= B[next_pos]*type[next_pos];
		 	pos = next_pos;//小车到达 
		 	t_full = full;
		 	full = B[next_pos] * not(type[next_pos]);//若CNC1有半孰料 
		 	if(type[next_pos] == 0) B[next_pos] = 1;//CNC1类型都会变为有加工产品 
		 	else B[next_pos] = t_full;  //经过CNC1装半数料后哦 
		 	begin = 1;
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
	//生成矩阵L 
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
void init2(){
	full = 0,t_full=0;//0表示当前为空车 
	for(int i=1;i<9;i++){ 
		S[i] = 0;//加工剩余时间
		B[i] = 0;//是否有孰料
		T[i] = 0;//当前状态到达其他CNC加工台的代价 
		numm1[i] = 0; //将任务量置零 
		numm2[i] = 0; 
	} 
	num = 0;//成品数量 
	for(int i=1;i<9;i++)
		for(int j=1;j<9;j++)
			P[i][j]=0; 
}
void print(){
	cout<<"*************MAX："<<max_num<<endl; 
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
void out(int worse){//输出excel中结果 
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
