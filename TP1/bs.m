function value = bs(value, L, low, high)
    % Efetua pesquisa binaria do valor 'v' no vetor 'L'
    % entre 'low' e 'high'

    m = floor((high - low) / 2 + low);

    if value < L(1) || value > L(length(L))
        return;
    end

    if high - low <= 1
        if low < length(L)
            if abs(L(low + 1) - value) < abs(L(low) - value)
                value = L(low+1);
            else
                value = L(low);
            end
        else
            value = L(low);
        end

        return;
    end

    if value > L(m)
        value = bs(value, L, m, high);
        return;
    elseif value < L(m)
        value = bs(value, L, low, m);
        return;
    end
end
