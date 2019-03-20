HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [ ] **If you volunteer to give the presentation next week, check this.**

--------------------

# 實驗題目

觀察C function要怎麼傳遞呼叫的參數以及回傳值

* 藉由遞增的參數以及不同型態的參數來觀察，我們將修改`main.c`如下:

```
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
```

* 此外，可以藉由objdump觀察轉譯至組語的結果

```
Disassembly of section .mytext:

00000000 <reset_handler-0x8>:
   0:	20000100 	andcs	r0, r0, r0, lsl #2
   4:	00000009 	andeq	r0, r0, r9

00000008 <reset_handler>:
   8:	b590      	push	{r4, r7, lr}
   a:	b083      	sub	sp, #12
   c:	af02      	add	r7, sp, #8
   e:	f000 f835 	bl	7c <arg_N_rtn_N>
  12:	f000 f839 	bl	88 <arg_N_rtn_1>
  16:	4b15      	ldr	r3, [pc, #84]	; (6c <reset_handler+0x64>)
  18:	681b      	ldr	r3, [r3, #0]
  1a:	4618      	mov	r0, r3
  1c:	f000 f84e 	bl	bc <arg_1_rtn_N>
  20:	4b13      	ldr	r3, [pc, #76]	; (70 <reset_handler+0x68>)
  22:	e9d3 2300 	ldrd	r2, r3, [r3]
  26:	4610      	mov	r0, r2
  28:	4619      	mov	r1, r3
  2a:	f000 f839 	bl	a0 <arg_d_rtn_1>
  2e:	4b0f      	ldr	r3, [pc, #60]	; (6c <reset_handler+0x64>)
  30:	681b      	ldr	r3, [r3, #0]
  32:	4618      	mov	r0, r3
  34:	f000 f84c 	bl	d0 <arg_1_rtn_1>
  38:	4b0e      	ldr	r3, [pc, #56]	; (74 <reset_handler+0x6c>)
  3a:	6819      	ldr	r1, [r3, #0]
  3c:	4b0b      	ldr	r3, [pc, #44]	; (6c <reset_handler+0x64>)
  3e:	681a      	ldr	r2, [r3, #0]
  40:	4b0d      	ldr	r3, [pc, #52]	; (78 <reset_handler+0x70>)
  42:	681b      	ldr	r3, [r3, #0]
  44:	4608      	mov	r0, r1
  46:	4611      	mov	r1, r2
  48:	461a      	mov	r2, r3
  4a:	f000 f84d 	bl	e8 <arg_3_rtn_1>
  4e:	4b0a      	ldr	r3, [pc, #40]	; (78 <reset_handler+0x70>)
  50:	6818      	ldr	r0, [r3, #0]
  52:	4b08      	ldr	r3, [pc, #32]	; (74 <reset_handler+0x6c>)
  54:	6819      	ldr	r1, [r3, #0]
  56:	4b05      	ldr	r3, [pc, #20]	; (6c <reset_handler+0x64>)
  58:	681a      	ldr	r2, [r3, #0]
  5a:	4b07      	ldr	r3, [pc, #28]	; (78 <reset_handler+0x70>)
  5c:	681c      	ldr	r4, [r3, #0]
  5e:	4b05      	ldr	r3, [pc, #20]	; (74 <reset_handler+0x6c>)
  60:	681b      	ldr	r3, [r3, #0]
  62:	9300      	str	r3, [sp, #0]
  64:	4623      	mov	r3, r4
  66:	f000 f84d 	bl	104 <arg_5_rtn_N>
  6a:	e7fe      	b.n	6a <reset_handler+0x62>
  6c:	00000120 	andeq	r0, r0, r0, lsr #2
  70:	00000130 	andeq	r0, r0, r0, lsr r1
  74:	00000128 	andeq	r0, r0, r8, lsr #2
  78:	00000124 	andeq	r0, r0, r4, lsr #2

0000007c <arg_N_rtn_N>:
  7c:	b480      	push	{r7}
  7e:	af00      	add	r7, sp, #0
  80:	46bd      	mov	sp, r7
  82:	f85d 7b04 	ldr.w	r7, [sp], #4
  86:	4770      	bx	lr

00000088 <arg_N_rtn_1>:
  88:	b480      	push	{r7}
  8a:	af00      	add	r7, sp, #0
  8c:	4b03      	ldr	r3, [pc, #12]	; (9c <arg_N_rtn_1+0x14>)
  8e:	681b      	ldr	r3, [r3, #0]
  90:	4618      	mov	r0, r3
  92:	46bd      	mov	sp, r7
  94:	f85d 7b04 	ldr.w	r7, [sp], #4
  98:	4770      	bx	lr
  9a:	bf00      	nop
  9c:	00000128 	andeq	r0, r0, r8, lsr #2

000000a0 <arg_d_rtn_1>:
  a0:	b480      	push	{r7}
  a2:	b083      	sub	sp, #12
  a4:	af00      	add	r7, sp, #0
  a6:	e9c7 0100 	strd	r0, r1, [r7]
  aa:	e9d7 2300 	ldrd	r2, r3, [r7]
  ae:	4610      	mov	r0, r2
  b0:	4619      	mov	r1, r3
  b2:	370c      	adds	r7, #12
  b4:	46bd      	mov	sp, r7
  b6:	f85d 7b04 	ldr.w	r7, [sp], #4
  ba:	4770      	bx	lr

000000bc <arg_1_rtn_N>:
  bc:	b480      	push	{r7}
  be:	b083      	sub	sp, #12
  c0:	af00      	add	r7, sp, #0
  c2:	6078      	str	r0, [r7, #4]
  c4:	370c      	adds	r7, #12
  c6:	46bd      	mov	sp, r7
  c8:	f85d 7b04 	ldr.w	r7, [sp], #4
  cc:	4770      	bx	lr
  ce:	bf00      	nop

000000d0 <arg_1_rtn_1>:
  d0:	b480      	push	{r7}
  d2:	b083      	sub	sp, #12
  d4:	af00      	add	r7, sp, #0
  d6:	6078      	str	r0, [r7, #4]
  d8:	687b      	ldr	r3, [r7, #4]
  da:	4618      	mov	r0, r3
  dc:	370c      	adds	r7, #12
  de:	46bd      	mov	sp, r7
  e0:	f85d 7b04 	ldr.w	r7, [sp], #4
  e4:	4770      	bx	lr
  e6:	bf00      	nop

000000e8 <arg_3_rtn_1>:
  e8:	b480      	push	{r7}
  ea:	b085      	sub	sp, #20
  ec:	af00      	add	r7, sp, #0
  ee:	60f8      	str	r0, [r7, #12]
  f0:	60b9      	str	r1, [r7, #8]
  f2:	607a      	str	r2, [r7, #4]
  f4:	687b      	ldr	r3, [r7, #4]
  f6:	4618      	mov	r0, r3
  f8:	3714      	adds	r7, #20
  fa:	46bd      	mov	sp, r7
  fc:	f85d 7b04 	ldr.w	r7, [sp], #4
 100:	4770      	bx	lr
 102:	bf00      	nop

00000104 <arg_5_rtn_N>:
 104:	b480      	push	{r7}
 106:	b085      	sub	sp, #20
 108:	af00      	add	r7, sp, #0
 10a:	60f8      	str	r0, [r7, #12]
 10c:	60b9      	str	r1, [r7, #8]
 10e:	607a      	str	r2, [r7, #4]
 110:	603b      	str	r3, [r7, #0]
 112:	69bb      	ldr	r3, [r7, #24]
 114:	4618      	mov	r0, r3
 116:	3714      	adds	r7, #20
 118:	46bd      	mov	sp, r7
 11a:	f85d 7b04 	ldr.w	r7, [sp], #4
 11e:	4770      	bx	lr

Disassembly of section .data:

00000120 <one>:
 120:	00001111 	andeq	r1, r0, r1, lsl r1

00000124 <two>:
 124:	00002222 	andeq	r2, r0, r2, lsr #4

00000128 <three>:
 128:	00003333 	andeq	r3, r0, r3, lsr r3
 12c:	00000000 	andeq	r0, r0, r0

00000130 <DoubleNum>:
 130:	916872b0 	strhls	r7, [r8, #-32]!	; 0xffffffe0
 134:	3fbf7ced 	svccc	0x00bf7ced
```

* 可以看到在呼叫函數後都會先分配一塊stack的空間`push {7}`，並且將變數存在該下減的sp的位址中，等到函數呼叫才會被倒出來使用(幾乎每個函數都有)

```
  a0:	b480      	push	{r7}
  a2:	b083      	sub	sp, #12
  a4:	af00      	add	r7, sp, #0
```

* 在下面可以觀察到函數使用三個參數的載入情形

```
  ee:	60f8      	str	r0, [r7, #12]
  f0:	60b9      	str	r1, [r7, #8]
  f2:	607a      	str	r2, [r7, #4]
```

* 值得注意的是如果輸入超過4個以上參數的話，第5個將會被放到stack中，如同下面:

```
 112:	69bb      	ldr	r3, [r7, #24]
```

結果與討論
===

* 以上的規則可以參考 Procedure Call Standard for the ARM® Architecture 文件，內容記載了各暫存器的不同用途

![image](https://github.com/morning78913/ESEmbedded_HW03/blob/master/img/AAPCS%20core%20registers.jpg)

* 並且詳盡告知r0~r3這四個是專門拿來存參數以及回傳結果的暫存器

![image](https://github.com/morning78913/ESEmbedded_HW03/blob/master/img/statement.jpg)
