#pragma once


class fuku_mutation_x86 : 
    public fuku_mutation {

    fuku_asm_x86 f_asm;
    ob_fuku_sensitivity settings;
    fuku_obfuscator * obfuscator;

    void fuku_mutation_x86::fuku_junk_1b(std::vector<fuku_instruction>& out_lines);
    void fuku_mutation_x86::fuku_junk_2b(std::vector<fuku_instruction>& out_lines);
    void fuku_mutation_x86::fuku_junk_4b(std::vector<fuku_instruction>& out_lines);
    void fuku_mutation_x86::fuku_junk_5b(std::vector<fuku_instruction>& out_lines);
    void fuku_mutation_x86::fuku_junk_7b(std::vector<fuku_instruction>& out_lines);


    void fuku_mutation_x86::fuku_junk(std::vector<fuku_instruction>& lines, unsigned int current_line_idx,std::vector<fuku_instruction>& out_lines);

    bool fuku_mutation_x86::fukutate_push(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_pop(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_add(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_sub(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_xor(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_and(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_inc(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_dec(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_test(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_cmp(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_jcc(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_jmp(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    bool fuku_mutation_x86::fukutate_ret(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);

    void fuku_mutation_x86::fukutation(std::vector<fuku_instruction>& lines, unsigned int current_line_idx, std::vector<fuku_instruction>& out_lines);
    void fuku_mutation_x86::obfuscate_lines(std::vector<fuku_instruction>& lines, unsigned int recurse_idx);
public:
    fuku_mutation_x86::fuku_mutation_x86(const ob_fuku_sensitivity& settings, fuku_obfuscator * obfuscator);
    fuku_mutation_x86::~fuku_mutation_x86();

    void fuku_mutation_x86::obfuscate(std::vector<fuku_instruction>& lines);

    void fuku_mutation_x86::generate_junk(std::vector<uint8_t>& junk, size_t junk_size);
};



