function count = hist(P, A)
    % Conta o número de ocorrências em P
    % dos símbolos do alfabeto A

    
    s = size(A);
    
    if(s(1) == 1)
        A = transpose(A);
    end
        
    s = size(A);
    
    count = zeros(1, s(1));

    for i=1:1:s(1)
        %i
        x = A(i,:);
        if(s(2) > 1)
            [~, t] = ismember(P, x, 'rows');
            f = sum(t)
            count(i) = f;
        else
            count(i) = length(find(P == x));
        %fprintf('%d, %d: %d\n', A(i), A(i+1), count(i));
       
    end
    
end