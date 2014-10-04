function v = bs(v, L, s, e)
    m = floor((e - s) / 2 + s);
    fprintf('s: %d e: %d\n', s, e);
    if v < L(1) | v > L(length(L))
        return
    end
    if e - s <= 1
        if s < length(L)
            if abs(L(s+1) - v) < abs(L(s) - v)
                v = L(s+1);
            else
                v = L(s);
            end
        else
            v = L(s);
        end
        return;
    end
    if v > L(m)
        v = bs(v, L, m, e);
        return;
    elseif v < L(m)
        v = bs(v, L, s, m);
        return;
    end

end
