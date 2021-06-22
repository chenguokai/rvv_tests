void _halt(int code) {
  __asm__ volatile("mv a0, %0; .word 0x0005006b" : :"r"(code));
}
void matrix_c(long long a1[0x4][0x8], long long a2[0x8][0x4], long long a3[0x4][0x4]) {
        long long ret;
        for (int i = 0; i < 0x4; ++i) {
                for (int j = 0; j < 0x4; ++j) {
                        ret = 0;
                        for (int k = 0; k < 0x8; ++k) {
                                ret  += a1[i][k] * a2[k][j];
                        }
                        a3[i][j] = ret;
                }
        }
}
void matrix_asm(char a1[0x10][0x10], char a2[0x10][0x10], char a3[0x10][0x10]);

__asm__(
	".globl matrix_asm\n\t"
	"matrix_asm:\n\t"
	"csrr a5, mstatus\n\t"
	"ori a5, a5, 0x600\n\t"
	"csrw mstatus, a5\n\t"
        "li a4, 16\n\t"
	"vsetvli a4, a4, e8, m1, tu, mu\n\t"
	"li a4, 0x10\n\t"
	"li a5, 0x0\n\t" // a5: i
	"loop_i:\n\t"
	"vxor.vv v0, v0, v0\n\t"
	"li a6, 0x0\n\t" // a6: k
	"loop_k:\n\t"
	"slli t0, a5, 4\n\t"
	"add t0, t0, a6\n\t"
	"add t0, t0, a0\n\t"
	"lb t1, (t0)\n\t" // t1: a1[i][k]
	"slli t0, a6, 4\n\t"
	"add t0, t0, a1\n\t"
	"vle8.v v1, (t0)\n\t" //  v1: a2[k][j] j = 0 to 0x10
	"vmacc.vx v0, t1, v1\n\t"
	"addi a6, a6, 1\n\t"
	"bgt a4, a6, loop_k\n\t"
	"slli t2, a5, 4\n\t"
	"add t2, t2, a2\n\t"
	"vse8.v v0, (t2)\n\t"
	"ret\n\t"
);

int no_main(char *array) {
	array = (char*)((unsigned int)array & 0xffffffffUL);
	
	char* array1 = (char**)array;
	char* array2 = (char**)((unsigned int)array + 0x400);
	char* array3 = (char**)((unsigned int)array + 0x800);
	for (int i = 0 ; i < 0x20; ++i) {
		for (int j = 0; j < 0x20; ++j) {
			array1[i * 0x10 + j] = i;
			array2[i * 0x10 + j] = j;
		}
	}
	matrix_c(array1, array2, array3);
	__asm__ volatile("ecall\n\t");
	return 0;
}

