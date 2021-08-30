//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
//
// Ice version 3.7.6
//
// <auto-generated>
//
// Generated from file `common_event.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __common_event_h__
#define __common_event_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/ValueF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Comparable.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/GCObject.h>
#include <Ice/Value.h>
#include <Ice/Incoming.h>
#include <Ice/IncomingAsync.h>
#include <Ice/FactoryTableInit.h>
#include <IceUtil/ScopedArray.h>
#include <Ice/Optional.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 307
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 >= 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 6
#       error Ice patch level mismatch!
#   endif
#endif

#ifdef ICE_CPP11_MAPPING // C++11 mapping

namespace squarepro
{


namespace event
{

class IEvent;
class IEventService;
class IEventServicePrx;

}

}

namespace squarepro
{

namespace event
{

class IEventService : public virtual ::Ice::Object
{
public:

    using ProxyType = IEventServicePrx;

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(::std::string id, const ::Ice::Current& current) const override;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector<::std::string> ice_ids(const ::Ice::Current& current) const override;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual ::std::string ice_id(const ::Ice::Current& current) const override;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    virtual void handleAsync(::std::shared_ptr<IEvent> event, ::std::function<void()> response, ::std::function<void(::std::exception_ptr)> exception, const ::Ice::Current& current) = 0;
    /// \cond INTERNAL
    bool _iceD_handle(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

    /// \cond INTERNAL
    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&) override;
    /// \endcond
};

}

}

namespace squarepro
{

namespace event
{

class IEvent : public ::Ice::ValueHelper<IEvent, ::Ice::Value>
{
public:

    virtual ~IEvent();

    IEvent() = default;

    IEvent(const IEvent&) = default;
    IEvent(IEvent&&) = default;
    IEvent& operator=(const IEvent&) = default;
    IEvent& operator=(IEvent&&) = default;

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<> ice_tuple() const
    {
        return std::tie();
    }

    /**
     * Obtains the Slice type ID of this value.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();
};

/// \cond INTERNAL
static IEvent _iceS_IEvent_init;
/// \endcond

}

}

namespace squarepro
{

namespace event
{

class IEventServicePrx : public virtual ::Ice::Proxy<IEventServicePrx, ::Ice::ObjectPrx>
{
public:

    void handle(const ::std::shared_ptr<IEvent>& event, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        _makePromiseOutgoing<void>(true, this, &IEventServicePrx::_iceI_handle, event, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto handleAsync(const ::std::shared_ptr<IEvent>& event, const ::Ice::Context& context = ::Ice::noExplicitContext)
        -> decltype(::std::declval<P<void>>().get_future())
    {
        return _makePromiseOutgoing<void, P>(false, this, &IEventServicePrx::_iceI_handle, event, context);
    }

    ::std::function<void()>
    handleAsync(const ::std::shared_ptr<IEvent>& event,
                ::std::function<void()> response,
                ::std::function<void(::std::exception_ptr)> ex = nullptr,
                ::std::function<void(bool)> sent = nullptr,
                const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<void>(std::move(response), std::move(ex), std::move(sent), this, &squarepro::event::IEventServicePrx::_iceI_handle, event, context);
    }

    /// \cond INTERNAL
    void _iceI_handle(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<void>>&, const ::std::shared_ptr<IEvent>&, const ::Ice::Context&);
    /// \endcond

    /**
     * Obtains the Slice type ID of this interface.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:

    /// \cond INTERNAL
    IEventServicePrx() = default;
    friend ::std::shared_ptr<IEventServicePrx> IceInternal::createProxy<IEventServicePrx>();

    virtual ::std::shared_ptr<::Ice::ObjectPrx> _newInstance() const override;
    /// \endcond
};

}

}

/// \cond STREAM
namespace Ice
{

}
/// \endcond

/// \cond INTERNAL
namespace squarepro
{

/// \cond INTERNAL
namespace event
{

using IEventPtr = ::std::shared_ptr<IEvent>;

using IEventServicePtr = ::std::shared_ptr<IEventService>;
using IEventServicePrxPtr = ::std::shared_ptr<IEventServicePrx>;

}
/// \endcond

}
/// \endcond

#else // C++98 mapping

namespace IceProxy
{

namespace squarepro
{

namespace event
{

class IEvent;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< IEvent>&);
::IceProxy::Ice::Object* upCast(IEvent*);
/// \endcond

class IEventService;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< IEventService>&);
::IceProxy::Ice::Object* upCast(IEventService*);
/// \endcond

}

}

}

namespace squarepro
{

namespace event
{

class IEvent;
/// \cond INTERNAL
::Ice::Object* upCast(IEvent*);
/// \endcond
typedef ::IceInternal::Handle< IEvent> IEventPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::squarepro::event::IEvent> IEventPrx;
typedef IEventPrx IEventPrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(IEventPtr&, const ::Ice::ObjectPtr&);
/// \endcond

class IEventService;
/// \cond INTERNAL
::Ice::Object* upCast(IEventService*);
/// \endcond
typedef ::IceInternal::Handle< IEventService> IEventServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::squarepro::event::IEventService> IEventServicePrx;
typedef IEventServicePrx IEventServicePrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(IEventServicePtr&, const ::Ice::ObjectPtr&);
/// \endcond

}

}

namespace squarepro
{

namespace event
{

/**
 * AMD callback class for squarepro::event::IEventService::handle_async.
 * Call the ice_response method for a successful completion, or the ice_exception
 * method in the case of an error.
 */
class AMD_IEventService_handle : public virtual ::Ice::AMDCallback
{
public:

    virtual ~AMD_IEventService_handle();

    /**
     * Call ice_response for a successful completion.
     */
    virtual void ice_response() = 0;
};

typedef ::IceUtil::Handle< ::squarepro::event::AMD_IEventService_handle> AMD_IEventService_handlePtr;

}

}

/// \cond INTERNAL
namespace IceAsync
{

namespace squarepro
{

namespace event
{

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#   pragma warning(push)
#   pragma warning(disable:4239)
#endif

class AMD_IEventService_handle : public ::squarepro::event::AMD_IEventService_handle, public ::IceInternal::IncomingAsync
{
public:

    AMD_IEventService_handle(::IceInternal::Incoming&);

    virtual void ice_response();
};

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#   pragma warning(pop)
#endif

}

}

}
/// \endcond

namespace squarepro
{

namespace event
{

/**
 * Base class for asynchronous callback wrapper classes used for calls to
 * IceProxy::squarepro::event::IEventService::begin_handle.
 * Create a wrapper instance by calling ::squarepro::event::newCallback_IEventService_handle.
 */
class Callback_IEventService_handle_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_IEventService_handle_Base> Callback_IEventService_handlePtr;

}

}

namespace IceProxy
{

namespace squarepro
{

namespace event
{

class IEvent : public virtual ::Ice::Proxy<IEvent, ::IceProxy::Ice::Object>
{
public:

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:
    /// \cond INTERNAL

    virtual ::IceProxy::Ice::Object* _newInstance() const;
    /// \endcond
};

class IEventService : public virtual ::Ice::Proxy<IEventService, ::IceProxy::Ice::Object>
{
public:

    void handle(const ::squarepro::event::IEventPtr& event, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        end_handle(_iceI_begin_handle(event, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_handle(const ::squarepro::event::IEventPtr& event, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_handle(event, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_handle(const ::squarepro::event::IEventPtr& event, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_handle(event, ::Ice::noExplicitContext, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_handle(const ::squarepro::event::IEventPtr& event, const ::Ice::Context& context, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_handle(event, context, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_handle(const ::squarepro::event::IEventPtr& event, const ::squarepro::event::Callback_IEventService_handlePtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_handle(event, ::Ice::noExplicitContext, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_handle(const ::squarepro::event::IEventPtr& event, const ::Ice::Context& context, const ::squarepro::event::Callback_IEventService_handlePtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_handle(event, context, cb, cookie);
    }

    void end_handle(const ::Ice::AsyncResultPtr& result);

private:

    ::Ice::AsyncResultPtr _iceI_begin_handle(const ::squarepro::event::IEventPtr&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

public:

    /**
     * Obtains the Slice type ID corresponding to this interface.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:
    /// \cond INTERNAL

    virtual ::IceProxy::Ice::Object* _newInstance() const;
    /// \endcond
};

}

}

}

namespace squarepro
{

namespace event
{

class IEvent : public virtual ::Ice::Object
{
public:

    typedef IEventPrx ProxyType;
    typedef IEventPtr PointerType;

    virtual ~IEvent();

    IEvent()
    {
    }

#ifdef ICE_CPP11_COMPILER
    IEvent(const IEvent&) = default;
    IEvent& operator=(const IEvent&) = default;
#endif

    /**
     * Polymorphically clones this object.
     * @return A shallow copy of this object.
     */
    virtual ::Ice::ObjectPtr ice_clone() const;

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(const ::std::string& id, const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual const ::std::string& ice_id(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    /**
     * Obtains a value factory that instantiates this class.
     * @return The value factory.
     */
    static ::Ice::ValueFactoryPtr ice_factory();

protected:

    /// \cond STREAM
    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
    /// \endcond
};
/// \cond INTERNAL
static ::Ice::ValueFactoryPtr _iceS_IEvent_init = ::squarepro::event::IEvent::ice_factory();
/// \endcond

/// \cond INTERNAL
inline bool operator==(const IEvent& lhs, const IEvent& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const IEvent& lhs, const IEvent& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

class IEventService : public virtual ::Ice::Object
{
public:

    typedef IEventServicePrx ProxyType;
    typedef IEventServicePtr PointerType;

    virtual ~IEventService();

#ifdef ICE_CPP11_COMPILER
    IEventService() = default;
    IEventService(const IEventService&) = default;
    IEventService& operator=(const IEventService&) = default;
#endif

    /**
     * Determines whether this object supports an interface with the given Slice type ID.
     * @param id The fully-scoped Slice type ID.
     * @param current The Current object for the invocation.
     * @return True if this object supports the interface, false, otherwise.
     */
    virtual bool ice_isA(const ::std::string& id, const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a list of the Slice type IDs representing the interfaces supported by this object.
     * @param current The Current object for the invocation.
     * @return A list of fully-scoped type IDs.
     */
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains a Slice type ID representing the most-derived interface supported by this object.
     * @param current The Current object for the invocation.
     * @return A fully-scoped type ID.
     */
    virtual const ::std::string& ice_id(const ::Ice::Current& current = ::Ice::emptyCurrent) const;

    /**
     * Obtains the Slice type ID corresponding to this class.
     * @return A fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    virtual void handle_async(const ::squarepro::event::AMD_IEventService_handlePtr& cb, const IEventPtr& event, const ::Ice::Current& current = ::Ice::emptyCurrent) = 0;
    /// \cond INTERNAL
    bool _iceD_handle(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

    /// \cond INTERNAL
    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

protected:

    /// \cond STREAM
    virtual void _iceWriteImpl(::Ice::OutputStream*) const;
    virtual void _iceReadImpl(::Ice::InputStream*);
    /// \endcond
};

/// \cond INTERNAL
inline bool operator==(const IEventService& lhs, const IEventService& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const IEventService& lhs, const IEventService& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

}

}

/// \cond STREAM
namespace Ice
{

}
/// \endcond

namespace squarepro
{

namespace event
{

/**
 * Type-safe asynchronous callback wrapper class used for calls to
 * IceProxy::squarepro::event::IEventService::begin_handle.
 * Create a wrapper instance by calling ::squarepro::event::newCallback_IEventService_handle.
 */
template<class T>
class CallbackNC_IEventService_handle : public Callback_IEventService_handle_Base, public ::IceInternal::OnewayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)();

    CallbackNC_IEventService_handle(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallbackNC<T>(obj, cb, excb, sentcb)
    {
    }
};

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T> Callback_IEventService_handlePtr
newCallback_IEventService_handle(const IceUtil::Handle<T>& instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_IEventService_handle<T>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T> Callback_IEventService_handlePtr
newCallback_IEventService_handle(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_IEventService_handle<T>(instance, 0, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T> Callback_IEventService_handlePtr
newCallback_IEventService_handle(T* instance, void (T::*cb)(), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_IEventService_handle<T>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T> Callback_IEventService_handlePtr
newCallback_IEventService_handle(T* instance, void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_IEventService_handle<T>(instance, 0, excb, sentcb);
}

/**
 * Type-safe asynchronous callback wrapper class with cookie support used for calls to
 * IceProxy::squarepro::event::IEventService::begin_handle.
 * Create a wrapper instance by calling ::squarepro::event::newCallback_IEventService_handle.
 */
template<class T, typename CT>
class Callback_IEventService_handle : public Callback_IEventService_handle_Base, public ::IceInternal::OnewayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const CT&);

    Callback_IEventService_handle(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::OnewayCallback<T, CT>(obj, cb, excb, sentcb)
    {
    }
};

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T, typename CT> Callback_IEventService_handlePtr
newCallback_IEventService_handle(const IceUtil::Handle<T>& instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_IEventService_handle<T, CT>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T, typename CT> Callback_IEventService_handlePtr
newCallback_IEventService_handle(const IceUtil::Handle<T>& instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_IEventService_handle<T, CT>(instance, 0, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T, typename CT> Callback_IEventService_handlePtr
newCallback_IEventService_handle(T* instance, void (T::*cb)(const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_IEventService_handle<T, CT>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::event::IEventService::begin_handle.
 */
template<class T, typename CT> Callback_IEventService_handlePtr
newCallback_IEventService_handle(T* instance, void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_IEventService_handle<T, CT>(instance, 0, excb, sentcb);
}

}

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
