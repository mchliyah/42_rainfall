# level0 

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


the program convert the argv to int and skip 4 bytes to fall into argv\[1\] "skip the binary ./level0" 

then conpaire with 0x1a7 => 423  to run the "/bin/sh"

```bash
level0@RainFall:~$ ./level0 423
$ cd ../level1
$ cat .pass*
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
$ 
```