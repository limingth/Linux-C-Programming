#!/usr/bin/awk -f
BEGIN {FS=" ";count = 0}
{
	if($2 ~/\".*\"$/)
	{
		count++;
	} 
}
END {printf("包括的本地文件个数为：%d\n", count)}
