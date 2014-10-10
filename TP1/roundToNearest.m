function P = roundToNearest(P, L)
    % Arrendonda os valores de P para o valor mais proximo
    % do alfabeto A com recurso a pesquisa binaria.

    for i=1:length(P)
        if P(i) >= L(1) && P(i) <= L(length(L))
            P(i) = binarySearch(P(i), L, 1, length(L));
        end
    end
end
