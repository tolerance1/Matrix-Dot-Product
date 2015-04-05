# Matrix-Dot-Product

This console benchmark creates two square matrixes of the same size. The sizes are specified in the ‘params.txt’ file separated by a whitespace and can be redefined. Then the following five measurements are taken (in milliseconds):

1.	The time to initialise matrix #1
2.	The time to initialise matrix #2
3.	The time to multiply matrix #1 by matrix #2
4.	The time to transpose matrix #2
5.	The time to multiply matrix #1 by transposed matrix #2

The elements of matrix #2 in a straightforward multiplication are accessed randomly in the memory. To obtain sequential access to elements, matrix #2 is transposed. The effect of transposition is then checked by multiplication again.

The results for each size of the matrixes are then written to ‘results.txt’ file. This file already contains the reference measurements performed on a Windows XP SP3, AMD Sempron 2300+ 1,58GHz Socket A  processor, DDR400 memory, on the system start-up, with no programs running and LAN disabled.

Note that multiplying two 1000 x 1000 matrixes is time consuming. On the aforementioned system it takes almost 2 minutes before transposition and near 1,5 minutes after. Also touching the console will pause the runtime and therefore distort the measurements.
