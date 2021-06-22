void _halt(int code) {
  __asm__ volatile("mv a0, %0; .word 0x0005006b" : :"r"(code));
}
void memset_c(char* dest, char val, long cnt) {
	for (int i = 0; i < cnt; ++i) {
		dest[i] = val;
	}
}

void memset_asm(char* dest, char val, long cnt);
__asm__(
	".globl memset_asm\n"
	"memset_asm:\n\t"
	"csrr a5, mstatus\n\t"
	"ori a5, a5, 0x600\n\t"
	"csrw mstatus, a5\n\t"
        "li a4, 32\n\t"
	"vsetvli a4, a4, e8, m1, tu, mu\n\t"
	"vxor.vv v1, v1, v1\n\t"
	"vadd.vx v1, v1, a1\n\t"
	"add a2, a0, a2\n\t"
	"// init done, start to fill\n\t"
	"loop:\n\t"
	"vse8.v v1, (a0)\n\t"
	"addi a0, a0, 32\n\t"
	"vse8.v v1, (a0)\n\t"
	"addi a0, a0, 32\n\t"
	"vse8.v v1, (a0)\n\t"
	"addi a0, a0, 32\n\t"
	"vse8.v v1, (a0)\n\t"
	"addi a0, a0, 32\n\t"
	"bgt a2, a0, loop\n\t"
	"ret\n\t"
);

int no_main(char *array) {
	memset_asm((unsigned int)array & 0xffffffffUL, 233, 0x1000);
	__asm__ volatile("ecall\n\t");
	return 0;
}
