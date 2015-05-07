//test zmiana
0.
Wszelkie zmiany w pliku vimrc.local (regulacja parametrow) beda widoczne
dopiero po tym jak zapisze sie ten plik, zamknie VIM i otworzy ponownie. Pliki
konfiguracyjne sa odczytywane tylko podczas otwierania VIM.

Program moze dzialac w trybie generacji losowych danych oraz w trybie
wlasciwym, czyli poszukiwania rozwiazania optymalnego - zalezy od opcji.

Oznaczenia literek - parametrow w komendzie definiujacej skrot klawiaturowy w
vimrc.local:

-l<filename> - laduj dane wejsciowe z pliku (BRAK SPACJI!)
-d - demo - nic specjalnego
-s<filename> - (tylko tryb generacji) zapisuje dane w pliku pod wskazana sciezka
-n - (tylko tryb generacji) liczba miast, wzdluz ktorych obliczana jest trasa,
jak sa reprezentowane w pliku to omawialismy, to jest ograniczone do 255 -
robi mod 256 bo zmienna jest zapisana na 8 bitach.
-p - liczba chromosomow w populacji (default: 20)
-a - liczba najlepszych chromosomow z poprzednej generacji bezposrednio
przepisanych do kolejnego pokolenia (default: 2)
-c - typ operatora krzyzowania - na razie tylko jeden (default: 1 - the only implemented)
-g - liczba nowogenerowanych chromosomow w kazdej populacji (patrz nizej) (default: 2)
-i - max liczba iteracji (default: 100)
-x - prawd. krzyzowania (default: 0.8)
-y - prawd. mutacji (default: 0.4)
-v - prog poprawy, ponizej ktorego uznaje sie ze brak poprawy (default: 0.5 %)
-w - ilosc KOLEJNYCH iteracji bez poprawy, ktora przerywa algorytm (default:
10)

np. zeby wygenerowac 10 miast do pliku abc.txt z glownego katalogu:
./build/main -n 10 -s"abc.txt"

odpalanie jest jako skrot klawiaturowy bo pisac to recznie to do pozygu
byloby.

Parametrami trzeba poslugiwac sie z mozgiem, tzn. jak jest 10 chromosomow w
populacji i ustawi sie a=10 i g=10 to nie bedzie zadnego krzyzowania. Nie
ma na takie bzdety zabezpieczen. a moze smialo byc 0 i g tez, wtedy bedzie
tylko selekcja i krzyzowanie.

Dla -x 0.2 i -y 0.2 cos sie wywalalo, prawdopodobnie zbyt niskie wartosci i
psuje mi sie operator krzyzowania ale nie zdazylem naprawic. dla 0.3 podobnie.
Byc moze nie zostal wylosowany zaden chromosom do skrzyzowania i to powoduje 
jakies problemy, pewnie z pustym wektorem do ktorego sie odwoluje albo cos
podobnego.

Po odpaleniu wynikowy wynik laduje w folderze files w pliku output.txt. Plik
sie dopisuje do konca ale niestety nie zrobilem przepisywania parametrow
danego uruchomienia.
jest tabelka z kolejnymi rekordami oraz zwycieski chromosom - nasza pozadana
kolejnosc przystankow.

1. 
Zastosowano reprezentacje sciezkowa chromosomow.
Dlugosc chromosomu jest zawsze rowna ilosci miast do przejechania i elementy
wewnatrz chromosomu nie powtarzaja sie bo jezeli zakladamy nieograniczona 
pojemnosc pojazdu to i tak zabieram z danego przystanku wszystkich wiec jadac 
przez ten sam przystanek drugi raz kogo mialbym zabrac? Liczenie tych samych
pasazerow po raz drugi odbiega od rzeczywistego przypadku.
Tak tez jest skonstruowany operator krzyzowania PMX aby nie powstawaly
chromosomy, w ktorych dubluja sie jakies geny (rekurencyjna look up table).

2.
Dystans dla chromosmu to suma odleglosci miedzy miastami wzdluz sciezki.
Wartosc chromosomu to suma dystansow wszystkich pasazerow zabranych wzdluz tej
sciezki (mozna powiedziec ze to cena, gdyby stawka za 1 km wynisila 1zl).

3.
Kontrolowanie maksymalnej ilosci roznych chromosomow. 
a) Rozmiar populacji dla przypadku gdy przejezdzamy przez wszystkie miasta:
Oznacza to, ze kazdy chromosom jest dlugosci x gdzie x to liczba miast. Wiadomo
z kombinatoryki, ze x miast mozna permutowac na x! sposobow wiec aby kazdy
chromosom byl unikalny w skali populacji to maksymalny rozmiar populacji jest
rowny x! Dla ulatwienia (zeby uniknac w programie liczenia duzych silni)
zakladamy, ze maksymalny rozmiar populacji dla 5 lub wiecej miast to 60 bo
120=5!, a nie chcemy otrzymac wszystkich chromosomów w pierwszej populacji
wiec na przyklad dopuszczamy maksymalnie polowe (wartosc umowna). Jezeli
zostanie ustawiona wieksza wartosc a liczba miast wynosi co najmniej 5 to
rozmiar populacji jest automatycznie zmniejszany do wartosci maksymalnej 60.
Dla liczby miast mniejszej niz 5 rozmiar takze jest zmniejszany ale do wartosci
odpowiedniej zaleznej od liczby miast (1,2 - program nic nie liczy), dla 3
jest to 3 a dla 4 - 12 (polowa silni).

4.
Ocena populacji.
Dla kazdego chromosomu w populacji jest obliczana funkcja oceny w nastepujacy
sposob: chromosom to ciag kolejnych przystankow - sciezka wzdluz wierzcholkow.
Dla kazdego przystanku pobierana jest lista pasazerow i z listy wybierani sa 
pasazerowie tylko Ci, ktorych przystanek docelowy - wierzcholek - zawiera sie
w sciezce danego chromosomu. Jezeli pasazer jest zabierany na poklad wtedy
obliczana jest cena jego biletu - dlugosc sciezki miedzy przystankiem, na
ktorym wsiadal a tym na ktorym wysiada liczona zgodnie z kolejnoscia
wierzcholkow dla danego chromosomu.
Ceny sprzedanych biletow dla kazdego pasazera tworza w sumie zysk calkowity z
danej sciezki.
Jednoczesnie obliczana jest calkowita dlugosc przebytej trasy wzdluz
wierzcholkow wskazanych przez ten chromosom.
Iloraz sumy cen sprzedanych biletow oraz calkowitej dlugosci trasy daje wynik
funkcji oceny - wspolczynnik zysk na kilometr. Im wyzsza wartosc tego
wspolczynnika tym bardziej oplaca sie wybrac taka trase.  

W kazdej populacji po jej ocenie jest robione sortowanie - ranking.

5.
Generacja kolejnej populacji.
W danej populacji jest p chromosomow. Prawdopodobienstwo krzyzowania wynosi x,
prawdopodobienstwo mutacji wynosi y. Liczba najlepszych chromosomow, ktore
przechodza nienaruszone wynosi a. Liczba nowogenerowanych wynosi g.
PARAMETRY a I g NALEZY DOBIERAC ROZSADNIE - nie ma zabezpieczen przed glupimi
wartosciami, np. jezeli p=20 to a=2 i g=3 jest ok ale p=10 a=2 g=8 jest o tyle
bez sensu, ze zadne chromosomy nie zostana wybrane w procesie selekcji bo
10 - 8 - 2 = 0.
Tak wiec w nowej populacji otrzymamy a chromosomow z poprzedniej, p - a - g z
procesu selekcji (z ktorych niektore skrzyzuja) oraz g nowo wygenerowanych.

Jesli zwiekszamy a to rosnie napor selekcyjny, czyli koncentracja na
najlepszych osobnikach ale maleje wtedy roznorodnosc populacji. Zmniejszajac a
sytuacja jest odwrotna. Parametr g daje mozliwosc zwiekszenia udzialu
nowogenerowanych rozwiazan - spoza obecnego obszaru. 
Istotna jest liczebnosc populacji. Odpowiedni
dobor tych parametrow jest kompromisem pomiedzy szerokim badaniem przestrzeni
rozwiazan a korzystaniem z wczesniej otrzymanych dobrych wynikow.

6.
Selekcja.
zrobione zgodnie z zasada ruletki opisana w ksiazce na str 59
wybierana jest liczba chromosomow = p - a - g
p - rozmair populacji, a - ile przodkow przechodzi nieruszonych,
g - ile nowych chromosomow jest losowo generowanych

7. 
Krzyzowanie.
W procesie selekcji wybrano p - a -g chromosomow - kandydatow do skrzyzowania.
Dla kazdego chromosomu otrzymanego w rezultacie selekcji generowana jest liczba losowa
r. Jezeli r<x (prawd. krzyz.) to chromosom jest wybierany do krzyzowania.
Jezeli r>=x to przechodzi do nowej populacji w swojej wczesniejszej postaci.
Wektor chromosomow wybranych do krzyzowania dla ulatwienia powinien miec
parzysta liczbe elementow, jezeli tak nie jest to zastosowano trik:
pierwszy element kandydatow do krzyzowania jest powtorzony na koncu a dla zgodnosci 
z wektorow, ktore przeszly we wczesniejszej postaci usuwany jest ostatni. 
Wtedy dalej zgadza sie liczba wektorow wyselekcjonowanych, ktore przeszly we
wczesniejszej postaci oraz tych, ktore beda skrzyzowane i wynosi p -a -g.
Kazde dwa chromosomy do skrzyzowania daja dwa nowe chromosomy w rezultacie,
dlatego liczba otrzymanych po krzyzowaniu jest rowna liczbie kandydatow do
krzyzowania. Chromosomy kandydaci do krzyzowania tworza pary, ktore sa poddawane
krzyzowaniu. Ile z wektorow wyselekcjonowanych zostanie kandydatami do
krzyzowania to zalezy od prawd. krzyzowania - WAZNY PARAMETR. Przy niskim 
prawd. krzyzowania mala czesc wyselekcjonowanych zostanie skrzyzowanych, 
przy wysokim duza.

Operator krzyzowania PMX
Najpierw wybierane sa dwa losowe punkty ciecia cut1 i cut2 - moga byc inne w
kazdym pokoleniu ale w zakresie jednej populacji pozostaja stale. Punkty sa
wybierane losowo i cut1 < cut2.

Innych nie zdazylem zaimplementowac chociaz program jest na to gotowy.

8. 
Mutacja
Z calej populacji wybierane jest p*y chromosomow, ktore zostana poddane
mutacji. Mutacja polega na zaminieniu ze soba miejscami dwoch losowo wybranych
genow wewnatrz chromosomu. p to rozmiar populacji a y to prawdopodobienstwo
mutacji (iloczyn jest zaokraglany w dol do liczby calkowitej). Jeden chromosom
moze zostac wybrany dwukrotnie do zmutowania.

9. 
Przerwanie iteracji
Albo gdy osianieta zostanie maksymalna ilosc iteracji ustawiona parametrem -i
albo gdy przez kolejne -w iteracji poprawa bedzie mniejsza niz prog -v to
wtedy tez algorytm uznaje, ze juz nic sie nie poprawia i lepiej skonczyc
liczyc a najlepsze dotad rozwiazanie przyjac za zadowalajace.

10.
Dodatkowo jest jeden przykladowy plik, ktory drukuje wszystkie chromosomy w
populacji.

11.
WYNIKI:
- przeglad dla duzych instancji testowych (np. 100 miast) dla roznych
  parametrow x i y
- wykres jak zmieniaja sie wyniki wraz ze zmiana tych parametrow a raczej
  szybkosc i ksztalt ich uzyskiwania (jakos tak) - z tabelek trzeba rypnac
wykresy - kilka z opisami tez bedzie w repozytorium.
- zbadac wplyw operatorow - tutaj dupa bo mamy tylko jeden :(

co do wykresu to ma byc na pionowej osi wartosc funkcji celu a na poziomej
indeks kolejnych iteracji.

