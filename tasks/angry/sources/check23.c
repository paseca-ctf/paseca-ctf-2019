int check23(char chr) // valid: 97
{
    if (((((((((chr * 1) + 878) << 5) ^ 2894) * 608) + 1610) - 729) ^ 1786) == 17851979)
        return 1;
    return 0;
}