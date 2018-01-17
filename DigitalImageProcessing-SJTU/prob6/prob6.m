orig_img = imread('ray_trace_bottle.tif');
[M,N] = size(orig_img);
scale_params = [4,4];
trans_params = [-10.3,-10.7];
rotate_param = 45;
scale_nn_result = scale(orig_img,'nn',scale_params(1),scale_params(2));
scale_bilinear_result = scale(orig_img,'bilinear',scale_params(1),scale_params(2));
subplot(1,2,1),imshow(scale_nn_result);title('nn result');
subplot(1,2,2),imshow(scale_bilinear_result);title('bilinear result');

trans_nn_result = translate(orig_img,'nn',trans_params(1),trans_params(2));
trans_bilinear_result = translate(orig_img,'bilinear',trans_params(1),trans_params(2));
subplot(1,2,1),imshow(trans_nn_result);title('nn result');
subplot(1,2,2),imshow(trans_bilinear_result);title('bilinear result');

rotate_nn_result = imrotate(orig_img,45,'nearest');
rotate_bilinear_result = imrotate(orig_img,45,'bilinear');
subplot(1,2,1),imshow(rotate_nn_result);title('nn result');
subplot(1,2,2),imshow(rotate_bilinear_result);title('bilinear result');