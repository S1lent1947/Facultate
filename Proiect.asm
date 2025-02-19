.MODEL small
.stack 200h

.DATA
    msg1 DB 13,10,'Introdu primul numar (0-9): $'
    msg2 DB 13,10,'Introdu al doilea numar (0-9): $'
    msg_result DB 13,10,'Rezultatul inmultirii: $'
    msg_par DB 13,10,'Rezultatul este PAR. $'
    msg_impar DB 13,10,'Rezultatul este IMPAR. $'
    num1 DB ? 
    num2 DB ?
    rezultat DW ?
.CODE

start:
    ; Initializare segment date
    mov ax, @data
    mov ds, ax

    ; Citire primul numar
    mov dx, offset msg1
    mov ah, 09h
    int 21h

    mov ah, 01h
    int 21h
    
    sub al, '0'        ; Converteste caracterul in numar
    mov num1, al

    ; Citire al doilea numar
    mov dx, offset msg2
    mov ah, 09h
    int 21h

    mov ah, 01h
    int 21h
    sub al, '0'        ; Converteste caracterul in numar
    mov num2, al

    ; Inmultire numere
    mov al, num1
    mul num2          ; AL * num2 -> AX
    mov rezultat, ax

    ; Afisare rezultat inmultire
    mov dx, offset msg_result
    mov ah, 09h
    int 21h

    mov ax, rezultat
    mov cx, 10
    mov bx, 0

convert_in_ascii:
    xor dx, dx
    div cx               ; Imparte AX la 10
    add dl, '0'          ; Converteste cifra in ASCII
    push dx              ; Salveaza cifra pe stiva
    inc bx               ; Creste numarul de cifre
    cmp ax, 0
    jne convert_in_ascii

print:
    pop dx               ; Scoate cifrele de pe stiva
    mov ah, 02h
    int 21h 
    dec bx
    jnz print

    ; Verificare paritate
    mov ax, rezultat
    and al, 1            ; Verifica ultimul bit
    jz par

impar:
    mov dx, offset msg_impar
    mov ah, 09h
    int 21h
    jmp finish

par:
    mov dx, offset msg_par
    mov ah, 09h
    int 21h

finish:
    ; Terminare program
    mov ah, 4ch
    int 21h

end start
