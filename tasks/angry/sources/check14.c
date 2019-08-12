int check14(char chr) // valid: 49
{
    if (((((((((chr * 1) + 1788) << 5) ^ 896) * 668) + 683) - 1520) ^ 682) == 39352977)
        return 1;
    return 0;
}