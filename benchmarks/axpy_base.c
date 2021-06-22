void _halt(int code) {
  __asm__ volatile("mv a0, %0; .word 0x0005006b" : :"r"(code));
}
void axpy_c(char* array_1, char* array_2, char a) {
	for (int i = 0; i < 0x400; ++i) {
		array_1[i] = array_2[i] * a + array_1[i];
	}
}

void axpy_asm(char* array_1, char* array_2, char a);

__asm__(
	".globl axpy_asm\n\t"
	"axpy_asm:\n\t"
	"csrr a5, mstatus\n\t"
	"ori a5, a5, 0x600\n\t"
	"csrw mstatus, a5\n\t"
        "li a4, 32\n\t"
	"vsetvli a4, a4, e8, m1, tu, mu\n\t"
	"addi a4, a1, 0x400\n\t"
	"loop:\n\t"
	"vle8.v v0, (a0)\n\t"
	"vle8.v v1, (a1)\n\t"
	"vmadd.vx v0, a2, v1\n\t"
	"vse8.v v0, (a0)\n\t"
	"addi a0, a0, 32\n\t"
	"addi a1, a1, 32\n\t"
	"bgt a4, a0, loop\n\t"
	"ret\n\t"
);

int no_main(char *array) {
	array = (char*)((unsigned int)array & 0xffffffffUL);
	for (int i = 0; i < 0x400; ++i) {
		array[i] = 1;
	}
	for (int i = 0; i < 0x400; ++i) {
		array[i + 0x800] = 2;
	}
	__asm__ volatile("ecall\n\t");
	return 0;
}

