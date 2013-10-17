/**
 *  @file      range.h
 *  @brief     Packaging range into a class.
 *  @author    Darren Liu (MSR.B, msr-b)
 *  @date      2013/10/12
 *  @copyright Copyright (c) 2013 Darren Liu. All rights reserved.
 */

#ifndef _RANGE_H_
#define _RANGE_H_

/// @brief A range.
template <typename _Ty>
class Range {
public:
	/// @brief constructor of range, don't care about the magnitude relation
	Range(const _Ty& a, const _Ty& b) {
		this -> lower = (a < b)? a : b;
		this -> upper = (a > b)? a : b;
	}
	/**
	 *  @brief  find whether a element in this range
	 *  @param  x     element
	 *  @return in or not
	 *  @retval true  in
	 *  @retval false not in
	 */
	bool in(const _Ty& x) const {
		return lower <= x && x <= upper;
	}
	/**
	 *  @brief  get lower limit
	 *  @return lower limit
	 */
	_Ty getLower() const {
		return lower;
	}
	/**
	 *  @brief  get upper limit
	 *  @return upper limit
	 */
	_Ty getUpper() const {
		return upper;
	}
private:
	/// @name limit
	/// @{
	/// @brief lower limit
	_Ty lower;
	/// @brief upper limit
	_Ty upper;
	/// @}
};
#endif