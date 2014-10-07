function count = hist(P, A)
    % Conta o numero de ocorrencias em P
    % dos simbolos do alfabeto A

    count = zeros(size(A));

    for i=1:length(A)
       f = length(find(P(:) == A(i)));
       count(i) = f;
    end
end