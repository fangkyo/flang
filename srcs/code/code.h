#ifndef CODE_H
#define CODE_H

#include <iostream>
using namespace std;

class CodeGenEngine;

enum AddrType{
    ADDR_IMMEDIA,      // 立即寻址
    ADDR_DIRECT,       // 直接寻址
    ADDR_REG_DIRECT,   // 寄存器立即寻址
    ADDR_INDIRECT,     // 间接寻址
    ADDR_REG_INDIRECT, // 寄存器间接寻址
    ADDR_BASE          // 基址寻址
};


struct Addr{
    AddrType m_type;
    union {
        int   m_val;    // immediate value
        char* m_data;   // direct address and indirect address
        int   m_reg;    // register direct address and indirect address
        int   m_offset; // base address ( always use the register BP as base )
    };

    int getInt() { return 0; }
    char getChar() { return 'c'; }
    char* getStr() { return NULL; }
    bool getBool() { return true; }
};

enum CodeType {
    CODE_PRINTI,
    CODE_PRINTC,
    CODE_PRINTS,
    CODE_ADD,
    CODE_SUB,
    CODE_MUL,
    CODE_DIV,
    CODE_MOV,
    CODE_LEA,
    CODE_PUSHD,
    CODE_PUSHB,
    CODE_POPD,
    CODE_POPB,
    CODE_CALL
};

class Code{
    public:
        CodeType m_type;
        int      m_oprndNum;
        Addr     m_oprnds[2];
        Code() : m_oprndNum(0) { }
        string toString() { return ""; }
        virtual void excute() = 0;
};

class PrintIntCode : public Code {
    public:
        PrintIntCode( const Addr& var ) {
            m_type = CODE_PRINTI;
            m_oprndNum = 1;
            m_oprnds[0] = var;
        }

        virtual void excute(){
            cout << m_oprnds[0].getInt() << endl;
        }
};

class MovCode : public Code {
    public:
        MovCode( const Addr& src, const Addr& dst ){
            m_type = CODE_MOV;
            m_oprndNum = 2;
            m_oprnds[0] = src;
            m_oprnds[1] = dst;
        }
};



#endif
