#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <iostream>
#include <queue>

using namespace std;

typedef char byte;

#define MEM_BLK_SIZE 4096

class MemoryPool{
    private:
        struct MemoryBlock {
            int    m_compacity;
            int    m_remain;
            byte*  m_data;

            MemoryBlock( int compacity ) {
                if( compacity <=0 ){
                    m_compacity = 0;
                    m_remain = 0;
                    m_data = NULL;
                    return;
                }
                m_compacity = compacity;
                m_remain = compacity;
                m_data = new byte[ compacity ];
            }

            MemoryBlock() {}
            
            bool operator < ( const MemoryBlock& blk ) const {
                return m_remain < blk.m_remain;
            }
        };

        priority_queue<MemoryBlock> m_memQueue;

    public:
        MemoryPool();
        ~MemoryPool();

        byte* alloc( int size );

        template < class T >
        byte* alloc() {
            return alloc(sizeof(T));
        }

};


#endif
