int check18(char chr) // valid: 52
{
    if (((((((((chr * 3) + 878) << 2) ^ 1328) * 1303) + 896) - 1380) ^ 3305) == 7034797)
        return 1;
    return 0;
}