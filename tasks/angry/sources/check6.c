int check6(char chr) // valid: 97
{
    if (((((((((chr * 7) + 1419) << 1) ^ 3154) * 1697) + 170) - 1650) ^ 387) == 12254637)
        return 1;
    return 0;
}