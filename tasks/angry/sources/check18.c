int check18(char chr) // valid: 52
{
    if (((((((((chr * 4) + 1449) << 3) ^ 3640) * 246) + 1583) - 1852) ^ 3344) == 3903107)
        return 1;
    return 0;
}