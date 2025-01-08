#include "DriverComms.h"
#include "Values.h"



//Split combo pattern into mask/pattern
void Parse(char* combo, char* pattern, char* mask)
{
	unsigned int patternLen = (strlen(combo) + 1) / 3;

	for (unsigned int i = 0; i < strlen(combo); i++)
	{
		if (combo[i] == ' ')
		{
			continue;
		}

		else if (combo[i] == '?')
		{
			mask[(i + 1) / 3] = '?';
			i += 2;
		}

		else
		{
			char byte = (char)strtol(&combo[i], 0, 16);
			pattern[(i + 1) / 3] = byte;
			mask[(i + 1) / 3] = 'x';
			i += 2;
		}
	}
	pattern[patternLen] = '\0';
	mask[patternLen] = '\0';
}

char* In_Scan(char* pattern, char* mask, char* begin, unsigned int size)
{
	unsigned int patternLength = strlen(mask);

	for (unsigned int i = 0; i < size - patternLength; i++)
	{
		bool found = true;
		for (unsigned int j = 0; j < patternLength; j++)
		{
			if (mask[j] != '?' && pattern[j] != *(begin + i + j))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return (begin + i);
		}
	}
	return nullptr;
}

struct buff
{
	char buffer[4096*32]; 
};

//External Wrapper
char* Ex_Scan(char* pattern, char* mask, char* begin, char* end)
{
	char* currentChunk = begin;
	SIZE_T bytesRead = (4096*32);

	while (currentChunk < end)
	{
		buff Buffer;


		//ReadProcessMemory(process->handle, currentChunk, &buffer, sizeof(buffer), &bytesRead);
		Buffer = ReadPM<buff>((UINT_PTR)currentChunk);

		char* internalAddress = In_Scan(pattern, mask, (char*)&Buffer, bytesRead);

		if (internalAddress != nullptr)
		{
			//calculate from internal to external
			uintptr_t offsetFromBuffer = internalAddress - (char*)&Buffer;
			return (currentChunk + offsetFromBuffer);
		}
		else
		{
			//advance to next chunk
			currentChunk = currentChunk + bytesRead;
		}
	}
	return nullptr;
}

uint32_t get_offset_from_instruction(uintptr_t instruction_address, uintptr_t base_of_module)
{
	uint64_t offsetnextinstruction = (instruction_address + 0x3 + 0x4) - base_of_module;
	uint32_t lpoffset = ReadPM<uint32_t>(instruction_address + 0x3) + offsetnextinstruction;
	return lpoffset;
}

uint32_t get_offset_from_instruction_2(uintptr_t instruction_address, uintptr_t base_of_module)
{
	uint64_t offsetnextinstruction = (instruction_address + 0x2 + 0x5) - base_of_module;
	uint32_t lpoffset = ReadPM<uint32_t>(instruction_address + 0x2) + offsetnextinstruction;
	return lpoffset;
}

uint64_t get_offset_from_sig(char* signature, char* mask, char* start, char* end)
{
	return get_offset_from_instruction((uintptr_t)Ex_Scan(signature, mask, start, end), (uintptr_t)start);
}
uint64_t get_offset_from_sig_2(char* signature, char* mask, char* start, char* end)
{
	return get_offset_from_instruction_2((uintptr_t)Ex_Scan(signature, mask, start, end), (uintptr_t)start);
}

uint64_t get_offset_wrapper(Signatures::Signature sig, uint64_t start, uint64_t end)
{
	return get_offset_from_instruction((uintptr_t)Ex_Scan((char*)sig.bytes, (char*)sig.mask, (char*)start, (char*)end), start);
}

uint64_t get_offset_wrapper_2(Signatures::Signature sig, uint64_t start, uint64_t end)
{
	return get_offset_from_instruction_2((uintptr_t)Ex_Scan((char*)sig.bytes, (char*)sig.mask, (char*)start, (char*)end), start);
}

