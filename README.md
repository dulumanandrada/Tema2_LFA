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

<img width="988" alt="Captură de ecran din 2022-05-24 la 15 05 43" src="https://user-images.githubusercontent.com/94484148/170030659-ab54e690-bf3c-44af-96da-f4b7aaa19866.png">

<img width="579" alt="Captură de ecran din 2022-05-24 la 15 05 58" src="https://user-images.githubusercontent.com/94484148/170030721-3f4a6fe9-2b68-4941-975b-02be6265ac77.png">
