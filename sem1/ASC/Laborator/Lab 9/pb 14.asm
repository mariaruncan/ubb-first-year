bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici, litere mari, cifre si caractere speciale. Sa se transforme toate literele mari din textul dat in litere mici. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier.
    nume_fisier db "transformare.txt", 0
    mod_acces db "w", 0
    text db "aw*g7?F6q!", 0
    len equ $-text
    descriptor_fisier dd -1
    aux resb 1
    

; our code starts here
segment code use32 class=code
    start:
        ; deschidere fisier
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add ESP, 4*2
        
        mov [descriptor_fisier], EAX    ; salvam valoarea returnata de fopen
        
        cmp EAX, 0
        je Final                        ; daca fisierul nu a fost deschis cu succes, sarim la Final
        
        mov ECX, len
        jecxz Final                     ; daca nu exista caractere in text, sarim la final
        
        mov ESI, text
        cld                             ; DF=0, stanga->dreapta
        
        ; transformare litere mici in litere mari
        Bucla:
            push ECX                    ; salvam valoarea lui ECX deoarece se modifica la apelarea functiei fprintf
            lodsb
            mov [aux], AL
            
            cmp byte[aux], 'a'
            jb Pass
            cmp byte[aux], 'z'
            ja Pass
            add byte[aux], 'A'-'a'
            
            Pass:
            push dword aux
            push dword [descriptor_fisier]
            call [fprintf]
            add ESP, 4*2
            
            pop ECX
        loop Bucla
        
        ;inchidere fisier
        push dword [descriptor_fisier]
        call [fclose]
        add ESP, 4
        
        Final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
