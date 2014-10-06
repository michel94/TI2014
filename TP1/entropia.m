function ent = entropia(P, A)
    ent = 0;
    P = P(:);
    %P = roundToNearest(P, A);
    total = sum(length(P)); 
    
    for i=1:length(A)
       f = sum(P == A(i));
       if f > 0
          prob = f/total;
          ent = ent + prob * log2(prob);
       end
    end
    ent = -ent;
    
end
