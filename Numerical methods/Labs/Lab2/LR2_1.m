x = 0:1/100:2;
y1 = x.^3;
y2 = 2*x.^2+10*x-15;

figure
subplot(1,2,1)
plot(x,y1,x,y2), grid
xlabel('Нелинейное уравнение')
legend('y = x^3','y = 2x^2+10x-15', 4);

subplot(1,2,2)
ezplot('x-cos(y)=1',[0,10])
hold on
ezplot('y-sin(x)=1',[0,10]), grid
hold off
xlabel('Система нелинейных уравнений')
legend('x-cos(y)=1','y-sin(x)=1', 4);

%ezplot('(x^2/9)-(y^2/(1.5^2))-1=0',[0,10]), hold
%ezplot('3*y-exp(x)-x=0',[0,10]), grid