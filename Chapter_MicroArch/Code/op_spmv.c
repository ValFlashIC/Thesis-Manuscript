/* Data:
 *   A(M, N), stored in CSC: A.ptr, A.idx, A.val
 *   b(N), dense:            b
 *   c(M), dense:            c
 * */

redEngineOn(config);

int currCol = A.ptr[0];
for (int j = 0; j < N; j++) { /* Column first */
    int nextCol = A.ptr[j+1];
    int bj      = b[j];

    for (int pos = currCol; pos < nextCol; pos++) {
        int idx = A.idx[pos];
        int val = A.val[pos] * bj;

        /* Without RED engine: c[idx] += val; */
        /* With RED engine: */
        int *addr    = c + idx;
        region_t reg = regionSelect();

        asm volatile ( /* RISC-V ISA: Type R */ /* REG(reg); */
            "reg x0, x0, %[rs2]"
            :
            : [rs2] "r" ((int) reg)
        );
        asm volatile ( /* RISC-V ISA: Type S */ /* RED(addr, val); */
            "red.w %[rs2], 0(%[rs1])"
            :
            : [rs2] "r" (addr), [rs2] "r" (val)
        );
    }

    currCol = nextCol;
}

redFlush();
redEngineOff();