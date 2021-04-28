function [ P ] = Triangulation(j, L1, L2, matchedPoints1 , matchedPoints2)
x= [matchedPoints1(j,:) 1]';
x_=[matchedPoints2(j,:) 1]';
A=[L1 -x zeros(3,1); L2 zeros(3,1) -x_ ];
[U,D,V] = svd(A);
h = V(1:4,6);
P=[h(1,1)/h(4,1) h(2,1)/h(4,1) h(3,1)/h(4,1) ]';
