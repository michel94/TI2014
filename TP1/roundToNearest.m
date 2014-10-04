function P = roundToNearest(P, L)
    
    for i=1:length(P)
        if P(i) >= L(1) & P(i) <= L(length(L))
            P(i) = bs(P(i), L, 1, length(L));
        end
    end

end
