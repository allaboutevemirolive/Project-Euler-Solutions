"""
DISCLAIMER: PYTHON 2.7 CODE
---
Used explicit formulas for mean and variance from 
http://math.furman.edu/~tlewis/math340/bertsekas/chap4/sec5.pdf
"""

from fractions import Fraction

def dice(sides):
    m1 = Fraction(sum(k for k in xrange(1, sides + 1)), sides)
    m2 = Fraction(sum(k * k for k in xrange(1, sides + 1)), sides)
    return m1, m2 - m1 * m1

def throw_dice(n, x):
    en, vn = n
    ex, vx = x
    return en * ex, vx * en + ex * ex * vn

def main():
    one = (Fraction(1), Fraction(0))
    e, v = reduce(throw_dice, map(dice, [4, 6, 8, 12, 20]), one)
    print "E={}, V={}".format(float(e), float(v))

if __name__ == '__main__':
    main()