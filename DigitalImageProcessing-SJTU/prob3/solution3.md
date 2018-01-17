#<center>Digital Image Processing</center>

<h6 align='center'>BB1603391 116033910045 修宇亮

##Problem 3 Requirement
![](http://xiublog.qiniudn.com/2016-10-13-16%3A18%3A40.jpg)

##Problem 3 solution

###matlab code
```matlab
orig_img = imread('orig.tif');  
subplot(2,3,1),imshow(orig_img);title('Original');
 %将灰度图像的二维不连续Fourier 变换的零频率成分移到频谱的中心
s=fftshift(fft2(orig_img));
[M,N]=size(s);                      %分别返回s的行数到M中，列数到N中
n1=floor(M/2);                       %对M/2进行取整
n2=floor(N/2);                       %对N/2进行取整
%ILPF滤波（程序中以d0=50为例）

d0=[10,30,60,160,460];                               %初始化d0
for d0_id=1:5
    h = zeros(size(s));
    for i=1:M
        for j=1:N
            d=sqrt((i-n1)^2+(j-n2)^2);    %点（i,j）到傅立叶变换中心的距离
%   pick any H function as H(u,v)
%             h(i,j) = 1/(1 + (d/d0(d0_id))^(2*2));   %blpf
%             h(i,j) = 1/(1 + (d0(d0_id)/d)^(2*2));   %bhpf
%             h(i,j)=1-1*exp(-1/2*(d^2/d0(d0_id)^2)); %ghpf
%             h(i,j)=1*exp(-1/2*(d^2/d0(d0_id)^2)); %glpf
%   ilpf
%             if d<=d0(d0_id)                      %点（i,j）在通带内的情况
%                 h(i,j)=1;                      %通带变换函数
%             else                          %点（i,j）在阻带内的情况
%                 h(i,j)=0;                      %阻带变换函数
%             end  
%   ihpf
%             if d>=d0(d0_id)                      %点（i,j）在通带内的情况
%                 h(i,j)=1;                      %通带变换函数
%             else                          %点（i,j）在阻带内的情况
%                 h(i,j)=0;                      %阻带变换函数
%             end 
        end
    end
    s_=h.*double(s);                      %ILPF滤波后的频域表示
    s_=ifftshift(s_);                       %对s进行反FFT移动
    %对s进行二维反离散的Fourier变换后，取复数的实部转化为无符号8位整数
    s_=uint8(real(ifft2(s_)));  
    out_name = sprintf('BHPF（d0=%d)',d0(d0_id));
    subplot(2,3,d0_id+1),imshow(s_); title(out_name);  %显示ILPF滤波后的图像
end

```
##Result
### Ideal Lowpass Filter
![](http://xiublog.qiniudn.com/2016-10-14-ilpf.jpg)

### Butterworth Lowpass Filter
![](http://xiublog.qiniudn.com/2016-10-14-blpf.jpg)

### Gaussian Lowpass Filter
![](http://xiublog.qiniudn.com/2016-10-14-glpf.jpg)

### Ideal Highpass Filter
![](http://xiublog.qiniudn.com/2016-10-14-ihpf.jpg)

### Butterworth Highpass Filter
![](http://xiublog.qiniudn.com/2016-10-14-bhpf.jpg)
### Gaussian Highpass Filter
![](http://xiublog.qiniudn.com/2016-10-14-ghpf.jpg)



