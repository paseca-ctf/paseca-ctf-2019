int check11(char chr) // valid: 95
{
    if (((((((((chr * 6) + 1717) << 2) ^ 4044) * 1562) + 1999) - 110) ^ 1170) == 17772115)
        return 1;
    return 0;
}