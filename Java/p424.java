package com.company;

import org.jacop.constraints.*;
import org.jacop.core.BoundDomain;
import org.jacop.core.IntVar;
import org.jacop.core.Store;
import org.jacop.search.*;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Created by aa on 06/04/17.
 */
public class p424 {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("p424.txt"));
        String line;
        long ss = 0;
        while ((line = br.readLine()) != null) {
            Kakuro k = parseKakuro(line);
            k.computeEquations();
            long kv = k.solve();
            ss += kv;
        }

        System.out.println(ss);
    }

    private static char chars[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    public static int getVarIndex(char c) {
        for (int i = 0; i < chars.length; i++)
            if (chars[i] == c)
                return i;
        return -1;
    }

    static HashMap<Integer, VarCell> vars = new HashMap<>();

    public static VarCell getVar(int i) {
        VarCell v = vars.computeIfAbsent(i, k -> new VarCell(i));
        return v;
    }

    public static Kakuro parseKakuro(String line) {
        String[] data = line.split(",");
        int sz = Integer.parseInt(data[0]);
        Kakuro k = new Kakuro(sz, 10);
        int r = 0, c = 0;
        boolean paren = false;
        for (int i = 1; i < data.length; i++) {
            String token = data[i];
            if (token.startsWith("(")) {
                token = data[i].substring(1);
                paren = true;
            }
            if (token.endsWith(")")) {
                token = token.substring(0, token.length() - 1);
                paren = false;
            }
            if (token.equals("O")) {
                k.addVariable(r, c);
            } else if (token.startsWith("v")) {
                if (k.board[r][c] == null)
                    k.board[r][c] = new SumCell();
                ((SumCell) k.board[r][c]).v = token.substring(1);
            } else if (token.startsWith("h")) {
                if (k.board[r][c] == null)
                    k.board[r][c] = new SumCell();
                ((SumCell) k.board[r][c]).h = token.substring(1);
            } else {
                k.board[r][c] = getVar(getVarIndex(token.charAt(0)));
            }
            if (paren) continue;
            c++;
            if (c == sz) {
                r++;
                c = 0;
            }
        }
        return k;
    }

    static class Kakuro {
        int varcount;
        int size;
        Cell[][] board;
        ArrayList<Equation> eqs;

        public Kakuro(int size, int varcount) {
            this.size = size;
            this.varcount = varcount; // 10 = A to J, index from 0, starting 10 are the O variables
            board = new Cell[size][size];
        }

        public void addVariable(int r, int c) {
            board[r][c] = getVar(varcount);
            varcount++;
        }

        public long solve() {
            int[][] ranges = new int[varcount][2];
            // A-J should be between 0 to 9
            for (int i = 0; i < 10; i++) {
                ranges[i][0] = 0;
                ranges[i][1] = 9;
            }
            // All O vars should be between 1 to 9
            for (int i = 10; i < varcount; i++) {
                ranges[i][0] = 1;
                ranges[i][1] = 9;
            }
            int[] vmsk = new int[10];
            int d10_1 = -1;
            int d10_2 = -1;
            int d10_3 = -1;

            // All A-J vars appearing outside sum cells should be from 1 to 9
            for (Equation eq : eqs) {
                for (VarCell v : eq.req) {
                    if (v.id < 10)
                        ranges[v.id][0] = 1;
                }
            }
            for (Equation eq : eqs) {
                // Sum Var = VU, components = 2 => V = 1 (9+8 = 17 = max value for 2 components)
                if (eq.v10 >= 0 && eq.req.size() == 2) {
                    if (vmsk[eq.v10] == 0) {
                        d10_1 = eq.v10;
                        vmsk[eq.v10] = 1;
                        ranges[eq.v10][0] = 1;
                        ranges[eq.v10][1] = 1;
                        ranges[eq.v1][1] = 7;
                        for (int j = 0; j < 10; j++) {
                            if (vmsk[j] != 0) continue;
                            // all others should have min value of 2 or more
                            if (ranges[j][0] == 1)
                                ranges[j][0] = 2;
                        }
                    }
                }
            }
            for (Equation eq : eqs) {
                // Sum Var = VU, components = 3 => V = 1 or 2. If 2, max U = 4 (9+8+7 = 24)
                if (eq.v10 >= 0 && eq.req.size() == 3) {
                    if (vmsk[eq.v10] == 0) {
                        int dmin = 1;
                        if (d10_1 >= 0) {
                            d10_2 = eq.v10;
                            dmin = 2;
                            ranges[eq.v1][1] = 4;
                        }
                        vmsk[eq.v10] = 1;
                        ranges[eq.v10][0] = dmin;
                        ranges[eq.v10][1] = 2;
                        for (int j = 0; j < 10; j++) {
                            if (vmsk[j] != 0) continue;
                            // all others should have min value of dmin+1 or more
                            if (ranges[j][0] > 0 && ranges[j][0] <= dmin)
                                ranges[j][0] = dmin + 1;
                        }
                    }
                }
            }

            for (Equation eq : eqs) {
                // Sum Var = VU, components >= 4 => V = 1 or 2 or 3.
                // If components = 5 && V = 3, max U = 5 (9+8+7+6+5 = 35)
                if (eq.v10 >= 0 && eq.req.size() >= 4) {
                    if (vmsk[eq.v10] == 0) {
                        int dmin = 1;
                        if (d10_1 >= 0) {
                            if (d10_2 >= 0) {
                                d10_3 = eq.v10;
                                dmin = 3;
                                if (eq.req.size() == 5) {
                                    ranges[eq.v1][1] = 5;
                                }
                            } else {
                                dmin = 2;
                            }
                        }
                        vmsk[eq.v10] = 1;
                        ranges[eq.v10][0] = dmin;
                        ranges[eq.v10][1] = 3;
                        for (int j = 0; j < 10; j++) {
                            if (vmsk[j] != 0) continue;
                            if (ranges[j][0] > 0 && ranges[j][0] <= dmin) {
                                if (dmin == 2)
                                    ranges[j][0] = dmin;
                                else
                                    ranges[j][0] = dmin + 1;
                            }
                        }
                    }
                }
            }

            // This is to propagate range constraints for sum equations where the sum is a single digit
            while (true) {
                boolean found = false;
                for (Equation eq : eqs) {
                    if (eq.v10 >= 0) continue;
                    int eqsz = eq.req.size();
                    int t = ((eqsz - 1) * eqsz) / 2;
                    for (VarCell v : eq.req) {
                        if (v.id < 10 && ranges[eq.v1][0] < ranges[v.id][0] + t) {
                            ranges[eq.v1][0] = ranges[v.id][0] + t;
                            found = true;
                        }
                        if (ranges[eq.v1][1] < ranges[v.id][1] + t) {
                            ranges[v.id][1] = ranges[eq.v1][1] - t;
                            found = true;
                        }
                    }
                }
                if (!found) break; // no more to propagate
            }

            // Rest is the code for JaCoP
            Store store = new Store(); // variable store for JaCoP
            IntVar[] ivars = new IntVar[varcount];
            for (int i = 0; i < ivars.length; i++) {
                ivars[i] = new IntVar(store, "V" + i, new BoundDomain(ranges[i][0], ranges[i][1]));
            }
            IntVar[] kvars = new IntVar[10];
            for (int i = 0; i < kvars.length; i++) kvars[i] = ivars[i];
            Constraint ctr = new Alldiff(kvars); // A to J should all take different values
            store.impose(ctr);

            IntVar[][] eqvars = new IntVar[eqs.size()][2];

            for (int i = 0; i < eqs.size(); i++) {
                Equation eq = eqs.get(i);
                if (eq.v10 >= 0) {
                    eqvars[i][0] = new IntVar(store, "RS" + i, new BoundDomain(0, 39)); // Right side of the equation
                    int[] weights = {10, 1};
                    IntVar[] srvars = {ivars[eq.v10], ivars[eq.v1]};
                    ctr = new SumWeight(srvars, weights, eqvars[i][0]); // If sum is UV, then the total is U*10+V
                    store.impose(ctr);
                } else {
                    eqvars[i][0] = ivars[eq.v1]; // If sum is just U, there is no need for a separate total variable
                }
                eqvars[i][1] = new IntVar(store, "LS" + i, new BoundDomain(0, 39)); // Left side of the equation

                kvars = new IntVar[eq.req.size()];
                for (int j = 0; j < kvars.length; j++)
                    kvars[j] = ivars[eq.req.get(j).id];
                ctr = new Alldiff(kvars); // All the components of the RHS of the equation should be unique
                store.impose(ctr);
                ctr = new Sum(kvars, eqvars[i][1]);
                store.impose(ctr);
                ctr = new XeqY(eqvars[i][0], eqvars[i][1]); // LHS of the Equation = RHS of the Equation
                store.impose(ctr);
            }

            Search<IntVar> search = new DepthFirstSearch<>();
            search.setPrintInfo(false);
            SelectChoicePoint<IntVar> select =
                    new InputOrderSelect<>(store, ivars,
                            new IndomainMin<>());
            boolean result = search.labeling(store, select);
            if (result) {
                long ans = 0;
                for (int i = 0; i < 10; i++) {
                    ans *= 10;
                    ans += ivars[i].value();
                }
                return ans;
            }
            System.out.println("Should not arrive here. No solution!!!\n");
            System.exit(0);
            return -1;
        }

        public void print() {
            System.out.println(size);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    board[i][j].print();
                    System.out.print(" ");
                }
                System.out.println();
            }
            if (eqs != null) {
                for (Equation eq : eqs) {
                    if (eq.v10 >= 0) {
                        getVar(eq.v10).print();
                        System.out.print("*10+");
                    }
                    getVar(eq.v1).print();
                    System.out.print("=");
                    for (VarCell v : eq.req) {
                        v.print();
                        System.out.print("+");
                    }
                    System.out.println("z");
                }
            }
        }

        public void computeEquations() {
            eqs = new ArrayList<Equation>();
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (!(board[i][j] instanceof SumCell)) continue;
                    SumCell sv = (SumCell) board[i][j];
                    if (sv.h != null)
                        eqs.add(getHSum(i, j));
                    if (sv.v != null)
                        eqs.add(getVSum(i, j));
                }
            }
        }

        public Equation getHSum(int r, int c) {
            SumCell sv = (SumCell) board[r][c];
            ArrayList<VarCell> vars = new ArrayList<>();
            for (int i = c + 1; i < size; i++) {
                if (board[r][i].id < 0) break;
                vars.add((VarCell) board[r][i]);
            }
            return new Equation(sv.h, vars);
        }


        public Equation getVSum(int r, int c) {
            SumCell sv = (SumCell) board[r][c];
            ArrayList<VarCell> vars = new ArrayList<>();
            for (int i = r + 1; i < size; i++) {
                if (board[i][c].id < 0) break;
                vars.add((VarCell) board[i][c]);
            }
            return new Equation(sv.v, vars);
        }
    }

    static class Cell {
        int id;

        protected Cell(int id) {
            this.id = id;
        }

        public void print() {
            System.out.print(id);
        }
    }

    static class VarCell extends Cell {
        public VarCell(int id) {
            super(id);
        }
    }

    static class SumCell extends Cell {
        String h;
        String v;

        public SumCell() {
            super(-1);
        }

        public void print() {
            if (v != null)
                System.out.print(v);
            else
                System.out.print(" ");
            System.out.print("\\");
            if (h != null)
                System.out.print(h);
            else
                System.out.print(" ");
        }

    }

    static class Equation {
        ArrayList<VarCell> req;
        int v1;
        int v10;

        public Equation(String leq, ArrayList<VarCell> req) {
            this.req = req;
            if (leq.length() == 1) {
                v1 = getVarIndex(leq.charAt(0));
                v10 = -1;
            } else {
                v1 = getVarIndex(leq.charAt(1));
                v10 = getVarIndex(leq.charAt(0));
            }
        }
    }
}
