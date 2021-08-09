#include "nlp.h"
#include <algorithm>
#include <cstring>  // strtok()

std::string intentToString( const Intent& i ) {
	switch( i ) {
	case Intent::None: return "None";
	case Intent::Fact: return "Fact";
	case Intent::Weather: return "Weather";
	case Intent::City: return "City";
	case Intent::PlaceToVisit: return "Place To visit";
	case Intent::GasStation: return "Gas station";
	case Intent::Hotel: return "Hotel";
	case Intent::Food: return "Food";
	case Intent::Emergency: return "Emergency";
	case Intent::WeatherInCity: return "Weather in city";
	case Intent::HotelInCity: return "Hotel in city";
	case Intent::PlaceToVisitInCity: return "Place to visit in city";
	case Intent::FactAboutCity: return "Fact about city";
	}
	return "ERROR";
};

//================================================

const std::map<Intent, std::vector<std::string>> SimpleNlp::s_keywords {
		{ Intent::Fact, { "interesting", "fact" } },
		{ Intent::Weather, { "weather", "rain", "thunderstorm" } },
		{ Intent::GasStation, { "gas", "petrol", "fuel" } },
		{ Intent::Hotel, { "hotel", "motel", "accommodation", "camping" } },
		{ Intent::Food, { "restaurant", "food", "pizza", "burger", "sushi" } },
		{ Intent::Emergency, { "accident", "doctor", "emergency", "injury", "crash" } },
		{ Intent::City, { "New York", "Paris", "Berlin", "Tokyo", "Freiburg", "Nuremberg", "Erlangen" } }
	};

Intent SimpleNlp::guessIntent( const std::string& request ) const {
	std::vector<std::string> input = tokenize ( request );

	std::vector<Intent> candidates;
	for ( const auto& [intent, hotwords] : s_keywords ) {
		if ( matchIntent( intent, input ) )
			candidates.push_back( intent );
	}

	if ( candidates.size() == 0 )
		return Intent::None;
	else if ( candidates.size() == 1 )
		return candidates.front();

	/**
	 * The candidates vector represents (multiple) 'basic intents' found.
	 * These have to be reduced to a 'higher order intent'.
	 *
	 * \todo Combine the found intents in vector candidates to higher
	 * level intents.
	 */
	return Intent::None;
}

bool SimpleNlp::matchIntent( const Intent& intent, const std::vector<std::string>& words ) const {
	for ( const auto& hotword : s_keywords.at( intent ) ) {
		auto it = std::find( words.begin(), words.end(), hotword );
		if ( it != words.end() ) {
			return true;
		}
	}
	return false;
}

/**
 * Extract the sequence of words from a given sentence (may be multi-line and
 * with punctuation).
 */
std::vector<std::string> SimpleNlp::tokenize( std::string sentence ) const {
	static const char delimiters[] = " \t\r\n";
	auto it = std::remove_if( sentence.begin(), sentence.end (), ispunct );
	sentence.erase ( it, sentence.end () );

	std::vector<std::string> tokens;
	/** \internal Splitting things in C++20 still seems to be an academic matter
	 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2210r0.html */
	for ( char *token = strtok( const_cast<char*>( sentence.c_str() ), delimiters );
		 token != nullptr; token = strtok(nullptr, delimiters) ) {
			 tokens.push_back( std::string(token) );
    }
	return tokens;
}

//================================================

#if false
#define CONFIG_CATCH_MAIN
#include "catch.hpp"

TEST_CASE("IntentsTest" ) {
	SimpleNlp nlp;

   SECTION("Basic Intents.") {
		Intent i = nlp.guessIntent( "Tell me an interesting fact." );
		REQUIRE( i == Intent::Fact );
		REQUIRE( formatIntent( i ) == std::string( "Intent: Get Fact" ) );

		i = nlp.guessIntent( "What is the weather like today?" );
		REQUIRE( i == Intent::Weather );
		REQUIRE( formatIntent( i ) == std::string( "Intent: Get Weather" ) );
   }

	SECTION("Complex Intents.") {
		Intent i = nlp.guessIntent( "What is the weather like in Paris today?" );
		REQUIRE( i == Intent::WeatherInCity );
		REQUIRE( formatIntent( i ) == std::string( "Intent: Get Weather City" ) );

		i = nlp.guessIntent( "Tell me a fact about Tokyo." );
		REQUIRE( i == Intent::FactAboutCity );
		REQUIRE( formatIntent( i ) == std::string( "Intent: Get Fact about City" ) );

		i = nlp.guessIntent( "Find a hotel in Freiburg." );
		REQUIRE( i == Intent::HotelInCity );
		REQUIRE( formatIntent( i ) == std::string( "Intent: Find Hotel in City" ) );
	}
}
#endif
