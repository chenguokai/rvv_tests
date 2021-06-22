void _halt(int code) {
  __asm__ volatile("mv a0, %0; .word 0x0005006b" : :"r"(code));
}
void memset_c(long long* dest, char val, long cnt) {
	for (int i = 0; i < cnt / 4; ++i) {
		dest[i] = val;
	}
}

void memset_asm(char* dest, char val, long cnt);
__asm__(
	".globl memset_asm\n"
	"memset_asm:\n\t"
        "li a1, 32\n\t"
	"vsetvli a1, a1, e8, m1, tu, mu\n\t"
	"vxor.vv v1, v1, v1\n\t"
	"vadd.vx v1, v1, a3\n\t"
	"// init done, start to fill\n\t"
);

int no_main(char *array) {
	memset_c((unsigned int)array & 0xffffffffUL, 233, 0x1000);
	__asm__ volatile("ecall\n\t");
	return 0;
}
