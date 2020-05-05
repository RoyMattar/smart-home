#ifndef FINDING_ALGORITHMS_HPP
#define FINDING_ALGORITHMS_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

namespace iq
{

template<class T, class Hasher = std::hash<T> >
class FindingVectorAlgorithms
{
public:
    bool FindFirstUnique(const std::vector<T>& a_vec, T& a_firstUnique);
    bool FindFirstNotUnique(const std::vector<T>& a_vec, T& a_firstUnique);
};


} //namespace iq

#include "finding_algorithms_inl.hpp"

#endif //FINDING_ALGORITHMS_HPP