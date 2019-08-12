int check25(char chr) // valid: 51
{
    if (((((((((chr * 7) + 1771) << 1) ^ 1494) * 522) + 1677) - 1783) ^ 257) == 2868019)
        return 1;
    return 0;
}