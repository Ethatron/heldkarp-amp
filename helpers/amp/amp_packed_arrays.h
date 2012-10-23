/***
* ==++==
*
* Copyright (c) Microsoft Corporation.  All rights reserved.
*
* ==--==
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* amp_packed_arrays.h
*
* C++ AMP Packed Array Types
*
* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/


// !!! DO NOT HAND EDIT !!!
// This file was generated.

#pragma once

#pragma warning(push)
#pragma warning(disable : 4100)
#include <amp.h>
#include <amprt.h>
#define _AMP_SHORT_ARRAYS_H
namespace Concurrency
{
namespace graphics
{
// Forward Declarations
class ushort2;
class ushort4;
class short2;
class short4;

class value_frag
{
public:
    typedef unsigned int value_type;
private:
    const int _M_ofs;
    value_type _M_ptr;
public:
    value_frag(const int ofs, value_type ptr) __GPU : _M_ofs(ofs), _M_ptr(ptr) {}
};

/// <summary>
///    Represent a packed vector of 2 unsigned shorts.
/// </summary>
class ushort2
{
public:
    typedef unsigned int value_type;
    static const int size = 1;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Uint_type;
private:
    value_type _M_xy[1];

public:
    value_frag operator [] (int _Component) __GPU
    {
	return value_frag(_Component, _M_xy[0]);
    }

    const value_frag operator [] (int _Component) const __GPU
    {
	return value_frag(_Component, _M_xy[0]);
    }

    __declspec( property( get = get_x, put = set_x) ) unsigned int x;
    __declspec( property( get = get_x, put = set_x) ) unsigned int r;

    unsigned int get_x() const __GPU {
        return _M_xy[0] & 0x0000FFFF;
    }

    void set_x(unsigned int _Value) __GPU
    {
        _M_xy[0] = (_M_xy[0] & 0xFFFF0000) + (_Value & 0x0000FFFF);
    }

    __declspec( property( get = get_y, put = set_y) ) unsigned int y;
    __declspec( property( get = get_y, put = set_y) ) unsigned int g;

    unsigned int get_y() const __GPU {
        return _M_xy[0] >> 16;
    }

    void set_y(unsigned int _Value) __GPU
    {
        _M_xy[0] = (_M_xy[0] & 0x0000FFFF) + (_Value << 16);
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    ushort2() __GPU
    {
        _M_xy[0] = 0;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V0">
    ///     The value to initialize element 0.
    /// </param>
    /// <param name="_V1">
    ///     The value to initialize element 1.
    /// </param>
    ushort2(unsigned int _V0, unsigned int _V1) __GPU
    {
        _M_xy[0] = (_V1 << 16) + (_V0 & 0x0000FFFF);
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    ushort2(unsigned int _V) __GPU
    {
        _M_xy[0] = (_V << 16) + (_V & 0x0000FFFF);
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort2(const short2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort2(const int2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort2(const uint2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort2(const float2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort2(const unorm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort2(const norm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort2(const double2& _Other) __GPU;

    ushort2 operator~() const __GPU
    {
        ushort2 _Value = *this;
        _Value._M_xy[0] = ~_Value._M_xy[0];
        return _Value;
    }

    ushort2& operator++() __GPU
    {
        uint2 _Value;
        _Value.x = get_x() + 1;
        _Value.y = get_y() + 1;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2 operator++(int) __GPU
    {
        ushort2 _Result = *this;
        ++(*this);
        return _Result;
    }

    ushort2& operator--() __GPU
    {
        uint2 _Value;
        _Value.x = get_x() - 1;
        _Value.y = get_y() - 1;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2 operator--(int) __GPU
    {
        ushort2 _Result = *this;
        --(*this);
        return _Result;
    }

    ushort2& operator+=(const ushort2& _Other) __GPU
    {
        uint2 _Value;
        _Value.x = get_x() + _Other.x;
        _Value.y = get_y() + _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2& operator-=(const ushort2& _Other) __GPU
    {
        uint2 _Value;
        _Value.x = get_x() - _Other.x;
        _Value.y = get_y() - _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2& operator*=(const ushort2& _Other) __GPU
    {
        uint2 _Value;
        _Value.x = get_x() * _Other.x;
        _Value.y = get_y() * _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2& operator/=(const ushort2& _Other) __GPU
    {
        uint2 _Value;
        _Value.x = get_x() / _Other.x;
        _Value.y = get_y() / _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2& operator%=(const ushort2& _Other) __GPU
    {
        uint2 _Value;
        _Value.x = get_x() % _Other.x;
        _Value.y = get_y() % _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2& operator^=(const ushort2& _Other) __GPU
    {
        ushort2 _Value1 = *this;
        ushort2 _Value2 = _Other;
        _Value1._M_xy[0] ^= _Value2._M_xy[0];
        *this = _Value1;
        return *this;
    }

    ushort2& operator|=(const ushort2& _Other) __GPU
    {
        ushort2 _Value1 = *this;
        ushort2 _Value2 = _Other;
        _Value1._M_xy[0] |= _Value2._M_xy[0];
        *this = _Value1;
        return *this;
    }

    ushort2& operator&=(const ushort2& _Other) __GPU
    {
        ushort2 _Value1 = *this;
        ushort2 _Value2 = _Other;
        _Value1._M_xy[0] &= _Value2._M_xy[0];
        *this = _Value1;
        return *this;
    }

    ushort2& operator>>=(const ushort2& _Other) __GPU
    {
        uint2 _Value;
        _Value.x = get_x() >> _Other.x;
        _Value.y = get_y() >> _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    ushort2& operator<<=(const ushort2& _Other) __GPU
    {
        uint2 _Value;
        _Value.x = get_x() << _Other.x;
        _Value.y = get_y() << _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) ushort2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) ushort2 rg;

    ushort2 get_xy() const __GPU {
        return ushort2(get_x(), get_y());
    }

    void set_xy(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
    }

    __declspec( property( get = get_yx, put = set_yx) ) ushort2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) ushort2 gr;

    ushort2 get_yx() const __GPU {
        return ushort2(get_y(), get_x());
    }

    void set_yx(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
    }

};

/// <summary>
///    Represent a packed vector of 4 unsigned shorts.
/// </summary>
class ushort4
{
public:
    typedef unsigned int value_type;
    static const int size = 4;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Uint_type;
private:
    value_type _M_xyzw[4];

public:
    value_frag operator [] (int _Component) __GPU
    {
	return value_frag(_Component & 1, _M_xyzw[_Component >> 1]);
    }

    const value_frag operator [] (int _Component) const __GPU
    {
	return value_frag(_Component & 1, _M_xyzw[_Component >> 1]);
    }

    __declspec( property( get = get_x, put = set_x) ) unsigned int x;
    __declspec( property( get = get_x, put = set_x) ) unsigned int r;

    unsigned int get_x() const __GPU {
        return _M_xyzw[0] & 0x0000FFFF;
    }

    void set_x(unsigned int _Value) __GPU
    {
        _M_xyzw[0] = (_M_xyzw[0] & 0xFFFF0000) + (_Value & 0x0000FFFF);
    }

    __declspec( property( get = get_y, put = set_y) ) unsigned int y;
    __declspec( property( get = get_y, put = set_y) ) unsigned int g;

    unsigned int get_y() const __GPU {
        return _M_xyzw[0] >> 16;
    }

    void set_y(unsigned int _Value) __GPU
    {
        _M_xyzw[0] = (_M_xyzw[0] & 0x0000FFFF) + (_Value << 16);
    }

    __declspec( property( get = get_z, put = set_z) ) unsigned int z;
    __declspec( property( get = get_z, put = set_z) ) unsigned int b;

    unsigned int get_z() const __GPU {
        return _M_xyzw[1] & 0x0000FFFF;
    }

    void set_z(unsigned int _Value) __GPU
    {
        _M_xyzw[1] = (_M_xyzw[1] & 0xFFFF0000) + (_Value & 0x0000FFFF);
    }

    __declspec( property( get = get_w, put = set_w) ) unsigned int w;
    __declspec( property( get = get_w, put = set_w) ) unsigned int a;

    unsigned int get_w() const __GPU {
        return _M_xyzw[1] >> 16;
    }

    void set_w(unsigned int _Value) __GPU
    {
        _M_xyzw[1] = (_M_xyzw[1] & 0x0000FFFF) + (_Value << 16);
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    ushort4() __GPU
    {
        _M_xyzw[0] = 0;
        _M_xyzw[1] = 0;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V0">
    ///     The value to initialize element 0.
    /// </param>
    /// <param name="_V1">
    ///     The value to initialize element 1.
    /// </param>
    /// <param name="_V2">
    ///     The value to initialize element 2.
    /// </param>
    /// <param name="_V3">
    ///     The value to initialize element 3.
    /// </param>
    ushort4(unsigned int _V0, unsigned int _V1, unsigned int _V2, unsigned int _V3) __GPU
    {
        _M_xyzw[0] = (_V1 << 16) + (_V0 & 0x0000FFFF);
        _M_xyzw[1] = (_V3 << 16) + (_V2 & 0x0000FFFF);
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    ushort4(unsigned int _V) __GPU
    {
        _M_xyzw[0] = (_V << 16) + (_V & 0x0000FFFF);
        _M_xyzw[1] = (_V << 16) + (_V & 0x0000FFFF);
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort4(const short4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort4(const int4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort4(const uint4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort4(const float4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort4(const unorm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort4(const norm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline ushort4(const double4& _Other) __GPU;

    ushort4 operator~() const __GPU
    {
        ushort4 _Value = *this;
        _Value._M_xyzw[0] = ~_Value._M_xyzw[0];
        _Value._M_xyzw[1] = ~_Value._M_xyzw[1];
        return _Value;
    }

    ushort4& operator++() __GPU
    {
        uint4 _Value;
        _Value.x = get_x() + 1;
        _Value.y = get_y() + 1;
        _Value.z = get_z() + 1;
        _Value.w = get_w() + 1;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4 operator++(int) __GPU
    {
        ushort4 _Result = *this;
        ++(*this);
        return _Result;
    }

    ushort4& operator--() __GPU
    {
        uint4 _Value;
        _Value.x = get_x() - 1;
        _Value.y = get_y() - 1;
        _Value.z = get_z() - 1;
        _Value.w = get_w() - 1;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4 operator--(int) __GPU
    {
        ushort4 _Result = *this;
        --(*this);
        return _Result;
    }

    ushort4& operator+=(const ushort4& _Other) __GPU
    {
        uint4 _Value;
        _Value.x = get_x() + _Other.x;
        _Value.y = get_y() + _Other.y;
        _Value.z = get_z() + _Other.z;
        _Value.w = get_w() + _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4& operator-=(const ushort4& _Other) __GPU
    {
        uint4 _Value;
        _Value.x = get_x() - _Other.x;
        _Value.y = get_y() - _Other.y;
        _Value.z = get_z() - _Other.z;
        _Value.w = get_w() - _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4& operator*=(const ushort4& _Other) __GPU
    {
        uint4 _Value;
        _Value.x = get_x() * _Other.x;
        _Value.y = get_y() * _Other.y;
        _Value.z = get_z() * _Other.z;
        _Value.w = get_w() * _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4& operator/=(const ushort4& _Other) __GPU
    {
        uint4 _Value;
        _Value.x = get_x() / _Other.x;
        _Value.y = get_y() / _Other.y;
        _Value.z = get_z() / _Other.z;
        _Value.w = get_w() / _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4& operator%=(const ushort4& _Other) __GPU
    {
        uint4 _Value;
        _Value.x = get_x() % _Other.x;
        _Value.y = get_y() % _Other.y;
        _Value.z = get_z() % _Other.z;
        _Value.w = get_w() % _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4& operator^=(const ushort4& _Other) __GPU
    {
        ushort4 _Value1 = *this;
        ushort4 _Value2 = _Other;
        _Value1._M_xyzw[0] ^= _Value2._M_xyzw[0];
        _Value1._M_xyzw[1] ^= _Value2._M_xyzw[1];
        *this = _Value1;
        return *this;
    }

    ushort4& operator|=(const ushort4& _Other) __GPU
    {
        ushort4 _Value1 = *this;
        ushort4 _Value2 = _Other;
        _Value1._M_xyzw[0] |= _Value2._M_xyzw[0];
        _Value1._M_xyzw[1] |= _Value2._M_xyzw[1];
        *this = _Value1;
        return *this;
    }

    ushort4& operator&=(const ushort4& _Other) __GPU
    {
        ushort4 _Value1 = *this;
        ushort4 _Value2 = _Other;
        _Value1._M_xyzw[0] &= _Value2._M_xyzw[0];
        _Value1._M_xyzw[1] &= _Value2._M_xyzw[1];
        *this = _Value1;
        return *this;
    }

    ushort4& operator>>=(const ushort4& _Other) __GPU
    {
        uint4 _Value;
        _Value.x = get_x() >> _Other.x;
        _Value.y = get_y() >> _Other.y;
        _Value.z = get_z() >> _Other.z;
        _Value.w = get_w() >> _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    ushort4& operator<<=(const ushort4& _Other) __GPU
    {
        uint4 _Value;
        _Value.x = get_x() << _Other.x;
        _Value.y = get_y() << _Other.y;
        _Value.z = get_z() << _Other.z;
        _Value.w = get_w() << _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) ushort2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) ushort2 rg;

    ushort2 get_xy() const __GPU {
        return ushort2(get_x(), get_y());
    }

    void set_xy(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
    }

    __declspec( property( get = get_xz, put = set_xz) ) ushort2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) ushort2 rb;

    ushort2 get_xz() const __GPU {
        return ushort2(get_x(), get_z());
    }

    void set_xz(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
    }

    __declspec( property( get = get_xw, put = set_xw) ) ushort2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) ushort2 ra;

    ushort2 get_xw() const __GPU {
        return ushort2(get_x(), get_w());
    }

    void set_xw(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
    }

    __declspec( property( get = get_yx, put = set_yx) ) ushort2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) ushort2 gr;

    ushort2 get_yx() const __GPU {
        return ushort2(get_y(), get_x());
    }

    void set_yx(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
    }

    __declspec( property( get = get_yz, put = set_yz) ) ushort2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) ushort2 gb;

    ushort2 get_yz() const __GPU {
        return ushort2(get_y(), get_z());
    }

    void set_yz(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
    }

    __declspec( property( get = get_yw, put = set_yw) ) ushort2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) ushort2 ga;

    ushort2 get_yw() const __GPU {
        return ushort2(get_y(), get_w());
    }

    void set_yw(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
    }

    __declspec( property( get = get_zx, put = set_zx) ) ushort2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) ushort2 br;

    ushort2 get_zx() const __GPU {
        return ushort2(get_z(), get_x());
    }

    void set_zx(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
    }

    __declspec( property( get = get_zy, put = set_zy) ) ushort2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) ushort2 bg;

    ushort2 get_zy() const __GPU {
        return ushort2(get_z(), get_y());
    }

    void set_zy(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
    }

    __declspec( property( get = get_zw, put = set_zw) ) ushort2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) ushort2 ba;

    ushort2 get_zw() const __GPU {
        return ushort2(get_z(), get_w());
    }

    void set_zw(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
    }

    __declspec( property( get = get_wx, put = set_wx) ) ushort2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) ushort2 ar;

    ushort2 get_wx() const __GPU {
        return ushort2(get_w(), get_x());
    }

    void set_wx(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
    }

    __declspec( property( get = get_wy, put = set_wy) ) ushort2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) ushort2 ag;

    ushort2 get_wy() const __GPU {
        return ushort2(get_w(), get_y());
    }

    void set_wy(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
    }

    __declspec( property( get = get_wz, put = set_wz) ) ushort2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) ushort2 ab;

    ushort2 get_wz() const __GPU {
        return ushort2(get_w(), get_z());
    }

    void set_wz(const ushort2& _Value) __GPU
    {
        ushort2 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) uint3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) uint3 rgb;

    uint3 get_xyz() const __GPU {
        return uint3(get_x(), get_y(), get_z());
    }

    void set_xyz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) uint3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) uint3 rga;

    uint3 get_xyw() const __GPU {
        return uint3(get_x(), get_y(), get_w());
    }

    void set_xyw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) uint3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) uint3 rbg;

    uint3 get_xzy() const __GPU {
        return uint3(get_x(), get_z(), get_y());
    }

    void set_xzy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) uint3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) uint3 rba;

    uint3 get_xzw() const __GPU {
        return uint3(get_x(), get_z(), get_w());
    }

    void set_xzw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) uint3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) uint3 rag;

    uint3 get_xwy() const __GPU {
        return uint3(get_x(), get_w(), get_y());
    }

    void set_xwy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) uint3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) uint3 rab;

    uint3 get_xwz() const __GPU {
        return uint3(get_x(), _M_xyzw[3], get_z());
    }

    void set_xwz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) uint3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) uint3 grb;

    uint3 get_yxz() const __GPU {
        return uint3(get_y(), get_x(), get_z());
    }

    void set_yxz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) uint3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) uint3 gra;

    uint3 get_yxw() const __GPU {
        return uint3(get_y(), get_x(), get_w());
    }

    void set_yxw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) uint3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) uint3 gbr;

    uint3 get_yzx() const __GPU {
        return uint3(get_y(), get_z(), get_x());
    }

    void set_yzx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) uint3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) uint3 gba;

    uint3 get_yzw() const __GPU {
        return uint3(get_y(), get_z(), get_w());
    }

    void set_yzw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) uint3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) uint3 gar;

    uint3 get_ywx() const __GPU {
        return uint3(get_y(), get_w(), get_x());
    }

    void set_ywx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) uint3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) uint3 gab;

    uint3 get_ywz() const __GPU {
        return uint3(get_y(), get_w(), get_z());
    }

    void set_ywz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) uint3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) uint3 brg;

    uint3 get_zxy() const __GPU {
        return uint3(get_z(), get_x(), get_y());
    }

    void set_zxy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) uint3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) uint3 bra;

    uint3 get_zxw() const __GPU {
        return uint3(get_z(), get_x(), get_w());
    }

    void set_zxw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) uint3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) uint3 bgr;

    uint3 get_zyx() const __GPU {
        return uint3(get_z(), get_y(), get_x());
    }

    void set_zyx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) uint3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) uint3 bga;

    uint3 get_zyw() const __GPU {
        return uint3(get_z(), get_y(), get_w());
    }

    void set_zyw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) uint3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) uint3 bar;

    uint3 get_zwx() const __GPU {
        return uint3(get_z(), get_w(), get_x());
    }

    void set_zwx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) uint3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) uint3 bag;

    uint3 get_zwy() const __GPU {
        return uint3(get_z(), get_w(), get_y());
    }

    void set_zwy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) uint3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) uint3 arg;

    uint3 get_wxy() const __GPU {
        return uint3(get_w(), get_x(), get_y());
    }

    void set_wxy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) uint3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) uint3 arb;

    uint3 get_wxz() const __GPU {
        return uint3(get_w(), get_x(), get_z());
    }

    void set_wxz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) uint3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) uint3 agr;

    uint3 get_wyx() const __GPU {
        return uint3(get_w(), get_y(), get_x());
    }

    void set_wyx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) uint3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) uint3 agb;

    uint3 get_wyz() const __GPU {
        return uint3(get_w(), get_y(), get_z());
    }

    void set_wyz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) uint3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) uint3 abr;

    uint3 get_wzx() const __GPU {
        return uint3(get_w(), get_z(), get_x());
    }

    void set_wzx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) uint3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) uint3 abg;

    uint3 get_wzy() const __GPU {
        return uint3(get_w(), get_z(), get_y());
    }

    void set_wzy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) ushort4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) ushort4 rgba;

    ushort4 get_xyzw() const __GPU {
        return ushort4(get_x(), get_y(), get_z(), get_w());
    }

    void set_xyzw(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) ushort4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) ushort4 rgab;

    ushort4 get_xywz() const __GPU {
        return ushort4(get_x(), get_y(), get_w(), get_z());
    }

    void set_xywz(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) ushort4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) ushort4 rbga;

    ushort4 get_xzyw() const __GPU {
        return ushort4(get_x(), get_z(), get_y(), get_w());
    }

    void set_xzyw(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) ushort4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) ushort4 rbag;

    ushort4 get_xzwy() const __GPU {
        return ushort4(get_x(), get_z(), get_w(), get_y());
    }

    void set_xzwy(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) ushort4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) ushort4 ragb;

    ushort4 get_xwyz() const __GPU {
        return ushort4(get_x(), get_w(), get_y(), get_z());
    }

    void set_xwyz(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) ushort4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) ushort4 rabg;

    ushort4 get_xwzy() const __GPU {
        return ushort4(get_x(), get_w(), get_z(), get_y());
    }

    void set_xwzy(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) ushort4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) ushort4 grba;

    ushort4 get_yxzw() const __GPU {
        return ushort4(get_y(), get_x(), get_z(), get_w());
    }

    void set_yxzw(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) ushort4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) ushort4 grab;

    ushort4 get_yxwz() const __GPU {
        return ushort4(get_y(), get_x(), get_w(), get_z());
    }

    void set_yxwz(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) ushort4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) ushort4 gbra;

    ushort4 get_yzxw() const __GPU {
        return ushort4(get_y(), get_z(), get_x(), get_w());
    }

    void set_yzxw(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) ushort4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) ushort4 gbar;

    ushort4 get_yzwx() const __GPU {
        return ushort4(get_y(), get_z(), get_w(), get_x());
    }

    void set_yzwx(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) ushort4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) ushort4 garb;

    ushort4 get_ywxz() const __GPU {
        return ushort4(get_y(), get_w(), get_x(), get_z());
    }

    void set_ywxz(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) ushort4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) ushort4 gabr;

    ushort4 get_ywzx() const __GPU {
        return ushort4(get_y(), get_w(), get_z(), get_x());
    }

    void set_ywzx(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) ushort4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) ushort4 brga;

    ushort4 get_zxyw() const __GPU {
        return ushort4(get_z(), get_x(), get_y(), get_w());
    }

    void set_zxyw(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) ushort4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) ushort4 brag;

    ushort4 get_zxwy() const __GPU {
        return ushort4(get_z(), get_x(), get_w(), get_y());
    }

    void set_zxwy(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) ushort4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) ushort4 bgra;

    ushort4 get_zyxw() const __GPU {
        return ushort4(get_z(), get_y(), get_x(), get_w());
    }

    void set_zyxw(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) ushort4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) ushort4 bgar;

    ushort4 get_zywx() const __GPU {
        return ushort4(get_z(), get_y(), get_w(), get_x());
    }

    void set_zywx(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) ushort4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) ushort4 barg;

    ushort4 get_zwxy() const __GPU {
        return ushort4(get_z(), get_w(), get_x(), get_y());
    }

    void set_zwxy(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) ushort4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) ushort4 bagr;

    ushort4 get_zwyx() const __GPU {
        return ushort4(get_z(), get_w(), get_y(), get_x());
    }

    void set_zwyx(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) ushort4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) ushort4 argb;

    ushort4 get_wxyz() const __GPU {
        return ushort4(get_w(), get_x(), get_y(), get_z());
    }

    void set_wxyz(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) ushort4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) ushort4 arbg;

    ushort4 get_wxzy() const __GPU {
        return ushort4(get_w(), get_x(), get_z(), get_y());
    }

    void set_wxzy(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) ushort4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) ushort4 agrb;

    ushort4 get_wyxz() const __GPU {
        return ushort4(get_w(), get_y(), get_x(), get_z());
    }

    void set_wyxz(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) ushort4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) ushort4 agbr;

    ushort4 get_wyzx() const __GPU {
        return ushort4(get_w(), get_y(), get_z(), get_x());
    }

    void set_wyzx(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) ushort4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) ushort4 abrg;

    ushort4 get_wzxy() const __GPU {
        return ushort4(get_w(), get_z(), get_x(), get_y());
    }

    void set_wzxy(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) ushort4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) ushort4 abgr;

    ushort4 get_wzyx() const __GPU {
        return ushort4(get_w(), get_z(), get_y(), get_x());
    }

    void set_wzyx(const ushort4& _Value) __GPU
    {
        ushort4 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
        set_x(_Val.w);
    }

};

/// <summary>
///    Represent a packed vector of 2 int's.
/// </summary>
class short2
{
public:
    typedef int value_type;
    static const int size = 2;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Int_type;
private:
    value_type _M_xy[2];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xy[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xy[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) int x;
    __declspec( property( get = get_x, put = set_x) ) int r;

    int get_x() const __GPU {
        return _M_xy[0];
    }

    void set_x(int _Value) __GPU
    {
        _M_xy[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) int y;
    __declspec( property( get = get_y, put = set_y) ) int g;

    int get_y() const __GPU {
        return _M_xy[1];
    }

    void set_y(int _Value) __GPU
    {
        _M_xy[1] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    short2() __GPU
    {
        _M_xy[0] = 0;
        _M_xy[1] = 0;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V0">
    ///     The value to initialize element 0.
    /// </param>
    /// <param name="_V1">
    ///     The value to initialize element 1.
    /// </param>
    short2(int _V0, int _V1) __GPU
    {
        _M_xy[0] = _V0;
        _M_xy[1] = _V1;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    short2(int _V) __GPU
    {
        _M_xy[0] = _V;
        _M_xy[1] = _V;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short2(const ushort2& _Other) __GPU;
    
    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short2(const int2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short2(const uint2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short2(const float2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short2(const unorm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short2(const norm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short2(const double2& _Other) __GPU;

    short2 operator~() const __GPU
    {
        short2 _Value = *this;
        _Value._M_xy[0] = ~_Value._M_xy[0];
        return _Value;
    }

    short2 operator-() const __GPU
    {
        int2 _Value;
        _Value.x = -get_x();
        _Value.y = -get_y();
        return short2(_Value.x, _Value.y);
    }

    short2& operator++() __GPU
    {
        int2 _Value;
        _Value.x = get_x() + 1;
        _Value.y = get_y() + 1;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2 operator++(int) __GPU
    {
        short2 _Result = *this;
        ++(*this);
        return _Result;
    }

    short2& operator--() __GPU
    {
        int2 _Value;
        _Value.x = get_x() - 1;
        _Value.y = get_y() - 1;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2 operator--(int) __GPU
    {
        short2 _Result = *this;
        --(*this);
        return _Result;
    }

    short2& operator+=(const short2& _Other) __GPU
    {
        int2 _Value;
        _Value.x = get_x() + _Other.x;
        _Value.y = get_y() + _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2& operator-=(const short2& _Other) __GPU
    {
        int2 _Value;
        _Value.x = get_x() - _Other.x;
        _Value.y = get_y() - _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2& operator*=(const short2& _Other) __GPU
    {
        int2 _Value;
        _Value.x = get_x() * _Other.x;
        _Value.y = get_y() * _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2& operator/=(const short2& _Other) __GPU
    {
        int2 _Value;
        _Value.x = get_x() / _Other.x;
        _Value.y = get_y() / _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2& operator%=(const short2& _Other) __GPU
    {
        int2 _Value;
        _Value.x = get_x() % _Other.x;
        _Value.y = get_y() % _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2& operator^=(const short2& _Other) __GPU
    {
        short2 _Value1 = *this;
        short2 _Value2 = _Other;
        _Value1._M_xy[0] ^= _Value2._M_xy[0];
        *this = _Value1;
        return *this;
    }

    short2& operator|=(const short2& _Other) __GPU
    {
        short2 _Value1 = *this;
        short2 _Value2 = _Other;
        _Value1._M_xy[0] |= _Value2._M_xy[0];
        *this = _Value1;
        return *this;
    }

    short2& operator&=(const short2& _Other) __GPU
    {
        short2 _Value1 = *this;
        short2 _Value2 = _Other;
        _Value1._M_xy[0] &= _Value2._M_xy[0];
        *this = _Value1;
        return *this;
    }

    short2& operator>>=(const short2& _Other) __GPU
    {
        int2 _Value;
        _Value.x = get_x() >> _Other.x;
        _Value.y = get_y() >> _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

    short2& operator<<=(const short2& _Other) __GPU
    {
        int2 _Value;
        _Value.x = get_x() << _Other.x;
        _Value.y = get_y() << _Other.y;
        set_x(_Value.x);
        set_y(_Value.y);
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) short2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) short2 rg;

    short2 get_xy() const __GPU {
        return short2(_M_xy[0], _M_xy[1]);
    }

    void set_xy(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        _M_xy[0] = _Val.x;
        _M_xy[1] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) short2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) short2 gr;

    short2 get_yx() const __GPU {
        return short2(_M_xy[1], _M_xy[0]);
    }

    void set_yx(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        _M_xy[1] = _Val.x;
        _M_xy[0] = _Val.y;
    }

};

/// <summary>
///    Represent a packed vector of 4 int's.
/// </summary>
class short4
{
public:
    typedef int value_type;
    static const int size = 4;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Int_type;
private:
    value_type _M_xyzw[4];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xyzw[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xyzw[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) int x;
    __declspec( property( get = get_x, put = set_x) ) int r;

    int get_x() const __GPU {
        return _M_xyzw[0] & 0x0000FFFF;
    }

    void set_x(int _Value) __GPU
    {
        _M_xyzw[0] = (_M_xyzw[0] & 0xFFFF0000) + (_Value & 0x0000FFFF);
    }

    __declspec( property( get = get_y, put = set_y) ) int y;
    __declspec( property( get = get_y, put = set_y) ) int g;

    int get_y() const __GPU {
        return _M_xyzw[0] >> 16;
    }

    void set_y(int _Value) __GPU
    {
        _M_xyzw[0] = (_M_xyzw[0] & 0x0000FFFF) + (_Value << 16);
    }

    __declspec( property( get = get_z, put = set_z) ) int z;
    __declspec( property( get = get_z, put = set_z) ) int b;

    int get_z() const __GPU {
        return _M_xyzw[1] & 0x0000FFFF;
    }

    void set_z(int _Value) __GPU
    {
        _M_xyzw[1] = (_M_xyzw[1] & 0xFFFF0000) + (_Value & 0x0000FFFF);
    }

    __declspec( property( get = get_w, put = set_w) ) int w;
    __declspec( property( get = get_w, put = set_w) ) int a;

    int get_w() const __GPU {
        return _M_xyzw[1] >> 16;
    }

    void set_w(int _Value) __GPU
    {
        _M_xyzw[1] = (_M_xyzw[1] & 0x0000FFFF) + (_Value << 16);
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    short4() __GPU
    {
        _M_xyzw[0] = 0;
        _M_xyzw[1] = 0;
        _M_xyzw[2] = 0;
        _M_xyzw[3] = 0;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V0">
    ///     The value to initialize element 0.
    /// </param>
    /// <param name="_V1">
    ///     The value to initialize element 1.
    /// </param>
    /// <param name="_V2">
    ///     The value to initialize element 2.
    /// </param>
    /// <param name="_V3">
    ///     The value to initialize element 3.
    /// </param>
    short4(int _V0, int _V1, int _V2, int _V3) __GPU
    {
        _M_xyzw[0] = _V0;
        _M_xyzw[1] = _V1;
        _M_xyzw[2] = _V2;
        _M_xyzw[3] = _V3;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    short4(int _V) __GPU
    {
        _M_xyzw[0] = _V;
        _M_xyzw[1] = _V;
        _M_xyzw[2] = _V;
        _M_xyzw[3] = _V;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short4(const ushort4& _Other) __GPU;
    
    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short4(const int4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short4(const uint4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short4(const float4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short4(const unorm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short4(const norm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline short4(const double4& _Other) __GPU;

    short4 operator~() const __GPU
    {
        short4 _Value = *this;
        _Value._M_xyzw[0] = ~_Value._M_xyzw[0];
        _Value._M_xyzw[1] = ~_Value._M_xyzw[1];
        return _Value;
    }

    short4 operator-() const __GPU
    {
        int4 _Value;
        _Value.x = -get_x();
        _Value.y = -get_y();
        _Value.z = -get_z();
        _Value.w = -get_w();
        return short4(_Value.x, _Value.y, _Value.z, _Value.w);
    }

    short4& operator++() __GPU
    {
        int4 _Value;
        _Value.x = get_x() + 1;
        _Value.y = get_y() + 1;
        _Value.z = get_z() + 1;
        _Value.w = get_w() + 1;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4 operator++(int) __GPU
    {
        short4 _Result = *this;
        ++(*this);
        return _Result;
    }

    short4& operator--() __GPU
    {
        int4 _Value;
        _Value.x = get_x() - 1;
        _Value.y = get_y() - 1;
        _Value.z = get_z() - 1;
        _Value.w = get_w() - 1;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4 operator--(int) __GPU
    {
        short4 _Result = *this;
        --(*this);
        return _Result;
    }

    short4& operator+=(const short4& _Other) __GPU
    {
        int4 _Value;
        _Value.x = get_x() + _Other.x;
        _Value.y = get_y() + _Other.y;
        _Value.z = get_z() + _Other.z;
        _Value.w = get_w() + _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4& operator-=(const short4& _Other) __GPU
    {
        int4 _Value;
        _Value.x = get_x() - _Other.x;
        _Value.y = get_y() - _Other.y;
        _Value.z = get_z() - _Other.z;
        _Value.w = get_w() - _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4& operator*=(const short4& _Other) __GPU
    {
        int4 _Value;
        _Value.x = get_x() * _Other.x;
        _Value.y = get_y() * _Other.y;
        _Value.z = get_z() * _Other.z;
        _Value.w = get_w() * _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4& operator/=(const short4& _Other) __GPU
    {
        int4 _Value;
        _Value.x = get_x() / _Other.x;
        _Value.y = get_y() / _Other.y;
        _Value.z = get_z() / _Other.z;
        _Value.w = get_w() / _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4& operator%=(const short4& _Other) __GPU
    {
        int4 _Value;
        _Value.x = get_x() % _Other.x;
        _Value.y = get_y() % _Other.y;
        _Value.z = get_z() % _Other.z;
        _Value.w = get_w() % _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4& operator^=(const short4& _Other) __GPU
    {
        short4 _Value1 = *this;
        short4 _Value2 = _Other;
        _Value1._M_xyzw[0] ^= _Value2._M_xyzw[0];
        _Value1._M_xyzw[1] ^= _Value2._M_xyzw[1];
        *this = _Value1;
        return *this;
    }

    short4& operator|=(const short4& _Other) __GPU
    {
        short4 _Value1 = *this;
        short4 _Value2 = _Other;
        _Value1._M_xyzw[0] |= _Value2._M_xyzw[0];
        _Value1._M_xyzw[1] |= _Value2._M_xyzw[1];
        *this = _Value1;
        return *this;
    }

    short4& operator&=(const short4& _Other) __GPU
    {
        short4 _Value1 = *this;
        short4 _Value2 = _Other;
        _Value1._M_xyzw[0] &= _Value2._M_xyzw[0];
        _Value1._M_xyzw[1] &= _Value2._M_xyzw[1];
        *this = _Value1;
        return *this;
    }

    short4& operator>>=(const short4& _Other) __GPU
    {
        int4 _Value;
        _Value.x = get_x() >> _Other.x;
        _Value.y = get_y() >> _Other.y;
        _Value.z = get_z() >> _Other.z;
        _Value.w = get_w() >> _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

    short4& operator<<=(const short4& _Other) __GPU
    {
        int4 _Value;
        _Value.x = get_x() << _Other.x;
        _Value.y = get_y() << _Other.y;
        _Value.z = get_z() << _Other.z;
        _Value.w = get_w() << _Other.w;
        set_x(_Value.x);
        set_y(_Value.y);
        set_z(_Value.z);
        set_w(_Value.w);
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) short2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) short2 rg;

    short2 get_xy() const __GPU {
        return short2(get_x(), get_y());
    }

    void set_xy(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
    }

    __declspec( property( get = get_xz, put = set_xz) ) short2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) short2 rb;

    short2 get_xz() const __GPU {
        return short2(get_x(), get_z());
    }

    void set_xz(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
    }

    __declspec( property( get = get_xw, put = set_xw) ) short2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) short2 ra;

    short2 get_xw() const __GPU {
        return short2(get_x(), get_w());
    }

    void set_xw(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
    }

    __declspec( property( get = get_yx, put = set_yx) ) short2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) short2 gr;

    short2 get_yx() const __GPU {
        return short2(get_y(), get_x());
    }

    void set_yx(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
    }

    __declspec( property( get = get_yz, put = set_yz) ) short2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) short2 gb;

    short2 get_yz() const __GPU {
        return short2(get_y(), get_z());
    }

    void set_yz(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
    }

    __declspec( property( get = get_yw, put = set_yw) ) short2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) short2 ga;

    short2 get_yw() const __GPU {
        return short2(get_y(), get_w());
    }

    void set_yw(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
    }

    __declspec( property( get = get_zx, put = set_zx) ) short2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) short2 br;

    short2 get_zx() const __GPU {
        return short2(get_z(), get_x());
    }

    void set_zx(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
    }

    __declspec( property( get = get_zy, put = set_zy) ) short2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) short2 bg;

    short2 get_zy() const __GPU {
        return short2(get_z(), get_y());
    }

    void set_zy(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
    }

    __declspec( property( get = get_zw, put = set_zw) ) short2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) short2 ba;

    short2 get_zw() const __GPU {
        return short2(get_z(), get_w());
    }

    void set_zw(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
    }

    __declspec( property( get = get_wx, put = set_wx) ) short2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) short2 ar;

    short2 get_wx() const __GPU {
        return short2(get_w(), get_x());
    }

    void set_wx(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
    }

    __declspec( property( get = get_wy, put = set_wy) ) short2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) short2 ag;

    short2 get_wy() const __GPU {
        return short2(get_w(), get_y());
    }

    void set_wy(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
    }

    __declspec( property( get = get_wz, put = set_wz) ) short2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) short2 ab;

    short2 get_wz() const __GPU {
        return short2(get_w(), get_z());
    }

    void set_wz(const short2& _Value) __GPU
    {
        short2 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) int3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) int3 rgb;

    int3 get_xyz() const __GPU {
        return int3(get_x(), get_y(), get_z());
    }

    void set_xyz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) int3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) int3 rga;

    int3 get_xyw() const __GPU {
        return int3(get_x(), get_y(), _M_xyzw[3]);
    }

    void set_xyw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) int3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) int3 rbg;

    int3 get_xzy() const __GPU {
        return int3(get_x(), get_z(), get_y());
    }

    void set_xzy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) int3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) int3 rba;

    int3 get_xzw() const __GPU {
        return int3(get_x(), get_z(), get_w());
    }

    void set_xzw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) int3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) int3 rag;

    int3 get_xwy() const __GPU {
        return int3(get_x(), get_w(), get_y());
    }

    void set_xwy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) int3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) int3 rab;

    int3 get_xwz() const __GPU {
        return int3(get_x(), get_w(), get_z());
    }

    void set_xwz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) int3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) int3 grb;

    int3 get_yxz() const __GPU {
        return int3(get_y(), get_x(), get_z());
    }

    void set_yxz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) int3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) int3 gra;

    int3 get_yxw() const __GPU {
        return int3(get_y(), get_x(), get_w());
    }

    void set_yxw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) int3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) int3 gbr;

    int3 get_yzx() const __GPU {
        return int3(get_y(), get_z(), get_x());
    }

    void set_yzx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) int3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) int3 gba;

    int3 get_yzw() const __GPU {
        return int3(get_y(), get_z(), get_w());
    }

    void set_yzw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) int3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) int3 gar;

    int3 get_ywx() const __GPU {
        return int3(get_y(), get_w(), get_x());
    }

    void set_ywx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) int3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) int3 gab;

    int3 get_ywz() const __GPU {
        return int3(get_y(), get_w(), get_z());
    }

    void set_ywz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) int3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) int3 brg;

    int3 get_zxy() const __GPU {
        return int3(get_z(), get_x(), get_y());
    }

    void set_zxy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) int3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) int3 bra;

    int3 get_zxw() const __GPU {
        return int3(get_z(), get_x(), get_w());
    }

    void set_zxw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) int3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) int3 bgr;

    int3 get_zyx() const __GPU {
        return int3(get_z(), get_y(), get_x());
    }

    void set_zyx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) int3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) int3 bga;

    int3 get_zyw() const __GPU {
        return int3(get_z(), get_y(), get_w());
    }

    void set_zyw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) int3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) int3 bar;

    int3 get_zwx() const __GPU {
        return int3(get_z(), get_w(), get_x());
    }

    void set_zwx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) int3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) int3 bag;

    int3 get_zwy() const __GPU {
        return int3(get_z(), get_w(), get_y());
    }

    void set_zwy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) int3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) int3 arg;

    int3 get_wxy() const __GPU {
        return int3(get_w(), get_x(), get_y());
    }

    void set_wxy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) int3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) int3 arb;

    int3 get_wxz() const __GPU {
        return int3(get_w(), get_x(), get_z());
    }

    void set_wxz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) int3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) int3 agr;

    int3 get_wyx() const __GPU {
        return int3(get_w(), get_y(), get_x());
    }

    void set_wyx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) int3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) int3 agb;

    int3 get_wyz() const __GPU {
        return int3(get_w(), get_y(), get_z());
    }

    void set_wyz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) int3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) int3 abr;

    int3 get_wzx() const __GPU {
        return int3(get_w(), get_z(), get_x());
    }

    void set_wzx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) int3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) int3 abg;

    int3 get_wzy() const __GPU {
        return int3(get_w(), get_z(), get_y());
    }

    void set_wzy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) short4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) short4 rgba;

    short4 get_xyzw() const __GPU {
        return short4(get_x(), get_y(), get_z(), get_w());
    }

    void set_xyzw(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) short4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) short4 rgab;

    short4 get_xywz() const __GPU {
        return short4(get_x(), get_y(), get_w(), get_z());
    }

    void set_xywz(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_x(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) short4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) short4 rbga;

    short4 get_xzyw() const __GPU {
        return short4(get_x(), get_z(), get_y(), get_w());
    }

    void set_xzyw(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) short4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) short4 rbag;

    short4 get_xzwy() const __GPU {
        return short4(get_x(), get_z(), get_w(), get_y());
    }

    void set_xzwy(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_x(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) short4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) short4 ragb;

    short4 get_xwyz() const __GPU {
        return short4(get_x(), get_w(), get_y(), get_z());
    }

    void set_xwyz(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) short4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) short4 rabg;

    short4 get_xwzy() const __GPU {
        return short4(get_x(), get_w(), get_z(), get_y());
    }

    void set_xwzy(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_x(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) short4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) short4 grba;

    short4 get_yxzw() const __GPU {
        return short4(get_y(), get_x(), get_z(), get_w());
    }

    void set_yxzw(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) short4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) short4 grab;

    short4 get_yxwz() const __GPU {
        return short4(get_y(), get_x(), get_w(), get_z());
    }

    void set_yxwz(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_y(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) short4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) short4 gbra;

    short4 get_yzxw() const __GPU {
        return short4(get_y(), get_z(), get_x(), get_w());
    }

    void set_yzxw(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) short4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) short4 gbar;

    short4 get_yzwx() const __GPU {
        return short4(get_y(), get_z(), get_w(), get_x());
    }

    void set_yzwx(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_y(_Val.x);
        set_z(_Val.y);
        set_w(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) short4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) short4 garb;

    short4 get_ywxz() const __GPU {
        return short4(get_y(), get_w(), get_x(), get_z());
    }

    void set_ywxz(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) short4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) short4 gabr;

    short4 get_ywzx() const __GPU {
        return short4(get_y(), get_w(), get_z(), get_x());
    }

    void set_ywzx(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_y(_Val.x);
        set_w(_Val.y);
        set_z(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) short4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) short4 brga;

    short4 get_zxyw() const __GPU {
        return short4(get_z(), get_x(), get_y(), get_w());
    }

    void set_zxyw(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) short4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) short4 brag;

    short4 get_zxwy() const __GPU {
        return short4(get_z(), get_x(), get_w(), get_y());
    }

    void set_zxwy(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_z(_Val.x);
        set_x(_Val.y);
        set_w(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) short4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) short4 bgra;

    short4 get_zyxw() const __GPU {
        return short4(get_z(), get_y(), get_x(), get_w());
    }

    void set_zyxw(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
        set_w(_Val.w);
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) short4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) short4 bgar;

    short4 get_zywx() const __GPU {
        return short4(get_z(), get_y(), get_w(), get_x());
    }

    void set_zywx(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_z(_Val.x);
        set_y(_Val.y);
        set_w(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) short4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) short4 barg;

    short4 get_zwxy() const __GPU {
        return short4(get_z(), get_w(), get_x(), get_y());
    }

    void set_zwxy(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_x(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) short4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) short4 bagr;

    short4 get_zwyx() const __GPU {
        return short4(get_z(), get_w(), get_y(), get_x());
    }

    void set_zwyx(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_z(_Val.x);
        set_w(_Val.y);
        set_y(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) short4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) short4 argb;

    short4 get_wxyz() const __GPU {
        return short4(get_w(), get_x(), get_y(), get_z());
    }

    void set_wxyz(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_y(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) short4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) short4 arbg;

    short4 get_wxzy() const __GPU {
        return short4(get_w(), get_x(), get_z(), get_y());
    }

    void set_wxzy(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_w(_Val.x);
        set_x(_Val.y);
        set_z(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) short4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) short4 agrb;

    short4 get_wyxz() const __GPU {
        return short4(get_w(), get_y(), get_x(), _M_xyzw[2]);
    }

    void set_wyxz(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_x(_Val.z);
        set_z(_Val.w);
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) short4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) short4 agbr;

    short4 get_wyzx() const __GPU {
        return short4(get_w(), get_y(), get_z(), get_x());
    }

    void set_wyzx(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_w(_Val.x);
        set_y(_Val.y);
        set_z(_Val.z);
        set_x(_Val.w);
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) short4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) short4 abrg;

    short4 get_wzxy() const __GPU {
        return short4(get_w(), get_z(), get_x(), get_y());
    }

    void set_wzxy(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_x(_Val.z);
        set_y(_Val.w);
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) short4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) short4 abgr;

    short4 get_wzyx() const __GPU {
        return short4(get_w(), get_z(), get_y(), get_x());
    }

    void set_wzyx(const short4& _Value) __GPU
    {
        short4 _Val = _Value;
        set_w(_Val.x);
        set_z(_Val.y);
        set_y(_Val.z);
        set_x(_Val.w);
    }

};


ushort2::ushort2(const short2& _Other) __GPU
{
    short2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

ushort2::ushort2(const int2& _Other) __GPU
{
    int2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

ushort2::ushort2(const uint2& _Other) __GPU
{
    uint2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

ushort2::ushort2(const float2& _Other) __GPU
{
    float2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

ushort2::ushort2(const unorm2& _Other) __GPU
{
    unorm2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

ushort2::ushort2(const norm2& _Other) __GPU
{
    norm2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

ushort2::ushort2(const double2& _Other) __GPU
{
    double2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}


ushort4::ushort4(const short4& _Other) __GPU
{
    short4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

ushort4::ushort4(const int4& _Other) __GPU
{
    int4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

ushort4::ushort4(const uint4& _Other) __GPU
{
    uint4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

ushort4::ushort4(const float4& _Other) __GPU
{
    float4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

ushort4::ushort4(const unorm4& _Other) __GPU
{
    unorm4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

ushort4::ushort4(const norm4& _Other) __GPU
{
    norm4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

ushort4::ushort4(const double4& _Other) __GPU
{
    double4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}


short2::short2(const ushort2& _Other) __GPU
{
    ushort2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

short2::short2(const int2& _Other) __GPU
{
    int2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

short2::short2(const uint2& _Other) __GPU
{
    uint2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

short2::short2(const float2& _Other) __GPU
{
    float2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

short2::short2(const unorm2& _Other) __GPU
{
    unorm2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

short2::short2(const norm2& _Other) __GPU
{
    norm2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}

short2::short2(const double2& _Other) __GPU
{
    double2 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
}


short4::short4(const ushort4& _Other) __GPU
{
    ushort4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

short4::short4(const int4& _Other) __GPU
{
    int4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

short4::short4(const uint4& _Other) __GPU
{
    uint4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

short4::short4(const float4& _Other) __GPU
{
    float4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

short4::short4(const unorm4& _Other) __GPU
{
    unorm4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

short4::short4(const norm4& _Other) __GPU
{
    norm4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}

short4::short4(const double4& _Other) __GPU
{
    double4 _Value = _Other;
    set_x(static_cast<value_type>(_Value.x));
    set_y(static_cast<value_type>(_Value.y));
    set_z(static_cast<value_type>(_Value.z));
    set_w(static_cast<value_type>(_Value.w));
}


inline ushort2 operator+(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return ushort2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline ushort2 operator-(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return ushort2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline ushort2 operator*(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return ushort2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline ushort2 operator/(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return ushort2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline ushort2 operator%(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return ushort2(_Value1.x % _Value2.x, _Value1.y % _Value2.y);
}

inline ushort2 operator^(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return _Value1 ^= _Value2;
}

inline ushort2 operator|(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return _Value1 |= _Value2;
}

inline ushort2 operator&(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return _Value1 &= _Value2;
}

inline ushort2 operator<<(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return ushort2(_Value1.x << _Value2.x, _Value1.y << _Value2.y);
}

inline ushort2 operator>>(const ushort2& _Lhs, const ushort2& _Rhs) __GPU
{
    ushort2 _Value1 = _Lhs;
    ushort2 _Value2 = _Rhs;
    return ushort2(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y);
}

inline ushort4 operator+(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return ushort4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline ushort4 operator-(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return ushort4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline ushort4 operator*(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return ushort4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline ushort4 operator/(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return ushort4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

inline ushort4 operator%(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return ushort4(_Value1.x % _Value2.x, _Value1.y % _Value2.y, _Value1.z % _Value2.z, _Value1.w % _Value2.w);
}

inline ushort4 operator^(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return _Value1 ^= _Value2;
}

inline ushort4 operator|(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return _Value1 |= _Value2;
}

inline ushort4 operator&(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return _Value1 &= _Value2;
}

inline ushort4 operator<<(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return ushort4(_Value1.x << _Value2.x, _Value1.y << _Value2.y, _Value1.z << _Value2.z, _Value1.w << _Value2.w);
}

inline ushort4 operator>>(const ushort4& _Lhs, const ushort4& _Rhs) __GPU
{
    ushort4 _Value1 = _Lhs;
    ushort4 _Value2 = _Rhs;
    return ushort4(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y, _Value1.z >> _Value2.z, _Value1.w >> _Value2.w);
}

inline short2 operator+(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return short2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline short2 operator-(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return short2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline short2 operator*(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return short2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline short2 operator/(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return short2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline short2 operator%(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return short2(_Value1.x % _Value2.x, _Value1.y % _Value2.y);
}

inline short2 operator^(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return _Value1 ^= _Value2;
}

inline short2 operator|(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return _Value1 |= _Value2;
}

inline short2 operator&(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return _Value1 &= _Value2;
}

inline short2 operator<<(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return short2(_Value1.x << _Value2.x, _Value1.y << _Value2.y);
}

inline short2 operator>>(const short2& _Lhs, const short2& _Rhs) __GPU
{
    short2 _Value1 = _Lhs;
    short2 _Value2 = _Rhs;
    return short2(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y);
}

inline short4 operator+(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return short4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline short4 operator-(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return short4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline short4 operator*(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return short4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline short4 operator/(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return short4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

inline short4 operator%(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return short4(_Value1.x % _Value2.x, _Value1.y % _Value2.y, _Value1.z % _Value2.z, _Value1.w % _Value2.w);
}

inline short4 operator^(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return _Value1 ^= _Value2;
}

inline short4 operator|(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return _Value1 |= _Value2;
}

inline short4 operator&(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return _Value1 &= _Value2;
}

inline short4 operator<<(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return short4(_Value1.x << _Value2.x, _Value1.y << _Value2.y, _Value1.z << _Value2.z, _Value1.w << _Value2.w);
}

inline short4 operator>>(const short4& _Lhs, const short4& _Rhs) __GPU
{
    short4 _Value1 = _Lhs;
    short4 _Value2 = _Rhs;
    return short4(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y, _Value1.z >> _Value2.z, _Value1.w >> _Value2.w);
}

template<>
struct short_vector_traits<ushort2>
{
    typedef unsigned int value_type;
    static int const size = 1;
};

template<>
struct short_vector_traits<ushort4>
{
    typedef unsigned int value_type;
    static int const size = 2;
};

template<>
struct short_vector_traits<short2>
{
    typedef int value_type;
    static int const size = 1;
};

template<>
struct short_vector_traits<short4>
{
    typedef int value_type;
    static int const size = 2;
};

namespace details
{

template<>
struct _Short_vector_type_traits<ushort2>
{
    typedef ushort2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Uint_type;
    static const unsigned int _Num_channels = 1;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<ushort4>
{
    typedef ushort4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Uint_type;
    static const unsigned int _Num_channels = 2;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<short2>
{
    typedef short2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Int_type;
    static const unsigned int _Num_channels = 1;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<short4>
{
    typedef short4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Int_type;
    static const unsigned int _Num_channels = 2;
    static const unsigned int _Default_bits_per_channel = 32;
};

} // namespace details

} // namespace graphics

} // namespace Concurrency
#pragma warning(pop)
// End of generated file
