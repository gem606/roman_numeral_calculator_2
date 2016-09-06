#include <check.h>
#include <stdlib.h>
#include "../src/roman_numeral.h"

static char *teststring[] = {
	"IVXLCDM", "ivxlcdm", "abcdefghi", "MCMLXVII", "MCMXLIIII", "MCMXLIII",
	"CLXXXXIX", "CDXXXIX", "MCCCCMLVII", "MCCCLVIII", "MCMVVIII",
	"MCMLVII", "LLLVD", "MCMLXIII", "MCDDDDD", "MCDLVIII", "IVX", "III",
	"MMCDLXXXVIII"
};

static int testparsed[] = {18, 18, 15, 10, 8, 4, 2};

START_TEST(check_roman_numeral_character)
{
	int strlength, len = 0;

	strlength = all_roman_numeral_character(*(&teststring[0]));
	ck_assert_int_gt(strlength, len);
}
END_TEST

START_TEST(check_I_substring_in_roman_numeral)
{
	char *rtstr, *tstring = "IIII";
	
	rtstr = (char *)is_substring_in_roman_numeral(*(&teststring[5]), tstring);
	ck_assert_ptr_eq(rtstr, NULL);
}
END_TEST

START_TEST(check_X_substring_in_roman_numeral)
{
	char *rtstr, *tstring = "XXXX";
	
	rtstr = (char *)is_substring_in_roman_numeral(*(&teststring[7]), tstring);
	ck_assert_ptr_eq(rtstr, NULL);
}
END_TEST

START_TEST(check_C_substring_in_roman_numeral)
{
	char *rtstr, *tstring = "CCCC";
	
	rtstr = (char *)is_substring_in_roman_numeral(*(&teststring[9]), tstring);
	ck_assert_ptr_eq(rtstr, NULL);
}
END_TEST

START_TEST(check_V_character_frequency)
{
	int ncount;
	char tstchar = 'V';

	ncount = roman_numeral_character_frequency(*(&teststring[11]), tstchar);
	ck_assert_int_le(ncount, 1);
}
END_TEST

START_TEST(check_L_character_frequency)
{
	int ncount;
	char tstchar = 'L';

	ncount = roman_numeral_character_frequency(*(&teststring[13]), tstchar);
	ck_assert_int_le(ncount, 1);
}
END_TEST
		
START_TEST(check_D_character_frequency)
{
	int ncount;
	char tstchar = 'D';

	ncount = roman_numeral_character_frequency(*(&teststring[15]), tstchar);
	ck_assert_int_le(ncount, 1);
}
END_TEST

START_TEST(check_roman_token_indexer)
{
	int tindex, len, sindex = 2;

	tindex = roman_numeral_token_indexer(*(&teststring[17]), &len);
	ck_assert_int_eq(tindex, sindex);
}
END_TEST

START_TEST(check_roman_numeral_token_extractor)
{
	int *parser_str, slen, indx;

	slen = strlen(*(&teststring[18]));
	parser_str = calloc((slen + 1), sizeof(int));
	ck_assert_ptr_ne(parser_str, NULL);
	indx = roman_numeral_parser((*(&teststring[18])), parser_str, slen);
	ck_assert_int_ne(-1, indx);
	free(parser_str);
}
END_TEST

START_TEST(check_roman_numeral_string_value)
{
	int string_value, test_value, *parsed_string, nelement;

	parsed_string = &testparsed[0];
	test_value = 2488;
	nelement = sizeof(testparsed) / sizeof(int);

	string_value = compute_value_roman_numeral_string(parsed_string, nelement);
	ck_assert_int_eq(string_value, test_value);
}
END_TEST

START_TEST(check_roman_numeral_value_to_string_conversion)
{
	int testvalue = 2488;
	char *rtstring;

	rtstring = (char *)calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	ck_assert_ptr_ne(rtstring, NULL);

	roman_numeral_value_to_string_conversion(rtstring, (long int)testvalue, MAX_STRING_LENGTH);
	ck_assert_str_eq(rtstring, teststring[18]);
}
END_TEST

START_TEST(check_numerical_adder)
{
	int testvalue_1 = 2488, testvalue_2 = 7986;
	long int results = 0;

	numerical_adder(&results, testvalue_2);
	ck_assert_int_eq(results, testvalue_2);
}
END_TEST

START_TEST(check_numerical_subtractor)
{
	int testvalue_2 = 2488, testvalue_1 = 5498;
	long int results = 7986;

	numerical_subtractor(&results, testvalue_2);
	ck_assert_int_eq(results, testvalue_1);
}
END_TEST
			
Suite *roman_numeral_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Roman_Numeral");

	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, check_roman_numeral_character);
	tcase_add_test(tc_core, check_I_substring_in_roman_numeral);
	tcase_add_test(tc_core, check_X_substring_in_roman_numeral);
	tcase_add_test(tc_core, check_C_substring_in_roman_numeral);
	tcase_add_test(tc_core, check_V_character_frequency);
	tcase_add_test(tc_core, check_L_character_frequency);
	tcase_add_test(tc_core, check_D_character_frequency);
	tcase_add_test(tc_core, check_roman_token_indexer);
	tcase_add_test(tc_core, check_roman_numeral_token_extractor);
	tcase_add_test(tc_core, check_roman_numeral_string_value);
	tcase_add_test(tc_core, check_roman_numeral_value_to_string_conversion);
	tcase_add_test(tc_core, check_numerical_adder);
	tcase_add_test(tc_core, check_numerical_subtractor);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = roman_numeral_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
