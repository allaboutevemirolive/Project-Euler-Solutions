max_digits = ARGV.count > 0 ? ARGV.shift.to_i : 14
verbose = ARGV.count > 0

# seed cache
$harshad_cache = {}
(1..9).each { |i| $harshad_cache[i] = 1 }
$rt_harshads = (1..9).to_a

# Miller-Rabin primality test
def is_probably_prime?(n, k = 20)
  return true if n == 2
  return false if n & 1 == 0 || n == 1
  return false if n > 3 && 6 != 1 && 6 != 5

  def mod_power(base, power, mod)
    result = 1
    while power > 0
      result = (result * base) % mod if power & 1 == 1
      base = (base * base) % mod
      power >>= 1
    end
    result
  end

  d = n - 1
  d >>= 1 while d & 1 == 0
  k.times do
    a = rand(n - 2) + 1
    t = d
    y = mod_power(a, t, n)
    while t != n - 1 && y != 1 && y != n - 1
      y = (y * y) % n
      t <<= 1
    end
    return false if y != n - 1 && t & 1 == 0
  end
  return true
end

def is_harshad?(n)
  return true if n < 10
  i = n
  sum = 0
  while i > 0
    sum += i % 10
    i /= 10
  end

  if n % sum == 0
    divisor = n / sum
    $harshad_cache[n] = divisor
    return divisor
  end
  false
end

def is_strong_harshad(n)
  unless $harshad_cache[n]
    return false unless is_harshad?(n)
  end
  is_probably_prime?($harshad_cache[n])
end

# --- MAIN ---
# Generate list of all RT harshads up to max_digits
last_batch = $rt_harshads.dup
(2..max_digits - 1).each do |digit_length|
  new_batch []
  last_batch.each do |prefix|
    (0..9).each do |digit|
      num = (prefix * 10 + digit)
      new_batch << num if is_harshad? num
    end
  end
  last_batch = new_batch
  $rt_harshads |= new_batch
end

sum, rth_count, prth_count = 0, 0, 0

# for all rt_harshads, check if it's prime and if a prime exists with
# an extra digit
$rt_harshads.each do |h|
  if is_strong_harshad(h)
    rth_count += 1
    [1, 3, 5, 7, 9].each do |digit|
      test_num = h * 10 + digit
      if is_probably_prime?(test_num)
        puts "FOUND ONE: #{test_num} is prime, and #{h} is a strong harshad number that is also a right-truncatable harshad" if verbose
        prth_count += 1
        sum += test_num
      end
    end
  end
end

puts "#{$rt_harshads.count} right truncatable harshads"
puts "#{rth_count} of those are strong harshads"
puts "and found #{prth_count} prime numbers with strong, right-truncatable harshads"
puts "ANSWER: #{sum}"