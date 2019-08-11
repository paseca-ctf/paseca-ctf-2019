int check3(char chr) // valid: 115
{
    if (((((((((chr * 4) + 1766) << 2) ^ 3544) * 92) + 1846) - 1610) ^ 95) == 1108723)
        return 1;
    return 0;
}