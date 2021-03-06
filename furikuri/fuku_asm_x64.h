#pragma once

enum fuku_reg64 {
    r_RAX,
    r_RCX,
    r_RDX,
    r_RBX,
    r_RSP,
    r_RBP,
    r_RSI,
    r_RDI,
    r_R8,
    r_R9,
    r_R10,
    r_R11,
    r_R12,
    r_R13,
    r_R14,
    r_R15,
};

class fuku_immediate64 {
    uint64_t imm_value;

public:
    fuku_immediate64::fuku_immediate64();
    fuku_immediate64::fuku_immediate64(uint64_t imm);
    fuku_immediate64::~fuku_immediate64();

public:
    void fuku_immediate64::set_imm(uint64_t imm);
public:
    bool fuku_immediate64::is_imm_8() const;
    bool fuku_immediate64::is_imm_16() const;
    bool fuku_immediate64::is_imm_32() const;
    bool fuku_immediate64::is_imm_64() const;

    uint64_t fuku_immediate64::get_imm() const;
};

class fuku_operand64 {
    uint8_t rex = 0;
    uint8_t buf[9];
    uint8_t len = 1;
    int8_t addend;

public:   
    fuku_operand64::fuku_operand64(fuku_reg64 base, int32_t disp);   // [base + disp/r]
    fuku_operand64::fuku_operand64(fuku_reg64 base, fuku_reg64 index, operand_scale scale, int32_t disp);// [base + index*scale + disp/r]  
    fuku_operand64::fuku_operand64(fuku_reg64 index, operand_scale scale, int32_t disp);// [index*scale + disp/r]
    fuku_operand64::fuku_operand64(fuku_operand64& base, int32_t offset);
    
public:
    void fuku_operand64::set_rex(uint8_t rex);
    void fuku_operand64::set_buf(uint8_t* buf, uint8_t len);
    void fuku_operand64::set_addend(int8_t addend);
public:
    bool address_uses_reg(fuku_reg64 reg) const;
    bool fuku_operand64::requires_rex() const;
    int  fuku_operand64::operand_size() const;
    int8_t fuku_operand64::get_addend() const;

    const uint8_t* fuku_operand64::get_buf() const;
    uint8_t fuku_operand64::get_length() const;
    uint8_t fuku_operand64::get_rex() const;
};


class fuku_asm_x64{
    uint8_t bytecode[16];
    uint8_t length;
    uint8_t imm_offset;

    void fuku_asm_x64::clear_space();

    void fuku_asm_x64::emit_b(uint8_t x);
    void fuku_asm_x64::emit_w(uint16_t x);
    void fuku_asm_x64::emit_dw(uint32_t x);
    void fuku_asm_x64::emit_qw(uint64_t x);

    void fuku_asm_x64::emit_rex_64();
    void fuku_asm_x64::emit_rex_64(fuku_reg64 reg, fuku_reg64 rm_reg);
    void fuku_asm_x64::emit_rex_64(fuku_reg64 reg, fuku_operand64& op);
    void fuku_asm_x64::emit_rex_64(fuku_reg64 rm_reg);
    void fuku_asm_x64::emit_rex_64(fuku_operand64& op);
    void fuku_asm_x64::emit_rex_32(fuku_reg64 reg, fuku_reg64 rm_reg);
    void fuku_asm_x64::emit_rex_32(fuku_reg64 reg, fuku_operand64& op);
    void fuku_asm_x64::emit_rex_32(fuku_reg64 rm_reg);
    void fuku_asm_x64::emit_rex_32(fuku_operand64& op);
    void fuku_asm_x64::emit_optional_rex_32(fuku_reg64 reg, fuku_reg64 rm_reg);
    void fuku_asm_x64::emit_optional_rex_32(fuku_reg64 reg, fuku_operand64& op);
    void fuku_asm_x64::emit_optional_rex_32(fuku_reg64 rm_reg);
    void fuku_asm_x64::emit_optional_rex_32(fuku_operand64& op);

    void fuku_asm_x64::emit_modrm(fuku_reg64 reg, fuku_reg64 rm_reg);
    void fuku_asm_x64::emit_modrm(int code, fuku_reg64 rm_reg);

    void fuku_asm_x64::emit_operand(int code, fuku_operand64& adr);

    void fuku_asm_x64::emit_rex(int size);
    void fuku_asm_x64::emit_rex(fuku_operand64& p1, int size);
    void fuku_asm_x64::emit_rex(fuku_reg64 p1, int size);

    void fuku_asm_x64::emit_rex(fuku_reg64 p1, fuku_reg64 p2, int size);
    void fuku_asm_x64::emit_rex(fuku_reg64 p1, fuku_operand64& p2, int size);



    void fuku_asm_x64::arithmetic_op(uint8_t opcode, fuku_reg64 reg, fuku_operand64& op, int size);
    void fuku_asm_x64::arithmetic_op(uint8_t opcode,fuku_reg64 reg,fuku_reg64 rm_reg,int size);
    void fuku_asm_x64::arithmetic_op_16(uint8_t opcode, fuku_reg64 reg, fuku_reg64 rm_reg);
    void fuku_asm_x64::arithmetic_op_16(uint8_t opcode, fuku_reg64 reg, fuku_operand64& rm_reg);
    void fuku_asm_x64::arithmetic_op_8(uint8_t opcode, fuku_reg64 reg, fuku_operand64& op);
    void fuku_asm_x64::arithmetic_op_8(uint8_t opcode, fuku_reg64 reg, fuku_reg64 rm_reg);
    void fuku_asm_x64::immediate_arithmetic_op(uint8_t subcode,fuku_reg64 dst,fuku_immediate64& src,int size);
    void fuku_asm_x64::immediate_arithmetic_op(uint8_t subcode, fuku_operand64& dst,fuku_immediate64& src, int size);
    void fuku_asm_x64::immediate_arithmetic_op_16(uint8_t subcode,fuku_reg64 dst,fuku_immediate64& src);
    void fuku_asm_x64::immediate_arithmetic_op_16(uint8_t subcode, fuku_operand64& dst,fuku_immediate64& src);
    void fuku_asm_x64::immediate_arithmetic_op_8(uint8_t subcode, fuku_operand64& dst,fuku_immediate64& src);
    void fuku_asm_x64::immediate_arithmetic_op_8(uint8_t subcode,fuku_reg64 dst,fuku_immediate64& src);
public:
    fuku_asm_x64::fuku_asm_x64();
    fuku_asm_x64::~fuku_asm_x64();

    fuku_instruction fuku_asm_x64::jmp(fuku_reg64 reg);
    fuku_instruction fuku_asm_x64::jmp(fuku_operand64& adr);
    fuku_instruction fuku_asm_x64::jmp(uint32_t offset);
    fuku_instruction fuku_asm_x64::jcc(fuku_condition cond, uint32_t offset);


    fuku_instruction fuku_asm_x64::clc();
    fuku_instruction fuku_asm_x64::cld();
    fuku_instruction fuku_asm_x64::cdq();
    fuku_instruction fuku_asm_x64::cmpb_al(fuku_immediate64& imm8);
    fuku_instruction fuku_asm_x64::cmpxchgb(fuku_operand64& dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::cmpxchgw(fuku_operand64& dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::emit_cmpxchg(fuku_operand64& dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::lfence();
    fuku_instruction fuku_asm_x64::cpuid();
    fuku_instruction fuku_asm_x64::cqo();
    fuku_instruction fuku_asm_x64::emit_dec(fuku_reg64 dst, int size);
    fuku_instruction fuku_asm_x64::emit_dec(fuku_operand64& dst, int size);
    fuku_instruction fuku_asm_x64::decb(fuku_reg64 dst);
    fuku_instruction fuku_asm_x64::decb(fuku_operand64& dst);
    fuku_instruction fuku_asm_x64::enter(fuku_immediate64& size);
    fuku_instruction fuku_asm_x64::hlt();
    fuku_instruction fuku_asm_x64::emit_idiv(fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_div(fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_imul(fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_imul(fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_imul(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_imul(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_imul(fuku_reg64 dst, fuku_reg64 src, fuku_immediate64& imm, int size);
    fuku_instruction fuku_asm_x64::emit_imul(fuku_reg64 dst, fuku_operand64& src, fuku_immediate64& imm, int size);
    fuku_instruction fuku_asm_x64::emit_inc(fuku_reg64 dst, int size);
    fuku_instruction fuku_asm_x64::emit_inc(fuku_operand64& dst, int size);
    fuku_instruction fuku_asm_x64::int3();
    fuku_instruction fuku_asm_x64::emit_lea(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::leave();
    fuku_instruction fuku_asm_x64::movb(fuku_reg64 dst, fuku_operand64& src);
    fuku_instruction fuku_asm_x64::movb(fuku_reg64 dst, fuku_immediate64& imm);
    fuku_instruction fuku_asm_x64::movb(fuku_operand64& dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::movb(fuku_operand64& dst, fuku_immediate64& imm);
    fuku_instruction fuku_asm_x64::movw(fuku_reg64 dst, fuku_operand64& src);
    fuku_instruction fuku_asm_x64::movw(fuku_operand64& dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::movw(fuku_operand64& dst, fuku_immediate64& imm);
    fuku_instruction fuku_asm_x64::emit_mov(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_mov(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_mov(fuku_operand64& dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_mov(fuku_reg64 dst, fuku_immediate64& value, int size);
    fuku_instruction fuku_asm_x64::emit_mov(fuku_operand64& dst, fuku_immediate64& value, int size);
    fuku_instruction fuku_asm_x64::movq(fuku_reg64 dst, int64_t value);
    fuku_instruction fuku_asm_x64::movq(fuku_reg64 dst, uint64_t value);
    fuku_instruction fuku_asm_x64::movsxbl(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::movsxbl(fuku_reg64 dst, fuku_operand64& src);
    fuku_instruction fuku_asm_x64::movsxbq(fuku_reg64 dst, fuku_operand64& src);
    fuku_instruction fuku_asm_x64::movsxbq(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::movsxwl(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::movsxwl(fuku_reg64 dst, fuku_operand64& src);
    fuku_instruction fuku_asm_x64::movsxwq(fuku_reg64 dst, fuku_operand64& src);
    fuku_instruction fuku_asm_x64::movsxwq(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::movsxlq(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::movsxlq(fuku_reg64 dst, fuku_operand64& src);
    fuku_instruction fuku_asm_x64::emit_movzxb(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_movzxb(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_movzxw(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_movzxw(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::repmovsb();
    fuku_instruction fuku_asm_x64::repmovsw();
    fuku_instruction fuku_asm_x64::emit_repmovs(int size);
    fuku_instruction fuku_asm_x64::mull(fuku_reg64 src);
    fuku_instruction fuku_asm_x64::mull(fuku_operand64& src);
    fuku_instruction fuku_asm_x64::mulq(fuku_reg64 src);
    fuku_instruction fuku_asm_x64::emit_neg(fuku_reg64 dst, int size);
    fuku_instruction fuku_asm_x64::emit_neg(fuku_operand64& dst, int size);
    fuku_instruction fuku_asm_x64::nop();
    fuku_instruction fuku_asm_x64::emit_not(fuku_reg64 dst, int size);
    fuku_instruction fuku_asm_x64::emit_not(fuku_operand64& dst, int size);
    fuku_instruction fuku_asm_x64::Nop(int n);
    fuku_instruction fuku_asm_x64::popq(fuku_reg64 dst);
    fuku_instruction fuku_asm_x64::popq(fuku_operand64& dst);
    fuku_instruction fuku_asm_x64::popfq();
    fuku_instruction fuku_asm_x64::pushq(fuku_reg64 src);
    fuku_instruction fuku_asm_x64::pushq(fuku_operand64& src);
    fuku_instruction fuku_asm_x64::pushq(fuku_immediate64& value);
    fuku_instruction fuku_asm_x64::pushq_imm32(int32_t imm32);
    fuku_instruction fuku_asm_x64::pushfq();
    fuku_instruction fuku_asm_x64::ret(int imm16);
    fuku_instruction fuku_asm_x64::ud2();
    fuku_instruction fuku_asm_x64::shld(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::shrd(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::xchgb(fuku_reg64 reg, fuku_operand64& op);
    fuku_instruction fuku_asm_x64::xchgw(fuku_reg64 reg, fuku_operand64& op);
    fuku_instruction fuku_asm_x64::emit_xchg(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_xchg(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::testb(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::testb(fuku_reg64 reg, fuku_immediate64& mask);
    fuku_instruction fuku_asm_x64::testb(fuku_operand64& op, fuku_immediate64& mask);
    fuku_instruction fuku_asm_x64::testb(fuku_operand64& op, fuku_reg64 reg);
    fuku_instruction fuku_asm_x64::testw(fuku_reg64 dst, fuku_reg64 src);
    fuku_instruction fuku_asm_x64::testw(fuku_reg64 reg, fuku_immediate64& mask);
    fuku_instruction fuku_asm_x64::testw(fuku_operand64& op, fuku_immediate64& mask);
    fuku_instruction fuku_asm_x64::testw(fuku_operand64& op, fuku_reg64 reg);
    fuku_instruction fuku_asm_x64::emit_test(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_test(fuku_reg64 reg, fuku_immediate64& mask, int size);
    fuku_instruction fuku_asm_x64::emit_test(fuku_operand64& op, fuku_immediate64& mask, int size);
    fuku_instruction fuku_asm_x64::emit_test(fuku_operand64& op, fuku_reg64 reg, int size);
    fuku_instruction fuku_asm_x64::emit_add(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_add(fuku_reg64 dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_add(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_add(fuku_operand64& dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_add(fuku_operand64& dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_and(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_and(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_and(fuku_operand64& dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_and(fuku_reg64 dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_and(fuku_operand64& dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_cmp(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_cmp(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_cmp(fuku_operand64& dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_cmp(fuku_reg64 dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_cmp(fuku_operand64& dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_or(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_or(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_or(fuku_operand64& dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_or(fuku_reg64 dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_or(fuku_operand64& dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_sbb(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_sub(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_sub(fuku_reg64 dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_sub(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_sub(fuku_operand64& dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_sub(fuku_operand64& dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_xor(fuku_reg64 dst, fuku_reg64 src, int size);
    fuku_instruction fuku_asm_x64::emit_xor(fuku_reg64 dst, fuku_operand64& src, int size);
    fuku_instruction fuku_asm_x64::emit_xor(fuku_reg64 dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_xor(fuku_operand64& dst, fuku_immediate64& src, int size);
    fuku_instruction fuku_asm_x64::emit_xor(fuku_operand64& dst, fuku_reg64 src, int size);
};

