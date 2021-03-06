
#include "generation.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	FILE* f;
	int i, j, k;

	f = fopen("wf_classes.cpp", "w");

	//macros
	fprintf(f, "#define __STDC_CONSTANT_MACROS\n#define __STDC_LIMIT_MACROS//these macros are not included by default in C++\n#include \"widefloat_float.h\"");

	fprintf(f, "\n\n\n#include \"wf_classes.hpp\"\n\n#include <climits> //for the highest values of integers\n#include <cmath> //for NAN\n\n\n");

	//tool for global state
	fprintf(f, "\n\n\t/* functions regarding global state (setters, getters, function for raising) */\nwidefloat_flags_t wf_fpstate::get_flags(){\n\treturn widefloat_get_flags();\n}\n\nint wf_fpstate::set_flags(widefloat_flags_t newflags){\n\treturn widefloat_set_flags(newflags);\n}\n\nint wf_fpstate::raise_flags(widefloat_flags_t newflags){\n\treturn widefloat_raise_flags(newflags);\n}\n\nwidefloat_roundingmode_t wf_fpstate::get_rounding_mode(){\n\treturn widefloat_get_rounding_mode();\n}\n\nint wf_fpstate::set_rounding_mode(widefloat_roundingmode_t new_rounding_mode){\n\treturn widefloat_set_rounding_mode(new_rounding_mode);\n}\n\n");

	//wf classes members
	fprintf(f, "\n\n\t/* definition of members and functions for widefloat classes */\n\n");

	//constructors
	fprintf(f, "\n\t/* constructors */\n");
	for(i=WF_TYPE;i<TYPE_NB;i++){
		constructor(f, i, -1);
		for(j=CPP_TYPE;j<TYPE_NB;j++){
			if(j==i){
				continue;
			}
			constructor(f, i, j);
		}
	}

	//casts
	fprintf(f, "\n\t/* casts */\n\n");
	for(i=WF_TYPE;i<TYPE_NB;i++){
		for(j=CPP_TYPE;j<WF_TYPE;j++){
			cast(f, i, j);
		}
	}

	//arithmetic
	fprintf(f, "\n\n\t/* operators : + - * / */\n");

	for(i=ARITH;i<ASSIGN;i++){
		for(j=CPP_TYPE;j<TYPE_NB;j++){
			for(k=WF_TYPE;k<TYPE_NB;k++){
				arith(f, j, i, k);
			}
		}
		for(j=WF_TYPE;j<TYPE_NB;j++){
			for(k=CPP_TYPE;k<WF_TYPE;k++){
				arith(f, j, i, k);
			}
		}
	}

	//comparisons
	fprintf(f, "\n\n\t/* comparisons */\n");
	for(i=COMP;i<COMP+6;i++){
		for(j=CPP_TYPE;j<TYPE_NB;j++){
			for(k=WF_TYPE;k<TYPE_NB;k++){
				comp(f, j, i, k);
			}
		}
		for(j=WF_TYPE;j<TYPE_NB;j++){
			for(k=CPP_TYPE;k<WF_TYPE;k++){
				comp(f, j, i, k);
			}
		}
	}

	//assignments
	fprintf(f, "\n\n\t/* assignments */\n");
	for(i=WF_TYPE;i<TYPE_NB;i++){
		for(j=CPP_TYPE;j<TYPE_NB;j++){
			if(j==i){
				continue;
			}
			assign(f, i, j);
		}
	}

	//extended assignments
	fprintf(f, "\n\n\t/* extended assignments*/\n");
	for(i=ASSIGN+1;i<=ASSIGN+4;i++){
		for(j=CPP_TYPE;j<TYPE_NB;j++){
			for(k=WF_TYPE;k<TYPE_NB;k++){
				ext_assign(f, j, i, k);
			}
		}
		for(j=WF_TYPE;j<TYPE_NB;j++){
			for(k=CPP_TYPE;k<WF_TYPE;k++){
				ext_assign(f, j, i, k);
			}
		}
	}

	/* + */
	fprintf(f, "\n\t/* unary plus */\n\n");
	for(i=WF_TYPE;i<TYPE_NB;i++){
		plus(f, i);
	}

	/* - */
	fprintf(f, "\n\t/* unary minus */\n\n");
	for(i=WF_TYPE;i<TYPE_NB;i++){
		minus(f, i);
	}

	/* sqrt */
	fprintf(f, "\n\t/* square root functions */\n");
	for(i=WF_TYPE;i<TYPE_NB;i++){
		for(j=WF_TYPE;j<=i;j++){
			wf_sqrt(f, i, j);
		}
	}

	/* fma */
	fprintf(f, "\n\t/* floating-point fused multiply and add */\n");
	for(i=WF_TYPE;i<TYPE_NB;i++){
		for(j=WF_TYPE;j<=i;j++){
			wf_fma(f, i, j);
		}
	}

	fclose(f);


	return 0;
}
