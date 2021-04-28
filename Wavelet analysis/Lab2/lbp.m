function [g] = lbp(f)
[N,M] = size(f);
g=0;
a(1,8)=0;
s=[2^7 2^6 2^5 2^4 2^3 2^2 2^1 2^0];
for i=1:N
    for j=1:M
        if i~=N % вниз
            if f(i,j)>=f(i+1,j) 
                    a(1,1)=1;
                else
                    a(1,1)=0;
            end
        end
        if i~=N && j~=M % вниз вправо
            if f(i,j)>=f(i+1,j+1) 
                a(1,2)=1;
            else
                a(1,2)=0;
            end
        end
        if j~=M
            if f(i,j)>=f(i,j+1) % вправо
                a(1,3)=1;
            else
                a(1,3)=0;
            end
        end
        if i~=1 && j~=M % наверх вправо
            if f(i,j)>=f(i-1,j+1) 
                a(1,4)=1;
            else
                a(1,4)=0;
            end
        end
        if i~=1
            if f(i,j)>=f(i-1,j) % наверх
                a(1,5)=1;
            else
                a(1,5)=0;
            end
        end
        if i~=1 && j~=1 % наверх влево
            if f(i,j)>=f(i-1,j-1) 
                a(1,6)=1;
            else
                a(1,6)=0;
            end
        end
        if j~=1
            if f(i,j)>=f(i,j-1) % влево
                a(1,7)=1;
            else
                a(1,7)=0;
            end
        end
        if i~=N && j~=1
            if f(i,j)>=f(i+1,j-1) % вниз влево
                a(1,8)=1;
            else
                a(1,8)=0;
            end
        end        
        g(i,j)=sum(a.*s);
    end
end

