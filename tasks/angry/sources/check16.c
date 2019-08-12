int check16(char chr) // valid: 95
{
    if (((((((((chr * 9) + 1738) << 1) ^ 1953) * 759) + 118) - 1921) ^ 2350) == 3860436)
        return 1;
    return 0;
}