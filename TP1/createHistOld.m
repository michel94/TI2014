function y = createHist2(P, A)
	P = sort(P);
	
	y = [];
	i = 1;
	while i <= length(P)
		s = 1;
		j = i+1;
		if j <= length(P)
			while P(i,:) == P(j,:)
				%disp(i + ' ' + j);
				s=s+1;
				j=j+1;
				i=i+1;
				if j>length(P)
					break;
				end
			end
		end
		%P(i,:) == A
		y = [y s];
		%end

		i=i+1;
		
	end
	bar(y);

end
