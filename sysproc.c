#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"


extern int worldpeace(void);
extern int numberofprocesses(void);
extern int spawn(void);
extern int getvasize(void);
extern int va_to_pa(void);
extern int get_pgtb_size(void);
extern int get_usr_pgtb_size(void);
extern int get_kernel_pgtb_size(void);
extern int getpasize(void);
extern int mmap(void);


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}


int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}


int sys_worldpeace(void){
    return worldpeace();
}
// This functin call returns number of processes in the runnable state 
 int sys_numberofprocesses(void){
    return numberofprocesses();
}

// This function call is used to create a n child process. This returns the list
// of pids of the child processes created and 0 to the child process.
 int sys_spawn(void){
    return spawn();
}

// This function call returns the size of the virtual address space of the process
 int sys_getvasize(void){
     return getvasize();
}
// This function call returns the physical address of the virtual address
 int sys_va_to_pa(void){
    return va_to_pa();
}
// This function call returns the size of the page table of the process
 int sys_get_pgtb_size(void){
      return get_pgtb_size();
}

// This function call returns the size of the user page table of the process
 int sys_get_usr_pgtb_size(void){
    return get_usr_pgtb_size();
}
// This function call returns the size of the kernel page table of the process
 int sys_get_kernel_pgtb_size(void){
    return get_kernel_pgtb_size();
}
// This function call returns the size of the physical address space of the process
 int sys_getpasize(void){
    return getpasize();
}

// This function call is used to allocate a page of memory
 int sys_mmap(void){
    return mmap();
}



int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
