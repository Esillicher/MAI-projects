clc;
N = 20;
w_min = 2; w_max = 9;
h_min = 5; h_max = 50;
S_min = 1/3; S_max = 3;
sigma_max = 5;
y_max = 10;
E = 1; F = 10;
x_p=zeros(N,1);

disp('-----------------------------------------------------------------');
disp('Исходные данные');
disp('-----------------------------------------------------------------');
fprintf(1,'Кол-во сегментов: %3.4f.\n', N)
fprintf(1,'Максимальная/минимальная ширина: %3.4f, %3.4f.\n', w_min, w_max)
fprintf(1,'Максимальная/минимальная высота: %3.4f, %3.4f.\n', h_min, h_max)
fprintf(1,'Соотношение сторон (максимальное/минимальное): %3.4f, %3.4f.\n', S_min, S_max)
fprintf(1,'Максимально допустимое напряжение: %3.4f.\n', sigma_max)
fprintf(1,'Максимальное вертикальное отклониение в конце балки: %3.4f.\n', y_max)
fprintf(1,'Приложенная сила: %3.4f.\n', F)
disp('-----------------------------------------------------------------');

% рекурсивный случай
disp('Рекурсивный случай');

cvx_begin gp
  variables w(N) h(N)

  v = cvx( zeros(N+1,1) );
  y = cvx( zeros(N+1,1) );
  for i = N:-1:1
    v(i) = 12*(i-1/2)*F/(E*w(i)*h(i)^3) + v(i+1);
    y(i) = 6*(i-1/3)*F/(E*w(i)*h(i)^3)  + v(i+1) + y(i+1);
  end

  minimize( w'*h )
  subject to
    w_min <= w <= w_max;
    h_min <= h <= h_max;
    S_min <= h./w <= S_max;
    6*F*[1:N]'./(w.*(h.^2)) <= sigma_max;
    y(1) <= y_max;
cvx_end

fprintf(1,'Кол-во сегментов: %3.4f.\n', N)
disp('Минимальная ширина и высота сегментов');
w, h
fprintf(1,'Минимальный объём балки: %3.4f.\n', sum(w.*h));
disp('-----------------------------------------------------------------');

figure, clf
plot_b(h,w,w_max,h_max,N)

% нерекурсивный случай

disp('Нерекурсивный случай');
cvx_begin gp
  
  variables w(N) h(N) v(N+1) y(N+1);

  minimize( w'*h )
  subject to
    
    d = 6*F*ones(N,1)./(E*ones(N,1).*w.*h.^3);
    for i = 1:N
      (2*i-1)*d(i) + v(i+1) <= v(i);
      (i-1/3)*d(i) + v(i+1) + y(i+1) <= y(i);
    end

    w_min <= w <= w_max;
    h_min <= h <= h_max;
    S_min <= h./w <= S_max;
    6*F*[1:N]'./(w.*(h.^2)) <= sigma_max;
    y(1) <= y_max;
cvx_end

disp('Минимальная ширина и высота сегментов');
w, h
fprintf(1,'Минимальный объём балки: %3.4f.\n', sum(w.*h))

% for i=N:-1:1
%     x_p(N-i+1,1) = w(i,1);
%     y_p(N-i+1,1) = y_p +  