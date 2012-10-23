/***
* ==++==
*
* Copyright (c) Microsoft Corporation.  All rights reserved.
*
* ==--==
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* amp_short_arrays.h
*
* C++ AMP Short Array Types
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
class uint2;
class uint3;
class uint4;
class int2;
class int3;
class int4;
class float2;
class float3;
class float4;
class unorm2;
class unorm3;
class unorm4;
class norm2;
class norm3;
class norm4;
class double2;
class double3;
class double4;

/// <summary>
///    Represent a short vector of 2 unsigned int's.
/// </summary>
class uint2
{
public:
    typedef unsigned int value_type;
    static const int size = 2;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Uint_type;
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

    __declspec( property( get = get_x, put = set_x) ) unsigned int x;
    __declspec( property( get = get_x, put = set_x) ) unsigned int r;

    unsigned int get_x() const __GPU {
        return _M_xy[0];
    }

    void set_x(unsigned int _Value) __GPU
    {
        _M_xy[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) unsigned int y;
    __declspec( property( get = get_y, put = set_y) ) unsigned int g;

    unsigned int get_y() const __GPU {
        return _M_xy[1];
    }

    void set_y(unsigned int _Value) __GPU
    {
        _M_xy[1] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    uint2() __GPU
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
    uint2(unsigned int _V0, unsigned int _V1) __GPU
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
    uint2(unsigned int _V) __GPU
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
    explicit inline uint2(const int2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint2(const float2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint2(const unorm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint2(const norm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint2(const double2& _Other) __GPU;

    uint2 operator~() const __GPU
    {
        uint2 _Value = *this;
        return uint2(~_Value.x, ~_Value.y);
    }

    uint2& operator++() __GPU
    {
        uint2 _Value = *this;
        ++_Value._M_xy[0];
        ++_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    uint2 operator++(int) __GPU
    {
        uint2 _Result = *this;
        ++(*this);
        return _Result;
    }

    uint2& operator--() __GPU
    {
        uint2 _Value = *this;
        --_Value._M_xy[0];
        --_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    uint2 operator--(int) __GPU
    {
        uint2 _Result = *this;
        --(*this);
        return _Result;
    }

    uint2& operator+=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator-=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator*=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator/=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator%=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x %= _Value2.x;
        _Value1.y %= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator^=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x ^= _Value2.x;
        _Value1.y ^= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator|=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x |= _Value2.x;
        _Value1.y |= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator&=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x &= _Value2.x;
        _Value1.y &= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator>>=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x >>= _Value2.x;
        _Value1.y >>= _Value2.y;
        *this = _Value1;
        return *this;
    }

    uint2& operator<<=(const uint2& _Other) __GPU
    {
        uint2 _Value1 = *this;
        uint2 _Value2 = _Other;
        _Value1.x <<= _Value2.x;
        _Value1.y <<= _Value2.y;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) uint2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) uint2 rg;

    uint2 get_xy() const __GPU {
        return uint2(_M_xy[0], _M_xy[1]);
    }

    void set_xy(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xy[0] = _Val.x;
        _M_xy[1] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) uint2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) uint2 gr;

    uint2 get_yx() const __GPU {
        return uint2(_M_xy[1], _M_xy[0]);
    }

    void set_yx(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xy[1] = _Val.x;
        _M_xy[0] = _Val.y;
    }

};

/// <summary>
///    Represent a short vector of 3 unsigned int's.
/// </summary>
class uint3
{
public:
    typedef unsigned int value_type;
    static const int size = 3;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Uint_type;
private:
    value_type _M_xyz[3];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xyz[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xyz[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) unsigned int x;
    __declspec( property( get = get_x, put = set_x) ) unsigned int r;

    unsigned int get_x() const __GPU {
        return _M_xyz[0];
    }

    void set_x(unsigned int _Value) __GPU
    {
        _M_xyz[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) unsigned int y;
    __declspec( property( get = get_y, put = set_y) ) unsigned int g;

    unsigned int get_y() const __GPU {
        return _M_xyz[1];
    }

    void set_y(unsigned int _Value) __GPU
    {
        _M_xyz[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) unsigned int z;
    __declspec( property( get = get_z, put = set_z) ) unsigned int b;

    unsigned int get_z() const __GPU {
        return _M_xyz[2];
    }

    void set_z(unsigned int _Value) __GPU
    {
        _M_xyz[2] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    uint3() __GPU
    {
        _M_xyz[0] = 0;
        _M_xyz[1] = 0;
        _M_xyz[2] = 0;
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
    uint3(unsigned int _V0, unsigned int _V1, unsigned int _V2) __GPU
    {
        _M_xyz[0] = _V0;
        _M_xyz[1] = _V1;
        _M_xyz[2] = _V2;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    uint3(unsigned int _V) __GPU
    {
        _M_xyz[0] = _V;
        _M_xyz[1] = _V;
        _M_xyz[2] = _V;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint3(const int3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint3(const float3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint3(const unorm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint3(const norm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint3(const double3& _Other) __GPU;

    uint3 operator~() const __GPU
    {
        uint3 _Value = *this;
        return uint3(~_Value.x, ~_Value.y, ~_Value.z);
    }

    uint3& operator++() __GPU
    {
        uint3 _Value = *this;
        ++_Value._M_xyz[0];
        ++_Value._M_xyz[1];
        ++_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    uint3 operator++(int) __GPU
    {
        uint3 _Result = *this;
        ++(*this);
        return _Result;
    }

    uint3& operator--() __GPU
    {
        uint3 _Value = *this;
        --_Value._M_xyz[0];
        --_Value._M_xyz[1];
        --_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    uint3 operator--(int) __GPU
    {
        uint3 _Result = *this;
        --(*this);
        return _Result;
    }

    uint3& operator+=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator-=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator*=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator/=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator%=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x %= _Value2.x;
        _Value1.y %= _Value2.y;
        _Value1.z %= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator^=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x ^= _Value2.x;
        _Value1.y ^= _Value2.y;
        _Value1.z ^= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator|=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x |= _Value2.x;
        _Value1.y |= _Value2.y;
        _Value1.z |= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator&=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x &= _Value2.x;
        _Value1.y &= _Value2.y;
        _Value1.z &= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator>>=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x >>= _Value2.x;
        _Value1.y >>= _Value2.y;
        _Value1.z >>= _Value2.z;
        *this = _Value1;
        return *this;
    }

    uint3& operator<<=(const uint3& _Other) __GPU
    {
        uint3 _Value1 = *this;
        uint3 _Value2 = _Other;
        _Value1.x <<= _Value2.x;
        _Value1.y <<= _Value2.y;
        _Value1.z <<= _Value2.z;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) uint2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) uint2 rg;

    uint2 get_xy() const __GPU {
        return uint2(_M_xyz[0], _M_xyz[1]);
    }

    void set_xy(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) uint2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) uint2 rb;

    uint2 get_xz() const __GPU {
        return uint2(_M_xyz[0], _M_xyz[2]);
    }

    void set_xz(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) uint2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) uint2 gr;

    uint2 get_yx() const __GPU {
        return uint2(_M_xyz[1], _M_xyz[0]);
    }

    void set_yx(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) uint2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) uint2 gb;

    uint2 get_yz() const __GPU {
        return uint2(_M_xyz[1], _M_xyz[2]);
    }

    void set_yz(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) uint2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) uint2 br;

    uint2 get_zx() const __GPU {
        return uint2(_M_xyz[2], _M_xyz[0]);
    }

    void set_zx(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) uint2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) uint2 bg;

    uint2 get_zy() const __GPU {
        return uint2(_M_xyz[2], _M_xyz[1]);
    }

    void set_zy(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) uint3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) uint3 rgb;

    uint3 get_xyz() const __GPU {
        return uint3(_M_xyz[0], _M_xyz[1], _M_xyz[2]);
    }

    void set_xyz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) uint3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) uint3 rbg;

    uint3 get_xzy() const __GPU {
        return uint3(_M_xyz[0], _M_xyz[2], _M_xyz[1]);
    }

    void set_xzy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) uint3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) uint3 grb;

    uint3 get_yxz() const __GPU {
        return uint3(_M_xyz[1], _M_xyz[0], _M_xyz[2]);
    }

    void set_yxz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) uint3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) uint3 gbr;

    uint3 get_yzx() const __GPU {
        return uint3(_M_xyz[1], _M_xyz[2], _M_xyz[0]);
    }

    void set_yzx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) uint3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) uint3 brg;

    uint3 get_zxy() const __GPU {
        return uint3(_M_xyz[2], _M_xyz[0], _M_xyz[1]);
    }

    void set_zxy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) uint3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) uint3 bgr;

    uint3 get_zyx() const __GPU {
        return uint3(_M_xyz[2], _M_xyz[1], _M_xyz[0]);
    }

    void set_zyx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

};

/// <summary>
///    Represent a short vector of 4 unsigned int's.
/// </summary>
class uint4
{
public:
    typedef unsigned int value_type;
    static const int size = 4;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Uint_type;
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

    __declspec( property( get = get_x, put = set_x) ) unsigned int x;
    __declspec( property( get = get_x, put = set_x) ) unsigned int r;

    unsigned int get_x() const __GPU {
        return _M_xyzw[0];
    }

    void set_x(unsigned int _Value) __GPU
    {
        _M_xyzw[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) unsigned int y;
    __declspec( property( get = get_y, put = set_y) ) unsigned int g;

    unsigned int get_y() const __GPU {
        return _M_xyzw[1];
    }

    void set_y(unsigned int _Value) __GPU
    {
        _M_xyzw[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) unsigned int z;
    __declspec( property( get = get_z, put = set_z) ) unsigned int b;

    unsigned int get_z() const __GPU {
        return _M_xyzw[2];
    }

    void set_z(unsigned int _Value) __GPU
    {
        _M_xyzw[2] = _Value;
    }

    __declspec( property( get = get_w, put = set_w) ) unsigned int w;
    __declspec( property( get = get_w, put = set_w) ) unsigned int a;

    unsigned int get_w() const __GPU {
        return _M_xyzw[3];
    }

    void set_w(unsigned int _Value) __GPU
    {
        _M_xyzw[3] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    uint4() __GPU
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
    uint4(unsigned int _V0, unsigned int _V1, unsigned int _V2, unsigned int _V3) __GPU
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
    uint4(unsigned int _V) __GPU
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
    explicit inline uint4(const int4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint4(const float4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint4(const unorm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint4(const norm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline uint4(const double4& _Other) __GPU;

    uint4 operator~() const __GPU
    {
        uint4 _Value = *this;
        return uint4(~_Value.x, ~_Value.y, ~_Value.z, ~_Value.w);
    }

    uint4& operator++() __GPU
    {
        uint4 _Value = *this;
        ++_Value._M_xyzw[0];
        ++_Value._M_xyzw[1];
        ++_Value._M_xyzw[2];
        ++_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    uint4 operator++(int) __GPU
    {
        uint4 _Result = *this;
        ++(*this);
        return _Result;
    }

    uint4& operator--() __GPU
    {
        uint4 _Value = *this;
        --_Value._M_xyzw[0];
        --_Value._M_xyzw[1];
        --_Value._M_xyzw[2];
        --_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    uint4 operator--(int) __GPU
    {
        uint4 _Result = *this;
        --(*this);
        return _Result;
    }

    uint4& operator+=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        _Value1.w += _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator-=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        _Value1.w -= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator*=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        _Value1.w *= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator/=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        _Value1.w /= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator%=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x %= _Value2.x;
        _Value1.y %= _Value2.y;
        _Value1.z %= _Value2.z;
        _Value1.w %= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator^=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x ^= _Value2.x;
        _Value1.y ^= _Value2.y;
        _Value1.z ^= _Value2.z;
        _Value1.w ^= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator|=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x |= _Value2.x;
        _Value1.y |= _Value2.y;
        _Value1.z |= _Value2.z;
        _Value1.w |= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator&=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x &= _Value2.x;
        _Value1.y &= _Value2.y;
        _Value1.z &= _Value2.z;
        _Value1.w &= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator>>=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x >>= _Value2.x;
        _Value1.y >>= _Value2.y;
        _Value1.z >>= _Value2.z;
        _Value1.w >>= _Value2.w;
        *this = _Value1;
        return *this;
    }

    uint4& operator<<=(const uint4& _Other) __GPU
    {
        uint4 _Value1 = *this;
        uint4 _Value2 = _Other;
        _Value1.x <<= _Value2.x;
        _Value1.y <<= _Value2.y;
        _Value1.z <<= _Value2.z;
        _Value1.w <<= _Value2.w;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) uint2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) uint2 rg;

    uint2 get_xy() const __GPU {
        return uint2(_M_xyzw[0], _M_xyzw[1]);
    }

    void set_xy(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) uint2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) uint2 rb;

    uint2 get_xz() const __GPU {
        return uint2(_M_xyzw[0], _M_xyzw[2]);
    }

    void set_xz(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xw, put = set_xw) ) uint2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) uint2 ra;

    uint2 get_xw() const __GPU {
        return uint2(_M_xyzw[0], _M_xyzw[3]);
    }

    void set_xw(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) uint2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) uint2 gr;

    uint2 get_yx() const __GPU {
        return uint2(_M_xyzw[1], _M_xyzw[0]);
    }

    void set_yx(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) uint2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) uint2 gb;

    uint2 get_yz() const __GPU {
        return uint2(_M_xyzw[1], _M_xyzw[2]);
    }

    void set_yz(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_yw, put = set_yw) ) uint2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) uint2 ga;

    uint2 get_yw() const __GPU {
        return uint2(_M_xyzw[1], _M_xyzw[3]);
    }

    void set_yw(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) uint2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) uint2 br;

    uint2 get_zx() const __GPU {
        return uint2(_M_xyzw[2], _M_xyzw[0]);
    }

    void set_zx(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) uint2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) uint2 bg;

    uint2 get_zy() const __GPU {
        return uint2(_M_xyzw[2], _M_xyzw[1]);
    }

    void set_zy(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_zw, put = set_zw) ) uint2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) uint2 ba;

    uint2 get_zw() const __GPU {
        return uint2(_M_xyzw[2], _M_xyzw[3]);
    }

    void set_zw(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_wx, put = set_wx) ) uint2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) uint2 ar;

    uint2 get_wx() const __GPU {
        return uint2(_M_xyzw[3], _M_xyzw[0]);
    }

    void set_wx(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_wy, put = set_wy) ) uint2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) uint2 ag;

    uint2 get_wy() const __GPU {
        return uint2(_M_xyzw[3], _M_xyzw[1]);
    }

    void set_wy(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_wz, put = set_wz) ) uint2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) uint2 ab;

    uint2 get_wz() const __GPU {
        return uint2(_M_xyzw[3], _M_xyzw[2]);
    }

    void set_wz(const uint2& _Value) __GPU
    {
        uint2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) uint3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) uint3 rgb;

    uint3 get_xyz() const __GPU {
        return uint3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xyz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) uint3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) uint3 rga;

    uint3 get_xyw() const __GPU {
        return uint3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xyw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) uint3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) uint3 rbg;

    uint3 get_xzy() const __GPU {
        return uint3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xzy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) uint3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) uint3 rba;

    uint3 get_xzw() const __GPU {
        return uint3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xzw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) uint3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) uint3 rag;

    uint3 get_xwy() const __GPU {
        return uint3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xwy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) uint3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) uint3 rab;

    uint3 get_xwz() const __GPU {
        return uint3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xwz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) uint3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) uint3 grb;

    uint3 get_yxz() const __GPU {
        return uint3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_yxz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) uint3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) uint3 gra;

    uint3 get_yxw() const __GPU {
        return uint3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yxw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) uint3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) uint3 gbr;

    uint3 get_yzx() const __GPU {
        return uint3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_yzx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) uint3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) uint3 gba;

    uint3 get_yzw() const __GPU {
        return uint3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yzw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) uint3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) uint3 gar;

    uint3 get_ywx() const __GPU {
        return uint3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_ywx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) uint3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) uint3 gab;

    uint3 get_ywz() const __GPU {
        return uint3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_ywz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) uint3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) uint3 brg;

    uint3 get_zxy() const __GPU {
        return uint3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zxy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) uint3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) uint3 bra;

    uint3 get_zxw() const __GPU {
        return uint3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zxw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) uint3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) uint3 bgr;

    uint3 get_zyx() const __GPU {
        return uint3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zyx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) uint3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) uint3 bga;

    uint3 get_zyw() const __GPU {
        return uint3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zyw(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) uint3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) uint3 bar;

    uint3 get_zwx() const __GPU {
        return uint3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zwx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) uint3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) uint3 bag;

    uint3 get_zwy() const __GPU {
        return uint3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zwy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) uint3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) uint3 arg;

    uint3 get_wxy() const __GPU {
        return uint3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wxy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) uint3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) uint3 arb;

    uint3 get_wxz() const __GPU {
        return uint3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wxz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) uint3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) uint3 agr;

    uint3 get_wyx() const __GPU {
        return uint3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wyx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) uint3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) uint3 agb;

    uint3 get_wyz() const __GPU {
        return uint3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wyz(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) uint3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) uint3 abr;

    uint3 get_wzx() const __GPU {
        return uint3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wzx(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) uint3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) uint3 abg;

    uint3 get_wzy() const __GPU {
        return uint3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wzy(const uint3& _Value) __GPU
    {
        uint3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) uint4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) uint4 rgba;

    uint4 get_xyzw() const __GPU {
        return uint4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xyzw(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) uint4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) uint4 rgab;

    uint4 get_xywz() const __GPU {
        return uint4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xywz(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) uint4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) uint4 rbga;

    uint4 get_xzyw() const __GPU {
        return uint4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xzyw(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) uint4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) uint4 rbag;

    uint4 get_xzwy() const __GPU {
        return uint4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xzwy(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) uint4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) uint4 ragb;

    uint4 get_xwyz() const __GPU {
        return uint4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xwyz(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) uint4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) uint4 rabg;

    uint4 get_xwzy() const __GPU {
        return uint4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xwzy(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) uint4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) uint4 grba;

    uint4 get_yxzw() const __GPU {
        return uint4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yxzw(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) uint4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) uint4 grab;

    uint4 get_yxwz() const __GPU {
        return uint4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_yxwz(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) uint4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) uint4 gbra;

    uint4 get_yzxw() const __GPU {
        return uint4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yzxw(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) uint4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) uint4 gbar;

    uint4 get_yzwx() const __GPU {
        return uint4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_yzwx(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) uint4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) uint4 garb;

    uint4 get_ywxz() const __GPU {
        return uint4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_ywxz(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) uint4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) uint4 gabr;

    uint4 get_ywzx() const __GPU {
        return uint4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_ywzx(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) uint4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) uint4 brga;

    uint4 get_zxyw() const __GPU {
        return uint4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zxyw(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) uint4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) uint4 brag;

    uint4 get_zxwy() const __GPU {
        return uint4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zxwy(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) uint4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) uint4 bgra;

    uint4 get_zyxw() const __GPU {
        return uint4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zyxw(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) uint4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) uint4 bgar;

    uint4 get_zywx() const __GPU {
        return uint4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zywx(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) uint4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) uint4 barg;

    uint4 get_zwxy() const __GPU {
        return uint4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zwxy(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) uint4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) uint4 bagr;

    uint4 get_zwyx() const __GPU {
        return uint4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zwyx(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) uint4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) uint4 argb;

    uint4 get_wxyz() const __GPU {
        return uint4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wxyz(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) uint4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) uint4 arbg;

    uint4 get_wxzy() const __GPU {
        return uint4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wxzy(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) uint4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) uint4 agrb;

    uint4 get_wyxz() const __GPU {
        return uint4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wyxz(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) uint4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) uint4 agbr;

    uint4 get_wyzx() const __GPU {
        return uint4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wyzx(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) uint4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) uint4 abrg;

    uint4 get_wzxy() const __GPU {
        return uint4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wzxy(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) uint4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) uint4 abgr;

    uint4 get_wzyx() const __GPU {
        return uint4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wzyx(const uint4& _Value) __GPU
    {
        uint4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

};

/// <summary>
///    Represent a short vector of 2 int's.
/// </summary>
class int2
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
    int2() __GPU
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
    int2(int _V0, int _V1) __GPU
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
    int2(int _V) __GPU
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
    explicit inline int2(const uint2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int2(const float2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int2(const unorm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int2(const norm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int2(const double2& _Other) __GPU;

    int2 operator~() const __GPU
    {
        int2 _Value = *this;
        return int2(~_Value.x, ~_Value.y);
    }

    int2 operator-() const __GPU
    {
        int2 _Value = *this;
        return int2(-_Value.x, -_Value.y);
    }

    int2& operator++() __GPU
    {
        int2 _Value = *this;
        ++_Value._M_xy[0];
        ++_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    int2 operator++(int) __GPU
    {
        int2 _Result = *this;
        ++(*this);
        return _Result;
    }

    int2& operator--() __GPU
    {
        int2 _Value = *this;
        --_Value._M_xy[0];
        --_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    int2 operator--(int) __GPU
    {
        int2 _Result = *this;
        --(*this);
        return _Result;
    }

    int2& operator+=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator-=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator*=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator/=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator%=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x %= _Value2.x;
        _Value1.y %= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator^=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x ^= _Value2.x;
        _Value1.y ^= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator|=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x |= _Value2.x;
        _Value1.y |= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator&=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x &= _Value2.x;
        _Value1.y &= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator>>=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x >>= _Value2.x;
        _Value1.y >>= _Value2.y;
        *this = _Value1;
        return *this;
    }

    int2& operator<<=(const int2& _Other) __GPU
    {
        int2 _Value1 = *this;
        int2 _Value2 = _Other;
        _Value1.x <<= _Value2.x;
        _Value1.y <<= _Value2.y;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) int2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) int2 rg;

    int2 get_xy() const __GPU {
        return int2(_M_xy[0], _M_xy[1]);
    }

    void set_xy(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xy[0] = _Val.x;
        _M_xy[1] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) int2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) int2 gr;

    int2 get_yx() const __GPU {
        return int2(_M_xy[1], _M_xy[0]);
    }

    void set_yx(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xy[1] = _Val.x;
        _M_xy[0] = _Val.y;
    }

};

/// <summary>
///    Represent a short vector of 3 int's.
/// </summary>
class int3
{
public:
    typedef int value_type;
    static const int size = 3;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Int_type;
private:
    value_type _M_xyz[3];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xyz[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xyz[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) int x;
    __declspec( property( get = get_x, put = set_x) ) int r;

    int get_x() const __GPU {
        return _M_xyz[0];
    }

    void set_x(int _Value) __GPU
    {
        _M_xyz[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) int y;
    __declspec( property( get = get_y, put = set_y) ) int g;

    int get_y() const __GPU {
        return _M_xyz[1];
    }

    void set_y(int _Value) __GPU
    {
        _M_xyz[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) int z;
    __declspec( property( get = get_z, put = set_z) ) int b;

    int get_z() const __GPU {
        return _M_xyz[2];
    }

    void set_z(int _Value) __GPU
    {
        _M_xyz[2] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    int3() __GPU
    {
        _M_xyz[0] = 0;
        _M_xyz[1] = 0;
        _M_xyz[2] = 0;
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
    int3(int _V0, int _V1, int _V2) __GPU
    {
        _M_xyz[0] = _V0;
        _M_xyz[1] = _V1;
        _M_xyz[2] = _V2;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    int3(int _V) __GPU
    {
        _M_xyz[0] = _V;
        _M_xyz[1] = _V;
        _M_xyz[2] = _V;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int3(const uint3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int3(const float3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int3(const unorm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int3(const norm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int3(const double3& _Other) __GPU;

    int3 operator~() const __GPU
    {
        int3 _Value = *this;
        return int3(~_Value.x, ~_Value.y, ~_Value.z);
    }

    int3 operator-() const __GPU
    {
        int3 _Value = *this;
        return int3(-_Value.x, -_Value.y, -_Value.z);
    }

    int3& operator++() __GPU
    {
        int3 _Value = *this;
        ++_Value._M_xyz[0];
        ++_Value._M_xyz[1];
        ++_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    int3 operator++(int) __GPU
    {
        int3 _Result = *this;
        ++(*this);
        return _Result;
    }

    int3& operator--() __GPU
    {
        int3 _Value = *this;
        --_Value._M_xyz[0];
        --_Value._M_xyz[1];
        --_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    int3 operator--(int) __GPU
    {
        int3 _Result = *this;
        --(*this);
        return _Result;
    }

    int3& operator+=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator-=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator*=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator/=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator%=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x %= _Value2.x;
        _Value1.y %= _Value2.y;
        _Value1.z %= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator^=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x ^= _Value2.x;
        _Value1.y ^= _Value2.y;
        _Value1.z ^= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator|=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x |= _Value2.x;
        _Value1.y |= _Value2.y;
        _Value1.z |= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator&=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x &= _Value2.x;
        _Value1.y &= _Value2.y;
        _Value1.z &= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator>>=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x >>= _Value2.x;
        _Value1.y >>= _Value2.y;
        _Value1.z >>= _Value2.z;
        *this = _Value1;
        return *this;
    }

    int3& operator<<=(const int3& _Other) __GPU
    {
        int3 _Value1 = *this;
        int3 _Value2 = _Other;
        _Value1.x <<= _Value2.x;
        _Value1.y <<= _Value2.y;
        _Value1.z <<= _Value2.z;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) int2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) int2 rg;

    int2 get_xy() const __GPU {
        return int2(_M_xyz[0], _M_xyz[1]);
    }

    void set_xy(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) int2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) int2 rb;

    int2 get_xz() const __GPU {
        return int2(_M_xyz[0], _M_xyz[2]);
    }

    void set_xz(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) int2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) int2 gr;

    int2 get_yx() const __GPU {
        return int2(_M_xyz[1], _M_xyz[0]);
    }

    void set_yx(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) int2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) int2 gb;

    int2 get_yz() const __GPU {
        return int2(_M_xyz[1], _M_xyz[2]);
    }

    void set_yz(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) int2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) int2 br;

    int2 get_zx() const __GPU {
        return int2(_M_xyz[2], _M_xyz[0]);
    }

    void set_zx(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) int2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) int2 bg;

    int2 get_zy() const __GPU {
        return int2(_M_xyz[2], _M_xyz[1]);
    }

    void set_zy(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) int3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) int3 rgb;

    int3 get_xyz() const __GPU {
        return int3(_M_xyz[0], _M_xyz[1], _M_xyz[2]);
    }

    void set_xyz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) int3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) int3 rbg;

    int3 get_xzy() const __GPU {
        return int3(_M_xyz[0], _M_xyz[2], _M_xyz[1]);
    }

    void set_xzy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) int3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) int3 grb;

    int3 get_yxz() const __GPU {
        return int3(_M_xyz[1], _M_xyz[0], _M_xyz[2]);
    }

    void set_yxz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) int3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) int3 gbr;

    int3 get_yzx() const __GPU {
        return int3(_M_xyz[1], _M_xyz[2], _M_xyz[0]);
    }

    void set_yzx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) int3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) int3 brg;

    int3 get_zxy() const __GPU {
        return int3(_M_xyz[2], _M_xyz[0], _M_xyz[1]);
    }

    void set_zxy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) int3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) int3 bgr;

    int3 get_zyx() const __GPU {
        return int3(_M_xyz[2], _M_xyz[1], _M_xyz[0]);
    }

    void set_zyx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

};

/// <summary>
///    Represent a short vector of 4 int's.
/// </summary>
class int4
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
        return _M_xyzw[0];
    }

    void set_x(int _Value) __GPU
    {
        _M_xyzw[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) int y;
    __declspec( property( get = get_y, put = set_y) ) int g;

    int get_y() const __GPU {
        return _M_xyzw[1];
    }

    void set_y(int _Value) __GPU
    {
        _M_xyzw[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) int z;
    __declspec( property( get = get_z, put = set_z) ) int b;

    int get_z() const __GPU {
        return _M_xyzw[2];
    }

    void set_z(int _Value) __GPU
    {
        _M_xyzw[2] = _Value;
    }

    __declspec( property( get = get_w, put = set_w) ) int w;
    __declspec( property( get = get_w, put = set_w) ) int a;

    int get_w() const __GPU {
        return _M_xyzw[3];
    }

    void set_w(int _Value) __GPU
    {
        _M_xyzw[3] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    int4() __GPU
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
    int4(int _V0, int _V1, int _V2, int _V3) __GPU
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
    int4(int _V) __GPU
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
    explicit inline int4(const uint4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int4(const float4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int4(const unorm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int4(const norm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline int4(const double4& _Other) __GPU;

    int4 operator~() const __GPU
    {
        int4 _Value = *this;
        return int4(~_Value.x, ~_Value.y, ~_Value.z, ~_Value.w);
    }

    int4 operator-() const __GPU
    {
        int4 _Value = *this;
        return int4(-_Value.x, -_Value.y, -_Value.z, -_Value.w);
    }

    int4& operator++() __GPU
    {
        int4 _Value = *this;
        ++_Value._M_xyzw[0];
        ++_Value._M_xyzw[1];
        ++_Value._M_xyzw[2];
        ++_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    int4 operator++(int) __GPU
    {
        int4 _Result = *this;
        ++(*this);
        return _Result;
    }

    int4& operator--() __GPU
    {
        int4 _Value = *this;
        --_Value._M_xyzw[0];
        --_Value._M_xyzw[1];
        --_Value._M_xyzw[2];
        --_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    int4 operator--(int) __GPU
    {
        int4 _Result = *this;
        --(*this);
        return _Result;
    }

    int4& operator+=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        _Value1.w += _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator-=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        _Value1.w -= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator*=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        _Value1.w *= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator/=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        _Value1.w /= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator%=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x %= _Value2.x;
        _Value1.y %= _Value2.y;
        _Value1.z %= _Value2.z;
        _Value1.w %= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator^=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x ^= _Value2.x;
        _Value1.y ^= _Value2.y;
        _Value1.z ^= _Value2.z;
        _Value1.w ^= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator|=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x |= _Value2.x;
        _Value1.y |= _Value2.y;
        _Value1.z |= _Value2.z;
        _Value1.w |= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator&=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x &= _Value2.x;
        _Value1.y &= _Value2.y;
        _Value1.z &= _Value2.z;
        _Value1.w &= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator>>=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x >>= _Value2.x;
        _Value1.y >>= _Value2.y;
        _Value1.z >>= _Value2.z;
        _Value1.w >>= _Value2.w;
        *this = _Value1;
        return *this;
    }

    int4& operator<<=(const int4& _Other) __GPU
    {
        int4 _Value1 = *this;
        int4 _Value2 = _Other;
        _Value1.x <<= _Value2.x;
        _Value1.y <<= _Value2.y;
        _Value1.z <<= _Value2.z;
        _Value1.w <<= _Value2.w;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) int2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) int2 rg;

    int2 get_xy() const __GPU {
        return int2(_M_xyzw[0], _M_xyzw[1]);
    }

    void set_xy(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) int2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) int2 rb;

    int2 get_xz() const __GPU {
        return int2(_M_xyzw[0], _M_xyzw[2]);
    }

    void set_xz(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xw, put = set_xw) ) int2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) int2 ra;

    int2 get_xw() const __GPU {
        return int2(_M_xyzw[0], _M_xyzw[3]);
    }

    void set_xw(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) int2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) int2 gr;

    int2 get_yx() const __GPU {
        return int2(_M_xyzw[1], _M_xyzw[0]);
    }

    void set_yx(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) int2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) int2 gb;

    int2 get_yz() const __GPU {
        return int2(_M_xyzw[1], _M_xyzw[2]);
    }

    void set_yz(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_yw, put = set_yw) ) int2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) int2 ga;

    int2 get_yw() const __GPU {
        return int2(_M_xyzw[1], _M_xyzw[3]);
    }

    void set_yw(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) int2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) int2 br;

    int2 get_zx() const __GPU {
        return int2(_M_xyzw[2], _M_xyzw[0]);
    }

    void set_zx(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) int2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) int2 bg;

    int2 get_zy() const __GPU {
        return int2(_M_xyzw[2], _M_xyzw[1]);
    }

    void set_zy(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_zw, put = set_zw) ) int2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) int2 ba;

    int2 get_zw() const __GPU {
        return int2(_M_xyzw[2], _M_xyzw[3]);
    }

    void set_zw(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_wx, put = set_wx) ) int2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) int2 ar;

    int2 get_wx() const __GPU {
        return int2(_M_xyzw[3], _M_xyzw[0]);
    }

    void set_wx(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_wy, put = set_wy) ) int2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) int2 ag;

    int2 get_wy() const __GPU {
        return int2(_M_xyzw[3], _M_xyzw[1]);
    }

    void set_wy(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_wz, put = set_wz) ) int2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) int2 ab;

    int2 get_wz() const __GPU {
        return int2(_M_xyzw[3], _M_xyzw[2]);
    }

    void set_wz(const int2& _Value) __GPU
    {
        int2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) int3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) int3 rgb;

    int3 get_xyz() const __GPU {
        return int3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xyz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) int3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) int3 rga;

    int3 get_xyw() const __GPU {
        return int3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xyw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) int3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) int3 rbg;

    int3 get_xzy() const __GPU {
        return int3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xzy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) int3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) int3 rba;

    int3 get_xzw() const __GPU {
        return int3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xzw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) int3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) int3 rag;

    int3 get_xwy() const __GPU {
        return int3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xwy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) int3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) int3 rab;

    int3 get_xwz() const __GPU {
        return int3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xwz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) int3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) int3 grb;

    int3 get_yxz() const __GPU {
        return int3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_yxz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) int3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) int3 gra;

    int3 get_yxw() const __GPU {
        return int3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yxw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) int3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) int3 gbr;

    int3 get_yzx() const __GPU {
        return int3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_yzx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) int3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) int3 gba;

    int3 get_yzw() const __GPU {
        return int3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yzw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) int3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) int3 gar;

    int3 get_ywx() const __GPU {
        return int3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_ywx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) int3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) int3 gab;

    int3 get_ywz() const __GPU {
        return int3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_ywz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) int3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) int3 brg;

    int3 get_zxy() const __GPU {
        return int3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zxy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) int3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) int3 bra;

    int3 get_zxw() const __GPU {
        return int3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zxw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) int3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) int3 bgr;

    int3 get_zyx() const __GPU {
        return int3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zyx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) int3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) int3 bga;

    int3 get_zyw() const __GPU {
        return int3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zyw(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) int3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) int3 bar;

    int3 get_zwx() const __GPU {
        return int3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zwx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) int3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) int3 bag;

    int3 get_zwy() const __GPU {
        return int3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zwy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) int3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) int3 arg;

    int3 get_wxy() const __GPU {
        return int3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wxy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) int3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) int3 arb;

    int3 get_wxz() const __GPU {
        return int3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wxz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) int3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) int3 agr;

    int3 get_wyx() const __GPU {
        return int3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wyx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) int3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) int3 agb;

    int3 get_wyz() const __GPU {
        return int3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wyz(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) int3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) int3 abr;

    int3 get_wzx() const __GPU {
        return int3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wzx(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) int3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) int3 abg;

    int3 get_wzy() const __GPU {
        return int3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wzy(const int3& _Value) __GPU
    {
        int3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) int4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) int4 rgba;

    int4 get_xyzw() const __GPU {
        return int4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xyzw(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) int4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) int4 rgab;

    int4 get_xywz() const __GPU {
        return int4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xywz(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) int4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) int4 rbga;

    int4 get_xzyw() const __GPU {
        return int4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xzyw(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) int4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) int4 rbag;

    int4 get_xzwy() const __GPU {
        return int4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xzwy(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) int4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) int4 ragb;

    int4 get_xwyz() const __GPU {
        return int4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xwyz(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) int4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) int4 rabg;

    int4 get_xwzy() const __GPU {
        return int4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xwzy(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) int4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) int4 grba;

    int4 get_yxzw() const __GPU {
        return int4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yxzw(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) int4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) int4 grab;

    int4 get_yxwz() const __GPU {
        return int4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_yxwz(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) int4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) int4 gbra;

    int4 get_yzxw() const __GPU {
        return int4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yzxw(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) int4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) int4 gbar;

    int4 get_yzwx() const __GPU {
        return int4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_yzwx(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) int4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) int4 garb;

    int4 get_ywxz() const __GPU {
        return int4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_ywxz(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) int4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) int4 gabr;

    int4 get_ywzx() const __GPU {
        return int4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_ywzx(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) int4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) int4 brga;

    int4 get_zxyw() const __GPU {
        return int4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zxyw(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) int4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) int4 brag;

    int4 get_zxwy() const __GPU {
        return int4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zxwy(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) int4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) int4 bgra;

    int4 get_zyxw() const __GPU {
        return int4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zyxw(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) int4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) int4 bgar;

    int4 get_zywx() const __GPU {
        return int4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zywx(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) int4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) int4 barg;

    int4 get_zwxy() const __GPU {
        return int4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zwxy(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) int4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) int4 bagr;

    int4 get_zwyx() const __GPU {
        return int4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zwyx(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) int4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) int4 argb;

    int4 get_wxyz() const __GPU {
        return int4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wxyz(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) int4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) int4 arbg;

    int4 get_wxzy() const __GPU {
        return int4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wxzy(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) int4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) int4 agrb;

    int4 get_wyxz() const __GPU {
        return int4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wyxz(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) int4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) int4 agbr;

    int4 get_wyzx() const __GPU {
        return int4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wyzx(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) int4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) int4 abrg;

    int4 get_wzxy() const __GPU {
        return int4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wzxy(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) int4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) int4 abgr;

    int4 get_wzyx() const __GPU {
        return int4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wzyx(const int4& _Value) __GPU
    {
        int4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

};

/// <summary>
///    Represent a short vector of 2 float's.
/// </summary>
class float2
{
public:
    typedef float value_type;
    static const int size = 2;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Float_type;
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

    __declspec( property( get = get_x, put = set_x) ) float x;
    __declspec( property( get = get_x, put = set_x) ) float r;

    float get_x() const __GPU {
        return _M_xy[0];
    }

    void set_x(float _Value) __GPU
    {
        _M_xy[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) float y;
    __declspec( property( get = get_y, put = set_y) ) float g;

    float get_y() const __GPU {
        return _M_xy[1];
    }

    void set_y(float _Value) __GPU
    {
        _M_xy[1] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    float2() __GPU
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
    float2(float _V0, float _V1) __GPU
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
    float2(float _V) __GPU
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
    explicit inline float2(const uint2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float2(const int2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float2(const unorm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float2(const norm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float2(const double2& _Other) __GPU;

    float2 operator-() const __GPU
    {
        float2 _Value = *this;
        return float2(-_Value.x, -_Value.y);
    }

    float2& operator++() __GPU
    {
        float2 _Value = *this;
        ++_Value._M_xy[0];
        ++_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    float2 operator++(int) __GPU
    {
        float2 _Result = *this;
        ++(*this);
        return _Result;
    }

    float2& operator--() __GPU
    {
        float2 _Value = *this;
        --_Value._M_xy[0];
        --_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    float2 operator--(int) __GPU
    {
        float2 _Result = *this;
        --(*this);
        return _Result;
    }

    float2& operator+=(const float2& _Other) __GPU
    {
        float2 _Value1 = *this;
        float2 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        *this = _Value1;
        return *this;
    }

    float2& operator-=(const float2& _Other) __GPU
    {
        float2 _Value1 = *this;
        float2 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        *this = _Value1;
        return *this;
    }

    float2& operator*=(const float2& _Other) __GPU
    {
        float2 _Value1 = *this;
        float2 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        *this = _Value1;
        return *this;
    }

    float2& operator/=(const float2& _Other) __GPU
    {
        float2 _Value1 = *this;
        float2 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) float2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) float2 rg;

    float2 get_xy() const __GPU {
        return float2(_M_xy[0], _M_xy[1]);
    }

    void set_xy(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xy[0] = _Val.x;
        _M_xy[1] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) float2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) float2 gr;

    float2 get_yx() const __GPU {
        return float2(_M_xy[1], _M_xy[0]);
    }

    void set_yx(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xy[1] = _Val.x;
        _M_xy[0] = _Val.y;
    }

};

/// <summary>
///    Represent a short vector of 3 float's.
/// </summary>
class float3
{
public:
    typedef float value_type;
    static const int size = 3;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Float_type;
private:
    value_type _M_xyz[3];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xyz[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xyz[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) float x;
    __declspec( property( get = get_x, put = set_x) ) float r;

    float get_x() const __GPU {
        return _M_xyz[0];
    }

    void set_x(float _Value) __GPU
    {
        _M_xyz[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) float y;
    __declspec( property( get = get_y, put = set_y) ) float g;

    float get_y() const __GPU {
        return _M_xyz[1];
    }

    void set_y(float _Value) __GPU
    {
        _M_xyz[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) float z;
    __declspec( property( get = get_z, put = set_z) ) float b;

    float get_z() const __GPU {
        return _M_xyz[2];
    }

    void set_z(float _Value) __GPU
    {
        _M_xyz[2] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    float3() __GPU
    {
        _M_xyz[0] = 0;
        _M_xyz[1] = 0;
        _M_xyz[2] = 0;
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
    float3(float _V0, float _V1, float _V2) __GPU
    {
        _M_xyz[0] = _V0;
        _M_xyz[1] = _V1;
        _M_xyz[2] = _V2;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    float3(float _V) __GPU
    {
        _M_xyz[0] = _V;
        _M_xyz[1] = _V;
        _M_xyz[2] = _V;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float3(const uint3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float3(const int3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float3(const unorm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float3(const norm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float3(const double3& _Other) __GPU;

    float3 operator-() const __GPU
    {
        float3 _Value = *this;
        return float3(-_Value.x, -_Value.y, -_Value.z);
    }

    float3& operator++() __GPU
    {
        float3 _Value = *this;
        ++_Value._M_xyz[0];
        ++_Value._M_xyz[1];
        ++_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    float3 operator++(int) __GPU
    {
        float3 _Result = *this;
        ++(*this);
        return _Result;
    }

    float3& operator--() __GPU
    {
        float3 _Value = *this;
        --_Value._M_xyz[0];
        --_Value._M_xyz[1];
        --_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    float3 operator--(int) __GPU
    {
        float3 _Result = *this;
        --(*this);
        return _Result;
    }

    float3& operator+=(const float3& _Other) __GPU
    {
        float3 _Value1 = *this;
        float3 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        *this = _Value1;
        return *this;
    }

    float3& operator-=(const float3& _Other) __GPU
    {
        float3 _Value1 = *this;
        float3 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        *this = _Value1;
        return *this;
    }

    float3& operator*=(const float3& _Other) __GPU
    {
        float3 _Value1 = *this;
        float3 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        *this = _Value1;
        return *this;
    }

    float3& operator/=(const float3& _Other) __GPU
    {
        float3 _Value1 = *this;
        float3 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) float2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) float2 rg;

    float2 get_xy() const __GPU {
        return float2(_M_xyz[0], _M_xyz[1]);
    }

    void set_xy(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) float2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) float2 rb;

    float2 get_xz() const __GPU {
        return float2(_M_xyz[0], _M_xyz[2]);
    }

    void set_xz(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) float2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) float2 gr;

    float2 get_yx() const __GPU {
        return float2(_M_xyz[1], _M_xyz[0]);
    }

    void set_yx(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) float2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) float2 gb;

    float2 get_yz() const __GPU {
        return float2(_M_xyz[1], _M_xyz[2]);
    }

    void set_yz(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) float2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) float2 br;

    float2 get_zx() const __GPU {
        return float2(_M_xyz[2], _M_xyz[0]);
    }

    void set_zx(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) float2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) float2 bg;

    float2 get_zy() const __GPU {
        return float2(_M_xyz[2], _M_xyz[1]);
    }

    void set_zy(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) float3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) float3 rgb;

    float3 get_xyz() const __GPU {
        return float3(_M_xyz[0], _M_xyz[1], _M_xyz[2]);
    }

    void set_xyz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) float3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) float3 rbg;

    float3 get_xzy() const __GPU {
        return float3(_M_xyz[0], _M_xyz[2], _M_xyz[1]);
    }

    void set_xzy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) float3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) float3 grb;

    float3 get_yxz() const __GPU {
        return float3(_M_xyz[1], _M_xyz[0], _M_xyz[2]);
    }

    void set_yxz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) float3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) float3 gbr;

    float3 get_yzx() const __GPU {
        return float3(_M_xyz[1], _M_xyz[2], _M_xyz[0]);
    }

    void set_yzx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) float3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) float3 brg;

    float3 get_zxy() const __GPU {
        return float3(_M_xyz[2], _M_xyz[0], _M_xyz[1]);
    }

    void set_zxy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) float3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) float3 bgr;

    float3 get_zyx() const __GPU {
        return float3(_M_xyz[2], _M_xyz[1], _M_xyz[0]);
    }

    void set_zyx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

};

/// <summary>
///    Represent a short vector of 4 float's.
/// </summary>
class float4
{
public:
    typedef float value_type;
    static const int size = 4;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Float_type;
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

    __declspec( property( get = get_x, put = set_x) ) float x;
    __declspec( property( get = get_x, put = set_x) ) float r;

    float get_x() const __GPU {
        return _M_xyzw[0];
    }

    void set_x(float _Value) __GPU
    {
        _M_xyzw[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) float y;
    __declspec( property( get = get_y, put = set_y) ) float g;

    float get_y() const __GPU {
        return _M_xyzw[1];
    }

    void set_y(float _Value) __GPU
    {
        _M_xyzw[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) float z;
    __declspec( property( get = get_z, put = set_z) ) float b;

    float get_z() const __GPU {
        return _M_xyzw[2];
    }

    void set_z(float _Value) __GPU
    {
        _M_xyzw[2] = _Value;
    }

    __declspec( property( get = get_w, put = set_w) ) float w;
    __declspec( property( get = get_w, put = set_w) ) float a;

    float get_w() const __GPU {
        return _M_xyzw[3];
    }

    void set_w(float _Value) __GPU
    {
        _M_xyzw[3] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    float4() __GPU
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
    float4(float _V0, float _V1, float _V2, float _V3) __GPU
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
    float4(float _V) __GPU
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
    explicit inline float4(const uint4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float4(const int4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float4(const unorm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float4(const norm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline float4(const double4& _Other) __GPU;

    float4 operator-() const __GPU
    {
        float4 _Value = *this;
        return float4(-_Value.x, -_Value.y, -_Value.z, -_Value.w);
    }

    float4& operator++() __GPU
    {
        float4 _Value = *this;
        ++_Value._M_xyzw[0];
        ++_Value._M_xyzw[1];
        ++_Value._M_xyzw[2];
        ++_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    float4 operator++(int) __GPU
    {
        float4 _Result = *this;
        ++(*this);
        return _Result;
    }

    float4& operator--() __GPU
    {
        float4 _Value = *this;
        --_Value._M_xyzw[0];
        --_Value._M_xyzw[1];
        --_Value._M_xyzw[2];
        --_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    float4 operator--(int) __GPU
    {
        float4 _Result = *this;
        --(*this);
        return _Result;
    }

    float4& operator+=(const float4& _Other) __GPU
    {
        float4 _Value1 = *this;
        float4 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        _Value1.w += _Value2.w;
        *this = _Value1;
        return *this;
    }

    float4& operator-=(const float4& _Other) __GPU
    {
        float4 _Value1 = *this;
        float4 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        _Value1.w -= _Value2.w;
        *this = _Value1;
        return *this;
    }

    float4& operator*=(const float4& _Other) __GPU
    {
        float4 _Value1 = *this;
        float4 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        _Value1.w *= _Value2.w;
        *this = _Value1;
        return *this;
    }

    float4& operator/=(const float4& _Other) __GPU
    {
        float4 _Value1 = *this;
        float4 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        _Value1.w /= _Value2.w;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) float2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) float2 rg;

    float2 get_xy() const __GPU {
        return float2(_M_xyzw[0], _M_xyzw[1]);
    }

    void set_xy(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) float2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) float2 rb;

    float2 get_xz() const __GPU {
        return float2(_M_xyzw[0], _M_xyzw[2]);
    }

    void set_xz(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xw, put = set_xw) ) float2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) float2 ra;

    float2 get_xw() const __GPU {
        return float2(_M_xyzw[0], _M_xyzw[3]);
    }

    void set_xw(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) float2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) float2 gr;

    float2 get_yx() const __GPU {
        return float2(_M_xyzw[1], _M_xyzw[0]);
    }

    void set_yx(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) float2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) float2 gb;

    float2 get_yz() const __GPU {
        return float2(_M_xyzw[1], _M_xyzw[2]);
    }

    void set_yz(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_yw, put = set_yw) ) float2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) float2 ga;

    float2 get_yw() const __GPU {
        return float2(_M_xyzw[1], _M_xyzw[3]);
    }

    void set_yw(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) float2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) float2 br;

    float2 get_zx() const __GPU {
        return float2(_M_xyzw[2], _M_xyzw[0]);
    }

    void set_zx(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) float2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) float2 bg;

    float2 get_zy() const __GPU {
        return float2(_M_xyzw[2], _M_xyzw[1]);
    }

    void set_zy(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_zw, put = set_zw) ) float2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) float2 ba;

    float2 get_zw() const __GPU {
        return float2(_M_xyzw[2], _M_xyzw[3]);
    }

    void set_zw(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_wx, put = set_wx) ) float2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) float2 ar;

    float2 get_wx() const __GPU {
        return float2(_M_xyzw[3], _M_xyzw[0]);
    }

    void set_wx(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_wy, put = set_wy) ) float2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) float2 ag;

    float2 get_wy() const __GPU {
        return float2(_M_xyzw[3], _M_xyzw[1]);
    }

    void set_wy(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_wz, put = set_wz) ) float2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) float2 ab;

    float2 get_wz() const __GPU {
        return float2(_M_xyzw[3], _M_xyzw[2]);
    }

    void set_wz(const float2& _Value) __GPU
    {
        float2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) float3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) float3 rgb;

    float3 get_xyz() const __GPU {
        return float3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xyz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) float3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) float3 rga;

    float3 get_xyw() const __GPU {
        return float3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xyw(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) float3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) float3 rbg;

    float3 get_xzy() const __GPU {
        return float3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xzy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) float3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) float3 rba;

    float3 get_xzw() const __GPU {
        return float3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xzw(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) float3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) float3 rag;

    float3 get_xwy() const __GPU {
        return float3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xwy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) float3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) float3 rab;

    float3 get_xwz() const __GPU {
        return float3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xwz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) float3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) float3 grb;

    float3 get_yxz() const __GPU {
        return float3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_yxz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) float3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) float3 gra;

    float3 get_yxw() const __GPU {
        return float3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yxw(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) float3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) float3 gbr;

    float3 get_yzx() const __GPU {
        return float3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_yzx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) float3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) float3 gba;

    float3 get_yzw() const __GPU {
        return float3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yzw(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) float3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) float3 gar;

    float3 get_ywx() const __GPU {
        return float3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_ywx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) float3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) float3 gab;

    float3 get_ywz() const __GPU {
        return float3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_ywz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) float3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) float3 brg;

    float3 get_zxy() const __GPU {
        return float3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zxy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) float3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) float3 bra;

    float3 get_zxw() const __GPU {
        return float3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zxw(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) float3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) float3 bgr;

    float3 get_zyx() const __GPU {
        return float3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zyx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) float3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) float3 bga;

    float3 get_zyw() const __GPU {
        return float3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zyw(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) float3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) float3 bar;

    float3 get_zwx() const __GPU {
        return float3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zwx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) float3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) float3 bag;

    float3 get_zwy() const __GPU {
        return float3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zwy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) float3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) float3 arg;

    float3 get_wxy() const __GPU {
        return float3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wxy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) float3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) float3 arb;

    float3 get_wxz() const __GPU {
        return float3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wxz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) float3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) float3 agr;

    float3 get_wyx() const __GPU {
        return float3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wyx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) float3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) float3 agb;

    float3 get_wyz() const __GPU {
        return float3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wyz(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) float3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) float3 abr;

    float3 get_wzx() const __GPU {
        return float3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wzx(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) float3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) float3 abg;

    float3 get_wzy() const __GPU {
        return float3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wzy(const float3& _Value) __GPU
    {
        float3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) float4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) float4 rgba;

    float4 get_xyzw() const __GPU {
        return float4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xyzw(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) float4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) float4 rgab;

    float4 get_xywz() const __GPU {
        return float4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xywz(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) float4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) float4 rbga;

    float4 get_xzyw() const __GPU {
        return float4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xzyw(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) float4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) float4 rbag;

    float4 get_xzwy() const __GPU {
        return float4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xzwy(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) float4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) float4 ragb;

    float4 get_xwyz() const __GPU {
        return float4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xwyz(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) float4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) float4 rabg;

    float4 get_xwzy() const __GPU {
        return float4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xwzy(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) float4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) float4 grba;

    float4 get_yxzw() const __GPU {
        return float4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yxzw(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) float4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) float4 grab;

    float4 get_yxwz() const __GPU {
        return float4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_yxwz(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) float4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) float4 gbra;

    float4 get_yzxw() const __GPU {
        return float4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yzxw(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) float4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) float4 gbar;

    float4 get_yzwx() const __GPU {
        return float4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_yzwx(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) float4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) float4 garb;

    float4 get_ywxz() const __GPU {
        return float4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_ywxz(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) float4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) float4 gabr;

    float4 get_ywzx() const __GPU {
        return float4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_ywzx(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) float4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) float4 brga;

    float4 get_zxyw() const __GPU {
        return float4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zxyw(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) float4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) float4 brag;

    float4 get_zxwy() const __GPU {
        return float4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zxwy(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) float4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) float4 bgra;

    float4 get_zyxw() const __GPU {
        return float4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zyxw(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) float4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) float4 bgar;

    float4 get_zywx() const __GPU {
        return float4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zywx(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) float4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) float4 barg;

    float4 get_zwxy() const __GPU {
        return float4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zwxy(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) float4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) float4 bagr;

    float4 get_zwyx() const __GPU {
        return float4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zwyx(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) float4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) float4 argb;

    float4 get_wxyz() const __GPU {
        return float4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wxyz(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) float4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) float4 arbg;

    float4 get_wxzy() const __GPU {
        return float4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wxzy(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) float4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) float4 agrb;

    float4 get_wyxz() const __GPU {
        return float4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wyxz(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) float4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) float4 agbr;

    float4 get_wyzx() const __GPU {
        return float4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wyzx(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) float4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) float4 abrg;

    float4 get_wzxy() const __GPU {
        return float4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wzxy(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) float4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) float4 abgr;

    float4 get_wzyx() const __GPU {
        return float4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wzyx(const float4& _Value) __GPU
    {
        float4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

};

/// <summary>
///    Represent a short vector of 2 unorm's.
/// </summary>
class unorm2
{
public:
    typedef unorm value_type;
    static const int size = 2;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Unorm_type;
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

    __declspec( property( get = get_x, put = set_x) ) unorm x;
    __declspec( property( get = get_x, put = set_x) ) unorm r;

    unorm get_x() const __GPU {
        return _M_xy[0];
    }

    void set_x(unorm _Value) __GPU
    {
        _M_xy[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) unorm y;
    __declspec( property( get = get_y, put = set_y) ) unorm g;

    unorm get_y() const __GPU {
        return _M_xy[1];
    }

    void set_y(unorm _Value) __GPU
    {
        _M_xy[1] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    unorm2() __GPU
    {
        _M_xy[0] = unorm(0.0f);
        _M_xy[1] = unorm(0.0f);
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
    unorm2(unorm _V0, unorm _V1) __GPU
    {
        _M_xy[0] = _V0;
        _M_xy[1] = _V1;
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
    unorm2(float _V0, float _V1) __GPU
    {
        _M_xy[0] = unorm(_V0);
        _M_xy[1] = unorm(_V1);
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    unorm2(unorm _V) __GPU
    {
        _M_xy[0] = _V;
        _M_xy[1] = _V;
    }

    explicit unorm2(float _V) __GPU
    {
        _M_xy[0] = unorm(_V);
        _M_xy[1] = unorm(_V);
    }

    /// <summary>
    ///     Copy constructor.
    /// </summary>
    /// <param name="_Other">
    ///     The object to copy from.
    /// </param>
    unorm2(const unorm2& _Other) __GPU
    {
        *this = _Other;
    }

    unorm2& operator=(const unorm2& _Other) __GPU
    {
        _M_xy[0] = _Other._M_xy[0];
        _M_xy[1] = _Other._M_xy[1];
        return *this;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm2(const uint2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm2(const int2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm2(const float2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm2(const norm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm2(const double2& _Other) __GPU;

    unorm2& operator++() __GPU
    {
        unorm2 _Value = *this;
        ++_Value._M_xy[0];
        ++_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    unorm2 operator++(int) __GPU
    {
        unorm2 _Result = *this;
        ++(*this);
        return _Result;
    }

    unorm2& operator--() __GPU
    {
        unorm2 _Value = *this;
        --_Value._M_xy[0];
        --_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    unorm2 operator--(int) __GPU
    {
        unorm2 _Result = *this;
        --(*this);
        return _Result;
    }

    unorm2& operator+=(const unorm2& _Other) __GPU
    {
        unorm2 _Value1 = *this;
        unorm2 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        *this = _Value1;
        return *this;
    }

    unorm2& operator-=(const unorm2& _Other) __GPU
    {
        unorm2 _Value1 = *this;
        unorm2 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        *this = _Value1;
        return *this;
    }

    unorm2& operator*=(const unorm2& _Other) __GPU
    {
        unorm2 _Value1 = *this;
        unorm2 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        *this = _Value1;
        return *this;
    }

    unorm2& operator/=(const unorm2& _Other) __GPU
    {
        unorm2 _Value1 = *this;
        unorm2 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) unorm2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) unorm2 rg;

    unorm2 get_xy() const __GPU {
        return unorm2(_M_xy[0], _M_xy[1]);
    }

    void set_xy(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xy[0] = _Val.x;
        _M_xy[1] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) unorm2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) unorm2 gr;

    unorm2 get_yx() const __GPU {
        return unorm2(_M_xy[1], _M_xy[0]);
    }

    void set_yx(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xy[1] = _Val.x;
        _M_xy[0] = _Val.y;
    }

};

/// <summary>
///    Represent a short vector of 3 unorm's.
/// </summary>
class unorm3
{
public:
    typedef unorm value_type;
    static const int size = 3;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Unorm_type;
private:
    value_type _M_xyz[3];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xyz[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xyz[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) unorm x;
    __declspec( property( get = get_x, put = set_x) ) unorm r;

    unorm get_x() const __GPU {
        return _M_xyz[0];
    }

    void set_x(unorm _Value) __GPU
    {
        _M_xyz[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) unorm y;
    __declspec( property( get = get_y, put = set_y) ) unorm g;

    unorm get_y() const __GPU {
        return _M_xyz[1];
    }

    void set_y(unorm _Value) __GPU
    {
        _M_xyz[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) unorm z;
    __declspec( property( get = get_z, put = set_z) ) unorm b;

    unorm get_z() const __GPU {
        return _M_xyz[2];
    }

    void set_z(unorm _Value) __GPU
    {
        _M_xyz[2] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    unorm3() __GPU
    {
        _M_xyz[0] = unorm(0.0f);
        _M_xyz[1] = unorm(0.0f);
        _M_xyz[2] = unorm(0.0f);
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
    unorm3(unorm _V0, unorm _V1, unorm _V2) __GPU
    {
        _M_xyz[0] = _V0;
        _M_xyz[1] = _V1;
        _M_xyz[2] = _V2;
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
    unorm3(float _V0, float _V1, float _V2) __GPU
    {
        _M_xyz[0] = unorm(_V0);
        _M_xyz[1] = unorm(_V1);
        _M_xyz[2] = unorm(_V2);
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    unorm3(unorm _V) __GPU
    {
        _M_xyz[0] = _V;
        _M_xyz[1] = _V;
        _M_xyz[2] = _V;
    }

    explicit unorm3(float _V) __GPU
    {
        _M_xyz[0] = unorm(_V);
        _M_xyz[1] = unorm(_V);
        _M_xyz[2] = unorm(_V);
    }

    /// <summary>
    ///     Copy constructor.
    /// </summary>
    /// <param name="_Other">
    ///     The object to copy from.
    /// </param>
    unorm3(const unorm3& _Other) __GPU
    {
        *this = _Other;
    }

    unorm3& operator=(const unorm3& _Other) __GPU
    {
        _M_xyz[0] = _Other._M_xyz[0];
        _M_xyz[1] = _Other._M_xyz[1];
        _M_xyz[2] = _Other._M_xyz[2];
        return *this;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm3(const uint3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm3(const int3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm3(const float3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm3(const norm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm3(const double3& _Other) __GPU;

    unorm3& operator++() __GPU
    {
        unorm3 _Value = *this;
        ++_Value._M_xyz[0];
        ++_Value._M_xyz[1];
        ++_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    unorm3 operator++(int) __GPU
    {
        unorm3 _Result = *this;
        ++(*this);
        return _Result;
    }

    unorm3& operator--() __GPU
    {
        unorm3 _Value = *this;
        --_Value._M_xyz[0];
        --_Value._M_xyz[1];
        --_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    unorm3 operator--(int) __GPU
    {
        unorm3 _Result = *this;
        --(*this);
        return _Result;
    }

    unorm3& operator+=(const unorm3& _Other) __GPU
    {
        unorm3 _Value1 = *this;
        unorm3 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        *this = _Value1;
        return *this;
    }

    unorm3& operator-=(const unorm3& _Other) __GPU
    {
        unorm3 _Value1 = *this;
        unorm3 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        *this = _Value1;
        return *this;
    }

    unorm3& operator*=(const unorm3& _Other) __GPU
    {
        unorm3 _Value1 = *this;
        unorm3 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        *this = _Value1;
        return *this;
    }

    unorm3& operator/=(const unorm3& _Other) __GPU
    {
        unorm3 _Value1 = *this;
        unorm3 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) unorm2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) unorm2 rg;

    unorm2 get_xy() const __GPU {
        return unorm2(_M_xyz[0], _M_xyz[1]);
    }

    void set_xy(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) unorm2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) unorm2 rb;

    unorm2 get_xz() const __GPU {
        return unorm2(_M_xyz[0], _M_xyz[2]);
    }

    void set_xz(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) unorm2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) unorm2 gr;

    unorm2 get_yx() const __GPU {
        return unorm2(_M_xyz[1], _M_xyz[0]);
    }

    void set_yx(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) unorm2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) unorm2 gb;

    unorm2 get_yz() const __GPU {
        return unorm2(_M_xyz[1], _M_xyz[2]);
    }

    void set_yz(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) unorm2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) unorm2 br;

    unorm2 get_zx() const __GPU {
        return unorm2(_M_xyz[2], _M_xyz[0]);
    }

    void set_zx(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) unorm2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) unorm2 bg;

    unorm2 get_zy() const __GPU {
        return unorm2(_M_xyz[2], _M_xyz[1]);
    }

    void set_zy(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) unorm3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) unorm3 rgb;

    unorm3 get_xyz() const __GPU {
        return unorm3(_M_xyz[0], _M_xyz[1], _M_xyz[2]);
    }

    void set_xyz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) unorm3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) unorm3 rbg;

    unorm3 get_xzy() const __GPU {
        return unorm3(_M_xyz[0], _M_xyz[2], _M_xyz[1]);
    }

    void set_xzy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) unorm3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) unorm3 grb;

    unorm3 get_yxz() const __GPU {
        return unorm3(_M_xyz[1], _M_xyz[0], _M_xyz[2]);
    }

    void set_yxz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) unorm3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) unorm3 gbr;

    unorm3 get_yzx() const __GPU {
        return unorm3(_M_xyz[1], _M_xyz[2], _M_xyz[0]);
    }

    void set_yzx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) unorm3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) unorm3 brg;

    unorm3 get_zxy() const __GPU {
        return unorm3(_M_xyz[2], _M_xyz[0], _M_xyz[1]);
    }

    void set_zxy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) unorm3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) unorm3 bgr;

    unorm3 get_zyx() const __GPU {
        return unorm3(_M_xyz[2], _M_xyz[1], _M_xyz[0]);
    }

    void set_zyx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

};

/// <summary>
///    Represent a short vector of 4 unorm's.
/// </summary>
class unorm4
{
public:
    typedef unorm value_type;
    static const int size = 4;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Unorm_type;
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

    __declspec( property( get = get_x, put = set_x) ) unorm x;
    __declspec( property( get = get_x, put = set_x) ) unorm r;

    unorm get_x() const __GPU {
        return _M_xyzw[0];
    }

    void set_x(unorm _Value) __GPU
    {
        _M_xyzw[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) unorm y;
    __declspec( property( get = get_y, put = set_y) ) unorm g;

    unorm get_y() const __GPU {
        return _M_xyzw[1];
    }

    void set_y(unorm _Value) __GPU
    {
        _M_xyzw[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) unorm z;
    __declspec( property( get = get_z, put = set_z) ) unorm b;

    unorm get_z() const __GPU {
        return _M_xyzw[2];
    }

    void set_z(unorm _Value) __GPU
    {
        _M_xyzw[2] = _Value;
    }

    __declspec( property( get = get_w, put = set_w) ) unorm w;
    __declspec( property( get = get_w, put = set_w) ) unorm a;

    unorm get_w() const __GPU {
        return _M_xyzw[3];
    }

    void set_w(unorm _Value) __GPU
    {
        _M_xyzw[3] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    unorm4() __GPU
    {
        _M_xyzw[0] = unorm(0.0f);
        _M_xyzw[1] = unorm(0.0f);
        _M_xyzw[2] = unorm(0.0f);
        _M_xyzw[3] = unorm(0.0f);
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
    unorm4(unorm _V0, unorm _V1, unorm _V2, unorm _V3) __GPU
    {
        _M_xyzw[0] = _V0;
        _M_xyzw[1] = _V1;
        _M_xyzw[2] = _V2;
        _M_xyzw[3] = _V3;
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
    unorm4(float _V0, float _V1, float _V2, float _V3) __GPU
    {
        _M_xyzw[0] = unorm(_V0);
        _M_xyzw[1] = unorm(_V1);
        _M_xyzw[2] = unorm(_V2);
        _M_xyzw[3] = unorm(_V3);
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    unorm4(unorm _V) __GPU
    {
        _M_xyzw[0] = _V;
        _M_xyzw[1] = _V;
        _M_xyzw[2] = _V;
        _M_xyzw[3] = _V;
    }

    explicit unorm4(float _V) __GPU
    {
        _M_xyzw[0] = unorm(_V);
        _M_xyzw[1] = unorm(_V);
        _M_xyzw[2] = unorm(_V);
        _M_xyzw[3] = unorm(_V);
    }

    /// <summary>
    ///     Copy constructor.
    /// </summary>
    /// <param name="_Other">
    ///     The object to copy from.
    /// </param>
    unorm4(const unorm4& _Other) __GPU
    {
        *this = _Other;
    }

    unorm4& operator=(const unorm4& _Other) __GPU
    {
        _M_xyzw[0] = _Other._M_xyzw[0];
        _M_xyzw[1] = _Other._M_xyzw[1];
        _M_xyzw[2] = _Other._M_xyzw[2];
        _M_xyzw[3] = _Other._M_xyzw[3];
        return *this;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm4(const uint4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm4(const int4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm4(const float4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm4(const norm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline unorm4(const double4& _Other) __GPU;

    unorm4& operator++() __GPU
    {
        unorm4 _Value = *this;
        ++_Value._M_xyzw[0];
        ++_Value._M_xyzw[1];
        ++_Value._M_xyzw[2];
        ++_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    unorm4 operator++(int) __GPU
    {
        unorm4 _Result = *this;
        ++(*this);
        return _Result;
    }

    unorm4& operator--() __GPU
    {
        unorm4 _Value = *this;
        --_Value._M_xyzw[0];
        --_Value._M_xyzw[1];
        --_Value._M_xyzw[2];
        --_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    unorm4 operator--(int) __GPU
    {
        unorm4 _Result = *this;
        --(*this);
        return _Result;
    }

    unorm4& operator+=(const unorm4& _Other) __GPU
    {
        unorm4 _Value1 = *this;
        unorm4 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        _Value1.w += _Value2.w;
        *this = _Value1;
        return *this;
    }

    unorm4& operator-=(const unorm4& _Other) __GPU
    {
        unorm4 _Value1 = *this;
        unorm4 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        _Value1.w -= _Value2.w;
        *this = _Value1;
        return *this;
    }

    unorm4& operator*=(const unorm4& _Other) __GPU
    {
        unorm4 _Value1 = *this;
        unorm4 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        _Value1.w *= _Value2.w;
        *this = _Value1;
        return *this;
    }

    unorm4& operator/=(const unorm4& _Other) __GPU
    {
        unorm4 _Value1 = *this;
        unorm4 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        _Value1.w /= _Value2.w;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) unorm2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) unorm2 rg;

    unorm2 get_xy() const __GPU {
        return unorm2(_M_xyzw[0], _M_xyzw[1]);
    }

    void set_xy(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) unorm2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) unorm2 rb;

    unorm2 get_xz() const __GPU {
        return unorm2(_M_xyzw[0], _M_xyzw[2]);
    }

    void set_xz(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xw, put = set_xw) ) unorm2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) unorm2 ra;

    unorm2 get_xw() const __GPU {
        return unorm2(_M_xyzw[0], _M_xyzw[3]);
    }

    void set_xw(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) unorm2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) unorm2 gr;

    unorm2 get_yx() const __GPU {
        return unorm2(_M_xyzw[1], _M_xyzw[0]);
    }

    void set_yx(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) unorm2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) unorm2 gb;

    unorm2 get_yz() const __GPU {
        return unorm2(_M_xyzw[1], _M_xyzw[2]);
    }

    void set_yz(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_yw, put = set_yw) ) unorm2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) unorm2 ga;

    unorm2 get_yw() const __GPU {
        return unorm2(_M_xyzw[1], _M_xyzw[3]);
    }

    void set_yw(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) unorm2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) unorm2 br;

    unorm2 get_zx() const __GPU {
        return unorm2(_M_xyzw[2], _M_xyzw[0]);
    }

    void set_zx(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) unorm2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) unorm2 bg;

    unorm2 get_zy() const __GPU {
        return unorm2(_M_xyzw[2], _M_xyzw[1]);
    }

    void set_zy(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_zw, put = set_zw) ) unorm2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) unorm2 ba;

    unorm2 get_zw() const __GPU {
        return unorm2(_M_xyzw[2], _M_xyzw[3]);
    }

    void set_zw(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_wx, put = set_wx) ) unorm2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) unorm2 ar;

    unorm2 get_wx() const __GPU {
        return unorm2(_M_xyzw[3], _M_xyzw[0]);
    }

    void set_wx(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_wy, put = set_wy) ) unorm2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) unorm2 ag;

    unorm2 get_wy() const __GPU {
        return unorm2(_M_xyzw[3], _M_xyzw[1]);
    }

    void set_wy(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_wz, put = set_wz) ) unorm2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) unorm2 ab;

    unorm2 get_wz() const __GPU {
        return unorm2(_M_xyzw[3], _M_xyzw[2]);
    }

    void set_wz(const unorm2& _Value) __GPU
    {
        unorm2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) unorm3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) unorm3 rgb;

    unorm3 get_xyz() const __GPU {
        return unorm3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xyz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) unorm3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) unorm3 rga;

    unorm3 get_xyw() const __GPU {
        return unorm3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xyw(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) unorm3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) unorm3 rbg;

    unorm3 get_xzy() const __GPU {
        return unorm3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xzy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) unorm3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) unorm3 rba;

    unorm3 get_xzw() const __GPU {
        return unorm3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xzw(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) unorm3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) unorm3 rag;

    unorm3 get_xwy() const __GPU {
        return unorm3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xwy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) unorm3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) unorm3 rab;

    unorm3 get_xwz() const __GPU {
        return unorm3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xwz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) unorm3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) unorm3 grb;

    unorm3 get_yxz() const __GPU {
        return unorm3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_yxz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) unorm3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) unorm3 gra;

    unorm3 get_yxw() const __GPU {
        return unorm3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yxw(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) unorm3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) unorm3 gbr;

    unorm3 get_yzx() const __GPU {
        return unorm3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_yzx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) unorm3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) unorm3 gba;

    unorm3 get_yzw() const __GPU {
        return unorm3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yzw(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) unorm3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) unorm3 gar;

    unorm3 get_ywx() const __GPU {
        return unorm3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_ywx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) unorm3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) unorm3 gab;

    unorm3 get_ywz() const __GPU {
        return unorm3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_ywz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) unorm3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) unorm3 brg;

    unorm3 get_zxy() const __GPU {
        return unorm3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zxy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) unorm3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) unorm3 bra;

    unorm3 get_zxw() const __GPU {
        return unorm3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zxw(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) unorm3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) unorm3 bgr;

    unorm3 get_zyx() const __GPU {
        return unorm3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zyx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) unorm3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) unorm3 bga;

    unorm3 get_zyw() const __GPU {
        return unorm3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zyw(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) unorm3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) unorm3 bar;

    unorm3 get_zwx() const __GPU {
        return unorm3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zwx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) unorm3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) unorm3 bag;

    unorm3 get_zwy() const __GPU {
        return unorm3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zwy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) unorm3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) unorm3 arg;

    unorm3 get_wxy() const __GPU {
        return unorm3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wxy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) unorm3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) unorm3 arb;

    unorm3 get_wxz() const __GPU {
        return unorm3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wxz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) unorm3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) unorm3 agr;

    unorm3 get_wyx() const __GPU {
        return unorm3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wyx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) unorm3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) unorm3 agb;

    unorm3 get_wyz() const __GPU {
        return unorm3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wyz(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) unorm3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) unorm3 abr;

    unorm3 get_wzx() const __GPU {
        return unorm3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wzx(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) unorm3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) unorm3 abg;

    unorm3 get_wzy() const __GPU {
        return unorm3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wzy(const unorm3& _Value) __GPU
    {
        unorm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) unorm4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) unorm4 rgba;

    unorm4 get_xyzw() const __GPU {
        return unorm4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xyzw(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) unorm4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) unorm4 rgab;

    unorm4 get_xywz() const __GPU {
        return unorm4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xywz(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) unorm4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) unorm4 rbga;

    unorm4 get_xzyw() const __GPU {
        return unorm4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xzyw(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) unorm4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) unorm4 rbag;

    unorm4 get_xzwy() const __GPU {
        return unorm4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xzwy(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) unorm4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) unorm4 ragb;

    unorm4 get_xwyz() const __GPU {
        return unorm4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xwyz(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) unorm4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) unorm4 rabg;

    unorm4 get_xwzy() const __GPU {
        return unorm4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xwzy(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) unorm4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) unorm4 grba;

    unorm4 get_yxzw() const __GPU {
        return unorm4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yxzw(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) unorm4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) unorm4 grab;

    unorm4 get_yxwz() const __GPU {
        return unorm4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_yxwz(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) unorm4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) unorm4 gbra;

    unorm4 get_yzxw() const __GPU {
        return unorm4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yzxw(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) unorm4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) unorm4 gbar;

    unorm4 get_yzwx() const __GPU {
        return unorm4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_yzwx(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) unorm4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) unorm4 garb;

    unorm4 get_ywxz() const __GPU {
        return unorm4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_ywxz(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) unorm4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) unorm4 gabr;

    unorm4 get_ywzx() const __GPU {
        return unorm4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_ywzx(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) unorm4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) unorm4 brga;

    unorm4 get_zxyw() const __GPU {
        return unorm4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zxyw(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) unorm4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) unorm4 brag;

    unorm4 get_zxwy() const __GPU {
        return unorm4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zxwy(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) unorm4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) unorm4 bgra;

    unorm4 get_zyxw() const __GPU {
        return unorm4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zyxw(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) unorm4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) unorm4 bgar;

    unorm4 get_zywx() const __GPU {
        return unorm4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zywx(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) unorm4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) unorm4 barg;

    unorm4 get_zwxy() const __GPU {
        return unorm4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zwxy(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) unorm4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) unorm4 bagr;

    unorm4 get_zwyx() const __GPU {
        return unorm4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zwyx(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) unorm4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) unorm4 argb;

    unorm4 get_wxyz() const __GPU {
        return unorm4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wxyz(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) unorm4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) unorm4 arbg;

    unorm4 get_wxzy() const __GPU {
        return unorm4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wxzy(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) unorm4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) unorm4 agrb;

    unorm4 get_wyxz() const __GPU {
        return unorm4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wyxz(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) unorm4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) unorm4 agbr;

    unorm4 get_wyzx() const __GPU {
        return unorm4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wyzx(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) unorm4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) unorm4 abrg;

    unorm4 get_wzxy() const __GPU {
        return unorm4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wzxy(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) unorm4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) unorm4 abgr;

    unorm4 get_wzyx() const __GPU {
        return unorm4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wzyx(const unorm4& _Value) __GPU
    {
        unorm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

};

/// <summary>
///    Represent a short vector of 2 norm's.
/// </summary>
class norm2
{
public:
    typedef norm value_type;
    static const int size = 2;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Norm_type;
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

    __declspec( property( get = get_x, put = set_x) ) norm x;
    __declspec( property( get = get_x, put = set_x) ) norm r;

    norm get_x() const __GPU {
        return _M_xy[0];
    }

    void set_x(norm _Value) __GPU
    {
        _M_xy[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) norm y;
    __declspec( property( get = get_y, put = set_y) ) norm g;

    norm get_y() const __GPU {
        return _M_xy[1];
    }

    void set_y(norm _Value) __GPU
    {
        _M_xy[1] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    norm2() __GPU
    {
        _M_xy[0] = norm(0.0f);
        _M_xy[1] = norm(0.0f);
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
    norm2(norm _V0, norm _V1) __GPU
    {
        _M_xy[0] = _V0;
        _M_xy[1] = _V1;
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
    norm2(float _V0, float _V1) __GPU
    {
        _M_xy[0] = norm(_V0);
        _M_xy[1] = norm(_V1);
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
    norm2(unorm _V0, unorm _V1) __GPU
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
    norm2(norm _V) __GPU
    {
        _M_xy[0] = _V;
        _M_xy[1] = _V;
    }

    explicit norm2(float _V) __GPU
    {
        _M_xy[0] = norm(_V);
        _M_xy[1] = norm(_V);
    }

    /// <summary>
    ///     Copy constructor.
    /// </summary>
    /// <param name="_Other">
    ///     The object to copy from.
    /// </param>
    norm2(const norm2& _Other) __GPU
    {
        *this = _Other;
    }

    norm2& operator=(const norm2& _Other) __GPU
    {
        _M_xy[0] = _Other._M_xy[0];
        _M_xy[1] = _Other._M_xy[1];
        return *this;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm2(const uint2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm2(const int2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm2(const float2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm2(const unorm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm2(const double2& _Other) __GPU;

    norm2 operator-() const __GPU
    {
        norm2 _Value = *this;
        return norm2(-_Value.x, -_Value.y);
    }

    norm2& operator++() __GPU
    {
        norm2 _Value = *this;
        ++_Value._M_xy[0];
        ++_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    norm2 operator++(int) __GPU
    {
        norm2 _Result = *this;
        ++(*this);
        return _Result;
    }

    norm2& operator--() __GPU
    {
        norm2 _Value = *this;
        --_Value._M_xy[0];
        --_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    norm2 operator--(int) __GPU
    {
        norm2 _Result = *this;
        --(*this);
        return _Result;
    }

    norm2& operator+=(const norm2& _Other) __GPU
    {
        norm2 _Value1 = *this;
        norm2 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        *this = _Value1;
        return *this;
    }

    norm2& operator-=(const norm2& _Other) __GPU
    {
        norm2 _Value1 = *this;
        norm2 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        *this = _Value1;
        return *this;
    }

    norm2& operator*=(const norm2& _Other) __GPU
    {
        norm2 _Value1 = *this;
        norm2 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        *this = _Value1;
        return *this;
    }

    norm2& operator/=(const norm2& _Other) __GPU
    {
        norm2 _Value1 = *this;
        norm2 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) norm2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) norm2 rg;

    norm2 get_xy() const __GPU {
        return norm2(_M_xy[0], _M_xy[1]);
    }

    void set_xy(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xy[0] = _Val.x;
        _M_xy[1] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) norm2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) norm2 gr;

    norm2 get_yx() const __GPU {
        return norm2(_M_xy[1], _M_xy[0]);
    }

    void set_yx(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xy[1] = _Val.x;
        _M_xy[0] = _Val.y;
    }

};

/// <summary>
///    Represent a short vector of 3 norm's.
/// </summary>
class norm3
{
public:
    typedef norm value_type;
    static const int size = 3;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Norm_type;
private:
    value_type _M_xyz[3];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xyz[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xyz[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) norm x;
    __declspec( property( get = get_x, put = set_x) ) norm r;

    norm get_x() const __GPU {
        return _M_xyz[0];
    }

    void set_x(norm _Value) __GPU
    {
        _M_xyz[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) norm y;
    __declspec( property( get = get_y, put = set_y) ) norm g;

    norm get_y() const __GPU {
        return _M_xyz[1];
    }

    void set_y(norm _Value) __GPU
    {
        _M_xyz[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) norm z;
    __declspec( property( get = get_z, put = set_z) ) norm b;

    norm get_z() const __GPU {
        return _M_xyz[2];
    }

    void set_z(norm _Value) __GPU
    {
        _M_xyz[2] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    norm3() __GPU
    {
        _M_xyz[0] = norm(0.0f);
        _M_xyz[1] = norm(0.0f);
        _M_xyz[2] = norm(0.0f);
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
    norm3(norm _V0, norm _V1, norm _V2) __GPU
    {
        _M_xyz[0] = _V0;
        _M_xyz[1] = _V1;
        _M_xyz[2] = _V2;
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
    norm3(float _V0, float _V1, float _V2) __GPU
    {
        _M_xyz[0] = norm(_V0);
        _M_xyz[1] = norm(_V1);
        _M_xyz[2] = norm(_V2);
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
    norm3(unorm _V0, unorm _V1, unorm _V2) __GPU
    {
        _M_xyz[0] = _V0;
        _M_xyz[1] = _V1;
        _M_xyz[2] = _V2;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    norm3(norm _V) __GPU
    {
        _M_xyz[0] = _V;
        _M_xyz[1] = _V;
        _M_xyz[2] = _V;
    }

    explicit norm3(float _V) __GPU
    {
        _M_xyz[0] = norm(_V);
        _M_xyz[1] = norm(_V);
        _M_xyz[2] = norm(_V);
    }

    /// <summary>
    ///     Copy constructor.
    /// </summary>
    /// <param name="_Other">
    ///     The object to copy from.
    /// </param>
    norm3(const norm3& _Other) __GPU
    {
        *this = _Other;
    }

    norm3& operator=(const norm3& _Other) __GPU
    {
        _M_xyz[0] = _Other._M_xyz[0];
        _M_xyz[1] = _Other._M_xyz[1];
        _M_xyz[2] = _Other._M_xyz[2];
        return *this;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm3(const uint3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm3(const int3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm3(const float3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm3(const unorm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm3(const double3& _Other) __GPU;

    norm3 operator-() const __GPU
    {
        norm3 _Value = *this;
        return norm3(-_Value.x, -_Value.y, -_Value.z);
    }

    norm3& operator++() __GPU
    {
        norm3 _Value = *this;
        ++_Value._M_xyz[0];
        ++_Value._M_xyz[1];
        ++_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    norm3 operator++(int) __GPU
    {
        norm3 _Result = *this;
        ++(*this);
        return _Result;
    }

    norm3& operator--() __GPU
    {
        norm3 _Value = *this;
        --_Value._M_xyz[0];
        --_Value._M_xyz[1];
        --_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    norm3 operator--(int) __GPU
    {
        norm3 _Result = *this;
        --(*this);
        return _Result;
    }

    norm3& operator+=(const norm3& _Other) __GPU
    {
        norm3 _Value1 = *this;
        norm3 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        *this = _Value1;
        return *this;
    }

    norm3& operator-=(const norm3& _Other) __GPU
    {
        norm3 _Value1 = *this;
        norm3 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        *this = _Value1;
        return *this;
    }

    norm3& operator*=(const norm3& _Other) __GPU
    {
        norm3 _Value1 = *this;
        norm3 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        *this = _Value1;
        return *this;
    }

    norm3& operator/=(const norm3& _Other) __GPU
    {
        norm3 _Value1 = *this;
        norm3 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) norm2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) norm2 rg;

    norm2 get_xy() const __GPU {
        return norm2(_M_xyz[0], _M_xyz[1]);
    }

    void set_xy(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) norm2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) norm2 rb;

    norm2 get_xz() const __GPU {
        return norm2(_M_xyz[0], _M_xyz[2]);
    }

    void set_xz(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) norm2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) norm2 gr;

    norm2 get_yx() const __GPU {
        return norm2(_M_xyz[1], _M_xyz[0]);
    }

    void set_yx(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) norm2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) norm2 gb;

    norm2 get_yz() const __GPU {
        return norm2(_M_xyz[1], _M_xyz[2]);
    }

    void set_yz(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) norm2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) norm2 br;

    norm2 get_zx() const __GPU {
        return norm2(_M_xyz[2], _M_xyz[0]);
    }

    void set_zx(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) norm2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) norm2 bg;

    norm2 get_zy() const __GPU {
        return norm2(_M_xyz[2], _M_xyz[1]);
    }

    void set_zy(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) norm3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) norm3 rgb;

    norm3 get_xyz() const __GPU {
        return norm3(_M_xyz[0], _M_xyz[1], _M_xyz[2]);
    }

    void set_xyz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) norm3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) norm3 rbg;

    norm3 get_xzy() const __GPU {
        return norm3(_M_xyz[0], _M_xyz[2], _M_xyz[1]);
    }

    void set_xzy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) norm3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) norm3 grb;

    norm3 get_yxz() const __GPU {
        return norm3(_M_xyz[1], _M_xyz[0], _M_xyz[2]);
    }

    void set_yxz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) norm3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) norm3 gbr;

    norm3 get_yzx() const __GPU {
        return norm3(_M_xyz[1], _M_xyz[2], _M_xyz[0]);
    }

    void set_yzx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) norm3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) norm3 brg;

    norm3 get_zxy() const __GPU {
        return norm3(_M_xyz[2], _M_xyz[0], _M_xyz[1]);
    }

    void set_zxy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) norm3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) norm3 bgr;

    norm3 get_zyx() const __GPU {
        return norm3(_M_xyz[2], _M_xyz[1], _M_xyz[0]);
    }

    void set_zyx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

};

/// <summary>
///    Represent a short vector of 4 norm's.
/// </summary>
class norm4
{
public:
    typedef norm value_type;
    static const int size = 4;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Norm_type;
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

    __declspec( property( get = get_x, put = set_x) ) norm x;
    __declspec( property( get = get_x, put = set_x) ) norm r;

    norm get_x() const __GPU {
        return _M_xyzw[0];
    }

    void set_x(norm _Value) __GPU
    {
        _M_xyzw[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) norm y;
    __declspec( property( get = get_y, put = set_y) ) norm g;

    norm get_y() const __GPU {
        return _M_xyzw[1];
    }

    void set_y(norm _Value) __GPU
    {
        _M_xyzw[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) norm z;
    __declspec( property( get = get_z, put = set_z) ) norm b;

    norm get_z() const __GPU {
        return _M_xyzw[2];
    }

    void set_z(norm _Value) __GPU
    {
        _M_xyzw[2] = _Value;
    }

    __declspec( property( get = get_w, put = set_w) ) norm w;
    __declspec( property( get = get_w, put = set_w) ) norm a;

    norm get_w() const __GPU {
        return _M_xyzw[3];
    }

    void set_w(norm _Value) __GPU
    {
        _M_xyzw[3] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    norm4() __GPU
    {
        _M_xyzw[0] = norm(0.0f);
        _M_xyzw[1] = norm(0.0f);
        _M_xyzw[2] = norm(0.0f);
        _M_xyzw[3] = norm(0.0f);
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
    norm4(norm _V0, norm _V1, norm _V2, norm _V3) __GPU
    {
        _M_xyzw[0] = _V0;
        _M_xyzw[1] = _V1;
        _M_xyzw[2] = _V2;
        _M_xyzw[3] = _V3;
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
    norm4(float _V0, float _V1, float _V2, float _V3) __GPU
    {
        _M_xyzw[0] = norm(_V0);
        _M_xyzw[1] = norm(_V1);
        _M_xyzw[2] = norm(_V2);
        _M_xyzw[3] = norm(_V3);
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
    norm4(unorm _V0, unorm _V1, unorm _V2, unorm _V3) __GPU
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
    norm4(norm _V) __GPU
    {
        _M_xyzw[0] = _V;
        _M_xyzw[1] = _V;
        _M_xyzw[2] = _V;
        _M_xyzw[3] = _V;
    }

    explicit norm4(float _V) __GPU
    {
        _M_xyzw[0] = norm(_V);
        _M_xyzw[1] = norm(_V);
        _M_xyzw[2] = norm(_V);
        _M_xyzw[3] = norm(_V);
    }

    /// <summary>
    ///     Copy constructor.
    /// </summary>
    /// <param name="_Other">
    ///     The object to copy from.
    /// </param>
    norm4(const norm4& _Other) __GPU
    {
        *this = _Other;
    }

    norm4& operator=(const norm4& _Other) __GPU
    {
        _M_xyzw[0] = _Other._M_xyzw[0];
        _M_xyzw[1] = _Other._M_xyzw[1];
        _M_xyzw[2] = _Other._M_xyzw[2];
        _M_xyzw[3] = _Other._M_xyzw[3];
        return *this;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm4(const uint4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm4(const int4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm4(const float4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm4(const unorm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline norm4(const double4& _Other) __GPU;

    norm4 operator-() const __GPU
    {
        norm4 _Value = *this;
        return norm4(-_Value.x, -_Value.y, -_Value.z, -_Value.w);
    }

    norm4& operator++() __GPU
    {
        norm4 _Value = *this;
        ++_Value._M_xyzw[0];
        ++_Value._M_xyzw[1];
        ++_Value._M_xyzw[2];
        ++_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    norm4 operator++(int) __GPU
    {
        norm4 _Result = *this;
        ++(*this);
        return _Result;
    }

    norm4& operator--() __GPU
    {
        norm4 _Value = *this;
        --_Value._M_xyzw[0];
        --_Value._M_xyzw[1];
        --_Value._M_xyzw[2];
        --_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    norm4 operator--(int) __GPU
    {
        norm4 _Result = *this;
        --(*this);
        return _Result;
    }

    norm4& operator+=(const norm4& _Other) __GPU
    {
        norm4 _Value1 = *this;
        norm4 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        _Value1.w += _Value2.w;
        *this = _Value1;
        return *this;
    }

    norm4& operator-=(const norm4& _Other) __GPU
    {
        norm4 _Value1 = *this;
        norm4 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        _Value1.w -= _Value2.w;
        *this = _Value1;
        return *this;
    }

    norm4& operator*=(const norm4& _Other) __GPU
    {
        norm4 _Value1 = *this;
        norm4 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        _Value1.w *= _Value2.w;
        *this = _Value1;
        return *this;
    }

    norm4& operator/=(const norm4& _Other) __GPU
    {
        norm4 _Value1 = *this;
        norm4 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        _Value1.w /= _Value2.w;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) norm2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) norm2 rg;

    norm2 get_xy() const __GPU {
        return norm2(_M_xyzw[0], _M_xyzw[1]);
    }

    void set_xy(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) norm2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) norm2 rb;

    norm2 get_xz() const __GPU {
        return norm2(_M_xyzw[0], _M_xyzw[2]);
    }

    void set_xz(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xw, put = set_xw) ) norm2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) norm2 ra;

    norm2 get_xw() const __GPU {
        return norm2(_M_xyzw[0], _M_xyzw[3]);
    }

    void set_xw(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) norm2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) norm2 gr;

    norm2 get_yx() const __GPU {
        return norm2(_M_xyzw[1], _M_xyzw[0]);
    }

    void set_yx(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) norm2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) norm2 gb;

    norm2 get_yz() const __GPU {
        return norm2(_M_xyzw[1], _M_xyzw[2]);
    }

    void set_yz(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_yw, put = set_yw) ) norm2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) norm2 ga;

    norm2 get_yw() const __GPU {
        return norm2(_M_xyzw[1], _M_xyzw[3]);
    }

    void set_yw(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) norm2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) norm2 br;

    norm2 get_zx() const __GPU {
        return norm2(_M_xyzw[2], _M_xyzw[0]);
    }

    void set_zx(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) norm2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) norm2 bg;

    norm2 get_zy() const __GPU {
        return norm2(_M_xyzw[2], _M_xyzw[1]);
    }

    void set_zy(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_zw, put = set_zw) ) norm2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) norm2 ba;

    norm2 get_zw() const __GPU {
        return norm2(_M_xyzw[2], _M_xyzw[3]);
    }

    void set_zw(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_wx, put = set_wx) ) norm2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) norm2 ar;

    norm2 get_wx() const __GPU {
        return norm2(_M_xyzw[3], _M_xyzw[0]);
    }

    void set_wx(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_wy, put = set_wy) ) norm2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) norm2 ag;

    norm2 get_wy() const __GPU {
        return norm2(_M_xyzw[3], _M_xyzw[1]);
    }

    void set_wy(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_wz, put = set_wz) ) norm2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) norm2 ab;

    norm2 get_wz() const __GPU {
        return norm2(_M_xyzw[3], _M_xyzw[2]);
    }

    void set_wz(const norm2& _Value) __GPU
    {
        norm2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) norm3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) norm3 rgb;

    norm3 get_xyz() const __GPU {
        return norm3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xyz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) norm3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) norm3 rga;

    norm3 get_xyw() const __GPU {
        return norm3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xyw(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) norm3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) norm3 rbg;

    norm3 get_xzy() const __GPU {
        return norm3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xzy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) norm3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) norm3 rba;

    norm3 get_xzw() const __GPU {
        return norm3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xzw(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) norm3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) norm3 rag;

    norm3 get_xwy() const __GPU {
        return norm3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xwy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) norm3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) norm3 rab;

    norm3 get_xwz() const __GPU {
        return norm3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xwz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) norm3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) norm3 grb;

    norm3 get_yxz() const __GPU {
        return norm3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_yxz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) norm3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) norm3 gra;

    norm3 get_yxw() const __GPU {
        return norm3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yxw(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) norm3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) norm3 gbr;

    norm3 get_yzx() const __GPU {
        return norm3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_yzx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) norm3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) norm3 gba;

    norm3 get_yzw() const __GPU {
        return norm3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yzw(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) norm3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) norm3 gar;

    norm3 get_ywx() const __GPU {
        return norm3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_ywx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) norm3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) norm3 gab;

    norm3 get_ywz() const __GPU {
        return norm3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_ywz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) norm3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) norm3 brg;

    norm3 get_zxy() const __GPU {
        return norm3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zxy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) norm3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) norm3 bra;

    norm3 get_zxw() const __GPU {
        return norm3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zxw(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) norm3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) norm3 bgr;

    norm3 get_zyx() const __GPU {
        return norm3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zyx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) norm3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) norm3 bga;

    norm3 get_zyw() const __GPU {
        return norm3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zyw(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) norm3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) norm3 bar;

    norm3 get_zwx() const __GPU {
        return norm3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zwx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) norm3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) norm3 bag;

    norm3 get_zwy() const __GPU {
        return norm3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zwy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) norm3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) norm3 arg;

    norm3 get_wxy() const __GPU {
        return norm3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wxy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) norm3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) norm3 arb;

    norm3 get_wxz() const __GPU {
        return norm3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wxz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) norm3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) norm3 agr;

    norm3 get_wyx() const __GPU {
        return norm3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wyx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) norm3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) norm3 agb;

    norm3 get_wyz() const __GPU {
        return norm3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wyz(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) norm3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) norm3 abr;

    norm3 get_wzx() const __GPU {
        return norm3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wzx(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) norm3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) norm3 abg;

    norm3 get_wzy() const __GPU {
        return norm3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wzy(const norm3& _Value) __GPU
    {
        norm3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) norm4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) norm4 rgba;

    norm4 get_xyzw() const __GPU {
        return norm4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xyzw(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) norm4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) norm4 rgab;

    norm4 get_xywz() const __GPU {
        return norm4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xywz(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) norm4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) norm4 rbga;

    norm4 get_xzyw() const __GPU {
        return norm4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xzyw(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) norm4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) norm4 rbag;

    norm4 get_xzwy() const __GPU {
        return norm4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xzwy(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) norm4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) norm4 ragb;

    norm4 get_xwyz() const __GPU {
        return norm4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xwyz(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) norm4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) norm4 rabg;

    norm4 get_xwzy() const __GPU {
        return norm4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xwzy(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) norm4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) norm4 grba;

    norm4 get_yxzw() const __GPU {
        return norm4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yxzw(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) norm4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) norm4 grab;

    norm4 get_yxwz() const __GPU {
        return norm4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_yxwz(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) norm4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) norm4 gbra;

    norm4 get_yzxw() const __GPU {
        return norm4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yzxw(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) norm4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) norm4 gbar;

    norm4 get_yzwx() const __GPU {
        return norm4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_yzwx(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) norm4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) norm4 garb;

    norm4 get_ywxz() const __GPU {
        return norm4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_ywxz(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) norm4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) norm4 gabr;

    norm4 get_ywzx() const __GPU {
        return norm4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_ywzx(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) norm4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) norm4 brga;

    norm4 get_zxyw() const __GPU {
        return norm4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zxyw(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) norm4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) norm4 brag;

    norm4 get_zxwy() const __GPU {
        return norm4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zxwy(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) norm4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) norm4 bgra;

    norm4 get_zyxw() const __GPU {
        return norm4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zyxw(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) norm4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) norm4 bgar;

    norm4 get_zywx() const __GPU {
        return norm4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zywx(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) norm4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) norm4 barg;

    norm4 get_zwxy() const __GPU {
        return norm4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zwxy(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) norm4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) norm4 bagr;

    norm4 get_zwyx() const __GPU {
        return norm4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zwyx(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) norm4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) norm4 argb;

    norm4 get_wxyz() const __GPU {
        return norm4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wxyz(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) norm4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) norm4 arbg;

    norm4 get_wxzy() const __GPU {
        return norm4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wxzy(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) norm4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) norm4 agrb;

    norm4 get_wyxz() const __GPU {
        return norm4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wyxz(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) norm4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) norm4 agbr;

    norm4 get_wyzx() const __GPU {
        return norm4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wyzx(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) norm4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) norm4 abrg;

    norm4 get_wzxy() const __GPU {
        return norm4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wzxy(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) norm4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) norm4 abgr;

    norm4 get_wzyx() const __GPU {
        return norm4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wzyx(const norm4& _Value) __GPU
    {
        norm4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

};

/// <summary>
///    Represent a short vector of 2 double's.
/// </summary>
class double2
{
public:
    typedef double value_type;
    static const int size = 2;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Double_type;
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

    __declspec( property( get = get_x, put = set_x) ) double x;
    __declspec( property( get = get_x, put = set_x) ) double r;

    double get_x() const __GPU {
        return _M_xy[0];
    }

    void set_x(double _Value) __GPU
    {
        _M_xy[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) double y;
    __declspec( property( get = get_y, put = set_y) ) double g;

    double get_y() const __GPU {
        return _M_xy[1];
    }

    void set_y(double _Value) __GPU
    {
        _M_xy[1] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    double2() __GPU
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
    double2(double _V0, double _V1) __GPU
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
    double2(double _V) __GPU
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
    explicit inline double2(const uint2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double2(const int2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double2(const float2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double2(const unorm2& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double2(const norm2& _Other) __GPU;

    double2 operator-() const __GPU
    {
        double2 _Value = *this;
        return double2(-_Value.x, -_Value.y);
    }

    double2& operator++() __GPU
    {
        double2 _Value = *this;
        ++_Value._M_xy[0];
        ++_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    double2 operator++(int) __GPU
    {
        double2 _Result = *this;
        ++(*this);
        return _Result;
    }

    double2& operator--() __GPU
    {
        double2 _Value = *this;
        --_Value._M_xy[0];
        --_Value._M_xy[1];
        *this = _Value;
        return *this;
    }

    double2 operator--(int) __GPU
    {
        double2 _Result = *this;
        --(*this);
        return _Result;
    }

    double2& operator+=(const double2& _Other) __GPU
    {
        double2 _Value1 = *this;
        double2 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        *this = _Value1;
        return *this;
    }

    double2& operator-=(const double2& _Other) __GPU
    {
        double2 _Value1 = *this;
        double2 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        *this = _Value1;
        return *this;
    }

    double2& operator*=(const double2& _Other) __GPU
    {
        double2 _Value1 = *this;
        double2 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        *this = _Value1;
        return *this;
    }

    double2& operator/=(const double2& _Other) __GPU
    {
        double2 _Value1 = *this;
        double2 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) double2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) double2 rg;

    double2 get_xy() const __GPU {
        return double2(_M_xy[0], _M_xy[1]);
    }

    void set_xy(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xy[0] = _Val.x;
        _M_xy[1] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) double2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) double2 gr;

    double2 get_yx() const __GPU {
        return double2(_M_xy[1], _M_xy[0]);
    }

    void set_yx(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xy[1] = _Val.x;
        _M_xy[0] = _Val.y;
    }

};

/// <summary>
///    Represent a short vector of 3 double's.
/// </summary>
class double3
{
public:
    typedef double value_type;
    static const int size = 3;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Double_type;
private:
    value_type _M_xyz[3];

public:
    value_type & operator [] (int _Component) __GPU
    {
	return _M_xyz[_Component];
    }

    const value_type operator [] (int _Component) const __GPU
    {
	return _M_xyz[_Component];
    }

    __declspec( property( get = get_x, put = set_x) ) double x;
    __declspec( property( get = get_x, put = set_x) ) double r;

    double get_x() const __GPU {
        return _M_xyz[0];
    }

    void set_x(double _Value) __GPU
    {
        _M_xyz[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) double y;
    __declspec( property( get = get_y, put = set_y) ) double g;

    double get_y() const __GPU {
        return _M_xyz[1];
    }

    void set_y(double _Value) __GPU
    {
        _M_xyz[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) double z;
    __declspec( property( get = get_z, put = set_z) ) double b;

    double get_z() const __GPU {
        return _M_xyz[2];
    }

    void set_z(double _Value) __GPU
    {
        _M_xyz[2] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    double3() __GPU
    {
        _M_xyz[0] = 0;
        _M_xyz[1] = 0;
        _M_xyz[2] = 0;
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
    double3(double _V0, double _V1, double _V2) __GPU
    {
        _M_xyz[0] = _V0;
        _M_xyz[1] = _V1;
        _M_xyz[2] = _V2;
    }

    /// <summary>
    ///     Constructor.
    /// </summary>
    /// <param name="_V">
    ///     The value for initialization.
    /// </param>
    double3(double _V) __GPU
    {
        _M_xyz[0] = _V;
        _M_xyz[1] = _V;
        _M_xyz[2] = _V;
    }

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double3(const uint3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double3(const int3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double3(const float3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double3(const unorm3& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double3(const norm3& _Other) __GPU;

    double3 operator-() const __GPU
    {
        double3 _Value = *this;
        return double3(-_Value.x, -_Value.y, -_Value.z);
    }

    double3& operator++() __GPU
    {
        double3 _Value = *this;
        ++_Value._M_xyz[0];
        ++_Value._M_xyz[1];
        ++_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    double3 operator++(int) __GPU
    {
        double3 _Result = *this;
        ++(*this);
        return _Result;
    }

    double3& operator--() __GPU
    {
        double3 _Value = *this;
        --_Value._M_xyz[0];
        --_Value._M_xyz[1];
        --_Value._M_xyz[2];
        *this = _Value;
        return *this;
    }

    double3 operator--(int) __GPU
    {
        double3 _Result = *this;
        --(*this);
        return _Result;
    }

    double3& operator+=(const double3& _Other) __GPU
    {
        double3 _Value1 = *this;
        double3 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        *this = _Value1;
        return *this;
    }

    double3& operator-=(const double3& _Other) __GPU
    {
        double3 _Value1 = *this;
        double3 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        *this = _Value1;
        return *this;
    }

    double3& operator*=(const double3& _Other) __GPU
    {
        double3 _Value1 = *this;
        double3 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        *this = _Value1;
        return *this;
    }

    double3& operator/=(const double3& _Other) __GPU
    {
        double3 _Value1 = *this;
        double3 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) double2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) double2 rg;

    double2 get_xy() const __GPU {
        return double2(_M_xyz[0], _M_xyz[1]);
    }

    void set_xy(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) double2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) double2 rb;

    double2 get_xz() const __GPU {
        return double2(_M_xyz[0], _M_xyz[2]);
    }

    void set_xz(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) double2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) double2 gr;

    double2 get_yx() const __GPU {
        return double2(_M_xyz[1], _M_xyz[0]);
    }

    void set_yx(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) double2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) double2 gb;

    double2 get_yz() const __GPU {
        return double2(_M_xyz[1], _M_xyz[2]);
    }

    void set_yz(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) double2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) double2 br;

    double2 get_zx() const __GPU {
        return double2(_M_xyz[2], _M_xyz[0]);
    }

    void set_zx(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) double2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) double2 bg;

    double2 get_zy() const __GPU {
        return double2(_M_xyz[2], _M_xyz[1]);
    }

    void set_zy(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) double3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) double3 rgb;

    double3 get_xyz() const __GPU {
        return double3(_M_xyz[0], _M_xyz[1], _M_xyz[2]);
    }

    void set_xyz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) double3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) double3 rbg;

    double3 get_xzy() const __GPU {
        return double3(_M_xyz[0], _M_xyz[2], _M_xyz[1]);
    }

    void set_xzy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyz[0] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) double3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) double3 grb;

    double3 get_yxz() const __GPU {
        return double3(_M_xyz[1], _M_xyz[0], _M_xyz[2]);
    }

    void set_yxz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[2] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) double3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) double3 gbr;

    double3 get_yzx() const __GPU {
        return double3(_M_xyz[1], _M_xyz[2], _M_xyz[0]);
    }

    void set_yzx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyz[1] = _Val.x;
        _M_xyz[2] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) double3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) double3 brg;

    double3 get_zxy() const __GPU {
        return double3(_M_xyz[2], _M_xyz[0], _M_xyz[1]);
    }

    void set_zxy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[0] = _Val.y;
        _M_xyz[1] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) double3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) double3 bgr;

    double3 get_zyx() const __GPU {
        return double3(_M_xyz[2], _M_xyz[1], _M_xyz[0]);
    }

    void set_zyx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyz[2] = _Val.x;
        _M_xyz[1] = _Val.y;
        _M_xyz[0] = _Val.z;
    }

};

/// <summary>
///    Represent a short vector of 4 double's.
/// </summary>
class double4
{
public:
    typedef double value_type;
    static const int size = 4;
private:
    static const _Short_vector_base_type_id _Base_type_id = _Double_type;
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

    __declspec( property( get = get_x, put = set_x) ) double x;
    __declspec( property( get = get_x, put = set_x) ) double r;

    double get_x() const __GPU {
        return _M_xyzw[0];
    }

    void set_x(double _Value) __GPU
    {
        _M_xyzw[0] = _Value;
    }

    __declspec( property( get = get_y, put = set_y) ) double y;
    __declspec( property( get = get_y, put = set_y) ) double g;

    double get_y() const __GPU {
        return _M_xyzw[1];
    }

    void set_y(double _Value) __GPU
    {
        _M_xyzw[1] = _Value;
    }

    __declspec( property( get = get_z, put = set_z) ) double z;
    __declspec( property( get = get_z, put = set_z) ) double b;

    double get_z() const __GPU {
        return _M_xyzw[2];
    }

    void set_z(double _Value) __GPU
    {
        _M_xyzw[2] = _Value;
    }

    __declspec( property( get = get_w, put = set_w) ) double w;
    __declspec( property( get = get_w, put = set_w) ) double a;

    double get_w() const __GPU {
        return _M_xyzw[3];
    }

    void set_w(double _Value) __GPU
    {
        _M_xyzw[3] = _Value;
    }

public:
    /// <summary>
    ///     Default constructor, initializes all elements with 0.
    /// </summary>
    double4() __GPU
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
    double4(double _V0, double _V1, double _V2, double _V3) __GPU
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
    double4(double _V) __GPU
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
    explicit inline double4(const uint4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double4(const int4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double4(const float4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double4(const unorm4& _Other) __GPU;

    /// <summary>
    ///     Constructor.
    ///     Each element is initialized by casting from the corresponding element in _Other.
    /// </summary>
    /// <param name="_Other">
    ///     The object used to initialize.
    /// </param>
    explicit inline double4(const norm4& _Other) __GPU;

    double4 operator-() const __GPU
    {
        double4 _Value = *this;
        return double4(-_Value.x, -_Value.y, -_Value.z, -_Value.w);
    }

    double4& operator++() __GPU
    {
        double4 _Value = *this;
        ++_Value._M_xyzw[0];
        ++_Value._M_xyzw[1];
        ++_Value._M_xyzw[2];
        ++_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    double4 operator++(int) __GPU
    {
        double4 _Result = *this;
        ++(*this);
        return _Result;
    }

    double4& operator--() __GPU
    {
        double4 _Value = *this;
        --_Value._M_xyzw[0];
        --_Value._M_xyzw[1];
        --_Value._M_xyzw[2];
        --_Value._M_xyzw[3];
        *this = _Value;
        return *this;
    }

    double4 operator--(int) __GPU
    {
        double4 _Result = *this;
        --(*this);
        return _Result;
    }

    double4& operator+=(const double4& _Other) __GPU
    {
        double4 _Value1 = *this;
        double4 _Value2 = _Other;
        _Value1.x += _Value2.x;
        _Value1.y += _Value2.y;
        _Value1.z += _Value2.z;
        _Value1.w += _Value2.w;
        *this = _Value1;
        return *this;
    }

    double4& operator-=(const double4& _Other) __GPU
    {
        double4 _Value1 = *this;
        double4 _Value2 = _Other;
        _Value1.x -= _Value2.x;
        _Value1.y -= _Value2.y;
        _Value1.z -= _Value2.z;
        _Value1.w -= _Value2.w;
        *this = _Value1;
        return *this;
    }

    double4& operator*=(const double4& _Other) __GPU
    {
        double4 _Value1 = *this;
        double4 _Value2 = _Other;
        _Value1.x *= _Value2.x;
        _Value1.y *= _Value2.y;
        _Value1.z *= _Value2.z;
        _Value1.w *= _Value2.w;
        *this = _Value1;
        return *this;
    }

    double4& operator/=(const double4& _Other) __GPU
    {
        double4 _Value1 = *this;
        double4 _Value2 = _Other;
        _Value1.x /= _Value2.x;
        _Value1.y /= _Value2.y;
        _Value1.z /= _Value2.z;
        _Value1.w /= _Value2.w;
        *this = _Value1;
        return *this;
    }

public:
    __declspec( property( get = get_xy, put = set_xy) ) double2 xy;
    __declspec( property( get = get_xy, put = set_xy) ) double2 rg;

    double2 get_xy() const __GPU {
        return double2(_M_xyzw[0], _M_xyzw[1]);
    }

    void set_xy(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_xz, put = set_xz) ) double2 xz;
    __declspec( property( get = get_xz, put = set_xz) ) double2 rb;

    double2 get_xz() const __GPU {
        return double2(_M_xyzw[0], _M_xyzw[2]);
    }

    void set_xz(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xw, put = set_xw) ) double2 xw;
    __declspec( property( get = get_xw, put = set_xw) ) double2 ra;

    double2 get_xw() const __GPU {
        return double2(_M_xyzw[0], _M_xyzw[3]);
    }

    void set_xw(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_yx, put = set_yx) ) double2 yx;
    __declspec( property( get = get_yx, put = set_yx) ) double2 gr;

    double2 get_yx() const __GPU {
        return double2(_M_xyzw[1], _M_xyzw[0]);
    }

    void set_yx(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_yz, put = set_yz) ) double2 yz;
    __declspec( property( get = get_yz, put = set_yz) ) double2 gb;

    double2 get_yz() const __GPU {
        return double2(_M_xyzw[1], _M_xyzw[2]);
    }

    void set_yz(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_yw, put = set_yw) ) double2 yw;
    __declspec( property( get = get_yw, put = set_yw) ) double2 ga;

    double2 get_yw() const __GPU {
        return double2(_M_xyzw[1], _M_xyzw[3]);
    }

    void set_yw(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_zx, put = set_zx) ) double2 zx;
    __declspec( property( get = get_zx, put = set_zx) ) double2 br;

    double2 get_zx() const __GPU {
        return double2(_M_xyzw[2], _M_xyzw[0]);
    }

    void set_zx(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_zy, put = set_zy) ) double2 zy;
    __declspec( property( get = get_zy, put = set_zy) ) double2 bg;

    double2 get_zy() const __GPU {
        return double2(_M_xyzw[2], _M_xyzw[1]);
    }

    void set_zy(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_zw, put = set_zw) ) double2 zw;
    __declspec( property( get = get_zw, put = set_zw) ) double2 ba;

    double2 get_zw() const __GPU {
        return double2(_M_xyzw[2], _M_xyzw[3]);
    }

    void set_zw(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
    }

    __declspec( property( get = get_wx, put = set_wx) ) double2 wx;
    __declspec( property( get = get_wx, put = set_wx) ) double2 ar;

    double2 get_wx() const __GPU {
        return double2(_M_xyzw[3], _M_xyzw[0]);
    }

    void set_wx(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
    }

    __declspec( property( get = get_wy, put = set_wy) ) double2 wy;
    __declspec( property( get = get_wy, put = set_wy) ) double2 ag;

    double2 get_wy() const __GPU {
        return double2(_M_xyzw[3], _M_xyzw[1]);
    }

    void set_wy(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
    }

    __declspec( property( get = get_wz, put = set_wz) ) double2 wz;
    __declspec( property( get = get_wz, put = set_wz) ) double2 ab;

    double2 get_wz() const __GPU {
        return double2(_M_xyzw[3], _M_xyzw[2]);
    }

    void set_wz(const double2& _Value) __GPU
    {
        double2 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
    }

    __declspec( property( get = get_xyz, put = set_xyz) ) double3 xyz;
    __declspec( property( get = get_xyz, put = set_xyz) ) double3 rgb;

    double3 get_xyz() const __GPU {
        return double3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xyz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_xyw, put = set_xyw) ) double3 xyw;
    __declspec( property( get = get_xyw, put = set_xyw) ) double3 rga;

    double3 get_xyw() const __GPU {
        return double3(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xyw(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xzy, put = set_xzy) ) double3 xzy;
    __declspec( property( get = get_xzy, put = set_xzy) ) double3 rbg;

    double3 get_xzy() const __GPU {
        return double3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xzy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xzw, put = set_xzw) ) double3 xzw;
    __declspec( property( get = get_xzw, put = set_xzw) ) double3 rba;

    double3 get_xzw() const __GPU {
        return double3(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xzw(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_xwy, put = set_xwy) ) double3 xwy;
    __declspec( property( get = get_xwy, put = set_xwy) ) double3 rag;

    double3 get_xwy() const __GPU {
        return double3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xwy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xwz, put = set_xwz) ) double3 xwz;
    __declspec( property( get = get_xwz, put = set_xwz) ) double3 rab;

    double3 get_xwz() const __GPU {
        return double3(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xwz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxz, put = set_yxz) ) double3 yxz;
    __declspec( property( get = get_yxz, put = set_yxz) ) double3 grb;

    double3 get_yxz() const __GPU {
        return double3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_yxz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_yxw, put = set_yxw) ) double3 yxw;
    __declspec( property( get = get_yxw, put = set_yxw) ) double3 gra;

    double3 get_yxw() const __GPU {
        return double3(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yxw(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_yzx, put = set_yzx) ) double3 yzx;
    __declspec( property( get = get_yzx, put = set_yzx) ) double3 gbr;

    double3 get_yzx() const __GPU {
        return double3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_yzx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_yzw, put = set_yzw) ) double3 yzw;
    __declspec( property( get = get_yzw, put = set_yzw) ) double3 gba;

    double3 get_yzw() const __GPU {
        return double3(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yzw(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_ywx, put = set_ywx) ) double3 ywx;
    __declspec( property( get = get_ywx, put = set_ywx) ) double3 gar;

    double3 get_ywx() const __GPU {
        return double3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_ywx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_ywz, put = set_ywz) ) double3 ywz;
    __declspec( property( get = get_ywz, put = set_ywz) ) double3 gab;

    double3 get_ywz() const __GPU {
        return double3(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_ywz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_zxy, put = set_zxy) ) double3 zxy;
    __declspec( property( get = get_zxy, put = set_zxy) ) double3 brg;

    double3 get_zxy() const __GPU {
        return double3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zxy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_zxw, put = set_zxw) ) double3 zxw;
    __declspec( property( get = get_zxw, put = set_zxw) ) double3 bra;

    double3 get_zxw() const __GPU {
        return double3(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zxw(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zyx, put = set_zyx) ) double3 zyx;
    __declspec( property( get = get_zyx, put = set_zyx) ) double3 bgr;

    double3 get_zyx() const __GPU {
        return double3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zyx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zyw, put = set_zyw) ) double3 zyw;
    __declspec( property( get = get_zyw, put = set_zyw) ) double3 bga;

    double3 get_zyw() const __GPU {
        return double3(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zyw(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
    }

    __declspec( property( get = get_zwx, put = set_zwx) ) double3 zwx;
    __declspec( property( get = get_zwx, put = set_zwx) ) double3 bar;

    double3 get_zwx() const __GPU {
        return double3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zwx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_zwy, put = set_zwy) ) double3 zwy;
    __declspec( property( get = get_zwy, put = set_zwy) ) double3 bag;

    double3 get_zwy() const __GPU {
        return double3(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zwy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxy, put = set_wxy) ) double3 wxy;
    __declspec( property( get = get_wxy, put = set_wxy) ) double3 arg;

    double3 get_wxy() const __GPU {
        return double3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wxy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_wxz, put = set_wxz) ) double3 wxz;
    __declspec( property( get = get_wxz, put = set_wxz) ) double3 arb;

    double3 get_wxz() const __GPU {
        return double3(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wxz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wyx, put = set_wyx) ) double3 wyx;
    __declspec( property( get = get_wyx, put = set_wyx) ) double3 agr;

    double3 get_wyx() const __GPU {
        return double3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wyx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wyz, put = set_wyz) ) double3 wyz;
    __declspec( property( get = get_wyz, put = set_wyz) ) double3 agb;

    double3 get_wyz() const __GPU {
        return double3(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wyz(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
    }

    __declspec( property( get = get_wzx, put = set_wzx) ) double3 wzx;
    __declspec( property( get = get_wzx, put = set_wzx) ) double3 abr;

    double3 get_wzx() const __GPU {
        return double3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wzx(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
    }

    __declspec( property( get = get_wzy, put = set_wzy) ) double3 wzy;
    __declspec( property( get = get_wzy, put = set_wzy) ) double3 abg;

    double3 get_wzy() const __GPU {
        return double3(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wzy(const double3& _Value) __GPU
    {
        double3 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
    }

    __declspec( property( get = get_xyzw, put = set_xyzw) ) double4 xyzw;
    __declspec( property( get = get_xyzw, put = set_xyzw) ) double4 rgba;

    double4 get_xyzw() const __GPU {
        return double4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_xyzw(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xywz, put = set_xywz) ) double4 xywz;
    __declspec( property( get = get_xywz, put = set_xywz) ) double4 rgab;

    double4 get_xywz() const __GPU {
        return double4(_M_xyzw[0], _M_xyzw[1], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_xywz(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xzyw, put = set_xzyw) ) double4 xzyw;
    __declspec( property( get = get_xzyw, put = set_xzyw) ) double4 rbga;

    double4 get_xzyw() const __GPU {
        return double4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_xzyw(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_xzwy, put = set_xzwy) ) double4 xzwy;
    __declspec( property( get = get_xzwy, put = set_xzwy) ) double4 rbag;

    double4 get_xzwy() const __GPU {
        return double4(_M_xyzw[0], _M_xyzw[2], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_xzwy(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_xwyz, put = set_xwyz) ) double4 xwyz;
    __declspec( property( get = get_xwyz, put = set_xwyz) ) double4 ragb;

    double4 get_xwyz() const __GPU {
        return double4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_xwyz(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_xwzy, put = set_xwzy) ) double4 xwzy;
    __declspec( property( get = get_xwzy, put = set_xwzy) ) double4 rabg;

    double4 get_xwzy() const __GPU {
        return double4(_M_xyzw[0], _M_xyzw[3], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_xwzy(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[0] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_yxzw, put = set_yxzw) ) double4 yxzw;
    __declspec( property( get = get_yxzw, put = set_yxzw) ) double4 grba;

    double4 get_yxzw() const __GPU {
        return double4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[2], _M_xyzw[3]);
    }

    void set_yxzw(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yxwz, put = set_yxwz) ) double4 yxwz;
    __declspec( property( get = get_yxwz, put = set_yxwz) ) double4 grab;

    double4 get_yxwz() const __GPU {
        return double4(_M_xyzw[1], _M_xyzw[0], _M_xyzw[3], _M_xyzw[2]);
    }

    void set_yxwz(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_yzxw, put = set_yzxw) ) double4 yzxw;
    __declspec( property( get = get_yzxw, put = set_yzxw) ) double4 gbra;

    double4 get_yzxw() const __GPU {
        return double4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_yzxw(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_yzwx, put = set_yzwx) ) double4 yzwx;
    __declspec( property( get = get_yzwx, put = set_yzwx) ) double4 gbar;

    double4 get_yzwx() const __GPU {
        return double4(_M_xyzw[1], _M_xyzw[2], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_yzwx(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_ywxz, put = set_ywxz) ) double4 ywxz;
    __declspec( property( get = get_ywxz, put = set_ywxz) ) double4 garb;

    double4 get_ywxz() const __GPU {
        return double4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_ywxz(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_ywzx, put = set_ywzx) ) double4 ywzx;
    __declspec( property( get = get_ywzx, put = set_ywzx) ) double4 gabr;

    double4 get_ywzx() const __GPU {
        return double4(_M_xyzw[1], _M_xyzw[3], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_ywzx(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[1] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zxyw, put = set_zxyw) ) double4 zxyw;
    __declspec( property( get = get_zxyw, put = set_zxyw) ) double4 brga;

    double4 get_zxyw() const __GPU {
        return double4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[1], _M_xyzw[3]);
    }

    void set_zxyw(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zxwy, put = set_zxwy) ) double4 zxwy;
    __declspec( property( get = get_zxwy, put = set_zxwy) ) double4 brag;

    double4 get_zxwy() const __GPU {
        return double4(_M_xyzw[2], _M_xyzw[0], _M_xyzw[3], _M_xyzw[1]);
    }

    void set_zxwy(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zyxw, put = set_zyxw) ) double4 zyxw;
    __declspec( property( get = get_zyxw, put = set_zyxw) ) double4 bgra;

    double4 get_zyxw() const __GPU {
        return double4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[0], _M_xyzw[3]);
    }

    void set_zyxw(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[3] = _Val.w;
    }

    __declspec( property( get = get_zywx, put = set_zywx) ) double4 zywx;
    __declspec( property( get = get_zywx, put = set_zywx) ) double4 bgar;

    double4 get_zywx() const __GPU {
        return double4(_M_xyzw[2], _M_xyzw[1], _M_xyzw[3], _M_xyzw[0]);
    }

    void set_zywx(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[3] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_zwxy, put = set_zwxy) ) double4 zwxy;
    __declspec( property( get = get_zwxy, put = set_zwxy) ) double4 barg;

    double4 get_zwxy() const __GPU {
        return double4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_zwxy(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_zwyx, put = set_zwyx) ) double4 zwyx;
    __declspec( property( get = get_zwyx, put = set_zwyx) ) double4 bagr;

    double4 get_zwyx() const __GPU {
        return double4(_M_xyzw[2], _M_xyzw[3], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_zwyx(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[2] = _Val.x;
        _M_xyzw[3] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wxyz, put = set_wxyz) ) double4 wxyz;
    __declspec( property( get = get_wxyz, put = set_wxyz) ) double4 argb;

    double4 get_wxyz() const __GPU {
        return double4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[1], _M_xyzw[2]);
    }

    void set_wxyz(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wxzy, put = set_wxzy) ) double4 wxzy;
    __declspec( property( get = get_wxzy, put = set_wxzy) ) double4 arbg;

    double4 get_wxzy() const __GPU {
        return double4(_M_xyzw[3], _M_xyzw[0], _M_xyzw[2], _M_xyzw[1]);
    }

    void set_wxzy(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[0] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wyxz, put = set_wyxz) ) double4 wyxz;
    __declspec( property( get = get_wyxz, put = set_wyxz) ) double4 agrb;

    double4 get_wyxz() const __GPU {
        return double4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[0], _M_xyzw[2]);
    }

    void set_wyxz(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[2] = _Val.w;
    }

    __declspec( property( get = get_wyzx, put = set_wyzx) ) double4 wyzx;
    __declspec( property( get = get_wyzx, put = set_wyzx) ) double4 agbr;

    double4 get_wyzx() const __GPU {
        return double4(_M_xyzw[3], _M_xyzw[1], _M_xyzw[2], _M_xyzw[0]);
    }

    void set_wyzx(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[1] = _Val.y;
        _M_xyzw[2] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

    __declspec( property( get = get_wzxy, put = set_wzxy) ) double4 wzxy;
    __declspec( property( get = get_wzxy, put = set_wzxy) ) double4 abrg;

    double4 get_wzxy() const __GPU {
        return double4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[0], _M_xyzw[1]);
    }

    void set_wzxy(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[0] = _Val.z;
        _M_xyzw[1] = _Val.w;
    }

    __declspec( property( get = get_wzyx, put = set_wzyx) ) double4 wzyx;
    __declspec( property( get = get_wzyx, put = set_wzyx) ) double4 abgr;

    double4 get_wzyx() const __GPU {
        return double4(_M_xyzw[3], _M_xyzw[2], _M_xyzw[1], _M_xyzw[0]);
    }

    void set_wzyx(const double4& _Value) __GPU
    {
        double4 _Val = _Value;
        _M_xyzw[3] = _Val.x;
        _M_xyzw[2] = _Val.y;
        _M_xyzw[1] = _Val.z;
        _M_xyzw[0] = _Val.w;
    }

};


uint2::uint2(const int2& _Other) __GPU
{
    int2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

uint2::uint2(const float2& _Other) __GPU
{
    float2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

uint2::uint2(const unorm2& _Other) __GPU
{
    unorm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

uint2::uint2(const norm2& _Other) __GPU
{
    norm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

uint2::uint2(const double2& _Other) __GPU
{
    double2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}


uint3::uint3(const int3& _Other) __GPU
{
    int3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

uint3::uint3(const float3& _Other) __GPU
{
    float3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

uint3::uint3(const unorm3& _Other) __GPU
{
    unorm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

uint3::uint3(const norm3& _Other) __GPU
{
    norm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

uint3::uint3(const double3& _Other) __GPU
{
    double3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}


uint4::uint4(const int4& _Other) __GPU
{
    int4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

uint4::uint4(const float4& _Other) __GPU
{
    float4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

uint4::uint4(const unorm4& _Other) __GPU
{
    unorm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

uint4::uint4(const norm4& _Other) __GPU
{
    norm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

uint4::uint4(const double4& _Other) __GPU
{
    double4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}


int2::int2(const uint2& _Other) __GPU
{
    uint2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

int2::int2(const float2& _Other) __GPU
{
    float2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

int2::int2(const unorm2& _Other) __GPU
{
    unorm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

int2::int2(const norm2& _Other) __GPU
{
    norm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

int2::int2(const double2& _Other) __GPU
{
    double2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}


int3::int3(const uint3& _Other) __GPU
{
    uint3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

int3::int3(const float3& _Other) __GPU
{
    float3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

int3::int3(const unorm3& _Other) __GPU
{
    unorm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

int3::int3(const norm3& _Other) __GPU
{
    norm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

int3::int3(const double3& _Other) __GPU
{
    double3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}


int4::int4(const uint4& _Other) __GPU
{
    uint4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

int4::int4(const float4& _Other) __GPU
{
    float4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

int4::int4(const unorm4& _Other) __GPU
{
    unorm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

int4::int4(const norm4& _Other) __GPU
{
    norm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

int4::int4(const double4& _Other) __GPU
{
    double4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}


float2::float2(const uint2& _Other) __GPU
{
    uint2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

float2::float2(const int2& _Other) __GPU
{
    int2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

float2::float2(const unorm2& _Other) __GPU
{
    unorm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

float2::float2(const norm2& _Other) __GPU
{
    norm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

float2::float2(const double2& _Other) __GPU
{
    double2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}


float3::float3(const uint3& _Other) __GPU
{
    uint3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

float3::float3(const int3& _Other) __GPU
{
    int3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

float3::float3(const unorm3& _Other) __GPU
{
    unorm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

float3::float3(const norm3& _Other) __GPU
{
    norm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

float3::float3(const double3& _Other) __GPU
{
    double3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}


float4::float4(const uint4& _Other) __GPU
{
    uint4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

float4::float4(const int4& _Other) __GPU
{
    int4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

float4::float4(const unorm4& _Other) __GPU
{
    unorm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

float4::float4(const norm4& _Other) __GPU
{
    norm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

float4::float4(const double4& _Other) __GPU
{
    double4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}


unorm2::unorm2(const uint2& _Other) __GPU
{
    uint2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

unorm2::unorm2(const int2& _Other) __GPU
{
    int2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

unorm2::unorm2(const float2& _Other) __GPU
{
    float2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

unorm2::unorm2(const norm2& _Other) __GPU
{
    norm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

unorm2::unorm2(const double2& _Other) __GPU
{
    double2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}


unorm3::unorm3(const uint3& _Other) __GPU
{
    uint3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

unorm3::unorm3(const int3& _Other) __GPU
{
    int3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

unorm3::unorm3(const float3& _Other) __GPU
{
    float3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

unorm3::unorm3(const norm3& _Other) __GPU
{
    norm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

unorm3::unorm3(const double3& _Other) __GPU
{
    double3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}


unorm4::unorm4(const uint4& _Other) __GPU
{
    uint4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

unorm4::unorm4(const int4& _Other) __GPU
{
    int4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

unorm4::unorm4(const float4& _Other) __GPU
{
    float4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

unorm4::unorm4(const norm4& _Other) __GPU
{
    norm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

unorm4::unorm4(const double4& _Other) __GPU
{
    double4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}


norm2::norm2(const uint2& _Other) __GPU
{
    uint2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

norm2::norm2(const int2& _Other) __GPU
{
    int2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

norm2::norm2(const float2& _Other) __GPU
{
    float2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

norm2::norm2(const unorm2& _Other) __GPU
{
    unorm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

norm2::norm2(const double2& _Other) __GPU
{
    double2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}


norm3::norm3(const uint3& _Other) __GPU
{
    uint3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

norm3::norm3(const int3& _Other) __GPU
{
    int3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

norm3::norm3(const float3& _Other) __GPU
{
    float3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

norm3::norm3(const unorm3& _Other) __GPU
{
    unorm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

norm3::norm3(const double3& _Other) __GPU
{
    double3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}


norm4::norm4(const uint4& _Other) __GPU
{
    uint4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

norm4::norm4(const int4& _Other) __GPU
{
    int4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

norm4::norm4(const float4& _Other) __GPU
{
    float4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

norm4::norm4(const unorm4& _Other) __GPU
{
    unorm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

norm4::norm4(const double4& _Other) __GPU
{
    double4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}


double2::double2(const uint2& _Other) __GPU
{
    uint2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

double2::double2(const int2& _Other) __GPU
{
    int2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

double2::double2(const float2& _Other) __GPU
{
    float2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

double2::double2(const unorm2& _Other) __GPU
{
    unorm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}

double2::double2(const norm2& _Other) __GPU
{
    norm2 _Value = _Other;
    _M_xy[0] = static_cast<value_type>(_Value.x);
    _M_xy[1] = static_cast<value_type>(_Value.y);
}


double3::double3(const uint3& _Other) __GPU
{
    uint3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

double3::double3(const int3& _Other) __GPU
{
    int3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

double3::double3(const float3& _Other) __GPU
{
    float3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

double3::double3(const unorm3& _Other) __GPU
{
    unorm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}

double3::double3(const norm3& _Other) __GPU
{
    norm3 _Value = _Other;
    _M_xyz[0] = static_cast<value_type>(_Value.x);
    _M_xyz[1] = static_cast<value_type>(_Value.y);
    _M_xyz[2] = static_cast<value_type>(_Value.z);
}


double4::double4(const uint4& _Other) __GPU
{
    uint4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

double4::double4(const int4& _Other) __GPU
{
    int4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

double4::double4(const float4& _Other) __GPU
{
    float4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

double4::double4(const unorm4& _Other) __GPU
{
    unorm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}

double4::double4(const norm4& _Other) __GPU
{
    norm4 _Value = _Other;
    _M_xyzw[0] = static_cast<value_type>(_Value.x);
    _M_xyzw[1] = static_cast<value_type>(_Value.y);
    _M_xyzw[2] = static_cast<value_type>(_Value.z);
    _M_xyzw[3] = static_cast<value_type>(_Value.w);
}



inline uint2 operator+(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline uint2 operator-(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline uint2 operator*(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline uint2 operator/(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline uint2 operator%(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x % _Value2.x, _Value1.y % _Value2.y);
}

inline uint2 operator^(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x ^ _Value2.x, _Value1.y ^ _Value2.y);
}

inline uint2 operator|(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x | _Value2.x, _Value1.y | _Value2.y);
}

inline uint2 operator&(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x& _Value2.x, _Value1.y& _Value2.y);
}

inline uint2 operator<<(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x << _Value2.x, _Value1.y << _Value2.y);
}

inline uint2 operator>>(const uint2& _Lhs, const uint2& _Rhs) __GPU
{
    uint2 _Value1 = _Lhs;
    uint2 _Value2 = _Rhs;
    return uint2(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y);
}

inline uint3 operator+(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z);
}

inline uint3 operator-(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z);
}

inline uint3 operator*(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z);
}

inline uint3 operator/(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z);
}

inline bool operator==(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z;
}

inline bool operator!=(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z;
}

inline uint3 operator%(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x % _Value2.x, _Value1.y % _Value2.y, _Value1.z % _Value2.z);
}

inline uint3 operator^(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x ^ _Value2.x, _Value1.y ^ _Value2.y, _Value1.z ^ _Value2.z);
}

inline uint3 operator|(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x | _Value2.x, _Value1.y | _Value2.y, _Value1.z | _Value2.z);
}

inline uint3 operator&(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x& _Value2.x, _Value1.y& _Value2.y, _Value1.z& _Value2.z);
}

inline uint3 operator<<(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x << _Value2.x, _Value1.y << _Value2.y, _Value1.z << _Value2.z);
}

inline uint3 operator>>(const uint3& _Lhs, const uint3& _Rhs) __GPU
{
    uint3 _Value1 = _Lhs;
    uint3 _Value2 = _Rhs;
    return uint3(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y, _Value1.z >> _Value2.z);
}

inline uint4 operator+(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline uint4 operator-(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline uint4 operator*(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline uint4 operator/(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

inline uint4 operator%(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x % _Value2.x, _Value1.y % _Value2.y, _Value1.z % _Value2.z, _Value1.w % _Value2.w);
}

inline uint4 operator^(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x ^ _Value2.x, _Value1.y ^ _Value2.y, _Value1.z ^ _Value2.z, _Value1.w ^ _Value2.w);
}

inline uint4 operator|(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x | _Value2.x, _Value1.y | _Value2.y, _Value1.z | _Value2.z, _Value1.w | _Value2.w);
}

inline uint4 operator&(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x& _Value2.x, _Value1.y& _Value2.y, _Value1.z& _Value2.z, _Value1.w& _Value2.w);
}

inline uint4 operator<<(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x << _Value2.x, _Value1.y << _Value2.y, _Value1.z << _Value2.z, _Value1.w << _Value2.w);
}

inline uint4 operator>>(const uint4& _Lhs, const uint4& _Rhs) __GPU
{
    uint4 _Value1 = _Lhs;
    uint4 _Value2 = _Rhs;
    return uint4(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y, _Value1.z >> _Value2.z, _Value1.w >> _Value2.w);
}

inline int2 operator+(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline int2 operator-(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline int2 operator*(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline int2 operator/(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline int2 operator%(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x % _Value2.x, _Value1.y % _Value2.y);
}

inline int2 operator^(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x ^ _Value2.x, _Value1.y ^ _Value2.y);
}

inline int2 operator|(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x | _Value2.x, _Value1.y | _Value2.y);
}

inline int2 operator&(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x& _Value2.x, _Value1.y& _Value2.y);
}

inline int2 operator<<(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x << _Value2.x, _Value1.y << _Value2.y);
}

inline int2 operator>>(const int2& _Lhs, const int2& _Rhs) __GPU
{
    int2 _Value1 = _Lhs;
    int2 _Value2 = _Rhs;
    return int2(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y);
}

inline int3 operator+(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z);
}

inline int3 operator-(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z);
}

inline int3 operator*(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z);
}

inline int3 operator/(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z);
}

inline bool operator==(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z;
}

inline bool operator!=(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z;
}

inline int3 operator%(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x % _Value2.x, _Value1.y % _Value2.y, _Value1.z % _Value2.z);
}

inline int3 operator^(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x ^ _Value2.x, _Value1.y ^ _Value2.y, _Value1.z ^ _Value2.z);
}

inline int3 operator|(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x | _Value2.x, _Value1.y | _Value2.y, _Value1.z | _Value2.z);
}

inline int3 operator&(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x& _Value2.x, _Value1.y& _Value2.y, _Value1.z& _Value2.z);
}

inline int3 operator<<(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x << _Value2.x, _Value1.y << _Value2.y, _Value1.z << _Value2.z);
}

inline int3 operator>>(const int3& _Lhs, const int3& _Rhs) __GPU
{
    int3 _Value1 = _Lhs;
    int3 _Value2 = _Rhs;
    return int3(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y, _Value1.z >> _Value2.z);
}

inline int4 operator+(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline int4 operator-(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline int4 operator*(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline int4 operator/(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

inline int4 operator%(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x % _Value2.x, _Value1.y % _Value2.y, _Value1.z % _Value2.z, _Value1.w % _Value2.w);
}

inline int4 operator^(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x ^ _Value2.x, _Value1.y ^ _Value2.y, _Value1.z ^ _Value2.z, _Value1.w ^ _Value2.w);
}

inline int4 operator|(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x | _Value2.x, _Value1.y | _Value2.y, _Value1.z | _Value2.z, _Value1.w | _Value2.w);
}

inline int4 operator&(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x& _Value2.x, _Value1.y& _Value2.y, _Value1.z& _Value2.z, _Value1.w& _Value2.w);
}

inline int4 operator<<(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x << _Value2.x, _Value1.y << _Value2.y, _Value1.z << _Value2.z, _Value1.w << _Value2.w);
}

inline int4 operator>>(const int4& _Lhs, const int4& _Rhs) __GPU
{
    int4 _Value1 = _Lhs;
    int4 _Value2 = _Rhs;
    return int4(_Value1.x >> _Value2.x, _Value1.y >> _Value2.y, _Value1.z >> _Value2.z, _Value1.w >> _Value2.w);
}

inline float2 operator+(const float2& _Lhs, const float2& _Rhs) __GPU
{
    float2 _Value1 = _Lhs;
    float2 _Value2 = _Rhs;
    return float2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline float2 operator-(const float2& _Lhs, const float2& _Rhs) __GPU
{
    float2 _Value1 = _Lhs;
    float2 _Value2 = _Rhs;
    return float2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline float2 operator*(const float2& _Lhs, const float2& _Rhs) __GPU
{
    float2 _Value1 = _Lhs;
    float2 _Value2 = _Rhs;
    return float2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline float2 operator/(const float2& _Lhs, const float2& _Rhs) __GPU
{
    float2 _Value1 = _Lhs;
    float2 _Value2 = _Rhs;
    return float2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const float2& _Lhs, const float2& _Rhs) __GPU
{
    float2 _Value1 = _Lhs;
    float2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const float2& _Lhs, const float2& _Rhs) __GPU
{
    float2 _Value1 = _Lhs;
    float2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline float3 operator+(const float3& _Lhs, const float3& _Rhs) __GPU
{
    float3 _Value1 = _Lhs;
    float3 _Value2 = _Rhs;
    return float3(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z);
}

inline float3 operator-(const float3& _Lhs, const float3& _Rhs) __GPU
{
    float3 _Value1 = _Lhs;
    float3 _Value2 = _Rhs;
    return float3(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z);
}

inline float3 operator*(const float3& _Lhs, const float3& _Rhs) __GPU
{
    float3 _Value1 = _Lhs;
    float3 _Value2 = _Rhs;
    return float3(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z);
}

inline float3 operator/(const float3& _Lhs, const float3& _Rhs) __GPU
{
    float3 _Value1 = _Lhs;
    float3 _Value2 = _Rhs;
    return float3(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z);
}

inline bool operator==(const float3& _Lhs, const float3& _Rhs) __GPU
{
    float3 _Value1 = _Lhs;
    float3 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z;
}

inline bool operator!=(const float3& _Lhs, const float3& _Rhs) __GPU
{
    float3 _Value1 = _Lhs;
    float3 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z;
}

inline float4 operator+(const float4& _Lhs, const float4& _Rhs) __GPU
{
    float4 _Value1 = _Lhs;
    float4 _Value2 = _Rhs;
    return float4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline float4 operator-(const float4& _Lhs, const float4& _Rhs) __GPU
{
    float4 _Value1 = _Lhs;
    float4 _Value2 = _Rhs;
    return float4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline float4 operator*(const float4& _Lhs, const float4& _Rhs) __GPU
{
    float4 _Value1 = _Lhs;
    float4 _Value2 = _Rhs;
    return float4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline float4 operator/(const float4& _Lhs, const float4& _Rhs) __GPU
{
    float4 _Value1 = _Lhs;
    float4 _Value2 = _Rhs;
    return float4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const float4& _Lhs, const float4& _Rhs) __GPU
{
    float4 _Value1 = _Lhs;
    float4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const float4& _Lhs, const float4& _Rhs) __GPU
{
    float4 _Value1 = _Lhs;
    float4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

inline unorm2 operator+(const unorm2& _Lhs, const unorm2& _Rhs) __GPU
{
    unorm2 _Value1 = _Lhs;
    unorm2 _Value2 = _Rhs;
    return unorm2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline unorm2 operator-(const unorm2& _Lhs, const unorm2& _Rhs) __GPU
{
    unorm2 _Value1 = _Lhs;
    unorm2 _Value2 = _Rhs;
    return unorm2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline unorm2 operator*(const unorm2& _Lhs, const unorm2& _Rhs) __GPU
{
    unorm2 _Value1 = _Lhs;
    unorm2 _Value2 = _Rhs;
    return unorm2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline unorm2 operator/(const unorm2& _Lhs, const unorm2& _Rhs) __GPU
{
    unorm2 _Value1 = _Lhs;
    unorm2 _Value2 = _Rhs;
    return unorm2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const unorm2& _Lhs, const unorm2& _Rhs) __GPU
{
    unorm2 _Value1 = _Lhs;
    unorm2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const unorm2& _Lhs, const unorm2& _Rhs) __GPU
{
    unorm2 _Value1 = _Lhs;
    unorm2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline unorm3 operator+(const unorm3& _Lhs, const unorm3& _Rhs) __GPU
{
    unorm3 _Value1 = _Lhs;
    unorm3 _Value2 = _Rhs;
    return unorm3(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z);
}

inline unorm3 operator-(const unorm3& _Lhs, const unorm3& _Rhs) __GPU
{
    unorm3 _Value1 = _Lhs;
    unorm3 _Value2 = _Rhs;
    return unorm3(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z);
}

inline unorm3 operator*(const unorm3& _Lhs, const unorm3& _Rhs) __GPU
{
    unorm3 _Value1 = _Lhs;
    unorm3 _Value2 = _Rhs;
    return unorm3(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z);
}

inline unorm3 operator/(const unorm3& _Lhs, const unorm3& _Rhs) __GPU
{
    unorm3 _Value1 = _Lhs;
    unorm3 _Value2 = _Rhs;
    return unorm3(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z);
}

inline bool operator==(const unorm3& _Lhs, const unorm3& _Rhs) __GPU
{
    unorm3 _Value1 = _Lhs;
    unorm3 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z;
}

inline bool operator!=(const unorm3& _Lhs, const unorm3& _Rhs) __GPU
{
    unorm3 _Value1 = _Lhs;
    unorm3 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z;
}

inline unorm4 operator+(const unorm4& _Lhs, const unorm4& _Rhs) __GPU
{
    unorm4 _Value1 = _Lhs;
    unorm4 _Value2 = _Rhs;
    return unorm4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline unorm4 operator-(const unorm4& _Lhs, const unorm4& _Rhs) __GPU
{
    unorm4 _Value1 = _Lhs;
    unorm4 _Value2 = _Rhs;
    return unorm4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline unorm4 operator*(const unorm4& _Lhs, const unorm4& _Rhs) __GPU
{
    unorm4 _Value1 = _Lhs;
    unorm4 _Value2 = _Rhs;
    return unorm4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline unorm4 operator/(const unorm4& _Lhs, const unorm4& _Rhs) __GPU
{
    unorm4 _Value1 = _Lhs;
    unorm4 _Value2 = _Rhs;
    return unorm4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const unorm4& _Lhs, const unorm4& _Rhs) __GPU
{
    unorm4 _Value1 = _Lhs;
    unorm4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const unorm4& _Lhs, const unorm4& _Rhs) __GPU
{
    unorm4 _Value1 = _Lhs;
    unorm4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

inline norm2 operator+(const norm2& _Lhs, const norm2& _Rhs) __GPU
{
    norm2 _Value1 = _Lhs;
    norm2 _Value2 = _Rhs;
    return norm2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline norm2 operator-(const norm2& _Lhs, const norm2& _Rhs) __GPU
{
    norm2 _Value1 = _Lhs;
    norm2 _Value2 = _Rhs;
    return norm2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline norm2 operator*(const norm2& _Lhs, const norm2& _Rhs) __GPU
{
    norm2 _Value1 = _Lhs;
    norm2 _Value2 = _Rhs;
    return norm2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline norm2 operator/(const norm2& _Lhs, const norm2& _Rhs) __GPU
{
    norm2 _Value1 = _Lhs;
    norm2 _Value2 = _Rhs;
    return norm2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const norm2& _Lhs, const norm2& _Rhs) __GPU
{
    norm2 _Value1 = _Lhs;
    norm2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const norm2& _Lhs, const norm2& _Rhs) __GPU
{
    norm2 _Value1 = _Lhs;
    norm2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline norm3 operator+(const norm3& _Lhs, const norm3& _Rhs) __GPU
{
    norm3 _Value1 = _Lhs;
    norm3 _Value2 = _Rhs;
    return norm3(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z);
}

inline norm3 operator-(const norm3& _Lhs, const norm3& _Rhs) __GPU
{
    norm3 _Value1 = _Lhs;
    norm3 _Value2 = _Rhs;
    return norm3(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z);
}

inline norm3 operator*(const norm3& _Lhs, const norm3& _Rhs) __GPU
{
    norm3 _Value1 = _Lhs;
    norm3 _Value2 = _Rhs;
    return norm3(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z);
}

inline norm3 operator/(const norm3& _Lhs, const norm3& _Rhs) __GPU
{
    norm3 _Value1 = _Lhs;
    norm3 _Value2 = _Rhs;
    return norm3(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z);
}

inline bool operator==(const norm3& _Lhs, const norm3& _Rhs) __GPU
{
    norm3 _Value1 = _Lhs;
    norm3 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z;
}

inline bool operator!=(const norm3& _Lhs, const norm3& _Rhs) __GPU
{
    norm3 _Value1 = _Lhs;
    norm3 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z;
}

inline norm4 operator+(const norm4& _Lhs, const norm4& _Rhs) __GPU
{
    norm4 _Value1 = _Lhs;
    norm4 _Value2 = _Rhs;
    return norm4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline norm4 operator-(const norm4& _Lhs, const norm4& _Rhs) __GPU
{
    norm4 _Value1 = _Lhs;
    norm4 _Value2 = _Rhs;
    return norm4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline norm4 operator*(const norm4& _Lhs, const norm4& _Rhs) __GPU
{
    norm4 _Value1 = _Lhs;
    norm4 _Value2 = _Rhs;
    return norm4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline norm4 operator/(const norm4& _Lhs, const norm4& _Rhs) __GPU
{
    norm4 _Value1 = _Lhs;
    norm4 _Value2 = _Rhs;
    return norm4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const norm4& _Lhs, const norm4& _Rhs) __GPU
{
    norm4 _Value1 = _Lhs;
    norm4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const norm4& _Lhs, const norm4& _Rhs) __GPU
{
    norm4 _Value1 = _Lhs;
    norm4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

inline double2 operator+(const double2& _Lhs, const double2& _Rhs) __GPU
{
    double2 _Value1 = _Lhs;
    double2 _Value2 = _Rhs;
    return double2(_Value1.x + _Value2.x, _Value1.y + _Value2.y);
}

inline double2 operator-(const double2& _Lhs, const double2& _Rhs) __GPU
{
    double2 _Value1 = _Lhs;
    double2 _Value2 = _Rhs;
    return double2(_Value1.x - _Value2.x, _Value1.y - _Value2.y);
}

inline double2 operator*(const double2& _Lhs, const double2& _Rhs) __GPU
{
    double2 _Value1 = _Lhs;
    double2 _Value2 = _Rhs;
    return double2(_Value1.x* _Value2.x, _Value1.y* _Value2.y);
}

inline double2 operator/(const double2& _Lhs, const double2& _Rhs) __GPU
{
    double2 _Value1 = _Lhs;
    double2 _Value2 = _Rhs;
    return double2(_Value1.x / _Value2.x, _Value1.y / _Value2.y);
}

inline bool operator==(const double2& _Lhs, const double2& _Rhs) __GPU
{
    double2 _Value1 = _Lhs;
    double2 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y;
}

inline bool operator!=(const double2& _Lhs, const double2& _Rhs) __GPU
{
    double2 _Value1 = _Lhs;
    double2 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y;
}

inline double3 operator+(const double3& _Lhs, const double3& _Rhs) __GPU
{
    double3 _Value1 = _Lhs;
    double3 _Value2 = _Rhs;
    return double3(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z);
}

inline double3 operator-(const double3& _Lhs, const double3& _Rhs) __GPU
{
    double3 _Value1 = _Lhs;
    double3 _Value2 = _Rhs;
    return double3(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z);
}

inline double3 operator*(const double3& _Lhs, const double3& _Rhs) __GPU
{
    double3 _Value1 = _Lhs;
    double3 _Value2 = _Rhs;
    return double3(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z);
}

inline double3 operator/(const double3& _Lhs, const double3& _Rhs) __GPU
{
    double3 _Value1 = _Lhs;
    double3 _Value2 = _Rhs;
    return double3(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z);
}

inline bool operator==(const double3& _Lhs, const double3& _Rhs) __GPU
{
    double3 _Value1 = _Lhs;
    double3 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z;
}

inline bool operator!=(const double3& _Lhs, const double3& _Rhs) __GPU
{
    double3 _Value1 = _Lhs;
    double3 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z;
}

inline double4 operator+(const double4& _Lhs, const double4& _Rhs) __GPU
{
    double4 _Value1 = _Lhs;
    double4 _Value2 = _Rhs;
    return double4(_Value1.x + _Value2.x, _Value1.y + _Value2.y, _Value1.z + _Value2.z, _Value1.w + _Value2.w);
}

inline double4 operator-(const double4& _Lhs, const double4& _Rhs) __GPU
{
    double4 _Value1 = _Lhs;
    double4 _Value2 = _Rhs;
    return double4(_Value1.x - _Value2.x, _Value1.y - _Value2.y, _Value1.z - _Value2.z, _Value1.w - _Value2.w);
}

inline double4 operator*(const double4& _Lhs, const double4& _Rhs) __GPU
{
    double4 _Value1 = _Lhs;
    double4 _Value2 = _Rhs;
    return double4(_Value1.x* _Value2.x, _Value1.y* _Value2.y, _Value1.z* _Value2.z, _Value1.w* _Value2.w);
}

inline double4 operator/(const double4& _Lhs, const double4& _Rhs) __GPU
{
    double4 _Value1 = _Lhs;
    double4 _Value2 = _Rhs;
    return double4(_Value1.x / _Value2.x, _Value1.y / _Value2.y, _Value1.z / _Value2.z, _Value1.w / _Value2.w);
}

inline bool operator==(const double4& _Lhs, const double4& _Rhs) __GPU
{
    double4 _Value1 = _Lhs;
    double4 _Value2 = _Rhs;
    return _Value1.x == _Value2.x && _Value1.y == _Value2.y && _Value1.z == _Value2.z && _Value1.w == _Value2.w;
}

inline bool operator!=(const double4& _Lhs, const double4& _Rhs) __GPU
{
    double4 _Value1 = _Lhs;
    double4 _Value2 = _Rhs;
    return _Value1.x != _Value2.x || _Value1.y != _Value2.y || _Value1.z != _Value2.z || _Value1.w != _Value2.w;
}

template<>
struct short_vector_traits<uint2>
{
    typedef unsigned int value_type;
    static int const size = 2;
};

template<>
struct short_vector_traits<uint3>
{
    typedef unsigned int value_type;
    static int const size = 3;
};

template<>
struct short_vector_traits<uint4>
{
    typedef unsigned int value_type;
    static int const size = 4;
};

template<>
struct short_vector_traits<int2>
{
    typedef int value_type;
    static int const size = 2;
};

template<>
struct short_vector_traits<int3>
{
    typedef int value_type;
    static int const size = 3;
};

template<>
struct short_vector_traits<int4>
{
    typedef int value_type;
    static int const size = 4;
};

template<>
struct short_vector_traits<float2>
{
    typedef float value_type;
    static int const size = 2;
};

template<>
struct short_vector_traits<float3>
{
    typedef float value_type;
    static int const size = 3;
};

template<>
struct short_vector_traits<float4>
{
    typedef float value_type;
    static int const size = 4;
};

template<>
struct short_vector_traits<unorm2>
{
    typedef unorm value_type;
    static int const size = 2;
};

template<>
struct short_vector_traits<unorm3>
{
    typedef unorm value_type;
    static int const size = 3;
};

template<>
struct short_vector_traits<unorm4>
{
    typedef unorm value_type;
    static int const size = 4;
};

template<>
struct short_vector_traits<norm2>
{
    typedef norm value_type;
    static int const size = 2;
};

template<>
struct short_vector_traits<norm3>
{
    typedef norm value_type;
    static int const size = 3;
};

template<>
struct short_vector_traits<norm4>
{
    typedef norm value_type;
    static int const size = 4;
};

template<>
struct short_vector_traits<double2>
{
    typedef double value_type;
    static int const size = 2;
};

template<>
struct short_vector_traits<double3>
{
    typedef double value_type;
    static int const size = 3;
};

template<>
struct short_vector_traits<double4>
{
    typedef double value_type;
    static int const size = 4;
};

namespace details
{

template<>
struct _Short_vector_type_traits<uint2>
{
    typedef uint2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Uint_type;
    static const unsigned int _Num_channels = 2;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<uint3>
{
    typedef uint3::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = false;
    static const _Short_vector_base_type_id _Format_base_type_id = _Invalid_type;
    static const unsigned int _Num_channels = 0;
    static const unsigned int _Default_bits_per_channel = 0;
};

template<>
struct _Short_vector_type_traits<uint4>
{
    typedef uint4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Uint_type;
    static const unsigned int _Num_channels = 4;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<int2>
{
    typedef int2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Int_type;
    static const unsigned int _Num_channels = 2;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<int3>
{
    typedef int3::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = false;
    static const _Short_vector_base_type_id _Format_base_type_id = _Invalid_type;
    static const unsigned int _Num_channels = 0;
    static const unsigned int _Default_bits_per_channel = 0;
};

template<>
struct _Short_vector_type_traits<int4>
{
    typedef int4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
   static const _Short_vector_base_type_id _Format_base_type_id = _Int_type;
    static const unsigned int _Num_channels = 4;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<float2>
{
    typedef float2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
    static const _Short_vector_base_type_id _Format_base_type_id = _Float_type;
    static const unsigned int _Num_channels = 2;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<float3>
{
    typedef float3::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = false;
    static const _Short_vector_base_type_id _Format_base_type_id = _Invalid_type;
    static const unsigned int _Num_channels = 0;
    static const unsigned int _Default_bits_per_channel = 0;
};

template<>
struct _Short_vector_type_traits<float4>
{
    typedef float4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
    static const _Short_vector_base_type_id _Format_base_type_id = _Float_type;
    static const unsigned int _Num_channels = 4;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<unorm2>
{
    typedef unorm2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
    static const _Short_vector_base_type_id _Format_base_type_id = _Unorm_type;
    static const unsigned int _Num_channels = 2;
    static const unsigned int _Default_bits_per_channel = 16;
};

template<>
struct _Short_vector_type_traits<unorm3>
{
    typedef unorm3::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = false;
    static const _Short_vector_base_type_id _Format_base_type_id = _Invalid_type;
    static const unsigned int _Num_channels = 0;
    static const unsigned int _Default_bits_per_channel = 0;
};

template<>
struct _Short_vector_type_traits<unorm4>
{
    typedef unorm4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
    static const _Short_vector_base_type_id _Format_base_type_id = _Unorm_type;
    static const unsigned int _Num_channels = 4;
    static const unsigned int _Default_bits_per_channel = 16;
};

template<>
struct _Short_vector_type_traits<norm2>
{
    typedef norm2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
    static const _Short_vector_base_type_id _Format_base_type_id = _Norm_type;
    static const unsigned int _Num_channels = 2;
    static const unsigned int _Default_bits_per_channel = 16;
};

template<>
struct _Short_vector_type_traits<norm3>
{
    typedef norm3::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = false;
    static const _Short_vector_base_type_id _Format_base_type_id = _Invalid_type;
    static const unsigned int _Num_channels = 0;
    static const unsigned int _Default_bits_per_channel = 0;
};

template<>
struct _Short_vector_type_traits<norm4>
{
    typedef norm4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
    static const _Short_vector_base_type_id _Format_base_type_id = _Norm_type;
    static const unsigned int _Num_channels = 4;
    static const unsigned int _Default_bits_per_channel = 16;
};

template<>
struct _Short_vector_type_traits<double2>
{
    typedef double2::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = true;
    static const _Short_vector_base_type_id _Format_base_type_id = _Double_type;
    static const unsigned int _Num_channels = 4;
    static const unsigned int _Default_bits_per_channel = 32;
};

template<>
struct _Short_vector_type_traits<double3>
{
    typedef double3::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = false;
    static const _Short_vector_base_type_id _Format_base_type_id = _Invalid_type;
    static const unsigned int _Num_channels = 0;
    static const unsigned int _Default_bits_per_channel = 0;
};

template<>
struct _Short_vector_type_traits<double4>
{
    typedef double4::value_type _Scalar_type;
    static const bool _Is_valid_SVT_for_texture = false;
    static const _Short_vector_base_type_id _Format_base_type_id = _Invalid_type;
    static const unsigned int _Num_channels = 0;
    static const unsigned int _Default_bits_per_channel = 0;
};

} // namespace details

} // namespace graphics

} // namespace Concurrency
#pragma warning(pop)
// End of generated file
