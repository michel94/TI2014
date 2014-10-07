function count = createHist(P, A)
    % Apresenta e devolve o histograma de ocorrencia dos simbolos
    % do alfabeto A na fonte de informacao P

    count = hist(P, A);

    waitfor(bar(count));
end
