function scale_result = scale(input,type,cx,cy)
    [M,N] = size(input);
    [scale_M,scale_N] = deal(ceil(M*cy),ceil(N*cx));
    scale_result = zeros(scale_M,scale_N);
    
    for m=1:scale_M
        for n=1:scale_N
            switch type
                case 'nn'
                    recov_m = min(M,max(1,round(m/cy)));
                    recov_n = min(N,max(1,round(n/cx)));
                    scale_result(m,n) = input(recov_m,recov_n);
                case 'bilinear'
                    scale_result(m,n) = bilinear(input,m,n,'scale',containers.Map({'cx','cy'},{cx,cy}));
            end
        end
    end
    
    scale_result = uint8(scale_result);
end
