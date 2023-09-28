# Hash funkcija

## Pseudo-kodas

## Eksperimentinis tyrimas ir rezultatų analizė

#### 2. Naudojant įvedimo failų pavyzdžius (pateiktus aplanke test failai) patikrinta, kad:
   - Hash ilgis yra 64 simboliai nepriklausomai nuo įvesties ilgio
   - To paties failo hash visada gaunamas vienodas.
   - Funkcija nesugeneruoja hash'o tuščiam failui.

| Test failas |                         Sugeneruotas hash                        |
|:-----------:|:----------------------------------------------------------------:|
|      1      | 6b1ad3c484f351bf47c4293f79da5ef3ae80752b24740c410000000000000000 |
|      2      | 1c70c4132c1505255734e181c21dbe601a833d026f91776af43c295b1b461401 |
|      3      | 1d96caffd0139f7b2d5383761254b7823ad51de8be1a2cb2370c741323403100 |
|      4      | 18c04d0105faf314221dc606e12f2de9e33ae07df8fbcd8c0a7de969ec136ed1 |
|      5      | 56c23ad79d0f69710a217f36bb653140c39ac0417e74acd194517bcdf2970210 |
|      6      | 56c517d9cbfd5a3121ce3eac3eb178e95e964fb3e283ad5c9dff82cf6e96d810 |
|      7      |                                 -                                |

#### 3. Funkcijos efektyvumo tyrimas naudojant failą konstitucija.txt

| Eilučių skaičius | Sugaištas laikas |
|:----------------:|:----------------:|
|         1        |     0.001261     |
|         2        |     0.001621     |
|         4        |     0.001718     |
|         8        |     0.001646     |
|        16        |     0.001948     |
|        32        |     0.002359     |
|        64        |     0.002706     |
|        128       |     0.007211     |
|        256       |     0.018595     |
|        512       |     0.030923     |
|        790       |     0.104057     |

#### 5. Naudojant failą "generated.txt" kolizijų rasta nebuvo.

#### 6.

#### 7. Išvados
Hash funkcija veikia su bet kokio ilgio simbolių eilute (išskyrus tuščią), sugeneruojamas hash'as yra 64 simbolių ilgio, funkcija deterministinė bei atspari kolizijai.


