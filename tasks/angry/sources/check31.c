int check31(char chr) // valid: 97
{
    if (((((((((chr * 1) + 953) << 2) ^ 2503) * 799) + 734) - 1617) ^ 1392) == 5251278)
        return 1;
    return 0;
}