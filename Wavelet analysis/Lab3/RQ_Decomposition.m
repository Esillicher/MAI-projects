function [ K, R ] = RQ_Decomposition( M )
syms x1;
E1 = cos(x1)*M(3,2)+sin(x1)*M(3,3);
x1=eval(solve(E1));

[r,n]=size(x1);
i = 1;
Qx = [1 0 0; 0 cos(real(x1(i,1))) -sin(real(x1(i,1))); 0 sin(real(x1(i,1))) cos(real(x1(i,1)))];  

M1 = M*Qx;
syms x2;
E2 = cos(x2)*M1(3,1)+sin(x2)*M1(3,3);
x2=eval(solve(E2));

[r,n]=size(x2);
Qy = [cos(real(x2(i,1))) 0 -sin(real(x2(i,1))); 0 1 0; sin(real(x2(i,1))) 0 cos(real(x2(i,1)))];
   

M2 = M*Qx*Qy;
syms x3;
E3 = cos(x3)*M2(2,1)+sin(x3)*M2(2,2);
x3=eval(solve(E3));

[r,n]=size(x3);
Qz = [cos(real(x3(i,1))) -sin(real(x3(i,1))) 0; sin(real(x3(i,1))) cos(real(x3(i,1))) 0; 0 0 1];


K = M*Qx*Qy*Qz;
R = inv(Qx*Qy*Qz);
