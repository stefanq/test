// -*- c++ -*-
#pragma once
#include <map>
#include <string>
#include <vector>

enum class Intent {
	None,
	/* Basic Intents. */
	Fact, Weather, City, PlaceToVisit, GasStation, Hotel, Food, Emergency,
	/* Second Order  Intents. */
	WeatherInCity, HotelInCity, PlaceToVisitInCity, FactAboutCity
};

std::string intentToString( const Intent& );
std::string formatIntent( const Intent& );

/**
 * A class for very basic natural language processing. The API of this class
 * is one methods guessIntent() for guessing the intent of a natural language
 * query string by applying a simple heuristic based on the occurrence of
 * associated hotwords for each known intent or alternatively combining two
 * intents to a higher order intent.
 * The set of known intents and the corresponding keywords is a static data
 * structure and can be easily extended.
 */
class SimpleNlp {
public:
	SimpleNlp() = default;

	static const std::map<Intent, std::vector<std::string>> s_keywords;

	Intent guessIntent( const std::string& request ) const;
	std::string formatIntent( const Intent& ) const;

private:
	std::vector<std::string> tokenize( std::string ) const;
	bool matchBasicIntent( const Intent&, const std::vector<std::string>& ) const;
	Intent matchHigherOrderIntent( Intent a, Intent b ) const;
};
