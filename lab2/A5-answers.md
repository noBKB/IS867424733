# Assignment 5

## 1. 运行记录

address 使用十六进制，value 保留程序打印的无符号十进制。

| 项目 | address | value |
|---|---|---:|
| AM1 | 0x000008A4 | 4 |
| AM2 | 0x000008A0 | 3 |
| AM3 | 0x00000134 | 4278255891 |
| AM4 | 0x00000184 | 4211147027 |
| AM5 | 0x001009FC | 1051136 |
| AM6 | 0x00100A00 | 7 |
| AM7 | 0x001009FC | 1051136 |
| AM8 | 0x00100A00 | 8 |
| AM9 | 0x001009FC | 1051120 |
| AM10 | 0x001009F0 | 66 |
| AM11 | 0x001009F1 | 111 |
| AM12 | 0x001009F2 | 110 |
| AM13 | 0x001009F3 | 106 |
| AM14 | 0x001009F0 | 205 |
| AM15 | 0x001009F1 | 171 |
| AM16 | 0x001009F2 | 52 |
| AM17 | 0x001009F3 | 18 |
| AF1 | 0x001009B4 | 9 |
| AM18 | 0x00100A00 | 8 |
| AM19 | 0x000008A4 | 9 |


## 2. AM18、AM19、AF1：为什么 gv 保留了增加后的值，而 m 没有？

### 瑞典语答案 / Svar på svenska

Före anropet `fun(m)` är värdet på `m` 8. C använder värdeöverföring (pass-by-value): funktionen får en kopia av värdet. Kopian heter `param`.

I `fun` ökar `param++` kopian från 8 till 9, så AF1 visar 9. Sedan skriver `gv = param` värdet 9 till den globala variabeln `gv`. Funktionen skriver aldrig tillbaka till `m` i `main`. Därför visar AM18 fortfarande 8 och AM19 visar 9.

Adresserna visar också att det är tre olika variabler:

| Variabel（变量） | Adress（地址） | Observerat värde（观察到的值） |
|---|---|---:|
| m i main | 0x00100A00 | 8 |
| param i fun | 0x001009B4 | 9 |
| gv | 0x000008A4 | 9 |

Kort muntligt svar: ”Funktionen ändrar en kopia av m och sparar sedan resultatet i gv. Därför ändras gv, men inte m.”

### 中文大白话解释

把变量想成装数字的小盒子。现在有三个盒子，分别叫 `m`、`param` 和 `gv`。

调用 `fun(m)` 时，不是把 m 的盒子交出去，而是把里面的数字 8 抄到一个新盒子 param 里。

函数做了两件事：

1. 把 param 里的 8 加一，变成 9。
2. 把这个 9 放进 gv 里。

整个过程没有碰 m 的盒子，所以最后 m 还是 8，param 和 gv 都是 9。这就是“按值传递”：传过去的是一份数字的副本。

**课堂上就说：函数改的是 m 的副本，不是 m 本身；它又把结果写进 gv，所以 gv 变了，m 没变。**

## 3. cp 是字符指针，cp 自身有多大？

### 瑞典语答案 / Svar på svenska

I RV32-miljön är pekaren `cp` 4 byte stor. Den lagrar en minnesadress. Typen `char *` betyder att pekaren pekar på ett tecken av typen `char`; den betyder inte att själva pekaren är en byte stor.

När vi läser `*cp` läser vi en `char`. När vi gör `cp++` flyttas pekaren fram en byte.

- `sizeof(cp)` är 4 byte: storleken på själva pekaren i denna miljö.
- `sizeof(*cp)` är 1 byte: storleken på en `char`.
- `sizeof(cs)` är 9 byte: storleken på hela teckenarrayen.

### 中文大白话解释

把 cp 想成一张写着“去哪里找字符”的纸条。纸条上装的是**地址**，不是整个字符串。

题目问的是“这张地址纸条本身占多大地方”。在本题的 RV32 机器上，答案是 **4 字节**。

容易混的三个东西是：

- cp：地址纸条本身，占 4 字节。
- *cp：按纸条上的地址找到的一个字符，占 1 字节。
- cs：装整段文字的地方，占 9 字节。

这里的字节可以先理解成一个存储小格子。看到 `char *`，你只知道它要去找字符，不能因此说指针自己也只有一个字节。

**课堂上就说：cp 本身是一个地址，在 RV32 上占 4 字节；它指向的一个 char 才占 1 字节。**

## 4. C 字符串如何存储？为什么需要 9 字节？

### 瑞典语答案 / Svar på svenska

En C-sträng lagras som tecken efter varandra i minnet. Efter det sista tecknet finns en nollbyte, `\0`, som markerar slutet på strängen.

`Bonjour!` har åtta synliga tecken. Med den avslutande nollbyten behövs därför nio byte.

```text
Tecken: B  o  n  j  o  u  r  !  NUL
Hex:    42 6F 6E 6A 6F 75 72 21 00
```

AM10–AM13 visar 66, 111, 110 och 106, alltså teckenkoderna för B, o, n och j. Adresserna ökar med en byte i taget, från `0x001009F0` till `0x001009F3`. Det stämmer med att tecknen ligger direkt efter varandra.

### 中文大白话解释

把内存想成一排小格子。在这里，一个格子放一个字符：

```text
[B][o][n][j][o][u][r][!][结束标记]
```

前面八格是能看见的文字。最后还要多放一格，告诉处理字符串的程序：“文字到这里结束了。”

这个结束标记写作 `\0`，它的数值是 0，不是可见字符“0”，也不会作为文字打印出来。

所以不是八格，而是 **8 个字符 + 1 个结束标记 = 9 字节**。AM10 到 AM13 读到的正是前四格：B、o、n、j。

**课堂上就说：八个字符后面还要一个零结束符，所以共九个字节。**

## 5. fun 和 main 的地址、所在节、内存种类，以及地址处数据的含义是什么？

### 瑞典语答案 / Svar på svenska

I denna körning börjar `fun` på adressen `0x00000134` och `main` på `0x00000184`. Båda ligger i kodsektionen `.text`. I experimentets minneslayout ligger koden i RAM. Namnet `.text` beskriver sektionens innehåll; det betyder inte att minnet är ROM.

Om vi läser ett ord vid en funktions startadress får vi en kodad maskininstruktion, inte funktionens returvärde. De observerade orden kan avkodas som RISC-V-instruktioner:

| Funktion | Adress | Instruktionsord, decimalt | Hexadecimalt | Instruktion |
|---|---|---:|---|---|
| fun | 0x00000134 | 4278255891 | 0xFF010113 | addi sp, sp, -16 |
| main | 0x00000184 | 4211147027 | 0xFB010113 | addi sp, sp, -80 |

Båda har opcode `0x13`, funct3 `0` och registren rd = rs1 = x2, alltså `sp`. Det teckenutökade 12-bitars omedelbara värdet är -16 respektive -80.

Instruktionerna minskar stackpekaren och reserverar 16 respektive 80 byte för funktionens stackram. Detta är en avkodning av de angivna instruktionsorden, inte en separat kontroll av den tillhörande ELF-filen. Andra kompilatorer eller optimeringsinställningar kan ge andra adresser och stackramar.

### 中文大白话解释

这题其实问了四件事，可以分开回答。

**第一，函数从哪里开始？** 把函数想成一张给电脑看的“操作步骤表”。fun 的第一步放在 `0x00000134`，main 的第一步放在 `0x00000184`。地址就是找到它们的位置编号，像门牌号。

**第二，属于哪个区域？** 这些操作步骤放在 `.text`，也就是“放代码的区域”。

**第三，放在哪种内存里？** 按本实验的布局，它们在 RAM，也就是电脑运行程序时使用的内存里。

**第四，为什么读出来是两个很大的数字？** 电脑把每条操作指令编码成数字。这里读到的是“电脑接下来该做什么”，不是“函数算出来的答案”。

这两条指令翻成人话就是：

- fun 开头：把栈指针减去 16，给这个函数留出 16 字节空间。
- main 开头：把栈指针减去 80，给这个函数留出 80 字节空间。

sp 是“栈指针”，用来帮助记录栈上分配空间的位置。这里栈向较小的地址增长，所以减小 sp 可以给函数留出工作空间。不要把这些指令当成“返回 -16”或“返回 -80”。

**课堂上就说：fun 和 main 在 RAM 的 .text 区域；它们开头存的是机器指令，这里分别给函数留出 16 和 80 字节的栈空间。**

## 6. in 和 gv 位于哪里？

### 瑞典语答案 / Svar på svenska

`in` ligger på `0x000008A0` i `.data`, eftersom den definieras med ett startvärde: `int in = 3;`.

`gv` ligger på `0x000008A4` i `.bss`. Den definieras som `int gv;` utan ett uttryckligt startvärde och nollinitialiseras när programmet startar.

Före AM1 tilldelar programmet `gv` värdet 4. Efter `fun` har den värdet 9, vilket syns i AM19. Adressen är fortfarande `0x000008A4`. Tilldelningen ändrar innehållet, inte variabelns adress eller sektion.

Sektionsplaceringen följer av variabeldeklarationerna och experimentets länklayout.

### 中文大白话解释

in 和 gv 是两个存数字的盒子，每个盒子都有固定的位置。

| 盒子 | 位置，也就是地址 | 放在哪个区域 |
|---|---|---|
| in | 0x000008A0 | .data |
| gv | 0x000008A4 | .bss |

为什么区域不同？

写 `int in = 3;` 时，已经告诉程序“开始就放 3”，所以这里把 in 放进 `.data`。

写 `int gv;` 时，没有写具体的初始数字。因为它是全局变量，程序启动时会把它初始化为 0；这里它放在 `.bss`。

后来程序把 gv 改成 4，再改成 9，等于把盒子里的数字换了，**不是把盒子搬走了**。所以它的地址一直相同，也一直属于 .bss。

**课堂上就说：in 在 0x000008A0 的 .data，gv 在 0x000008A4 的 .bss。改 gv 的值不会改变它的位置。**

## 7. p 和 m 分配在哪里？为什么地址远大于 in 和 gv？

### 瑞典语答案 / Svar på svenska

`p` och `m` är lokala variabler i `main`. I denna körning ligger de i mains stackram:

- `&p = 0x001009FC`.
- `&m = 0x00100A00`.

Experimentets minneslayout placerar stacken efter kod och globala data och reserverar ungefär 1 MiB för den. Stackpekaren börjar vid stackområdets övre ände, och stacken växer mot lägre adresser. Därför har dessa lokala variabler högre adresser än `in` och `gv`.

Det beror på just denna minneslayout. C kräver inte att lokala variabler alltid ska ha högre adresser än globala variabler. I andra situationer kan kompilatorn också lägga lokala variabler i register.

### 中文大白话解释

把内存想成一条有门牌号的长街。这次程序安排：

- 前面门牌号比较小的地方，放代码和 in、gv 这样的全局变量。
- 后面门牌号比较大的地方，留给函数工作时使用，这块地方叫“栈”。

main 运行时，需要放 p 和 m，于是把它们放在自己的那块栈空间里：

- p 在 `0x001009FC`。
- m 在 `0x00100A00`。

这就是它们地址数字比较大的原因：**它们被安排在街道后面的区域**。不是说 p 和 m 的数值很大，也不是说它们比全局变量“更重要”。

这里栈分配空间时朝较小的地址移动，可以想成从街道后端开始，往前腾出工作位置。这是本次程序的安排，别的程序不一定完全相同。

**课堂上就说：p 和 m 在 main 的栈里，本实验把栈安排在较高地址，所以它们的地址比 in、gv 大。**

## 8. AM5 时，p 的地址、p 的值、p 指向的值分别是什么？

### 瑞典语答案 / Svar på svenska

Programmet har gjort `p = &m;`. Det betyder att p lagrar adressen till m.

| Uttryck（表达式） | Betydelse（含义） | Värde vid AM5（结果） |
|---|---|---|
| &p | Adressen till själva pekarvariabeln p | 0x001009FC |
| p | Adressen som lagras i p | 1051136 = 0x00100A00 = &m |
| *p | Heltalet på adressen som p pekar på | 7, bekräftat av AM6 |

Anropet `print_word(..., &p)` visar var p finns och vilken adress p innehåller. Värdet på m visas separat av AM6.

### 中文大白话解释

这三个东西最容易混。继续用“地址纸条”的例子：

- **&p：纸条放在哪里？** 放在 `0x001009FC`。
- **p：纸条上写着什么地址？** 写着 `0x00100A00`，也就是 m 的位置。
- **\*p：照着纸条去找，那里装着什么？** 装着数字 7。

所以 p 里面保存的是地址，不是数字 7。要看到 7，需要“按地址去找”，这个动作写成 `*p`。

记录里的 `1051136` 和 `0x00100A00` 是同一个数：前者用十进制写，后者用十六进制写，不能当成两个不同地址。

**课堂上就说：p 自己在 0x001009FC，里面存的是 m 的地址 0x00100A00；按这个地址找到的整数是 7。**

## 9. AM7 时，这三个值有什么变化？

### 瑞典语答案 / Svar på svenska

Mellan AM5 och AM7 kör programmet `*p = *p + 1;`. Det ändrar heltalet som p pekar på, alltså m. Själva pekaren p ändras inte.

| Uttryck | AM5 | AM7 |
|---|---|---|
| &p | 0x001009FC | 0x001009FC |
| p | 0x00100A00 | 0x00100A00 |
| *p | 7 | 8 |

AM5 och AM7 visar samma adress och värde eftersom båda läser själva pekarvariabeln. Ändringen av m syns i AM6 och AM8, som visar 7 respektive 8.

Vid AM9 har programmet däremot gjort `p = (int*)cp;`. Då ändras adressen i p till `1051120 = 0x001009F0`, alltså startadressen för cs. Själva p ligger fortfarande på `0x001009FC`.

### 中文大白话解释

`*p = *p + 1;` 的意思是：

“照着 p 上写的地址去找，把找到的那个数字加一。”

原来找到 7，现在把它改成 8。纸条仍放在原处，纸条上写的地址也没有改，所以：

- &p 不变：纸条没搬家。
- p 不变：纸条上的地址没改。
- *p 从 7 变 8：目的地里面的数字改了。

这就解释了为什么 AM5 和 AM7 的输出看着一样：它们都在检查纸条，而发生变化的是目的地里的数字。AM6 和 AM8 才是在看那个数字，所以分别看到 7 和 8。

到 AM9 就不同了。执行 `p = (int*)cp;` 相当于把纸条上的地址改成字符串开头的位置 `0x001009F0`。从此 p 指向字符串开头，而不再指向 m。

**课堂上就说：AM7 时 &p 和 p 都没变，只有 *p 从 7 变成了 8，因为代码改的是 p 指向的内容。**

## 10. AM14–AM17 表明是大端序还是小端序？为什么？

### 瑞典语答案 / Svar på svenska

Programmet skriver `0x1234abcd` med `*p = 0x1234abcd;`. Vid den tidpunkten pekar p på början av cs, så skrivningen ersätter de första fyra byten i cs.

| Adress, stigande（地址递增） | Byte, decimalt | Byte, hexadecimalt |
|---|---:|---|
| 0x001009F0 | 205 | CD |
| 0x001009F1 | 171 | AB |
| 0x001009F2 | 52 | 34 |
| 0x001009F3 | 18 | 12 |

Den minst signifikanta byten i `0x1234ABCD` är `CD`. Den ligger på den lägsta adressen. Denna byteordning kallas little-endian.

Med big-endian skulle byten i stigande adressordning i stället vara `12 34 AB CD`.

### 中文大白话解释

先把 `0x1234ABCD` 每两位分成一组：

```text
12 | 34 | AB | CD
```

每一组占一个字节。写到内存里时，要决定“哪一组先放到最小的地址”。

这次从最小地址往后看，读出来是：

```text
CD | AB | 34 | 12
```

也就是把数字右边、代表较低位的 CD 放在最小地址。这个规则就叫**小端序**。

这里的“小”说的是数字的低位，不是“CD 比 12 小”。事实上 CD 的数值更大，但它仍然是这个四字节整数的最低有效字节。

如果最小地址先放 12，后面依次放 34、AB、CD，就叫大端序。

**课堂上就说：最低地址存的是最低有效字节 CD，所以是小端序。**
