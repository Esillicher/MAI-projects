function [fun] = rfunction(L,b,m,s,X,x)
    [N,M]=size(X);
    f=0;
    fun=0;
    y=[ones(1,m) -ones(1,s)];
    for i=1:N
        f=f+L(i,1)*y(1,i)*sum(X(i,:).*x);
    end
    fun=f+b;
end
