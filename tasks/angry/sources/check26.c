int check26(char chr) // valid: 95
{
    if (((((((((chr * 1) + 227) << 5) ^ 2158) * 76) + 1514) - 1785) ^ 893) == 626660)
        return 1;
    return 0;
}