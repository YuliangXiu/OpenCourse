#<center>Digital Image Processing</center>

<h6 align='center'>BB1603391 116033910045 修宇亮

##Problem 2 Requirement
![](http://xiublog.qiniudn.com/2016-10-01-21%3A05%3A34.jpg)

##Problem solutions

###solu2.m

```matlab
subplot(2,4,1);
imshow(imread('skeleton_orig.tif'));
title('original image');
orig_img = double(imread('skeleton_orig.tif'));
lap_result = orig_img;
soble_result = orig_img;
soble_ave_result = orig_img;
syms h w
[h,w] = size(orig_img);

% laplacian
subplot(2,4,2);
lap_mat = double([0,1,0;1,-4,1;0,1,0]);
for row = 2:h-1
    for col = 2:w-1
        conv_region = orig_img(row-1:row+1,col-1:col+1);
        lap_result(row,col) = sum(sum(conv_region.*lap_mat));
    end
end
lap_result = image_scale(lap_result);
lap_img = uint8(lap_result);
imshow(lap_img);
title('laplacian template');

%laplacian + origin
subplot(2,4,3);
orig_lap_result = orig_img + lap_result;
orig_lap_img = uint8(orig_lap_result);
imshow(orig_lap_img);
title('laplacian image');

% soble3*3
subplot(2,4,4);
soble_mat1 = double([-1,-2,-1;0,0,0;1,2,1]);
soble_mat2 = double([-1,0,1;-2,0,2;-1,0,1]);
for row = 2:h-1
    for col = 2:w-1
        conv_region = orig_img(row-1:row+1,col-1:col+1);
        soble_result(row,col) = abs(sum(sum(conv_region.*soble_mat1)))+abs(sum(sum(conv_region.*soble_mat2)));
    end
end
soble_result = image_scale(soble_result);
soble_img = uint8(soble_result);
imshow(soble_img);
title('soble image');


%average5*5
subplot(2,4,5);
for row = 3:h-2
    for col = 3:w-2
        conv_region = soble_result(row-2:row+2,col-2:col+2);
        soble_ave_result(row,col) = 1/25*(sum(conv_region(:)));
    end
end

soble_ave_result = image_scale(soble_ave_result);
soble_ave_img = uint8(soble_ave_result);
imshow(soble_ave_img);
title('average image');

% ave_soble * (laplacian + origin)
subplot(2,4,6);
soble_lap_result = image_scale(soble_ave_result .* orig_lap_result);
soble_lap_img = uint8(soble_lap_result);
imshow(soble_lap_img);
title('soble-lap template');

%soble + lap + origin
subplot(2,4,7);
soble_orig_result = soble_lap_result + orig_img;
soble_orig_img = uint8(soble_orig_result);
imshow(soble_orig_img);
title('soble-lap image');

%mi layer
subplot(2,4,8);
mi_result = image_scale(soble_orig_result.^0.5);
mi_img = uint8(mi_result);
imshow(mi_img);
title('mi image');

```
###image_scale.m
```matlab
function output  = image_scale(input)
    input = input - min(input(:));
    output = 255*(input/max(input(:)));
end
```

##Result Image
![](http://xiublog.qiniudn.com/2016-10-04-all_results.bmp)
###original image
![](http://xiublog.qiniudn.com/2016-10-04-skeleton_orig.tif)
###laplacian template
![](http://xiublog.qiniudn.com/2016-10-04-laplacian.bmp)
###laplacian image
![](http://xiublog.qiniudn.com/2016-10-04-orig%2Blaplacian.bmp)
###soble image
![](http://xiublog.qiniudn.com/2016-10-04-soble3-3.bmp)
###average image
![](http://xiublog.qiniudn.com/2016-10-04-soble%2Bave.bmp)
###soble-lap template
![](http://xiublog.qiniudn.com/2016-10-04-soble_lap.bmp)
###soble-lap image
![](http://xiublog.qiniudn.com/2016-10-04-soble_lap_orig.bmp)
###mi image
![](http://xiublog.qiniudn.com/2016-10-04-final.bmp)