int zeller(int y, int m, int d)
{
    if (m < 3)
        y--, m += 12;

    return (y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + d) % 7;
}