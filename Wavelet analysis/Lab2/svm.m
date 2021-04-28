function[L,b]=svm(X,m,s,C)
    [N,M]=size(X);
    y=[ones(1,m) -ones(1,s)];
    H=zeros(N,N);
        for i=1:N
            for j=1:N
                H(i,j)=y(1,i)*y(1,j)*sum(X(i,:).*X(j,:));
            end
        end
        f=-ones(N,1);
        Aeq=y;
        beq=0;
        lb=zeros(N,1);
        ub=C*ones(N,1);
    options = optimset('MaxIter', 5000);
    L = quadprog(H,f,[],[],Aeq, beq, lb, ub,[], options);
    nabor = 0;
    o=1;
    for i=1:N    
        if L(i,1)>0 && L(i,1)<C
            nabor(o,1)=i;
            o=o+1;
        end
    end
    [R,M]=size(nabor);
    s=zeros(R,1);
    for r=1:R
        for i=1:N
            s(r,1)=s(r,1)+L(i,1)*y(1,i)*sum(X(i,:).*X(r,:));
        end
        s(r,1)=-s(r,1)+1/y(1,r);
    end
    b=median(s);
%     w=0;
%     for i=1:N
%         w=w+L(i,1)*y(1,i)*X(i,:);
%     end
%     b=1-sum(w.*X(1,:));
end
