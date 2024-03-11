#include <stdio.h>
#include <openssl/bn.h>
#define NBITS 256

void printBN(char *msg, BIGNUM *a){
// Convert the BIGNUM to number string
char * number_str = BN_bn2hex(a);
// Print out the number string
printf("%s %s\n", msg, number_str);
// Free the dynamically allocated memory
OPENSSL_free(number_str);
}

int main(){
BN_CTX *ctx = BN_CTX_new();
BIGNUM *p = BN_new();
BIGNUM *q = BN_new();
BIGNUM *e = BN_new();
BIGNUM *d = BN_new();
BIGNUM *res1 = BN_new();
BIGNUM *res2 = BN_new();
BIGNUM *res3 = BN_new();
BIGNUM *one = BN_new();
// กำหนดค่า p q e ตามที่โจทย์ให้
//โดยใช้ hex2bn เปลี่ยนเลขฐาน 16 เป็น Bignum
BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
BN_hex2bn(&e, "0D88C3");

// Assign the Modulus
//ใช้ dec2bn เปลี่ยน decimal เป็น Bignum
//หา p-1 และ q-1 แล้วเก็บไว้ใน res1 และ res2 หลังจากนั้นใช้ res3 เก็บค่า (p-1)(q-1)
BN_dec2bn(&one,"1");
//res1 = p-1
BN_sub(res1, p, one);
//res2 = q-1
BN_sub(res2, q, one);
//res3=res1*res2
BN_mul(res3, res1, res2, ctx);
//ใช้ mod_inverse เพื่อ Generate Key
BN_mod_inverse(d, e, res3, ctx);
//print BN
printBN("d= ",d);
return 0;
}
      
