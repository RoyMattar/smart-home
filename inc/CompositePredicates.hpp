#ifndef COMPOSITE_PREDICATES_HPP
#define COMPOSITE_PREDICATES_HPP

namespace advcpp
{

template <typename P1, typename P2>
class AndPredicate
{
public:
    AndPredicate (P1 a_p1, P2 a_p2) NOEXCEPTIONS : m_p1(a_p1), m_p2(a_p2) { }
    bool operator() () const NOEXCEPTIONS { return m_p1() && m_p2(); }

private:
    P1 m_p1;
    P2 m_p2;
};

template <typename P1, typename P2>
AndPredicate<P1, P2> And (P1 a_p1, P2 a_p2) { return AndPredicate<P1, P2>(a_p1, a_p2); }
//template <typename P1, typename P2>
//AndPredicate<P1, P2> operator&& (P1 a_p1, P2 a_p2) { return AndPredicate<P1, P2>(a_p1, a_p2); }

template <typename P1, typename P2>
class OrPredicate
{
public:
    OrPredicate (P1 a_p1, P2 a_p2) NOEXCEPTIONS : m_p1(a_p1), m_p2(a_p2) { }
    bool operator() () const NOEXCEPTIONS { return m_p1() || m_p2(); }

private:
    P1 m_p1;
    P2 m_p2;
};

template <typename P1, typename P2>
OrPredicate<P1, P2> Or (P1 a_p1, P2 a_p2) { return OrPredicate<P1, P2>(a_p1, a_p2); }
//template <typename P1, typename P2>
//OrPredicate<P1, P2> operator|| (P1 a_p1, P2 a_p2) { return OrPredicate<P1, P2>(a_p1, a_p2); }

template <typename P>
class NotPredicate
{
public:
    NotPredicate (P a_p) NOEXCEPTIONS : m_p(a_p) { }
    bool operator() () const NOEXCEPTIONS { return !m_p(); }

private:
    P m_p;
};

template <typename P>
NotPredicate<P> Not (P a_p) { return NotPredicate<P>(a_p); }
//template <typename P>
//NotPredicate<P> operator! (P a_p) { return NotPredicate<P>(a_p); }

} // advcpp

#endif // COMPOSITE_PREDICATES_HPP