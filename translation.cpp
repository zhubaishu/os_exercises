
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
    unsigned int va, pa;
    freopen("input.txt","r",stdin);
    cin >> va >> pa;
    unsigned int pde_idx = (va >> 22) & 0x3FF;
    unsigned int pde_ctx = ((pde_idx - 0x300 + 1) << 12)+ 0x3;
    unsigned int pte_idx = (va >> 12) & 0x3FF;
    unsigned int pte_ctx = pa & ~0x3FF | 0x3;
    printf("va 0x%08x, pa 0x%08x, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x\n", 
    va, pa, pde_idx, pde_ctx, pte_idx, pte_ctx);
    fclose(stdin);
    return 0;
}
