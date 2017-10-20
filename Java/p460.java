import java.util.Arrays;

public class p460 {

	private static void solve() {
		int N = 10000;
		
		int[][] co = new int[100000][];
		int p = 0;
		for (int i = 0; i <= N / 2; i++) {
			for (int j = 1; j <= N / 2; j++) {
				if (Math.abs(Math.sqrt((N / 2 - i) * (N / 2 - i) + j * j) - N / 2) <= 0.5) {
					co[p++] = new int[]{i, j};
				}
			}
		}
		
		int n = p;
		double[] td = new double[n];
		Arrays.fill(td, Double.POSITIVE_INFINITY);
		Heap q = new Heap(n);
		q.add(0, 0);
		td[0] = 0;
		
		boolean[] ved = new boolean[n];
		while (q.size() > 0) {
			int cur = q.argmin();
			if (cur == p - 1) {
				tr(td[cur] * 2);
				return;
			}
			q.remove(cur);
			int bx = co[cur][0], by = co[cur][1];
			ved[cur] = true;
			
			for (int i = 0; i < n; i++) {
				if (i != cur && !ved[i]) {
					int x = co[i][0], y = co[i][1];
					double v = y == by ? y : (y - by) / (Math.log(y) - Math.log(by));
					double nd = td[cur] + Math.sqrt((bx - x) * (bx - x) + (by - y) * (by - y)) / v;
					
					if (nd < td[i]) {
						td[i] = nd;
						q.update(i, nd);
					}
				}
			}
		}
	}
	public static void main(String[] args) {
		solve();
	}
	private static void tr(Object... o) {
		System.out.println(Arrays.deepToString(o));
	}
	
	private static class Heap {
		public double[] a;
		public int[] map;
		private int[] imap;
		public int n;
		public int pos;
		public static double INF = Double.POSITIVE_INFINITY;
		
		public Heap(int m) {
			n = Integer.highestOneBit((m + 1) << 1);
			a = new double[n];
			map = new int[n];
			imap = new int[n];
			Arrays.fill(a, INF);
			Arrays.fill(map, -1);
			Arrays.fill(imap, -1);
			pos = 1;
		}
		
		public double add(int ind, double x) {
			int ret = imap[ind];
			if (imap[ind] < 0) {
				a[pos] = x;
				map[pos] = ind;
				imap[ind] = pos;
				pos++;
				up(pos - 1);
			}
			return ret != -1 ? a[ret] : x;
		}
		
		public double update(int ind, double x) {
			int ret = imap[ind];
			if (imap[ind] < 0) {
				a[pos] = x;
				map[pos] = ind;
				imap[ind] = pos;
				pos++;
				up(pos - 1);
			} else {
				a[ret] = x;
				up(ret);
				down(ret);
			}
			return x;
		}
		
		public double remove(int ind) {
			if (pos == 1) return INF;
			if (imap[ind] == -1) return INF;
			
			pos--;
			int rem = imap[ind];
			double ret = a[rem];
			map[rem] = map[pos];
			imap[map[pos]] = rem;
			imap[ind] = -1;
			a[rem] = a[pos];
			a[pos] = INF;
			map[pos] = -1;
			
			up(rem);
			down(rem);
			return ret;
		}
		
		public double min() { return a[1]; }
		public int argmin() { return map[1]; }
		public int size() { return pos - 1; }
		
		private void up(int cur) {
			for (int c = cur, p = c >>> 1; p >= 1 && a[p] > a[c]; c >>>= 1, p >>>= 1) {
				double d = a[p]; a[p] = a[c]; a[c] = d;
				int e = imap[map[p]]; imap[map[p]] = imap[map[c]]; imap[map[c]] = e;
				e = map[p]; map[p] = map[c]; map[c] = e;
			}
		}
		
		private void down(int cur) {
			for (int c = cur; 2 * c < pos; ) {
				int b = a[2 * c] < a[2 * c + 1] ? 2 * c : 2 * c + 1;
				if (a[b] < a[c]) {
					double d = a[c]; a[c] = a[b]; a[b] = d;
					int e = imap[map[c]]; imap[map[c]] = imap[map[b]]; imap[map[b]] = e;
					
					e = map[c]; map[c] = map[b]; map[b] = e;
					c = b;
				} else break;
			}
		}
	}
}

