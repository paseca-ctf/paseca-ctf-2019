int check28(char chr) // valid: 48
{
    if (((((((((chr * 3) + 750) << 3) ^ 3338) * 211) + 1923) - 1050) ^ 2549) == 1243778)
        return 1;
    return 0;
}