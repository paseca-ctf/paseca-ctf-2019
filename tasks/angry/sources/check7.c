int check7(char chr) // valid: 123
{
    if (((((((((chr * 3) + 654) << 5) ^ 3440) * 1380) + 204) - 489) ^ 2676) == 40469847)
        return 1;
    return 0;
}