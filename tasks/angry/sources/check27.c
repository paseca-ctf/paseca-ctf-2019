int check27(char chr) // valid: 121
{
    if (((((((((chr * 8) + 457) << 1) ^ 134) * 183) + 1963) - 530) ^ 3005) == 547944)
        return 1;
    return 0;
}