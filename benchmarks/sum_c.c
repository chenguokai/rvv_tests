#pragma O2
void _halt(int code) {
  __asm__ volatile("mv a0, %0; .word 0x0005006b" : :"r"(code));
}
void sum_c(char* array);
	/*
	for (int i = 0; i < 0x20; ++i) {
		for (int j = 0; j < 0x80; ++i) {
			array[i] += j;
		}
	}*/
__asm__(
	".globl sum_c\n\t"
	"sum_c:\n\t"
	"li a1, 0x4\n\t"
	"li a2, 0x0\n\t"
	"loop1:\n\t"
	"lb a5, (a0)\n\t"
	"li a3, 0x80\n\t"
	"li a4, 0x0\n\t"
	"loop2:\n\t"
	"add a5, a5, a4\n\t"
	"addi a4, a4, 1\n\t"
	"bgt a3, a4, loop2\n\t"
	"sb a5, (a0)\n\t"
	"addi a2, a2, 1\n\t"
	"addi a0, a0, 1\n\t"
	"bgt a1, a2, loop1\n\t"
	"ret\n\t"
);
/*
void sum_asm(char* array);
__asm__(
	".globl sum_asm\n\t"
	"sum_asm:\n\t"
	"csrr a5, mstatus\n\t"
	"ori a5, a5, 0x600\n\t"
	"csrw mstatus, a5\n\t"
        "li a4, 32\n\t"
	"vsetvli a4, a4, e8, m1, tu, mu\n\t"
	"vle8.v v0, (a0)\n\t"
	"li a1, 0x80\n\t"
	"li a2, 0x0\n\t"
	"loop:\n\t"
	"vadd.vx v0, v0, a2\n\t"
	"addi a2, a2, 1\n\t"
	"bgt a1, a2, loop\n\t"
	"vse8.v v0, (a0)\n\t"
	"ret\n\t"
);
*/
int no_main(char *array) {
	array = (char*)((unsigned int)array & 0xffffffffUL);
	for (int i = 0; i < 0x20; ++i) {
		array[i] = i;
	}
	sum_c(array);
	__asm__ volatile("ecall\n\t");
	return 0;
}

