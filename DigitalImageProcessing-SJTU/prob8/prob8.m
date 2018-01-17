% img = imread('noisy_fingerprint.tif');
% se = strel('square',3);
% eroded1 = imerode(img,se);
% dilated1 = imdilate(eroded1,se);
% close_img = imclose(dilated1,se);
% imshow(close_img);title('close-dilate+enrode');
% 
% img = imread('licoln_from_penny.tif');
% se = strel('square',3);
% eroded = imerode(img,se);
% boundary = imsubtract(img,eroded);
% subplot(1,2,1),imshow(img);title('original');
% subplot(1,2,2),imshow(boundary);title('boundary');

% img = im2bw(imread('region_filling_reflections.tif'));
% fill_img = imfill(img,[53 42],4);
% subplot(1,2,1),imshow(img);title('original');
% subplot(1,2,2),imshow(fill_img);title('fill image');
% 
% img = im2bw(imread('chickenfilet_with_bones.tif'),0.8);
% se = strel('square',5);
% enroded = imerode(img,se);
% subplot(3,1,1),imshow(imread('chickenfilet_with_bones.tif'));title('original');
% subplot(3,1,2),imshow(img);title('threshold');
% subplot(3,1,3),imshow(enroded);title('enroded');
% connected_info = bwconncomp(enroded,8)

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
