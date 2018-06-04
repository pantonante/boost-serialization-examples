// #define TEXT_ARCHIVE

#ifdef TEXT_ARCHIVE

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using Serializer = boost::archive::text_oarchive;
using Deserializer = boost::archive::text_iarchive;

#else

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

using Serializer = boost::archive::xml_oarchive;
using Deserializer = boost::archive::xml_iarchive;

#endif

// It is important to place the BOOST_CLASS_EXPORT in the same source module that includes any of
// the archive class headers.
#include "class_export.h"