clc, clear
a=zeros(11,11);
a(1,2)=11;a(1,3)=27;a(1,4)=11;a(1,5)=12;a(1,6)=29;a(1,7)=26;a(1,8)=42;a(1,9)=22;a(1,10)=36;a(1,11)=34;
a(2,3)=18;a(2,4)=3;a(2,5)=4;a(2,6)=19;a(2,7)=16;a(2,8)=32;a(2,9)=13;a(2,10)=28;a(2,11)=25;
a(3,4)=18;a(3,5)=16;a(3,6)=9;a(3,7)=6;a(3,8)=17;a(3,9)=15;a(3,10)=11;a(3,11)=13;
a(4,5)=3;a(4,6)=19;a(4,7)=16;a(4,8)=32;a(4,9)=15;a(4,10)=27;a(4,11)=25;
a(5,6)=17;a(5,7)=15;a(5,8)=31;a(5,9)=14;a(5,10)=26;a(5,11)=24;
a(6,7)=7;a(6,8)=17;a(6,9)=20;a(6,10)=11;a(6,11)=17;
a(7,8)=17;a(7,9)=14;a(7,10)=14;a(7,11)=12;
a(8,9)=25;a(8,10)=13;a(8,11)=11;
a(9,10)=26;a(9,11)=15;
a(10,11)=18;
% a(1,2)=11;;a(1,4)=11;a(1,5)=12;
% a(2,4)=3;a(2,5)=4;a(2,9)=13;
% a(3,6)=9;a(3,7)=6;a(3,9)=15;a(3,10)=11;a(3,11)=13;
% a(4,5)=3;a(4,9)=15;
% a(5,7)=15;a(5,9)=14;
% a(6,7)=7;a(6,10)=11;
% a(7,9)=14;a(7,10)=14;a(7,11)=12;
% a(8,10)=13;a(8,11)=11;
% a(9,11)=15;
for i=1:11
    for j=1:11
        if(a(i,j)~=0)
            a(i,j)=a(i,j)+1;
        end
    end
end

a=a' ; %matlab工具箱要求数据是下三角矩阵

[i,j,v]=find(a);
c=sparse(a)%构造稀疏矩阵，只储存非零元素及其位置，节约储存空间。用b=full(b)可转化为满阵
[x,y,z]=graphshortestpath(c,1,8,'Directed',false) % Directed是标志图为有向或无向的属性，该图是无向图，对应的属性值为false，或0。 
% h=view(biograph(c,[],'ShowArrows','off','ShowWeights','on')) 