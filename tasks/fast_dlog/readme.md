## Just take your flag
We received a file with really (I promise) important information, but it cannot load into our paseca calculator. Can you help us?
## Flag
paseca{bzbz_4ll_b335_l0v3_m47h_4nd_1_l0v3_my_p453c4}
## Notes
[DEPLOY] Заливать только файл из папки static

[EXPLOIT] Эксплойт работает 30-50 минут и потребляет 3-4 ГБ оперативы

## WriteUp
First of all start given program. It prints "Hello! Your flag is on the way, just take a seat and wait a bit" 
and beginning of the flag with some delay between symbols.
Open executable in disassembler and find main function by searching string "Hello".
In this function we see a lot of strange data on the stack and presumably loop that prints flag with some nested loops.
After some debugging and reversing we have understood that program tries to solve discrete logarithm problem by exhaustive search.
Data on stack are parameters for the equation. There are 3 arrays with parameters for every flag symbol.
Just extract these parameters and solve all equations with some "fast" algorithm(Baby-step giant-step, Pohlig–Hellman algorithm) and take lsb from every result.
