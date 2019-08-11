int check17(char chr) // valid: 116
{
    if (((((((((chr * 2) + 1707) << 2) ^ 933) * 1682) + 449) - 1623) ^ 1490) == 12879262)
        return 1;
    return 0;
}