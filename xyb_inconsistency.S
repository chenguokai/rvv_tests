.text
_start:
    li a0, 0x400800
    csrs mstatus, a0
    la a1, smode
    csrw mepc, a1
    // come into s mode
    mret
smode:
    la a2, dead
    csrw sepc, a2
    la a3, good
    csrw stvec, a3
    // try calling sret which will raise II
    sret
dead:
    j dead

good:
    j good
