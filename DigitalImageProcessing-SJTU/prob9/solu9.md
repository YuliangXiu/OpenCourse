#<center>Digital Image Processing</center>

<h6 align='center'>BB1603391 116033910045 修宇亮

##Problem 9 Requirement
![](http://xiublog.qiniudn.com/image/2016-12-23-063212.jpg)

##Problem 9 solution
###edge_detection.m
```matlab
img = imread('building.tif');
gray_img = mat2gray(img);
thresh = 0.33;
ave_filter_img = imfilter(gray_img,ones(5,5)/25);

robert_img = edge(ave_filter_img,'Roberts');
prewitt_img = edge(ave_filter_img,'Prewitt');
sobel_img = edge(ave_filter_img,'Sobel');

marr_img = edge(ave_filter_img,'log',0.0008,4);
canny_img = edge(ave_filter_img,'Canny',[0.04 0.1],4);

% imshow(canny_img);title('robert');

subplot(2,3,1),imshow(img);title('original');
subplot(2,3,2),imshow(robert_img);title('robert');
subplot(2,3,3),imshow(prewitt_img);title('prewitt');
subplot(2,3,4),imshow(sobel_img);title('sobel');
subplot(2,3,5),imshow(marr_img);title('marr');
subplot(2,3,6),imshow(canny_img);title('canny');
```
###Original
![](http://xiublog.qiniudn.com/image/2016-12-23-082240.jpg)
###Roberts
![](http://xiublog.qiniudn.com/image/2016-12-23-082857.jpg)
###Prewitt
![](http://xiublog.qiniudn.com/image/2016-12-23-082458.jpg)
###Sobel
![](http://xiublog.qiniudn.com/image/2016-12-23-082548.jpg)
###Marr-Hildren
![](http://xiublog.qiniudn.com/image/2016-12-23-082627.jpg)
###Canny
![](http://xiublog.qiniudn.com/image/2016-12-23-082655.jpg)

###thresh_seg.m

```matlab
function T=gbt(x)

[M,N]=size(x);
T=x(randi(M-1),randi(N-1));
T0=0;

mean1=sum(sum(x(x<=T)))/sum(sum(x<=T));
mean2=sum(sum(x(x>T)))/sum(sum(x>T));

while abs(T-T0)>10^-8
    T0=T;
    T=(mean1+mean2)/2;
    mean1=sum(sum(x(x<=T)))/sum(sum(x<=T));
    mean2=sum(sum(x(x>T)))/sum(sum(x>T));
end

img = mat2gray(imread('polymersomes.tif'));
gbt_img = im2bw(img,gbt(img));
otsu_thresh = graythresh(img);
otsu_img = im2bw(img,otsu_thresh);

imshowpait(gbt_img,otsu_img,'montage');

```
![](http://xiublog.qiniudn.com/image/2016-12-23-085120.jpg)

