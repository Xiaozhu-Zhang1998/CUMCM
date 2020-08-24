#include<iostream>
#include<cmath>
#define  inf  5000//无穷大
using namespace std;
//对于不同情况只需要修改以下初值： 
int ons = 20, tws = 33, ths = 46; 
int pro[2] = {400,378};//加工时间,CNC1=455,CNC2=182 
int rep[9] = {0,28,31,28,31,28,31,28,31}; 
bool type[9]; 
int put_down = 25; 
/*
int ons = 18, tws = 32, ths = 46; 
int pro[2] = {455,182};//加工时间,CNC1=455,CNC2=182 
int rep[9] = {0,27,32,27,32,27,32,27,32}; 
bool type[9]; 
int put_down = 25;*/ 
int L[2][9][9] = {0};
int full = 0,t_full;//0表示当前为空车 
int S[9] = {10000,0,0,0,0,0,0,0,0};//加工剩余时间
bool B[9] = {0,0,0,0,0,0,0,0,0};//是否有孰料
int num = 0;//成品数量 
int T[9] = {10000,0} ;//当前状态到达其他CNC加工台的代价 
void init();
void print(); 
/*就近原则；*/
//int min_index(int *T){
//	int i=1,num=9;
//	int min_ind = i;
//	for(; i<num; i++ ){
//		if(T[i] < T[min_ind]) min_ind = i;
//	}
//	return min_ind;
//}


//FIFO原则 
//int min_index(int *T){
//	int i=1,num=9;
//	int min_T_ind = 0;
//	int min_S_ind = 0;
//	bool temp = 0; //temp = 1，表示可以作为下一次选择 
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
//			//if(full == 1 && type[i] == 1  || full == 0)  //若车上有半熟料，则必须去CNC2，空车则去等的最久的CNC1 或 满CNC2
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

////HRRN原则 
int min_index(int *T){
	int temp[9]; 
	int max_ind = 1;
	int num = 9;
	for(int i=1; i<num; i++ ){
		 
		if(T[i] < inf)//确保S<0,并且T是时间代价 
			temp[i] = (-S[i] + T[i]) / T[i];//等待时间越长，优先级越高；  代价越小，优先级越高。	
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
				//此时若S为正，则说明CNC机器经过S[i]秒后可以加工下一任务;
				//若S为负，则说明CNC机器已经加工完毕，等待|S[i]|秒 
			} 
			//若是CNC1 S = pro1,而 CNC2 S = pro2*full  - put_down*B
			if(type[next_pos] == 0)
				S[next_pos] = pro[0] ;
			else if(type[next_pos] == 1 && full==1) S[next_pos] = pro[1] - B[next_pos]*put_down;
		 	time+=T[next_pos];//时间需要延长这个过程的时间 
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
	//i1...i8，分别代表各个CNC机器的类型，若ik=1表示第k个机器为类型2 
//	cout<<i1<<" "<<i2<<" "<<i3<<" "<<i4<<" "<<i5<<" "<<i6<<" "<<i7<<" "<<i8<<"布局下，最大数为："<<num<<endl; 
	cout<<num<<endl;
	}
	return 0;
} 
void init(){
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
	full = 0,t_full=0;//0表示当前为空车 
	for(int i=1;i<9;i++){ 
		S[i] = 0;//加工剩余时间
		B[i] = 0;//是否有孰料
		T[i] = 0;//当前状态到达其他CNC加工台的代价 
	} 
	num = 0;//成品数量 
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
