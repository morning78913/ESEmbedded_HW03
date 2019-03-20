void	arg_N_rtn_N(void);
int	arg_N_rtn_1(void);
void 	arg_1_rtn_N(int);
double	arg_d_rtn_1(double);
int 	arg_1_rtn_1(int);
int 	arg_3_rtn_1(int, int, int);
int	arg_5_rtn_N(int ,int, int, int, int);

int	one = 0x1111;
int	two = 0x2222;
int	three = 0x3333;
double	DoubleNum = 0.123;

void reset_handler(void)
{
	arg_N_rtn_N();
	arg_N_rtn_1();
	arg_1_rtn_N(one);
	arg_d_rtn_1(DoubleNum);
	arg_1_rtn_1(one);
	arg_3_rtn_1(three, one, two);
	arg_5_rtn_N(two, three, one, two, three);

	while (1)
	;
}

/********************************/

void	arg_N_rtn_N(void)
{
	
}

int	arg_N_rtn_1(void)
{
	return three;
}

double	arg_d_rtn_1(double d)
{
	return d;
}

void	arg_1_rtn_N(int a)
{

}

int	arg_1_rtn_1(int a)
{
	return a;
}

int	arg_3_rtn_1(int a, int b, int c)
{
	return c;
}

int	arg_5_rtn_N(int a, int b, int c, int d, int e)
{
	return e;
}
