require 'Date'

count = 0
1901.upto(2000) do |y|
    1.upto(12) do |m|
        count += 1 if Date.civil(y, m).wday == 0
    end
end
