# Assignment 3：简单性能比较



## 怎么测

### Metod

Här sammanfattas några tidigare tester från den 16 september 2026 med avrundade tider. Inga nya tester har gjorts och inga exakta maxgränser har sökts.

Testmiljö: Windows, AMD Ryzen 7 9800X3D och LLVM-MinGW Clang 22.1.8, utan optimeringsflaggor. Ett skript mätte tiden. Utskriften skickades till en nullenhet för att undvika skärmvisningens tidsåtgång.

### 中文

把输入的数字调大，看看三个程序分别要跑多久。这里从 2026-09-16 已有的本机测试中挑了几个结果，时间用约数表示，方便比较。没有重新测试，也没有去找刚好卡在 2 秒或 10 秒的最大值。

测试电脑是 Windows，AMD Ryzen 7 9800X3D；编译器是 LLVM-MinGW Clang 22.1.8，没有加优化选项。测试时不把质数显示在屏幕上，否则大量刷屏也会花时间。程序仍然执行打印，只是输出被送到空设备。原测试由脚本计时，下面是自己复测的简单方法。

在学校的 Linux 电脑上，编译好程序后可以这样测：

På skolans Linux-dator kan programmen, efter kompilering, tidmätas så här:

```bash
time ./print-primes 1000000 > /dev/null
time ./sieves 1000000 > /dev/null
time ./sieves-heap 1000000 > /dev/null
```

看 `real` 后面的时间。跑得很快就把数字加大，超过目标时间就把数字减小，不用反复试到刚好 2 秒或 10 秒。下面是 Windows 上已有的结果，不是这些 Linux 命令的新结果。

Läs tiden efter `real`. Öka indata om programmet går snabbt och minska om tiden blir för lång. Resultaten nedan kommer från de tidigare Windows-testerna, inte från dessa Linux-kommandon.

## 大概结果

### Ungefärliga resultat

| Program | Ett resultat under 2 sekunder | Ett resultat under 10 sekunder |
|---|---|---|
| print-primes | n = 5 miljoner, cirka 1,6 s | n = 16 miljoner, cirka 8,1 s |
| sieves-heap | n = 75 miljoner, cirka 1,5 s | n = 400 miljoner, cirka 8,8 s |
| sieves | n = 1 miljon, under 0,1 s | Stackutrymmet tog slut innan tidsgränsen blev problemet |

De största primtalen för dessa indata är 4 999 999 och 15 999 989 för `print-primes`, 74 999 959 och 399 999 959 för `sieves-heap`, samt 999 983 för `sieves`.

Primtalen kontrollerades separat, inte genom avläsning under tidmätningen. Detta är exempel, inte de absoluta maxvärdena inom 2 eller 10 sekunder.

Stackversionen fungerade vid n = 1 miljon men fick stack overflow vid n = 1,5 miljoner. Problemet var minnesutrymme, inte hastighet. Den exakta gränsen är okänd och kan skilja sig mellan datorer.

### 中文

| 程序 | 2 秒以内的一组结果 | 10 秒以内的一组结果 |
|---|---|---|
| print-primes | 输入 500 万，约 1.6 秒 | 输入 1600 万，约 8.1 秒 |
| sieves-heap | 输入 7500 万，约 1.5 秒 | 输入 4 亿，约 8.8 秒 |
| sieves | 输入 100 万，不到 0.1 秒 | 再给时间也没用，本机先遇到了栈空间不足 |

题目问的是“最后能打印到哪个质数”，不只是输入有多大。上面输入对应的最后一个质数是：

- print-primes：4,999,999 和 15,999,989。
- sieves-heap：74,999,959 和 399,999,959。
- sieves 输入 100 万时：999,983。

这些质数根据输入范围另外计算核对，不是从计时运行的屏幕上抄下来的。它们是测试例子，不代表 2 秒或 10 秒内的绝对最大质数。质数本身不能随便取整，所以这里保留完整数字。

栈版本在本机输入 100 万时能运行，输入 150 万时出现栈溢出。也就是说，用来放数组的空间不够了，不是因为程序算得太慢。这里不确定它刚好能承受的最大输入是多少，学校电脑的限制也可能不同。

## 为什么会有差别

### Varför skiljer det sig?

`print-primes` testar möjliga delare för varje tal på nytt. Det tar längre tid när talen blir större.

Sållen markerar i stället multiplar av varje primtal: 4, 6, 8 … för 2, sedan 6, 9, 12 … för 3. De omarkerade talen är primtal. Det sparar arbete och var mycket snabbare här.

`sieves` och `sieves-heap` använder samma algoritm. Skillnaden är var arrayen lagras. Heap kan vanligtvis rymma större arrayer än stacken, men även heap har en gräns.

### 中文

`print-primes` 是一个数一个数地检查：这个数能不能被别的数整除？换到下一个数，又要重新检查，所以数字大了以后比较慢。

筛法像是在一张数字表上划掉不可能是质数的数。比如找到 2，就划掉 4、6、8……；找到 3，再划掉 6、9、12……。最后没被划掉的就是质数。这样不用对每个数都从头检查，所以这次测试中快得多。

`sieves` 和 `sieves-heap` 用的是同一种筛法，主要区别是数组放在哪里。栈（stack）能放的东西比较有限；堆（heap）通常能申请更大的空间，所以堆版本这次能处理更大的输入，但它也不是没有内存上限。

## 口试时可以这样解释

### Kort svar på svenska

”I de här exemplen tog den vanliga metoden cirka 1,6 sekunder upp till 5 miljoner. Sållen på heap tog cirka 1,5 sekunder upp till 75 miljoner och var alltså mycket snabbare. Stackversionen var också snabb, men en för stor array gav stack overflow. Det är ungefärliga jämförelser, inte exakta maxvärden. Datorn och sättet att skriva ut påverkar tiden.”

### 中文

“这几个例子里，普通方法算到 500 万大概用了 1.6 秒，堆上的筛法算到 7500 万大概用了 1.5 秒，所以筛法明显更快。栈上的筛法也很快，但是数组太大时空间不够，程序会失败。这些只是大概比较，不是精确的最大值。换电脑或者把结果都显示在屏幕上，时间也会变。”

本页是已有测试的简要整理，完整记录仍保留在本地工作材料中。这里的时间是本机结果，不是 DTEK-V 板上的结果。

Detta är en kort sammanfattning av tidigare tester. Fullständiga mätningar finns kvar i det lokala arbetsmaterialet. Tiderna gäller testdatorn, inte DTEK-V-kortet.
