int check20(char chr) // valid: 116
{
    if (((((((((chr * 7) + 1292) << 2) ^ 2915) * 235) + 735) - 944) ^ 4002) == 2621394)
        return 1;
    return 0;
}