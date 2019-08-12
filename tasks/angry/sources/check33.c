int check33(char chr) // valid: 103
{
    if (((((((((chr * 3) + 1237) << 5) ^ 3614) * 421) + 1194) - 449) ^ 3) == 22349948)
        return 1;
    return 0;
}