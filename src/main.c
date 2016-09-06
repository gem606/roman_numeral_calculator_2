/*
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "roman_numeral.h"

int main(void)
{
	struct calculator_register *pregister, *pptr, *dptr;
	long int accumul = 0, saved_accumul;
	int nreg = 0, request, strl, *reg, token, i;
	char *rn_string, *sdisplay;

	/* Allocate storage */
	rn_string = (char *)calloc(MAX_STRING_LENGTH + 1, sizeof(char));
	assert(rn_string != NULL);

	pptr = (struct calculator_register *)calloc(MAX_NUMBER_REGISTERS,
			sizeof(struct calculator_register));
	assert(pptr != NULL);
	pregister = pptr;

	while (TRUE) {
		/* Display User Interface */
		request = roman_numeral_calculator_interface();

		switch(request) {
		case 1:
			if (nreg >= MAX_NUMBER_REGISTERS) {
				printf("Calculator Registers - FULL\n");
				continue;
			}

			/* Get Roman Numeral String */
			memset(rn_string, '\0', MAX_STRING_LENGTH);
			getstring(rn_string);

			/* Validate String */
			if ((valid_roman_numeral_string(rn_string)) != SUCCESS) {
				printf("Invalid Roman Numeral- String = %s\n", rn_string);
				continue;
			}

			/* Parse Roman Numeral String */
			strl = strlen(rn_string);
			reg = (int *)calloc(strl + 1, sizeof(int));

			assert(reg != NULL);

			if ((token = roman_numeral_parser(rn_string, reg, strl)) <= 0) {
				free(reg);
				continue;
			}

			pptr->register_token = token;

			/* Compute value or Roman Numeral String */
			pptr->register_value = compute_value_roman_numeral_string(reg, token);

			/* Update register indeces */
			pptr += 1;
			nreg++;
			free(reg);

			break;
		case 2:
			/* Add Roman Numeral String */
			dptr = pregister;

			/* Accumulate Roman Numeral Value */
			if (!nreg && !accumul) {
				printf("Accumulator = *****\n");
				continue;
			}

			/* Add last register value to accumulator */
			if (nreg) {
				dptr += (nreg - 1);
				numerical_adder(&accumul, dptr->register_value);

				dptr->register_value = 0;

				/* Display the Roman Numeral Register Value */
				sdisplay = (char *)calloc(MAX_STRING_LENGTH + 1, sizeof(char));
				assert(sdisplay != NULL);

				roman_numeral_value_to_string_conversion(sdisplay, accumul,
					MAX_STRING_LENGTH);

				if (strlen(sdisplay) > 0)
					printf("Accumulator = %s\n", sdisplay);

				/* Adjust register tracker and pointer */
				nreg--;
				pptr -= 1;
				free(sdisplay);
			}
			break;
		case 3:
			/* Subtracting Roman Numeral String */
			dptr = pregister;

			/* Accumulate Roman Numeral Value */
			if (!nreg && !accumul) {
				printf("Accumulator = *****\n");
				continue;
			}

			if (!nreg && accumul) {
				/* Display the Roman Numeral Register Value */
				sdisplay = (char *)calloc(MAX_STRING_LENGTH + 1, sizeof(char));
				assert(sdisplay != NULL);

				roman_numeral_value_to_string_conversion(sdisplay, accumul,
					MAX_STRING_LENGTH);

				if (strlen(sdisplay) > 0)
					printf("Accumulator = %s\n", sdisplay);

				free(sdisplay); 
				continue;
			}

			dptr += (nreg - 1);
			if (nreg == 1 && !accumul)
				numerical_adder(&accumul, dptr->register_value);
			else {
				/* Subtract last register value from accumulator */
				saved_accumul = accumul;

				numerical_subtractor(&accumul, dptr->register_value);

				if (accumul <= 0) {
					accumul = saved_accumul;
					printf("Accumulator = *****\n");
					continue;
				}
			}
			dptr->register_value = 0;

			/* Display the Roman Numeral Register Value */
			sdisplay = (char *)calloc(MAX_STRING_LENGTH + 1, sizeof(char));
			assert(sdisplay != NULL);

			roman_numeral_value_to_string_conversion(sdisplay, accumul,
				MAX_STRING_LENGTH);

			if (strlen(sdisplay) > 0)
				printf("Accumulator = %s\n", sdisplay);

			/* Adjust register tracker and pointer */
			nreg--;
			pptr -= 1;
			free(sdisplay);
			break;
		case 4:
			/* Display the Roman Numeral Register Value */
			sdisplay = (char *)calloc(MAX_STRING_LENGTH + 1, sizeof(char));
			assert(sdisplay != NULL);

			dptr = pregister;

			for ( i = 0; i < nreg; i++) {
				roman_numeral_value_to_string_conversion(sdisplay,
					(long int)dptr->register_value, MAX_STRING_LENGTH);

				if (strlen(sdisplay) > 0)
					printf("Register[%d] = %s\n", i, sdisplay);

				dptr += 1;
			}
			free(sdisplay);				
			break;
		case 5:
			/* Display Accumulator Value */
			if (!accumul) {
				printf("Accumulator = *****\n");
				continue;
			}

			/* Display the Roman Numeral Register Value */
			sdisplay = (char *)calloc(MAX_STRING_LENGTH + 1, sizeof(char));
			assert(sdisplay != NULL);

			roman_numeral_value_to_string_conversion(sdisplay, accumul,
					MAX_STRING_LENGTH);

			if (strlen(sdisplay) > 0)
				printf("Accumulator = %s\n", sdisplay);

			free(sdisplay);
			break;
		case 6:
			/* Clear Accumulator */
			accumul = 0;
			break;
		case 7:
			/* Exit Roman Numeral Calculator */
			goto out;
		default:
			printf("\nUnsupported Operational Request\n\n");
			break;
		}
	}
out:
	free(pregister);
	free(rn_string);

	return 0;
}
