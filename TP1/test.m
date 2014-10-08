a = [1 2 3 5 6 7 6 9];
b = zeros(length(a)/2, 2);
for i=1:2:length(a)
    b(floor(i/2)+1, 1) = a(i);
    b(floor(i/2)+1, 2) = a(i+1);
end
b