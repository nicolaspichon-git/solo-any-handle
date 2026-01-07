//------------------------------------------------------------------------------
//
// Copyright (c) 2020 Nicolas Pichon
//
// Distributed under the Boost Software License, Version 1.0.
//    (See http://www.boost.org/LICENSE_1_0.txt)
//
//------------------------------------------------------------------------------

#include <boost/core/ignore_unused.hpp>
#include <boost/test/unit_test.hpp>

////////////////////////////////////////////////////////////////////////////////
namespace solo { namespace tests {
////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( SoloAnyHandleTestSuite )

//..............................................................................

class TestObjectBase
{
public:
    virtual ~TestObjectBase() noexcept = default;
    virtual int data() const noexcept { return -1; }
    virtual void setdata(int a_)  { boost::ignore_unused(a_); }
    bool operator==(TestObjectBase const &another) const noexcept { return data() == another.data(); }
    bool operator!=(TestObjectBase const &another) const noexcept { return data() != another.data(); }
};

class TestObject final: public TestObjectBase
{
public:
    explicit TestObject(int a_ = 0) noexcept : a(a_) {}
    int data() const noexcept override { return a; }
    void setdata(int a_) override { a = a_;}
private:
    int a;
};

//..............................................................................

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////
}}// EONS SOLOTESTS
////////////////////////////////////////////////////////////////////////////////
