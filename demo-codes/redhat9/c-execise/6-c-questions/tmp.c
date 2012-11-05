main()
{ int i;
  for (i=1;i<=10000;i++)
 {
  if (i%2!=0)
    if(i%3==0)
      printf("%d",i);
    else continue;
  else continue;
 }
}
