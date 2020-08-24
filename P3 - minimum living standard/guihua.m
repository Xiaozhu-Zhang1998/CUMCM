clc;
clear;
% options= optimset('MaxIter',10000);
[x,fval]=fmincon('fun',[0;1000],[],[],[],[],[0;0],[],'nonlinearcondition')
x=vpa(x,9)
