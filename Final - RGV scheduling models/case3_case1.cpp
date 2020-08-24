#include<iostream>
#include<ctime>
#include<stdlib.h>
using namespace std;
#define  inf  5000//无穷大
int pro = 560;//加工时间 
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
int S[9] = {0,0,0,0,0,0,0,0,0};//加工剩余时间
bool B[9] = {0,0,0,0,0,0,0,0,0};//是否有孰料
int num = 0;//成品数量 
int T[9] ;//当前状态到达其他CNC加工台的代价 
int endtime[9][10000]={0}; //记录时间
int error[9][1000]={0};
int numm[9]={0}; 
int breakNo[100],breakBeT[100],breakEnT[100],breakPos[100],numBR = 0; //记录故障 
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
	cout<<"当前错误有："<<endl; 
	for(int i=0;i<numBR;i++){ //开始时间，结束时间，机床编号 
		cout<<breakBeT[i]<<" "<<breakEnT[i] <<" "<<breakPos[i] <<endl;
	}
}
//就近原则；
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
double	randnum	, breaktime, runtime;//故障率、 维护时间、 距离机器工作的时间 
void ifbreak(int next_pos){
	randnum = randuni();
 	breaktime = 600 + 600*randuni();
 	runtime = randuni();
	//发生故障 
	if(randnum<=0.01){
		S[next_pos] = breaktime + runtime;//加工剩余时间
		B[next_pos] = 0;//是否有孰料
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
	int pos = 0,next_pos = 0;//小车起始位置 
	bool begin = 0;
	while(time<3600*8){
		/**********评估过程***********/ 
		for(int j=1;j<9;j++){
			T[j] = L[pos][j] + rep[j] + B[j]*put_down ;
			if((S[j]-L[pos][j]) > 0)
				T[j] += (S[j]-L[pos][j])*inf; 
			//移动T + 上下料T + 清洗T + 假设不会提前过去等待 
		}
		/**********选择过程***********/
		next_pos = min_index(T);//选择代价最小的
		if(T[next_pos] < inf) //若过去无需等待，则选择。
		{
			for(int i=1;i<9;i++){
				S[i] -= T[next_pos];//选择后，在这一过程中,RGV无法做其他工作，所以下一次选择经过T[next_pos]时间 
				//此时若S为正，则说明CNC机器经过S[i]秒后可以加工下一任务;
				//若S为负，则说明CNC机器已经加工完毕，等待|S[i]|秒 
			} 
			S[next_pos] = pro -  B[next_pos]*put_down;
		 	time+=T[next_pos];//时间需要延长这个过程的时间 
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
				S[i] --;//此时若S为正，则说明CNC机器经过S[i]秒后可以加工下一任务;
				//若S为负，则说明CNC机器已经加工完毕，等待|S[i]|秒 
			} 
			begin = 0;
		}
	}
	out(endtime);
	 cout<<num<<endl;
	return 0;
} 
