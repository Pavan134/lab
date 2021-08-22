Vm.c(allocuvm):
int
allocuvm(pde_t *pgdir, uint oldsz, uint newsz)
{
char *mem;
uint a;
if(newsz >= KERNBASE)
return 0;
if(newsz < oldsz)
return oldsz;
a = PGROUNDUP(oldsz);
for(; a < newsz; a += PGSIZE){
mem = kalloc();
if(mem == 0){
cprintf("allocuvm out of memory\n");
deallocuvm(pgdir, newsz, oldsz);
return 0;
}
memset(mem, 0, PGSIZE);
if(mappages(pgdir, (char*)a, PGSIZE, V2P(mem), PTE_W|PTE_U) < 0){
cprintf("allocuvm out of memory (2)\n");
deallocuvm(pgdir, newsz, oldsz);
kfree(mem);
return 0;
}
}
return newsz;
}
Vm.c(deallocuvm):
int
deallocuvm(pde_t *pgdir, uint oldsz, uint newsz)
{
pte_t *pte;
uint a, pa;
if(newsz >= oldsz)
return oldsz;
a = PGROUNDUP(newsz);
for(; a < oldsz; a += PGSIZE){
pte = walkpgdir(pgdir, (char*)a, 0);
if(!pte)
a = PGADDR(PDX(a) + 1, 0, 0) - PGSIZE;
else if((*pte & PTE_P) != 0){
pa = PTE_ADDR(*pte);
if(pa == 0)
panic("kfree");
char *v = P2V(pa);
kfree(v);
*pte = 0;
}
}
return newsz;
}
Vm.c(seginit):
void seginit(void)
{
struct cpu *c;
// Map "logical" addresses to virtual addresses using identity map.
// Cannot share a CODE descriptor for both kernel and user
// because it would have to have DPL_USR, but the CPU forbids
// an interrupt from CPL=0 to DPL=3.
c = &cpus[cpunum()];
c->gdt[SEG_KCODE] = SEG(STA_X|STA_R, 0, 0xffffffff, 0);
c->gdt[SEG_KDATA] = SEG(STA_W, 0, 0xffffffff, 0);
c->gdt[SEG_UCODE] = SEG(STA_X|STA_R, 0, 0xffffffff, DPL_USER);
c->gdt[SEG_UDATA] = SEG(STA_W, 0, 0xffffffff, DPL_USER);
// Map cpu, and curproc
c->gdt[SEG_KCPU] = SEG(STA_W, &c->cpu, 8, 0);
lgdt(c->gdt, sizeof(c->gdt));
loadgs(SEG_KCPU << 3);
// Initialize cpu-local storage.
cpu = c;
proc = 0;
}