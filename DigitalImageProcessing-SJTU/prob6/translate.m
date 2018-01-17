function trans_result = translate(input,type,tx,ty)
    [M,N] = size(input);
    [trans_M,trans_N] = deal(ceil(M+2*abs(ty)),ceil(N+2*abs(tx)));
    trans_result = zeros(trans_M,trans_N);
    input_init = zeros(trans_M,trans_N);
    for m=1:M
        for n=1:N
            input_init(m+round(abs(ty)),n+round(abs(tx))) = input(m,n);
        end
    end
    if tx == fix(tx) || ty == fix(tx)
        type = 'nn';
    end
        
    
    switch type
        case 'nn'
            for m=1:trans_M
                for n=1:trans_N
                    trans_result(m,n) = input_init(max(1,min(trans_M,m-round(ty))),max(1,min(trans_N,n-round(tx))));
                end
            end    
        case 'bilinear'          
            for m=1:trans_M
                for n=1:trans_N
                    trans_result(m,n) = bilinear(input_init,m,n,'trans',containers.Map({'tx','ty'},{tx,ty}));
                end
            end 
    end
    
    trans_result = uint8(trans_result);
end
