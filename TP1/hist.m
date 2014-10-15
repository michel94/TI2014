function count = hist(P, A)
    % Conta o numero de ocorrencias em P
    % dos simbolos do alfabeto A.

    s = size(A);

    if (s(1) == 1)
        A = transpose(A);
        s = size(A);
    end

    count = zeros(1, s(1));
    
	alf = intersect(unique(P, 'rows'), A, 'rows');
	h = size(alf);
	h = h(1);

    for i=1:h
        x = alf(i, :);

        if (s(2) > 1)
            count(i) = sum(all(bsxfun(@eq, x, P),2));
        else
            count(i) = length(find(P == x));
        end
    end
end