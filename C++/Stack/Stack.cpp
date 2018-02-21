#include "Stack.hpp"
#include <iostream>

const CStack_data_t CSTACK_POISON = -666666;

CStack::CStack()
{
	amount = 0;
	for (int i = 0; i < CSTACK_SIZE; i++)
		data[i] = CSTACK_POISON;
}

CStack::~CStack()
{
	amount = 0;
	for (int i = 0; i < CSTACK_SIZE; i++)
		data[i] = CSTACK_POISON;
}

CStack_data_t CStack::pop()
{
	if (amount == 0)
	{
		help(CSTACK_POP_FROM_EMPTY);
		return CSTACK_POISON;
	}
	amount--;
	CStack_data_t result = data[amount];
	data[amount] = CSTACK_POISON;
	return result;
}

CStack_error_code CStack::push(CStack_data_t value)
{
	if (amount == CSTACK_SIZE)
	{
		help(CSTACK_PUSH_TO_FULL);
		return CSTACK_PUSH_TO_FULL;
	}
	data[amount++] = value;
	return check();
}

CStack_error_code CStack::check()
{
	if (amount < 0) return CSTACK_NEGATIVE_AMOUNT;
	if (amount == CSTACK_SIZE) return CSTACK_FULL;
	if (amount > CSTACK_SIZE) return CSTACK_BIG_AMOUNT;
	return CSTACK_OK;
}

void CStack::dump()
{
	std::cout << "CStack dump. [" << convert_error_code_to_string(check()) << "]" << std::endl;
	std::cout << "{" << std::endl;
	std::cout << "	amount = " << amount << std::endl;
	for (int i = 0; i < CSTACK_SIZE; i++)
		if (data[i] != CSTACK_POISON)
			std::cout << "	data[" << i << "] = " << data[i] << std::endl;
	std:: cout << std::endl << "}" << std::endl;
}

const char* convert_error_code_to_string(CStack_error_code code)
{
	switch (code)
	{
		#define _RET_CODE(code) case code: return #code;
		_RET_CODE(CSTACK_OK)
		_RET_CODE(CSTACK_NEGATIVE_AMOUNT)
		_RET_CODE(CSTACK_FULL)
		_RET_CODE(CSTACK_BIG_AMOUNT)
		_RET_CODE(CSTACK_PUSH_TO_FULL)
		_RET_CODE(CSTACK_POP_FROM_EMPTY)
		#undef _RET_CODE
	}
}

void help(CStack_error_code code)
{
	if (code != 0)
		std::cout << "\033[1;31m" << convert_error_code_to_string(code) << "\033[0m" << std::endl;
	else
		std::cout << convert_error_code_to_string(code) << std::endl;
}
