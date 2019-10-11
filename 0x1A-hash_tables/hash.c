static unsigned long
sdbm(str)
	unsigned char *str;
{
        unsigned long hash = 0;
        int c;

        while (c = *str++)
		hash = c + (hash << 6) + (hash << 16) - hash;

        return hash;
}
int main()
{
	unsigned char *new;

	return(sdbm("Write a hash function implementing the djb2 algorithm."));
}
