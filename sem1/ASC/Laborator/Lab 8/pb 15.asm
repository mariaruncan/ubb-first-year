bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze a+b. Sa se afiseze rezultatul adunarii in baza 16.
    mesaj_a db "a=", 0
    mesaj_b db "b=", 0
    format1 db "%d", 0
    format2 db "suma numerelor a si b este:%x", 0 
    a resd 1
    b resd 1

; our code starts here
segment code use32 class=code
    start:
        ;afisare "a="
        push dword mesaj_a
        call[printf]
        add esp, 4*1
        
        ; citire a
        push dword a        ; punem pe stiva adresa lui a
        push dword format1
        call[scanf]
        add esp, 4*2
        
        ; afisare "b="
        push dword mesaj_b
        call[printf]
        add esp, 4*1
        
        ; citire b
        push dword b        ; punem pe stiva adresa lui b
        push dword format1
        call[scanf]
        add esp, 4*2
        
        ; suma a+b
        mov eax, dword[a]
        add eax, dword[b]
        
        ; afisare suma
        push eax
        push format2
        call[printf]
        add esp, 4*2
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
