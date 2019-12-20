
int soNguyenTo(int soA)
{
	if (soA < 2)
	{
		return -1;
	}
	else
	{
		int i = 0;
		for (i = 2; i <= soA/2; i++)
		{
			if (soA % i == 0)
			{
				return -1;
			}
		}
	}
	return soA;
}


