#include<iostream>
#include<sstream>
using namespace std;
int ship[11],mi[11]; 
int AtoF=36, BtoC=27, CtoD=26, CtoB=27, DtoF=27,
DtoH=43, EtoI=14, EtoG=15, FtoI=22, FtoJ=11,
FtoK=20, GtoE=15, GtoC=6, HtoB=41, HtoG=24,
ItoK=15, JtoA=43, KtoA=41, KtoD=31, KtoG=12;


int ItoB_=13,DtoE_=3,ItoH_=25,BtoC_=18;
void fun(int t){
	t-=1;
	
	if(t<=KtoA)
		ship[0]-=2;
	else if(t<=JtoA) 
		ship[0]-=1;
	else;
	
	if(t<=CtoB)
		ship[1]-=2;
	else if(t<=HtoB) 
		ship[1]-=1;
	else ship[1]++;
	
	if(t<=GtoC)
		ship[2]-=4;
	else if(t<=BtoC) 
		ship[2]-=3;
	else ship[2]-=1;
	
	if(t<=CtoD)
		ship[3]-=4;
	else if(t<=KtoD) 
		ship[3]-=1;
	else ship[3]++;
	
	if(t<=GtoE)
		ship[4]-=3;
	else ship[4]--;
	
	if(t<=DtoF)
		ship[5]-=4;
	else if(t<=AtoF) 
		ship[5]-=2;
	else;
	
	if(t<=KtoG)
		ship[6]-=3;
	else if(t<=EtoG) 
		ship[6]-=2;
	else if(t<=HtoG)
		ship[6]--;
	else ;
	
	if(t<=DtoH)
		ship[7]-=3; 	
	else ship[7]--;
	
	if(t<=EtoI)
		ship[8]-=2;
	else if(t<=FtoI)
		ship[8]=ship[8];
	else ship[8]++;
	
	if(t<=FtoJ)
		ship[9]--;
	else;
	
	if(t<=ItoK)
		ship[10]-=4;
	else if(t<=FtoK) 
		ship[10]-=2;
	else ;


}
void diaodu(int t){
	if(t>=24&&t<30) {  //I->B
		ship[8]--;
	} 
	if(t>=(24+ItoB_) &&t<(30+ItoB_))
		ship[1]++;
	
	if(t>=33&&t<40){   //D->E
		ship[3]--;
	} 
	if(t>=(33+DtoE_)&&t<(40+DtoE_)){   //D->E
		ship[4]++;
	} 
	
	if(t>=30){   //I->H
		ship[8]--;
	} 
	if(t>=(30+ItoH_)){   //I->H
		ship[7]++;
	}  
	
	if(t>=40){   //D->E
		ship[3]--;
	} 
	if(t>=(40+DtoE_)){   //D->E
		ship[4]++;
	}  
	
	if(t>=43){   //B->C
		ship[1]--;
	} 
	if(t>=(43+BtoC_)){   //B->C
		ship[2]++;
	}  
}
void finmin(){
	for(int j=0;j<11;j++){
		if(mi[j]>ship[j])
			mi[j]=ship[j];
	}
			
}
int main(){
	for(int i=0;i<100;i++)
	{
//		for(int j=0;j<11;j++)
//			ship[j]=0;
		fun(i);
		diaodu(i);
		finmin(); 
		for(int j=0;j<11;j++)
			cout<<ship[j]<<" ";
		cout<<endl;
	}
	
	int n=0;
	for(int j=0;j<11;j++){
		char t = 'A'+j; 
		cout<<t<<"最少船数为: "<<-mi[j]<<endl;
	}
	return 0;
} 
