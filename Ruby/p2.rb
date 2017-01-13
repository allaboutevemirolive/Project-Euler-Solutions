sum = 0
n1, n2 = 1, 2
sequence = []
sequence.push(n1, n2)
next_number = n1 + n2
begin
	sequence << next_number
	n1 = n2
	n2 = next_number
	next_number = n1 + n2
end while next_number < 4000000

sequence.each do | number |
	if (number % 2 == 0)
		sum += number
	end
end
puts sum.to_s