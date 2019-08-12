int check36(char chr) // valid: 125
{
    if (((((((((chr * 6) + 924) << 2) ^ 2612) * 965) + 54) - 456) ^ 1133) == 3978135)
        return 1;
    return 0;
}