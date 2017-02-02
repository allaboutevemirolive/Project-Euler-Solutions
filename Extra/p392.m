%
%  Boundary conditions: x(0) = 0, y(0) = 1, x(1) = 1, y(1) = 0
%
%  y(i) = sqrt( 1.0 - x(i)^2 )
%
%  y(i)' = -x(i) / y(i)
%
%  Area = 4 * sum((x(i) - x(i-1))*y(i-1))
%
%  Area' = (y(j-1) - y(j)) - (x(j+1) - x(j))*(x(j)/y(j)) = 0
%
%  x(j+1) = x(j) + (y(j-1) - y(j))*(y(j)/x(j))
%

tic
x0 = 0;
y0 = 1;
n = 400;
delta = 0.01;
x1 = 0.02;

for jj = 1:200
    x(1) = x1 + delta;
    y(1) = sqrt(1-x(1)^2);
    
    x(2) = ((y0 - y(1))*y(1)/x(1)) + x(1);
    y(2) = sqrt(1 - x(2)^2);
    
    for ii = 3:((n/2)+1)
        x(ii) = ((y(ii-2) - y(ii-1))*y(ii-1)/x(ii-1))+x(ii-1);
        y(ii) = sqrt(1 - x(ii)^2);
    end
    
    if isreal(y(((n/2)+1)))
        x1 = x1 + delta;
    else
        delta = delta/2;
    end
end

A = (x(1) - x0)*y0;
for ii = 2:((n/2)+1)
    A = A + (x(ii) - x(ii - 1))*y(ii-1);
end
A*4
toc