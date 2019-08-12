int check30(char chr) // valid: 95
{
    if (((((((((chr * 4) + 19) << 3) ^ 1979) * 1670) + 1270) - 375) ^ 3025) == 5027392)
        return 1;
    return 0;
}