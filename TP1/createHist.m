function count = createHist(P, A)
    % Mostra e devolve o histograma de ocorr?ncia dos s?mbolos
    % do alfabeto A na fonte de informa??o P

    count = zeros(size(A));

    for i=1:length(A)
       f = length(find(P == A(i)));
       count(i) = f;
    end

    waitfor(bar(count));
end
