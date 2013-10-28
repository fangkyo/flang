#include "memory_pool.h"

MemoryPool::MemoryPool() {
}

MemoryPool::~MemoryPool(){
    while( !m_memQueue.empty() ){

        cout << "release block" <<endl;
        cout << m_memQueue.top().m_compacity <<endl;
        cout << m_memQueue.top().m_remain <<endl;

        delete m_memQueue.top().m_data;
        m_memQueue.pop();
    }
}

byte* MemoryPool::alloc( int size ){


    if( m_memQueue.empty() || m_memQueue.top().m_remain < size ) {
        
        MemoryBlock memBlk;
        memBlk.m_compacity = size > MEM_BLK_SIZE ? size : MEM_BLK_SIZE;
        memBlk.m_remain = memBlk.m_compacity - size;
        memBlk.m_data = new byte[ memBlk.m_compacity ];
        m_memQueue.push( memBlk );

    }else{

        MemoryBlock memBlk = m_memQueue.top();
        m_memQueue.pop();
        byte* pData = memBlk.m_data + memBlk.m_remain;
        memBlk.m_remain -= size;
        m_memQueue.push( memBlk );
        return pData;
    }
}
