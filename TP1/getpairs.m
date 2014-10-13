function r = getpairs(v1)
    [p,q] = meshgrid(v1, v1);
    r = [p(:) q(:)];
end