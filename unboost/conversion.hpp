// conversion.hpp --- Unboost conversion
//////////////////////////////////////////////////////////////////////////////

#ifndef UNBOOST_CONVERSION_HPP_
#define UNBOOST_CONVERSION_HPP_

#include <unboost/core.hpp>

// If not choosed, choose one
#if ((defined(UNBOOST_USE_CXX11_CONVERSION) + defined(UNBOOST_USE_BOOST_CONVERSION)) == 0)
    #ifdef UNBOOST_USE_CXX11
        #define UNBOOST_USE_CXX11_CONVERSION
    #elif defined(UNBOOST_USE_BOOST)
        #define UNBOOST_USE_BOOST_CONVERSION
    #else
        #ifdef UNBOOST_CXX11    // C++11
            #define UNBOOST_USE_CXX11_CONVERSION
        #elif defined(_MSC_VER)
            #if (_MSC_VER >= 1600)
                // Visual C++ 2010 and later
                #define UNBOOST_USE_CXX11_CONVERSION
            #else
                #define UNBOOST_USE_BOOST_CONVERSION
            #endif
        #else
            #define UNBOOST_USE_BOOST_CONVERSION
        #endif
    #endif
#endif
#include <cstdlib>
#include <string>       // for std::string, std::wstring
#include <sstream>      // for std::stringstream
// Adapt choosed one
#ifdef UNBOOST_USE_CXX11_CONVERSION
    #include <typeinfo> // for std::bad_cast
    namespace unboost {
        class bad_lexical_cast : public std::bad_cast {
        public:
            bad_lexical_cast() { }
        };
        template <typename T, typename U>
        inline T lexical_cast(const U& value) {
            std::stringstream stream;
            stream << value;
            if (stream.fail()) {
                throw bad_lexical_cast();
            }
            T result;
            stream >> result;
            if (stream.fail()) {
                throw bad_lexical_cast();
            }
            return result;
        }
        using std::stoi;
        using std::stol;
        using std::stoul;
        using std::stoll;
        using std::stoull;
        using std::stof;
        using std::stod;
        using std::stold;
        using std::to_string;
        using std::to_wstring;
    } // namespace unboost
#elif defined(UNBOOST_USE_BOOST_CONVERSION)
    #include <boost/lexical_cast.hpp>           // for lexical_cast
    #include <boost/exception/to_string.hpp>    // for boost::to_string
    #include <climits>      // for INT_MAX, INT_MIN, FLT_MAX, ...
    #include <stdexcept>    // for std::invalid_argument, ...
    namespace unboost {
        using boost::lexical_cast;
        inline long stol(const std::string& str, size_t *pos = NULL, int base = 10) {
            long ret;
            size_t npos;
            if (pos == NULL) {
                pos = &npos;
            }
            char *end = NULL;
            ret = std::strtol(str.c_str(), &end, base);
            *pos = end - str.c_str();
            if (*pos == 0) {
                throw std::invalid_argument("stol");
            }
            return ret;
        }
        inline long stoul(const std::string& str, size_t *pos = NULL, int base = 10) {
            long ret;
            size_t npos;
            if (pos == NULL) {
                pos = &npos;
            }
            char *end = NULL;
            ret = std::strtoul(str.c_str(), &end, base);
            *pos = end - str.c_str();
            if (*pos == 0) {
                throw std::invalid_argument("stoul");
            }
            return ret;
        }
        inline int stoi(const std::string& str, size_t *pos = NULL, int base = 10) {
            long n = unboost::stol(str, pos, base);
            if (n > INT_MAX || n < INT_MIN) {
                throw std::out_of_range("stoi");
            }
            return static_cast<int>(n);
        }
        #ifdef UNBOOST_CXX11    // C++11
            inline long long
            stoll(const std::string& str, size_t *pos = NULL, int base = 10) {
                long long ret;
                size_t npos;
                if (pos == NULL) {
                    pos = &npos;
                }
                char *end = NULL;
                ret = std::strtoll(str.c_str(), &end, base);
                *pos = end - str.c_str();
                if (*pos == 0) {
                    throw std::invalid_argument("stoll");
                }
                return ret;
            }
            inline unsigned long long
            stoull(const std::string& str, size_t *pos = NULL, int base = 10) {
                unsigned long long ret;
                size_t npos;
                if (pos == NULL) {
                    pos = &npos;
                }
                char *end = NULL;
                ret = std::strtoull(str.c_str(), &end, base);
                *pos = end - str.c_str();
                if (*pos == 0) {
                    throw std::invalid_argument("stoull");
                }
                return ret;
            }
        #else   // ndef UNBOOST_CXX11
            inline __int64 stoll(const std::string& str) {
                // TODO: support pos and base
                std::stringstream stream;
                stream << str;
                __int64 result;
                stream >> result;
                if (stream.fail()) {
                    throw std::invalid_argument("stoll");
                }
                return result;
            }
            inline unsigned __int64 stoull(const std::string& str) {
                // TODO: support pos and base
                std::stringstream stream;
                stream << str;
                unsigned __int64 result;
                stream >> result;
                if (stream.fail()) {
                    throw std::invalid_argument("stoull");
                }
                return result;
            }
        #endif  // ndef UNBOOST_CXX11
        inline float stof(const std::string& str, size_t *pos = NULL) {
            double d;
            size_t npos;
            if (pos == NULL) {
                pos = &npos;
            }
            char *end = NULL;
            d = std::strtod(str.c_str(), &end);
            *pos = end - str.c_str();
            if (*pos == 0) {
                throw std::invalid_argument("stof");
            }
            if (d > FLT_MAX || d < -FLT_MAX) {
                throw std::out_of_range("stof");
            }
            float ret = static_cast<float>(d);
            return ret;
        }
        inline double stod(const std::string& str, size_t *pos = NULL) {
            double ret;
            size_t npos;
            if (pos == NULL) {
                pos = &npos;
            }
            char *end = NULL;
            ret = std::strtod(str.c_str(), &end);
            *pos = end - str.c_str();
            if (*pos == 0) {
                throw std::invalid_argument("stod");
            }
            return ret;
        }
        using boost::to_string;
        template <typename T>
        inline std::wstring to_wstring(const T& value) {
            std::wstringstream stream;
            stream << value;
            return stream.str();
        }
    } // namespace unboost
#else
    #error Your compiler is not supported yet. You lose.
#endif

#endif  // ndef UNBOOST_CONVERSION_HPP_