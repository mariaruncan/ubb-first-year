bits 32
global start

extern exit, fopen, fgets, fclose, printf

import exit msvcrt.dll
import fopen msvcrt.dll
import fgets msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll


extern adauga_la_sir

segment data use32 class=data public
    nume_fisier db "numere.txt", 0
    mod_acces db "r", 0
    descriptor dd 0
    numar times 100 db 0
    contor_negative dd 0
    contor_pozitive dd 0
    N times 100 db 0
    P times 100 db 0
    format_neg db "Numere negative: %s ", 0Ah, 0
    format_poz db "Numere pozitive: %s", 0


segment code use32 class=code public
    start:
        ; Se citesc din fisierul numere.txt mai multe numere (pozitive si negative). Sa se creeze 2 siruri rezultat N si P astfel: 
        ; N - doar numere negative si P - doar numere pozitive. Afisati cele 2 siruri rezultate pe ecran.
         
        ; deschidere fisier
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        jz sfarsit
    
        mov [descriptor], eax
        
        ; citire linie cu linie
        citire:
            push dword [descriptor]
            push dword 100
            push dword numar
            call [fgets]
            add esp, 4*3
            
            cmp eax, 0
            je gata
            
            cmp byte[numar], "-"
            je negativ
            
            jmp pozitiv
            
            ; adauga_la_sir(sir_dest, sir_sura, contor)
            negativ:
                push dword [contor_negative]
                push dword numar
                push dword N
                call adauga_la_sir
                add esp, 4*3
                
                mov [contor_negative], ebx  ; actualizam contorul
                
                jmp next
                
            pozitiv:
                push dword [contor_pozitive]
                push dword numar
                push dword P
                call adauga_la_sir
                add esp, 4*3
                
                mov [contor_pozitive], ebx  ; actualizam contorul
            
            next:
         
        jmp citire
        
        gata:
        
        ; inchidere fisier
        push dword [descriptor]
        call [fclose]
        add esp, 4*1
        
        ; afisare siruri
        push dword N
        push dword format_neg
        call [printf]
        add esp, 4*2
        
        push dword P
        push dword format_poz
        call [printf]
        add esp, 4*2
        
        sfarsit:
        
        push    dword 0
        call    [exit]
