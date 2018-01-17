orig_img = imread('book_cover.jpg');
[M,N] = size(orig_img);
% produce noise image
PSF = fspecial('motion',100,45);
blur_img = imfilter(orig_img,PSF,'circular');
gau_noise = imnoise2('gaussian',M,N,0,sqrt(0.001));
blur_gau_img = im2uint8(im2double(blur_img) + gau_noise);

%wiener deconvolution filter result
sn = abs(fft2(gau_noise)).^2;
na = sum(sn(:))/numel(gau_noise);
sf = abs(fft2(orig_img)).^2;
fa = sum(sf(:))/numel(orig_img);
R = na/fa;

%wiener parametric filter result
ncorr = fftshift(real(ifft2(sn)));
icorr = fftshift(real(ifft2(sf)));
blur_wd_img = deconvwnr(blur_img,PSF,ncorr,icorr);
blur_gau_wd_img = deconvwnr(blur_gau_img,PSF,ncorr,icorr);

% plot
set(gcf,'position',[0,0,800,600]);
subplot(2,2,1),imshow(blur_img);title('blur image');
subplot(2,2,2),imshow(blur_gau_img);title('add gaussian');
subplot(2,2,3),imshow(blur_wd_img);title('blur wiener param');
subplot(2,2,4),imshow(blur_gau_wd_img);title('blur gaussian wiener param');