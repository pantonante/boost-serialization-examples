#include <boost/serialization/export.hpp>

/**
 * @brief In this file you have to export every derived class that you plan to serialize.
 *
 */

#include "pentagon.h"
#include "triangle.h"

BOOST_CLASS_EXPORT(Triangle);
BOOST_CLASS_EXPORT(Pentagon);
