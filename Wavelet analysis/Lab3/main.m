clear;
% Два изображения одной сцены
Im1 = imread('House/001.jpg');
Im2 = imread('House/002.jpg');

% Точки первого изображения
fid = fopen('House/2D/001.corners'); 
Tp = textscan(fid, '%n %n'); 
fclose(fid);
N = length(Tp{1,1});
points1 = zeros(N,2);
points1(:,1) = Tp{1,1}(:,1);
points1(:,2) = Tp{1,2}(:,1);
p2D_Im1 = cornerPoints(single(points1));

% Точки второго изображения
fid = fopen('House/2D/002.corners'); 
Tp = textscan(fid, '%n %n'); 
fclose(fid);
N = length(Tp{1,1});
points2 = zeros(N,2);
points2(:,1) = Tp{1,1}(:,1);
points2(:,2) = Tp{1,2}(:,1);
p2D_Im2 = cornerPoints(single(points2));

figure;
imshow(Im1);
hold on;
plot(p2D_Im1.selectStrongest(p2D_Im1.Count));
hold off;

figure;
imshow(Im2);
hold on;
plot(p2D_Im2.selectStrongest(p2D_Im2.Count));
hold off;

% 3D точки
fid = fopen('House/3D/p3d'); 
Tp = textscan(fid, '%n %n %n'); 
fclose(fid);
N = length(Tp{1,1});
p3D = zeros(N,3);
p3D(:,1) = Tp{1,1}(:,1);
p3D(:,2) = Tp{1,2}(:,1);
p3D(:,3) = Tp{1,3}(:,1);

% Матрица камеры L_1
fid = fopen('House/2D/001.P'); 
Tp = textscan(fid, '%n %n %n %n'); 
fclose(fid);
L1 = zeros(3,4);
for i = 1:1:3
    L1(i,1) = Tp{1,1}(i,1);
    L1(i,2) = Tp{1,2}(i,1);
    L1(i,3) = Tp{1,3}(i,1);
    L1(i,4) = Tp{1,4}(i,1);
end

% Матрица камеры L_2
fid = fopen('House/2D/002.P'); 
Tp = textscan(fid, '%n %n %n %n'); 
fclose(fid);
L2 = zeros(3,4);
for i = 1:1:3
    L2(i,1) = Tp{1,1}(i,1);
    L2(i,2) = Tp{1,2}(i,1);
    L2(i,3) = Tp{1,3}(i,1);
    L2(i,4) = Tp{1,4}(i,1);
end

% Соответствия между точками изображений
fid = fopen('House/2D/nview-corners'); 
Tl = textscan(fid, '%s %s %s'); 
fclose(fid);
N = length(Tl{1,1});
Match = zeros(N,3);
Location = zeros(N,2);
S = 0;
for i = 1:1:N
    c = Tl{1,1}(i,1);
    if (strcmp(c,'*'))
        Match(i,1) = -1;
    else
        Match(i,1) = str2double(c)+1;
    end
    c = Tl{1,2}(i,1);
    if (strcmp(c,'*'))
        Match(i,2) = -1;
    else
        Match(i,2) = str2double(c)+1;
    end
    c = Tl{1,3}(i,1);
    if (strcmp(c,'*'))
        Match(i,3) = -1;
    else
        Match(i,3) = str2double(c)+1;
    end
    if ((Match(i,1) ~= -1) && (Match(i,2) ~= -1))
        S = S + 1;
        Location(S,:) = Match(i,1:2);
    end
end
Location = Location(1:S,:);
matchedPoints1 = points1(Location(:,1),:);
matchedPoints2 = points2(Location(:,2),:);
figure; ax = axes;
showMatchedFeatures(Im1,Im2,matchedPoints1,matchedPoints2,'montage','Parent',ax);

% ========================= Часть 1. Триангуляция =========================
N = size(matchedPoints1,1);
Y = zeros(3,N);
for j = 1:1:N
    [ P ] = Triangulation(j,L1, L2, matchedPoints1, matchedPoints2);
    Y(:,j) = P(1:3,1);
end
figure;
hold on;
plot3(Y(1,:),Y(2,:),Y(3,:),'.r');
plot3(p3D(:,1),p3D(:,2),p3D(:,3),'og');
hold off;
%========================== Часть 2. Калибровочная матрица ================
M = L1(:,1:3);
[ K1, R1 ] = RQ_Decomposition( M ); % Эту функцию необходимо написать
M = L2(:,1:3);
[ K2, R2 ] = RQ_Decomposition( M );
%========================= Часть 3. Метрическая реконструкция =============
% Переходим к нормированным координатам
norm_matchedPoints1 = zeros(N,2);
norm_matchedPoints2 = zeros(N,2);
for i = 1:1:N
    x_prime = zeros(3,1)+1;
    x = zeros(3,1)+1;
    x_prime(1:2,1) = (matchedPoints2(i,:))';
    x(1:2,1) = (matchedPoints1(i,:))';
    x_prime = inv(K2) * x_prime;
    x = inv(K1) * x;
    norm_matchedPoints1(i,:) = (x(1:2,1)/x(3,1))';
    norm_matchedPoints2(i,:) = (x_prime(1:2,1)/x_prime(3,1))';
end
% Находим существенную матрицу
E = estimateFundamentalMatrix(norm_matchedPoints1,norm_matchedPoints2,'Method','Norm8Point');
[U,D,V]= svd(E);
E = U*[1 0 0;0 1 0;0 0 0]*V';
W = [0 -1 0; 1 0 0; 0 0 1];
% Нахождение матриц камер по заданной существенной матрице
[ L1_rec, L2_rec_all ] = MatrixCamers( U,V, W ); % Эту функцию необходимо написать
% Выбираем нужную камеру по наибольшему количеству точек,
% находящихся перед камерой. Если $P_j$ - точка после триангуляции, то
% находим ее проекции на плоскости изображений $x=L_{1,rec}P_j$
% $x'=L_{2,rec}Pj$. Точка находится перед камерами, 
% если $x_3 > 0$ и $x'_3 > 0$.
P_all = cell(4,1); % Триангуляция для всех найденных камер
NumP = zeros(4,1);
for i = 1:1:4
    if i==1
        L2_rec = L2_rec_all(1:3,:);
    end
    if i==2
        L2_rec = L2_rec_all(4:6,:);
    end
    if i==3
        L2_rec = L2_rec_all(7:9,:);
    end
    if i==4
        L2_rec = L2_rec_all(10:12,:);
    end    
    Y = zeros(3,N);
    s = 0;
    for j = 1:1:N        
        [ Pj ] = Triangulation( j, L1_rec, L2_rec, norm_matchedPoints1, norm_matchedPoints2 );
        x1 = L1_rec' * Pj;
        x2 = L2_rec' * Pj;
        if ((x1(3,1) > 0) && (x2(3,1) > 0))
            s = s + 1;
            Y(:,s) = Pj(1:3,1);        
        end
    end
    NumP(i,1) = s;
    P_all{i,1} = Y;    
end
MaxNumP = max(NumP);
i = find(NumP == MaxNumP);
Y = P_all{i,1};
figure;
plot3(Y(1,:),Y(2,:),Y(3,:),'.r');