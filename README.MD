## MD5 HASH GENERATOR

C program that demonstrates the basic working of the MD5 message-digest algorithm.

#### Running the program

```
gcc md5.c -o test
./test
```

End of file character terminates input

#### What to expect

The program is the barebones version of the MD5 algorithm in that it can handle only 448 bits of input(equal to one block in the MD5 scheme).<br>

The program prints the digest in little endian.<br>

The code is not thoroughly tested,so some errors are to be expected.(I have come across none so far)<br>

The explanation of the algorithm in totality can be found [here](https://en.wikipedia.org/wiki/MD5#Algorithm)



