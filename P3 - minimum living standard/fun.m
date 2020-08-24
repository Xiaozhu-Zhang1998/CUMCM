% function f =fun(x)
%     f=-0.9*(exp(norminv(x(3),0,1)*0.5742+8.4087)+x(6)+exp(norminv(x(2),0,1)*0.5742+8.4087)+x(5)+exp(norminv(x(1),0,1)*0.5742+8.4087)+x(4))/1310.101+0.1*(exp(log(10*x(4)/(exp(norminv(x(1),0,1)*0.5742+8.4087)-1)))+exp(log(10*x(5)/(exp(norminv(x(2),0,1)*0.5742+8.4087)-1)))+exp(log(10*x(6)/(exp(norminv(x(3),0,1)*0.5742+8.4087)-1))));
%  
% end
function f =fun(x)
    f=-0.9*(exp(norminv(x(1),0,1)*0.64927+7.490348)+x(2))/306.47+0.1*(exp(log(10*x(2)/(exp(norminv(x(1),0,1)*0.64927+7.490348)-1))));
end

