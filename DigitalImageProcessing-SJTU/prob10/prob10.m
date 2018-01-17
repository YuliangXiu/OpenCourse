clear;clc;
img = mat2gray(imread('noisy_stroke.tif'));
ave_img = imfilter(img,ones(9,9)/81);
otsu_thresh = graythresh(ave_img);
otsu_img = im2bw(ave_img,otsu_thresh);
se = strel('square',3);
eroded = imerode(otsu_img,se);
boundary_img = im2bw(imsubtract(otsu_img,imfill(eroded,'holes')),0);
[row,col] = find(boundary_img==1);
[s,su] = bsubsamp([row col],50);

subsample = zeros(570,570);
for i=1:32
    subsample(s(i,1),s(i,2))=1;
end

[x,y] = clockwise_order(s(:,1),s(:,2));
c = connectpoly(x,y);
lines = zeros(570,570);
for i=1:1664
    lines(c(i,1),c(i,2))=1;
end

[m,n] = clockwise_order(su(:,1),su(:,2));
cn_result = fchcode([m,n],8);

subplot(2,3,1),imshow(img);title('original');
subplot(2,3,2),imshow(ave_img);title('imfilter ave');
subplot(2,3,3),imshow(otsu_img);title('otsu');
subplot(2,3,4),imshow(boundary_img);title('boundary');
subplot(2,3,5),imshow(subsample);title('subsample');
subplot(2,3,6),imshow(lines);title('lines');