dim = 6;
num = 10000;
X = rand(num,dim)*100;
Y= sum(X,2)
% Y = rand(num,1)*10;
[b, bint,r,rint,stats]=regress(Y,X);
b
loss = sum(X*b-Y)