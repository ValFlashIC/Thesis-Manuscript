redEngineOn(config);

/* A is stored in BaCSC format with pointers delimiting the band sections */
int currCol_OB1     = A.ptr[0];   /* begining of the column - first OB section*/
for (int j = 0, int k = 0; j < N; j++, k += 3) {
    int currCol_IB  = A.ptr[k+1]; /* begining of the band   - IB section */
    int currCol_OB2 = A.ptr[k+2]; /* end of the band        - second OB section */
    int nextCol     = A.ptr[k+3]; /* end of the column      - next column */
    int bj          = b[j];

    /* 1st step: top OB section of the column */
    REG(OBR);
    for (int pos = currCol_OB1; pos < currCol_IB; pos++) {
        int idx = A.idx[pos];
        int val = A.val[pos] * bj;
        RED(c + idx, val);
    }

    /* 2nd step: IB section of the column */
    REG(IBR);
    for (int pos = currCol_IB; pos < currCol_OB2; pos++) {
        int idx = A.idx[pos];
        int val = A.val[pos] * bj;
        RED(c + idx, val);
    }

    /* 3rd step: bottom OB section of the column */   
    REG(OBR);
    for (int pos = currCol_OB2; pos < nextCol; pos++) {
        int idx = A.idx[pos];
        int val = A.val[pos] * bj;
        RED(c + idx, val);
    }

    currCol_OB1 = nextCol; /* begining of the next column */
}

redFlush();
redEngineOff();