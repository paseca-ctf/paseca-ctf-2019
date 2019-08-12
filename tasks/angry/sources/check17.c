int check17(char chr) // valid: 116
{
    if (((((((((chr * 8) + 1396) << 5) ^ 3848) * 9) + 1116) - 96) ^ 47) == 695787)
        return 1;
    return 0;
}