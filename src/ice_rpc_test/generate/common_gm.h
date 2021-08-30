//
// Copyright (c) ZeroC, Inc. All rights reserved.
//
//
// Ice version 3.7.6
//
// <auto-generated>
//
// Generated from file `common_gm.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __common_gm_h__
#define __common_gm_h__

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
#include "common_basetype.h"
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


namespace gm
{

class GmLuaPayloadRequest;
class IGmService;
class IGmServicePrx;

}

}

namespace squarepro
{

namespace gm
{

class IGmService : public virtual ::Ice::Object
{
public:

    using ProxyType = IGmServicePrx;

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

    virtual void luaEvaluateAsync(::std::shared_ptr<GmLuaPayloadRequest> request, ::std::function<void(const ::std::string& returnValue)> response, ::std::function<void(::std::exception_ptr)> exception, const ::Ice::Current& current) = 0;
    /// \cond INTERNAL
    bool _iceD_luaEvaluate(::IceInternal::Incoming&, const ::Ice::Current&);
    /// \endcond

    /// \cond INTERNAL
    virtual bool _iceDispatch(::IceInternal::Incoming&, const ::Ice::Current&) override;
    /// \endcond
};

}

}

namespace squarepro
{

namespace gm
{

class GmLuaPayloadRequest : public ::Ice::ValueHelper<GmLuaPayloadRequest, ::Ice::Value>
{
public:

    virtual ~GmLuaPayloadRequest();

    GmLuaPayloadRequest() = default;

    GmLuaPayloadRequest(const GmLuaPayloadRequest&) = default;
    GmLuaPayloadRequest(GmLuaPayloadRequest&&) = default;
    GmLuaPayloadRequest& operator=(const GmLuaPayloadRequest&) = default;
    GmLuaPayloadRequest& operator=(GmLuaPayloadRequest&&) = default;

    /**
     * One-shot constructor to initialize all data members.
     */
    GmLuaPayloadRequest(const ::std::string& luaPayload, const ::std::string& scriptType) :
        luaPayload(luaPayload),
        scriptType(scriptType)
    {
    }

    /**
     * Obtains a tuple containing all of the value's data members.
     * @return The data members in a tuple.
     */
    std::tuple<const ::std::string&, const ::std::string&> ice_tuple() const
    {
        return std::tie(luaPayload, scriptType);
    }

    /**
     * Obtains the Slice type ID of this value.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

    ::std::string luaPayload;
    ::std::string scriptType;
};

/// \cond INTERNAL
static GmLuaPayloadRequest _iceS_GmLuaPayloadRequest_init;
/// \endcond

}

}

namespace squarepro
{

namespace gm
{

class IGmServicePrx : public virtual ::Ice::Proxy<IGmServicePrx, ::Ice::ObjectPrx>
{
public:

    ::std::string luaEvaluate(const ::std::shared_ptr<GmLuaPayloadRequest>& request, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _makePromiseOutgoing<::std::string>(true, this, &IGmServicePrx::_iceI_luaEvaluate, request, context).get();
    }

    template<template<typename> class P = ::std::promise>
    auto luaEvaluateAsync(const ::std::shared_ptr<GmLuaPayloadRequest>& request, const ::Ice::Context& context = ::Ice::noExplicitContext)
        -> decltype(::std::declval<P<::std::string>>().get_future())
    {
        return _makePromiseOutgoing<::std::string, P>(false, this, &IGmServicePrx::_iceI_luaEvaluate, request, context);
    }

    ::std::function<void()>
    luaEvaluateAsync(const ::std::shared_ptr<GmLuaPayloadRequest>& request,
                     ::std::function<void(::std::string)> response,
                     ::std::function<void(::std::exception_ptr)> ex = nullptr,
                     ::std::function<void(bool)> sent = nullptr,
                     const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _makeLamdaOutgoing<::std::string>(std::move(response), std::move(ex), std::move(sent), this, &squarepro::gm::IGmServicePrx::_iceI_luaEvaluate, request, context);
    }

    /// \cond INTERNAL
    void _iceI_luaEvaluate(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::std::string>>&, const ::std::shared_ptr<GmLuaPayloadRequest>&, const ::Ice::Context&);
    /// \endcond

    /**
     * Obtains the Slice type ID of this interface.
     * @return The fully-scoped type ID.
     */
    static const ::std::string& ice_staticId();

protected:

    /// \cond INTERNAL
    IGmServicePrx() = default;
    friend ::std::shared_ptr<IGmServicePrx> IceInternal::createProxy<IGmServicePrx>();

    virtual ::std::shared_ptr<::Ice::ObjectPrx> _newInstance() const override;
    /// \endcond
};

}

}

/// \cond STREAM
namespace Ice
{

template<typename S>
struct StreamReader<::squarepro::gm::GmLuaPayloadRequest, S>
{
    static void read(S* istr, ::squarepro::gm::GmLuaPayloadRequest& v)
    {
        istr->readAll(v.luaPayload, v.scriptType);
    }
};

}
/// \endcond

/// \cond INTERNAL
namespace squarepro
{

/// \cond INTERNAL
namespace gm
{

using GmLuaPayloadRequestPtr = ::std::shared_ptr<GmLuaPayloadRequest>;

using IGmServicePtr = ::std::shared_ptr<IGmService>;
using IGmServicePrxPtr = ::std::shared_ptr<IGmServicePrx>;

}
/// \endcond

}
/// \endcond

#else // C++98 mapping

namespace IceProxy
{

namespace squarepro
{

namespace gm
{

class GmLuaPayloadRequest;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< GmLuaPayloadRequest>&);
::IceProxy::Ice::Object* upCast(GmLuaPayloadRequest*);
/// \endcond

class IGmService;
/// \cond INTERNAL
void _readProxy(::Ice::InputStream*, ::IceInternal::ProxyHandle< IGmService>&);
::IceProxy::Ice::Object* upCast(IGmService*);
/// \endcond

}

}

}

namespace squarepro
{

namespace gm
{

class GmLuaPayloadRequest;
/// \cond INTERNAL
::Ice::Object* upCast(GmLuaPayloadRequest*);
/// \endcond
typedef ::IceInternal::Handle< GmLuaPayloadRequest> GmLuaPayloadRequestPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::squarepro::gm::GmLuaPayloadRequest> GmLuaPayloadRequestPrx;
typedef GmLuaPayloadRequestPrx GmLuaPayloadRequestPrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(GmLuaPayloadRequestPtr&, const ::Ice::ObjectPtr&);
/// \endcond

class IGmService;
/// \cond INTERNAL
::Ice::Object* upCast(IGmService*);
/// \endcond
typedef ::IceInternal::Handle< IGmService> IGmServicePtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::squarepro::gm::IGmService> IGmServicePrx;
typedef IGmServicePrx IGmServicePrxPtr;
/// \cond INTERNAL
void _icePatchObjectPtr(IGmServicePtr&, const ::Ice::ObjectPtr&);
/// \endcond

}

}

namespace squarepro
{

namespace gm
{

/**
 * AMD callback class for squarepro::gm::IGmService::luaEvaluate_async.
 * Call the ice_response method for a successful completion, or the ice_exception
 * method in the case of an error.
 */
class AMD_IGmService_luaEvaluate : public virtual ::Ice::AMDCallback
{
public:

    virtual ~AMD_IGmService_luaEvaluate();

    /**
     * Call ice_response for a successful completion.
     */
    virtual void ice_response(const ::std::string& result) = 0;
};

typedef ::IceUtil::Handle< ::squarepro::gm::AMD_IGmService_luaEvaluate> AMD_IGmService_luaEvaluatePtr;

}

}

/// \cond INTERNAL
namespace IceAsync
{

namespace squarepro
{

namespace gm
{

#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#   pragma warning(push)
#   pragma warning(disable:4239)
#endif

class AMD_IGmService_luaEvaluate : public ::squarepro::gm::AMD_IGmService_luaEvaluate, public ::IceInternal::IncomingAsync
{
public:

    AMD_IGmService_luaEvaluate(::IceInternal::Incoming&);

    virtual void ice_response(const ::std::string&);
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

namespace gm
{

/**
 * Base class for asynchronous callback wrapper classes used for calls to
 * IceProxy::squarepro::gm::IGmService::begin_luaEvaluate.
 * Create a wrapper instance by calling ::squarepro::gm::newCallback_IGmService_luaEvaluate.
 */
class Callback_IGmService_luaEvaluate_Base : public virtual ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_IGmService_luaEvaluate_Base> Callback_IGmService_luaEvaluatePtr;

}

}

namespace IceProxy
{

namespace squarepro
{

namespace gm
{

class GmLuaPayloadRequest : public virtual ::Ice::Proxy<GmLuaPayloadRequest, ::IceProxy::Ice::Object>
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

class IGmService : public virtual ::Ice::Proxy<IGmService, ::IceProxy::Ice::Object>
{
public:

    ::std::string luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr& request, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return end_luaEvaluate(_iceI_begin_luaEvaluate(request, context, ::IceInternal::dummyCallback, 0, true));
    }

    ::Ice::AsyncResultPtr begin_luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr& request, const ::Ice::Context& context = ::Ice::noExplicitContext)
    {
        return _iceI_begin_luaEvaluate(request, context, ::IceInternal::dummyCallback, 0);
    }

    ::Ice::AsyncResultPtr begin_luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr& request, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_luaEvaluate(request, ::Ice::noExplicitContext, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr& request, const ::Ice::Context& context, const ::Ice::CallbackPtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_luaEvaluate(request, context, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr& request, const ::squarepro::gm::Callback_IGmService_luaEvaluatePtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_luaEvaluate(request, ::Ice::noExplicitContext, cb, cookie);
    }

    ::Ice::AsyncResultPtr begin_luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr& request, const ::Ice::Context& context, const ::squarepro::gm::Callback_IGmService_luaEvaluatePtr& cb, const ::Ice::LocalObjectPtr& cookie = 0)
    {
        return _iceI_begin_luaEvaluate(request, context, cb, cookie);
    }

    ::std::string end_luaEvaluate(const ::Ice::AsyncResultPtr& result);

private:

    ::Ice::AsyncResultPtr _iceI_begin_luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr&, const ::Ice::Context&, const ::IceInternal::CallbackBasePtr&, const ::Ice::LocalObjectPtr& cookie = 0, bool sync = false);

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

namespace gm
{

class GmLuaPayloadRequest : public virtual ::Ice::Object
{
public:

    typedef GmLuaPayloadRequestPrx ProxyType;
    typedef GmLuaPayloadRequestPtr PointerType;

    virtual ~GmLuaPayloadRequest();

    GmLuaPayloadRequest()
    {
    }

    /**
     * One-shot constructor to initialize all data members.
     */
    GmLuaPayloadRequest(const ::std::string& luaPayload, const ::std::string& scriptType) :
        luaPayload(luaPayload),
        scriptType(scriptType)
    {
    }

#ifdef ICE_CPP11_COMPILER
    GmLuaPayloadRequest(const GmLuaPayloadRequest&) = default;
    GmLuaPayloadRequest& operator=(const GmLuaPayloadRequest&) = default;
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

    ::std::string luaPayload;
    ::std::string scriptType;
};
/// \cond INTERNAL
static ::Ice::ValueFactoryPtr _iceS_GmLuaPayloadRequest_init = ::squarepro::gm::GmLuaPayloadRequest::ice_factory();
/// \endcond

/// \cond INTERNAL
inline bool operator==(const GmLuaPayloadRequest& lhs, const GmLuaPayloadRequest& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const GmLuaPayloadRequest& lhs, const GmLuaPayloadRequest& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) < static_cast<const ::Ice::Object&>(rhs);
}
/// \endcond

class IGmService : public virtual ::Ice::Object
{
public:

    typedef IGmServicePrx ProxyType;
    typedef IGmServicePtr PointerType;

    virtual ~IGmService();

#ifdef ICE_CPP11_COMPILER
    IGmService() = default;
    IGmService(const IGmService&) = default;
    IGmService& operator=(const IGmService&) = default;
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

    virtual void luaEvaluate_async(const ::squarepro::gm::AMD_IGmService_luaEvaluatePtr& cb, const GmLuaPayloadRequestPtr& request, const ::Ice::Current& current = ::Ice::emptyCurrent) = 0;
    /// \cond INTERNAL
    bool _iceD_luaEvaluate(::IceInternal::Incoming&, const ::Ice::Current&);
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
inline bool operator==(const IGmService& lhs, const IGmService& rhs)
{
    return static_cast<const ::Ice::Object&>(lhs) == static_cast<const ::Ice::Object&>(rhs);
}

inline bool operator<(const IGmService& lhs, const IGmService& rhs)
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
struct StreamWriter< ::squarepro::gm::GmLuaPayloadRequest, S>
{
    static void write(S* ostr, const ::squarepro::gm::GmLuaPayloadRequest& v)
    {
        ostr->write(v.luaPayload);
        ostr->write(v.scriptType);
    }
};

template<typename S>
struct StreamReader< ::squarepro::gm::GmLuaPayloadRequest, S>
{
    static void read(S* istr, ::squarepro::gm::GmLuaPayloadRequest& v)
    {
        istr->read(v.luaPayload);
        istr->read(v.scriptType);
    }
};

}
/// \endcond

namespace squarepro
{

namespace gm
{

/**
 * Type-safe asynchronous callback wrapper class used for calls to
 * IceProxy::squarepro::gm::IGmService::begin_luaEvaluate.
 * Create a wrapper instance by calling ::squarepro::gm::newCallback_IGmService_luaEvaluate.
 */
template<class T>
class CallbackNC_IGmService_luaEvaluate : public Callback_IGmService_luaEvaluate_Base, public ::IceInternal::TwowayCallbackNC<T>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception&);
    typedef void (T::*Sent)(bool);
    typedef void (T::*Response)(const ::std::string&);

    CallbackNC_IGmService_luaEvaluate(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallbackNC<T>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    /// \cond INTERNAL
    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        IGmServicePrx proxy = IGmServicePrx::uncheckedCast(result->getProxy());
        ::std::string ret;
        try
        {
            ret = proxy->end_luaEvaluate(result);
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
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::gm::IGmService::begin_luaEvaluate.
 */
template<class T> Callback_IGmService_luaEvaluatePtr
newCallback_IGmService_luaEvaluate(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::std::string&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_IGmService_luaEvaluate<T>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::gm::IGmService::begin_luaEvaluate.
 */
template<class T> Callback_IGmService_luaEvaluatePtr
newCallback_IGmService_luaEvaluate(T* instance, void (T::*cb)(const ::std::string&), void (T::*excb)(const ::Ice::Exception&), void (T::*sentcb)(bool) = 0)
{
    return new CallbackNC_IGmService_luaEvaluate<T>(instance, cb, excb, sentcb);
}

/**
 * Type-safe asynchronous callback wrapper class with cookie support used for calls to
 * IceProxy::squarepro::gm::IGmService::begin_luaEvaluate.
 * Create a wrapper instance by calling ::squarepro::gm::newCallback_IGmService_luaEvaluate.
 */
template<class T, typename CT>
class Callback_IGmService_luaEvaluate : public Callback_IGmService_luaEvaluate_Base, public ::IceInternal::TwowayCallback<T, CT>
{
public:

    typedef IceUtil::Handle<T> TPtr;

    typedef void (T::*Exception)(const ::Ice::Exception& , const CT&);
    typedef void (T::*Sent)(bool , const CT&);
    typedef void (T::*Response)(const ::std::string&, const CT&);

    Callback_IGmService_luaEvaluate(const TPtr& obj, Response cb, Exception excb, Sent sentcb)
        : ::IceInternal::TwowayCallback<T, CT>(obj, cb != 0, excb, sentcb), _response(cb)
    {
    }

    /// \cond INTERNAL
    virtual void completed(const ::Ice::AsyncResultPtr& result) const
    {
        IGmServicePrx proxy = IGmServicePrx::uncheckedCast(result->getProxy());
        ::std::string ret;
        try
        {
            ret = proxy->end_luaEvaluate(result);
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
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::gm::IGmService::begin_luaEvaluate.
 */
template<class T, typename CT> Callback_IGmService_luaEvaluatePtr
newCallback_IGmService_luaEvaluate(const IceUtil::Handle<T>& instance, void (T::*cb)(const ::std::string&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_IGmService_luaEvaluate<T, CT>(instance, cb, excb, sentcb);
}

/**
 * Creates a callback wrapper instance that delegates to your object.
 * Use this overload when your callback methods receive a cookie value.
 * @param instance The callback object.
 * @param cb The success method of the callback object.
 * @param excb The exception method of the callback object.
 * @param sentcb The sent method of the callback object.
 * @return An object that can be passed to an asynchronous invocation of IceProxy::squarepro::gm::IGmService::begin_luaEvaluate.
 */
template<class T, typename CT> Callback_IGmService_luaEvaluatePtr
newCallback_IGmService_luaEvaluate(T* instance, void (T::*cb)(const ::std::string&, const CT&), void (T::*excb)(const ::Ice::Exception&, const CT&), void (T::*sentcb)(bool, const CT&) = 0)
{
    return new Callback_IGmService_luaEvaluate<T, CT>(instance, cb, excb, sentcb);
}

}

}

#endif

#include <IceUtil/PopDisableWarnings.h>
#endif
