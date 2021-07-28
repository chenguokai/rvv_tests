.text
_start:
    la a0, mhandle
    csrw mtvec, a0
    li a1, 1
/* Test starts herh */
    csrrw x0, mhartid, x0 // trap
    csrrw a0, mhartid, a1 // trap
    csrrs a0, mhartid, x0 // no trap
    csrrs a0, mhartid, a1 // ttap
    csrrwi x0, mhartid, 1 // trap
    csrrwi x1, mhartid, 1 // trap
    csrrci x1, mhartid, 1 // trap
    csrrci x1, mhartid, 0 // no trap
dead:
    j dead

mhandle:
    csrr t0, mepc
    addi t0, t0, 4
    csrw mepc, t0
    mret
