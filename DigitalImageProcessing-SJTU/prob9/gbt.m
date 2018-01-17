function T=gbt(x)

[M,N]=size(x);
T=x(randi(M-1),randi(N-1));
T0=0;

mean1=sum(sum(x(x<=T)))/sum(sum(x<=T));
mean2=sum(sum(x(x>T)))/sum(sum(x>T));

while abs(T-T0)>10^-8
    T0=T;
    T=(mean1+mean2)/2;
    mean1=sum(sum(x(x<=T)))/sum(sum(x<=T));
    mean2=sum(sum(x(x>T)))/sum(sum(x>T));
end

 
 