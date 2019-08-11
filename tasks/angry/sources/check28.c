int check28(char chr) // valid: 48
{
    if (((((((((chr * 9) + 400) << 4) ^ 1909) * 1666) + 664) - 1692) ^ 575) == 21944665)
        return 1;
    return 0;
}