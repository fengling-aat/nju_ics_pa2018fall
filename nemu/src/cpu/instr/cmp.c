#include "cpu/instr.h"

static void instr_execute_2op(){
	operand_read(&opr_src);
	operand_read(&opr_dest);
	alu_sub(opr_src.val, opr_dest.val, data_size);
	printf("left: %x right: %x ZF: %x\n", opr_src.val, opr_dest.val, cpu.eflags.ZF);
}

make_instr_func(cmp_i2rm_bv){
	OPERAND rm, imm;
	rm.data_size = data_size;
	imm.data_size = 8;

	int len = 1;
	len += modrm_rm(eip + 1, &rm);

	imm.type = OPR_IMM;
	imm.addr = eip + len;
	operand_read(&imm);
	operand_read(&rm);

	uint32_t tval = sign_ext(imm.val, 8);
	alu_sub(tval, rm.val, data_size);
	return 1 + len;
}

make_instr_impl_2op(cmp, r, rm, v);
