%-------------------------------------------------------------------------------
% Скрипт, готовящий матрицу векторов-признаков по изображениям, используя
% LBP-преобразование. Первые 200 строк - мужчины, остальные 200 строк - женщины
%-------------------------------------------------------------------------------
m = 200;
s = 200;
n = 5;
zones = 10;
X = zeros(m+s, zones*n*n);
p = 0;
for i = 1:1:m
    filename = strcat('OB/M/',int2str(i),'.png');
    f = imread(filename);
    g = lbp(f);
    x = vector_lbp(g,n,zones);   
    p = p + 1;
    X(p,:) = x;
end
for i = 1107:1:(1106+s)
    filename = strcat('OB/W/',int2str(i),'.png');
    f = imread(filename);
    g = lbp(f);
    x = vector_lbp(g,n,zones);
    p = p + 1;
    X(p,:) = x;
end
%-------------------------------------------------------------------------
%  Применение SVM для определения пола человека
%  X - данная, ранее созданная матрица векторов-признаков
%-------------------------------------------------------------------------
C = 2;
m = 200;
s = 200;
n = 5;
zones = 10;
% Обучаем классификатор
[L,b]=svm(X,m,s,C); 
% Классификатор на обучающей выборке
MAN = zeros(1,m);
for i = 1:1:m
    x = X(i,:);
    % Решающая функция. Написть самим
    MAN(i)=sign(rfunction(L,b,m,s,X,x));
end
WOMAN = zeros(1,s);
for i = 1:1:s
    x = X(i+m,:);
    WOMAN(i)=sign(rfunction(L,b,m,s,X,x));
end
% Тестирующая выборка. Тестируем классификатор.
m2 = 100;
s2 = 100;
% Матрица векторов признаков для тестирующей выборки
Y = zeros(m2+s2, zones*n*n);
p = 0;
for i = 201:1:300
    filename = strcat('TEST/M/',int2str(i),'.png');
    f = imread(filename);
    g = lbp(f);
    x = vector_lbp(g,n,zones);
    p = p + 1;
    Y(p,:) = x;
end
for i = 1307:1:1406
    filename = strcat('TEST/W/',int2str(i),'.png');
    f = imread(filename);
    g = lbp(f);
    x = vector_lbp(g,n,zones);
    p = p + 1;
    Y(p,:) = x;
end
ThisIsAMan = zeros(1,m2);
Numb = zeros(1,m2);
for i = 1:1:m2
    x = Y(i,:);
    Numb(i) = i;
    ThisIsAMan(i)=sign(rfunction(L,b,m,s,X,x));
end
ThisIsAWoman = zeros(1,s2);
for i = 1:1:s2
    x = Y(i+m2,:);
    ThisIsAWoman(i)=sign(rfunction(L,b,m,s,X,x));
end
figure;hold on;plot(Numb,ThisIsAMan,'r.'); plot(Numb,ThisIsAWoman,'b.'); hold off;