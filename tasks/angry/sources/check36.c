int check36(char chr) // valid: 125
{
    if (((((((((chr * 7) + 1231) << 2) ^ 3473) * 337) + 919) - 1651) ^ 1987) == 3923630)
        return 1;
    return 0;
}