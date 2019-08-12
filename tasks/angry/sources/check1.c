int check1(char chr) // valid: 112
{
    if (((((((((chr * 5) + 1078) << 1) ^ 1423) * 534) + 631) - 1459) ^ 1356) == 1264586)
        return 1;
    return 0;
}