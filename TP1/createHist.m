function count = createHist(P, A)
    % Mostra e devolve o histograma de ocorr?ncia dos s?mbolos
    % do alfabeto A na fonte de informa??o P
    
    count = hist(P, A);

    waitfor(bar(count));
end
