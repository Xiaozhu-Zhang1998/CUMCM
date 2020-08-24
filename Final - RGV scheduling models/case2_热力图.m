
%���ؿ���ѧϰ�������ֲ���ͼ
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


%����һ�ĵ�һ������͵ڶ���������ȹ켣ͼ
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
xlabel('��ǰʱ��t');
ylabel('RGV����λ��');
title('case1��RGV���ȹ켣')

subplot(212)
plot(t,wei,'-^')
axis([0 5000 0.5 4.5])
xlabel('��ǰʱ��t');
ylabel('RGV����λ��');
title('case2��RGV���ȹ켣')