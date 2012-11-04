#include <stdio.h>
#include <math.h>

enum coordinate_type { RECTANGULAR, POLAR };
struct complex_struct {
    enum coordinate_type t;
	double a, b;
};

double rect_real_part(struct complex_struct z)
{
	return z.a;
}

double rect_img_part(struct complex_struct z)
{
	return z.b;
}

double rect_magnitude(struct complex_struct z)
{
	return sqrt(z.a * z.a + z.b * z.b);
}

double rect_angle(struct complex_struct z)
{
	double PI = acos(-1.0);

	if (z.a > 0)
		return atan(z.b / z.a);
	else
		return atan(z.b / z.a) + PI;
}

double pol_real_part(struct complex_struct z)
{
	return z.a * cos(z.b);
}

double pol_img_part(struct complex_struct z)
{
	return z.a * sin(z.b);
}

double pol_magnitude(struct complex_struct z)
{
	return z.a;
}

double pol_angle(struct complex_struct z)
{
	return z.b;
}

double (*real_part_tbl[])(struct complex_struct) = { rect_real_part, pol_real_part };
double (*img_part_tbl[])(struct complex_struct) = { rect_img_part, pol_img_part };
double (*magnitude_tbl[])(struct complex_struct) = { rect_magnitude, pol_magnitude };
double (*angle_tbl[])(struct complex_struct) = { rect_angle, pol_angle };

#define real_part(z) real_part_tbl[z.t](z)
#define img_part(z) img_part_tbl[z.t](z)
#define magnitude(z) magnitude_tbl[z.t](z)
#define angle(z) angle_tbl[z.t](z)

int main(void)
{
	
	return 0;
}