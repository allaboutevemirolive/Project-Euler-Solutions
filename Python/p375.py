# S_n is a cyclic sequence with period 6308948
# Given n <= 6308948, we can get a special map f.
# f(i) = [0, n - 1] for every 1 <= i <= n.
# Sort n
# Pick smallest element S_i_0 * f(i_0) = [0, n - 1], which means
# i_0 is in the segment [0, n - 1]. S_i_0 contributes
# (i_0 - 0 + 1)(n - 1 - i_0 + 1) times in M(n). Since i_0 is chosen,
# now we need to split [0, n - 1] into the following segments:
# [0, i_0 - 1] and [i_0 + 1, n - 1]
# Now pdate the map by f(j) = [0, i_0 - 1] for 0 <= j <= i_0 - 1
# f(j) = [i_0 + 1, n - 1] for i_0 + 1 <= j <= n - 1.
# Keep doing this
#If we pick the k-th smallest element S_i_k * f(i_k) = [a_k, b_k],
# add S_i_k(i_k - a_k + 1)(b_k - i_k + 1) to M(n).
# Update the map f by f(j) = [a_k, i_k - 1] for a_k <= j <= i_k - 1,
# f(j) = [i_k + 1, b_k] for i_k + 1 <= k <= b_k.
# Consider n > 6308948. One of the issues I had was to find what to do then.
# But I found out that the smallest element S_i_0 can break long cyclic
# sequences into several noncyclic sequences. So we need to consider
# the following four sums:
# 1. head sum
# 2. middle sum with repetition
# 3. tail sum
# 4. smallest element contribution
# For 1, 2, 3, it's done. For 4, we consider the number of all possible
# (i, j) pairs, and then we subtract all bad pairs between 2 successively
# small elements (also 2 boundary cases).


import sys

class PseudoRandomNumberGenerator():
    def get_period(self):
        return 6308948

    def generate(self, n):
        result = []
        s, count = 290797, 0
        visited = {s: count}
        while count < n:
            s, count = (s**2) % 50515093, count + 1
            if s in visited:
                break
            result.append(s)
            visited[s] = count
        return result

class SegmentManager():
    def __init__(self, length):
        self.segment_list_map = {}
        for i in range(length):
            self.segment_list_map[i] = (0, length - 1)

    def find(self, pos):
        return self.segment_list_map[pos]

    def split(self, segment, pos):
        begin, end = segment
        for i in range(begin, pos):
            self.segment_list_map[i] = (begin, pos - 1)
        for i in range(pos + 1, end + 1):
            self.segment_list_map[i] = (pos + 1, end)

class Problem():
    def solve(self):
        for n in [10, 10000, 2000000000]:
            print(n, "=>", self.get(n))

    def get(self, n):
        generator = PseudoRandomNumberGenerator()
        period = generator.get_period()
        number_list = generator.generate(n)
        return self.__get_periodic_list(number_list, period, n)

    def __get_periodic_list(self, number_list, period, n):
        min_pos = self.__get_min_element_pos(number_list)
        repeated_count = (n - min_pos - 1) // period

        head_length = min_pos
        tail_length = n - (min_pos + repeated_count * period + 1)
        min_element_interval_count = n * (n + 1) // 2 \
                - head_length * (head_length + 1) // 2 \
                - repeated_count * (period - 1) * period // 2 \
                - tail_length * (tail_length + 1) // 2

        head_sum = self.__get_nonperiodic_list(number_list[0:min_pos])

        repeated_sum = self.__get_nonperiodic_list(number_list[min_pos+1:period] + number_list[0:min_pos]) if repeated_count > 0 else 0
        
        tail_n = n % period
        tail_list = number_list[min_pos + 1:tail_n] if tail_n > min_pos else number_list[min_pos + 1:] + number_list[:tail_n]
        tail_sum = self.__get_nonperiodic_list(tail_list)

        total_sum = min_element_interval_count * number_list[min_pos] \
                + head_sum \
                + repeated_sum * repeated_count \
                + tail_sum
        return total_sum

    def __get_nonperiodic_list(self, number_list):
        number_count = len(number_list)
        sorted_list = sorted([(number_list[i], i) for i in range(number_count)])
        result = 0
        manager = SegmentManager(number_count)
        for i in range(number_count):
            number, pos = sorted_list[i]
            segment = manager.find(pos)
            manager.split(segment, pos)
            begin, end = segment
            result += number * (pos - begin + 1) * (end - pos + 1)
        return result

    def __get_min_element_pos(self, number_list):
        pos = 0
        min_so_far = number_list[0]
        for i in range(1, len(number_list)):
            if number_list[i] < min_so_far:
                pos = i
                min_so_far = number_list[i]
        return pos

def main():
    problem = Problem()
    problem.solve()

if __name__ == '__main__':
    sys.exit(main())