#ifndef __GCWEAKREF__
#define __GCWEAKREF__

using namespace System;
using namespace System::Runtime::InteropServices;

template <typename T>
class gcweakref
{
private:
	IntPtr handle;
public:
	gcweakref()
	{
		handle = GCHandle::ToIntPtr(GCHandle::Alloc(nullptr,GCHandleType::Weak));
	}

	gcweakref(T value)
	{
		handle = GCHandle::ToIntPtr(GCHandle::Alloc(value,GCHandleType::Weak));
	}

	gcweakref(const gcweakref &other)
	{
		handle = GCHandle::ToIntPtr(GCHandle::Alloc(GCHandle::FromIntPtr(other.handle).Target,GCHandleType::Weak));
	}

	gcweakref &operator=(T value)
	{
		GCHandle::FromIntPtr(handle).Target = value;
		return *this;
	}

	gcweakref &operator=(const gcweakref &other)
	{
		GCHandle::FromIntPtr(handle).Target = GCHandle::FromIntPtr(other.handle).Target;
		return *this;
	}

	operator T() const
	{
		return (T)GCHandle::FromIntPtr(handle).Target;
	}

	T operator->() const
	{
		return (T)GCHandle::FromIntPtr(handle).Target;
	}

	~gcweakref()
	{
		GCHandle::FromIntPtr(handle).Free();
	}
};

#endif
