/**
 *     Copyright 2017-2019 Couchbase, Inc.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include "couchbase.h"

#define LOGARGS(lvl) LCB_LOG_##lvl, NULL, "pcbc/geo_polygon_search_query", __FILE__, __LINE__

zend_class_entry *pcbc_geo_polygon_search_query_ce;
zend_class_entry *pcbc_coordinate_ce;

PHP_METHOD(GeoPolygonSearchQuery, __construct)
{
    int rv;
    zval *coordinates = NULL;

    rv = zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "a", &coordinates);
    if (rv == FAILURE) {
        return;
    }
    zend_update_property(pcbc_geo_polygon_search_query_ce, getThis(), ZEND_STRL("coordinates"), coordinates TSRMLS_CC);
}

PHP_METHOD(GeoPolygonSearchQuery, field)
{
    zend_string *field = NULL;
    int rv;

    rv = zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "S", &field);
    if (rv == FAILURE) {
        RETURN_NULL();
    }

    zend_update_property_str(pcbc_geo_polygon_search_query_ce, getThis(), ZEND_STRL("field"), field TSRMLS_CC);

    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(GeoPolygonSearchQuery, boost)
{
    double boost = 0;
    int rv;

    rv = zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "d", &boost);
    if (rv == FAILURE) {
        RETURN_NULL();
    }

    zend_update_property_double(pcbc_geo_polygon_search_query_ce, getThis(), ZEND_STRL("boost"), boost TSRMLS_CC);

    RETURN_ZVAL(getThis(), 1, 0);
}

PHP_METHOD(GeoPolygonSearchQuery, jsonSerialize)
{
    int rv;

    rv = zend_parse_parameters_none();
    if (rv == FAILURE) {
        RETURN_NULL();
    }

    array_init(return_value);

    zval *prop, ret;

    prop = zend_read_property(pcbc_geo_polygon_search_query_ce, getThis(), ZEND_STRL("coordinates"), 0, &ret);
    add_assoc_zval(return_value, "polygon_points", prop);
    Z_TRY_ADDREF_P(prop);

    prop = zend_read_property(pcbc_geo_polygon_search_query_ce, getThis(), ZEND_STRL("field"), 0, &ret);
    if (Z_TYPE_P(prop) != IS_NULL) {
        add_assoc_zval(return_value, "field", prop);
        Z_TRY_ADDREF_P(prop);
    }

    prop = zend_read_property(pcbc_geo_polygon_search_query_ce, getThis(), ZEND_STRL("boost"), 0, &ret);
    if (Z_TYPE_P(prop) != IS_NULL) {
        add_assoc_zval(return_value, "boost", prop);
        Z_TRY_ADDREF_P(prop);
    }
}

ZEND_BEGIN_ARG_INFO_EX(ai_GeoPolygonSearchQuery_jsonSerialize, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_GeoPolygonSearchQuery_construct, 0, 0, 1)
ZEND_ARG_TYPE_INFO(0, coordinates, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ai_GeoPolygonSearchQuery_field, 0, 1, Couchbase\\GeoPolygonSearchQuery, 0)
ZEND_ARG_TYPE_INFO(0, field, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(ai_GeoPolygonSearchQuery_boost, 0, 1, Couchbase\\GeoPolygonSearchQuery, 0)
ZEND_ARG_TYPE_INFO(0, boost, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

// clang-format off
zend_function_entry geo_polygon_search_query_methods[] = {
    PHP_ME(GeoPolygonSearchQuery, __construct, ai_GeoPolygonSearchQuery_construct, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(GeoPolygonSearchQuery, jsonSerialize, ai_GeoPolygonSearchQuery_jsonSerialize, ZEND_ACC_PUBLIC)
    PHP_ME(GeoPolygonSearchQuery, boost, ai_GeoPolygonSearchQuery_boost, ZEND_ACC_PUBLIC)
    PHP_ME(GeoPolygonSearchQuery, field, ai_GeoPolygonSearchQuery_field, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
// clang-format on

PHP_METHOD(Coordinate, __construct)
{
    int rv;
    double longitude = 0;
    double latitude = 0;

    rv = zend_parse_parameters_throw(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &longitude, &latitude);
    if (rv == FAILURE) {
        return;
    }
    zend_update_property_double(pcbc_coordinate_ce, getThis(), ZEND_STRL("longitude"), longitude TSRMLS_CC);
    zend_update_property_double(pcbc_coordinate_ce, getThis(), ZEND_STRL("latitude"), latitude TSRMLS_CC);
}

PHP_METHOD(Coordinate, jsonSerialize)
{
    int rv;

    rv = zend_parse_parameters_none();
    if (rv == FAILURE) {
        RETURN_NULL();
    }

    array_init_size(return_value, 2);

    zval *prop, ret;

    prop = zend_read_property(pcbc_coordinate_ce, getThis(), ZEND_STRL("longitude"), 0, &ret);
    add_next_index_zval(return_value, prop);
    Z_TRY_ADDREF_P(prop);

    prop = zend_read_property(pcbc_coordinate_ce, getThis(), ZEND_STRL("latitude"), 0, &ret);
    add_next_index_zval(return_value, prop);
    Z_TRY_ADDREF_P(prop);
}

ZEND_BEGIN_ARG_INFO_EX(ai_Coordinate_construct, 0, 0, 2)
ZEND_ARG_TYPE_INFO(0, longitude, IS_DOUBLE, 0)
ZEND_ARG_TYPE_INFO(0, latitude, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(ai_Coordinate_jsonSerialize, 0, 0, 0)
ZEND_END_ARG_INFO()

// clang-format off
zend_function_entry coordinate_methods[] = {
    PHP_ME(Coordinate, __construct, ai_Coordinate_construct, ZEND_ACC_PUBLIC)
    PHP_ME(Coordinate, jsonSerialize, ai_Coordinate_jsonSerialize, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
// clang-format on

PHP_MINIT_FUNCTION(GeoPolygonSearchQuery)
{
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Couchbase", "GeoPolygonSearchQuery", geo_polygon_search_query_methods);
    pcbc_geo_polygon_search_query_ce = zend_register_internal_class(&ce TSRMLS_CC);

    zend_class_implements(pcbc_geo_polygon_search_query_ce TSRMLS_CC, 2, pcbc_json_serializable_ce,
                          pcbc_search_query_ce);

    zend_declare_property_null(pcbc_geo_polygon_search_query_ce, ZEND_STRL("boost"), ZEND_ACC_PRIVATE TSRMLS_CC);
    zend_declare_property_null(pcbc_geo_polygon_search_query_ce, ZEND_STRL("field"), ZEND_ACC_PRIVATE TSRMLS_CC);
    zend_declare_property_null(pcbc_geo_polygon_search_query_ce, ZEND_STRL("coordinates"), ZEND_ACC_PRIVATE TSRMLS_CC);

    INIT_NS_CLASS_ENTRY(ce, "Couchbase", "Coordinate", coordinate_methods);
    pcbc_coordinate_ce = zend_register_internal_class(&ce TSRMLS_CC);
    zend_class_implements(pcbc_coordinate_ce TSRMLS_CC, 1, pcbc_json_serializable_ce);
    zend_declare_property_null(pcbc_coordinate_ce, ZEND_STRL("longitude"), ZEND_ACC_PRIVATE TSRMLS_CC);
    zend_declare_property_null(pcbc_coordinate_ce, ZEND_STRL("latitude"), ZEND_ACC_PRIVATE TSRMLS_CC);
    return SUCCESS;
}
