clearvars;
% Данное изображение
J1 = imread('1.tif');
% Преобразованное изображение
J2 = imread('2.tif');
% Угловые точки на изображении J1
points1 = detectHarrisFeatures(J1); % ????? $x_1$
figure;
imshow(J1);
hold on;


plot(points1.selectStrongest(200));
hold off;
% Угловые точки на изображении J2
points2 = detectHarrisFeatures(J2); % ????? $x_2$
figure;
imshow(J2);
hold on;
plot(points2.selectStrongest(200));
hold off;
% Получение дескрипторов
[f1,vpts1] = extractFeatures(J1,points1);
[f2,vpts2] = extractFeatures(J2,points2);
% Сравнение дескрипторов изображений % $x_2 <-> x_1$
indexPairs = matchFeatures(f1,f2);
% Число используемых точеченых соответствий
% для построения матрицы гомографии
N = size(indexPairs,1);
matchedPoints1 = vpts1(indexPairs(1:N,1));
matchedPoints2 = vpts2(indexPairs(1:N,2));
figure; ax = axes;
showMatchedFeatures(J1,J2,matchedPoints1,matchedPoints2,'montage','Parent',ax);
% Вычисление матрицы гомографии $x_2 = H \cdot x_1$.
% Здесь $x_1, x_2$ - столбцы.
x = [matchedPoints1.Location ones(N,1)]; % x
x_ = [matchedPoints2.Location ones(N,1)]; % x'
A = zeros(3*N,9);

for i=1:N
   A(3*(i-1)+1,1:3) = 0;
   A(3*(i-1)+1,4:6) = -x_(i,3)*x(i,:);
   A(3*(i-1)+1,7:9) = x_(i,2)*x(i,:);
   
   A(3*(i-1)+2,1:3) = x_(i,3)*x(i,:);
   A(3*(i-1)+2,4:6) = 0;
   A(3*(i-1)+2,7:9) = -x_(i,1)*x(i,:);
   
   A(3*(i-1)+3,1:3) = -x_(i,2)*x(i,:);
   A(3*(i-1)+3,4:6) = x_(i,1)*x(i,:);
   A(3*(i-1)+3,7:9) = 0;
end

[U,D,V] = svd(A);
h = V(:,9);
H = [ h(1:3) h(4:6) h(7:9)];
% Обратное преобразование
T = H; % Транспонирование на случай, если $x_1, x_2$ - столбцы
t_proj = projective2d(T^(-1)); % [u v w] = [x y z] T, T=H'
J2_p = imwarp(J2, t_proj); % преобразование изображения
figure;
imshowpair(J2_p,J1,'montage');