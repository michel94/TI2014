function ent = entropia(P, A)
    % Calcula a entropia, ou seja, o numero
    % medio de bits minimo na codificao de P

    ent = 0;
    P = P(:);
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
