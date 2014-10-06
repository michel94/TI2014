function count = createHist(P, A)
    
    count = zeros(size(A));

    for i=1:length(A)
       f = length(find(P(:) == A(i)));
       count(i) = f;
    end
    
end