#<center>Digital Image Processing</center>

<h6 align='center'>BB1603391 116033910045 修宇亮
##Problem 8 Requirement new
![](http://xiublog.qiniudn.com/image/2016-12-24-035010.jpg)
##Problem 8 Requirement old
![](http://xiublog.qiniudn.com/image/2016-12-22-082534.jpg)

##Problem 8 solution new

###opening by reconstruction
```matlab
img = imread('Fig0929(a)(text_image).tif');
se = strel('rectangle',[51 1]);
eroded = imerode(img,se);
opened = imopen(img,se);
rec_open = imreconstruct(eroded,img);

subplot(2,2,1),imshow(img);title('original');
subplot(2,2,2),imshow(eroded);title('eroded');
subplot(2,2,3),imshow(opened);title('opened');
subplot(2,2,4),imshow(rec_open);title('rec_open');
```

![](http://xiublog.qiniudn.com/image/2016-12-24-034819.jpg)

###filling holes
```matlab
img = imread('Fig0929(a)(text_image).tif');
f_img = zeros(size(img));
[M,N] = size(img);

f_img(1,:) = 1-img(1,:);
f_img(M,:) = 1-img(M,:);
f_img(:,1) = 1-img(:,1);
f_img(:,N) = 1-img(:,N);

se = strel('square',3);
fill_img = imadd(logical((~(logical(imdilate(logical(f_img),se)).*(~img))).*(~img)),img);

subplot(2,2,1),imshow(img);title('original');
subplot(2,2,2),imshow(~img);title('reverse');
subplot(2,2,3),imshow(f_img);title('f_img');
subplot(2,2,4),imshow(fill_img);title('fill_img');
```
![](http://xiublog.qiniudn.com/image/2016-12-24-044237.jpg)

###Border clearing
```matlab
img = imread('Fig0931(a)(text_image).tif');
f_img = zeros(size(img));
[M,N] = size(img);

f_img(1,:) = 1-img(1,:);
f_img(M,:) = 1-img(M,:);
f_img(:,1) = 1-img(:,1);
f_img(:,N) = 1-img(:,N);

se = strel('square',3);
eroded = imdilate(f_img,se);
border = imreconstruct(logical(eroded),img);

subplot(1,2,1),imshow(border);title('border');
subplot(1,2,2),imshow(imsubtract(img,border));title('no border');

```

![](http://xiublog.qiniudn.com/image/2016-12-24-050247.jpg)
##Problem 8 solution old

###close&open.m

```matlab
img = imread('noisy_fingerprint.tif');
se = strel('square',3);
eroded1 = imerode(img,se);
dilated1 = imdilate(eroded1,se);
close_img = imclose(dilated1,se);
imshow(close_img);title('close-dilate+enrode');
```
###boundary_extraction.m
```matlab
img = imread('licoln_from_penny.tif');
se = strel('square',3);
eroded = imerode(img,se);
boundary = imsubtract(img,eroded);
subplot(1,2,1),imshow(img);title('original');
subplot(1,2,2),imshow(boundary);title('boundary');
```
###hole_fill.m
```matlab
img = imread('region_filling_reflections.tif');
fill_img = imfill(img,'holes');
subplot(1,2,1),imshow(img);title('original');
subplot(1,2,2),imshow(fill_img);title('fill image');
```
###connected_extraction.m
```matlab
img = im2bw(imread('chickenfilet_with_bones.tif'),0.8);
se = strel('square',5);
enroded = imerode(img,se);
connected_info = bwconncomp(enroded,8)
```

##Result
###original fingerprint
![](http://xiublog.qiniudn.com/image/2016-12-22-124552.jpg)
###open-enrode
![](http://xiublog.qiniudn.com/image/2016-12-22-123903.jpg)
###open-dilate
![](http://xiublog.qiniudn.com/image/2016-12-22-124109.jpg)
###close-dilate+enrode
![](http://xiublog.qiniudn.com/image/2016-12-22-124327.jpg)
###boundary extraction
![](http://xiublog.qiniudn.com/image/2016-12-22-124849.jpg)
###hole filling
![](http://xiublog.qiniudn.com/image/2016-12-22-130554.jpg)
###connected component extraction
![](http://xiublog.qiniudn.com/image/2016-12-22-132849.jpg)

###statistics result
```matlab
connected_info = 

    Connectivity: 8
       ImageSize: [321 712]
      NumObjects: 17
    PixelIdxList: {1x17 cell}

>> connected_info.PixelIdxList

ans = 

  Columns 1 through 6

    [6x1 double]    [7x1 double]    [39x1 double]    [128x1 double]    [91608]    [93534]

  Columns 7 through 12

    [21x1 double]    [599x1 double]    [7x1 double]    [11x1 double]    [7x1 double]    [3x1 double]

  Columns 13 through 17

    [112839]    [4x1 double]    [19x1 double]    [664x1 double]    [80x1 double]
```
