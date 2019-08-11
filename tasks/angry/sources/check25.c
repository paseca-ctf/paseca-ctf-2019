int check25(char chr) // valid: 51
{
    if (((((((((chr * 3) + 1966) << 1) ^ 426) * 422) + 1077) - 1677) ^ 1705) == 1849769)
        return 1;
    return 0;
}