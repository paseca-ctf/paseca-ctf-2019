int check26(char chr) // valid: 95
{
    if (((((((((chr * 5) + 987) << 3) ^ 85) * 1510) + 907) - 1613) ^ 2259) == 17742127)
        return 1;
    return 0;
}