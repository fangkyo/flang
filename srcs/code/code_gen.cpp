#include "code_gen.h"
#include "code.h"

CodeGenEngine::CodeGenEngine(int regNum) {
  if (regNum <= 0 || regNum > 32) regNum = DEFAULT_REG_NUM;
  m_regs.resize(regNum);
  m_regIdx = 0;
  m_offset = 0;
}

void CodeGenEngine::newTmp(Addr& addr, int size) {
  for (int i = 0; i < m_regs.size(); ++i) {
    if (NULL == m_regs[i]) {
      m_regs[i] = &addr;
      incRegIdx();
      return;
    }
  }

  Addr* pAddr = m_regs[m_regIdx];
  pAddr->m_type = ADDR_BASE;
  pAddr->m_reg = EBP;
  pAddr->m_offset = m_offset;
  m_offset += size;
  m_regs[m_regIdx] = &addr;
  incRegIdx();
}

void CodeGenEngine::useTmp(Addr& addr, int size) {
  if (addr.m_type == ADDR_REG_DIRECT) {
    if (addr.m_reg > 2 && addr.m_reg < m_regs.size()) {
      m_regs[addr.m_reg] = NULL;
    }
  } else if (addr.m_type == ADDR_BASE) {
    if (addr.m_reg = EBP && addr.m_offset + size == m_offset) {
      m_offset -= size;
    }
  }
}

void CodeGenEngine::incRegIdx() {
  m_regIdx = (m_regIdx + 1) % m_regs.size() + 3;
}

void CodeGenEngine::clearTmp() {
  for (int i = 3; i < m_regs.size(); ++i) {
    m_regs[i] = NULL;
  }
  m_offset = 0;
  m_regIdx = 0;
}
