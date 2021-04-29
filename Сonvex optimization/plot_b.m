function plot_b(height,width,w_max,h_max,p)

N = length(height);
for k = 0:N-1
  [X, Y] = data_rect(height(N-k),fliplr(width(N:-1:N-k,1)));
  plot(X,Y); hold on;
end
% W=[0 35]; 
% H=[-10 10];
% %axis([0 p*w_max -2*w_max 2*w_max]);
% Z=[0 0]; % линия координат
% plot(W,Z, 'k');
% plot(Z,H, 'k');
hold off;
grid on;
xlabel('width')
ylabel('height')
return;


%****************************************************************
function [X, Y] = data_rect(h,width)
%****************************************************************
n=length(width);
w=zeros(1,2);
for i=1:n
    if i == 1
        w(1,1)=w(1,1)+width(i,1);
    else
        w(1,1)=w(1,1)+width(i,1);
        w(1,2)=w(1,2)+width(i-1,1);
    end
    
end
X = [w(1,2) w(1,1) w(1,1) w(1,2) w(1,2)];
Y = [-h/2 -h/2 h/2 h/2 -h/2];

