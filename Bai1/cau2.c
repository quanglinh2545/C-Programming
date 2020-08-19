void cau2()
{
	FILE*f;
	f=fopen("chuoi.inp","rt");
	char*s;
	s=new char[256];
	fprintf(g,"cau 2:\n",f);
	while(!feof(f))
	{
		fgets(s,256,f);
		int h=strlen(s)-1;
		fprintf(g,"%d\n",h);
	}
	fclose(f);
}