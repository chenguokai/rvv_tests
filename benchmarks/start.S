/* This is the startup file for a minimal test suit */
.globl _start
_start:
    li sp, 0x80200000 // 32 MiB above the startup address
    lui a0, %hi(0x80300000)
    addi a0, a0, %lo(0x80300000)
    li a1, 0
    j no_main
    sd a0, (zero) // trigger a fault
dead:
    j dead
