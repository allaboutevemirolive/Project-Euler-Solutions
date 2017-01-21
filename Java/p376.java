import java.util.TreeMap;
import java.util.TreeSet;

/**
 * Created by aa on 21/01/17.
 *
 * Using dynamic programming to iterate over pip-count. Each state includes
 * how many sides are marked on each of the 3 dice, and how many known cases
 * there are where each beats its successor.
 *
 * After that is complete, you can count the states where all sides are marked
 * and each beats its successor more than half the time. Divide the total by 3,
 * because each set was counted 3 times.
 *
 * Really fun to implement.
 */

public class p376 {

    private static final int SIDES = 6;
    private static final int HALF_CASES = SIDES * SIDES / 2;

    public class State implements Comparable<State> {
        private int aSides, bSides, cSides;
        private int aOverB, bOverC, cOverA;

        private State(int aSides, int bSides, int cSides, int aOverB, int bOverC,
                     int cOverA) {
            this.aSides = aSides;
            this.bSides = bSides;
            this.cSides = cSides;
            this.aOverB = aOverB;
            this.bOverC = bOverC;
            this.cOverA = cOverA;
        }

        private TreeSet<State> spawn() {
            TreeSet<State> states = new TreeSet<>();
            for (int a1 = aSides; a1 <= SIDES; a1++) {
                for (int b1 = bSides; b1 <= SIDES; b1++) {
                    for (int c1 = cSides; c1 <= SIDES; c1++) {
                        State s1 = new State(a1, b1, c1,
                                aOverB + (a1 - aSides) * bSides,
                                bOverC + (b1 - bSides) * cSides,
                                cOverA + (c1 - cSides) * aSides);
                        states.add(s1);
                    }
                }
            }
            return states;
        }

        private boolean isNonTransitive() {
            return (aOverB > HALF_CASES && bOverC > HALF_CASES && cOverA > HALF_CASES);
        }

        private boolean isFull() {
            return (aSides == SIDES && bSides == SIDES && cSides == SIDES);
        }

        public int compareTo(State that) {
            int result = this.aSides - that.aSides;
            if (result != 0) return result;

            result = this.bSides - that.bSides;
            if (result != 0) return result;

            result = this.cSides - that.cSides;
            if (result != 0) return result;

            result = this.aOverB - that.aOverB;
            if (result != 0) return result;
            result = this.bOverC - that.bOverC;

            if (result != 0) return result;
            result = this.cOverA - that.cOverA;


            return result;
        }
    }

    private int n;

    private p376(int n) {
        this.n = n;
    }

    private long count() {
        TreeMap<State, Long> d0 = new TreeMap<>();
        d0.put(new State(0, 0 , 0, 0, 0, 0), 1L);

        for (int i = 1; i <= n; i++) {

            TreeMap<State, Long> d1 = new TreeMap<>();
            for (State s0 : d0.keySet()) {
                long c0 = d0.get(s0);

                for (State s1 : s0.spawn()) {
                    Long c1 = d1.get(s1);

                    if (c1 == null) c1 = 0L;
                    c1 += c0;
                    d1.put(s1, c1);
                }
            }
            d0 = d1;
            System.out.println("After " + i + " iterations, there are " + d0.size() + " states.");
        }

        long result = 0;
        for (State s : d0.keySet()) {
            if (s.isFull() && s.isNonTransitive()) {
                result += d0.get(s);
            }
        }

        System.out.println("Raw count => " + result);
        result /= 3;
        System.out.println("Count => " + result);

        return result;
    }

    public static void main(String[] args) {
        p376 p = new p376(30);
        System.out.println(p.count());
    }
}
