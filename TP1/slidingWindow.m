function [mutualInfVector] = slidingWindow(query, target, alphabet, step)
    % Desliza pelo target step by step calculando as varias entropias
    % conjuntas.

    % Chamada de exemplo do enunciado:
    %   slidingWindow([2 6 4 10 5 9 5 8 0 8],
    %                 [6 8 9 7 2 4 9 9 4 9 1 4 8 0 1 2 2 6 3 2 0 7 4 9 5 4 8 5 2 7 8 0 7 4 8 5 7 4 3 2 2 7 3 5 2 7 4 9 9 6],
    %                 0:10,
    %                 1);
    
    s = length(target) - length(query) + 1;

    mutualInfVector = zeros(1, length(1:step:s));
    for i=1:step:s
        mutualInfVector(ceil(i / step)) = mutualInf(query, target(i: i + length(query) - 1), alphabet);
    end

    mutualInfVector = transpose(mutualInfVector);
end