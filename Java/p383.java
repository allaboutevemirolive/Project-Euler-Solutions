import java.math.BigDecimal;
import java.util.*;

/**
 * Created by aa on 24/01/17.
 */
public class p383 {
    private Map<Integer, Intervals383> mapI = new HashMap<Integer, Intervals383>();
    private List<Integer> N_5;
    private long N;

    p383 (long N) {
        this.N = N;
        N_5 = getN_5(N);
        initMapI(N_5.size());
    }

    public void p383() {
        System.out.println("t5(" + N + ") = " + f383(N_5));
    }

    public long f383(List<Integer> n_5) {
        long count = 0;
        long prefix = 0;
        int deg = n_5.size();  // next power = great than our
        Intervals383 interval;
        int shift = 0;
        for (Integer digit : n_5) {
            int i = 0;
            interval = mapI.get(deg);
            shift = (2 * getS5(prefix) - getS5(2 * prefix)) / 4;
            for (i = 0; i < digit; i++) {
                if (i < 2) {
                    count += interval.structure.get(i).getShiftedInterval(shift).getCount();
                } else if (i == 2) {
                    IIntervalDeltas currentInterval = interval.structure.get(2);
                    if (currentInterval instanceof CenterIntervalDeltas) {
                        CenterIntervalDeltas centerInterval = (CenterIntervalDeltas) currentInterval;
                        count += centerInterval.centerDown.getShiftedInterval(shift).getCount();
                        shift = (2 * getS5(prefix) + 1 - getS5(2 * prefix + 1)) / 4;
                        count += centerInterval.centerUp.getShiftedInterval(shift).getCount();
                    }
                } else // i == 3
                {
                    count += interval.structure.get(i).getShiftedInterval(shift).getCount();
                }
            }
            prefix *= 5;
            prefix += digit;
            deg--;
        }
        return count;
    }

    public static List<Integer> getN_5(long N) {
        List<Integer> ret = new ArrayList<Integer>();
        BigDecimal NN = new BigDecimal(N);
        BigDecimal five = new BigDecimal(5);
        BigDecimal[] res;
        while (NN.longValue() > 0) {
            res = NN.divideAndRemainder(five);
            ret.add(0, res[1].intValue());
            NN = res[0];
        }
        return ret;
    }

    public static int getS5(long N) {
        int res = 0;
        for (Integer i : getN_5(N)) {
            res += i;
        }
        return res;
    }

    public interface IIntervalDeltas {
        public int getDeg();

        public long getCount();

        public Map<Integer, Long> getMap();

        public IntervalDeltas getShiftedInterval(int n);
    }

    public class IntervalDeltas implements IIntervalDeltas {
        private int deg; // 5^deg = length of the interval
        private Map<Integer, Long> map = new HashMap<Integer, Long>();
        //Integer = delta Long = #i | with this delta
        private long count = 0;

        IntervalDeltas(int d, Map<Integer, Long> m) {
            deg = d;
            map = m;
            for (Integer i : map.keySet()) {
                count += map.get(i);
            }
        }

        public int getDeg() {
            return deg;
        }

        public long getCount() {
            return count;
        }

        public Map<Integer, Long> getMap() {
            return map;
        }

        public Map<Integer, Long> getShiftedMap(int n) {
            Map<Integer, Long> shiftedMap = new HashMap<Integer, Long>();
            for (Integer i : map.keySet()) {
                if (i > n)
                    shiftedMap.put(i - n, map.get(i));
            }
            return shiftedMap;
        }

        public IntervalDeltas getShiftedInterval(int n) {
            Map<Integer, Long> newShiftedMap = new HashMap<Integer,
                    Long>(getShiftedMap(n));
            return new IntervalDeltas(deg, newShiftedMap);
        }
    }

    public class CenterIntervalDeltas extends IntervalDeltas
            implements IIntervalDeltas {
        IIntervalDeltas centerDown;
        IIntervalDeltas centerUp;

        CenterIntervalDeltas(int d, IIntervalDeltas cD, IIntervalDeltas cU) {
            super(d, mergeTwoIntervalsDeltas(cD, cU).getMap());
            this.centerDown = cD;
            this.centerUp = cU;
        }
    }

    public class Intervals383 {
        public int deg;
        IIntervalDeltas intervalDeltas;
        // 5 intervals
        List<IIntervalDeltas> structure = new ArrayList<IIntervalDeltas>();

        public Intervals383(int d, IIntervalDeltas zi, IIntervalDeltas fi,
                            IIntervalDeltas ciD, IIntervalDeltas ciU,
                            IIntervalDeltas ti, IIntervalDeltas foi) {
            deg = d;
            structure.add(zi);
            structure.add(fi);
            structure.add(new CenterIntervalDeltas(d - 1, ciD, ciU));
            structure.add(ti);
            structure.add(foi);
            initIntervalDeltas();
        }

        public long getT5() {
            return intervalDeltas.getCount();
        }

        private void initIntervalDeltas() {
            for (IIntervalDeltas one : this.structure) {
                intervalDeltas = mergeTwoIntervalsDeltas(intervalDeltas, one);
            }
        }
    }

    private IIntervalDeltas mergeTwoIntervalsDeltas(IIntervalDeltas one,
                                                    IIntervalDeltas two) {
        if (one == null)
            return two;
        if (two == null)
            return one;
        else {
            Map<Integer, Long> res = new HashMap<Integer, Long>();
            int deg = Math.max(one.getDeg(), two.getDeg());
            Long count1;
            Long count2;
            Set<Integer> set = new HashSet<Integer>(one.getMap().keySet());
            for (Integer i : two.getMap().keySet()) {
                set.add(i);
            }
            for (Integer d : set) {
                count1 = one.getMap().get(d);
                count2 = two.getMap().get(d);
                if (count1 != null && count2 != null)
                    res.put(d, count1 + count2);
                else if (count1 != null && count2 == null)
                    res.put(d, count1);
                else if (count1 == null && count2 != null)
                    res.put(d, count2);
                else {
                    //do nothing
                }
            }
            return new IntervalDeltas(deg, res);
        }
    }

    private IntervalDeltas changeLastInterval(int newDeg, IIntervalDeltas last) {
        Map<Integer, Long> newMap = last.getMap();
        if (newMap.containsKey(newDeg - 2)) {
            long n = last.getMap().get(newDeg - 2);
            newMap.remove(newDeg - 2);
            if (n > 1) {
                newMap.put(newDeg - 2, n - 1);
            }
            newMap.put(newDeg, 1L);
        } else {
            newMap.put(newDeg, 1L);
        }
        return new IntervalDeltas(last.getDeg(), newMap);
    }

    private Intervals383 createNextInterval(Intervals383 prev) {
        IIntervalDeltas cDown =
                mergeTwoIntervalsDeltas(prev.structure.get(0), prev.structure.get(1));
        cDown = mergeTwoIntervalsDeltas(cDown, ((CenterIntervalDeltas)
                (prev.structure.get(2))).centerDown);
        IIntervalDeltas cUp =
                mergeTwoIntervalsDeltas((((CenterIntervalDeltas)
                                (prev.structure.get(2))).centerUp).getShiftedInterval(1),
                        prev.structure.get(3).getShiftedInterval(1));
        cUp = mergeTwoIntervalsDeltas(cUp,
                prev.structure.get(4).getShiftedInterval(1));
        IIntervalDeltas last = prev.intervalDeltas.getShiftedInterval(1);
        last = changeLastInterval(prev.deg + 1, last);
        Intervals383 next = new Intervals383(prev.deg + 1,
                prev.intervalDeltas,
                prev.intervalDeltas,
                cDown,
                cUp,
                prev.intervalDeltas.getShiftedInterval(1),
                last);
        return next;
    }

    public void initMapI(int n) {
        Map<Integer, Long> mapZero = new HashMap<>();
        mapZero.put(0, 0L);
        Map<Integer, Long> mapOne = new HashMap<>();
        mapOne.put(1, 1L);
        Map<Integer, Long> mapTwo = new HashMap<>();
        mapTwo.put(2, 1L);
        IntervalDeltas zero0 = new IntervalDeltas(0, mapZero);
        IntervalDeltas zero1 = new IntervalDeltas(1, mapZero);
        IntervalDeltas first0 = new IntervalDeltas(0, mapOne);
        IntervalDeltas first1 = new IntervalDeltas(1, mapOne);
        IntervalDeltas second1 = new IntervalDeltas(1, mapTwo);
        Intervals383 zeroI = new Intervals383(0, zero0, zero0, zero0, zero0, zero0, zero0);
        Intervals383 firstI = new Intervals383(1, zero0, zero0, zero0, zero0, zero0, first0);
        Intervals383 secondI = new Intervals383(2, first1, first1, zero1, zero1, zero1, second1);
        mapI.put(0, zeroI);
        mapI.put(1, firstI);
        mapI.put(2, secondI);
        for (int i = 3; i <= n; i++) {
            Intervals383 prev = mapI.get(i - 1);
            Intervals383 next = createNextInterval(prev);
            mapI.put(i, next);
        }
    }

    public static void main(String[] args) {
        long beginTime = (new Date()).getTime();

        long N = 1000000000000000000L;
        p383 p383 = new p383(N);
        p383.p383();

        long endTime = (new Date()).getTime();
        System.out.println("time = " + (endTime - beginTime) + "ms");
    }

}
