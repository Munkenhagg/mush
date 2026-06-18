#include <mush.h>
#include <user_config.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char **tokenize(char *cmdinput, char **cmdoutput) {
	tok_state_t tok_state = NORMAL;
	tok_flags_t tok_flags;
	int curarrnum = 0;
	bool last_was_space = false;
	for (int i = 0; cmdinput[i] != '\0'; i++) {
		char *arrapp = NULL;
		char stri[2] = {cmdinput[i], '\0'};
		switch (tok_state) {
			case NORMAL: {
				switch(cmdinput[i]) {
					case ' ': {
						if (!last_was_space) {
							curarrnum++;
							last_was_space = true;
						}
						break;
					}
					case '\"': {
						tok_state = DOUBLE_QUOTE;
						break;
					}
					case '\'': {
						tok_state = SINGLE_QUOTE;
						break;
					}
					case '$': {
						tok_flags |= VARIABLE;
						break;
					}
					default: {
						last_was_space = false;
					}
				}
				if (i != 0) {
					arrapp = strjoin(cmdoutput[curarrnum],stri);
				} else {
					arrapp = strdup(stri);
				}
				cmdoutput[curarrnum] = arrapp;
				break;
			}
			case DOUBLE_QUOTE: {
				switch(cmdinput[i]) {
					case '$': {
						tok_flags |= VARIABLE;
						break;
					}
					case '\"': {
						tok_state = NORMAL;
						break;
					}
					default:
				}
				arrapp = strjoin(cmdoutput[curarrnum],stri);
				cmdoutput[curarrnum] = arrapp;
				break;
			}
			default: {
				printf("tokenizer: tok_state enum may be broken. this shouldnt happen on a stable version\ncause: did not find a case for tok_state\n");
				#ifdef STRICT_MODE
					printf("Exiting due to strict mode. Reason should be above\n");
					exit_iact_sh(0);
				#endif
				break;
			}
		}
	}
	return cmdoutput;
}
