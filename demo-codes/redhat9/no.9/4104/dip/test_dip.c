
int main(void)
{
	int value = 0;

	while(1)
	{
		value = dip_get_value();
		printf("get dip value = 0x%x \n", value);
	}

	return 0;
}
