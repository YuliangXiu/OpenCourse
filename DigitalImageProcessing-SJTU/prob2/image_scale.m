function output  = image_scale(input)
    input = input - min(input(:));
    output = 255*(input/max(input(:)));
end