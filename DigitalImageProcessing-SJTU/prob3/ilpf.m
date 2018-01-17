orig_img = imread('orig.tif');  
subplot(2,3,1),imshow(orig_img);title('Original');
 %���Ҷ�ͼ��Ķ�ά������Fourier �任����Ƶ�ʳɷ��Ƶ�Ƶ�׵�����
s=fftshift(fft2(orig_img));
[M,N]=size(s);                      %�ֱ𷵻�s��������M�У�������N��
n1=floor(M/2);                       %��M/2����ȡ��
n2=floor(N/2);                       %��N/2����ȡ��
%ILPF�˲�����������d0=50Ϊ����

d0=[10,30,60,160,460];                               %��ʼ��d0
for d0_id=1:5
    h = zeros(size(s));
    for i=1:M
        for j=1:N
            d=sqrt((i-n1)^2+(j-n2)^2);    %�㣨i,j��������Ҷ�任���ĵľ���
%pick any H function as H(u,v)
%             h(i,j) = 1/(1 + (d/d0(d0_id))^(2*2));   %blpf
%             h(i,j) = 1/(1 + (d0(d0_id)/d)^(2*2));   %bhpf
%             h(i,j)=1-1*exp(-1/2*(d^2/d0(d0_id)^2)); %ghpf
%             h(i,j)=1*exp(-1/2*(d^2/d0(d0_id)^2)); %glpf
%ilpf
%             if d<=d0(d0_id)                      %�㣨i,j����ͨ���ڵ����
%                 h(i,j)=1;                      %ͨ���任����
%             else                          %�㣨i,j��������ڵ����
%                 h(i,j)=0;                      %����任����
%             end  
%ihpf
%             if d>=d0(d0_id)                      %�㣨i,j����ͨ���ڵ����
%                 h(i,j)=1;                      %ͨ���任����
%             else                          %�㣨i,j��������ڵ����
%                 h(i,j)=0;                      %����任����
%             end 
        end
    end
    s_=h.*double(s);                      %ILPF�˲����Ƶ���ʾ
    s_=ifftshift(s_);                       %��s���з�FFT�ƶ�
    %��s���ж�ά����ɢ��Fourier�任��ȡ������ʵ��ת��Ϊ�޷���8λ����
    s_=uint8(real(ifft2(s_)));  
    out_name = sprintf('BHPF��d0=%d)',d0(d0_id));
    subplot(2,3,d0_id+1),imshow(s_); title(out_name);  %��ʾILPF�˲����ͼ��
end
