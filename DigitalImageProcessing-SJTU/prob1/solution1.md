#<center>Digital Image Processing</center>

<h6 align='center'>BB1603391 116033910045 修宇亮

##Problem 1 Requirement
![](http://xiublog.qiniudn.com/2016-09-25-16%3A03%3A25.jpg)

##Problem solutions

###code of histogram of Fig1
```matlab
f = imread('Fig1.jpg');
h = imhist(f,25);
horz = linspace(0,255,25);
bar(horz,h);
axis([0 255 0 120000]);
set(gca,'xtick',0:10:255);
xlabel('grey level');
ylabel('pixel num');
title('Histogram of Fig1');
```
###original Fig1
![](http://xiublog.qiniudn.com/2016-09-25-Fig1.jpg)
###histogram of Fig1
![](http://xiublog.qiniudn.com/2016-09-25-a.jpg)
###code of equalization of Fig1
```matlab
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

```
###enhanced Fig1
![](http://xiublog.qiniudn.com/2016-09-25-b.jpg)
###histogram of enhanced Fig1
![](http://xiublog.qiniudn.com/2016-09-25-c.jpg)
###code of histogram-equalization transform
```matlab
f = imread('Fig1.jpg');
h = imhist(f);
cum_h = cumsum(h);
bar(cum_h);
xlabel('grey level');
ylabel('cumulated pixel num');
title('Histogram-Equalization Transform');

```
###histogram-equalization transform function
![](http://xiublog.qiniudn.com/2016-09-25-d.jpg)




