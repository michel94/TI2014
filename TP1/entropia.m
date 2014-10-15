function ent = entropia(P, A)
    % Calcula a entropia, ou seja, o numero
    % medio de bits minimo para os simbolos de A
    % na codificao da fonte de informacao P

    s = size(A);

    if (s(1) == 1)
        A = transpose(A);
        s = size(A);
    end

    ent = 0;
    total = length(P);
    
    alf = intersect(unique(P, 'rows'), A, 'rows');
    h = size(alf);
    h = h(1);

    
    for i=1:h
        x = alf(i, :);

        if (s(2) > 1)
            %[~, t] = ismember(P, x, 'rows');
            %f = sum(t);
            
            f = sum(all(bsxfun(@eq, x, P),2)); %sum(ismember(P, x,'rows')); 
        else
            f = length(find(P == x));
        end

        if f > 0
            prob = f / total;
            ent = ent + (prob * log2(prob));
        end
    end

    ent = -ent;
end
