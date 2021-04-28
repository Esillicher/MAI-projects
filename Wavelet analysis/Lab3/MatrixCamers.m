function [ L1_rec, L2_rec_all ] = MatrixCamers( U,V, W )
L1_rec=[eye(3) zeros(3,1)];
L2_1 = [U*W*V' U(:,3)];
L2_2 = [U*W*V' -U(:,3)];
L2_3 = [U*W'*V' U(:,3)];
L2_4 = [U*W'*V' -U(:,3)];

L2_rec_all = [L2_1 ; L2_2 ; L2_3 ; L2_4 ]; 