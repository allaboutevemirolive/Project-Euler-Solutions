int(f, a, b) = {
    F = intformal(f, x);
    return (subst(F, x, b) - subst(F, x, a));
}

{
    N = 40;
    G = 0;
    G = 0;
    f1 = 1;
    f2 = 0;

    for (i = 1, N,
        G += int(f1, 1 - x, 1);
        H += int(f2, 2 - x, 2);
        f2 = int(f1, x - 1, 1) + int(f2, 1, x);
        f1 = int(f1, 0, x);
    );

    print(int(G*x, 0, 1));
    print(int(H*x, 0, 1));
    print(int(G*int(H, x, 1), 0, 1));
}