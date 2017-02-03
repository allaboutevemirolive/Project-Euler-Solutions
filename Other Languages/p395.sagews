minx,miny,maxx,maxy=0,0,0,1
k=0.01
l=[((0.0,0.0),(1.0,0.0),1.0)]
for n in [1..100]:
    m=[]
    for (a,b,s) in l:
        if(n>13):
            if abs(a[0]-minx)>k and abs(a[0]-maxx)>k and abs(a[1]-miny)>k and abs(a[1]-maxy)>k:
                continue
        w=(b[0]-a[0],b[1]-a[1])
        v=(-w[1],w[0])
        c=(a[0]+v[0],a[1]+v[1])
        d=(b[0]+v[0],b[1]+v[1])
        tw=(0.8*w[0]-0.6*w[1],+0.6*w[0]+0.8*w[1])
        e=(c[0]+0.8*tw[0],c[1]+0.8*tw[1])
        m+=[(c,e,s*0.8),(e,d,s*0.6)]
        minx=min((minx,c[0],d[0]))
        maxx=max((maxx,c[0],d[0]))
        miny=min((miny,c[1],d[1]))
        maxy=max((maxy,c[1],d[1]))

    print n,len(m),k,maxx,maxy,minx,miny,(maxx-minx)*(maxy-miny)
    if len(m)>10000: k*=0.5
    l=m