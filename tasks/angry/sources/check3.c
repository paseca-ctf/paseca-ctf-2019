int check3(char chr) // valid: 115
{
    if (((((((((chr * 2) + 862) << 5) ^ 2736) * 1833) + 410) - 1160) ^ 3937) == 61090211)
        return 1;
    return 0;
}