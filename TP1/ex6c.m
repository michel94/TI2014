

r = zeros(7, 2);

for i=1:7
    r(i, 1) = ex6mminf(sprintf('dados/Song0%d.wav', i));
    r(i, 2) = i;
end

sortrows(r, -1);

for i=1:7
    disp(r(i, 1));
    disp(sprintf('Song0%d.wav', r(i, 2)) );
end
