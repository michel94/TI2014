function ent = entropia(P, A)
    % Calcula a entropia, ou seja, o numero
    % medio de bits minimo para os simbolos de A
    % na codificao da fonte de informacao P
    
    s = size(A);
    
    if(s(1) == 1)
        A = transpose(A);
    end
        
    s = size(A);
    ent = 0;
    total = size(P);
    total = total(1);

    for i=1:1:s(1)
        x = A(i,:);
        if(s(2) > 1)
            [~, t] = ismember(P, x, 'rows');
            f = sum(t);
        else
            f = length(find(P == x));
        end
        
        if f > 0
            prob = f/total;
            ent = ent + prob * log2(prob);
        end
    end
    
    ent = -ent;
    
end