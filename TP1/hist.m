function count = hist(P, A)
    % Conta o numero de ocorrencias em P
    % dos simbolos do alfabeto A.

    s = size(A);

    if (s(1) == 1)
        A = transpose(A);
        s = size(A);
    end

    count = zeros(1, s(1));

    for i=1:s(1)
        x = A(i, :);

        if (s(2) > 1)
            [~, t] = ismember(P, x, 'rows');
            f = sum(t);
            count(i) = f;
        else
            count(i) = length(find(P == x));
        end
    end
end