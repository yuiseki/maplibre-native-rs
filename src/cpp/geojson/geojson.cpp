#include "geojson.h"

// The precompiled maplibre-native amalgam is produced with
// `armerge --keep-symbols 'mbgl.*'`, which localizes every non-mbgl symbol,
// including mapbox::geojson::parse/stringify. Compile the geojson-cpp
// implementation here (header form) so this single bridge translation unit
// provides those definitions for the whole bridge.
#include <mapbox/geojson_impl.hpp>
#include <mapbox/geojson_value_impl.hpp>

#include <string>
#include <utility>

namespace mln::bridge::geojson {

GeoJson::GeoJson(mapbox::geojson::geojson value) : value_(std::move(value)) {}

const mapbox::geojson::geojson& GeoJson::get() const {
    return value_;
}

std::unique_ptr<GeoJson> parse(rust::Str json) {
    return std::make_unique<GeoJson>(mapbox::geojson::parse(std::string(json)));
}

std::unique_ptr<GeoJson> clone(const GeoJson& geojson) {
    return std::make_unique<GeoJson>(geojson.get());
}

rust::String stringify(const GeoJson& geojson) {
    return mapbox::geojson::stringify(geojson.get());
}

} // namespace mln::bridge::geojson
