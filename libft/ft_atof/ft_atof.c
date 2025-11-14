/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:40:36 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/13 19:58:20 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# define EXP_BIAS 0b01111111111
# define EXP_UNIT 0b0000000000000001

#if 1

// 指数部の桁数を取得する関数
// void	set_exp(unsigned char *res_ptr, const char *nptr)
// {
// 	uint16_t			exp;
// 	unsigned long long	comp;

// 	exp = EXP_BIAS;
// 	while (ft_isdigit(*nptr))
// 	{
// 		exp += EXP_UNIT;
// 		nptr++;
// 	}
// 	if (!exp || *nptr != '.')
// 		return (exp);
// 	nptr++;
// 	comp = 0;
// 	while (ft_isdigit(*nptr))
// 	{
// 	}
// }

double	ft_atof(const char *nptr)
{
	double				res;
	double				base;
	unsigned char		*res_ptr;

	res = 0;
	res_ptr = (unsigned char *)&res;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		res_ptr[7] |= (1 << 7) * (*(nptr++) == '-');
	while (ft_isdigit(*nptr))
		res = res * 10 + *(nptr++) - '0';
	if (*nptr != '.')
		return (res);
	nptr++;
	base = 0.1;
	while (ft_isdigit(*nptr))
	{
		res += (*(nptr++) - '0') * base;
		base *= 0.1;
	}
	return (res);
}

#include <stdlib.h>
int	main(int argc, char *argv[]) {
	double	my;
	double	real;

	if (argc == 1)
		return 1;
	my = ft_atof(argv[1]);
	real = atof(argv[1]);
	printf("ft\t:%.20f\n", my);
	printf("orig\t:%.20f\n", real);
	return (0);
}
#endif

void	print_specified_bytes_as_binary(unsigned char byte, int start, int end) {
	if (start < end || 7 < start || end < 0)
		return ;
	for (int bit = start; bit >= end; bit--) {
		if (byte & (1 << bit))
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
}

void	print_bytes_as_binary(unsigned char byte) {
	print_specified_bytes_as_binary(byte, 7, 0);
}

void	print_double_bits(void *ptr) {
	unsigned char	*bytes = (unsigned char *)ptr;
	size_t			i;

	i = 8;
	while (i != 0) {
		--i;
		if (i == 7) {
			print_specified_bytes_as_binary(bytes[i], 7, 7);
			write(1, ", ", 2);
			print_specified_bytes_as_binary(bytes[i], 6, 0);
		}
		else if (i == 6) {
			print_specified_bytes_as_binary(bytes[i], 7, 4);
			write(1, ", ", 2);
			print_specified_bytes_as_binary(bytes[i], 3, 0);
		}
		else
			print_bytes_as_binary(bytes[i]);
		if (i != 0 && i != 7)
			write(1, ", ", 2);
	}
	write(1, "\n", 1);
}

void	print_memory_bits(void *ptr, size_t size, bool big) {
	unsigned char	*bytes = (unsigned char *)ptr;

	if (big) {
		for (size_t i = size; i != 0; ) {
			print_bytes_as_binary(bytes[i]);
			--i;
			if (i != 0)
				write(1, ", ", 2);
		}
	}
	else {
		for (size_t i = 0; i < size; i++) {
			print_bytes_as_binary(bytes[i]);
			if (i < size - 1)
				write(1, ", ", 2);
		}
	}
	write(1, "\n", 1);
}

void	update_buff(int n, char *buff) {
	if (n == 1)
		buff[n] = '.';
	else
		buff[n] = '0';
	buff[n + 1] = '1';
}

void	print_minus_binary(int n) {
	char	buff[1025];

	memset(&buff, 0, 1025);
	buff[0] = '0';
	for (int i = 1; i < n + 1; i ++) {
		update_buff(i, buff);
		double atof_res = atof(buff);
		uint64_t uint_val;
		memcpy(&uint_val, &atof_res, sizeof(double));
		printf("# define T_P_%d	", i);
		printf("0x%016llx\n", (unsigned long long)uint_val);
	}
}

#include "atof.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long long	minus_table_1(int i)
{
	static const unsigned long long	g_two_minus_table[] = \
	{T_M_1, T_M_2, T_M_3, T_M_4, T_M_5, T_M_6, T_M_7, T_M_8, \
T_M_9, T_M_10, T_M_11, T_M_12, T_M_13, T_M_14, T_M_15, T_M_16, \
T_M_17, T_M_18, T_M_19, T_M_20, T_M_21, T_M_22, T_M_23, T_M_24, \
T_M_25, T_M_26, T_M_27, T_M_28, T_M_29, T_M_30, T_M_31, T_M_32, \
T_M_33, T_M_34, T_M_35, T_M_36, T_M_37, T_M_38, T_M_39, T_M_40, \
T_M_41, T_M_42, T_M_43, T_M_44, T_M_45, T_M_46, T_M_47, T_M_48, \
T_M_49, T_M_50, T_M_51, T_M_52, T_M_53, T_M_54, T_M_55, T_M_56, \
T_M_57, T_M_58, T_M_59, T_M_60, T_M_61, T_M_62, T_M_63, T_M_64, \
T_M_65, T_M_66, T_M_67, T_M_68, T_M_69, T_M_70, T_M_71, T_M_72, \
T_M_73, T_M_74, T_M_75, T_M_76, T_M_77, T_M_78, T_M_79, T_M_80, \
T_M_81, T_M_82, T_M_83, T_M_84, T_M_85, T_M_86, T_M_87, T_M_88, \
T_M_89, T_M_90, T_M_91, T_M_92, T_M_93, T_M_94, T_M_95, T_M_96, \
T_M_97, T_M_98, T_M_99, T_M_100, T_M_101, T_M_102, T_M_103, T_M_104, \
T_M_105, T_M_106, T_M_107, T_M_108};

	return (g_two_minus_table[i]);
}

unsigned long long	minus_table_2(int i)
{
	static const unsigned long long	g_two_minus_table[] = \
	{T_M_109, T_M_110, T_M_111, T_M_112, T_M_113, T_M_114, T_M_115, T_M_116, \
T_M_117, T_M_118, T_M_119, T_M_120, T_M_121, T_M_122, T_M_123, T_M_124, \
T_M_125, T_M_126, T_M_127, T_M_128, T_M_129, T_M_130, T_M_131, T_M_132, \
T_M_133, T_M_134, T_M_135, T_M_136, T_M_137, T_M_138, T_M_139, T_M_140, \
T_M_141, T_M_142, T_M_143, T_M_144, T_M_145, T_M_146, T_M_147, T_M_148, \
T_M_149, T_M_150, T_M_151, T_M_152, T_M_153, T_M_154, T_M_155, T_M_156, \
T_M_157, T_M_158, T_M_159, T_M_160, T_M_161, T_M_162, T_M_163, T_M_164, \
T_M_165, T_M_166, T_M_167, T_M_168, T_M_169, T_M_170, T_M_171, T_M_172, \
T_M_173, T_M_174, T_M_175, T_M_176, T_M_177, T_M_178, T_M_179, T_M_180, \
T_M_181, T_M_182, T_M_183, T_M_184, T_M_185, T_M_186, T_M_187, T_M_188, \
T_M_189, T_M_190, T_M_191, T_M_192, T_M_193, T_M_194, T_M_195, T_M_196, \
T_M_197, T_M_198, T_M_199, T_M_200, T_M_201, T_M_202, T_M_203, T_M_204, \
T_M_205, T_M_206, T_M_207, T_M_208, T_M_209, T_M_210, T_M_211, T_M_212, \
T_M_213, T_M_214, T_M_215, T_M_216};

	return (g_two_minus_table[i - 108]);
}

unsigned long long	minus_table_3(int i)
{
	static const unsigned long long	g_two_minus_table[] = \
	{T_M_217, T_M_218, T_M_219, T_M_220, T_M_221, T_M_222, T_M_223, T_M_224, \
T_M_225, T_M_226, T_M_227, T_M_228, T_M_229, T_M_230, T_M_231, T_M_232, \
T_M_233, T_M_234, T_M_235, T_M_236, T_M_237, T_M_238, T_M_239, T_M_240, \
T_M_241, T_M_242, T_M_243, T_M_244, T_M_245, T_M_246, T_M_247, T_M_248, \
T_M_249, T_M_250, T_M_251, T_M_252, T_M_253, T_M_254, T_M_255, T_M_256, \
T_M_257, T_M_258, T_M_259, T_M_260, T_M_261, T_M_262, T_M_263, T_M_264, \
T_M_265, T_M_266, T_M_267, T_M_268, T_M_269, T_M_270, T_M_271, T_M_272, \
T_M_273, T_M_274, T_M_275, T_M_276, T_M_277, T_M_278, T_M_279, T_M_280, \
T_M_281, T_M_282, T_M_283, T_M_284, T_M_285, T_M_286, T_M_287, T_M_288, \
T_M_289, T_M_290, T_M_291, T_M_292, T_M_293, T_M_294, T_M_295, T_M_296, \
T_M_297, T_M_298, T_M_299, T_M_300, T_M_301, T_M_302, T_M_303, T_M_304, \
T_M_305, T_M_306, T_M_307, T_M_308, T_M_309, T_M_310, T_M_311, T_M_312, \
T_M_313, T_M_314, T_M_315, T_M_316, T_M_317, T_M_318, T_M_319, T_M_320, \
T_M_321, T_M_322, T_M_323, T_M_324};

	return (g_two_minus_table[i - 216]);
}

unsigned long long	get_minus_table(int i)
{
	i -= 1;
	if (i < 0 || 324 <= i)
		return (0);
	if (0 <= i && i < 108)
		return (minus_table_1(i));
	if (108 <= i && i < 216)
		return (minus_table_2(i));
	return (minus_table_3(i));
}

// int	main(int argc, char *argv[])
// {
// 	u_double	u;

// 	if (argc == 1)
// 		return (1);
// 	if (argc == 2)
// 		u.i = 0x3fb999999999999a;
// 	else
// 		u.i = get_minus_table(atoi(argv[2]));
// 	printf("double: %f\n", u.d);
// 	print_double_bits(&u.i);
// 	if (u.d < atof(argv[1]))
// 		printf("big\n");
// 	else
// 		printf("small\n");
// 	return (0);
// }

#if 0
int	main(int argc, char *argv[])
{
	bool	big = false;
	if (argc == 1)
		return 1;
	if (2 < argc)
		big = true;
	double	atof_res = atof(argv[1]);
	uint64_t	uint_val;

	memcpy(&uint_val, &atof_res, sizeof(double));
	printf("atof\t:%.22f\n", atof_res);
	printf("binary\t:0x%016llx\n", (unsigned long long)uint_val);
	print_double_bits(&uint_val);
	return 0;
}

#endif
// #endif