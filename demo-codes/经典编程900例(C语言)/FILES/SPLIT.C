#include <stdio.h>
#include <dir.h>
#include <stdlib.h>

void main (void)
  {
    char *path_1 = "C:\\SUBDIR\\FILENAME.EXT";
    char *path_2 = "SUBDIR\\FILENAME.EXT";
    char *path_3 = "FILENAME.EXE";

    char subdir[_MAX_DIR];
    char drive[_MAX_DRIVE];
    char filename[_MAX_FNAME];
    char extension[_MAX_EXT];

    _splitpath (path_1, drive, subdir, filename, extension);
    printf ("Splitting %s\n", path_1);
    printf ("Drive %s Subdir %s Filename %s Extension %s\n",
      drive, subdir, filename, extension);
  
    _splitpath (path_2, drive, subdir, filename, extension);
    printf ("Splitting %s\n", path_2);
    printf ("Drive %s Subdir %s Filename %s Extension %s\n",
      drive, subdir, filename, extension);

    _splitpath (path_3, drive, subdir, filename, extension);
    printf ("Splitting %s\n", path_3);
    printf ("Drive %s Subdir %s Filename %s Extension %s\n",
      drive, subdir, filename, extension);

  }

