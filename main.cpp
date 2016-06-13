
#include <wiz/global.h>
#include <wiz/wizardError.h>
#include <vector>

namespace wiz {

	const long long BIGIINT_BASE = long long(1000000000); /// chk!!  changable?
	const std::vector<long long> zero_int(1, 0); /// ZERO_INT
											 // const std::vector<long long> one_int( 1, '1' );
	const std::vector<long long> ndef_int; ///  empty state..
		
	std::vector<long long> remove_first_zeros(const std::vector<long long>& x) /// remove first all zeros.
	{
		int zero_num = 0;

		for (int i = 0; i < x.size(); i++)
		{
			if (x[i] != 0) { break; }
			zero_num++;
		}
		if (0 == zero_num) { return x; }
		if (x.size() == zero_num) { return ndef_int; } /// chk...
		std::vector<long long> temp(x.size() - zero_num);
		for (int i = 0; i < temp.size(); i++)
		{
			temp[i] = x[i + zero_num];
		}

		return temp;
	}

	bool IsSameValues(const std::vector<long long>& arr1, const std::vector<long long>& arr2)
	{
		std::vector<long long> _arr1 = remove_first_zeros(arr1);
		std::vector<long long> _arr2 = remove_first_zeros(arr2);

		if (_arr1.size() != _arr2.size()) { return false; }
		for (int i = 0; i < _arr1.size(); i++)
		{
			if (_arr1[i] != _arr2[i]) { return false; }
		}
		return true;
	}
	

	bool operator<(const std::vector<long long>& x, const std::vector<long long>& y)
	{
		std::vector<long long> _x = remove_first_zeros(x);
		std::vector<long long> _y = remove_first_zeros(y);

		if (_x.size() > _y.size()) { return false; }
		if (_x.size() < _y.size()) { return true; }
		if (_x.empty()) // also y.empty..
		{
			return false; /// chk?
		}
		for (int i = 0; i < _x.size(); i++)
		{
			if (_x[i] > _y[i]) { return false; }
			if (_x[i] < _y[i]) { return true; }
		}
		// same...
		return false;
	}

	std::vector<long long> add_last_zeros(const std::vector<long long>& x, const int n)
	{
		if (x.size() + n <= 0) { return ndef_int; }
		std::vector<long long> temp(x.size() + n, 0);
		for (int i = 0; i < x.size(); i++)
		{
			temp[i] = x[i];
		}
		return temp;
	}
	int max(const int a, const int b)
	{
		if (a > b) { return a; }
		return b;
	}
	int min(const int a, const int b)
	{
		if (a > b) { return b; }
		return a;
	}
	std::vector<long long> _int_plus(const std::vector<long long>& x, const std::vector<long long>& y)
	{
		// err-> return empty array of long long.
		if (x.empty() || y.empty()) { return ndef_int; }
		std::vector<long long> _x = remove_first_zeros(x);
		std::vector<long long> _y = remove_first_zeros(y);
		if (_x.empty()) { _x = zero_int; }
		if (_y.empty()) { _y = zero_int; }

		const int _max = wiz::max(_x.size(), _y.size());
		const int _min = wiz::min(_x.size(), _y.size());
		std::vector<long long> temp(_max + 1, 0);
		long long itemp = 0;
		int w = _x.size() - 1;
		int v = _y.size() - 1;
		int u = temp.size() - 1;


		for (int num = 0; num < _min; num++)
		{
			long long sum = (_x[w]) + (_y[v]) + itemp;
			temp[u] = (sum % BIGIINT_BASE);
			itemp = sum / BIGIINT_BASE;
			w--;
			v--;
			u--;
		}
		for (; w >= 0; w--)
		{
			long long sum = (_x[w]) + itemp;
			temp[u] = (sum % BIGIINT_BASE);
			itemp = sum / BIGIINT_BASE;
			u--;
		}
		for (; v >= 0; v--)
		{
			long long sum = (_y[v]) + itemp;
			temp[u] = (sum % BIGIINT_BASE);
			itemp = sum / BIGIINT_BASE;
			u--;
		}
		temp[0] = (itemp);

		std::vector<long long> ret = remove_first_zeros(temp);
		if (ret.empty()) { return wiz::zero_int; }
		return ret;
	}
	std::vector<long long> _int_minus(const std::vector<long long>& x, const std::vector<long long>& y) // x >= y
	{
		if (x.empty() || y.empty()) { return ndef_int; }
		std::vector<long long> _x = remove_first_zeros(x);
		std::vector<long long> _y = remove_first_zeros(y);
		if (_x.empty()) { _x = zero_int; }
		if (_y.empty()) { _y = zero_int; }

		if (_x == _y) { return wiz::zero_int; }
		if (_x < _y) { throw wiz::Error(__FILE__, __LINE__, " in int_minus, must be x >= y, but now x < y. "); }


		std::vector<long long> temp(_x.size(), 0);
		const int min = _y.size();
		int w = _x.size() - 1;
		int v = _y.size() - 1;
		int u = temp.size() - 1;
		long long itemp = 0;

		for (int num = 0; num < min; num++)
		{
			long long dif = (_x[w]) - (_y[v]);
			if (dif < 0) /// chk!!
			{
				dif = dif + BIGIINT_BASE;
				long long count = w - 1;
				while (_x[count] == 0) {
					_x[count] = (BIGIINT_BASE-1);
					count--;
				}
				_x[count]--;
			}
			temp[u] = (dif % BIGIINT_BASE);

			w--;
			v--;
			u--;
		}
		//
		for (; w >= 0; w--)
		{
			long long dif = (_x[w]);
			temp[u] = (dif % BIGIINT_BASE);
			u--;
		}

		std::vector<long long> ret = remove_first_zeros(temp);
		if (ret.empty()) { return wiz::zero_int; }
		return ret;
	}
	std::vector<long long> _int_multiple(const std::vector<long long>& x, const long long ch)
	{
		if (x.empty()) { return ndef_int; }
		std::vector<long long> _x = remove_first_zeros(x);
		if (_x.empty()) { _x = zero_int; }

		std::vector<long long> temp(_x.size() + 1, 0);
		long long itemp = 0;

		for (int i = temp.size() - 1; i >= 1; i--)
		{
			long long sum = (ch) * (_x[i - 1]) + itemp;
			temp[i] = (sum % BIGIINT_BASE);
			itemp = sum / BIGIINT_BASE;
		}
		temp[0] = (itemp);
		std::vector<long long> ret = remove_first_zeros(temp);
		if (ret.empty()) { return wiz::zero_int; }
		return ret;
	}
	std::vector<long long> _int_multiple(const std::vector<long long>& x, const std::vector<long long>& y)
	{
		if (x.empty() || y.empty()) { return ndef_int; }
		std::vector<long long> _x = remove_first_zeros(x);
		std::vector<long long> _y = remove_first_zeros(y);
		if (_x.empty()) { _x = zero_int; }
		if (_y.empty()) { _y = zero_int; }

		std::vector<long long> sum = zero_int;

		long long w = 0;
		for (int i = _y.size() - 1; i >= 0; i--) {
			std::vector<long long> temp = add_last_zeros(_int_multiple(_x, _y[i]), w);
			if (temp.empty()) {
				temp = wiz::zero_int;
			}
			std::vector<long long> temp2 = _int_plus(sum, temp);
			sum.clear();
			sum = temp2;
			w++;
		}

		std::vector<long long> ret = remove_first_zeros(sum);
		if (ret.empty()) { return wiz::zero_int; }
		return ret;
	}
	std::vector<long long> _int_sub(const std::vector<long long>& x, const int start, const int end)
	{
		// chk start <= end!
		std::vector<long long> temp(end - start + 1);
		for (int i = 0; i < temp.size(); i++)
		{
			temp[i] = x[i + start];
		}

		return temp;
	}

	std::vector<long long> _int_concat(const std::vector<long long>& x, const std::vector<long long>& y)
	{
		if (x.empty() && y.empty()) { return ndef_int; }
		std::vector<long long> temp(x.size() + y.size());
		int count = 0;
		for (int i = 0; i < x.size(); i++)
		{
			temp[count] = x[i];
			count++;
		}
		for (int i = 0; i < y.size(); i++)
		{
			temp[count] = y[i];
			count++;
		}

		return temp;
	}

	/// chk this...
	bool _int_divide(const std::vector<long long>& x, const std::vector<long long>& y,
		std::vector<long long>& quotient, // ¸ò
		std::vector<long long>& remainder) // ³ª¸ÓÁö
	{
		if (x.empty() || y.empty()) { return false; } /// chk???
		std::vector<long long> _x = remove_first_zeros(x);
		const std::vector<long long> _y = remove_first_zeros(y);

		if (_y.empty()) { throw wiz::Error(__FILE__, __LINE__, "_int_divide, x/0 error"); }
		if (_x.empty()) { _x = zero_int; }
		if (_x < _y) {
			quotient.clear(); quotient = wiz::zero_int;
			remainder.clear();
			remainder = _x;
			return true;
		}

		//
		vector<long long> vec_quo;
		int k = 0;
		int m = 0;
		std::vector<long long> itemp;
		std::vector<long long> val;

		while (true) {
			if (m >= _x.size()) { break; }
			const std::vector<long long> temp_concat = _int_concat(itemp, _int_sub(_x, m, k));
			if (temp_concat < _y)
			{
				vec_quo.push_back((0));
				//cout << "chk1" << endl;
				k++;
				if (IsSameValues(zero_int, temp_concat))
				{
					// cout << "chk.." << endl;
					m++; k = m;
					itemp.clear();
				}
				else if (k == _x.size()) {
					itemp.clear();
					itemp = temp_concat; // remove_first_zeros( temp_concat );
										 /// chk 2014.01.07
					break;
				}
			}
			else
			{
				for (long long j = 1; j <= (BIGIINT_BASE-1); j++) {
					val.clear();
					val = _int_minus(temp_concat, _int_multiple(_y, (j)));

					if (val < _y) {
						// cout << "chk2 " << j << endl;
						vec_quo.push_back((j));//
						itemp.clear();
						itemp = remove_first_zeros(val);
						break;
					}
				}
				m = k + 1;
				k = m;
			}
		}

		// return
		quotient.clear(); quotient = remove_first_zeros(vec_quo);
		if (quotient.empty()) { quotient = zero_int; }
		remainder.clear();
		if (itemp.empty()) { remainder = zero_int; }
		else remainder = itemp;
		return true;
	}

	class BigInt /// class : long Int...
	{
	public:
		std::vector<long long> val; /// absolute value!
		bool sign; /// +(true), -(false)
	public:
		explicit BigInt() : sign( true )
		{
		}

		explicit BigInt(const std::vector<long long>& val, const bool& sign)
			: val(val), sign(sign)
		{
		}
		BigInt& operator=(const BigInt& longInt)
		{
			BigInt temp = longInt;
			val.clear();
			val = temp.val;
			sign = temp.sign;

			return *this;
		}
	public:
		//  <
		// ==
		friend bool operator<(const BigInt& num1, const BigInt& num2)
		{
			return (num1 - num2).sign == false;
		}
		friend bool operator==(const BigInt& num1, const BigInt& num2)
		{
			return IsSameValues((num1 - num2).val, zero_int);
		}
		friend bool operator<=(const BigInt& num1, const BigInt& num2)
		{
			return num1 < num2 || num1 == num2;
		}

		friend BigInt operator+(const BigInt& num1, const BigInt& num2)
		{
			if (num1.val.empty() || num2.val.empty())
			{
				throw wiz::Error(__FILE__, __LINE__, "empty problem, in + ");
			}
			BigInt number;

			if (num1.sign == num2.sign) {
				number.val = _int_plus(num1.val, num2.val);
				number.sign = num1.sign;
				if (IsSameValues(zero_int, number.val)) { number.sign = true; }// think only +0.
			}
			else if (num1.sign && !num2.sign) {
				if (num1.val < num2.val)
				{
					number.val = _int_minus(num2.val, num1.val);
					number.sign = false; // minus
				}
				else if (IsSameValues(num1.val, num2.val))
				{
					number.val = std::vector<long long>(1, 0);
					number.sign = true; // +0 = 0 = -0 ??
				}
				else
				{
					number.val = _int_minus(num1.val, num2.val);
					number.sign = true;
				}
			}
			else if (!num1.sign && num2.sign) {
				if (num1.val < num2.val)
				{
					number.val = _int_minus(num2.val, num1.val);
					number.sign = true; // minus
				}
				else if (IsSameValues(num1.val, num2.val))
				{
					number.val = std::vector<long long>(1,(0));
					number.sign = true; // +0 = 0 = -0 ??
				}
				else
				{
					number.val = _int_minus(num1.val, num2.val);
					number.sign = false;
				}
			}
			return number;
		}
		friend BigInt operator-(const BigInt& num1, const BigInt& num2)
		{
			if (num1.val.empty() || num2.val.empty())
			{
				throw wiz::Error(__FILE__, __LINE__, "empty problem, in - ");
			}
			BigInt number = num2;
			number.sign = !number.sign;

			return num1 + number;
		}
		friend BigInt operator*(const BigInt& num1, const BigInt& num2)
		{
			if (num1.val.empty() || num2.val.empty())
			{
				throw wiz::Error(__FILE__, __LINE__, "empty problem, in * ");
			}
			BigInt temp;
			temp.val = _int_multiple(num1.val, num2.val);
			temp.sign = (num1.sign == num2.sign);

			return temp;
		}
		friend BigInt operator/(const BigInt& num1, const BigInt& num2)
		{
			if (num1.val.empty() || num2.val.empty())
			{
				throw wiz::Error(__FILE__, __LINE__, "empty problem, in / ");
			}
			BigInt temp;
			std::vector<long long> quotient;
			std::vector<long long> remainder;

			_int_divide(num1.val, num2.val, quotient, remainder);

			temp.val = quotient;
			temp.sign = (num1.sign == num2.sign); /// chk...

			return temp;
		}
		friend BigInt operator%(const BigInt& num1, const BigInt& num2)
		{
			if (num1.val.empty() || num2.val.empty())
			{
				throw wiz::Error(__FILE__, __LINE__, "empty problem, in % ");
			}
			if (!num1.sign || !num2.sign) /// chk...
			{
				throw wiz::Error(__FILE__, __LINE__, "BigInt%, sign is minus");
			}

			BigInt temp;
			std::vector<long long> quotient;
			std::vector<long long> remainder;

			_int_divide(num1.val, num2.val, quotient, remainder);

			temp.val = remainder;
			temp.sign = true;


			return temp;
		}

	};

}

using namespace wiz;

#include <iostream>
#include <ctime>

int main(void)
{
	int a = clock();
	BigInt x, y;
	x = BigInt(std::vector<long long>{ 1 }, true);
	y = BigInt(std::vector<long long>{ 1 }, true);
	BigInt Max(std::vector<long long>{ 222222222, 99999 }, true);
	//
	//for (; x <= Max; x = x + BigInt(std::vector<long long>{1}, true))
	{
	//	y = y * x;
	}	
	int b = clock();
	y = Max / BigInt(std::vector<long long>{ 123456 }, true);
	for( auto& val : y.val ) 
		std::cout << val << std::endl;
	std::cout << b - a << "ms" << std::endl;
	return 0;
}
