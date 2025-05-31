# Aprašymas

Programa, skirta apdoroti studentų duomenis.
Programos versijose analizuojamas bei tobulinamas programos našumas, efektyvumas bei paruošimas vartotojuj.

Yra sukurta programos dokumentacija - `dokumentacija.pdf`.

# Naudojimo instrukcijos

**Kad paleisti programą, turite atlikti šiuos veiksmus:**

1. Paleiskite `setup.exe` ir leiskite įdiegti programą
2. Programa bus įdiegta -> `Program Files` -> `VU` -> `Neda` kataloge
3. Paleiskite `Objektinis.exe` failą

**Reikalavimai**

- Operacinė sistema: Windows 10 x64-bit arba naujesnė versija
- Įdiegta CMake (3.25 arba naujesnė versija)
- Kompiliatorius: g++ (su C++11 arba naujesne versija)

## Katalogai:
- `analysis` - programos veikimo analizės rezultatai, naudojami tam tikrose programos versijose
- `docs` - doxygen failai
- `files` - programoje vykdymo metu naudojami .txt failai (įtrauktas į `.gitignore` ir atsiras tik paleidus programą)
- `include` - antraščių `.h` failai 
- `src` - `.cpp` failai
  
## Duomenų įvestis
| Tipas        | Aprašymas                                                                                                         |
|-------------|-------------------------------------------------------------------------------------------------------------------|
| Rankinis      | Vartotojas suveda duomenis ranka tiesiai į konsolę.                                                                |
| Automatinis   | Naudojamas vartotojui norint sugeneruoti atsitiktinius duomenis bei testavimui, naudojamas `istringstream`.        |
| Iš failo     | Skaitomi duomenys iš failo naudojant `ifstream` (v1.2 teste numatytas vienas dydis - 3, kitur galima rinktis iš 5 dydžių). |

## Duomenų išvestis
| Tipas      | Aprašymas                             |
|-----------|--------------------------------------|
| Į ekraną  | Duomenys atvaizduojami konsolėje per `cout <<` |
| Į failą   | Duomenys saugomi faile per `ostringstream` |

## Kompiliavimas programavimo aplinkoje
| Tipas      | Aprašymas                             |
|-----------|--------------------------------------|
| Programa  |`cd build && .\Objektinis.exe` (nukreipia į MENU) |
| Catch2 testai  | `cd build && .\tests.exe` |

## MENU
Paleidus programą, vartotojas pateks į meniu, kuriame galės pasirinkti ar nori vykdyti programą ar tyrimus. Žemiau pateikiami atitinkami MENU, kurie atsiras po pasirinkimo.

## Programos MENU
| Parinktis | Aprašymas                                                                            |
| :-------- | :----------------------------------------------------------------------------------- |
| **1** | Įvesti viską rankiniu būdu                                                           |
| **2** | Generuoti atsitiktinius pažymius (vardus įvesti ranka)                               |
| **3** | Generuoti atsitiktinius vardus ir pažymius                                           |
| **4** | Skaityti iš failo                                                                    |
| **5** | Užbaigti programą                                                                    |

## Tyrimų MENU
| Parinktis | Aprašymas                                                                     |
| :-------- | :---------------------------------------------------------------------------- |
| **1** | Failų generavimas                                                             |
| **2** | Programos veikimo laikas                                                      |
| **3** | Rule of Five testavimas                                                       |
| **4** | Nuosavo vektoriaus testavimas                                                 |
| **5** | Vector ir `std::vector` paskirstymo testavimas                              |
| **0** | Užbaigti programą                                                             |


# Versija v3.0

1. Šioje versijoje implementuotas nuosavas vektorius `Vector`, kuris padengia daugiau nei 80% `std::vector` funkcionalumo.
Vektorius aprašytas `include`/`ownVector.h` faile.
2. Sukurtas programos diegimo failas naudojant Inno Setup (nes buvo naudojama VS Code aplinka).

## `Vector<T>` Klasės Aprašymas

Šiame skyriuje aprašomi `Vector<T>` klasės metodai, kurie suteikia dinaminio masyvo funkcionalumą, panašų į `std::vector`.

### Konstruktoriai

| Funkcija                                | Aprašymas                                                                 |
| :-------------------------------------- | :------------------------------------------------------------------------ |
| `Vector()`                              | **Numatytasis konstruktorius.** Sukuria tuščią vektorių.                  |
| `Vector(size_t n)`                      | Sukuria vektorių su `n` elementų.                                         |
| `Vector(size_t n, const T& value)`      | Sukuria vektorių su `n` elementų, inicijuotų nurodyta `value`.            |
| `Vector(std::initializer_list<T> init)` | Sukuria vektorių iš inicializavimo sąrašo.                               |

### Rule of Five Metodai

| Funkcija                                   | Aprašymas                                                         |
| :----------------------------------------- | :---------------------------------------------------------------- |
| `Vector(const Vector<T>& other)`           | **Kopijavimo konstruktorius.** Sukuria vektoriaus kopiją.           |
| `Vector(Vector<T>&& other) noexcept`       | **Perkėlimo konstruktorius.** Perkėlia kitą vektorių.              |
| `~Vector()`                                | **Destruktorius.** Atlaisvina užimtą atmintį.                      |
| `Vector<T>& operator=(const Vector<T>& other)` | **Kopijavimo priskyrimo operatorius.** Kopijuoja kito vektoriaus turinį. |
| `Vector<T>& operator=(Vector<T>&& other) noexcept` | **Perkėlimo priskyrimo operatorius.** Perkelia kito vektoriaus turinį.  |

### Elementų Prieiga

| Funkcija                     | Aprašymas                                                      |
| :--------------------------- | :------------------------------------------------------------- |
| `operator[](size_t index)`   | **Tiesioginė prieiga** prie elemento pagal indeksą (nera saugus). |
| `const operator[](size_t index) const` | Konstantiška versija.                                          |
| `back()`                     | Grąžina **paskutinį** vektoriaus elementą.                       |
| `const back() const`         | Konstantiška versija.                                          |
| `front()`                    | Grąžina **pirmą** vektoriaus elementą.                          |
| `const front() const`        | Konstantiška versija.                                          |
| `data()`                     | Grąžina **rodyklę** į pirmojo elemento masyvą.                   |
| `const data() const`         | Konstantiška versija.                                          |
| `at(size_t index)`           | **Saugus pasiekimas** prie elemento pagal indeksą; meta `std::out_of_range` jei indeksas už ribų. |
| `const at(size_t index) const` | Konstantiška versija.                                          |

### Iteratoriai

| Funkcija               | Aprašymas                                         |
| :--------------------- | :------------------------------------------------ |
| `begin()`              | Grąžina rodyklę į **pirmą elementą**.              |
| `const begin() const`  | Konstantiška versija.                             |
| `end()`                | Grąžina rodyklę į elementą **už paskutinio**.       |
| `const end() const`    | Konstantiška versija.                             |

### Dydis ir Talpa

| Funkcija            | Aprašymas                                     |
| :------------------ | :-------------------------------------------- |
| `size() const`      | Grąžina **elementų kiekį** (dydį) vektoriuje.  |
| `capacity() const`  | Grąžina **rezervuotą atminties kiekį**.      |
| `empty() const`     | Patikrina, ar vektorius yra **tuščias**.      |

### Atminties Valdymas

| Funkcija                     | Aprašymas                                                              |
| :--------------------------- | :--------------------------------------------------------------------- |
| `reserve(size_t new_cap)`    | **Rezervuoja** nurodytą atminties kiekį (`new_cap`).                  |
| `shrink_to_fit()`            | **Sumažina talpą** iki dabartinio elementų skaičiaus (dydžio).         |
| `reallocate(size_t new_cap)` | **(Privatus) Perplanuoja** atmintį. Naudojamas vidiniams perskirstymams. |
| `getReallocationCount() const` | Grąžina **atminties perskirstymų skaičių**.                    |

### Modifikavimo Funkcijos

| Funkcija                                  | Aprašymas                                                                 |
| :---------------------------------------- | :------------------------------------------------------------------------ |
| `push_back(const T& value)`               | Prideda elementą į vektoriaus **galą** (kopija).                            |
| `push_back(T&& value)`                    | Prideda elementą į vektoriaus **galą** (perkėlimas).                       |
| `emplace_back(Args&&... args)`           | Konstruoja elementą tiesiogiai vektoriaus gale. Tai efektyviau, nes išvengiama kopijavimo/perkėlimo. |
| `pop_back()`                              | Pašalina **paskutinį** elementą.                                          |
| `clear()`                                 | **Išvalo** vektorių (dydis tampa 0).                                     |
| `resize(size_t new_size)`                 | Keičia vektoriaus dydį. Nauji elementai neinicijuojami.                   |
| `resize(size_t new_size, const T& value)` | Keičia vektoriaus dydį ir inicijuoja naujus elementus nurodyta `value`.   |
| `insert(size_t index, const T& value)`    | **Įterpia** elementą nurodytoje pozicijoje.                               |
| `erase(size_t index)`                     | **Pašalina** elementą nurodytoje pozicijoje.                              |
| `swap(Vector<T>& other)`                  | **Sukeičia** dviejų vektorių turinį.                                     |
| `assign(size_t count, const T& value)`    | Priskiria `count` elementų su ta pačia `value`.                           |

### Palyginimo Operatoriai

| Funkcija                      | Aprašymas                                       |
| :---------------------------- | :---------------------------------------------- |
| `operator==(const Vector<T>& other) const` | Patikrina, ar du vektoriai yra **lygūs**.      |
| `operator!=(const Vector<T>& other) const` | Patikrina, ar du vektoriai yra **nelygūs**.    |
| `operator<(const Vector<T>& other) const`  | Patikrina, ar dabartinis vektorius yra **mažesnis** už kitą. |
| `operator>(const Vector<T>& other) const`  | Patikrina, ar dabartinis vektorius yra **didesnis** už kitą. |

### Paieškos Funkcijos

| Funkcija                 | Aprašymas                                          |
| :----------------------- | :------------------------------------------------- |
| `contains(const T& value) const` | Patikrina, ar vektoriuje yra nurodyta `value`.    |
| `index_of(const T& value) const` | Grąžina pirmosios `value` pasikartojimo indeksą, arba `-1` jei nerasta. |

### Kitos Naudingos Funkcijos

| Funkcija                    | Aprašymas                                                            |
| :-------------------------- | :------------------------------------------------------------------- |
| `slice(size_t start, size_t end) const` | Grąžina naują vektorių, sudarytą iš elementų nuo `start` iki `end-1`. |
| `sort()`                    | **Rūšiuoja** vektoriaus elementus.                                   |
| `unique()`                  | Pašalina **pasikartojančius** elementus iš surūšiuoto vektoriaus.   |
| `map(std::function<T(const T&)> func) const` | Grąžina naują vektorių, pritaikytą funkciją kiekvienam elementui. |
| `reverse()`                 | **Apverčia** vektoriaus elementų tvarką.                             |
| `remove(const T& value)`    | Pašalina **pirmą pasikartojančią** nurodytą reikšmę.                  |

## Pradinis Vector testas
Atliktas pradinis Vector testas lyginant su std::vector. Patikrintas bazinis funkcionalumas. Testas aprašytas `src`/`functions.cpp` faile -> `void testOwnVector()`. Jį galima įvykdyti pasirinkus Menu -> testavimas -> nuosavo vektoriaus testavimas.
![image](https://github.com/user-attachments/assets/870b535f-c4ce-4415-966c-e806e8f4b30a)

Visi pradiniai testai praėjo sėkmingai.

## UNIT testai
Atlikti catch2 unit testai pilnam nuosavo vektoriaus klasės funkcionalumui ištirti. Aprašyti `src`/`catchTest.cpp` faile.
![image](https://github.com/user-attachments/assets/b93649f9-3504-4282-a99c-443899cac994)

Visi catch testai praėjo sėkmingai.

## Efektyvumo testai
Atlikti efektyvumo testai lyginant `std::vector` ir nuosavą `Vector`, tuščius vektorius užpildant: 10000, 100000, 1000000, 10000000 ir 100000000 int elementų naudojant push_back() funkciją. Testas aprašytas `src`/`functions.cpp` faile -> `benchmarkPushBack`. Testavimui naudota `std::chrono::high_resolution_clock` biblioteka.

| Elementų skaičius | std::vector (s) | Own Vector (s) | std::vector reallocations | Own Vector reallocations | 
|-------------------|-----------------|----------------|---------------------------|--------------------------|
| 10 000            | 0.00047         | 0.00015        | 15                        | 15                       |                         
| 100 000           | 0.00277         | 0.00120        | 18                        | 18                       |
| 1 000 000         | 0.02323         | 0.00635        | 21                        | 21                       |
| 10 000 000        | 0.18471         | 0.07862        | 25                        | 25                       |
| 100 000 000       | 1.86080         | 0.68589        | 28                        | 28                       |


**Išvados:**
- Nuosavas `Vector` konteineris parodė geresnį našumą už `std::vector`, ypač užpildant didesnius kiekius elementų.
- Perskirstymai (reallocations) nuosavam `Vector` vyksta maždaug 15-28 kartus priklausomai nuo duomenų kiekio, kas atitinka dvigubinimo strategiją atminties valdyme ir yra tokie aptys kaip ir `std::vector`.



# Programos versijos

Kiekviena versija išsamiai aprašyta jos `README.md` faile.
Programos v1.0 versijos yra atskiroje `opp` repozitorijoje.

## v.pradinė
C++ programa, skirta studentų pažymiams apskaičiuoti, naudojant vidurkio ir medianos metodus. Vartotojai įveda studentų vardus, namų darbų pažymius ir egzaminų rezultatus, o programa pateikia suformatuotus rezultatus. `Makefile` automatizuoja kompiliavimą, o `gitignore` pašalina nereikalingus failus iš „Git“ sekimo.

## v0.1
Optimizuoti failai ir pataisytos galutinio pažymio apskaičiavimo funkcijos. Įgyvendinti du skirtingi vykdomieji failai: vienas su vektorių masyvais, kitas – su dinaminiais C masyvais pažymiams. Pridėta `meniu` funkcija, leidžianti atsitiktinai generuoti pasirinktus duomenis.

## v0.2
Prie meniu pridėta failų skaitymo parinktis, rūšiavimo parinktys (pagal vardą, pavardę ir galutinį pažymį) ir parinktis pasirinkti, ar spausdinti rezultatą į monitorių, ar į failą. Taip pat pridėti `TimeMeasurement` failai, skirti sekti laiką ir apskaičiuoti vidutinius testavimo laikus.

## v0.3
Pridėtas išimčių tvarkymas funkcijoms `readFromFile`, `output` ir `sortStudents`. Sukurti aplankai ir atnaujintas `makefile`.

## v0.4
Pridėta failų generavimo funkcija su pasirinktu dydžiu, studentų grupavimas į dvi grupes pagal pasirinktą galutinio pažymio tipą ir dvi laiko matavimo testavimo funkcijos. Pakeista `timeMeasurement` funkcija, kad testų rezultatai būtų spausdinami į failą, o ne į konsolę. Atnaujintas `README`, įtraukiant laiko matavimo testų rezultatus. Optimizuotos kelios funkcijos, siekiant geresnio našumo.

## v1.0prad
Pridėta nauja laiko testavimo funkcija ir versija su 3 skirtingais konteineriais: `vector`, `deque` ir `list`. Atliktas laiko tyrimas, o rezultatai pateikti faile `README`.

## v1.0
Pridėti testavimai su trimis skirtingomis strategijomis studentų rūšiavimo į grupes funkcijai. Optimizuotas geriausias rūšiavimas (`vector` konteinerio su pirma strategija). Atliktas spartos bei atminties naudojimo tyrimas, o rezultatai pateikti faile `README`. Pridėtas programos diegimo bei paleidimo  `CMake` failas bei `README` aprašyta įdiegimo instrukcija.

## v1.1
`Vector` konteinerio versijoje duomenų struktūra pakeista iš `struct` į `class`. Atlikti programos spartos bei SSD naudojimo testai lyginant `struct` ir `class` su skirtingomis optimizavimo vėliavėlėmis: `O1`, `O2` ir `O3`. Tyrimo rezultatai aprašyti `README` faile. 

## v1.2
Pašalinti `deque` bei `list` versijų katalogai. Pritaikyta Rule of Five ir persidengimo operatoriai. Atliktas testas patikrinantis `Student` klasės metodų veikimą, testui naudojami papildomi `.txt` failai kurie susikuria automatiškai.

## v1.5
Sukurta nauja bazinė klasė `Zmogus`. `Student` klasė paversta į derived. Patikrinta, ar nauji metodai praeina testus iš versijos 1.2
Kad įsitikint, jog klasė `Zmogus` yra abstrakti, reikia atkomentuoti funkciją `void testZmogausClass()` failuose `functions.cpp` bei `functions.h`.

## v2.0
Sukurta klasę aprašanti dokumentacija, HTML ir TEX formatais, su sukompiliuotu PDF failu. Atlikti Catch2 testai faile `src`/`catchTest.cpp`.

## v3.0
Implementuotas nuosavas `Vector` padengiantis daugiau nei 80% `std::vector` funkcionalumo. Atlikti efektyvumo bei funkcionalumo testavimai, programa perrašyta ant nuosavo `Vector`. Sukurtas programos diegimo failas.
