Descrierea soluției pe cerințe

Am folosit doar 2 fisiere pentru a rezolva tema, fisierul LANparty.h drept header si LANparty.c pentru dezvoltarea tuturor functiilor.

Cerința 1

Pentru a crea lista cu echipele am decis să folosesc 3 structuri de date, prima este structura Player care conține date despre fiecare jucător:
nume, prenume și punctajul individual. A doua este structura Nod_echipa care conține datele fiecărei echipe, numărul de membri, numele echipei,
un vector dinamic de structura Player și punctajul echipei calculat prin media aritmetică a punctajelor membrilor. Structura Lista_de_echipe are un câmp
cu echipa respectivă nodului listei și un pointer către următorul nod. Am ales să implementez structura Nod_echipa cu scopul de a facilita 
manevrările ulterioare de date ale unui echipe de la o listă la alta sau de la o listă la un arbore etc. De asemenea, structura Lista_de_echipe a putut fi
utilizată ulterior pentru implementarea de stive.
Prima funcție apelată în main este citire_fisier care citește numărul n de echipe care este salvat în variabila nr_echipe,transmisă ca adresă în funcția citire_fisier
și apoi funcția apelează funcția createNode de nr_echipe ori. Această funcție citește datele din fișier corespunzătoare unei echipe și returnează o variabilă de tip Nod_echipa.
Citirea numelor echipelor s-a dovedit problematică necesitând eliminarea unor caractere \r care se aflau în fișierele de intrare ale checker-ului. După crearea nodului, acesta
se introduce la începutul listei, capul acesteia fiind reprezentat de variabila cap_lista declarată în funcția citire_fisier. Funcția de adăugare este identică cu o funcție de
push a unei stive, având și numele de push. După îndeplinirea pașilor funcția citire_fisier returnează capul listei, permițând utilizarea ei în main pentru alte cerințe.
Pentru a afișa numele echipelor am implementat funcția afisare_echipe care primește capul listei create și parcurge lista și afișează în fișier numele de echipe. O problemă care
a apărut a fost faptul că unele nume au fost citite cu un spațiu în plus la final. Problema s-a soluționat prin afișarea caracter cu caracter cu excepția ultimului în cazul
în care acesta era un spațiu.

Cerința 2

Am implementat funcția eliminare_echipe_punctaj_minim ce primește adresa capului listei de echipe și adresa numărului de echipe din listă. Mai întâi se face apelul pentru putere_maxima_a_lui_2
care calculează cea mai mare putere a lui 2 mai mică sau egală cu numărul de echipe. Pentru fiecare nod de echipă șters conținutul de la adresa numărului de echipe este decrementat. Funcția
apoi conține un while care durează până când numărul de echipe este redus la numărul necesar. Pentru a afla punctajul minim din funție se reține în variabila punctaj_minim punctajul de la cap.
Se parcurge lista și în cazul în care se descoperă o echipă de punctaj mai mic se actualizează punctajul minim și se reține adresa minimului în variabila echipa_de_punctaj_minim.
După parcurgerea întregii liste, se șterge nodul echipa_de_punctaj_minim. Aici există 2 cazuri pentru care se implementează 2 funcții diferite. Una pentru a șterge capul listei și alta
pentru a șterge un nod din interior. Ultima instrucțiune din while este decrementarea conținutului de la adresa numărului de echipe.
În urma acestui while funcția se termină și se afișează în main lista actualizată.

Cerința 3

Sunt folosite 2 structuri pentru coada de meciuri, Meci și Queue. Meci conține 2 date de tip Nod_echipa și adresa următorului Meci,iar Queue are adresa primului și ultimului meci.
Funcția principală la această cerință este funcția matchmaker, care primește adresa listei cu echipe, adresa listei care va fi folosită pentru primele 8 echipe și numărul de echipe
(pentru a determina numărul de runde). Mai întâi se creează coada cu meciurile și apoi se apelează matchfiller care parcurge lista și pune câte 2 echipe în coada de meciuri folosind o funcție
enqueue tipică(creează un nod de tip Meci care conține cele 2 echipe și îl adaugă la finalul cozii). După aceea se declară 2 int-uri, unul pentru numărul rundei(se incrementează la fiecare rundă) și altul pentru numărul de echipe rămase.
Într-un while se va efectua afișarea de meciuri și câștigători cât timp numărul de echipe rămase este mai mare decât 1(numărul se împarte la 2 la începutul while-ului). Mai întâi se golește coada folosind un 
dequeue care returnează adresa Meciului. Funcția matchprint afișează meciul în sine(aici a trebuit să efectuez aceleași măsuri ca în funcția afisare_echipe pentru a evita afișarea de spații nedorite). În funcție de echipa din meci cu mai multe puncte
se apelează funcția add_in_stacks care preia cele 2 echipe din meci și stack-urile de învingători și pierzători și face push celor 2 echipe în stack-urile corespunzătoare(de asemenea actualizează
punctajul echipei prin incrementarea punctajelor membrilor echipei și recalcularea mediei punctelor).
După ce se golește coada se șterge stiva de pierzători cu funcția delete_losers. După aceea se intră într-un alt while care rulează până când se golește stiva de învingători. Aici se apelează funcția pop de 2 ori urmată 
de teamprint a 2 echipe. Teamprint primește un Nod_echipa și afișează numele echipei și punctajul echipei. După aceea se iau cele 2 echipe scoase și se folosește enqueue pentru a repopula coada cu noi meciuri.
Dacă numărul de echipe curente este egal cu 8 se adaugă cele 2 echipe la sfârșitul listei cu primele 8 echipe, iar dacă numărul de echipe curente este egal cu 1 nu se aplică pașii precenți, doar se scoate echipa din stivă
și se afișează cu teamprint ultima echipă rămasă.

Cerința 4

Structura de date folosită aici este numită sugestiv Arbore, conține un Nod_echipa și adrese către cei 2 copii. Arborele este creat cu funcția generate_arbor care primește lista cu primele 8 echipe.
Se declară rădăcina root și se parcurge lista. Fiecare Nod_echipa de la fiecare termen al listei este transmis către funcția insert_node_in_tree.
Aceasta are caracter recursiv. Dacă ajunge într-un root NULL va crea noul nod cu funcția new_nod_in_tree(preia Nod_echipa-ul corespunzător și returnează un Arbore*) și returnează root-ul.
Altfel, se procedează ca la un binary search tree, dacă punctajul echipei de introdus este mai mic decât nodul curent se introduce noul nod la stânga, în caz contrar la dreapta.
Dacă punctajele sunt egale se va pune în funcție de numele echipei în ordine descrescătoare. După introducerea celor 8 echipe arborele se parcurge într-o inordine de tip right-root-left(cu scopul de a
afișa echipele în ordine descrescătoare a punctajelor, odată ce echipa de punctaj maxim se situează în cel mai de dreapta nod) cu funcția inorder și se afișează numele echipei împreună cu punctajul corespunzător.
În final, funcția generate_arbor returnează arborele creat pentru a putea fi folosit la cerința 5.

Cerința 5

Am declarat o structură numită AVL care reprezintă arborele de tip AVL. Este asemănătoare cu Arbore, cu excepția adăugării unui nou câmp care reține înălțimea nodului respectiv(calculată cu funcția height, cu caracter recursiv). la această cerință am implementat
funcția afisare_in_arbore_AVL care primește arborele generat la cerința 4. Mai întâi se apelează funcția generate_AVL, aceasta parcurge arborele în inordine ca la 4, preia echipa respectivă și o transmite funcției insert_in_AVL.
În acest mod se introduc echipele în ordine descrescătoare, un lucru avantajos deoarece se introduc noi frunze doar la stânga celui mai din stânga nod. În plus, acest fapt face ca singura funcție de rotație tipică unui arbore AVL
necesară aici să fie rotația la dreapta în cazul în care lumgimea subarborelui stâng al nodului curent să fie mai mare cu mai mult de 1 decât cel drept. După umplerea arborelui am implementat funcția printlevel pentru a afișa echipele de pe nivelul 2.
Aceasta primește AVL-ul și un int care reprezintă nivelul. Dacă nivelul primit e 0 atunci afișează numele echipei de la acel nod de arbore. Altfel apelează recursiv funcția pentru copiii nodului transmițând la int level-1.
Astfel se apelează în afisare_in_arbore_AVL printlevel cu level=2. La final se șterge AVL-ul folosind o funcție de ștergere recursivă care parcurge arborele în postordine.

Main

Acesta conține variabile pentru numărul de echipe,lista de echipe, lista cu primele 8 echipe, primul arbore și un vector dinamic în care sunt înregistrate cele 5 numere din fișierul c.in. În main se deschid fișierele c.in și r.out, d.in se deschide și se închide
în funcția citire_fisier(de aceea aceasta primește un string cu numele fișierului). Mai întâi se citește conținutul din c.in. Apoi se creează lista în forma ei inițială. Apoi urmează o serie de if-uri care efectuează funcțiile corespunzătoare task-urilor
în funcție de datele înregistate în vectorul taskuri(de exemplu dacă taskuri[2]==0 atunci înseamnă că nu se efectuează task-ul 3). La sfârșitul main-ului se închid fișierele și se șterg listele împreună cu arborele de tip Arbore generat anterior.

Concluzii

Efectuarea temei mi-a ridicat câteva probleme la implementare precum gestionarea unor caractere și spații neașteptate din d.in. Lucrul modularizat cu multe funții și o mulțime de structuri de date s-a dovedit o experiență utilă, fiind prima oară
când am efectuat un proiect de acest fel. Am învățat cum să lucrez cu un checker, activitate care m-a "forțat" să lucrez pe Linux și VSCode proiectul, ceea ce nu am mai încercat până acum. Mi s-a părut interesantă provocarea de a lucra cu mai
multe structuri de date și consider că am reușit acum să le înțeleg în mare parte avantajele și dezavantajele. Exercițiul lucrului cu alocare dinamică a fost foarter util, dar o să admit că nu am reușit o eliberare corectă și totală de memorie. Am încercat mai
multe opțiuni dar acestea rezultau în checker-ul afișând erori după unele teste care uneori cauzau ca testul să eșueze, alteori nu.
Cel mai probabil este cauzată de faptul că structura Nod_echipa nu a fost lucrată ca un pointer. Am realizat mult prea târziu că nu e bine că am folosit-o așa. Cu mai multă atenție din partea mea aș fi putut probabil să ajung la o implementare mult
mai eficientă din punct de vedere al memoriei dar îmi asum greșeala de implementare. Am învățat cum să procedez mai bine în viitor. În cele din urmă, cu excepția unor părți de memorie folosită prost, implementarea mea a fost relativ bună,
dar și algoritmii pe care i-am folosit puteau fi cel mai probabil optimizați în unele segmente de program, precum la cerința 3.
În concluzie, am ajuns la o soluție care a reușit să genereze fișierele r.out corecte și am putut să pun în aplicație cunoștințe legate de implementarea mai multor tipuri de structuri de date, chiar dacă în anumite locuri codul își pierde eficiența.
Sper ca explicațiile oferite în acest document să fie suficient de clare.                             




