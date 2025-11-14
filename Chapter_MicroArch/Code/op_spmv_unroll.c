int OBtop = PTR[0]; 
for (int n=0, int k=0; n < N; n++, k+=3) {
    xn = X[n];
    int pos     = OBtop;   /* start of column */
    int IB      = PTR[k+1]; /* start of band */
    int OBbot   = PTR[k+2]; /* end of band   */
    int nextCol = PTR[k+3]; /* end of column */
    /* 1st step: top out-of-band region */
    REG(SRT); /* set region = SRT */ 
    blockPos = (IB - OBtop) / 8;
    for (int i=0; i < blockPos; pos+=8, i++)
        /* Read IDX, VAL, Mult., RED unroll 8x */
        REDiter_unroll_8(pos, xn);
    for (; pos < IB; pos++)
        REDiter_1(pos, xn);
    /* 2nd step: in-band region */
    REG(DRC); /* set region = DRC */
    blockPos = (OBbot - pos) / 8;
    for (int i=0; i < blockPos; pos+=8, i++)
        REDiter_unroll_8(pos, xn);
    for (; pos < OBbot; pos++)
        REDiter_1(pos, xn);
    /* 3rd step: bottom out-of-band region */   
    REG(SRT); /* set region = SRT */
    blockPos = (nextCol - pos) / 8;
    for (int i=0; i < blockPos; pos+=8, i++)
        REDiter_unroll_8(pos, xn);
    for (; pos < nextCol; pos++)
        REDiter_1(pos, xn);
    OBtop = nextCol;
}
flush();