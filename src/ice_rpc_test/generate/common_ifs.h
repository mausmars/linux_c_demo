//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
//
// Ice version 3.7.6
//
// <auto-generated>
//
// Generated from file `common_ifs.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __common_ifs_h__
#define __common_ifs_h__

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


namespace ifs
{

class HostInfo;
class ICommonService;
class ICommonServicePrx;

}

}

namespace squarepro
{

namespace ifs
{

class ICommonService : public virtual ::Ice::Object
{
public:

    using ProxyType = ICommonServicePrx;

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

    virtual void getServiceHostInfoAsync(::std::string serviceId, ::std::function<void(const ::std::shared_ptr<HostInfo>& returnValue)> response, ::std::function<void(::std::exception_ptr)> exception, const ::Ice::Current& current) = 0;
    /// \cond INTERNAL
    bool _iceD_getServiceHostInfo(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

    /// \cond INTERNAL
    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&) override;
    /// \endcond
};

}

}

namespace squarepro
{

namespace ifs
{

class HostInfo : public ::Ice::ValueHelper<HostInfo, ::Ice::Value>
{
public:

    virtual ~HostInfo();

    HostInfo() = default;

    HostInfo(const HostInfo&) = default;
    HostInfo(HostInfo&&) = default;
    HostInfo& operator=(const HostInfo&) = default;
    HostInfo& operator=(HostInfo&&) = default;

    /**
     * One-shot constructor to initialize all data members.
     */
    HostInfo(const ::std::string& host, int port) :
        host(host),
        port(port)
    {
    }

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const ::std::string&, const int&> ice_tuple() const
    {
        return std::tie(host, port);
    }

    /**
     * Obtains the Slice type ID of this value.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    ::std::string host;
    int port;
};

/// \cond INTERNAL
static HostInfo _iceS_HostInfo_init;
/// \endcond

}

}

namespace squarepro
{

namespace ifs
{

class ICommonServicePrx : public virtual ::Ice::Proxy<ICommonServicePrx, ::Ice::ObjectPrx>
{
public:

    ::std::shared_ptr<HostInfo> getServiceHostInfo(const ::std::string& serviceId, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _makePromiseOutgoing<::std::shared_ptr<::squarepro::ifs::HostInfo>>(true, this, &ICommonServicePrx::_iceI_getServiceHostInfo, serviceId, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto getServiceHostInfoAsync(const ::std::string& serviceId, const ::Ice::Context& context = ::Ice::noExplicitContext)
        -> decltype(::std::declval<P<::std::shared_ptr<::squarepro::ifs::HostInfo>>>().get_future())
    {
        return _makePromiseOutgoing<::std::shared_ptr<::squarepro::ifs::HostInfo>, P>(false, this, &ICommonServicePrx::_iceI_getServiceHostInfo, serviceId, context);
    }

    ::std::function<void()>
    getServiceHostInfoAsync(const ::std::string& serviceId,
                            ::std::function<void(::std::shared_ptr<::squarepro::ifs::HostInfo>)> response,
                            ::std::function<void(::std::exception_ptr)> ex = nullptr,
                            ::std::function<void(bool)> sent = nullptr,
                            const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<::std::shared_ptr<::squarepro::ifs::HostInfo>>(std::move(response), std::move(ex), std::move(sent), this, &squarepro::ifs::ICommonServicePrx::_iceI_getServiceHostInfo, serviceId, context);
    }

    /// \cond INTERNAL
    void _iceI_getServiceHostInfo(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::std::shared_ptr<::squarepro::ifs::HostInfo>>>&, const ::std::string&, const ::Ice::Context&);
    /// \endcond

    /**
     * Obtains the Slice type ID of this interface.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:

    /// \cond INTERNAL
    ICommonServicePrx() = default;
    friend ::std::shared_ptr<ICommonServicePrx> IceInternal::createProxy<ICommonServicePrx>();

    virtual ::std::shared_ptr<::Ice::ObjectPrx> _newInstance() const override;
    /// \endcond
};

}

}

/// \cond STREAM
namespace Ice
{

template<typename S>
struct StreamReader<::squarepro::ifs::HostInfo, S>
{
    static void read(S* istr, ::squarepro::ifs::HostInfo& v)
    {
        istr->readAll(v.host, v.port);
    }
};

}
/// \endcond

/// \cond INTERNAL
namespace squarepro
{

/// \cond INTERNAL
namespace ifs
{

using HostInfoPtr = ::std::shared_ptr<HostInfo>;

using ICommonServicePtr = ::std::shared_ptr<ICommonService>;
using ICommonServicePrxPtr = ::std::shared_ptr<ICommonServicePrx>;

}
/// \endcond

}
/// \endcond

#else // C++98 mapping

namespace IceProxy
{

namespace squarepro
{

namespace ifs
{

class HostInfo;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< HostInfo>&);
::IceProxy::Ice::Object* upCast(HostInfo*);
/// \endcond

class ICommonService;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< ICommonService>&);
::IceProxy::Ice::Object* upCast(ICommonService*);
/// \endcond

}

}

}

namespace squarepro
{

namespace ifs
{

class HostInfo;
/// \cond INTERNAL
::Ice::Object* upCast(HostInfo*);
/// \endcond
typedef ::IceInternal::Handle< HostInfo> HostInfoPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::squarepro::ifs::HostInfo> HostInfoPrx;
typedef HostInfoPrx HostInfoPrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(HostInfoPtr&, const ::Ice::ObjectPtr&);
/// \endcond

class ICommonService;
/// \cond INTERNAL
::Ice::Object* upCast(ICommonService*);
/// \endcond
typedef ::IceInternal::Handle< ICommonService> ICommonServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::squarepro::ifs::ICommonService> ICommonServicePrx;
typedef ICommonServicePrx ICommonServicePrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(ICommonServicePtr&, const ::Ice::ObjectPtr&);
/// \endcond

}

}

namespace squarepro
{

namespace ifs
{

/**
 * AMD callback class for squarepro::ifs::ICommonService::getServiceHostInfo_async.
 * Call the ice_response method for a successful completion, or the ice_exception
 * method in the case of an error.
 */
class AMD_ICommonService_getServiceHostInfo : public virtual ::Ice::AMDCallback
{
public:

    virtual ~AMD_ICommonService_getServiceHostInfo();

    /**
     * Call ice_response for a successful completion.
     */
    virtual void ice_response(const HostInfoPtr& result) = 0;
};

typedef ::IceUtil::Handle< ::squarepro::ifs::AMD_ICommonService_getServiceHostInfo> AMD_ICommonService_getServiceHostInfoPtr;

}

}

/// \cond INTERNAL
namespace IceAsync
{

namespace squarepro
{

namespace ifs
{

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#   pragma warning(push)
#   pragma warning(disable:4239)
#endif

class AMD_ICommonService_getServiceHostInfo : public ::squarepro::ifs::AMD_ICommonService_getServiceHostInfo, public ::IceInternal::IncomingAsync
{
public:

    AMD_ICommonService_getServiceHostInfo(::IceInternal::Incoming&);

    virtual void ice_response(const ::squarepro::ifs::HostInfoPtr&);
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

namespace ifs
{

/**
 * Base class for asynchronous callback wrapper classes used for calls to
 * IceProxy::squarepro::ifs::ICommonService::begin_getServiceHostInfo.
 * Create a wrapper instance by calling ::squarepro::ifs::newCallback_ICommonService_getServiceHostInfo.
 */
class Callback_ICommonService_getServiceHostInfo_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_ICommonService_getServiceHostInfo_Base> Callback_ICommonService_getServiceHostInfoPtr;

}

}

namespace IceProxy
{

namespace squarepro
{

namespace ifs
{

class HostInfo : public virtual ::Ice::Proxy<HostInfo, ::IceProxy::Ice::Object>
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

class ICommonService : public virtual ::Ice::Proxy<ICommonService, ::IceProxy::Ice::Object>
{
public:

    ::squarepro::ifs::HostInfoPtr getServiceHostInfo(const ::std::string& serviceId, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return end_getServiceHostInfo(_iceI_begin_getServiceHostInfo(serviceId, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_getServiceHostInfo(const ::std::string& serviceId, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_getServiceHostInfo(serviceId, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_getServiceHostInfo(const ::std::string& serviceId, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getServiceHostInfo(serviceId, ::Ice::noExplicitContext, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_getServiceHostInfo(const ::std::string& serviceId, const ::Ice::Context& context, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getServiceHostInfo(serviceId, context, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_getServiceHostInfo(const ::std::string& serviceId, const ::squarepro::ifs::Callback_ICommonService_getServiceHostInfoPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getServiceHostInfo(serviceId, ::Ice::noExplicitContext, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_getServiceHostInfo(const ::std::string& serviceId, const ::Ice::Context& context, const ::squarepro::ifs::Callback_ICommonService_getServiceHostInfoPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_getServiceHostInfo(serviceId, context, cb, cookie);
    }

    ::squarepro::ifs::HostInfoPtr end_getServiceHostInfo(const ::Ice::AsyncResultPtr& result);

private:

    ::Ice::AsyncResultPtr _iceI_begin_getServiceHostInfo(const ::std::string&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

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

namespace ifs
{

class HostInfo : public virtual ::Ice::Object
{
public:

    typedef HostInfoPrx ProxyType;
    typedef HostInfoPtr PointerType;

    virtual ~HostInfo();

    HostInfo()
    {
    }

    /**
     * One-shot constructor to initialize all data members.
     */
    HostInfo(const ::std::string& host, ::Ice::Int port) :
        host(host),
        port(port)
    {
    }

#ifdef ICE_CPP11_COMPILER
    HostInfo(const HostInfo&) = default;
    HostInfo& operator=(const HostInfo&) = default;
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

public:

    ::std::string host;
    ::Ice::Int port;
};
/// \cond INTERNAL
static ::Ice::ValueFactoryPtr _iceS_HostInfo_init = ::squarepro::ifs::HostInfo::ice_factory();
/// \endcond

/// \cond INTERNAL
inline bool operator==(const HostInfo& lhs, const HostInfo& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const HostInfo& lhs, const HostInfo& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

class ICommonService : public virtual ::Ice::Object
{
public:

    typedef ICommonServicePrx ProxyType;
    typedef ICommonServicePtr PointerType;

    virtual ~ICommonService();

#ifdef ICE_CPP11_COMPILER
    ICommonService() = default;
    ICommonService(const ICommonService&) = default;
    ICommonService& operator=(const ICommonService&) = default;
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

    virtual void getServiceHostInfo_async(const ::squarepro::ifs::AMD_ICommonService_getServiceHostInfoPtr& cb, const ::std::string& serviceId, const ::Ice::Current& current = ::Ice::emptyCurrent) = 0;
    /// \cond INTERNAL
    bool _iceD_getServiceHostInfo(::IceInternal::Incoming&, const ::Ice::Current&);
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
inline bool operator==(const ICommonService& lhs, const ICommonService& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const ICommonService& lhs, const ICommonService& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

}

}

/// \cond STREAM
namespace Ice
{

template<typename S>
struct StreamWriter< ::squarepro::ifs::HostInfo, S>
{
    static void write(S* ostr, const ::squarepro::ifs::HostInfo& v)
    {
        ostr->write(v.host);
        ostr->write(v.port);
    }
};

template<typename S>
struct StreamReader< ::squarepro::ifs::HostInfo, S>
{
    static void read(S* istr, ::squarepro::ifs::HostInfo& v)
    {
        istr->read(v.host);
        istr->read(v.port);
    }
};

}
/// \endcond

namespace squarepro
{

namespace ifs
{

/**
 * Type-safe asynchronous callback wrapper class used for calls to
 * IceProxy::squarepro::ifs::ICommonService::begin_getServiceHostInfo.
 * Create a wrapper instance by calling ::squarepro::ifs::newCallback_ICommonService_getServiceHostInfo.
 */
template<class T>
class CallbackNC_ICommonService_getServiceHostInfo : public Callback_ICommonService_getServiceHostInfo_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const HostInfoPtr&);

    CallbackNC_ICommonService_getServiceHostInfo(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    /// \cond INTERNAL
    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ICommonServicePrx proxy = ICommonServicePrx::uncheckedCast(result->getProxy());
        HostInfoPtr ret;
        try
        {
            ret = proxy->end_getServiceHostInfo(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::CallbackNC<T>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::CallbackNC<T>::_callback.get()->*_response)(ret);
        }
    }
    /// \endcond

private:

    Response _response;
};

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::ifs::ICommonService::begin_getServiceHostInfo.
 */
template<class T> Callback_ICommonService_getServiceHostInfoPtr
newCallback_ICommonService_getServiceHostInfo(const IceUtil::Handle<T>& instance, void (T::*cb)(const HostInfoPtr&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_ICommonService_getServiceHostInfo<T>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::ifs::ICommonService::begin_getServiceHostInfo.
 */
template<class T> Callback_ICommonService_getServiceHostInfoPtr
newCallback_ICommonService_getServiceHostInfo(T* instance, void (T::*cb)(const HostInfoPtr&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_ICommonService_getServiceHostInfo<T>(instance, cb, excb, sentcb);
}

/**
 * Type-safe asynchronous callback wrapper class with cookie support used for calls to
 * IceProxy::squarepro::ifs::ICommonService::begin_getServiceHostInfo.
 * Create a wrapper instance by calling ::squarepro::ifs::newCallback_ICommonService_getServiceHostInfo.
 */
template<class T, typename CT>
class Callback_ICommonService_getServiceHostInfo : public Callback_ICommonService_getServiceHostInfo_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const HostInfoPtr&, const CT&);

    Callback_ICommonService_getServiceHostInfo(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    /// \cond INTERNAL
    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        ICommonServicePrx proxy = ICommonServicePrx::uncheckedCast(result->getProxy());
        HostInfoPtr ret;
        try
        {
            ret = proxy->end_getServiceHostInfo(result);
        }
        catch(const ::Ice::Exception& ex)
        {
            ::IceInternal::Callback<T, CT>::exception(result, ex);
            return;
        }
        if(_response)
        {
            (::IceInternal::Callback<T, CT>::_callback.get()->*_response)(ret, CT::dynamicCast(result->getCookie()));
        }
    }
    /// \endcond

private:

    Response _response;
};

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::ifs::ICommonService::begin_getServiceHostInfo.
 */
template<class T, typename CT> Callback_ICommonService_getServiceHostInfoPtr
newCallback_ICommonService_getServiceHostInfo(const IceUtil::Handle<T>& instance, void (T::*cb)(const HostInfoPtr&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_ICommonService_getServiceHostInfo<T, CT>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::ifs::ICommonService::begin_getServiceHostInfo.
 */
template<class T, typename CT> Callback_ICommonService_getServiceHostInfoPtr
newCallback_ICommonService_getServiceHostInfo(T* instance, void (T::*cb)(const HostInfoPtr&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_ICommonService_getServiceHostInfo<T, CT>(instance, cb, excb, sentcb);
}

}

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
