///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives
  #include <string>
  #include <cstddef>
  #include <locale>
  #include <iostream>

  #include "WordFrequency.hpp"
/////////////////////// END-TO-DO (1) ////////////////////////////







// unnamed, anonymous namespace providing non-member private working area
namespace
{
  std::string sanitize( const std::string & word )
  {
    constexpr char bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";            // leading and trailing characters to be removed
    static std::locale locality;

    auto startIndex = word.find_first_not_of( bad_char );                  // start with the first non-bad character
    if( startIndex == std::string::npos ) startIndex = word.size();        // if the word contains only bad characters ...

    std::size_t count    = 0;                                              // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );              // end with the first non-bad character

    if( endIndex != std::string::npos ) count = endIndex - startIndex + 1; // number of characters to use in results

    auto result = word.substr( startIndex, count );                        // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );              // convert to lower case

    return result;
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
WordFrequency::WordFrequency(std::istream & fin) {
  std::string word = "";
  while (fin >> word) {
    word = sanitize(word);
    ++table[word];
  }
}
/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////
std::size_t WordFrequency::numberOfWords() const {
  return table.size();
}
/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////
std::size_t WordFrequency::wordCount( const std::string & theWord) const {
  std::string cleanedTheWord = sanitize(theWord);
  auto where = table.find(cleanedTheWord);
  if (where == table.end()) {
    return 0;
  }
  return where->second;
}
/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////
std::string WordFrequency::mostFrequentWord() const {
  if (!table.empty()) {
    std::size_t max = 0;
    std::string mFW = "";
    for (const auto & i : table) {
      if (i.second > max) {
        max = i.second;
        mFW = i.first;
      }
    }
    return mFW;
  }
  return "";
}
/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map
std::size_t WordFrequency::maxBucketSize() const {
  if (table.empty()) {
    return 0;
  }
  std::size_t max = 0;
  for (std::size_t i = 0; i < table.bucket_count(); ++i) {
    std::size_t currentBucket = table.bucket_size(i);
    if (currentBucket > max) {
      max = currentBucket;
    }
  }
  return max;
}
/////////////////////// END-TO-DO (6) ////////////////////////////
