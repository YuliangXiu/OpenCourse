%ԭʼͼ����ֱ��ͼ
subplot(1,2,1);
f = imread('Fig1.jpg');
h = imhist(f,25);
horz = linspace(0,255,25);
bar(horz,h);
axis([0 255 0 120000]);
set(gca,'xtick',0:10:255);
xlabel('grey level');
ylabel('pixel num');
title('Histogram of Fig1');

%ֱ��ͼ���⻯
subplot(1,2,2);
f = imread('Fig1.jpg');
eq_f = histeq(f);
imshow(eq_f);
h = imhist(eq_f,25);
horz = linspace(0,255,25);
bar(horz,h);
axis([0 255 0 120000]);
set(gca,'xtick',0:10:255);
xlabel('grey level');
ylabel('pixel num');
title('Histogram of enhanced Fig1');

%���ֱ��ͼ���⻯��ת������
f = imread('Fig1.jpg');
h = imhist(f);
cum_h = cumsum(h);
bar(cum_h);
xlabel('grey level');
ylabel('cumulated pixel num');
title('Histogram-Equalization Transform');


