img = mat2gray(imread('polymersomes.tif'));
gbt_img = im2bw(img,gbt(img));
otsu_thresh = graythresh(img);
otsu_img = im2bw(img,otsu_thresh);

imshowpair(gbt_img,otsu_img,'montage');