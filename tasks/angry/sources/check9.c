int check9(char chr) // valid: 49
{
    if (((((((((chr * 8) + 1453) << 5) ^ 1454) * 1994) + 858) - 1170) ^ 4048) == 115901956)
        return 1;
    return 0;
}