function inf = mutualInf(x, y, alf)
%MUTUALINF 
%   
    x = x(:);
    y = y(:);
    z = zeros([length(x), 2]);
    for i=1:1:length(x)
        z(i, 1) = x(i);
        z(i, 2) = y(i);
    end
    z;
    
    inf = entropia(x, alf) + entropia(y, alf);
    entropia(z, getpairs(alf));
    inf  = inf - entropia(z, getpairs(alf));

end

