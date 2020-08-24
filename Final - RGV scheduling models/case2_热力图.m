
%蒙特卡洛学习经验矩阵分布热图
clc;
clear;
data = [0,40,0,31,0,0,0,0;
        30,0,40,0,2,0,1,0;
        0,0,0,0,0,13,0,60;
        39,0,31,0,1,0,0,0;
        0,30,0,39,0,1,0,0;
        1,0,1,0,56,0,12,0;
        0,2,0,1,0,56,0,12;
        0,0,0,0,12,0,59,0];
xvalues = {'CNC1','CNC2','CNC3','CNC4','CNC5','CNC6','CNC7','CNC8'};
yvalues = {'CNC1','CNC2','CNC3','CNC4','CNC5','CNC6','CNC7','CNC8'};
yvalues=yvalues'
HeatMap(data,'Colormap',' redbluecmap','ColumnLabels',yvalues,'RowLabels',xvalues);
colorbar


%任务一的第一种情况和第二种情况调度轨迹图
RGV=xlsread('data.xlsx');
RGV1=xlsread('dataa.xlsx')
%RGV=RGV';
a=RGV(:,1)
b=RGV(:,2);
wei=floor((RGV1(:,1)+1)./2);
t=RGV1(:,2);

subplot(211)
plot(b,a,'-^')
axis([0 10000 0.5 4.5])
xlabel('当前时间t');
ylabel('RGV所在位置');
title('case1的RGV调度轨迹')

subplot(212)
plot(t,wei,'-^')
axis([0 5000 0.5 4.5])
xlabel('当前时间t');
ylabel('RGV所在位置');
title('case2的RGV调度轨迹')