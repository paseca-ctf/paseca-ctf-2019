int check1(char chr) // valid: 112
{
    if (((((((((chr * 8) + 1341) << 4) ^ 2804) * 868) + 713) - 752) ^ 856) == 28696241)
        return 1;
    return 0;
}