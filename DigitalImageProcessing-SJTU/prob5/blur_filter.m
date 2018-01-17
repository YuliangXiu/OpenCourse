function H = blur_filter(F,a,b,T)
    [M,N] = size(F);
    H = F;
    for U=1:M
        for V=1:N
            puab = pi*(U*a+V*b);
            H(U,V) = T*sin(puab).*exp(-j*puab)./puab;
        end
    end
end