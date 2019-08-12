int check19(char chr) // valid: 115
{
    if (((((((((chr * 3) + 281) << 4) ^ 428) * 1186) + 2) - 1741) ^ 3250) == 11698559)
        return 1;
    return 0;
}