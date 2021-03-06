// *******************************************************************************************
// This file is a part of GTShark software distributed under GNU GPL 3 licence.
// The homepage of the GTShark project is https://github.com/refresh-bio/GTShark
//
// Author : Sebastian Deorowicz and Agnieszka Danek
// Version: 1.1
// Date   : 2019-05-09
// *******************************************************************************************

#include "utils.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>

#ifdef OUR_STRTOL
// *****************************************************************************************
#ifdef __APPLE__
long int strtol(const char* str, char** endptr, int base)
#else
long int strtol(const char* str, char** endptr, int base) noexcept
#endif
{
	if (base != 10)
	{
		std::cerr << "unsuported base " << base << std::endl;
		fflush(stdout);
		getchar();
		exit(1);
	}

	long int val = 0;
	char *p = (char*)str;
	
	while (*p >= '0' && *p <= '9') 
	{
		val = val * 10 + (*p++ - '0');
	}

	if (endptr)
		*endptr = p;

	return val;
}
#endif

// ************************************************************************************
void cumulate_sums(vector<uint32_t> &v_hist, uint32_t &max_count)
{
	// Determine cumulated histogram
	uint32_t v = 0;
	uint32_t cum = 0;
	uint32_t hist_size = (uint32_t) v_hist.size();
	max_count = 0;

	for (uint32_t i = 0; i < hist_size; ++i)
	{
		v = v_hist[i];
		v_hist[i] = cum;
		cum += v;

		if (v > max_count)
			max_count = v;
	}
}

// ************************************************************************************
void cumulate_sums(array<uint32_t, SIGMA> &a_hist, uint32_t &max_count)
{
	// Determine cumulated histogram
	uint32_t v = 0;
	uint32_t cum = 0;
	uint32_t hist_size = (uint32_t)a_hist.size();
	max_count = 0;

	for (uint32_t i = 0; i < hist_size; ++i)
	{
		v = a_hist[i];
		a_hist[i] = cum;
		cum += v;

		if (v > max_count)
			max_count = v;
	}
}

// ************************************************************************************
void calc_cumulate_histogram(const vector<uint8_t> &data, vector<uint32_t> &v_hist, uint32_t &max_count)
{
	fill(v_hist.begin(), v_hist.end(), 0u);

	for (auto x : data)
		++v_hist[x];

	cumulate_sums(v_hist, max_count);
}

// ************************************************************************************
void calc_cumulate_histogram(const vector<pair<uint8_t, uint32_t>> &rle_data, vector<uint32_t> &v_hist, uint32_t &max_count)
{
	fill(v_hist.begin(), v_hist.end(), 0u);

	for (auto x : rle_data)
		v_hist[x.first] += x.second;

	cumulate_sums(v_hist, max_count);
}

// ************************************************************************************
string trim(string s)
{
	while (!s.empty() & (s.back() == '\n' || s.back() == '\r'))
		s.pop_back();

	return s;
}

// ************************************************************************************
uint64_t popcnt(uint64_t x)
{
	return _mm_popcnt_u64(x);
//	return __popcnt64(x);

	return 0;
}

// EOF
