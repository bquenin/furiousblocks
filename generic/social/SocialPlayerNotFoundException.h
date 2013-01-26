//
// Created by bquenin on 1/26/13.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __SocialPlayerNotFoundException_H_
#define __SocialPlayerNotFoundException_H_

#if !defined(SOCIAL_API)
  #if defined (__GNUC__) && (__GNUC__ >= 4)
    #define SOCIAL_API __attribute__ ((visibility ("default")))
  #else
		#define SOCIAL_API
	#endif
#endif

#include "Poco/JSON/JSON.h"
#include "Poco/Exception.h"

POCO_DECLARE_EXCEPTION(SOCIAL_API, SocialPlayerNotFoundException, Poco::Exception)


#endif //__SocialPlayerNotFoundException_H_
