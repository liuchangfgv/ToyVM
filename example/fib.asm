//int fib(int n) {
//    if (n <= 1) {
//        return 1;
//    }
// return fib(n - 1) + fib(n - 2);
//}

.fib
    // n pop from stack
    pop ecx
    
    mov ecx, ebx
    num 1
    // if n <= 1
    cmp
    jge taga  // return n

    // fib(n - 1)
    num 1
    mov eax, ebx
    mov ecx,eax
    sub // n-1
    push eax
    call fib
    pop edx

    // fib(n - 2)
    num 2
    mov eax, ebx
    mov ecx, eax
    sub // n-2
    push eax
    call fib
    pop eax

    // add fib(n - 1) and fib(n - 2)
    mov edx, eax
    add

    //return
    push eax
    ret
taga:
    num 1
    push eax
    ret

//int main(){
//    for (int i = 0; i <5;i++){
//        outnum(fib(i));
//    }
//}
.main
    num 5
    mov eax, ecx
    num 1
    mov eax, ebx
    mov eax, 16 // 16 is number 1
    num 0
    mov eax, edx
loop:
    push eax
    call fib
    pop eax
    outnum eax
    mov 16, ebx
    add
    mov ecx, ebx
    cmp
    jle loop
    ret