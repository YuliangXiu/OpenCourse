orig_img = imread('Circuit.tif');
noise_type = {'uniform','gaussian','salt & pepper','lognormal','rayleigh','exponential','erlang'};
filter_type = {'amean','gmean','hmean','chmean','median','max','min','midpoint','atrimmed'};
[M,N] = size(orig_img);
bins  = 51;

for i=3:3
    set(gcf, 'position', [0 0 1200 300]);
    subplot(1,3,1),imshow(orig_img);title('original image');
    switch i
        case 1
            noise = imnoise2(noise_type{i},M,N,0,0.1);
        case 2
            noise = imnoise2(noise_type{i},M,N,0,0.1);
        case 3
            % salt
            noise = imnoise2(noise_type{i},M,N,0,0.1);
            noise_img1 = orig_img;
            noise_img1(noise == 1) = 255;
            % pepper
            noise = imnoise2(noise_type{i},M,N,0.1,0);
            noise_img2 = orig_img;
            noise_img2(noise == 0) = 0;
        otherwise
            noise = imnoise2(noise_type{i},M,N);
        
    end
    
    subplot(1,3,2),hist(noise(:),bins);title([noise_type{i},' noise']);
    if i ~= 3
        noise_img = im2uint8(im2double(orig_img)+noise);
        subplot(1,3,3),imshow(noise_img);title([noise_type{i},' image']);
    else
        subplot(1,3,3),imshow(noise_img1);title([noise_type{i},' image']);
%         subplot(1,3,3),imshow(noise_img2);title([noise_type{i},' image']);
    end
    
end

i=5;
j=5;
num = [4,4,4,4,3];
switch i
    case 1
        % uniform
        noise = imnoise2(noise_type{i},M,N,0,0.1);
        noise_img = im2uint8(im2double(orig_img)+noise);
    case 2
        % gaussian
        noise = imnoise2(noise_type{i},M,N,0,0.1);
        noise_img = im2uint8(im2double(orig_img)+noise);
    case 3
        % salt
        noise = imnoise2(noise_type{i},M,N,0,0.1);
        noise_img1 = orig_img;
        noise_img1(noise == 1) = 255;
        % pepper
        noise = imnoise2(noise_type{i},M,N,0.1,0);
        noise_img2 = orig_img;
        noise_img2(noise == 0) = 0;
    case 4
        % salt & peper
        noise = imnoise2(noise_type{3},M,N,0.1,0.1);
        noise_img = orig_img;
        noise_img(noise == 1) = 255;
        noise_img(noise == 0) = 0;
    case 5
        % uniform
        noise = imnoise2(noise_type{1},M,N,0,0.1);
        noise_img1 = im2uint8(im2double(orig_img)+noise);
        % salt & peper
        noise = imnoise2(noise_type{3},M,N,0.1,0.1);
        noise_img2 = noise_img1;
        noise_img2(noise == 1) = 255;
        noise_img2(noise == 0) = 0;
       

end
switch j
    case 1
        set(gcf, 'position', [0 0 num(j)*400 300]);
        subplot(1,num(j),1),imshow(orig_img);title('original image');
        subplot(1,num(j),2),imshow(noise_img);title([noise_type{i},' image']);
        amean_uniform_img = spfilt(noise_img,'amean');
        subplot(1,num(j),3),imshow(amean_uniform_img);title([filter_type{1},' result']);
        gmean_uniform_img = spfilt(noise_img,'gmean');
        subplot(1,num(j),4),imshow(gmean_uniform_img);title([filter_type{2},' result']);
    case 2
        set(gcf, 'position', [0 0 num(j)*400 300]);
        subplot(1,num(j),1),imshow(noise_img1);title('salt image');
        subplot(1,num(j),2),imshow(noise_img2);title('pepper image');
        chmean_salt_img = spfilt(noise_img1,'chmean',3,3,-1.5);
        subplot(1,num(j),3),imshow(chmean_salt_img);title('salt result');
        chmean_pepper_img = spfilt(noise_img2,'chmean',3,3,1.5);
        subplot(1,num(j),4),imshow(chmean_pepper_img);title('pepper result');
    case 3
        set(gcf, 'position', [0 0 num(j)*400 300]);
        subplot(1,num(j),1),imshow(noise_img);title('salt&pepper image');
        median_salt_pepper_img1 = spfilt(noise_img,'median');
        subplot(1,num(j),2),imshow(median_salt_pepper_img1);title('median 1st');
        median_salt_pepper_img2 = spfilt(median_salt_pepper_img1,'median');
        subplot(1,num(j),3),imshow(median_salt_pepper_img2);title('median 2nd');
        median_salt_pepper_img3 = spfilt(median_salt_pepper_img2,'median');
        subplot(1,num(j),4),imshow(median_salt_pepper_img3);title('median 3rd');
    case 4
        set(gcf, 'position', [0 0 num(j)*400 300]);
        subplot(1,num(j),1),imshow(noise_img1);title('salt image');
        subplot(1,num(j),2),imshow(noise_img2);title('pepper image');
        min_salt_img = spfilt(noise_img1,'min',3,3);
        max_pepper_img = spfilt(noise_img2,'max',3,3);
        subplot(1,num(j),3),imshow(min_salt_img);title('min result');
        subplot(1,num(j),4),imshow(max_pepper_img);title('max result');
    case 5
        set(gcf, 'position', [0 0 num(j)*400 600]);
        subplot(2,num(j),1),imshow(noise_img1);title('uniform image');
        subplot(2,num(j),2),imshow(noise_img2);title('salt&pepper image');
        amean_result = spfilt(noise_img2,'amean',5,5);
        subplot(2,num(j),3),imshow(amean_result);title('amean result');
        gmean_result = spfilt(amean_result,'gmean',5,5);
        subplot(2,num(j),4),imshow(gmean_result);title('gmean result');
        median_result = spfilt(gmean_result,'median',5,5);
        subplot(2,num(j),5),imshow(median_result);title('median result');
        altrimmed_result = spfilt(median_result,'atrimmed',5,5,4);
        subplot(2,num(j),6),imshow(altrimmed_result);title('atrimmed result');
        
        
        
end
