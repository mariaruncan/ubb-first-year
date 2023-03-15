bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a. Se dau doua siruri de cuvinte a si b. Sa se obtina sirul c astfel:
        ; - concatenati sirul octetilor low din primul sir cu sirul octetilor high din al doilea sir.
        ; - sirul c se va ordona crescator
        ; - numerele din siruri se vor interpreta cu semn
        ; - afisati sirul c (numere in baza 16)
        ; Exemplu:
        ; a = 1234h,5678h,90h
        ; b = 4h,0abcdh,10h,1122h
        ; c = 34h, 78h, 90h, 00h, 0abh, 00h, 11h -> 00h, 00h, 11h, 34h, 78h, 90h, 0abh
    a dw 1234h, 5678h, 90h
    len_a equ ($-a)/2
    b dw 4h,0abcdh,10h,1122h
    len_b equ ($-b)/2
    c resb len_a + len_b
    format db "%x", 0
    nume_fisier db "output.txt", 0
    mod_acces db "a", 0
    descriptor_fisier dd 0
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, len_a
        jecxz pass1
        
        mov esi, a
        mov edi, c
        
        octeti_low_a:
            lodsw       ; esi=esi+2
            stosb       ; edi=edi+1
        loop octeti_low_a
        
        pass1:
        
        mov ecx, len_b
        jecxz pass2
        
        mov esi, b
        
        octeti_high_b:
            lodsw       ; esi=esi+2
            push ecx
            mov cl, 8
            shr ax, cl  ; rotim bitii lui ax cu 8 poz ca in al sa fie octetul high din ax
            stosb       ; edi=edi+1
            pop ecx
        loop octeti_high_b
        
        pass2:
        
        mov dl, 1       ; DL=variabila semafor pentru verificare daca sirul este sortati; DL=1 pt sir neosrtat, altfel DL=0 
    
        bubble_sort:
            cmp dl, 0
            jz sfarsit_bubble_sort
            mov dl, 0
            mov ecx, len_a+len_b-1            
            mov esi, c              ; acum c este sir sursa
            comparare:
                mov al, [esi]
                mov bl, [esi+1]
                cmp al, bl          ; comparam doua elemente consecutive ale sirului
                jbe pass3
                mov [esi], bl
                mov [esi+1], al     ; in caz ca el1>el2, le interschimbam si DL devine 1
                mov dl, 1
            
            pass3:
                inc esi
            loop comparare
        
        jmp bubble_sort
        
        sfarsit_bubble_sort:
        
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor_fisier], eax
        
        mov ecx, len_a+len_b
        mov esi, 0
        
        afisare:
            push ecx
        
            mov ebx, 0
            mov bl, [c+esi]
            
            push ebx
            push dword format
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4*3
          
            inc esi
            pop ecx
        loop afisare
        
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4*1
       ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
