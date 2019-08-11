int check21(char chr) // valid: 95
{
    if (((((((((chr * 6) + 693) << 1) ^ 845) * 507) + 209) - 67) ^ 1844) == 1373851)
        return 1;
    return 0;
}