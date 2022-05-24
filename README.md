# Tema2_LFA
DFA-minimal

Un algoritm care are ca input un DFA si face transformarea acestuia paa intr-o forma minimala a sa. Aceste are la baza Teorema lui Myhill-Nerode.
Teorie: https://www.geeksforgeeks.org/minimization-of-dfa-using-myhill-nerode-theorem/?ref=rp

Cum functioneaza?
  - separam starile in 2 grupe: stari nefinale si stari finale.
  - marcam starile de forma (Qa, Qb), unde Qa este stare finala, iar Qb este stare nefinala.
  - daca (Qa, x) si (Qb, x) sunt marcate, atunci vom marca si (Qa, Qb).
  - repetam procesul anterior pana ce nu vom mai aduce nicio modificare.

Observatii:
  - grupa initiala este grupa ce contine starea initiala.
  - grupele finale sunt cele ce contin o stare finala.
  
  ## Modele de DFA-minimal:
 
<img width="411" alt="Captură de ecran din 2022-04-03 la 01 30 05" src="https://user-images.githubusercontent.com/94484148/161403398-d8045259-f6b6-4e27-b25c-5086535d049a.png">

<img  width="411" alt="ex1" src= "https://user-images.githubusercontent.com/94484148/170030156-ae9a8010-8f94-4f16-b801-456ffbb65bb1.png">
