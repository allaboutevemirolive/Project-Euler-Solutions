/**
 * Created by aa on 25/01/17.
 *
 * Made this too complicated until I realised I was finding solutions
 * where the ellipse was not actually maximal.
 *
 * I realised that the triangle and its ellipse must be a projection of
 * an equilateral triangle with its in-circle.
 *
 * I started with an equilateral triangle with vertices at
 * (-1, √3), (-1,-√3) and (2, 0)
 *
 * Then for some angle w in range 0 through 90 degrees, and
 * ellipse axes a, b, with a^2 - b^2 = 13, the vertices are
 * (- a * cos w - a * √3 * sin w, - b * sin w + c * √3 * cos w)
 * (- a * cos w + a * √3 * sin w, - b * sin w - c * √3 * cos w)
 * ( 2 * a * cos w              , 2 * b * sin w)
 *
 * The area of the triangle is a * b * 3√3.
 *
 * If cos w = 0 or sin w = 0, there two congruent triangles, 
 * but otherwise there are 4 congruent triangles
 *
 * For those coordinates to be integral there must be integers c, s, u, v 
 * and z such that
 * cos w = 1 / √z , sin w = √3 / √z, a = u * √z, b = v * √(3 * z)
 *
 * and the area of the triangle is 9 * z * u * v.
 * 
 * Also:
 * c^2 + 3 * s^2 = z
 * u^2 - 3 * v^2 = 13 / z
 * 
 * From the second of these, either z = 1 or z = 13, and there are 3 families
 * (u, v) defined by
 * u_(r+1) = 2 * u_r + 3 * v_r
 * v_(r+1) = u_r + 2 * v_r
 * 
 * The solution z = 1 gives 2 families starting from
 * u_1 = 4
 * v_1 = 1, and
 * u_1 = 4
 * v_1 = 1
 * 
 * There's one family for z = 13, starting from u_1 = 2, v_1 = 1
 * 
 * Also if z = 1, then c = 1 and s = 0, and the largest absolute value of 
 * any coordinates is given by max(2 * u, 3 * v)
 * While if z = 13, then c = 1 and s = 0, and the largest absolute value of
 * any coordinates is given by max(7 * u, 12 * v)
 */
public class p385 {
    public static void main(String[] args) {
        maxEllipse(1000000000L);
    }

    static void maxEllipse(long n) {
        long ans = 0;
        long u = 4, v = 1, m = 18, t = m * u * v, h1 = 2 * u, h2 = 3 * v;

        while ((h1 <= n) && (h2 <= n)) {
            ans += t;
            v = u + 2 * v;
            u = h1 + h2;
            t = m * u * v;
            h1 = 2 * u;
            h2 = 3 * v;
            System.out.println("u, v, t, h1, h2\t=> " + u + ", " + v);
        }

        u = 5;
        v = 2;
        t = u * v * m;
        h1 = 2 * u;
        h2 = 3 * v;

        while ((h1 <= n) && (h2 <= n)) {
            ans += t;
            v = u + 2 * v;
            u = h1 + h2;
            t = m * u * v;
            h1 = 2 * u;
            h2 = 3 * v;
            System.out.println("u, v, t\t=> " + u + ", " + v + ", " + t);
        }

        m = 36 * 13;
        u = 2;
        v = 1;
        t = m * u * v;
        while ((7 * u <= n) && (12 * v <= n)) {
            ans += t;
            System.out.println("u, v, t\t=> " + u + ", " + v + ", " + t);
            long u1 = 2 * u + 3 * v;
            v = u + 2 * v;
            u = u1;
            t = m * u * v;
        }

        System.out.printf("For n at %d, the answer is %d", n, ans);
    }
}