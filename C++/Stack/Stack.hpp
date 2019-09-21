const int CSTACK_SIZE = 1024;
typedef int CStack_data_t;

typedef enum CStack_error_codes
{
	CSTACK_OK = 0,
	CSTACK_NEGATIVE_AMOUNT,
	CSTACK_FULL,
	CSTACK_BIG_AMOUNT,
	CSTACK_PUSH_TO_FULL,
	CSTACK_POP_FROM_EMPTY
} CStack_error_code;

struct CStack
{
	CStack_data_t data[CSTACK_SIZE];
	int amount;

	CStack();
	~CStack();
	
	CStack_error_code push(CStack_data_t value);
	CStack_data_t pop();
	CStack_error_code check();
	void dump();
};

const char* convert_error_code_to_string(CStack_error_code code);
void help(CStack_error_code code);
