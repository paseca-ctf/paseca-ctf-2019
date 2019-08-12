int check24(char chr) // valid: 107
{
    if (((((((((chr * 5) + 1026) << 4) ^ 2345) * 1829) + 1666) - 19) ^ 2430) == 49033554)
        return 1;
    return 0;
}