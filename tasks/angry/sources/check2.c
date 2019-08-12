int check2(char chr) // valid: 97
{
    if (((((((((chr * 1) + 1102) << 3) ^ 1055) * 689) + 1745) - 15) ^ 3215) == 5890166)
        return 1;
    return 0;
}