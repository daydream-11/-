#ifndef __HTTP_RESPONSE__
#define __HTTP_RESPONSE__

#include "HttpRequest.h"

class CHttpResponse
{
public:
	CHttpResponse(CHttpRequest* request)
    {
        _pHttpRequest = request;
        _succeed = false;
        _responseData.clear();
        _errorBuffer.clear();
    }

    virtual ~CHttpResponse()
    {
       
    }

    inline CHttpRequest* getHttpRequest()
    {
        return _pHttpRequest;
    }

    inline bool isSucceed()
    {
        return _succeed;
    };
    
    inline std::vector<char>* getResponseData()
    {
        return &_responseData;
    }

    inline int getResponseCode()
    {
        return _responseCode;
    }

    /** Get the rror buffer which will tell you more about the reason why http request failed
     */
    inline const char* getErrorBuffer()
    {
        return _errorBuffer.c_str();
    }
    
    // setters, will be called by CCHttpClient
    // users should avoid invoking these methods
    
    
    /** Set if the http request is returned successfully,
     Althrough users can judge if (http code == 200), we want a easier way
     This setter is mainly used in CCHttpClient, users mustn't set it directly
     */
    inline void setSucceed(bool value)
    {
        _succeed = value;
    };
    
    
    /** Set the http response raw buffer, is used by CCHttpClient      
     */
    inline void setResponseData(std::vector<char>* data)
    {
        _responseData = *data;
    }
    
    
    /** Set the http response errorCode
     */
    inline void setResponseCode(int value)
    {
        _responseCode = value;
    }
    
    
    /** Set the error buffer which will tell you more the reason why http request failed
     */
    inline void setErrorBuffer(const char* value)
    {
        _errorBuffer.clear();
        _errorBuffer.assign(value);
    };
    
protected:
    bool initWithRequest(CHttpRequest* request);
    
    // properties
    CHttpRequest*        _pHttpRequest;  /// the corresponding HttpRequest pointer who leads to this response 
    bool                _succeed;       /// to indecate if the http reqeust is successful simply
    std::vector<char>   _responseData;  /// the returned raw data. You can also dump it as a string
    int                 _responseCode;    /// the status code returned from libcurl, e.g. 200, 404
    std::string         _errorBuffer;   /// if _responseCode != 200, please read _errorBuffer to find the reason 
    
};

#endif //__HTTP_RESPONSE_H__
