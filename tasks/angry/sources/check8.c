int check8(char chr) // valid: 100
{
    if (((((((((chr * 9) + 61) << 2) ^ 432) * 124) + 145) - 1842) ^ 2545) == 463230)
        return 1;
    return 0;
}