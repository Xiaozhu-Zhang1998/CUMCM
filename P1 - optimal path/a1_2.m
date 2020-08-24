% clear%求非线性多元函数无约束极值
% ff=@(x)sin(x(1))+cos(x(2));
% x0=[0,0];
% [sx,sfval,sexit,soutput]=fminsearch(ff,x0)
clear
clc
f=@(v)500./v+(0.0625*v+1.875)*1.3;
[v,fimn]=fminbnd(f,0,150)
ezplot(f,[0,150])

