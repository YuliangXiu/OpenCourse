function [ out, revertclass ] = tofloat( in )
%TOFLOAT Convert image to floating point
%   [OUT, REVERTCLASS] = TOFLOAT(IN) converts the input image IN to
%   floating-point. If IN is a double or single image, then OUT equals IN.
%   Otherwise, OUT equals IM2SINGLE(IN). REVERTCLASS is a function handle
%   that can be used o convert back to the class of IN.
%
%   Author: Roland Bruggmann
%   Created: January 2016
%
%   Reference:
%   Rafael C. Gonzales, Richard E. Woods und Steven L. Eddins. 
%   Digital Image Processing using MATLAB(R). 2. Ed. 
%   Appendix C. P. 806. 
%   Prentice Hall, 2004. isbn: 978-0-982-08540-0.

    identity = @(x) x;
    tosingle = @im2single;

    table = {
        'uint8',   tosingle, @im2uint8
        'uint16',  tosingle, @im2uint16
        'int16',   tosingle, @im2int16
        'logical', tosingle, @logical
        'double',  identity, identity
        'single',  identity, identity
    };

    classIndex = find(strcmp(class(in),table(:,1)));

    if isempty(classIndex)
        error('');
    end

    out = table{classIndex,2}(in);
    revertclass = table{classIndex,3};

end