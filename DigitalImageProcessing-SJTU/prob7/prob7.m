img = imread('lenna.tif');
[M,N] = size(img);
all_in = zeros(3*M,3*N);

for k=1:3
    tran_img = waveletcdf97(double(img),k*3);
    tran_img(tran_img<1/40);
    img_rec = waveletcdf97(tran_img(tran_img>1/40),-k*3);
    img_diff=imsubtract(img,uint8(img_rec));
    all_in((k-1)*M+1:(k-1)*M+M,1:N*3)=[img,img_rec,img_diff];
end

imshow(mat2gray(all_in));
