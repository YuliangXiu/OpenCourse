function [x y] = clockwise_order(x,y)
    cx = mean(x);
    cy = mean(y);
    a = atan2(y - cy, x - cx);
    [~, order] = sort(a);
    x = x(order);
    y = y(order);
end