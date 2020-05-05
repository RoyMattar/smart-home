#ifndef FINDING_ALGORITHMS_INL_HPP
#define FINDING_ALGORITHMS_INL_HPP

#include <algorithm>


namespace iq { namespace finding_algorithm_details
{

template<class T, class Hasher>
std::unordered_map<T, size_t, Hasher> buildFrequencies(const std::vector<T>& a_vec){
    std::unordered_map<T, size_t, Hasher> frequency;
    
    // const size_t numOfElements = a_vec.size();        
    // for(size_t i = 0; i < numOfElements; ++i)
    // {
    //     const T& element = a_vec[i];
    //     frequency[element] += 1;
    // }

    // struct Inserter {
    //     std::unordered_map<T, size_t, Hasher>& m;
    //     Inserter(std::unordered_map<T, size_t, Hasher>& m) :m(m) {}
    //     void operator()(const T& e) const {
    //         ++m[e];
    //     }
    // };
    
    // std::for_each(a_vec.begin(), a_vec.end(), Inserter(frequency) );

    for( const T& element : a_vec){
        ++frequency[element];
    }
    
    
    return frequency;
}


template<class T, class Hasher, typename Predicate>
class FrequencyPred {
    typedef std::unordered_map<T, size_t, Hasher> FrequencyMap;
    FrequencyMap const& m_frequencyMap;
    Predicate m_pred;
public:
    FrequencyPred(FrequencyMap const& f) : m_frequencyMap(f) {}
    bool operator()(T const& element) const {         
        typename FrequencyMap::const_iterator it = m_frequencyMap.find(element);
        return m_pred(it->second);
    }
};

template<class T, class Hasher, class Predicate>
bool FindFirstFrequencyPredicate(const std::vector<T>& a_vec, T& a_firstUnique)
{
    // std::unordered_map<T, size_t, Hasher> frequency = buildFrequencies<T,Hasher>(a_vec);
    auto frequency = buildFrequencies<T,Hasher>(a_vec);
    
    FrequencyPred<T, Hasher, Predicate> pred(frequency);
    //typename std::vector<T>::const_iterator it = std::find_if(a_vec.begin(), a_vec.end(), pred);
    auto it = std::find_if(a_vec.begin(), a_vec.end(), pred);
    if(it != a_vec.end()){
        a_firstUnique = *it;
        return true;
    }
    return false;
}

class FindUnique
{
public:
    bool operator()(size_t a_frequency) const;
};

bool FindUnique::operator()(size_t a_frequency) const
{
    return a_frequency == 1;
}


// res depends on input only :: pure functions
// int fx(int x){
//     return x*g_z;
// }

//Function Object
//    functor : category theory
class FindNotUnique
{
public:
    bool operator()(size_t a_frequency) const;
};

bool FindNotUnique::operator()(size_t a_frequency) const
{
    return a_frequency > 1;
}

} //namespace finding_algorithm_details

template<class T, class Hasher>
bool FindingVectorAlgorithms<T, Hasher>::FindFirstUnique(const std::vector<T>& a_vec, T& a_firstUnique)
{
    using finding_algorithm_details::FindFirstFrequencyPredicate;
    using finding_algorithm_details::FindUnique;

    return FindFirstFrequencyPredicate<T, Hasher, FindUnique>(a_vec, a_firstUnique);
}

template<class T, class Hasher>
bool FindingVectorAlgorithms<T, Hasher>::FindFirstNotUnique(const std::vector<T>& a_vec, T& a_firstUnique)
{
    using finding_algorithm_details::FindFirstFrequencyPredicate;
    using finding_algorithm_details::FindNotUnique;
    return FindFirstFrequencyPredicate<T, Hasher, FindNotUnique>(a_vec, a_firstUnique);
}

} //namespace iq

#endif //FINDING_ALGORITHMS_INL_HPP