#include<iostream>
#define  inf  5000//无穷大
using namespace std;
int ons = 23, tws = 41, ths = 59; 
int pro = 580;//加工时间 
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
int S[9] = {0,0,0,0,0,0,0,0,0};//加工剩余时间
bool B[9] = {0,0,0,0,0,0,0,0,0};//是否有孰料
int endtime[9][10000]={0}; //记录时间
int numm[9]={0}; 
int num = 0;//成品数量 
int T[9] ;//当前状态到达其他CNC加工台的代价 
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
//就近原则；
int min_index(int *T){
	int i=1,num=9;
	int min_ind = i;
	
	for(; i<num; i++ ){
		if(T[i] < T[min_ind]) min_ind = i;
	}
	
	return min_ind;
}
//等待优先原则 
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
//优先原则 
//int min_index(int *T){
//	int temp[9];
//	int max_ind = 1;
//	int num = 9;
//	for(int i=1; i<num; i++ ){	 
//		if(T[i] < inf)//确保S<0,并且T是时间代价 
//			temp[i] = (-S[i] + T[i]) / T[i];//等待时间越长，优先级越高；  代价越小，优先级越高。	
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
	int pos = 1,next_pos = 0;//小车起始位置 
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
			num+= B[next_pos];	 
		 	pos = next_pos;
		 	B[next_pos] = 1;
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
	out(endtime);
	 cout<<num<<endl;
	return 0;
} 
