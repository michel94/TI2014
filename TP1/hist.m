function count = hist(P, A)
    % Conta o número de ocorrências em P
    % dos símbolos do alfabeto A

    count = zeros(size(A));

    for i=1:length(A)
       f = length(find(P(:) == A(i)));
       count(i) = f;
    end
    
end