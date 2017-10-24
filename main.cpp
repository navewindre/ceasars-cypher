#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
 
static const char* const file_data =
R"(BCYKUNCM 1718
YFOGNSKGYW 7580
WARDA 9334
NBKL 1934
UWSZHGKSQ 9160
BQAECO 1628
EDLGDOCXZ 9297
XWXEWNV 802)";
 
char normalized_char( char in, int difference ) {
    int diff_normalized = difference % 26;
    char ret = in + diff_normalized;
    
    if ( ret < 65 ) {
        int diff = 65 - ret;
        ret = 91 - diff;
    }
    
    if ( ret > 90 ) {
        int diff = ret - 90;
        ret = 64 + diff;
    }
   
    return ret;
}
 
struct hash_t {
    std::string m_str;
    size_t      m_hash;
   
    auto decrypt( ) {
        std::string decrypted_str( m_str );
       
        for ( size_t i{ }; i < m_str.length( ); ++i ) {
            decrypted_str[ i ] = normalized_char( m_str[ i ], -int( m_hash ) );
        }
       
        return decrypted_str.c_str( );
    }
};
 
std::vector< std::string >  strings;
std::vector< hash_t >       hashes;
 
void parse_strings( ) {
    int start{ -1 };
   
    for ( size_t i{ }; i <= strlen( file_data ); ++i ) {
        if ( file_data[ i ] == '\n' || !file_data[ i ] ) {
            std::string str( file_data + start + 1, i - start - 1 );
            strings.push_back( str );
            start = i;
        }
    }
}
 
void parse_hashes( ) {
    for ( const auto& it : strings ) {
        if ( !::isdigit( it[ it.length( ) - 1 ] ) ) {
            hashes.push_back( { it, 0 } );
            continue;
        }
       
        for ( size_t i{ }; i < it.length( ); ++i ) {
            if ( it[ i ] == ' ' ) {
                std::string str = it;
                str.resize( i );
               
                auto value = static_cast< size_t >(
                    atoi( it.c_str( ) + i + 1 ) );
                   
                hashes.push_back( { str, value } );
            }
        }
    }
}
 
int main( ) {
    parse_strings( );
    parse_hashes( );
   
    for ( auto& it : hashes ) {
        printf( "string: %s hash: %lu decrypt: %s\n", it.m_str.c_str( ), it.m_hash, it.decrypt( ) );  
    }  
}
