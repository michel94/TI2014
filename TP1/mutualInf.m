function [inf] = mutualInf(X, Y, alf)
    % Calcula a informacao mutua entre X e Y.

    offset = - min(min(X), min(Y)) + 1;
    matrix = zeros(length(alf));

    for i=1:length(X)
        matrix(X(i) + offset, Y(i) + offset) = matrix(X(i) + offset, Y(i) + offset) + 1;
    end

    probConj = matrix ./ sum(sum(matrix));
    x = sum(matrix) ./ sum(sum(matrix));
    y = sum(matrix') ./ sum(sum(matrix));

    inf = calcEnt(x) + calcEnt(y) - calcEnt(probConj);
end

function [h] = calcEnt(x)
    x = nonzeros(x);
    h = -sum(x .* log2(x));
end