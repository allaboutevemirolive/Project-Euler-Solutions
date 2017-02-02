package com.company;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.*;
import java.util.*;
import java.util.List;

/**
 * Created by aa on 02/02/17.
 * Had to rotate vectors.
 * TODO: do this with transforming matrices instead of rotating vectors
 */
@SuppressWarnings("serial")
public class p395 extends JFrame {
    public static void main(String[] args) {
        new p395();
    }

    private p395() {
        setSize(1000, 1000);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        add(new DrawStuff(), BorderLayout.CENTER);
        setVisible(true);
    }

    private double A2 = Math.atan(-23 / 14.), A1 = Math.atan(53 / 21.);
    private double M2 = Math.asin(4 / 5.), M1 = Math.asin(3 / 5.);
    private double L2 = Math.sqrt(29 / 25.), L1 = Math.sqrt(13 / 10.);

    private class Square {
        Graphics g;
        double theta, x, y, s;

        private Square(Graphics G, double a, double b, double c, double e) {
            g = G;
            theta = a;
            x = b;
            y = c;
            s = e;
        }

        private void print() {
            double D = s / Math.sqrt(2), COS = D * Math.cos(Math.PI / 4 + theta),
                    SIN = D * Math.sin(Math.PI / 4 + theta);

            double[] xtmp = new double[] {x + COS, x - SIN, x - COS, x + SIN};
            double[] ytmp = new double[] {y - SIN, y - COS, y + SIN, y + COS};
            int[] X = new int[4], Y = new int[4];

            for (int i = 0; i < 4; i++) {
                X[i] = (int) xtmp[i];
                Y[i] = (int) ytmp[i];
            }
            g.drawPolygon(X, Y, 4);
        }

        private Square getSide3() {
            double nA2 = theta - M2, R2 = s * L2;
            double nX2 = x + R2 * Math.cos(-theta + A2);
            double nY2 = y + R2 * Math.sin(-theta + A2);

            return new Square(g, nA2, nX2, nY2, s * 3 / 5);
        }

        private Square getSide4() {
            double nA1 = theta + M1, R1 = s * L1;
            double nX1 = x - R1 * Math.cos(theta - A1), nY1 = y + R1 * Math.sin(theta - A1);

            return new Square(g, nA1, nX1, nY1, s * 4 / 5);
        }
    }

    private ArrayList<Comparator<Square>> C = new ArrayList<>();

    private class DrawStuff extends JPanel {
        List<Square> SQUARES = new ArrayList<>();

        public void paint(Graphics g) {
            double unit = 150;
            Square I = new Square(g, 0, 600, 600, unit);

            C.add((A, B) -> A.y < B.y ? 1 : -1);

            C.add((A, B) -> A.y > B.y ? 1 : -1);

            C.add((A, B) -> A.x < B.x ? 1 : -1);

            C.add((A, B) -> A.x > B.x ? 1 : -1);

            double LIMITS[] = new double[4];

            for (int ci = 0; ci < 4; ci++) {
                drawSquare(I, 0);

                for (int i = 0; i < 100; i++) {
                    ArrayList<Square> newSQUARES = new ArrayList<>();
                    for (Square s : SQUARES) {
                        newSQUARES.add(s.getSide3());
                        newSQUARES.add(s.getSide4());

                        s.print();
                    }

                    newSQUARES.sort(C.get(ci));
                    SQUARES = newSQUARES.subList(0, newSQUARES.size() / 2);
                }

                if (ci < 2)
                    LIMITS[ci] = SQUARES.get(0).y;
                else
                    LIMITS[ci] = SQUARES.get(0).x;

                SQUARES.clear();
            }

            System.out.printf("%.10f\n", (LIMITS[1] - LIMITS[0]) * (LIMITS[3] - LIMITS[2]) / (unit * unit));
        }

        private void drawSquare(Square s, int depth) {
            if (depth == 5) {
                SQUARES.add(s);
                return;
            }

            s.print();

            Square s3 = s.getSide3();
            Square s4 = s.getSide4();

            drawSquare(s3, depth + 1);
            drawSquare(s4, depth + 1);
        }
    }
}
