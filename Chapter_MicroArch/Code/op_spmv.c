startRedEngine();
for (int n=0; n<N; n++) { /* Column first */
    int bn = b[n];
    int currPos = A.ptr[n];
    int nextPos = A.ptr[n+1];
    for (int pos=currPos; pos<nextPos; pos++) {
        int idx = A.idx[pos];
        int val = A.val[pos] * bn;
        /* Without RED engine: c[idx] += val; */
        /* With RED engine: */
        int *addr = c + idx;
        region_t reg = regionSelect();
        asm volatile ( /* RISC-V ISA: Type R */
            "reg x0, x0, %[rs2]"
            :
            : [rs2] "r" ((int) reg)
        );
        asm volatile ( /* RISC-V ISA: Type S */
            "red.w %[rs2], 0(%[rs1])"
            :
            : [rs2] "r" (addr), [rs2] "r" (val)
        );
    }
}
flushAndStopRedEngine();