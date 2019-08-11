int check2(char chr) // valid: 97
{
    if (((((((((chr * 8) + 1922) << 2) ^ 3085) * 1635) + 86) - 567) ^ 2484) == 15963610)
        return 1;
    return 0;
}