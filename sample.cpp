// AnySizeStruct sample
// This file is public domain software (PDS).
//////////////////////////////////////////////////////////////////////////////

#include "AnySizeStruct.hpp"
#include <cstdio>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

struct AAA {
    int m_a;
    int m_b;
    AAA(int a, int b) : m_a(a), m_b(b) { }
};

//////////////////////////////////////////////////////////////////////////////

int main(void) {
    #ifdef ANYSIZESTRUCT_CXX11
        AnySizeStruct<AAA, 25> aaa(2, 3);
        AnySizeStruct<AAA, 30> aaa2(aaa);
        printf("%d\n", aaa.size());
        printf("%d\n", aaa2.size());
        printf("%d\n", aaa2->m_a);
        printf("%d\n", (*aaa2).m_a);
        printf("%d\n", (&aaa2)->m_a);
        aaa2->m_a = 20;
        aaa = aaa2;
        printf("%d\n", aaa->m_a);
        AnySizeStruct<std::vector<int> > vec = {200, 300, 400};
        printf("%d\n", vec.ref()[2]);
    #else
        AnySizeStruct<AAA, 25> aaa(AAA(2, 3));
        AnySizeStruct<AAA, 30> aaa2(aaa);
        printf("%d\n", aaa.size());
        printf("%d\n", aaa2.size());
        printf("%d\n", aaa2->m_a);
        printf("%d\n", (*aaa2).m_a);
        printf("%d\n", (&aaa2)->m_a);
        aaa2->m_a = 20;
        aaa = aaa2;
        printf("%d\n", aaa->m_a);
        AnySizeStruct<std::vector<int> > vec;
        vec->push_back(200);
        vec->push_back(300);
        vec->push_back(400);
        printf("%d\n", vec.ref()[2]);
    #endif
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
