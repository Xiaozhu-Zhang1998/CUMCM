function [f,ceq] = nonlinearcondition(x)
    f(1)=x(1)*x(2)-0.0025*4489;%���Ի��߷����Բ���ʽԼ����Ĭ��<=0��
    f(2)=(exp(norminv(x(1),0,1)*0.64927+7.490348))/306.47-1.5;
    f(3)=1-exp(norminv(x(1),0,1)*0.64927+7.490348)/306.47;
    ceq=0;          %�����Ե�ʽԼ��
end
% function [f,ceq] = nonlinearcondition(x)
%     f(1)=x(1)*x(4)+(x(2)-x(1))*x(5)+(x(3)-x(2))*x(6)-0.005*10446;%���Ի��߷����Բ���ʽԼ����Ĭ��<=0��
%     f(2)=(exp(norminv(x(3),0,1)*0.5742+8.4087))/1310.101-1.1;
%     f(3)=1-exp(norminv(x(3),0,1)*0.5742+8.4087)/1310.101;
%     f(4)=x(1)-x(2)+0.015;
%     f(5)=x(2)-x(3)+0.015;
%     f(6)=x(5)-x(4);
%     f(7)=x(6)-x(5);
%     ceq=0;          %�����Ե�ʽԼ��
% end
