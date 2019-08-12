int check23(char chr) // valid: 97
{
    if (((((((((chr * 6) + 276) << 2) ^ 3277) * 1367) + 1552) - 146) ^ 3895) == 574118)
        return 1;
    return 0;
}