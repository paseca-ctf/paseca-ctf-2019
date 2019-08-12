int check10(char chr) // valid: 100
{
    if (((((((((chr * 1) + 666) << 2) ^ 3747) * 1729) + 1214) - 560) ^ 395) == 2371490)
        return 1;
    return 0;
}