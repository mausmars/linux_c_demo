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

#include "common_gm.h"
#include <IceUtil/PushDisableWarnings.h>
#include <Ice/LocalException.h>
#include <Ice/ValueFactory.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/InputStream.h>
#include <Ice/OutputStream.h>
#include <IceUtil/PopDisableWarnings.h>

#if defined(_MSC_VER)
#   pragma warning(disable:4458) // declaration of ... hides class member
#elif defined(__clang__)
#   pragma clang diagnostic ignored "-Wshadow"
#elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wshadow"
#endif

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

namespace
{

const ::IceInternal::DefaultValueFactoryInit<::squarepro::gm::GmLuaPayloadRequest> iceC_squarepro_gm_GmLuaPayloadRequest_init("::squarepro::gm::GmLuaPayloadRequest");

const ::std::string iceC_squarepro_gm_IGmService_ids[2] =
{
    "::Ice::Object",
    "::squarepro::gm::IGmService"
};
const ::std::string iceC_squarepro_gm_IGmService_ops[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "luaEvaluate"
};
const ::std::string iceC_squarepro_gm_IGmService_luaEvaluate_name = "luaEvaluate";

}

bool
squarepro::gm::IGmService::ice_isA(::std::string s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_squarepro_gm_IGmService_ids, iceC_squarepro_gm_IGmService_ids + 2, s);
}

::std::vector<::std::string>
squarepro::gm::IGmService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector<::std::string>(&iceC_squarepro_gm_IGmService_ids[0], &iceC_squarepro_gm_IGmService_ids[2]);
}

::std::string
squarepro::gm::IGmService::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
squarepro::gm::IGmService::ice_staticId()
{
    static const ::std::string typeId = "::squarepro::gm::IGmService";
    return typeId;
}

/// \cond INTERNAL
bool
squarepro::gm::IGmService::_iceD_luaEvaluate(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::OperationMode::Normal, current.mode);
    auto istr = inS.startReadParams();
    ::std::shared_ptr<GmLuaPayloadRequest> iceP_request;
    istr->readAll(iceP_request);
    istr->readPendingValues();
    inS.endReadParams();
    auto inA = ::IceInternal::IncomingAsync::create(inS);
    auto responseCB = [inA](const ::std::string& ret)
    {
        auto ostr = inA->startWriteParams();
        ostr->writeAll(ret);
        inA->endWriteParams();
        inA->completed();
    };
    this->luaEvaluateAsync(::std::move(iceP_request), responseCB, inA->exception(), current);
    return false;
}
/// \endcond

/// \cond INTERNAL
bool
squarepro::gm::IGmService::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_squarepro_gm_IGmService_ops, iceC_squarepro_gm_IGmService_ops + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_squarepro_gm_IGmService_ops)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_luaEvaluate(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}
/// \endcond

squarepro::gm::GmLuaPayloadRequest::~GmLuaPayloadRequest()
{
}

const ::std::string&
squarepro::gm::GmLuaPayloadRequest::ice_staticId()
{
    static const ::std::string typeId = "::squarepro::gm::GmLuaPayloadRequest";
    return typeId;
}

/// \cond INTERNAL
void
squarepro::gm::IGmServicePrx::_iceI_luaEvaluate(const ::std::shared_ptr<::IceInternal::OutgoingAsyncT<::std::string>>& outAsync, const ::std::shared_ptr<GmLuaPayloadRequest>& iceP_request, const ::Ice::Context& context)
{
    _checkTwowayOnly(iceC_squarepro_gm_IGmService_luaEvaluate_name);
    outAsync->invoke(iceC_squarepro_gm_IGmService_luaEvaluate_name, ::Ice::OperationMode::Normal, ::Ice::FormatType::DefaultFormat, context,
        [&](::Ice::OutputStream* ostr)
        {
            ostr->writeAll(iceP_request);
            ostr->writePendingValues();
        },
        nullptr);
}
/// \endcond

/// \cond INTERNAL
::std::shared_ptr<::Ice::ObjectPrx>
squarepro::gm::IGmServicePrx::_newInstance() const
{
    return ::IceInternal::createProxy<IGmServicePrx>();
}
/// \endcond

const ::std::string&
squarepro::gm::IGmServicePrx::ice_staticId()
{
    return IGmService::ice_staticId();
}

#else // C++98 mapping

namespace
{

namespace
{

const ::std::string iceC_squarepro_gm_IGmService_luaEvaluate_name = "luaEvaluate";

}

}

squarepro::gm::AMD_IGmService_luaEvaluate::~AMD_IGmService_luaEvaluate()
{
}

/// \cond INTERNAL
IceAsync::squarepro::gm::AMD_IGmService_luaEvaluate::AMD_IGmService_luaEvaluate(::IceInternal::Incoming& in) :
    ::IceInternal::IncomingAsync(in)
{
}

void
IceAsync::squarepro::gm::AMD_IGmService_luaEvaluate::ice_response(const ::std::string& ret)
{
    ::Ice::OutputStream* ostr = startWriteParams();
    ostr->write(ret);
    endWriteParams();
    completed();
}
/// \endcond

/// \cond INTERNAL
::IceProxy::Ice::Object* ::IceProxy::squarepro::gm::upCast(GmLuaPayloadRequest* p) { return p; }

void
::IceProxy::squarepro::gm::_readProxy(::Ice::InputStream* istr, ::IceInternal::ProxyHandle< GmLuaPayloadRequest>& v)
{
    ::Ice::ObjectPrx proxy;
    istr->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new GmLuaPayloadRequest;
        v->_copyFrom(proxy);
    }
}
/// \endcond

/// \cond INTERNAL
::IceProxy::Ice::Object*
IceProxy::squarepro::gm::GmLuaPayloadRequest::_newInstance() const
{
    return new GmLuaPayloadRequest;
}
/// \endcond

const ::std::string&
IceProxy::squarepro::gm::GmLuaPayloadRequest::ice_staticId()
{
    return ::squarepro::gm::GmLuaPayloadRequest::ice_staticId();
}

/// \cond INTERNAL
::IceProxy::Ice::Object* ::IceProxy::squarepro::gm::upCast(IGmService* p) { return p; }

void
::IceProxy::squarepro::gm::_readProxy(::Ice::InputStream* istr, ::IceInternal::ProxyHandle< IGmService>& v)
{
    ::Ice::ObjectPrx proxy;
    istr->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new IGmService;
        v->_copyFrom(proxy);
    }
}
/// \endcond

::Ice::AsyncResultPtr
IceProxy::squarepro::gm::IGmService::_iceI_begin_luaEvaluate(const ::squarepro::gm::GmLuaPayloadRequestPtr& iceP_request, const ::Ice::Context& context, const ::IceInternal::CallbackBasePtr& del, const ::Ice::LocalObjectPtr& cookie, bool sync)
{
    _checkTwowayOnly(iceC_squarepro_gm_IGmService_luaEvaluate_name, sync);
    ::IceInternal::OutgoingAsyncPtr result = new ::IceInternal::CallbackOutgoing(this, iceC_squarepro_gm_IGmService_luaEvaluate_name, del, cookie, sync);
    try
    {
        result->prepare(iceC_squarepro_gm_IGmService_luaEvaluate_name, ::Ice::Normal, context);
        ::Ice::OutputStream* ostr = result->startWriteParams(::Ice::DefaultFormat);
        ostr->write(iceP_request);
        ostr->writePendingValues();
        result->endWriteParams();
        result->invoke(iceC_squarepro_gm_IGmService_luaEvaluate_name);
    }
    catch(const ::Ice::Exception& ex)
    {
        result->abort(ex);
    }
    return result;
}

::std::string
IceProxy::squarepro::gm::IGmService::end_luaEvaluate(const ::Ice::AsyncResultPtr& result)
{
    ::Ice::AsyncResult::_check(result, this, iceC_squarepro_gm_IGmService_luaEvaluate_name);
    ::std::string ret;
    if(!result->_waitForResponse())
    {
        try
        {
            result->_throwUserException();
        }
        catch(const ::Ice::UserException& ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, ex.ice_id());
        }
    }
    ::Ice::InputStream* istr = result->_startReadParams();
    istr->read(ret);
    result->_endReadParams();
    return ret;
}

/// \cond INTERNAL
::IceProxy::Ice::Object*
IceProxy::squarepro::gm::IGmService::_newInstance() const
{
    return new IGmService;
}
/// \endcond

const ::std::string&
IceProxy::squarepro::gm::IGmService::ice_staticId()
{
    return ::squarepro::gm::IGmService::ice_staticId();
}

squarepro::gm::GmLuaPayloadRequest::~GmLuaPayloadRequest()
{
}

/// \cond INTERNAL
::Ice::Object* squarepro::gm::upCast(GmLuaPayloadRequest* p) { return p; }

/// \endcond
::Ice::ObjectPtr
squarepro::gm::GmLuaPayloadRequest::ice_clone() const
{
    ::Ice::Object* p = new GmLuaPayloadRequest(*this);
    return p;
}

namespace
{
const ::std::string iceC_squarepro_gm_GmLuaPayloadRequest_ids[2] =
{
    "::Ice::Object",
    "::squarepro::gm::GmLuaPayloadRequest"
};

}

bool
squarepro::gm::GmLuaPayloadRequest::ice_isA(const ::std::string& s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_squarepro_gm_GmLuaPayloadRequest_ids, iceC_squarepro_gm_GmLuaPayloadRequest_ids + 2, s);
}

::std::vector< ::std::string>
squarepro::gm::GmLuaPayloadRequest::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&iceC_squarepro_gm_GmLuaPayloadRequest_ids[0], &iceC_squarepro_gm_GmLuaPayloadRequest_ids[2]);
}

const ::std::string&
squarepro::gm::GmLuaPayloadRequest::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
squarepro::gm::GmLuaPayloadRequest::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::squarepro::gm::GmLuaPayloadRequest";
    return typeId;
#else
    return iceC_squarepro_gm_GmLuaPayloadRequest_ids[1];
#endif
}

/// \cond STREAM
void
squarepro::gm::GmLuaPayloadRequest::_iceWriteImpl(::Ice::OutputStream* ostr) const
{
    ostr->startSlice(ice_staticId(), -1, true);
    ::Ice::StreamWriter< GmLuaPayloadRequest, ::Ice::OutputStream>::write(ostr, *this);
    ostr->endSlice();
}

void
squarepro::gm::GmLuaPayloadRequest::_iceReadImpl(::Ice::InputStream* istr)
{
    istr->startSlice();
    ::Ice::StreamReader< GmLuaPayloadRequest, ::Ice::InputStream>::read(istr, *this);
    istr->endSlice();
}
/// \endcond

namespace
{
const ::IceInternal::DefaultValueFactoryInit< ::squarepro::gm::GmLuaPayloadRequest> iceC_squarepro_gm_GmLuaPayloadRequest_init("::squarepro::gm::GmLuaPayloadRequest");
}

::Ice::ValueFactoryPtr
squarepro::gm::GmLuaPayloadRequest::ice_factory()
{
    return ::IceInternal::factoryTable->getValueFactory(::squarepro::gm::GmLuaPayloadRequest::ice_staticId());
}

/// \cond INTERNAL
void
squarepro::gm::_icePatchObjectPtr(GmLuaPayloadRequestPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = GmLuaPayloadRequestPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(GmLuaPayloadRequest::ice_staticId(), v);
    }
}
/// \endcond

squarepro::gm::IGmService::~IGmService()
{
}

/// \cond INTERNAL
::Ice::Object* squarepro::gm::upCast(IGmService* p) { return p; }

/// \endcond

namespace
{
const ::std::string iceC_squarepro_gm_IGmService_ids[2] =
{
    "::Ice::Object",
    "::squarepro::gm::IGmService"
};

}

bool
squarepro::gm::IGmService::ice_isA(const ::std::string& s, const ::Ice::Current&) const
{
    return ::std::binary_search(iceC_squarepro_gm_IGmService_ids, iceC_squarepro_gm_IGmService_ids + 2, s);
}

::std::vector< ::std::string>
squarepro::gm::IGmService::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&iceC_squarepro_gm_IGmService_ids[0], &iceC_squarepro_gm_IGmService_ids[2]);
}

const ::std::string&
squarepro::gm::IGmService::ice_id(const ::Ice::Current&) const
{
    return ice_staticId();
}

const ::std::string&
squarepro::gm::IGmService::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::squarepro::gm::IGmService";
    return typeId;
#else
    return iceC_squarepro_gm_IGmService_ids[1];
#endif
}

/// \cond INTERNAL
bool
squarepro::gm::IGmService::_iceD_luaEvaluate(::IceInternal::Incoming& inS, const ::Ice::Current& current)
{
    _iceCheckMode(::Ice::Normal, current.mode);
    ::Ice::InputStream* istr = inS.startReadParams();
    GmLuaPayloadRequestPtr iceP_request;
    istr->read(iceP_request);
    istr->readPendingValues();
    inS.endReadParams();
    this->luaEvaluate_async(new IceAsync::squarepro::gm::AMD_IGmService_luaEvaluate(inS), iceP_request, current);
    return false;
}
/// \endcond

namespace
{
const ::std::string iceC_squarepro_gm_IGmService_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "luaEvaluate"
};

}

/// \cond INTERNAL
bool
squarepro::gm::IGmService::_iceDispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair<const ::std::string*, const ::std::string*> r = ::std::equal_range(iceC_squarepro_gm_IGmService_all, iceC_squarepro_gm_IGmService_all + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - iceC_squarepro_gm_IGmService_all)
    {
        case 0:
        {
            return _iceD_ice_id(in, current);
        }
        case 1:
        {
            return _iceD_ice_ids(in, current);
        }
        case 2:
        {
            return _iceD_ice_isA(in, current);
        }
        case 3:
        {
            return _iceD_ice_ping(in, current);
        }
        case 4:
        {
            return _iceD_luaEvaluate(in, current);
        }
        default:
        {
            assert(false);
            throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
        }
    }
}
/// \endcond

/// \cond STREAM
void
squarepro::gm::IGmService::_iceWriteImpl(::Ice::OutputStream* ostr) const
{
    ostr->startSlice(ice_staticId(), -1, true);
    ::Ice::StreamWriter< IGmService, ::Ice::OutputStream>::write(ostr, *this);
    ostr->endSlice();
}

void
squarepro::gm::IGmService::_iceReadImpl(::Ice::InputStream* istr)
{
    istr->startSlice();
    ::Ice::StreamReader< IGmService, ::Ice::InputStream>::read(istr, *this);
    istr->endSlice();
}
/// \endcond

/// \cond INTERNAL
void
squarepro::gm::_icePatchObjectPtr(IGmServicePtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = IGmServicePtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(IGmService::ice_staticId(), v);
    }
}
/// \endcond

namespace Ice
{
}

#endif
