.text
_start:
    li a1, 2
    vsetvli a1, a1, e8, m2, tu, mu
    la a0, _data
    vse8.v v0, (a0)
1:
    j 1b
_data:
    .byte 0x1
    .byte 0x2
    .byte 0x3
    .byte 0x4
    .byte 0x5
    .byte 0x6
    .byte 0x7
    .byte 0x8
    .byte 0x9
    .byte 0xa
    .byte 0xb
    .byte 0xc
    .byte 0xd
    .byte 0xe
    .byte 0xf
