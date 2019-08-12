int check21(char chr) // valid: 95
{
    if (((((((((chr * 1) + 245) << 4) ^ 2688) * 315) + 1956) - 173) ^ 133) == 2562226)
        return 1;
    return 0;
}