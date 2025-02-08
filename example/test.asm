@str "Hello, world!"
.main
    num 10
    mov 0, 2
    num 1
    mov 0, 1
loop:
    outnum 0
    add
    mov 2, 1
    cmp
    mov 0, 4
    num 1
    mov 0, 1
    mov 4, 0
    jle loop
    outstr str
    ret