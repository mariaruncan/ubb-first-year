; Se dau cuvintele A si B. Se cere cuvantul C format astfel:
;- bitii 0-2 ai lui C coincid cu bitii 10-12 ai lui B
;- bitii 3-6 ai lui C au valoarea 1
;- bitii 7-10 ai lui C coincid cu bitii 1-4 ai lui A
;- bitii 11-12 ai valoarea 0
;- bitii 13-15 ai lui C concid cu inverul bitilor 9-11 ai lui B

; Vom obtine cuvantul C prin operatii succesive de "izolare". Numim operatia
; de izolare a bitilor 10-12 ai lui B, pastrarea intacta a valorii acestor
; biti, si initializarea cu 0 a celorlalti biti. Operatiunea de izolare se
; realizeaza cu ajutorul operatorului and intre cuvantul B si masca
; 0001110000000000. Odata bitii izolati, printr-o operatie de rotire se
; deplaseaza grupul de biti doriti in pozitia dorita. Cuvantul final se
; obtine prin aplicarea operatorului or intre rezultatele intermediare
; obtinute in urma izolarii si rotirii.
; Observatie: rangul bitilor se numara de la dreapta la stanga

bits 32 ;asamblare si compilare pentru arhitectura de 32 biti
; definim punctul de intrare in programul principal
global  start 

extern  exit ; indicam asamblorului ca exit exista, chiar daca noi nu o vom defini
import  exit msvcrt.dll; exit este o functie care incheie procesul, este definita in msvcrt.dll
        ; msvcrt.dll contine exit, printf si toate celelalte functii C-runtime importante
segment  data use32 class=data ; segmentul de date in care se vor defini variabilele 
     a dw 0111011101010111b
     b dw 1001101110111110b
     c dw 0
     ; c = ib11 ib10 ib9 0 0 a4 a3 a2    a1 1 1 1 1 b12 b11 b10
segment  code use32 class=code ; segmentul de cod
start: 

     mov  bx, 0 ; in registrul bx vom calcula rezultatul

     mov  ax, [b] ; izolam bitii 10-12 ai lui b
     and  ax, 0001110000000000b   ; ax = 0 0 0 b12     b11 b10 0 0     0 0 0 0    0 0 0 0
     mov  cl, 10
     ror  ax, cl ; rotim 10 pozitii spre dreapta    ax = 0 0 0 0   0 0 0 0    0 0 0 0    0 b12 b11 b10
     or   bx, ax ; punem bitii in rezultat       bx = 0 0 0 0   0 0 0 0    0 0 0 0    0 b12 b11 b10

     or   bx, 0000000001111000b ; facem biti 3-6 din rezultat sa aiba valoarea 1     bx = 0 0 0 0   0 0 0 0   0 1 1 1   1 b12 b11 10

     mov  ax, [a] ; izolam biti 1-4 ai lui a    
     and  ax, 0000000000011110b     ; ax = 0 0 0 0   0 0 0 0    0 0 0 a4   a3 a2 a1 0
     mov  cl, 6
     rol  ax, cl ; rotim 6 pozitii spre stanga    ax = 0 0 0 0  0 a4 a3 a2   a1 0 0 0   0 0 0 0
     or   bx, ax ; punem bitii in rezultat        bx = 0 0 0 0  0 a4 a3 a2   a1 1 1 1   1 b12 b11 b10

     and  bx, 1110011111111111b ; facem biti 11-12 din rezultat sa aiba valoarea 0

     mov  ax, [b]
     not  ax ; inversam valoarea lui b   
     and  ax, 0000111000000000b ; izolam biti 9-11 ai lui b   ax = 0 0 0 0  ib11 ib10 ib9 0   0 0 0 0   0 0 0 0
     mov  cl, 4
     rol  ax, cl ; deplasam biti 4 pozitii spre stanga    ax = ib11 ib10 ib9 0   0 0 0 0   0 0 0 0   0 0 0 0
     or   bx, ax ; punem biti in rezultat      bx = ib11 ib10 ib9 0   0 a4 a3 a2   a1 1 1 1   1 b12 b11 b10

     mov  [c], bx ; punem valoarea din registru in variabila rezultat

     push dword 0 ;se pune pe stiva codul de retur al functiei exit
     call [exit] ;apelul functiei sistem exit pentru terminarea executiei programului	
